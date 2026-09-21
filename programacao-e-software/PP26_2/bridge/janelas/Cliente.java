package br.padroes.bridge;

public class Cliente {
	public static void main(String[] args) {
		JanelaAbstrata janela = new JanelaEditBox(new JanelaMacOS());
		janela.desenhar();

	}
}
