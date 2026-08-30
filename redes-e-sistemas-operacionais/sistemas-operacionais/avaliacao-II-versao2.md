# Sistemas Operacionais - Avaliação II

### Questão 1 (20 pts)

Explique o conceito de **"condição de corrida"** em Sistemas Operacionais e forneça um exemplo que ilustre como ela pode ocorrer. Em seguida, descreva como a **exclusão mútua** pode ser utilizada para resolver esse problema, mencionando uma das regras para uma boa solução de região crítica.

---

### Questão 2 (20 pts)

Analise as afirmações abaixo sobre **Gerenciamento de Memória e Arquivos**, e classifique-as como Verdadeira (V) ou Falsa (F).

* **(**F**)** A. Em SOs monoprogramáveis e simples, como o DOS, a memória física é diretamente utilizada pelos programas, o que oferece um isolamento robusto entre processos e facilita a realocação de programas.
* **(**V**)** B. O swapping permite que o sistema execute mais processos do que a memória principal pode comportar, copiando processos inativos para o disco e trazendo-os de volta quando necessário, porém, pode gerar um overhead de E/S.
* **(**F**)** C. O algoritmo de substituição de páginas Ótimo é considerado teoricamente perfeito por gerar o número mínimo possível de *page faults* e é amplamente utilizado em SOs modernos devido à sua praticidade de implementação.
* **(**V**)** D. No gerenciamento de arquivos, a estrutura "Sequência de Registros" é a mais comum em SOs modernos como Windows e Linux, onde o arquivo é tratado como uma cadeia linear de bytes sem estrutura imposta pelo SO.
* **(**V**)** E. Em um sistema de arquivos hierárquicos, como os utilizados no Windows e Linux, é possível ter arquivos com o mesmo nome em diretórios diferentes.

---

### Questão 3 (20 pts)

O escalonamento de processos é uma função crucial de um Sistema Operacional. Discuta quais são as **principais razões** pelas quais o **escalonamento** é necessário em sistemas modernos e quais são os **objetivos gerais** que todos os algoritmos de escalonamento buscam atingir. Além disso, diferencie **escalonamento preemptivo de não-preemptivo**, fornecendo um exemplo de algoritmo para cada tipo.

---

### Questão 4 (20 pts)

Em um pequeno escritório, um servidor de impressão utiliza um Sistema Operacional que implementa o algoritmo de escalonamento **Round-Robin (Chaveamento Circular)** para gerenciar as requisições de impressão. Considere a seguinte situação:

* **Processo A (Documento Marketing):** Necessita de 15 unidades de tempo de CPU para ser impresso.
* **Processo B (Relatório Financeiro):** Necessita de 10 unidades de tempo de CPU para ser impresso.
* **Processo C (Boletim Informativo):** Necessita de 5 unidades de tempo de CPU para ser impresso.

O **quantum** de tempo para o escalonador Round-Robin é de **5 unidades de tempo**. Não há *overhead* de troca de contexto.

Explique a ordem em que os processos serão escalonados pelo sistema operacional para impressão e determine em qual unidade de tempo cada processo será concluído. Detalhe cada ciclo de execução até que todos os processos sejam finalizados.

---
# Respostas

### Questão 1: Condição de Corrida e Exclusão Mútua

* **Condição de Corrida:** Ocorre quando dois ou mais processos acessam e manipulam dados compartilhados simultaneamente, e o resultado final depende da ordem específica em que os acessos ocorrem.
* **Exemplo:** Dois processos tentando incrementar a mesma variável global "contador" ao mesmo tempo. Ambos leem o valor 10, ambos incrementam para 11 e gravam. O resultado final é 11, quando deveria ser 12.
* **Exclusão Mútua:** É a técnica que garante que, se um processo está executando em sua região crítica, nenhum outro processo pode entrar nela.
* **Regras para uma boa solução:** 1. Dois processos não podem estar simultaneamente em suas regiões críticas.
2. Nenhuma suposição pode ser feita sobre a velocidade ou o número de CPUs.
3. Nenhum processo fora de sua região crítica pode bloquear outros processos.
4. Nenhum processo deve esperar eternamente para entrar em sua região crítica.

---

### Questão 2: Gerenciamento de Memória e Arquivos (Gabarito)

* **A. (F)** — Sistemas monoprogramáveis **não** oferecem isolamento robusto; um programa pode facilmente sobrescrever partes do SO na memória.
* **B. (V)** — Esta é a função do swapping, embora o custo de mover dados para o disco (E/S) seja alto.
* **C. (F)** — O algoritmo Ótimo é **impossível** de implementar na prática, pois exige saber o futuro (quais páginas serão usadas). Ele serve apenas como benchmark.
* **D. (V)** — Erro comum na prova: No Windows/Linux, arquivos são "streams de bytes" (sequência linear). A estrutura interna é responsabilidade da aplicação, não do SO.
* **E. (V)** — O caminho absoluto (path) diferencia os arquivos (ex: `/home/user/doc.txt` e `/tmp/doc.txt`).

---

### Questão 3: Escalonamento de Processos

* **Razões:** Necessário para prover multiprogramação, manter a CPU ocupada e garantir interatividade em sistemas de tempo compartilhado.
* **Objetivos Gerais:** Justiça (equidade na CPU), Eficiência (manter CPU a 100%), Tempo de Resposta baixo (para usuários interativos) e *Throughput* (vazão máxima de processos).
* **Diferença:**
* **Preemptivo:** O SO pode interromper um processo em execução para dar a CPU a outro (ex: **Round-Robin** ou **SRTF**).
* **Não-Preemptivo:** O processo detém a CPU até que termine ou bloqueie voluntariamente (ex: **FIFO/FCFS** ou **SJF**).

---

### Questão 4: Resolução Round-Robin (Quantum = 5)

Os processos entram na fila (assumindo ordem A, B, C).

**Ciclo 1:**

1. **Processo A:** Executa 5 unidades. (Restam 10). Tempo acumulado: **5**
2. **Processo B:** Executa 5 unidades. (Restam 5). Tempo acumulado: **10**
3. **Processo C:** Executa 5 unidades. (Restam 0). **CONCLUÍDO no tempo 15.**

**Ciclo 2:**
4.  **Processo A:** Executa mais 5 unidades. (Restam 5). Tempo acumulado: **20**
5.  **Processo B:** Executa mais 5 unidades. (Restam 0). **CONCLUÍDO no tempo 25.**

**Ciclo 3:**
6.  **Processo A:** Executa as últimas 5 unidades. (Restam 0). **CONCLUÍDO no tempo 30.**

**Resumo das Conclusões:**

* **Processo C:** 15 unidades de tempo.
* **Processo B:** 25 unidades de tempo.
* **Processo A:** 30 unidades de tempo.