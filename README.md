# Compilador de Portugol

Implementação de um **Compilador completo para a linguagem Portugol**, desenvolvido no contexto académico de Ciência da Computação (Mackenzie). O projeto abrange todas as fases clássicas de compilação: análise léxica, análise sintática (parser), análise semântica e geração de código intermédio/executável.

---

## 🚀 Visão Geral do Projeto

Este compilador foi construído para traduzir código estruturado na linguagem educacional Portugol para uma linguagem de destino ou representação intermédia, validando regras de escopo, tipos de dados e gramática formal.

* **Análise Léxica (Lexer):** Reconhecimento de tokens, palavras-chave, operadores e literais.
* **Análise Sintática (Parser):** Construção da árvore sintática abstrata (AST) com base na gramática formal da linguagem.
* **Análise Semântica:** Verificação de tipos, declaração de variáveis e tratamento de escopo.
* **Geração de Código:** Tradução estruturada para a linguagem alvo.

---

## 🛠️ Stack Tecnológica

* **Linguagem:** Java / Python / C++ *(ajusta aqui conforme a linguagem em que implementaste, ex: Java com ANTLR/JFlex, ou Python)*
* **Conceitos de Compiladores:** Autômatos Finitos, Gramáticas Livres de Contexto (CFG), Árvores de Sintaxe Abstrata (AST), Tabela de Símbolos.

---

## ⚙️ Arquitetura do Compilador

1. **Fase 1 (Lexer):** Varre o código fonte de entrada e converte a sequência de caracteres em tokens válidos.
2. **Fase 2 (Parser):** Valida a hierarquia sintática e constrói a AST. Mensagens de erro detalhadas indicam linha e coluna em caso de falhas de sintaxe.
3. **Fase 3 (Semantic Checker):** Assegura que variáveis não declaradas não são utilizadas e previne incompatibilidades de atribuição de tipos.
4. **Fase 4 (Code Generator):** Emite o código final otimizado.

---

## 🚀 Como Executar

1. Clone o repositório:
   ```bash
   git clone [https://github.com/Lucas-IudiCG/Compilador-de-Portugol.git](https://github.com/Lucas-IudiCG/Compilador-de-Portugol.git)
   cd Compilador-de-Portugol
