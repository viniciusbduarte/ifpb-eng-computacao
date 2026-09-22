package br.padroes.bridge;

import java.util.Scanner;
public class JanelaLinux implements JanelaImplementada {

	@Override
	public void desenharJanela(String titulo) {
		System.out.println(titulo + " - Janela Linux");
	}

	@Override
	public void desenharBotao(String titulo) {
		System.out.println(titulo + " - Botão Linux");
	}

	@Override
	public void desenharCaixaTexto(String rotulo) {
		System.out.println(rotulo + " - Caixa de Texto Linux");
	}

	@Override
	public String lerCaixaTexto() {
		Scanner leitor = new Scanner(System.in);
		return leitor.nextLine();
	}

}
