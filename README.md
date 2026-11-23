# 📚 Resumos e Exercícios — Sistemas Operativos (SO)

Repositório de apoio para o **Mini-teste de Sistemas Operativos**, contendo resoluções das aulas práticas, exercícios extra (Bash e C), fichas de treino e sumários teóricos[cite: 1, 2].

---

## 🗂️ Estrutura do Repositório

### 1. Aulas Práticas Resolvidas
Guiões e exercícios resolvidos organizados por aula (ordem cronológica):

#### NEM TODOS OS EXERCICIOS ESTÃO RESOLVIDOS OU 100% COMPLETOS (E quando digo isto, não é só das aulas, é em modo geral)

---

### 2. Exercícios Extra e Treino
Pastas com exercícios divididos por tema para praticar programação:

* **`Exs_Bash/`** — Exercícios de *shell scripting* em Bash[cite: 1].
* **`Exs_C_SemConcorrencia/`** — Exercícios introdutórios/base em C (sem concorrência)[cite: 1].
* **`Exs_C_Concorrencia/`** — Exercícios de C focados em processos/concorrência[cite: 1].
* **`Ficha_C_dados/`** — Ficha e ficheiros de dados para exercícios de C (sem concorrência)[cite: 1].
* **`teste_rapido.c`** *(e executável `teste_rapido`)* — Pequeno exercício prático de teste (baseado na Aula 5)[cite: 1].

---

### 3. Preparação para o Teste Modelo
* **`Teste_Modelo_SO_pacote./`** — Enunciado e ficheiros de um teste modelo.
* **`Teste_Modelo_SO_Resolucao.pdf`** — Resolução comentada do teste modelo.

---

### 4. 📄 Sumários e Apontamentos (PDF)
Guias teóricos rápidos para revisão antes da avaliação:

* 📘 [`Sumario_SO_Bash.pdf`](./Sumario_SO_Bash.pdf) — Resumo de comandos e scripting em Bash[cite: 1].
* 📘 [`Sumario_SO_Aulas_5_6_7.pdf`](./Sumario_SO_Aulas_5_6_7.pdf) — Matéria correspondente às aulas 5, 6 e 7[cite: 1].
* 📘 [`Sumario_SO_Aulas_8_9.pdf`](./Sumario_SO_Aulas_8_9.pdf) — Matéria correspondente às aulas 8 e 9[cite: 1].
* 📕 [`Sumario_SO_Teste_Completo-1.pdf`](./Sumario_SO_Teste_Completo-1.pdf) — Compilação geral de matéria para o teste[cite: 1].

---

## 💻 Como compilar os ficheiros em C
Para testar qualquer exercício em C no terminal Linux:

```bash
gcc -Wall -Wextra nome_do_ficheiro.c -o programa
./programa
