module decodificador_de_teclado (
    input  logic        clk,
    input  logic        rst,
    input  logic        enable,
    input  logic [3:0]  col_matriz,
    output logic [3:0]  lin_matriz,
    output senhaPac_t   digitos_value,
    output logic        digitos_valid
);


    // =========================
    // FSM
    // =========================
    typedef enum logic [3:0] {
        IDLE,
        SCAN,
        DETECT,
        DEBOUNCE,
        DECODE,
        STORE,
        ENTER,
        CLEAR,
        BIP,
        RESET,
        DELAY_2S,
        DELAY_1S    
    } state_t;

    state_t state, next_state;