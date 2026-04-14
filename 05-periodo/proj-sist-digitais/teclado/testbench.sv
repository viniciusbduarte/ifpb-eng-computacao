`timescale 1ns/1ns

module testbench;

  logic clk;
  logic rst;
  logic enable;
  logic [3:0] col_matriz;
  logic [3:0] lin_matriz;
  senhaPac_t digitos_value;
  logic digitos_valid;

  decodificador_de_teclado dut(
    .clk(clk),
    .rst(rst),
    .enable(enable),
    .col_matriz(col_matriz),
    .lin_matriz(lin_matriz),
    .digitos_value(digitos_value),
    .digitos_valid(digitos_valid)
  );

  always #500ns clk = ~clk;

  // Task para pressionar tecla sincronizada com varredura
  task pressionar_tecla(input int linha, input int coluna);
    logic [3:0] col_code;
    logic [3:0] lin_code;
    int tempo_inicio;

    case (coluna)
      0: col_code = 4'b0111;
      1: col_code = 4'b1011;
      2: col_code = 4'b1101;
      default: col_code = 4'b1111;
    endcase

    case (linha)
      0: lin_code = 4'b0111;
      1: lin_code = 4'b1011;
      2: lin_code = 4'b1101;
      default: lin_code = 4'b1110;
    endcase

    $display("[%0t] Pressionar: Linha %d, Coluna %d", $time, linha, coluna);

    // Aguarda a linha correta aparecer
    while (dut.lin_matriz !== lin_code) #1us;
    $display("[%0t] Linha sincronizada - Ativando coluna", $time);

    // Ativa coluna
    col_matriz = col_code;
    tempo_inicio = $time;
    #1us;

    // Mantém por 500 µs de TEMPO REAL (não ciclos)
    while (($time - tempo_inicio) < 500000) begin
      #1us;
    end

    col_matriz = 4'b1111;
    $display("[%0t] Tecla liberada", $time);
  endtask

  initial begin
    $dumpfile("sim.vcd");
    $dumpvars(0, testbench);

    clk = 0;
    rst = 1;
    enable = 1;
    col_matriz = 4'b1111;

    #2us;
    rst = 0;
    $display("[%0t] Sistema inicializado", $time);

    $display("\n=== TESTE 1: Tecla 1 ===");
    pressionar_tecla(0, 0);
    #10us;

    $display("\n=== TESTE 2: Tecla 2 ===");
    pressionar_tecla(0, 1);
    #10us;

    $display("\n=== TESTE 3: Tecla * (Confirmar) ===");
    pressionar_tecla(3, 0);
    #50us;

    $display("\n=== FIM ===");
    $finish;
  end

  always @(posedge digitos_valid) begin
    $display("[%0t] *** VALIDADO: %h ***", $time, digitos_value);
  end

  always @(posedge dut.key_pulse) begin
    $display("[%0t] key_pulse: %h", $time, dut.key_bcd);
  end

endmodule
