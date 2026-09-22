package br.padroes.bridge;

public class Cliente {
	public static void main(String[] args) {
		JanelaAbstrata janela = new JanelaDialogo(new JanelaLinux());
		janela.desenhar();

		janela = new JanelaAviso(new JanelaLinux());
		janela.desenhar();

		janela = new JanelaDialogo(new JanelaWindows());
		janela.desenhar();

		janela = new JanelaDialogo(new JanelaMac());
		janela.desenhar();

		JanelaCaixaTexto entrada = new JanelaCaixaTexto(new JanelaMac());
		entrada.desenhar();
		String valor = entrada.obterTexto();
		System.out.println("Valor digitado: " + valor);

	}
}
