public class FormaCirculo extends Forma {
    public FormaCirculo(Cor cor) {
        super(cor);
    }

    @Override
    public void desenhar() {
        System.out.println("Desenhando um circulo " + cor() + ".");
    }
}
