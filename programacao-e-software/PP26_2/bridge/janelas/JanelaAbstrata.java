package br.padroes.bridge;

public abstract class JanelaAbstrata {

	protected JanelaImplementada janela;

	public JanelaAbstrata(JanelaImplementada j) {
		janela = j;
	}

	public void desenharJanela(String titulo) {
		janela.desenharJanela(titulo);
	}

	public void desenharBotao(String titulo) {
		janela.desenharBotao(titulo);
	}

	public void desenharCaixaTexto(String rotulo) {
		janela.desenharCaixaTexto(rotulo);
	}

	public abstract void desenhar();

}
