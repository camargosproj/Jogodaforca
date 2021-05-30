#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
int fim;
struct tentativas{
    char letrasdigitadas[26];
    int contador;
    int erros;
    int acertos;
} tentativa;
struct jogadores{
    char nome[20];
}jogador1;

bool tentarPalavra(){
    char palavraCompleta[TAMANHO_PALAVRA];
    if(tentativa.acertos == strlen(palavrasecreta)/2){
        printf("Já sabe a palavra? Digite: ");
        scanf("%s", palavraCompleta);
        for(int i = 0; i < strlen(palavrasecreta); i++){
        if(palavraCompleta[i] == palavrasecreta[i]){
            fim = 1;
            return false;
        }else{
            tentativa.erros = 5;
        }
    }
    }
}
int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
   
    for(int i = 0; i < tentativa.contador; i++) {

        if(!letraexiste(tentativa.letrasdigitadas[i])) {
            tentativa.erros++;
        }
    }

    return tentativa.erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return fim;
        }
        
    }

    return fim;
}


void iniciar() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n"); 

    printf("Digite o nome do primeiro Jogador: ");
    scanf("%s",jogador1.nome);
    printf("Olá %s, Bem-Vindo\n\n", jogador1.nome);


}

void chuta() {
    char chute;
    printf("Tente uma letra: ");
    scanf(" %c", &chute);    
    printf("A palavra é %s \n",palavrasecreta);


    if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
        tentativa.acertos++;
    } else {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }

    tentativa.letrasdigitadas[tentativa.contador] = chute;
    tentativa.contador++;
}

int jachutou(char letra) {
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
void desenhaforca() {

    int erros = chuteserrados();

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

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}
//Procura palavra no arquivo txt usando a função rand 
void escolhepalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

//Acessa o aquivo txt para adicionar novas palavras
void adicionapalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }

}
//Inicio do programa
int main() {

    iniciar();
    escolhepalavra();

    do {
        tentarPalavra();
        desenhaforca();
        chuta();
    } while (!ganhou() && !enforcou() && tentarPalavra());

    if(ganhou()) {
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();
}