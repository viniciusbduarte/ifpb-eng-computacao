package br.padroes.bridge;

import java.util.Scanner; // 1. Importa a classe

public class JanelaEditBox extends JanelaAbstrata {

    Scanner scanner = new Scanner(System.in); // 2. Cria o leitor

	public JanelaEditBox(JanelaImplementada j) {
		super(j);
	}

	@Override
	public void desenhar() {
		desenharJanela("Janela de edição");
        String texto = scanner.nextLine(); // 3. Lê o texto digitado
        System.out.println("Texto digitado: " + texto);
		desenharBotao("Enviar");
        scanner.close(); // 4. Fecha o leitor
	}

}
