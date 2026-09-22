package br.padroes.bridge;

public class JanelaCaixaTexto extends JanelaAbstrata {

	public JanelaCaixaTexto(JanelaImplementada j) {
		super(j);
	}

	@Override
	public void desenhar() {
		desenharJanela("Janela de Entrada de Dados");
		desenharCaixaTexto("Digite um valor:");
		desenharBotao("Ok");
	}

	public String obterTexto() {
		return janela.lerCaixaTexto();
	}

}