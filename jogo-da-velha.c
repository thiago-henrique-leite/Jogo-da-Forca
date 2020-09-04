//JOGO DA VELHA - IMPLEMENTADO POR THIAGO HENRIQUE LEITE DA SILVA
//Ultima Atualização em 04/setembro/2020

#include <stdio.h>
#include <stdlib.h>

int jogador, jogada, pos, fim;
char jogo[9], reinicio;
char player1[50], player2[50];

void inicializa() {
    jogada=0;
    fim=0;
    for(int i=0; i<9; i++) 
        jogo[i] = ' ';
}

void display(char jogo[]) {
    system("cls");
    printf("\n\n\t#*******JOGO DA VELHA*******#\n"); 
    printf("\n\t  1 | 2 | 3  \t  %c | %c | %c", jogo[0], jogo[1], jogo[2]);
    printf("\n\t-------------\t-------------");
    printf("\n\t  4 | 5 | 6  \t  %c | %c | %c", jogo[3], jogo[4], jogo[5]);
    printf("\n\t-------------\t-------------");
    printf("\n\t  7 | 8 | 9  \t  %c | %c | %c", jogo[6], jogo[7], jogo[8]);
    printf("\n");
}

int deuvelha() {
    return(jogada >= 9);
}

int terminou() {
    return(jogada>2 && (jogo[0]==jogo[1] && jogo[1]==jogo[2] && (jogo[0] == 'X' && jogo[2] == 'X' || jogo[0] == 'O' && jogo[2] == 'O') )
                    || (jogo[3]==jogo[4] && jogo[4]==jogo[5] && (jogo[3] == 'X' && jogo[5] == 'X' || jogo[3] == 'O' && jogo[5] == 'O') )
                    || (jogo[6]==jogo[7] && jogo[7]==jogo[8] && (jogo[6] == 'X' && jogo[8] == 'X' || jogo[6] == 'O' && jogo[8] == 'O') )
                    || (jogo[0]==jogo[3] && jogo[3]==jogo[6] && (jogo[0] == 'X' && jogo[6] == 'X' || jogo[0] == 'O' && jogo[6] == 'O') )
                    || (jogo[1]==jogo[4] && jogo[4]==jogo[7] && (jogo[1] == 'X' && jogo[7] == 'X' || jogo[1] == 'O' && jogo[7] == 'O') )
                    || (jogo[2]==jogo[5] && jogo[5]==jogo[8] && (jogo[2] == 'X' && jogo[8] == 'X' || jogo[2] == 'O' && jogo[8] == 'O') )
                    || (jogo[0]==jogo[4] && jogo[4]==jogo[8] && (jogo[0] == 'X' && jogo[8] == 'X' || jogo[0] == 'O' && jogo[8] == 'O') )
                    || (jogo[2]==jogo[4] && jogo[4]==jogo[6] && (jogo[2] == 'X' && jogo[6] == 'X' || jogo[2] == 'O' && jogo[6] == 'O') ) );
}

void resultado() {
    if(terminou()==1)
        printf("\n\t%s VENCEU!!!\n", jogador == 1 ? player1 : player2);
    else if(deuvelha()==1)
        printf("\n\tDEU VELHA!!!\n");
}

void nomes_jogadores() {
    printf("\n\tDigite o nome do jogador 1: ");
    scanf(" %[^\n]s", player1);
    printf("\n\tDigite o nome do jogador 2: ");
    scanf(" %[^\n]s", player2);
}

int main(void) {

    system("color 60");

    do {
        inicializa();
        display(jogo);
        nomes_jogadores();
        do {
            display(jogo);
            if(jogada % 2 == 0)
                jogador = 1;
            else jogador = 2;
            
            printf("\n\t%s [%c]\n", jogador==1 ? player1 : player2, jogador==1 ? 'X':'O');
            printf("\n\tDigite a posicao da jogada: ");
            scanf("%d", &pos);
            
            if(pos>=1 && pos<=9) {
                if(jogo[pos-1] == ' ') {
                    if(jogador==1)
                        jogo[pos-1] = 'X';
                    else jogo[pos-1] = 'O';
                    jogada++;
                }
            }
        } while(!terminou() && !deuvelha());
        
        display(jogo);
        resultado();
        printf("\n\tQuer jogar denovo? <S> Sim <N> Nao: ");
        scanf(" %c", &reinicio);
        
    } while(toupper(reinicio)=='S');
    
}
