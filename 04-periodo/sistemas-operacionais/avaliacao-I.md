# Sistemas Operacionais - Avaliação I

### Questão 1 (15 pts)

Os Sistemas Operacionais geralmente operam em dois modos de execução que definem o nível de privilégio da atividade: o **modo usuário** e o **modo kernel**. Explique o que são esses dois modos de execução, e por qual motivo essa separação entre modos é importante.

---

### Questão 2 (20 pts)

Analise as afirmações abaixo e classifique-as como Verdadeira (V) ou Falsa (F):

* **(**F**)** A chamada de sistema `fork()` no Linux cria um novo processo que é uma cópia exata do processo pai, compartilhando o mesmo código, mas com um novo espaço de dados.
* **(**F**)** Em modo usuário, o Sistema Operacional permite o acesso total ao hardware.
* **(**V**)** Os sistemas de tempo real (RTOS) são projetados para aplicações que exigem respostas em prazos rigorosos.
* **(**F**)** Uma interface gráfica do usuário (GUI) tem como objetivo permitir ao usuário interagir com o SO através de comandos digitados.
* **(**V**)** Em um sistema com threads em modo usuário, uma única chamada de sistema bloqueante (ex: leitura de um arquivo) feita por uma thread irá bloquear todas as outras threads do mesmo processo.

---

### Questão 3 (20 pts)

Em Sistemas Operacionais, um processo possui três estados básicos: **Executando**, **Bloqueado** e **Pronto**, e transita entre esses estados.

> **Diagrama de Transições:**
> * **Executando** ⟷ **Pronto** (Transições 3 e 4)
> * **Executando** ⟶ **Bloqueado** (Transição 6)
> * **Bloqueado** ⟶ **Pronto** (Transição 1)
> * **Bloqueado** ⟷ **Pronto** (Transições 1 e 2)
> * **Executando** ⟵ **Bloqueado** (Transição 5)
> 
> 

Dentre as transições enumeradas da figura, algumas delas não ocorrem conceitualmente. Explique quais destas não ocorrem em processos no Sistema Operacional, justificando sua resposta.

---

### Questão 4 (15 pts)

Quais são as condições que podem levar ao **término de um processo**? Diferencie entre término normal, término por erro e término involuntário.

---

### Questão 5 (15 pts)

A criação de processos é um evento fundamental em sistemas operacionais modernos. Descreva como funciona a criação de processos no **Linux** (usando `fork` e `execve`) e no **Windows** (usando `CreateProcess`). Qual a principal diferença filosófica entre essas duas abordagens?

---

### Questão 6 (15 pts)

A implementação de threads pode ser feita em modo usuário ou em modo kernel, cada uma com suas vantagens e desvantagens. Explique por que a criação e o término de threads em **modo usuário** são consideravelmente mais rápidos do que em **modo kernel**. Em que tipo de aplicação a implementação em modo usuário seria mais vantajosa, mesmo com a limitação de chamadas de sistema bloqueantes?

---

## Respostas: Avaliação I - Sistemas Operacionais

### Questão 1: Modos de Execução

* **Modo Usuário:** É um modo não privilegiado onde as aplicações rodam. O acesso direto ao hardware e a instruções sensíveis é bloqueado para proteger o sistema.
* **Modo Kernel (ou Supervisor):** É o modo privilegiado onde o SO opera. Tem acesso total à CPU, memória e periféricos.
* **Importância:** A separação garante a **segurança e estabilidade**. Impede que um processo mal-intencionado ou com erro (bug) acesse diretamente o hardware, apague dados de outros processos ou derrube o sistema inteiro.

---

### Questão 2: Verdadeiro ou Falso (Gabarito Corrigido)

* **A. (F)** — *Por que é falsa?* O `fork()` cria uma cópia, mas o Linux moderno usa **Copy-on-Write (COW)**. O espaço de dados é compartilhado inicialmente e só é duplicado se houver escrita.
* **B. (F)** — O acesso total é exclusivo do modo Kernel.
* **C. (V)** — Definição clássica de RTOS (determinismo de tempo).
* **D. (F)** — A GUI usa elementos visuais (janelas, ícones); comandos digitados são do CLI (Terminal).
* **E. (V)** — Em threads de nível de usuário, o kernel enxerga apenas um processo. Se uma thread bloqueia, o SO suspende o processo inteiro.

---

### Questão 3: Estados de Processos

As transições que **não ocorrem** conceitualmente são:

* **Transição 2 (Pronto → Bloqueado):** Um processo só bloqueia se estiver executando e solicitar uma E/S ou recurso não disponível. No estado "Pronto", ele apenas espera a CPU.
* **Transição 5 (Bloqueado → Executando):** Um processo que sai do bloqueio (ex: terminou a leitura do disco) não vai direto para a CPU. Ele vai para a fila de "Pronto" para aguardar o escalonador.

---

### Questão 4: Término de Processos

1. **Término Normal (Voluntário):** O processo finaliza sua tarefa e executa uma chamada de sistema (ex: `exit()`).
2. **Término por Erro (Voluntário):** O processo detecta que algo está errado (ex: arquivo não encontrado) e decide encerrar a si mesmo.
3. **Término Involuntário (Erro Fatal ou Cancelamento):** O SO mata o processo por erro grave (ex: falha de segmentação, divisão por zero) ou outro processo o encerra via sinal (ex: `kill`).

---

### Questão 5: Criação de Processos (Linux vs. Windows)

* **Linux (`fork` + `execve`):** O `fork()` cria um clone idêntico do pai. O `execve()` então substitui a imagem desse clone pelo novo programa. **Filosofia:** Simplicidade e modularidade; permite manipular o ambiente entre o clone e a execução.
* **Windows (`CreateProcess`):** Uma única chamada complexa que recebe inúmeros parâmetros (cerca de 10) para criar o processo do zero e carregar o executável. **Filosofia:** Abordagem de "chamada única" de alta performance e configuração explícita.

---

### Questão 6: Threads em Modo Usuário

* **Rapidez:** Não exige a troca de contexto de hardware (trap para o kernel). A troca de threads é apenas uma troca de registradores e PC (Program Counter) feita por uma biblioteca na própria memória do processo.
* **Vantagem:** É ideal para aplicações de **alta computação paralela** ou simuladores que precisam de milhões de trocas de contexto por segundo, onde o overhead do kernel tornaria o sistema lento. Mesmo com o risco de bloqueio, elas brilham em tarefas puramente de CPU.

---
