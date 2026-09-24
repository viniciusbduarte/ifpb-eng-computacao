package br.padroes.bridge;

import java.util.Scanner;

public class JanelaWindows implements JanelaImplementada {

	@Override
	public void desenharJanela(String titulo) {
		System.out.println(titulo + " - Janela Windows");
	}

	@Override
	public void desenharBotao(String titulo) {
		System.out.println(titulo + " - Botão Windows");
	}

	@Override
	public void desenharCaixaTexto(String rotulo) {
		System.out.println(rotulo + " - Caixa de Texto Windows");
	}

	@Override
	public String lerCaixaTexto() {
		Scanner leitor = new Scanner(System.in);
		return leitor.nextLine();
	}

}
