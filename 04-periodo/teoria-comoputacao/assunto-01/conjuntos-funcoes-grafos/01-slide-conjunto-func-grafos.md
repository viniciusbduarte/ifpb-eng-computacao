# Teoria da Computação  
## Fundamentos Matemáticos

### Tópicos
- Conjuntos e Sequências  
- Funções e Relações  
- Grafos  
- Alfabetos, cadeias e linguagens  
- Lógica Booleana  

---

## 1. Conjuntos

### Definição
Um conjunto é uma coleção de objetos considerados como uma unidade.

**Propriedades:**
- Podem conter qualquer tipo de objeto, inclusive outros conjuntos.
- Os objetos são chamados de elementos ou membros.
- Elementos não se repetem (repetições não alteram o conjunto).
- Não há ordem entre os elementos.

### Multiconjunto
Quando a repetição de elementos é relevante, temos um **multiconjunto**.

---

### Pertinência

- Elemento pertence a um conjunto: `∈`
- Elemento não pertence a um conjunto: `∉`

**Exemplo:**
```
C = {14, 3, 4, 42}
14 ∈ C
10 ∉ C
```

---

### Subconjuntos

- A é subconjunto de B: `A ⊆ B`
- A é subconjunto próprio de B: `A ⊊ B`

---

### Cardinalidade

Tipos de conjuntos:
- Vazio: `C = {}` ou `C = Ø`
- Finito: `C = {14, 3, 4, 42}`
- Infinito: `C = {14, 3, 4, 42, ...}`

---

### Operações com Conjuntos

#### União
```
A ∪ B
```
Conjunto com todos os elementos de A e B.

**Exemplo:**
```
A = {14, 3}
B = {4, 42}
A ∪ B = {14, 3, 4, 42}
```

#### Interseção
```
A ∩ B
```
Conjunto com os elementos comuns a A e B.

**Exemplo:**
```
A = {14, 3, 5, 7, 10}
B = {10, 4, 42, 7, 8}
A ∩ B = {7, 10}
```

---

## 2. Sequências e Tuplas

### Sequência
Lista ordenada de objetos.

**Características:**
- A ordem importa:
  ```
  (3, 42, 15) ≠ (42, 3, 15)
  ```
- Pode haver repetição:
  ```
  (3, 42, 15) ≠ (3, 42, 15, 15)
  ```
- Pode ser finita ou infinita.

### Tuplas (k-uplas)
Sequências com k elementos:
- 2-upla: dupla
- 3-upla: tripla
- 4-upla: quádrupla

---

## 3. Produto Cartesiano

Dado dois conjuntos A e B:
```
A × B = {(a, b) | a ∈ A e b ∈ B}
```

**Exemplo:**
```
A = {5, 3}
B = {a, b, c}

A × B = {(5,a), (5,b), (5,c), (3,a), (3,b), (3,c)}
```

---

## 4. Funções e Relações

### Função
Objeto que relaciona entradas e saídas.

Notação:
```
f: D → C
```

### Exemplos
```
abs: Z → Z
abs(2) = 2
abs(-2) = 2

add: Z × Z → Z
add(2,2) = 4
```

---

## 5. Grafos

### Conceitos fundamentais
- Vértices e arestas
- Grafos direcionados e não-direcionados
- Grau
- Subgrafo
- Caminho
- Ciclo
- Árvore
- Conectividade

---

## Recomendações

### Leitura
- Sipser: páginas 1 a 15

### Exercícios
- Sipser: páginas 26, 27 e 28