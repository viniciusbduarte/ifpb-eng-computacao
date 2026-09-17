public class AplicacaoSemBridge {
    public static void main(String[] args) {
        Forma quadradoVermelho = new QuadradoVermelho();
        Forma quadradoAzul = new QuadradoAzul();
        Forma circuloVermelho = new CirculoVermelho();
        Forma circuloAzul = new CirculoAzul();

        quadradoVermelho.desenhar();
        quadradoAzul.desenhar();
        circuloVermelho.desenhar();
        circuloAzul.desenhar();
    }
}
