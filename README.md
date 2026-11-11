# Compilador de Portugol

Implementação de um compilador completo para a linguagem educacional **Portugol**, desenvolvido com foco em Ciência da Computação para tradução e execução de código estruturado em pseudocódigo para instruções de baixo nível ou linguagem intermédia.

---

## 🚀 Sobre o Projeto

Este projeto demonstra a aplicação prática de conceitos fundamentais de compiladores e linguagens formais:
* **Análise Léxica (Lexer):** Conversão do código fonte em sequência de *tokens* válidos.
* **Análise Sintática (Parser):** Verificação da gramática e construção de árvore sintática (AST - *Abstract Syntax Tree*).
* **Análise Semântica:** Validação de tipos, escopo de variáveis e declarações.
* **Geração de Código / Execução:** Tradução das instruções para execução direta ou ambiente simulado.

---

## 🛠️ Stack Tecnológica

* **Linguagem Principal:** Python (ou outra linguagem utilizada no projeto)
* **Conceitos & Paradigmas:** Autômatos, Gramáticas Livres de Contexto (GLC), Árvores Sintáticas e Tratamento de Erros

---

## 📊 Arquitetura do Compilador

```text
[ Código Fonte (Portugol) ] 
       │
       ▼
 [ Análise Léxica ] ──> (Geração de Tokens)
       │
       ▼
 [ Análise Sintática ] ──> (Construção da AST)
       │
       ▼
 [ Análise Semântica ] ──> (Checagem de Tipos e Escopos)
       │
       ▼
 [ Geração de Código / Execução ]
