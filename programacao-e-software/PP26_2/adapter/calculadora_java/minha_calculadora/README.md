# Sistema Orientado a Objetos — Calculadora Básica

**Aluno:** Vinicius Batista Duarte
**Matrícula:** 202411250040

---

## 1) Versão do compilador Java utilizada

`javac 26.0.2.1` (JDK 26)

Comando de compilação utilizado:

```bash
javac -encoding UTF-8 Calculadora_202411250040.java Cliente_202411250040.java
```

## 2) IDE e respectiva versão

Compilação e geração da biblioteca realizadas via terminal (Prompt de Comando / PowerShell), utilizando diretamente as ferramentas do JDK (`javac` e `jar`).

## 3) Sistema operacional e respectiva versão

Windows 11

## 4) Tipo da biblioteca criada para a Calculadora

`.jar` (`Calculadora_202411250040.jar`)

Comando utilizado para gerar a biblioteca:

```bash
jar cf Calculadora_202411250040.jar Calculadora_202411250040.class
```

Comando utilizado para compilar e executar o Cliente usando a biblioteca:

```bash
javac -encoding UTF-8 -cp Calculadora_202411250040.jar Cliente_202411250040.java
java -cp ".;Calculadora_202411250040.jar" Cliente_202411250040
```

## 5) Descrição de cada método da classe `Calculadora_202411250040`

| Método | Descrição |
|---|---|
| `public double somar(double a, double b)` | Recebe dois números (`a` e `b`) e retorna o resultado da soma entre eles (`a + b`). |
| `public double subtrair(double a, double b)` | Recebe dois números (`a` e `b`) e retorna o resultado da subtração entre eles (`a - b`), sendo `a` o minuendo e `b` o subtraendo. |
| `public double multiplicar(double a, double b)` | Recebe dois números (`a` e `b`) e retorna o resultado da multiplicação entre eles (`a * b`). |
| `public double dividir(double a, double b)` | Recebe dois números (`a` e `b`) e retorna o resultado da divisão de `a` por `b` (`a / b`). Caso o divisor `b` seja igual a zero, o método lança `ArithmeticException` com a mensagem `"Divisão por zero não é permitida."`, evitando que o programa seja encerrado abruptamente por erro não tratado. |

## 6) Estrutura geral do sistema

- **`Calculadora_202411250040.java` / `.jar`** — Classe-biblioteca com as 4 operações básicas (soma, subtração, multiplicação e divisão). Não possui método `main`; é destinada a ser importada e reutilizada por outras classes clientes.
- **`Cliente_202411250040.java`** — Classe que contém o método `public static void main(String[] args)`. Instancia `Calculadora_202411250040` e dispara uma sequência de chamadas às operações públicas, imprimindo os resultados no terminal shell.

## 7) Como executar no Windows 11

1. Instale um JDK versão 17 ou superior, marcando a opção de adicionar ao PATH.
2. Coloque `Calculadora_202411250040.jar` e `Cliente_202411250040.java` na mesma pasta.
3. Abra o Prompt de Comando nessa pasta e compile o Cliente referenciando o jar:
   ```bash
   javac -cp Calculadora_202411250040.jar Cliente_202411250040.java
   ```
4. Execute:
   ```bash
   java -cp ".;Calculadora_202411250040.jar" Cliente_202411250040
   ```