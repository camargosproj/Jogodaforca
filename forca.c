 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constante para uso do tamanho limite da palvras secreta
#define tamanho 20
//Declaração de funções
void iniciar();
void tentarletra();
void mostraforca();
void escolhepalavrasecreta();
int palavraSecretaou();
int perdeu();
int jatentou(char letra);

int letraexiste(char letra);

char palavrasecreta[tamanho];
struct tentativas{
    char letrasdigitadas[30];
    int contador;
} tentativa;
struct jogadores{
    char nome[20];
}jogador;


void iniciar() {
    printf("/////////////////////\n");
    printf("//    BEM-VINDO   //\n");
    printf("// JOGO DA FORCA //\n");
    printf("///////////////////\n\n"); 

    printf("DIGITE SEU NOME: ");
    scanf("%s",jogador.nome);
    printf("OLÁ, %s! BEM-VINDO\n\n", jogador.nome);


}
int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

// retorna a quantida de erros para quebrar o loop
int tentativaserradas() {
    int erros = 0;

    for(int i = 0; i < tentativa.contador; i++) {

        if(!letraexiste(tentativa.letrasdigitadas[i])) {
            erros++;
        }
    }

    return erros;
}

int perdeu() {
    return tentativaserradas() >= 5;
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jatentou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}
void tentarletra() {
    char chute;
    printf("DIGITE UMA LETRA MAIUSCULA: ");
    scanf(" %c", &chute);    

    if(letraexiste(chute)) {
        printf("VAMOS LÁ! A PALAVRA CONTÉM A LETRA %c\n\n", chute);
    } else {
        printf("\nQUE PENA! A PALAVRA NÃO CONTÉM A LETRA %c\n\n", chute);
    }

    tentativa.letrasdigitadas[tentativa.contador] = chute;
    tentativa.contador++;
}

int jatentou(char letra) {
    int achou = 0;
    for(int j = 0; j < tentativa.contador; j++) {
        if(tentativa.letrasdigitadas[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}
//Mostra a forca e O traço para adicionar a letra
void mostraforca() {

    int erros = tentativaserradas();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jatentou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}
//Procura palavra no arquivo txt usando a função rand 
void escolhepalavrasecreta() {
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("ARQUIVO NÃO DISPONÍVEL.\n\n");
        exit(1);
    }

    int numerodepalavras;
    fscanf(f, "%d", &numerodepalavras);

    srand(time(0));
    int numeroAleatorio = rand() % numerodepalavras;

    for(int i = 0; i <= numeroAleatorio; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

//Acessa o aquivo txt para adicionar novas palavras
void addNovaPalavra() {
    char op;

    printf("GOSTARIA DE ADICIONAR MAIS ALGUMA PALAVRA AO NOSSO BANCO DE PALAVRAS? (S/N)?");
    scanf(" %c", &op);

    if(op == 'S') {
        char novapalavra[tamanho];

        printf("DIGITE A PALAVRA, EM LETRAS MAIÚSCULAS: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("ARQUIVO NÃO DISPONÍVEL.\n\n");
            exit(1);
        }

        int contador;
        fscanf(f, "%d", &contador);
        contador++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", contador);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }

}
//Inicio do programa
int main() {
    iniciar();
    escolhepalavrasecreta();

    do {
        mostraforca();
        tentarletra();

    } while (!acertou() && !perdeu());

    if(acertou()) {
        printf("\nPARABÉNS, %s! VOCÊ CONSEGUIU!\n\n", jogador.nome);

        printf("--------------------------- \n");
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("////////VENCEDOR!////////// \n");
        printf("///////// %s /////////// \n", jogador.nome);
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("--------------------------- \n");

    } else {
        printf("\nQUE PENA, %s!NÃO FOI DESSA VEZ, TENTE MAIS UMA.\n", jogador.nome);
        printf("A PALAVRA SECRETA ERA ...\n\n");
        printf("--------------------------- \n");
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("///////// %s /////////// \n", palavrasecreta);
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("/////////////////////////// \n");
        printf("--------------------------- \n");


     
    }

    addNovaPalavra();
}
