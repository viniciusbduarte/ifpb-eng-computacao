/**
 * Cliente_202411250040
 *
 * Classe responsável por consumir a biblioteca Calculadora_202411250040,
 * disparando uma sequência de chamadas às operações públicas dela.
 *
 * Autor: Vinicius Batista Duarte
 * Matrícula: 202411250040
 */
public class Cliente_202411250040 {

    public static void main(String[] args) {

        Calculadora_202411250040 calculadora = new Calculadora_202411250040();

        double a = 10.0;
        double b = 5.0;

        System.out.println("===== Sistema de Operações Matemáticas Básicas =====");
        System.out.println("Valores utilizados: a = " + a + " | b = " + b);
        System.out.println();

        double resultadoSoma = calculadora.somar(a, b);
        System.out.println("Soma:            " + a + " + " + b + " = " + resultadoSoma);

        double resultadoSubtracao = calculadora.subtrair(a, b);
        System.out.println("Subtração:       " + a + " - " + b + " = " + resultadoSubtracao);

        double resultadoMultiplicacao = calculadora.multiplicar(a, b);
        System.out.println("Multiplicação:   " + a + " * " + b + " = " + resultadoMultiplicacao);

        try {
            double resultadoDivisao = calculadora.dividir(a, b);
            System.out.println("Divisão:         " + a + " / " + b + " = " + resultadoDivisao);
        } catch (ArithmeticException e) {
            System.out.println("Erro na divisão: " + e.getMessage());
        }

        System.out.println();
        System.out.println("--- Teste adicional: divisão por zero ---");
        double c = 8.0;
        double d = 0.0;
        try {
            double resultadoDivisaoZero = calculadora.dividir(c, d);
            System.out.println("Divisão:         " + c + " / " + d + " = " + resultadoDivisaoZero);
        } catch (ArithmeticException e) {
            System.out.println("Erro na divisão: " + e.getMessage());
        }

        System.out.println();
        System.out.println("===== Fim da execução =====");
    }
}