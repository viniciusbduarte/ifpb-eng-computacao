# Relatório técnico: busca de raízes por gradiente descendente

## 1. Objetivo

Este projeto implementa gradiente descendente para resolver equações não lineares e compara o método com bisseção, falsa posição e ponto fixo nas seis funções da questão 4 da lista. Newton-Raphson e secante aparecem como referências adicionais. O notebook associado contém o código, tabelas, gráficos e medições de tempo.

As regras da atividade foram mantidas: no máximo 200 iterações, tolerância de `1e-10`, intervalo fornecido para métodos fechados e limite direito como estimativa inicial dos métodos abertos.

## 2. Funções de teste

| Caso | Função | Intervalo | Raiz de referência |
|---|---|---:|---:|
| a | `2x^4 + 4x^3 + 3x^2 - 10x - 15` | `[0, 3]` | `1.492878708664` |
| b | `(x + 3)(x + 1)(x - 2)^3` | `[0, 5]` | `2` |
| c | `5x^3 + x^2 - exp(1 - 2x) + cos(x) + 20` | `[-5, 5]` | `-0.929560459838` |
| d | `x sin(x) + 4` | `[1, 5]` | `4.323239543714` |
| e | `(x - 3)^5 ln(x)` | `[2, 5]` | `3` |
| f | `x^10 - 1` | `[0.8, 1.2]` | `1` |

As raízes de referência foram calculadas com `scipy.optimize.brentq` e servem apenas para medir `erro_abs`; elas não participam da execução dos métodos comparados.

## 3. Métodos

### Bisseção

A bisseção exige `f(a)f(b) < 0`. O ponto médio divide o intervalo, e o subintervalo sem troca de sinal é descartado. O método é fechado e robusto: se a função for contínua e houver uma mudança de sinal, a raiz permanece isolada. Sua convergência é linear, portanto o número de iterações é previsível, mas geralmente maior que o de métodos abertos.

O notebook usa `scipy.optimize.bisect`, com `xtol=1e-10` e `maxiter=200`.

### Falsa posição

A falsa posição conserva a segurança do intervalo, mas calcula a nova aproximação pela reta que une `(a, f(a))` e `(b, f(b))`:

$$
x = \frac{a f(b)-b f(a)}{f(b)-f(a)}.
$$

Ela costuma ser vantajosa quando a função é aproximadamente linear em uma parte do intervalo. Pode, porém, prender uma extremidade por muitas iterações, especialmente em funções assimétricas ou com raiz múltipla.

### Ponto fixo

O método reescreve a equação como `x = g(x)` e calcula

$$
x_{k+1}=g(x_k).
$$

A convergência local depende de `|g'(x*)| < 1`. Foram usadas reformulações amortecidas `g(x) = x - lambda f(x)`, com `lambda` pequeno quando necessário. A escolha de `g` é parte essencial do método: duas reformulações da mesma equação podem ter comportamentos completamente diferentes.

Nas funções (b) e (e), a raiz relevante é múltipla. Como a função fica plana na raiz, a iteração simples pode não atingir o resíduo `1e-10` em 200 passos. Isso é reportado como não convergência, e não tratado como uma falha artificial do programa.

### Gradiente descendente

Uma raiz de `f` é um mínimo de um objetivo não negativo. O objetivo principal foi

$$
J(x)=\frac{1}{2}f(x)^2,
$$

cujo gradiente é `f(x) f'(x)`. Assim,

$$
x_{k+1}=x_k-\alpha f(x_k)f'(x_k).
$$

Também foi testado `J(x) = log(1 + f(x)^2)`, com gradiente
`2 f(x) f'(x)/(1 + f(x)^2)`. O objetivo logarítmico reduz a influência de valores muito grandes de `f`.

A implementação possui:

- backtracking: reduz a taxa quando o objetivo aumenta;
- limite de passo, evitando saltos excessivos;
- parada por `|f(x)| <= 1e-10`;
- multistart: executa o método em vários pontos do intervalo e agrupa raízes próximas;
- registro de chamadas, iterações e backtracks.

O multistart é importante porque o gradiente descendente é um método local. Uma única inicialização encontra somente a raiz cuja bacia de atração contém o ponto inicial.

Para tornar esse comportamento observável, o notebook também usa a função
`h(x) = (x + 2)(x - 1)(x - 3)` no intervalo `[-3, 4]`. Ela possui as três raízes
`-2`, `1` e `3`. O GD é executado a partir de 61 pontos uniformes; ao final, as
aproximações são agrupadas e comparadas com essas três raízes exatas.

### Newton-Raphson e secante

Newton usa

$$
x_{k+1}=x_k-\frac{f(x_k)}{f'(x_k)}.
$$

Perto de uma raiz simples e com uma boa inicialização, sua convergência é quadrática. Em compensação, uma inicialização ruim pode causar saltos, divisão por derivada pequena ou convergência para outra raiz.

A secante substitui a derivada por uma inclinação calculada com dois pontos. Ela evita derivadas analíticas e costuma ser rápida, mas é sensível aos dois valores iniciais.

## 4. Arranjo experimental

Para o GD foram testadas as taxas `0.001`, `0.01`, `0.05` e `0.1`, combinadas com os objetivos `quadratic` e `log_quadratic`. Cada configuração foi executada a partir de 21 pontos uniformes em cada intervalo. A taxa de convergência foi calculada como a fração de inicializações que alcançou o critério em até 200 iterações. Em empate, a configuração com menor média de iterações foi preferida. O notebook calcula e exibe explicitamente a tabela `resumo_sweep` ordenada por esses critérios e salva a escolha em `melhor_configuracao`.

A varredura executada selecionou `lr=0.1` e o objetivo quadrático pela maior taxa média de convergência; em empate, seria usado o menor número médio de iterações. Essa configuração, com backtracking habilitado e `max_step=1`, é usada na tabela principal. O teste multistart é apresentado separadamente porque a comparação principal usa uma execução representativa, como os demais métodos.

Para cada execução são registrados:

- `raiz`: aproximação retornada;
- `erro_abs`: distância até a referência independente;
- `residuo`: `|f(raiz)|`;
- `iteracoes`: passos realizados;
- `convergiu`: atendimento do critério de parada;
- `tempo_ms`: tempo médio por execução, medido com `timeit.repeat`;
- chamadas da função e da derivada, quando aplicável.

## 5. Discussão dos resultados

A bisseção é a referência de robustez. Ela não depende de derivada nem de uma taxa de aprendizagem, mas paga por isso com mais iterações. Na função (f), o ponto médio do intervalo é exatamente `1`, por isso a raiz é encontrada imediatamente.

A falsa posição pode reduzir o número de iterações em funções com comportamento quase linear, mas não possui a mesma regularidade de redução do intervalo da bisseção. Em raízes múltiplas, tanto a falsa posição quanto a bisseção podem apresentar resíduo pequeno enquanto a aproximação ainda está relativamente distante da raiz.

O ponto fixo é competitivo quando a reformulação é contrativa, como ocorre em boa parte de (a), (c), (d) e (f). Na função (d), por exemplo, uma escolha inadequada de `g` poderia divergir; a escolha amortecida torna a sequência convergente, porém lenta. Em (b) e (e), a multiplicidade explica a lentidão: a derivada da função se anula na raiz, reduzindo a força de atração da iteração simples.

O GD apresenta uma vantagem conceitual: não precisa de troca de sinal e pode pesquisar várias raízes com multistart. Seu desempenho depende muito de `alpha`, da escala de `f` e do objetivo. O backtracking melhora a estabilidade, mas adiciona avaliações de função. Para funções bem condicionadas e ponto inicial favorável, Newton e secante normalmente usam menos iterações; para inicializações difíceis, o GD amortecido pode ser mais previsível.

Newton é especialmente eficiente quando a derivada não é pequena perto da raiz, mas o resultado deve ser interpretado com cuidado. Na função (d), uma inicialização no limite direito pode convergir para outra raiz real fora do intervalo de interesse, embora o resíduo seja excelente. Esse exemplo mostra por que `convergiu=True` não substitui a verificação do intervalo e do `erro_abs`.

Os tempos dependem da máquina, do kernel e do custo das funções. Eles não devem ser tratados como uma constante universal. O número de chamadas é uma métrica complementar mais estável para entender por que o GD com backtracking pode custar mais que um método de fórmula fechada.

## 6. Conclusão

O experimento confirma que não existe um método dominante para todas as funções. Bisseção é a escolha mais segura quando há intervalo com mudança de sinal; falsa posição pode ser mais rápida em alguns formatos; ponto fixo exige uma reformulação contrativa; GD é flexível e pode localizar múltiplas raízes via multistart; Newton e secante são muito rápidos perto de raízes simples, mas mais sensíveis à inicialização.

As funções (b) e (e) são os casos mais instrutivos. Elas mostram que raízes múltiplas tornam a função plana, dificultam a convergência e separam claramente dois conceitos: resíduo pequeno e erro pequeno na variável. Por isso, o relatório sempre apresenta ambos.

## 7. Execução

Abra `projeto_gradiente_descendente_ajustado_graficos_executado.ipynb` e execute as células em ordem. O ambiente precisa ter `numpy`, `pandas`, `scipy`, `matplotlib` e Jupyter. A célula de tempo também mostra um exemplo de uso de `%timeit`.
