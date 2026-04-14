// ================================================================
// Módulo: decodificador_de_teclado
// Descrição: Lê teclado matricial 4x4, aplica debounce, auto-repeat
//            e timeout. Saída: vetor de 20 dígitos BCD + pulso de
//            validação de 1 ciclo.
// Clock esperado: 1 MHz (1 ciclo = 1 µs)
// ================================================================

`timescale 1us / 1ns

// Struct para armazenar sequência de dígitos capturados
// Array de 20 posições, cada uma contendo um dígito BCD (4 bits)
// digits[19] = dígito mais antigo / digits[0] = dígito mais recente
typedef struct packed {
    logic [19:0][3:0] digits;
} senhaPac_t;

module decodificador_de_teclado (
    // Sinais de controle
    input  logic       clk,           // Clock de 1 MHz
    input  logic       rst,           // Reset síncrono, ativo em alto
    input  logic       enable,        // Ativa processamento a cada ciclo
    // Interface com teclado matricial (active-low)
    input  logic [3:0] col_matriz,    // Colunas (entrada - sensores)
    output logic [3:0] lin_matriz,    // Linhas (saída - ativa uma linha por vez)
    // Saídas
    output senhaPac_t  digitos_value, // Buffer com sequência capturada
    output logic       digitos_valid  // Pulso de 1 ciclo indicando saída pronta
);

    // -----------------------------------------------------------
    // Parâmetros de temporização (1 MHz → 1 ciclo = 1 µs)
    // -----------------------------------------------------------
    // Debounce: aguarda 100 µs (100 ciclos) de chave pressionada
    localparam logic [6:0]  DEBOUNCE_VAL = 7'd100;
    // Processamento: delay de 20 µs para confirmar dígito
    localparam logic [4:0]  PROCESS_VAL  = 5'd20;
    // Hold time: 2 s de espera antes de iniciar auto-repeat
    localparam logic [20:0] HOLD_VAL     = 21'd2_000_000;
    // Rate: intervalo de 1 s entre repetições automáticas
    localparam logic [20:0] RATE_VAL     = 21'd1_000_000;
    // Timeout: reseta sequência após 5 s sem atividade
    localparam logic [22:0] TIMEOUT_VAL  = 23'd5_000_000;

    // -----------------------------------------------------------
    // Varredura de linhas (active-low)
    // Percorre as 4 linhas da matriz sequencialmente
    // -----------------------------------------------------------
    // Índice de varredura: 0-3 representando as 4 linhas
    logic [1:0] scan_idx;

    // Incrementa índice de varredura a cada ciclo (quando enable=1)
    // Após atingir 3, volta para 0 (contador de 4 estados)
    always_ff @(posedge clk) begin
        if (rst)         scan_idx <= 2'd0;
        else if (enable) scan_idx <= scan_idx + 2'd1;
    end

    // Decodificador combinacional: converte scan_idx para linha ativa (active-low)
    // Uma linha é ativada por vez, as outras ficam em repouso
    always_comb begin
        case (scan_idx)
            2'd0:    lin_matriz = 4'b0111;  // Linha 0 ativa (bit 0 = 0)
            2'd1:    lin_matriz = 4'b1011;  // Linha 1 ativa (bit 1 = 0)
            2'd2:    lin_matriz = 4'b1101;  // Linha 2 ativa (bit 2 = 0)
            default: lin_matriz = 4'b1110;  // Linha 3 ativa (bit 3 = 0)
        endcase
    end

    // -----------------------------------------------------------
    // Decodificação da matriz (linha × coluna)
    // Converte combinação de linha e coluna ativa em código BCD
    // -----------------------------------------------------------
    // Código BCD do dígito detectado (0-9, A=*, B=#, F=inválido)
    logic [3:0] raw_bcd;
    // Flag informando que existe uma combinação linha-coluna válida
    logic       raw_valid;

    // Busca tabela de códigos da matriz 4x4 do teclado
    // Entrada: combinação {lin_matriz, col_matriz}
    // Saída: dígito BCD + flag de validade
    always_comb begin
        // Valores padrão: sem tecla pressionada
        raw_bcd   = 4'hF;  // 0xF = código inválido
        raw_valid = 1'b0;
        // Decodificação: testa todas as combinações linha-coluna ativas
        case ({lin_matriz, col_matriz})
            {4'b0111, 4'b0111}: begin raw_bcd = 4'h1; raw_valid = 1'b1; end  // Lin0-Col0 = 1
            {4'b0111, 4'b1011}: begin raw_bcd = 4'h2; raw_valid = 1'b1; end  // Lin0-Col1 = 2
            {4'b0111, 4'b1101}: begin raw_bcd = 4'h3; raw_valid = 1'b1; end  // Lin0-Col2 = 3
            {4'b1011, 4'b0111}: begin raw_bcd = 4'h4; raw_valid = 1'b1; end  // Lin1-Col0 = 4
            {4'b1011, 4'b1011}: begin raw_bcd = 4'h5; raw_valid = 1'b1; end  // Lin1-Col1 = 5
            {4'b1011, 4'b1101}: begin raw_bcd = 4'h6; raw_valid = 1'b1; end  // Lin1-Col2 = 6
            {4'b1101, 4'b0111}: begin raw_bcd = 4'h7; raw_valid = 1'b1; end  // Lin2-Col0 = 7
            {4'b1101, 4'b1011}: begin raw_bcd = 4'h8; raw_valid = 1'b1; end  // Lin2-Col1 = 8
            {4'b1101, 4'b1101}: begin raw_bcd = 4'h9; raw_valid = 1'b1; end  // Lin2-Col2 = 9
            {4'b1110, 4'b1011}: begin raw_bcd = 4'h0; raw_valid = 1'b1; end  // Lin3-Col1 = 0
            {4'b1110, 4'b0111}: begin raw_bcd = 4'hA; raw_valid = 1'b1; end  // Lin3-Col0 = * (A)
            {4'b1110, 4'b1101}: begin raw_bcd = 4'hB; raw_valid = 1'b1; end  // Lin3-Col2 = # (B)
            default:;  // Demais combinações são inválidas
        endcase
    end

    // -----------------------------------------------------------
    // FSM de debounce e auto-repeat
    // Filtra leitura ruidosa, detecta liberação da tecla e gera
    // pulsos de repetição automática com hold time e rate customizáveis
    // -----------------------------------------------------------
    // Estados da máquina: espera → contagem → travado
    // DB_IDLE: aguardando tecla pressionada
    // DB_COUNT: contando ciclos de debounce
    // DB_LOCKED: tecla validada, gerenciando auto-repeat
    typedef enum logic [1:0] { DB_IDLE, DB_COUNT, DB_LOCKED } db_st_t;

    // Estado atual da FSM de debounce
    db_st_t     db_st;
    // Contador de debounce (máx 100 ciclos = 100 µs)
    logic [6:0] db_cnt;
    // Código BCD da tecla capturada e validada
    logic [3:0] key_bcd;
    // Pulso indicando que debounce terminou (1 ciclo)
    logic       key_pulse;
    // Contador para auto-repeat: hold inicial + rate contínuo
    logic [20:0] rep_cnt;
    // Flag diferenciando hold phase (0) de repeat rate phase (1)
    logic        rep_phase;
    // Pulso de auto-repeat (1 ciclo, repetido a cada RATE_VAL)
    logic        rep_pulse;

    // Máquina de estados para debounce e auto-repeat
    // Responsável por validar leitura da tecla e gerar pulsos de acionamento
    always_ff @(posedge clk) begin
        if (rst) begin
            // Reinicia todos os sinais para estado inicial
            db_st     <= DB_IDLE;
            db_cnt    <= '0;          // Zera contador de debounce
            key_bcd   <= 4'hF;        // Código inválido
            key_pulse <= 1'b0;        // Sem pulso
            rep_cnt   <= '0;          // Zera contador de repetição
            rep_phase <= 1'b0;        // Fase hold (não está em repetição)
            rep_pulse <= 1'b0;        // Sem pulso de repetição
        end else if (enable) begin
            // Default: limpa pulsos de saída (são asserts por 1 ciclo)
            key_pulse <= 1'b0;
            rep_pulse <= 1'b0;

            case (db_st)
                // Estado IDLE: espera por uma tecla pressionada
                DB_IDLE: begin
                    if (raw_valid) begin
                        // Detectou sinal de entrada → inicia contagem de debounce
                        db_cnt  <= 7'd1;
                        key_bcd <= raw_bcd;     // Salva código da tecla
                        db_st   <= DB_COUNT;    // Vai para contador
                    end
                end

                // Estado COUNT: aguarda 100 ciclos com mesma tecla (debounce)
                DB_COUNT: begin
                    if (!raw_valid) begin
                        // Sinal desapareceu → tecla falsa, volta para IDLE
                        db_st  <= DB_IDLE;
                        db_cnt <= '0;
                    end else if (db_cnt >= DEBOUNCE_VAL - 7'd1) begin
                        // Completou debounce → gera pulso e move para travado
                        key_pulse <= 1'b1;      // Pulso de 1 ciclo
                        db_cnt    <= '0;        // Reseta contador
                        rep_cnt   <= '0;        // Zera auto-repeat
                        rep_phase <= 1'b0;      // Enter hold phase
                        db_st     <= DB_LOCKED; // Tecla validada
                    end else begin
                        // Continua contando ciclos
                        db_cnt <= db_cnt + 7'd1;
                    end
                end

                // Estado LOCKED: tecla pressionada, gerencia auto-repeat
                DB_LOCKED: begin
                    if (!raw_valid) begin
                        // Tecla foi liberada → volta para IDLE
                        db_st     <= DB_IDLE;
                        rep_cnt   <= '0;
                        rep_phase <= 1'b0;
                    end else if (key_bcd <= 4'h9) begin
                        // Só auto-repeat dígitos 0-9 (não * nem #)
                        rep_cnt <= rep_cnt + 21'd1;

                        // Hold phase (espera 2 s antes de começar repetição)
                        if (!rep_phase && rep_cnt >= HOLD_VAL - 21'd1) begin
                            rep_pulse <= 1'b1;      // Gera pulso
                            rep_cnt   <= '0;        // Reseta para rate
                            rep_phase <= 1'b1;      // Enter rate phase
                        end
                        // Rate phase (repete a cada 1 s)
                        else if (rep_phase && rep_cnt >= RATE_VAL - 21'd1) begin
                            rep_pulse <= 1'b1;      // Gera pulso
                            rep_cnt   <= '0;        // Reseta para próxima repetição
                        end
                    end
                end

                default: db_st <= DB_IDLE;
            endcase
        end
    end

    // -----------------------------------------------------------
    // FSM principal: vetor de saída, timeout e validação
    // Gerencia acúmulo de dígitos, confirmação por * e reset por #
    // Implementa timeout de 5 s sem atividade
    // -----------------------------------------------------------
    // Estados da FSM principal
    // ST_IDLE: aguardando primeiro dígito
    // ST_DIGIT: acumulando dígitos (0-9)
    // ST_CONFIRM: confirmando sequência (pressionou *)
    // ST_HASH: reseta (pressionou #)
    // ST_TIMEOUT: sequência expirou (5 s sem atividade)
    // ST_CLR: limpando, volta para IDLE
    typedef enum logic [2:0] {
        ST_IDLE, ST_DIGIT, ST_CONFIRM, ST_HASH, ST_TIMEOUT, ST_CLR
    } fsm_t;

    // Estado atual da FSM
    fsm_t        fsm;
    // Contador de processamento (delay de confirmação)
    logic [4:0]  proc_cnt;
    // Contador de timeout global (máx 5 s)
    logic [22:0] to_cnt;
    // Flag indicando que timeout está ativo
    logic        to_active;

    // Máquina de estados principal
    // Acumula dígitos, gerencia timeout, confirma ou reseta sequência
    always_ff @(posedge clk) begin
        if (rst) begin
            // Reinicia estado para buffer limpo
            digitos_value.digits <= {20{4'hF}};  // Preenche com código inválido (0xF)
            digitos_valid <= 1'b0;               // Sem pulso de validação
            fsm           <= ST_IDLE;            // Volta para estado de espera
            to_active     <= 1'b0;               // Timeout desativo
            to_cnt        <= '0;
            proc_cnt      <= '0;
        end else if (enable) begin
            // Default: limpa pulso de validação (assert por 1 ciclo)
            digitos_valid <= 1'b0;

            // Timeout global de 5 s (ativo sempre que to_active=1)
            // Timeout ativo: incrementa contador; se atingir limite, força timeout
            if (to_active) begin
                if (to_cnt >= TIMEOUT_VAL - 23'd1) begin
                    // Espirou 5 s → entra em estado de timeout
                    to_active <= 1'b0;
                    to_cnt    <= '0;
                    fsm       <= ST_TIMEOUT;
                end else begin
                    // Continua contando
                    to_cnt <= to_cnt + 23'd1;
                end
            end

            case (fsm)
                // Estado IDLE: espera primeiro dígito ou tecla especial
                ST_IDLE: begin
                    if (key_pulse) begin
                        // Recebeu pulso de tecla → ativa timeout
                        to_active <= 1'b1;
                        to_cnt    <= '0;
                        if (key_bcd == 4'hA) begin
                            // * (confirmação): confirma sequência vazia
                            proc_cnt <= '0;         // Zera contador de delay
                            fsm <= ST_CONFIRM;
                        end else if (key_bcd == 4'hB) begin
                            // # (reset): limpa (mesmo sem dígitos)
                            fsm <= ST_HASH;
                        end else begin
                            // Dígito 0-9: insere na posição 0
                            digitos_value.digits[0] <= key_bcd;
                            fsm <= ST_DIGIT;
                        end
                    end
                end

                // Estado DIGIT: acumulando dígitos (pode vir de key_pulse ou rep_pulse)
                ST_DIGIT: begin
                    if (key_pulse || rep_pulse) begin
                        // Recebeu novo acionamento → reseta contador de timeout
                        to_cnt <= '0;
                        if (key_bcd == 4'hA) begin
                            // * (confirmação)
                            proc_cnt <= '0;         // Zera contador de delay
                            fsm <= ST_CONFIRM;
                        end else if (key_bcd == 4'hB) begin
                            // # (reset)
                            fsm <= ST_HASH;
                        end else begin
                            // Dígito: desloca array para esquerda (posições antigas se perdem)
                            // Novo dígito entra em digits[0]; digits[19] sai do buffer
                            digitos_value.digits[19] <= digitos_value.digits[18];
                            digitos_value.digits[18] <= digitos_value.digits[17];
                            digitos_value.digits[17] <= digitos_value.digits[16];
                            digitos_value.digits[16] <= digitos_value.digits[15];
                            digitos_value.digits[15] <= digitos_value.digits[14];
                            digitos_value.digits[14] <= digitos_value.digits[13];
                            digitos_value.digits[13] <= digitos_value.digits[12];
                            digitos_value.digits[12] <= digitos_value.digits[11];
                            digitos_value.digits[11] <= digitos_value.digits[10];
                            digitos_value.digits[10] <= digitos_value.digits[9];
                            digitos_value.digits[9]  <= digitos_value.digits[8];
                            digitos_value.digits[8]  <= digitos_value.digits[7];
                            digitos_value.digits[7]  <= digitos_value.digits[6];
                            digitos_value.digits[6]  <= digitos_value.digits[5];
                            digitos_value.digits[5]  <= digitos_value.digits[4];
                            digitos_value.digits[4]  <= digitos_value.digits[3];
                            digitos_value.digits[3]  <= digitos_value.digits[2];
                            digitos_value.digits[2]  <= digitos_value.digits[1];
                            digitos_value.digits[1]  <= digitos_value.digits[0];
                            digitos_value.digits[0]  <= key_bcd;
                        end
                    end
                end

                // Estado CONFIRM: processa confirmação (aguarda 20 µs de delay)
                ST_CONFIRM: begin
                    if (proc_cnt >= PROCESS_VAL - 5'd1) begin
                        // Completou delay → gera pulso de validação
                        digitos_valid <= 1'b1;      // Pulso de 1 ciclo
                        proc_cnt      <= '0;
                        to_active     <= 1'b0;      // Desativa timeout
                        to_cnt        <= '0;
                        fsm           <= ST_CLR;    // Prepara limpeza
                    end else begin
                        // Continua aguardando delay
                        proc_cnt <= proc_cnt + 5'd1;
                    end
                end

                // Estado HASH: tecla # pressionada (reset)
                // digitos_valid pulsa por 1 ciclo pois é zerado no início do bloco (always_ff)
                ST_HASH: begin
                    digitos_value.digits <= {20{4'hB}};  // Preenche com # (código 0xB)
                    digitos_valid <= 1'b1;               // Pulso de saída (1 ciclo)
                    to_active     <= 1'b0;               // Desativa timeout
                    to_cnt        <= '0;
                    fsm           <= ST_CLR;
                end

                // Estado TIMEOUT: sequência expirou (5 s sem atividade)
                ST_TIMEOUT: begin
                    digitos_value.digits <= {20{4'hE}};  // Preenche com código de erro
                    digitos_valid <= 1'b1;               // Pulso de saída
                    to_cnt        <= '0;
                    fsm           <= ST_CLR;
                end

                // Estado CLR: limpeza e retorno para IDLE
                ST_CLR: begin
                    // Reseta vetor para estado inicial
                    digitos_value.digits <= {20{4'hF}};  // Preenche com código inválido
                    proc_cnt      <= '0;                 // Zera contador de processamento
                    fsm           <= ST_IDLE;            // Volta para espera
                end

                default: fsm <= ST_IDLE;
            endcase
        end
    end

endmodule