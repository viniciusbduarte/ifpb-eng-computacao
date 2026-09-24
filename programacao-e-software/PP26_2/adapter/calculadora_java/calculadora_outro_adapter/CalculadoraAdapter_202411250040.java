public class CalculadoraAdapter_202411250040 extends Calculadora_202321250008 {

    public double somar(double a, double b) {
        return super.somar(a, b);
    }

    @Override
    public double subtrair(double a, double b) {
        return super.subtrair(a, b);
    }

    public double multiplicar(double a, double b) {
        return super.multiplicar(a, b);
    }

    @Override
    public double dividir(double a, double b) {
        if (b == 0) {
            throw new ArithmeticException("Divisão por zero não é permitida.");
        }
        return super.dividir(a, b);
    }
}
