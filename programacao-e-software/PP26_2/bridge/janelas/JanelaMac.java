package br.padroes.bridge;

import java.util.Scanner;

public class JanelaMac implements JanelaImplementada {

	@Override
	public void desenharJanela(String titulo) {
		System.out.println(titulo + " - Janela Mac");
	}

	@Override
	public void desenharBotao(String titulo) {
		System.out.println(titulo + " - Botão Mac");
	}

	@Override
	public void desenharCaixaTexto(String rotulo) {
		System.out.println(rotulo + " - Caixa de Texto Mac");
	}

	@Override
	public String lerCaixaTexto() {
		Scanner leitor = new Scanner(System.in);
		return leitor.nextLine();
	}

}