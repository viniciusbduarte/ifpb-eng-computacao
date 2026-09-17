# Exemplo do padrao Bridge

O exemplo usa formas (`Quadrado` e `Circulo`) e cores (`Vermelho` e `Azul`).

## Sem Bridge

Em `sem-bridge/`, a forma e a cor ficam acopladas na mesma classe. Para atender
as duas formas e as duas cores, e necessario criar quatro classes:

- `QuadradoVermelho`
- `QuadradoAzul`
- `CirculoVermelho`
- `CirculoAzul`

Adicionar uma nova forma ou uma nova cor aumenta a quantidade de combinacoes e
exige novas classes.

## Com Bridge

Em `com-bridge/`, `Forma` e a abstracao e `Cor` e a implementacao que pode ser
variada. `Quadrado` e `Circulo` recebem uma `Cor` no construtor, mantendo as duas
hierarquias independentes.

Assim, qualquer forma pode ser combinada com qualquer cor sem criar uma classe
para cada combinacao.

## Execucao

Com o JDK instalado, execute a partir de cada diretorio:

```text
javac *.java
java AplicacaoSemBridge
```

```text
javac *.java
java AplicacaoComBridge
```
