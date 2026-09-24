public class AplicacaoComBridge {
    public static void main(String[] args) {
        Cor vermelho = new CorVermelha();
        Cor azul = new CorAzul();

        Forma quadradoVermelho = new Quadrado(vermelho);
        Forma quadradoAzul = new Quadrado(azul);
        Forma circuloVermelho = new FormaCirculo(vermelho);
        Forma circuloAzul = new FormaCirculo(azul);

        quadradoVermelho.desenhar();
        quadradoAzul.desenhar();
        circuloVermelho.desenhar();
        circuloAzul.desenhar();
    }
}
