package br.padroes.bridge;
public class JanelaMacOS implements JanelaImplementada {

	@Override
	public void desenharJanela(String titulo) {
		System.out.println(titulo + " - Janela Mac OS");
	}

	@Override
	public void desenharBotao(String titulo) {
		System.out.println(titulo + " - Botão Mac OS");
	}

}
