/*==============================================================================
 * Nome do Programa: [Nome do programa]
 * Descrição       : [Descrição do que o programa faz]
 * Autor           : [Seu nome]
 * Data de Criação : [Data]
 * Última Modificação: [Data da última modificação]
 * Versão          : [Versão do programa, ex: 1.0]
 *==============================================================================
 */ 

//========================= BIBLIOTECAS =======================================
#include <stdio.h>
// [Outras bibliotecas necessárias]

//========================= CONSTANTES GLOBAIS ===============================
/* Defina aqui constantes globais, se necessário. */
#define EXEMPLO_CONSTANTE 100

//========================= VARIÁVEIS GLOBAIS ===============================
/* Declare aqui variáveis globais, se necessário. */
int variavelGlobal = 0;

//========================= PROTÓTIPOS DE FUNÇÕES ============================
/* Liste os protótipos das funções aqui. */
void exemploFuncao(void);

//========================= FUNÇÃO PRINCIPAL ================================
int main() {
    /*
     * Descrição:
     * Função principal do programa. Realiza a execução principal.
     */
    printf("Olá, mundo!\n");

    // Chamada de funções auxiliares
    exemploFuncao();

    return 0;
}

//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ========================
void exemploFuncao(void) {
    /*
     * Descrição:
     * Exemplo de função auxiliar.
     */
    printf("Executando a função auxiliar!\n");
}
