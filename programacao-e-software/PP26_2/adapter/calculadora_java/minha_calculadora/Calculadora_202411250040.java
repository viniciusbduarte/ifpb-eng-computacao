/**
 * Calculadora_202411250040
 *
 * Biblioteca que implementa as quatro operações matemáticas básicas:
 * soma, subtração, multiplicação e divisão.
 *
 * Autor: Vinicius Batista Duarte
 * Matrícula: 202411250040
 */
public class Calculadora_202411250040 {

    /**
     * Realiza a soma de dois números.
     * @param a primeiro operando
     * @param b segundo operando
     * @return resultado da soma (a + b)
     */
    public double somar(double a, double b) {
        return a + b;
    }

    /**
     * Realiza a subtração de dois números.
     * @param a minuendo
     * @param b subtraendo
     * @return resultado da subtração (a - b)
     */
    public double subtrair(double a, double b) {
        return a - b;
    }

    /**
     * Realiza a multiplicação de dois números.
     * @param a primeiro fator
     * @param b segundo fator
     * @return resultado da multiplicação (a * b)
     */
    public double multiplicar(double a, double b) {
        return a * b;
    }

    /**
     * Realiza a divisão de dois números.
     * @param a dividendo
     * @param b divisor
     * @return resultado da divisão (a / b)
     * @throws ArithmeticException caso o divisor (b) seja igual a zero
     */
    public double dividir(double a, double b) {
        if (b == 0) {
            throw new ArithmeticException("Divisão por zero não é permitida.");
        }
        return a / b;
    }
}