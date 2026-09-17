public class Circulo extends Forma {
    public Circulo(Cor cor) {
        super(cor);
    }

    @Override
    public void desenhar() {
        System.out.println("Desenhando um circulo " + cor() + ".");
    }
}
