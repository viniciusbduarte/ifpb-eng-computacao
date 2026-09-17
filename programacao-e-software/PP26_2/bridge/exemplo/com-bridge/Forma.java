public abstract class Forma {
    private final Cor cor;

    protected Forma(Cor cor) {
        this.cor = cor;
    }

    protected String cor() {
        return cor.nome();
    }

    public abstract void desenhar();
}
