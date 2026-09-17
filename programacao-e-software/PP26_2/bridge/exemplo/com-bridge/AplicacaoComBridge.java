public class AplicacaoComBridge {
    public static void main(String[] args) {
        Cor vermelho = new Vermelho();
        Cor azul = new Azul();

        Forma quadradoVermelho = new Quadrado(vermelho);
        Forma quadradoAzul = new Quadrado(azul);
        Forma circuloVermelho = new Circulo(vermelho);
        Forma circuloAzul = new Circulo(azul);

        quadradoVermelho.desenhar();
        quadradoAzul.desenhar();
        circuloVermelho.desenhar();
        circuloAzul.desenhar();
    }
}
