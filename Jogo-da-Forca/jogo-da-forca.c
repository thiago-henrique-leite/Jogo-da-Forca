//JOGO DA FORCA COMPLETO -IMPLEMENTADO POR THIAGO HENRIQUE LEITE DA SILVA
//Ultima Atualizacao em 06/setembro/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define maxtam 50 //Tamanho máximo de uma palavra
#define limpaTela system("cls") 

//CABECALHO DE FUNCOES 
void inicia_variaveis();
int  letra_repetida(char);
void comoJogar();
void creditos();
void modo_de_jogo();
void escolha_da_palavra();
void sorteiaPalavra();
void abertura();
int  tela_inicial();
void inicia_palavra();
void imprime_palavra();
void iniciaVetor();
void atualiza_contador();
void le_novaletra();
void imprime_letrastentadas();
void verifica_novaletra();
void atualiza_infos();
void desenhaforca();
int  terminou();
void jogo_da_forca();
void resultado();
int  jogar_denovo();
int  sair();

//******************************************************************VÁRIÁVEIS GLOBAIS***************************************************************************************

char palavra_sorteada[maxtam], chutes[maxtam], dica[maxtam], palavra_digitada[maxtam]; 
int num_chutes, max_chutes, indice, certas, encontrou, indice_dica;
int tam_palavra, cont, erros, quant_letras, soma, inicio, modoJogo;
char *letras_tentadas;
char reiniciar, c;
 
//BANCO DE PALAVRAS
char bancodePalavras[100][maxtam] = 
    {
        "null", "Nome", "Cidade ou Pais", "Marca", "Objeto", "Profissao", "Animal", "Alimento", "Tem no Hospital", "Time de Futebol",                    //Dicas
        "Romario", "Alcione", "Marinalva", "Orivaldo", "Claudete", "Pietro", "Jamylle", "Bernardo", "Antonella", "Tobias",                               //Nomes
        "Madrid", "Egito", "Jacarei", "Africa", "Israel", "Singapura", "Bahamas", "Guatemala", "Honduras", "Indonesia",                                  //Cidades ou Países
        "Danone", "Havaianas", "Yamaha", "Lamborghini", "Porsche", "Samsung", "Gillette", "Diesel", "Oakley", "Uber",                                    //Marcas
        "Machado", "Webcam", "Sanfona", "Teclado", "Vassoura", "Gaiola", "Telescopio", "Coturno", "Parafusadeira", "Bicicleta",                          //Objetos
        "Economista", "Astronomo", "Psicopedagogo", "Nutricionista", "Esteticista", "Pedreiro", "Jornalista", "Advogado", "Programador", "Engenheiro",   //Profissões
        "Babuino", "Quati", "Orangotango", "Hipopotamo", "Dromedario", "Jabuti", "Mariposa", "Pinguim", "Rinoceronte", "Capivara",                       //Animais
        "Estrogonofe", "Marmelada", "Tamarindo", "Yakissoba", "Caviar", "Rocambole", "Damasco", "Nectarina", "Temaki", "Feijoada",                       //Alimentos
        "Seringa", "Equipamentos", "Exames", "Medicamento", "Cirurgia", "Parto", "Enfermeira", "Benzetacil", "Paciente", "Atendimento",                  //Tem no Hospital
        "Santos", "Barcelona", "Juventus", "Figueirense", "Zenit", "Penapolense", "Liverpool", "Chelsea", "Independiente", "Cruzeiro"                    //Times de Futebol
    };
    
//***************************************************************************************************************************************************************************
    
//INICIALIZA AS VARIÁVEIS COM OS DEVIDOS VALORES
void inicia_variaveis() {
    quant_letras=0;
    indice_dica=0;
    tam_palavra=0;
    max_chutes=7;
    num_chutes=0; 
    encontrou=0; 
    modoJogo=0;
    indice=0; 
    certas=0; 
    erros=0;
    soma=0; 
    cont=7;
}

//VERIFICA SE A LETRA NaO e REPETIDA
int letra_repetida(char letra) {
    int aux=0;
    
    for(int i=0; i<soma; i++)
        if(letra == letras_tentadas[i]) 
            aux = 1;
            
    if(aux==0) return 1;
    else return 0;
}

//REGRAS DE COMO JOGAR
void comoJogar() {
    char resp;
    abertura();
    printf("\n\n\t\tComo Jogar:\n");
    printf("\n\t(1) O jogador tem que acertar qual e a palavra proposta, tendo como dica o tema ligado a palavra.");
    printf("\n\t(2) A cada rodada o jogador digita uma letra por vez.");
    printf("\n\t(3) A cada letra certa, sera revelado em que lugar ela se encontra na palavra secreta.");
    printf("\n\t(4) A cada letra errada, e desenhada uma parte do corpo do enforcado e perde-se uma vida.");
    printf("\n\t(5) O jogo termina se o jogador perder as 7 vidas ou completar a palavra proposta.");
    printf("\n\t(6) O modo de jogo <1> seleciona uma palavra aleatoria do jogo e da uma dica para o jogador tentar acertar.");
    printf("\n\t(7) O modo de jogo <2> permite o usuario digitar uma palavra e uma dica para um amigo tentar advinhar.");
    printf("\n\t(8) Omitir os acentos na hora da digitacao das palavras.");                     
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PRESSIONE <ENTER> PARA VOLTAR A TELA INICIAL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\t");
    fflush(stdin);
    while(resp != 10) 
        resp = getchar();
    tela_inicial();
}

//CReDITOS DO JOGO
void creditos() {
    int resp;
    abertura();
    printf("\n\n\t\tCreditos:\n");
    printf("\n\tJogo desenvolvido por Thiago Henrique Leite da Silva");
    printf("\n\t3 Semestre de Ciencia da Computacao na Universidade Federal de Sao Paulo (UNIFESP)");
    printf("\n\tUltima modificacao em 06/09/2020");
    printf("\n\tinstagram.com/thiagoh.leite");
    printf("\n\tgithub.com/thiago-henrique-leite");
    printf("\n\n\tDeus e Fiel");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PRESSIONE <ENTER> PARA VOLTAR A TELA INICIAL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\t");
    fflush(stdin);
    while(resp != 10) 
        resp = getchar();
    tela_inicial();
}

//OPcÕES INICIAIS - MODO DE JOGO
void modo_de_jogo() {
    char lixo;
    abertura();
    printf("\n\t\t\t\t\t\t  ----------------------------\n");
    printf("\t\t\t\t\t\t  |       MODO DE JOGO       |\n");
    printf("\t\t\t\t\t\t  ----------------------------\n");
    printf("\t\t\t\t\t\t  |     <1> SINGLE-PLAYER    |\n");
    printf("\t\t\t\t\t\t  |     <2> MULTIPLAYER      |\n");
    printf("\t\t\t\t\t\t  |     <3> VOLTAR           |\n");
    printf("\t\t\t\t\t\t  ----------------------------\n");
    printf("\n\t\t\t\t\t Digite a opcao desejada e pressione <enter>: ");
    scanf("%d", &modoJogo);
    scanf("%c", &lixo);
    if(modoJogo != 1 && modoJogo != 2 && modoJogo != 3)
        modo_de_jogo();
    else if(modoJogo == 3)
        tela_inicial();
}

//ESCOLHA DA PALAVRA, SE SERÁ ALEATÓRIA OU DIGITADA
void escolha_da_palavra() {
    
    abertura();
    
    if(modoJogo == 2) {
        printf("\n\tNo Modo MULTIPLAYER e voce quem escreve a palavra e uma dica relacionada a ela para seu amigo advinhar!\n");
        printf("\n\tObservacao: Omitir os acentos da palavra escolhida.\n");
        printf("\n\t\tDigite a palavra e pressione <enter>: ");
        scanf(" %[^\n]s", palavra_digitada);
        
        strcpy(palavra_sorteada, palavra_digitada);
        tam_palavra = strlen(palavra_sorteada);
        quant_letras = tam_palavra;
        
        printf("\t\tDigite uma dica relacionada a esta palavra e pressione <enter>: ");
        scanf(" %[^\n]s", dica);
    }
    else sorteiaPalavra();
}

//SORTEIA UMA PALAVRA DO BANCO DE PALAVRAS E DETERMINA A DICA PARA ESTA PALAVRA
void sorteiaPalavra() {
    
    int indice_palavra;
    
    //sorteia um nUmero aleatório entre 10 e 99
    srand(time(NULL));
    indice_palavra = rand()%100;
        if(indice_palavra < 90)
            indice_palavra = indice_palavra+10;

    //calcula o índice da dica da palavra sorteada (as dicas estao do índice 1 ate o 9)
    indice_dica = indice_palavra/10;
    
    strcpy(palavra_sorteada, bancodePalavras[indice_palavra]);
    tam_palavra = strlen(palavra_sorteada);
    quant_letras = tam_palavra;
    strcpy(dica, bancodePalavras[indice_dica]);
}

//ABERTURA DO JOGO
void abertura() {
    
    limpaTela;
    printf("\n\t\t          __  ______  ______  ______    ____    ______    _____  ______  ____    ______  ______        "); 
    printf("\n\t\t         / / / __  / / ____/ / __  /   / __ \\  / _   /   / ___/ / __  / / __ \\  / ____/ / _   /        ");
    printf("\n\t\t    __  / / / / / / / / __  / / / /   / / / / / /_/ /   / /_   / / / / / /_/ / / /     / /_/ /     ");
    printf("\n\t\t   / /_/ / / /_/ / / /_/ / / /_/ /   / /_/ / / __  /   / __/  / /_/ / / // /  / /___  / __  /      ");
    printf("\n\t\t  /_____/ /_____/ /_____/ /_____/   /_____/ /_/ /_/   /_/    /_____/ /_/ /_/ /_____/ /_/ /_/        ");
    printf("\n\n");    
}

//TELA DE BOAS VINDAS
int tela_inicial() {
    char lixo;
    abertura();
    inicio = 0;
    printf("\n\n\t\t\t\t\t\t\t BEM-VINDO(A)!\n\n");
    printf("\t\t\t ESTE JOGO TEM POR OBJETIVO AJUDAR CRIANCAS A ULTRAPASSAREM PROBLEMAS DE DISLEXIA\n\n\n");
    printf("\t\t\t\t\t\t  ----------------------------\n");
    printf("\t\t\t\t\t\t  |      MENU PRINCIPAL      |\n");
    printf("\t\t\t\t\t\t  ----------------------------\n");
    printf("\t\t\t\t\t\t  |      1. NOVO JOGO        |\n");
    printf("\t\t\t\t\t\t  |      2. COMO JOGAR       |\n");
    printf("\t\t\t\t\t\t  |      3. CREDITOS         |\n");
    printf("\t\t\t\t\t\t  |      4. SAIR             |\n");
    printf("\t\t\t\t\t\t  ----------------------------\n");
    printf("\n\t\t\t\t\t Digite a opcao desejada e pressione <enter>: ");
    scanf("%d", &inicio);
    scanf("%c", &lixo);
    
    if(inicio==1) 
        modo_de_jogo();
    
    else if(inicio==2) 
        comoJogar();
    
    else if(inicio==3) 
        creditos();
    
    else if(inicio==4)
        return 0;    
        
    else tela_inicial();
    
}

//INICIA A PALAVRA COM ESPAÇOS VAZIOS
void inicia_palavra() {
    
    for(int i=0; i<tam_palavra; i++) {
        if(palavra_sorteada[i] == '-' || palavra_sorteada[i] == ' ') {
            certas++;
            quant_letras--;
            if(palavra_sorteada[i] == '-')
                chutes[i] = '-';
        }
        else chutes[i] = '_';
    }
    
}

//IMPRIME ESPAÇOS DA PALAVRA A SEREM PREENCHIDOS
void imprime_palavra() {
    
    printf("\n\n\t  PALAVRA: ");
    for(int i=0; i<tam_palavra; i++) 
            if(chutes[i] == '_')
                printf(" __");
            else if(chutes[i] == '-')
                printf(" - ");
            else if(chutes[i] == ' ')
                printf("   ");
            else printf("  %c", chutes[i]);
    printf("  (%d LETRAS)\n", quant_letras);
    printf("\n\t  Dica: %s\n", dica);
    printf("\n\t  *********************************************************************************************************\n");
    
}

//INICIA VETOR COM AS LETRAS TENTADAS
void iniciaVetor() {
    letras_tentadas = (char*)malloc((tam_palavra+max_chutes) * sizeof(char));
}

//ATUALIZA O CONTADOR DE TENTATIVAS 
void atualiza_contador() {
    printf("\n\t  Vidas Restantes = %d\t\t\t\t    Digite '#' a qualquer momento para abandonar a partida!\n", cont);
}

//Le UMA NOVA LETRA
void le_novaletra() {
    
    char lixo;
    int auxiliar;
    
    printf("\t  Digite uma letra e pressione <enter>: ");
    c = getchar();
    scanf("%c", &lixo);
    
    auxiliar = c; //Tratamento caso o usuário insira a letra depois de pressionar enter
    if(auxiliar == 10) 
        if(lixo != 10) {
            c = lixo;
            scanf("%c", &lixo);
        }
  
    if(c != '#' && c != 10) {
        verifica_novaletra();
        letras_tentadas[indice] = c;
        indice++;
        soma++;
    }
    
}

//IMPPRIME LETRAS JÁ TENTADAS
void imprime_letrastentadas() {
    
    if(indice != 0) {
            printf("\n\t  Letras Tentadas: ");
            for(int i=0; i<indice; i++) 
                printf("%c / ", letras_tentadas[i]);
            printf("\n");
        }
}

//VERIFICA SE A LETRA INSERIDA ESTÁ NA PALAVRA
void verifica_novaletra() {
    
    encontrou=0;
    if(letra_repetida(c)==1) 
            for(int i=0; i<tam_palavra; i++)
                if(toupper(palavra_sorteada[i]) == toupper(c)) {
                    chutes[i] = toupper(c);
                    certas++;
                    encontrou=1;
                }
}

//ATUALIZA O CONTADOR, QUANTIDADE DE ERROS E NUMERO DE CHUTES
void atualiza_infos() {
    
    if(c != 10)
        if(!encontrou && c != '#') {
            cont--;
            erros++;
        }
        else num_chutes++;
    
}

//DESENHA A FORCA
void desenhaforca() {
    
    printf("\n");
	printf("\t      _______       \n");
	printf("\t     |/      |      \n");
	printf("\t     |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	printf("\t     |      %c%c%c  \n", (erros>=4?'\\':' '), (erros>=2?'|':' '), (erros>=5?'/': ' '));
	printf("\t     |       %c     \n", (erros>=3?'|':' '));
	printf("\t     |      %c %c   \n", (erros>=6?'/':' '), (erros>=7?'\\':' '));
	printf("\t     |              \n");
	printf("\t    _|___           \n");
	printf("\n");
	
	
}

//VERIFICA SE O JOGO TERMINOU
int terminou() {
    return(certas == tam_palavra || cont <= 0 || c == '#');
}

//FUNcaO DO JOGO EM SI
void jogo_da_forca() {
    
    do {
        abertura();
        imprime_palavra();
        atualiza_contador();
        imprime_letrastentadas();
        desenhaforca();
        le_novaletra();
        atualiza_infos();
        
    } while(!terminou());
    
}

//IMPRIME O RESULTADO DA PARTIDA
void resultado() {
    
    if(cont <= 0 || c == '#') {
        printf("\n\t\t    INFELIZMENTE VOCE PERDEU, TENTE NOVAMENTE! A PALAVRA ERA --> %s <--", palavra_sorteada);
        printf("\n\t\t\t\t\t\t          __       ");
        printf("\n\t\t\t\t\t\t         |  |      ");
        printf("\n\t\t\t\t\t\t     ____|  |____  ");
        printf("\n\t\t\t\t\t\t    |____    ____| ");
        printf("\n\t\t\t\t\t\t         |  |      ");
        printf("\n\t\t\t\t\t\t         |  |      ");
        printf("\n\t\t\t\t\t\t         |  |      ");
        printf("\n\t\t\t\t\t\t         |__|      ");
        printf("\n\n");
    } 
    else {
        printf("\t\t\t\t\t\t  PARABENS, VOCE GANHOU!");
        printf("\n\t\t\t\t\t\t                __ ");
        printf("\n\t\t\t\t\t\t               |  |");
        printf("\n\t\t\t\t\t\t         ______|  |");
        printf("\n\t\t\t\t\t\t        |______   |");
        printf("\n\t\t\t\t\t\t        |______   |");
        printf("\n\t\t\t\t\t\t     ___|______   |");
        printf("\n\t\t\t\t\t\t    |_____________|");
        printf("\n\n");
    }
    
}

//VERIFICA SE O USUÁRIO QUER JOGAR DENOVO
int jogar_denovo() {
    char lixo;
    int auxiliar;
    if(c != '#') {
            printf("\tQuer jogar denovo? <S> SIM <N> NAO -> ");
            scanf("%c", &reiniciar);
            scanf("%c", &lixo);
            if(toupper(lixo) == toupper('s')) {
                reiniciar = lixo;
                scanf("%c", &lixo);
            }
    }
}

//VERIFICA SE O USUÁRIO QUER SAIR DO JOGO
int sair() {
    if(inicio==4)
        return 1;
    else return 0;
}

int main() {
    
    setlocale(LC_ALL, "Portuguese");
    system("color 47");
    
    do {
        inicia_variaveis();
        abertura();
        tela_inicial();
        if(!sair()) {
            escolha_da_palavra();
            inicia_palavra();
            iniciaVetor();
            jogo_da_forca();
            abertura();
            imprime_palavra();
            imprime_letrastentadas();
            desenhaforca();
            resultado();
            jogar_denovo();
            free(letras_tentadas);
        }
        
    } while(toupper(reiniciar) == 'S' && c != '#' && inicio != 4);
    
    printf("\n\n\tOBRIGADO POR JOGAR, VOLTE SEMPRE!\n\n");
    
}