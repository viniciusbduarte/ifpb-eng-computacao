**Sistemas Operacionais - Avaliação II**
---

## Questões

**1. (15) O Problema do Produtor-Consumidor** é um dos problemas clássicos de sincronização em Sistemas Operacionais. Descreva em que consiste esse problema, destacando os principais desafios relacionados ao acesso concorrente a um buffer compartilhado. Em seguida, explique como os semáforos podem ser utilizados para implementar uma solução robusta, mencionando quais semáforos seriam necessários e qual a função de cada um.

**2. (20) Analise as afirmações abaixo sobre Gerenciamento de Memória e Arquivos**, e classifique-as como Verdadeira (V) ou Falsa (F).

* **A.** ( ) A técnica de paginação divide o espaço de endereçamento lógico de um processo em blocos de tamanho fixo chamados frames, e a memória física em blocos de mesmo tamanho chamados páginas.
* **B.** ( ) A alocação contígua de arquivos é eficiente para leitura sequencial, mas sofre com o problema da fragmentação externa, tornando difícil o redimensionamento de arquivos após sua criação.
* **C.** ( ) A Translation Lookaside Buffer (TLB) é uma pequena memória de hardware que armazena uma cópia completa da tabela de páginas de todos os processos, a fim de acelerar a tradução de endereços virtuais para físicos.
* **D.** ( ) No sistema de arquivos do Linux, as extensões de arquivo (como ".txt" ou ".sh") são essenciais para o sistema operacional identificar o tipo de arquivo e associá-lo a um programa padrão, de forma semelhante ao Windows.
* **E.** ( ) O acesso aleatório a arquivos, comum em sistemas de banco de dados, permite que os dados sejam lidos ou escritos em qualquer ordem, pulando diretamente para uma posição específica do arquivo, o que torna mais complexo de implementar que o acesso sequencial.

**3. (15) O escalonamento de processos** é uma função crucial de um Sistema Operacional. Discuta quais são as **principais razões** pelas quais o **escalonamento** é necessário em sistemas modernos e quais são os **objetivos gerais** que todos os algoritmos de escalonamento buscam atingir. Além disso, diferencie **escalonamento preemptivo de não-preemptivo**, fornecendo um exemplo de algoritmo para cada tipo.

**4. (15) Os algoritmos de escalonamento** são classificados com base em diferentes critérios e objetivos. Compare os algoritmos **Shortest Job First (SJF)** e **Escalonamento por Prioridades**. Discuta o principal objetivo de cada um, suas vantagens e a principal desvantagem que ambos compartilham.

**5. (20) Em um pequeno escritório**, um servidor de impressão utiliza um Sistema Operacional que implementa o algoritmo de escalonamento **Round-Robin (Chaveamento Circular)** para gerenciar as requisições de impressão. Considere a seguinte situação:

* **Processo A (Documento Marketing):** Necessita de 18 unidades de tempo de CPU para ser impresso.
* **Processo B (Relatório Financeiro):** Necessita de 10 unidades de tempo de CPU para ser impresso.
* **Processo C (Boletim Informativo):** Necessita de 8 unidades de tempo de CPU para ser impresso.

O **quantum** de tempo para o escalonador Round-Robin é de **8 unidades de tempo**. Não há *overhead* de troca de contexto.

Explique a ordem em que os processos serão escalonados pelo sistema operacional para impressão e determine em qual unidade de tempo cada processo será concluído. Detalhe cada ciclo de execução até que todos os processos sejam finalizados.

---

**6. (15) Em um sistema operacional que emprega o algoritmo de substituição de páginas NRU (Not Recently Used)**, a memória principal contém as seguintes páginas, com seus respectivos bits R e M logo após o sistema ter zerado periodicamente todos os bits R:

| Página | Bit R | Bit M |
| --- | --- | --- |
| P1 | 1 | 0 |
| P2 | 0 | 1 |
| P3 | 1 | 1 |
| P4 | 0 | 0 |
| P5 | 0 | 0 |

Se ocorrer uma falta de página e o sistema precisar remover uma página da memória para carregar uma nova, qual seria a ordem de prioridade para a substituição das páginas, da mais provável a ser removida para a menos provável? Explique o raciocínio por trás de cada categoria de página no NRU.


Aqui está o arquivo Markdown contendo as respostas para a sua prova de Sistemas Operacionais, com base nos conteúdos estudados e na resolução das questões apresentadas nas imagens.

---

# Respostas da Avaliação II - Sistemas Operacionais

### Questão 1: O Problema do Produtor-Consumidor

O problema consiste em dois processos que compartilham um buffer de tamanho fixo: o **Produtor**, que gera dados e os coloca no buffer, e o **Consumidor**, que remove os dados para processá-los.

* **Desafios:** O principal desafio é evitar que o produtor tente inserir dados em um buffer cheio e que o consumidor tente remover dados de um buffer vazio, além de garantir que ambos não acessem a mesma posição de memória simultaneamente (condição de corrida).
* **Solução com Semáforos:**
* **Semáforo `mutex` (Binário):** Garante a exclusão mútua no acesso ao buffer (valor inicial 1).
* **Semáforo `empty` (Contador):** Controla o número de posições vazias no buffer (valor inicial = N). O produtor decrementa este semáforo.
* **Semáforo `full` (Contador):** Controla o número de posições ocupadas (valor inicial 0). O consumidor decrementa este semáforo.



---

### Questão 2: Gerenciamento de Memória e Arquivos (V/F)

* **A. (F)** – A paginação divide o espaço lógico em **páginas** e a memória física em **frames** (quadros), e não o contrário como sugere o enunciado.
* **B. (V)** – A alocação contígua é excelente para leitura rápida, mas gera fragmentação externa pois exige blocos de espaço livre ininterruptos.
* **C. (F)** – A TLB armazena apenas as entradas de páginas **mais utilizadas recentemente**, e não a tabela completa de todos os processos.
* **D. (F)** – No Linux, o tipo de arquivo é identificado pelos metadados (magic numbers/headers) e permissões, sendo as extensões apenas convenções para o usuário.
* **E. (V)** – O acesso aleatório permite saltar para qualquer parte do arquivo, o que é fundamental para bancos de dados, mas exige uma estrutura de indexação mais complexa.

---

### Questão 3: Escalonamento de Processos

* **Necessidade:** É necessário para maximizar o uso da CPU, garantir a multiprogramação e fornecer interatividade aos usuários.
* **Objetivos Gerais:** Justiça (equidade), eficiência, baixo tempo de resposta e alto *throughput* (vazão).
* **Diferença:**
* **Preemptivo:** O SO pode interromper um processo em execução para dar lugar a outro (ex: **Round-Robin**).
* **Não-Preemptivo:** O processo retém a CPU até terminar ou bloquear voluntariamente (ex: **First-Come, First-Served - FCFS**).



---

### Questão 4: SJF vs. Prioridades

* **SJF (Shortest Job First):** O objetivo é minimizar o tempo médio de espera, escolhendo o processo com o menor próximo pico de CPU.
* **Prioridades:** O objetivo é garantir que processos mais importantes sejam executados primeiro.
* **Vantagens:** O SJF é ótimo para o tempo médio de espera; o de Prioridades garante urgência.
* **Desvantagem Comum:** Ambos sofrem de **Starvation** (inanição), onde processos longos ou de baixa prioridade podem nunca ser executados.

---

### Questão 5: Resolução Round-Robin (Quantum = 8)

**Processos:** A (18u), B (10u), C (8u).

1. **0 - 8u:** Executa **A**. Restam 10u de A.
2. **8 - 16u:** Executa **B**. Restam 2u de B.
3. **16 - 24u:** Executa **C**. **C concluído em 24u**.
4. **24 - 32u:** Executa **A**. Restam 2u de A.
5. **32 - 34u:** Executa **B**. **B concluído em 34u**.
6. **34 - 36u:** Executa **A**. **A concluído em 36u**.

* **Conclusão C:** 24u
* **Conclusão B:** 34u
* **Conclusão A:** 36u

---

### Questão 6: Algoritmo NRU (Not Recently Used)

A ordem de prioridade para remoção (da mais provável para a menos provável) segue as classes do NRU:

1. **Classe 0 (R=0, M=0):** **P4 e P5**. São as melhores candidatas pois não foram lidas nem modificadas recentemente.
2. **Classe 1 (R=0, M=1):** **P2**. Foi modificada, mas não foi referenciada no último intervalo de tempo.
3. **Classe 2 (R=1, M=0):** **P1**. Foi referenciada recentemente, mas está "limpa" (não modificada).
4. **Classe 3 (R=1, M=1):** **P3**. É a pior candidata, pois está sendo usada e precisaria ser salva no disco se removida.

**Ordem Final:** P4 ou P5  P2  P1  P3.

---