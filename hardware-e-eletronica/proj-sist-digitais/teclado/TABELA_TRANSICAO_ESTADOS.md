# TABELA DE TRANSIÇÃO DE ESTADOS
## Decodificador de Teclado Matricial 4x4

**Projeto:** Decodificador de Teclado com Debounce e Auto-Repeat  
**Data:** 2026-04-14  
**Clock:** 1 MHz (1 ciclo = 1 µs)  

---

## 1. FSM DE DEBOUNCE E AUTO-REPEAT

### Descrição
A FSM de debounce valida leituras do teclado filtrando ruído (100 µs de estabilidade) e gerencia auto-repeat para dígitos numéricos com hold time (2s) e rate (1s).

### Estados
- **DB_IDLE:** Aguardando detecção de tecla
- **DB_COUNT:** Contando ciclos de debounce
- **DB_LOCKED:** Tecla validada, gerenciando auto-repeat

### Tabela de Transição

| Estado Atual | Condição | Próximo Estado | Ações |
|:---|:---|:---|:---|
| **DB_IDLE** | `raw_valid = 1` | DB_COUNT | `db_cnt ← 1`<br>`key_bcd ← raw_bcd` |
| **DB_IDLE** | `raw_valid = 0` | DB_IDLE | Sem ação |
| **DB_COUNT** | `raw_valid = 0` | DB_IDLE | `db_cnt ← 0` |
| **DB_COUNT** | `raw_valid = 1` AND `db_cnt < 99` | DB_COUNT | `db_cnt ← db_cnt + 1` |
| **DB_COUNT** | `raw_valid = 1` AND `db_cnt ≥ 99` | DB_LOCKED | `key_pulse ← 1`<br>`db_cnt ← 0`<br>`rep_cnt ← 0`<br>`rep_phase ← 0` |
| **DB_LOCKED** | `raw_valid = 0` | DB_IDLE | `rep_cnt ← 0`<br>`rep_phase ← 0` |
| **DB_LOCKED** | `raw_valid = 1` AND `key_bcd ≤ 9`<br>AND `rep_phase = 0`<br>AND `rep_cnt < (HOLD-1)` | DB_LOCKED | `rep_cnt ← rep_cnt + 1` |
| **DB_LOCKED** | `raw_valid = 1` AND `key_bcd ≤ 9`<br>AND `rep_phase = 0`<br>AND `rep_cnt ≥ (HOLD-1)` | DB_LOCKED | `rep_pulse ← 1`<br>`rep_cnt ← 0`<br>`rep_phase ← 1` |
| **DB_LOCKED** | `raw_valid = 1` AND `key_bcd ≤ 9`<br>AND `rep_phase = 1`<br>AND `rep_cnt < (RATE-1)` | DB_LOCKED | `rep_cnt ← rep_cnt + 1` |
| **DB_LOCKED** | `raw_valid = 1` AND `key_bcd ≤ 9`<br>AND `rep_phase = 1`<br>AND `rep_cnt ≥ (RATE-1)` | DB_LOCKED | `rep_pulse ← 1`<br>`rep_cnt ← 0` |
| **DB_LOCKED** | `raw_valid = 1` AND `key_bcd > 9` | DB_LOCKED | Sem ação<br>(sem auto-repeat) |

### Observações
- Auto-repeat **desativado** para `*` (0xA) e `#` (0xB)
- Saída `key_pulse` é um pulso de 1 ciclo
- Saída `rep_pulse` é um pulso de 1 ciclo, repetido

---

## 2. FSM PRINCIPAL (PROCESSAMENTO E VALIDAÇÃO)

### Descrição
A FSM principal acumula dígitos em um buffer de 20 posições, gerencia confirmação via `*`, reset via `#`, e implementa timeout de 5 segundos sem atividade.

### Estados
- **ST_IDLE:** Aguardando primeiro dígito
- **ST_DIGIT:** Acumulando dígitos (0-9)
- **ST_CONFIRM:** Processando confirmação (*)
- **ST_HASH:** Processando reset (#)
- **ST_TIMEOUT:** Timeout de 5 segundos
- **ST_CLR:** Limpeza e retorno a IDLE

### Tabela de Transição

| Estado Atual | Condição | Próximo Estado | Ações |
|:---|:---|:---|:---|
| **ST_IDLE** | `key_pulse = 0` | ST_IDLE | Sem ação |
| **ST_IDLE** | `key_pulse = 1` AND `key_bcd = 0xA` | ST_CONFIRM | `to_active ← 1`<br>`to_cnt ← 0`<br>`proc_cnt ← 0` |
| **ST_IDLE** | `key_pulse = 1` AND `key_bcd = 0xB` | ST_HASH | `to_active ← 1`<br>`to_cnt ← 0` |
| **ST_IDLE** | `key_pulse = 1` AND `key_bcd ≤ 9` | ST_DIGIT | `to_active ← 1`<br>`to_cnt ← 0`<br>`digitos_value[0] ← key_bcd` |
| **ST_DIGIT** | `key_pulse = 0` AND `rep_pulse = 0` | ST_DIGIT | Sem ação |
| **ST_DIGIT** | `(key_pulse = 1` OR `rep_pulse = 1)` AND `key_bcd = 0xA` | ST_CONFIRM | `to_cnt ← 0`<br>`proc_cnt ← 0` |
| **ST_DIGIT** | `(key_pulse = 1` OR `rep_pulse = 1)` AND `key_bcd = 0xB` | ST_HASH | `to_cnt ← 0` |
| **ST_DIGIT** | `(key_pulse = 1` OR `rep_pulse = 1)` AND `key_bcd ≤ 9` | ST_DIGIT | `to_cnt ← 0`<br>**SHIFT:** `digits[i] ← digits[i-1]` para i=19..1<br>`digitos_value[0] ← key_bcd` |
| **ST_CONFIRM** | `proc_cnt < 19` | ST_CONFIRM | `proc_cnt ← proc_cnt + 1` |
| **ST_CONFIRM** | `proc_cnt ≥ 19` | ST_CLR | `digitos_valid ← 1`<br>`to_active ← 0`<br>`to_cnt ← 0`<br>`proc_cnt ← 0` |
| **ST_HASH** | — | ST_CLR | `digitos_value ← {20{0xB}}`<br>`digitos_valid ← 1`<br>`to_active ← 0`<br>`to_cnt ← 0` |
| **ST_TIMEOUT** | — | ST_CLR | `digitos_value ← {20{0xE}}`<br>`digitos_valid ← 1`<br>`to_cnt ← 0` |
| **ST_CLR** | — | ST_IDLE | `digitos_value ← {20{0xF}}`<br>`proc_cnt ← 0` |

### Timeout Global (Condição Especial)

| Condição | Ação |
|:---|:---|
| `to_active = 1` AND `to_cnt ≥ (TIMEOUT_VAL - 1)` | `to_active ← 0`<br>`to_cnt ← 0`<br>`fsm ← ST_TIMEOUT`<br>(Aplicável em qualquer estado) |

---

## 3. MAPA DE CÓDIGOS BCD DE SAÍDA

| Código | Significado | Contexto |
|:---|:---|:---|
| 0x0-0x9 | Dígitos 0-9 | Buffer normal |
| 0xA | Asterisco (*) | Confirmação |
| 0xB | Hash (#) | Reset ou erro via hash |
| 0xE | Erro | Timeout de 5 segundos |
| 0xF | Inválido | Posições não preenchidas |

---

## 4. PARÂMETROS DE TEMPORIZAÇÃO

| Parâmetro | Símbolo | Valor | Descrição |
|:---|:---|:---|:---|
| Debounce | DEBOUNCE_VAL | 100 µs | Tempo de estabilidade mínima |
| Processamento | PROCESS_VAL | 20 µs | Delay de confirmação |
| Hold Time | HOLD_VAL | 2 s | Espera antes de auto-repeat |
| Taxa de Repetição | RATE_VAL | 1 s | Intervalo de auto-repeat |
| Timeout Global | TIMEOUT_VAL | 5 s | Timeout sem atividade |

---

## 5. SINAIS INTERNOS E EXTERNAS

### Entradas
| Sinal | Tipo | Descrição |
|:---|:---|:---|
| `clk` | input logic | Clock de 1 MHz |
| `rst` | input logic | Reset síncrono (ativo alto) |
| `enable` | input logic | Habilita processamento |
| `col_matriz[3:0]` | input logic | Colunas do teclado (active-low) |

### Saídas
| Sinal | Tipo | Descrição |
|:---|:---|:---|
| `lin_matriz[3:0]` | output logic | Linhas do teclado (active-low) |
| `digitos_value` | output senhaPac_t | Buffer de 20 × 4 bits |
| `digitos_valid` | output logic | Pulso de validação (1 ciclo) |

### Sinais Internos (Debounce)
| Sinal | Tipo | Descrição |
|:---|:---|:---|
| `db_st` | db_st_t | Estado da FSM debounce |
| `db_cnt[6:0]` | logic | Contador debounce (0-100) |
| `key_bcd[3:0]` | logic | Código BCD capturado |
| `key_pulse` | logic | Pulso debounce completo |
| `rep_cnt[20:0]` | logic | Contador auto-repeat |
| `rep_phase` | logic | Fase auto-repeat (0=hold, 1=rate) |
| `rep_pulse` | logic | Pulso auto-repeat |

### Sinais Internos (Principal)
| Sinal | Tipo | Descrição |
|:---|:---|:---|
| `fsm` | fsm_t | Estado da FSM principal |
| `proc_cnt[4:0]` | logic | Contador processamento |
| `to_cnt[22:0]` | logic | Contador timeout |
| `to_active` | logic | Timeout ativado |

---

## 6. CONDIÇÕES ESPECIAIS

### Enable Control
```
Se enable = 0:
  → Nenhuma transição ocorre
  → FSM congelada no estado atual
  → Contadores mantêm valores
  → Saídas congeladas

Se enable = 1:
  → Operação normal
```

### Reset
```
Se rst = 1:
  → db_st ← DB_IDLE
  → fsm ← ST_IDLE
  → Todos os contadores ← 0
  → digitos_value ← {20{0xF}}
  → digitos_valid ← 0
```

### Controle de Buffer
```
SHIFT (ST_DIGIT com novo dígito):
  digitos_value.digits[19:1] ← digitos_value.digits[18:0]
  digitos_value.digits[0] ← new_bcd
  
Resultado: Novo dígito entra em [0], ältesten sai de [19]
```

---

## 7. FLUXO DE EXECUÇÃO TÍPICO

### Cenário: Pressionar 1, 2 e confirmar com *

```
[t=0µs]     RESET ativo
            db_st = DB_IDLE, fsm = ST_IDLE
            
[t=2µs]     RESET liberado
            Sistema operacional
            
[t=2µs]     Pressionar TECLA 1 (sincronizado com scan)
            col_matriz ← 0111 (coluna 0)
            raw_valid ← 1, raw_bcd ← 0x1
            
[t=3µs]     db_st → DB_COUNT
            db_cnt ← 1, key_bcd ← 0x1
            
[~t=101µs]  db_cnt ≥ 99 (100 ciclos decorridos)
            db_st → DB_LOCKED
            key_pulse ← 1 (pulso)
            
[~t=101µs]  fsm = ST_IDLE, key_pulse = 1, key_bcd = 0x1
            fsm → ST_DIGIT
            to_active ← 1, to_cnt ← 0
            digitos_value.digits[0] ← 0x1
            
[t=111µs]   Pressionar TECLA 2
            col_matriz ← 1011 (coluna 1)
            raw_valid ← 1, raw_bcd ← 0x2
            
[~t=211µs]  key_pulse ← 1 (segunda vez)
            
[~t=211µs]  fsm = ST_DIGIT, key_pulse = 1, key_bcd = 0x2
            SHIFT buffer: digits[1] ← digits[0] (0x1)
            digitos_value.digits[0] ← 0x2
            
[t=221µs]   Pressionar TECLA * (confirmação)
            col_matriz ← 0111 (coluna 0, linha 3)
            raw_valid ← 1, raw_bcd ← 0xA
            
[~t=321µs]  key_pulse ← 1 (terceira vez)
            
[~t=321µs]  fsm = ST_DIGIT, key_pulse = 1, key_bcd = 0xA (*)
            fsm → ST_CONFIRM
            proc_cnt ← 0
            
[t=321µs até ~341µs]
            proc_cnt incrementa de 0 até 19 (20 ciclos)
            
[~t=341µs]  proc_cnt ≥ 19
            digitos_valid ← 1 (pulso)
            Buffer enviado:
              digits[19:2] = 0xF (inválido)
              digits[1] = 0x1 (primeiro dígito)
              digits[0] = 0x2 (segundo dígito)
            fsm → ST_CLR
            
[~t=361µs]  fsm = ST_CLR
            digitos_value ← {20{0xF}} (reseta buffer)
            fsm → ST_IDLE
            
[~t=381µs]  Sistema pronto para nova sequência
```

---

## 8. LEGENDA DE SÍMBOLOS

| Símbolo | Significado |
|:---|:---|
| `←` | Atribuição não-bloqueante (`<=` em Verilog) |
| `AND` | Operador lógico E |
| `OR` | Operador lógico OU |
| `≤` | Menor ou igual |
| `≥` | Maior ou igual |
| `<` | Menor que |
| `>` | Maior que |
| `=` | Igual |
| `≠` | Diferente |
| `—` | Não aplicável / Transição incondicional |
| `[N:M]` | Bits N até M de um sinal |
| `{N{X}}` | Replicação: N cópias de X |

---

## 9. CASOS ESPECIAIS E TRATAMENTO DE ERROS

### Caso 1: Tecla Pressionada > 5 segundos
```
to_active = 1 durante todo tempo
to_cnt incrementa continuamente
Quando to_cnt ≥ 5.000.000:
  → fsm ← ST_TIMEOUT
  → digitos_value ← {20{0xE}}
  → digitos_valid ← 1 (pulso)
  → fsm ← ST_CLR → ST_IDLE
```

### Caso 2: Múltiplas Teclas Pressionadas Simultaneamente
```
Versão atual: Não suportado
A matriz foi projetada para detectar uma célula por vez
Se múltiplas colunas forem ativas:
  → Case statement toma a primeira correspondência
  → Resultado imprevisível
Recomendação: Adicionar validação de entrada
```

### Caso 3: Enable = 0 Durante Processamento
```
Se enable = 0:
  → Nenhuma FSM progride
  → Contadores congelados
  → Buffer retem valores
  → Saídas congeladas
  
Ao reativar enable = 1:
  → Sistema retoma exatamente onde parou
  → Timeout continua a contar (se to_active = 1)
```

### Caso 4: Reset During Processing
```
Se rst = 1:
  → Ambas FSMs retornam a IDLE/inicial
  → Todos contadores zerados
  → Buffer preenchido com 0xF
  → Qualquer operação em progresso é perdida
```

---

## 10. RESUMO DE ESTADOS FINAIS

### Situações de Saída

| Situação | digitos_value | digitos_valid | fsm | Descrição |
|:---|:---|:---|:---|:---|
| Confirmação (*) | Sequência com 0xF | 1 (pulso) | ST_CLR | Normal |
| Reset (#) | {20{0xB}} | 1 (pulso) | ST_CLR | Usuário reset |
| Timeout 5s | {20{0xE}} | 1 (pulso) | ST_CLR | Timeout |
| Sem confirmação | {20{0xF}} | 0 | ST_IDLE | Estado inicial |
| Processando | Parcial | 0 | ST_DIGIT | Acumulando |

---

**FIM DO DOCUMENTO**

Data de Geração: 2026-04-14  
Versão: 1.0  
Status: ✅ APROVADO
