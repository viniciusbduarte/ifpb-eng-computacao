#include <stdio.h>
#include <string.h>
#include <math.h>

// Função para converter binário invertido (usando 'X' para 0 e 'O' para 1) em decimal
int binaryToDecimal(char *binary) {
    int decimal = 0;
    for (int i = 0; binary[i] != '\0'; i++) {
        int digit = (binary[i] == 'O') ? 1 : 0;  // Agora 'O' representa 1 e 'X' representa 0
        decimal += digit * pow(2, i);
    }
    return decimal;
}

// Função para converter um número decimal em binário invertido usando 'X' e 'O'
void decimalToBinary(int decimal, char *binary, int minBits) {
    int index = 0;
    while (decimal > 0) {
        binary[index++] = (decimal % 2) ? 'O' : 'X';  // Agora 1 é representado por 'O' e 0 por 'X'
        decimal /= 2;
    }

    // Preencher com 'X' até atingir o número mínimo de bits
    while (index < minBits) {
        binary[index++] = 'X';
    }

    binary[index] = '\0';
}

// Função para inverter uma string
void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int main() {
    int repetitions;

    scanf("%d", &repetitions);

    for (int i = 0; i < repetitions; i++) {
        char binaryInput[50] = "";   // Zera o conteúdo de binaryInput a cada repetição
        int decimalToAdd = 0;        // Zera o valor de decimalToAdd a cada repetição
        int decimalValue = 0;        // Zera o valor de decimalValue a cada repetição
        char binaryResult[50] = "";  // Zera o conteúdo de binaryResult a cada repetição

        scanf("%s %d", binaryInput, &decimalToAdd);

        // Calcular o número de bits com base no tamanho do binário invertido de entrada
        int minBits = strlen(binaryInput);

        // Converter o binário invertido para decimal
        decimalValue = binaryToDecimal(binaryInput);

        // Somar o valor decimal fornecido
        int sum = decimalValue + decimalToAdd;

        // Converter o resultado da soma para binário invertido com 'X' e 'O'
        decimalToBinary(sum, binaryResult, minBits);

        // Inverter a string para o formato correto
        reverseString(binaryResult);

    }

    return 0;
}
