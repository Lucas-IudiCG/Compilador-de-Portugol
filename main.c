#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ########### TIPOS DOS ANALISADOR LEXICO E SINTATICO

typedef enum{
    ERRO,
    INICIO,
    IDENTIFICADOR,
    NUMERO,
    OP_SOMA,
    OP_SUB,
    OU,
    OP_MULT,
    DIV,
    PONTO_VIRGULA,
    PONTO,
    ESCREVA,
    ABRIR_PARENTESES,
    FECHAR_PARENTESES,
    VIRGULA,
    VARIAVEL,
    FIM,
    E,
    VERDADEIRO,
    FALSO,
    INTEIRO,
    LOGICO,
    DOIS_PONTOS,
    ALGORITMO,
    MAIOR,
    MAIOR_IGUAL,
    IGUAL,
    MENOR,
    MENOR_IGUAL,
    HASHTAG,
    SE,
    ENQUANTO,
    LEIA,
    ENTAO,
    SENAO,
    FACA,
    EOS
}TAtomo;

typedef struct{
  TAtomo atomo;
  int linha;
  float atributo_numero;
  char atributo_ID[16];
}TInfoAtomo;

//para ler o arquivo ou inves de armazenar em string, nós armazenamos em um array de char, isso causou algumas mudanças no código
char buffer[1000];
int erro=0;
int leitura(){ // função que le arquivo txt, e armazena em buffer
  FILE  *textfile;// define um FILE
  int x = 0;
  
  int a=0;
  textfile = fopen("input.txt", "r");//abre o file
  if (textfile) {
    buffer[a]=fgetc(textfile);
    while(buffer[a]!=EOF){
        a++;
        buffer[a]=fgetc(textfile);
    }
}
  return a;
}

TInfoAtomo obter_atomo();
TInfoAtomo reconhece_numero();
TInfoAtomo reconhece_id();
void programa();
void consome(TAtomo);
void expressao();
void comando();

// reconhece terminal é uma das funções mais importantes do codigo e substitui o strcmp, do codigo original
  //essa função funciona por pegar o inicio, e o fim de do buffer e transformando em um array, esse array pode ser comparado com strcmp, e devolve a Palavra chave.
// essa função também recebe c, que é a categoria, se for categoria 1, analiza palavras e se for categoria 2 é um número
TInfoAtomo reconhece_terminal(int q, int j,int c){
  TInfoAtomo infoAtomo;
  char array[j-q];
  int a=0;
  for(a =0;a<j-q;a++){
    array[a]=buffer[q+a];
  }
  array[a]='\0';
  if(0==strcmp(array,"ou")){
  infoAtomo.atomo  = OU;
  return infoAtomo;
  }
  else if(0==strcmp(array,"E")){
  infoAtomo.atomo  = E;
  return infoAtomo;
  }
  else if(0==strcmp(array,"DIV")){
    infoAtomo.atomo  = DIV;
  return infoAtomo;
  }
  else if(0==strcmp(array,"enquanto")){
    infoAtomo.atomo  = ENQUANTO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"leia")){
  infoAtomo.atomo  = LEIA;
  return infoAtomo;
  }
  else if(0==strcmp(array,"se")){
    infoAtomo.atomo  = SE;
  return infoAtomo;
  }
  else if(0==strcmp(array,"senao")){
    infoAtomo.atomo  = SENAO;
    strcpy(infoAtomo.atributo_ID,"senao");
  return infoAtomo;
  }
  else if(0==strcmp(array,"faca")){
    infoAtomo.atomo  = FACA;
  return infoAtomo;
  }
  else if(0==strcmp(array,"variavel")){
    infoAtomo.atomo  = VARIAVEL;
  return infoAtomo;
  }
  else if(0==strcmp(array,"escreva")){
    infoAtomo.atomo  = ESCREVA;
  return infoAtomo;
  }
     else if(0==strcmp(array,"logico")){
    infoAtomo.atomo  = LOGICO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"inicio")){
    infoAtomo.atomo  = INICIO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"entao")){
    infoAtomo.atomo  = ENTAO;
  return infoAtomo;
  }

  else if(0==strcmp(array,"fim")){
    infoAtomo.atomo  = FIM;
  return infoAtomo;
  }
  else if(0==strcmp(array,"algoritmo")){
    infoAtomo.atomo  = ALGORITMO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"verdadeiro")){
    infoAtomo.atomo  = VERDADEIRO;
  return infoAtomo;
  }
else if(0==strcmp(array,"falso")){
    infoAtomo.atomo  = FALSO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"logico")){
    infoAtomo.atomo  = LOGICO;
  return infoAtomo;
  }
  else if(0==strcmp(array,"inteiro")){
    infoAtomo.atomo  = INTEIRO;
  return infoAtomo;
  }
  
  else if(c==1){
    infoAtomo.atomo  = IDENTIFICADOR;
    strcpy(infoAtomo.atributo_ID,array);
  return infoAtomo;
    }
  else if(c==2){
    infoAtomo.atomo  = NUMERO;
    strcpy(infoAtomo.atributo_ID,array);
  return infoAtomo;
    }
    
  else{
    infoAtomo.atomo  = ERRO;
  return infoAtomo;
  }
 
   }
  
char strAtomo[][30] = { "Erro lexico","Inicio" ,"IDENTIFICADOR","NUMERO","Op de Soma","Op de Subtração","Ou","Op Multiplicao","Div","Ponto e Virgula", "Ponto","Escreva","Abrir Parenteses","Fechar Parenteses","Virgula","Variavel","Fim","E","Verdadeiro","Falso","Inteiro","Logico","Dois Pontos","Algoritmo","Maior","Maior Igual","Igual","Menor","Menor Igual","Hashtag","Se","Enquanto","Leia","Entao","Senao","Faca","Fim Analise Sintatica"};

int i=0;// "i" indica o elemento atual do array que será analizado
int contaLinha=1;

TInfoAtomo InfoAtomo;
TAtomo lookahead;
int main(void) {
  int a=leitura();
  InfoAtomo = obter_atomo();
  lookahead = InfoAtomo.atomo;
  programa(); // chama o simbolo inicial da gramatica
  if(lookahead==36)// se finalizou em EOS.
  printf("%d linhas analisadas, analise sintatica finalizada com sucesso.",InfoAtomo.linha);

    return 0;
}

// Destroy é a função destroi os dois tipos de comentarios, o comentario "/*" até "*/", e o comentario "//",  
void Destroy(int a){
  if(a==0){
    goto q0;
  }
  if(a==1){
    goto q1;
  }
q0:
  if(!(buffer[i-1]=='*' && buffer[i]=='/')){
        i++;
    if(buffer[i]=='\n'){
      contaLinha++;
    }
      goto q0;
    }
  i++;
printf("#%d: Comentario\n",InfoAtomo.linha+1);
  return;
q1:
  if(!(buffer[i]=='\n')){
        i++;
      goto q1;
    }
  i++;
  contaLinha++;
  printf("#%d: Comentario\n",InfoAtomo.linha);
return;
}


TInfoAtomo obter_atomo(){ //essa função verifica qual será o proximo atomo a ser analizado
  TInfoAtomo infoAtomo;
  while( buffer[i]==' '){
    i++;
  }// pula espaços antes de comentarios
  if( buffer[i]=='/' && buffer[i+1]=='*'){
    Destroy(0);
  }//detecta comentario tipo 0="/*" até "*/"
  if( buffer[i]=='/' && buffer[i+1]=='/'){
    Destroy(1);
  }//detecta comentario tipo 1="//" até "/n"
  while( buffer[i]==' ' || buffer[i]=='\n' || buffer[i]=='\t' || buffer[i]== '\r'){
        if(buffer[i] == '\n')
            contaLinha++;
        i++;
  }// pula espaços
  // reconhece numeros
  if(isdigit(buffer[i])){
        infoAtomo = reconhece_numero();
    }
    // reconhece identificador
    else if(isalpha(buffer[i])){
        infoAtomo = reconhece_id();
    }
      else if(buffer[i] == '+'){
        infoAtomo.atomo = OP_SOMA;
        i++;
    }
 else if(buffer[i] == '+'){
        infoAtomo.atomo = OP_SOMA;
        i++;
    }
    else if(buffer[i] == '*'){
        infoAtomo.atomo = OP_MULT;
        i++;
    }
    else if(buffer[i] == '-'){
        infoAtomo.atomo = OP_SUB;
        i++;
    }
   
    else if(buffer[i] == '('){
        infoAtomo.atomo = ABRIR_PARENTESES;
        i++;
    }
      else if(buffer[i] == ')'){
        infoAtomo.atomo = FECHAR_PARENTESES;
        i++;
    }
    else if(buffer[i] == ';'){
        infoAtomo.atomo = PONTO_VIRGULA;
        i++;
    }
    else if(buffer[i] == ','){
        infoAtomo.atomo = VIRGULA;
        i++;
    }
    else if(buffer[i] == ':'){
        infoAtomo.atomo = DOIS_PONTOS;
        i++;
    }
    else if(buffer[i] == '.'){
        infoAtomo.atomo = PONTO;
        i++;
    }
      //relacional “<” | “<=” | “=” | “#” | “>” | “>=
    else if(buffer[i] == '<'){
        infoAtomo.atomo = MENOR;
        i++;
    }
    else if(buffer[i] == '<' && buffer[i+1] == '='){
        infoAtomo.atomo = MENOR_IGUAL;
        i=i+2;
    }
    else if(buffer[i] == '='){
        infoAtomo.atomo = IGUAL;
        i++;
    }
    else if(buffer[i] == '#'){
        infoAtomo.atomo = HASHTAG;
        i++;
    }
    else if(buffer[i] == '>'){
        infoAtomo.atomo = MAIOR;
        i++;
    }
    else if(buffer[i] == '>' && buffer[i+1] == '='){
        infoAtomo.atomo = MAIOR_IGUAL;
        i=i+2;
    }
    else if(buffer[i+1] == '\x0'){
        infoAtomo.atomo = EOS;
        i++;
    }
    else
        infoAtomo.atomo = ERRO;

    infoAtomo.linha = contaLinha;
    return infoAtomo;
}

// funcao reconhe o atomo NUMERO
TInfoAtomo reconhece_numero(){
    int x=i;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

  
    if( isdigit(buffer[i]) ){
        i++;
        goto q1;
    }
    return infoAtomo;

q1:
    if( isdigit(buffer[i]) ){
        i++;
        goto q1;
    }
    if(buffer[i]=='.' ){
        i++;
        goto q2;
    }
  if(buffer[i]=='E' || buffer[i]=='e'){
        i++;
        goto q2;
    }
    // Se for letra ou outro simbolo que nao pertence ao alfabeto do mini analisador lexico
    return infoAtomo;

q2:
    if( isdigit(buffer[i]) ){
        i++;
        goto q3;
    }
    if( buffer[i]=='+' || buffer[i]=='-' ){
        i++;
        goto q3;
    }
    // Se for letra ou outro simbolo que nao pertence ao alfabeto do mini analisador lexico
    return infoAtomo;
q3:
    if( isdigit(buffer[i]) ){
        i++;
        goto q3;
    }
    if( isalpha(buffer[i]))
        return infoAtomo; // retorna o InfoAtomo com erro
  
      return reconhece_terminal(x,i,2);
}

TInfoAtomo reconhece_id(){// reconhece_ID ficou muito simples, já que parte de sua função foi passada para o reconhece terminal ,(foi repassado simplesmente para uma compreensão mais facil, já que o reconhece_terminal basicamente substitui o strcmp do codigo original)
    int x=i;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

    if(isalpha(buffer[i])){
        i++;
        goto q1;
    }
    return infoAtomo;
q1:
    if(isalpha(buffer[i])||isdigit(buffer[i])||buffer[i]=='_'){
        i++;
        goto q1;
    }
  return reconhece_terminal(x,i,1);

}

void consome( TAtomo atomo ){
    if( lookahead == atomo ){
        InfoAtomo = obter_atomo();
        lookahead = InfoAtomo.atomo;
      printf("#%d: %s",InfoAtomo.linha,strAtomo[lookahead]);
      // se for um identificador printa seu nome
      if(lookahead==2){
        printf("  -atributo: %s",InfoAtomo.atributo_ID);
      }
      printf("\n");
    }
  else{
    //erro é uma variavel feita apenas para verificar se existe erro em comando, já que pode ter uma sequencia de varios comandos
    //o que causava erro na hora de mostrar aonde ocorreu o erro.
    if(erro>0){
      printf("#%03d: Erro sintatico\n", InfoAtomo.linha);
    printf("erro sintatico: esperado [%s] encontrado [%s]\n",strAtomo[lookahead],strAtomo[atomo]);
        exit(1);
    }
        else{
        printf("#%03d: Erro sintatico\n", InfoAtomo.linha);
    printf("erro sintatico: esperado [%s] encontrado [%s]\n",strAtomo[atomo],strAtomo[lookahead]);
        exit(1);
    }
    }
}
//<lista_variavel> ::= identificador { “,” identificador }
void Lista_Variavel(){
  consome(IDENTIFICADOR);
  while(buffer[i-1]==','){
  consome(VIRGULA);
  consome(IDENTIFICADOR);
    }
}

//<declaracao_de_variaveis> ::= variavel {<lista_variavel> “:” <tipo> “;”}+
void DeclaracaoVariavel(){
  consome(VARIAVEL);
  Lista_Variavel();
  consome(DOIS_PONTOS);
  if(lookahead==20)//20 = inteiro
  consome(INTEIRO);
  else
    consome(LOGICO);
  consome(PONTO_VIRGULA);
}

//<fator> ::= identificador |numero |verdadeiro |falso |“(” <expressao> “)”
void fator(){
  // 18 =verdadeiro
  if (lookahead==18){
    consome(VERDADEIRO);
  }
  // 19 =falso
  if (lookahead==19){
    consome(FALSO);
  }
  //15 = variavel
  if (lookahead==15){
    consome(VARIAVEL);
  }
  //2 = identificador
  if (lookahead==2){ 
    consome(IDENTIFICADOR);
  }
  //12= Abrir_parenteses
  if (lookahead==12){
    consome(ABRIR_PARENTESES);
    expressao();
    consome(FECHAR_PARENTESES);
    
  }
}

//<termo> ::= <fator> { ( “*” | div | e )<fator> }
void Termo(){
  fator();
  while(buffer[i-1]=='*' || buffer[i-1]=='e'||(buffer[i-1]=='o' && buffer[i]=='u')){
  if(buffer[i-1]=='*'){
    consome(OP_MULT);
  }
  else if(buffer[i-1]=='e'){
    consome(E);
  }
    else if(buffer[i-1]=='d' && buffer[i]=='i' && buffer[i+1]=='v'){
    consome(DIV);
  }
  fator();
}
}

//<expressao_simples> ::= [“+” | “−”] <termo> { (“+” | “−” | ou ) <termo> }
void Expressao_Simples(){
  if(buffer[i-1]=='-'){
    consome(OP_SUB);
  }
  else if(buffer[i-1]=='+'){
    consome(OP_SOMA);
  }
  Termo();
  while(buffer[i-1]=='-' || buffer[i-1]=='+'||(buffer[i-1]=='o' && buffer[i]=='u')){
  if(buffer[i-1]=='-'){
    consome(OP_SUB);
  }
  else if(buffer[i-1]=='+'){
    consome(OP_SOMA);
  }
    else if(buffer[i-1]=='o' && buffer[i+1]=='u'){
    consome(OU);
  }
  Termo();
}
}
//<relacional> ::= “<” | “<=” | “=” | “#” | “>” | “>=”
int relacional(){
  if(buffer[i-1] == '<'){
     consome(MENOR);
     return 1;
  }
  else if(buffer[i-1] == '<' && buffer[i] == '='){
  consome(MENOR_IGUAL);
  return 1;  
  }
else if(buffer[i-1] == '='){
    consome(IGUAL);
    return 1;
}
else if(buffer[i-1] == '#'){
    consome(HASHTAG);
    return 1;
}
else if(buffer[i-1] == '>'){
    consome(MAIOR);
    return 1;
}
else if(buffer[i-1] == '>' && buffer[i] == '='){
    consome(MAIOR_IGUAL);
  return 1;
    }
  return 0;
}

//<expressao> ::= <expressao_simples> [<relacional> <expressao_simples> ]
void expressao(){
  Expressao_Simples();
  int v=relacional();
  if(v>0){
    Expressao_Simples();
}
}

//<comando_saida> ::= escreva “(“ <expressao> { “,” <expressao> } “)”
void Comando_Saida(){
  consome(ESCREVA);
  consome(ABRIR_PARENTESES);
  expressao();
  while(buffer[i-1]==','){
    consome(VIRGULA);
    expressao();
      }
  consome(FECHAR_PARENTESES);
}

//<comando_atribuicao> ::= identificador “:=” <expressao>
void Comando_Atribuicao(){
  consome(IDENTIFICADOR);
  consome(DOIS_PONTOS);
  consome(IGUAL);
  expressao();
}

//<comando_se> ::= se “(” <expressao> “)” entao <comando> [senao <comando>]
void Comando_Se(){
  consome(SE);
  consome(ABRIR_PARENTESES);
  expressao();
  consome(FECHAR_PARENTESES);
  consome(ENTAO);
  comando();
  if(lookahead==34){
    consome(SENAO);
    comando();
  }
  
}

//<comando_enquanto> ::= enquanto “(” <expressao> “)” faca <comando>
void Comando_Enquanto(){
  consome(ENQUANTO);
  consome(ABRIR_PARENTESES);
  expressao();
  consome(FECHAR_PARENTESES);
  consome(FACA);
  comando();
}

//<comando_entrada> ::= leia “(“ <lista_variavel> “)”
void Comando_Entrada(){
  consome(LEIA);
  consome(ABRIR_PARENTESES);
  Lista_Variavel();
  consome(FECHAR_PARENTESES);
}

//<comando_composto> ::= inicio <comando> { “;” <comando>} fim
void Comando_Composto(){
  //if lookahead não for erro
  if(lookahead!=0){
  InfoAtomo = obter_atomo();
  lookahead = InfoAtomo.atomo;
 comando();
    //9=Ponto Virgula
  while(lookahead==9){
    consome(PONTO_VIRGULA);
if(lookahead==11||lookahead==2||lookahead==30||lookahead==32||lookahead==31)
      comando();
  else{
    lookahead=1;
    erro=1;
    break;
  }
}
    //if lookahead não for erro
  if(lookahead!=0)
    consome(FIM);
  }
}

//<comando> ::= <comando_atribuicao> |<comando_se> |<comando_enquanto> |<comando_entrada> |<comando_saida> |<comando_composto>
void comando(){
  //11= Escreva
  if(lookahead==11){
  Comando_Saida();
  }
    //2=Identificador
  else if(lookahead==2){
  Comando_Atribuicao();
  }
    //30 = se
  else if(lookahead==30){
  Comando_Se();
  }
    //31 = enquanto
  else if(lookahead==31){
  Comando_Enquanto();
  }
    //32 = leia
  else if(lookahead==32){
  Comando_Entrada();
  }
    // 1= inicio
  else if(lookahead==1){
  Comando_Composto();
  }
}

void bloco(){
  DeclaracaoVariavel();
  Comando_Composto();
}

void programa(){
    consome(ALGORITMO);
    consome(IDENTIFICADOR);
    consome(PONTO_VIRGULA);
    bloco();
    consome(PONTO);
}