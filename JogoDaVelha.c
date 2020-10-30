#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define MAT_SIZE 3

#define USUARIO 1
#define COMPUTADOR 0

int printInicio(char novamente[])
{
    char resp;
    while(toupper(resp) != 'S' || toupper(resp) != 'N' )
    {
        printf("Você quer jogar %so JOGO DA VELHA? (S/N)", novamente);
        fflush(stdin);
        resp = getchar();

        if(toupper(resp) == 'S')
            break;

        if(toupper(resp) == 'N')
            return 0;
    }
    system("cls");
    return 1;
}

void printMatriz(char matriz[MAT_SIZE][MAT_SIZE])
{
    printf("\n MATRIZ ATUAL:");

    printf("\nColuna  >\t 0\t 1\t 2\n\n");
    for(int i = 0; i < MAT_SIZE; i++)
    {
            printf("Linha %d > ", i);
        for(int j = 0; j < MAT_SIZE; j++)
        {
            printf("\t %c ",matriz[i][j]);
        }
        printf("\n");
    }
}

void vezComputador(char mat[MAT_SIZE][MAT_SIZE])
{
    int adicionado = 0;
    do{
        int i = rand() % 3;
        int j = rand() % 3;

    if(mat[i][j] == 'O' || mat[i][j] == 'X') //se a posição já está ocupada.
    {
        continue;
    }
    else
    {
        adicionado = 1;
        mat[i][j] = 'O';
    }
    }while(!adicionado);

    printf("\n\tO Computador jogou...\n\n");
}

void vezUsuario(char mat[MAT_SIZE][MAT_SIZE])
{
    int linha = 0;
    int coluna = 0;

    int valida = 0;

    do{
        printf("\nSua vez. *Esolha um campo válido.");
        printf("\n Linha: ");
        scanf("%d", &linha);
        printf("\n Coluna: ");
        scanf("%d", &coluna);

        if( ( (linha < 0 || linha > 2) || (coluna < 0 || coluna > 2) ) ||
            (mat[linha][coluna] == 'X' || mat[linha][coluna] == 'O') ) /*valida a posição*/
        {
            system("cls");
            printf("\n\t INSIRA UMA POSIÇÃO VÁLIDA.\n\n");
            valida = 0;
            printMatriz(mat);
        }
        else
            valida = 1;

    }while(!valida);

    mat[linha][coluna] = 'X';
}

void printVitoria(int userComp)
{
    if(userComp)
        printf("\n\n\t PARABÉNS !!! VOCÊ VENCEU !!. \n\n");
    else
        printf("\n\n\t UMA PENA. VOCÊ PERDEU, MAS TENTE NOVAMENTE. \n\n");
}

int verificaVitoria(char mat[MAT_SIZE][MAT_SIZE], int isUsuario)
{
    char verifica;
    if(isUsuario) //veerifica se a verificação é do usuario ou do computador
        verifica = 'X'; //usuario
    else
        verifica = 'O'; //computador

    //8 modos de vencer. Posições a seguir
    //00 + 11 + 22
    //02 + 11 + 20
    //00 + 10 + 20
    //01 + 11 + 21

    //02 + 12 + 22
    //00 + 01 + 02
    //10 + 11 + 12
    //20 + 21 + 22
    if( (mat[0][0] == verifica && mat[1][1] == verifica && mat[2][2] == verifica) ||
        (mat[0][2] == verifica && mat[1][1] == verifica && mat[2][0] == verifica) ||
        (mat[0][0] == verifica && mat[1][0] == verifica && mat[2][0] == verifica) ||
        (mat[0][1] == verifica && mat[1][1] == verifica && mat[2][1] == verifica) ||

        (mat[0][2] == verifica && mat[1][2] == verifica && mat[2][2] == verifica) ||
        (mat[0][0] == verifica && mat[0][1] == verifica && mat[0][2] == verifica) ||
        (mat[1][0] == verifica && mat[1][1] == verifica && mat[1][2] == verifica) ||
        (mat[2][0] == verifica && mat[2][1] == verifica && mat[2][2] == verifica) )
        {
            return 1;
        }
        return 0;
}

void limpaJogo(char mat[MAT_SIZE][MAT_SIZE])
{
    //limpa a matriz
    for(int i = 0; i <= MAT_SIZE; i++)
    {
        for(int j = 0; j <= MAT_SIZE; j++)
        {
            mat[i][j] = '-';
        }
    }
}

void finalizaJogo(int jogadas, int empates, int usuario_venceu, int comp_venceu)
{
    system("cls");
    printf("\n\n\t RELATORIO FINAL. \n");
    printf("Partidas jogadas: %d", jogadas);
    printf("\nPartidas empatadas: %d", empates);
    printf("\nUsuário venceu: %d", usuario_venceu);
    printf("\nComputador venceu: %d\n\n", comp_venceu);

    exit(1);
}

int empate(char mat[MAT_SIZE][MAT_SIZE])
{
    for(int i = 0; i <= MAT_SIZE; i++)
    {
        for(int j = 0; j <= MAT_SIZE; j++)
        {
            if( mat[i][j] == '-') //ainda tem posição disponível
                return 0;
        }
    }
    return 1; //se empate
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); //random toda execução. Para escolher a posição que o computador insere.
    /*
    - Descrição estratégias
    - Referências
    - Comentários
    */

    char mat[MAT_SIZE][MAT_SIZE] = {'-', '-', '-',
                                   '-', '-', '-',
                                   '-', '-', '-'};

    unsigned int partidas_jogadas = 0;
    unsigned int partidas_empatadas = 0;
    unsigned int usuario_venceu = 0;
    unsigned int comp_venceu = 0;


    /* 1 - vez do usuario       | Usuario:       X
     * 0 - vez do computador    | Computador:    O
     */
    int vez_usuario = 1;

    //application loop
    do
    {
        /* Se o usuario responde 'N' no inicio a partida e finalizada \
        *  e é mostrado os resultados para o usuário com finalizaJogo().
        */
        if(partidas_jogadas > 0) /*se não for o primerio jogo adiciona 'novamente' na pergunta.*/
        {
            if( !printInicio("novamente ") )
                finalizaJogo(partidas_jogadas, partidas_empatadas, usuario_venceu, comp_venceu);
        }
        else
        {
            if( !printInicio("") )
                finalizaJogo(partidas_jogadas, partidas_empatadas, usuario_venceu, comp_venceu);
        }


        int finalizada = 0;

        //loop - rodadas
        do
        {
            //vez do usuário
            if(vez_usuario)
            {
                printMatriz(mat);
                vezUsuario(mat);

                if( verificaVitoria(mat, USUARIO) ) //verifica vitória do usuario
                {
                    system("cls");

                    finalizada = 1;
                    printVitoria(USUARIO);
                    printMatriz(mat);

                    usuario_venceu++;
                }
                vez_usuario = 0; //vez do computador
            }
            else
            {
                //vez do computador
                vezComputador(mat);

                if( verificaVitoria(mat, COMPUTADOR) ) //verifica vitória do computador
                {
                    system("cls");

                    finalizada = 1;
                    printVitoria(COMPUTADOR);
                    printMatriz(mat);

                    comp_venceu++;
                }
                vez_usuario = 1;//vez do usuario
            }

            //verifica empate
            if( empate(mat) )
            {
                partidas_empatadas++;
                finalizada = 1;
            }

            if(!finalizada)
                system("cls");

        }while(!finalizada);

        //conta partidas jogadas
        partidas_jogadas++;

        printf("\n\n\t PARTIDA FINALIZADA. \n\n");

        //limpar jogo
        limpaJogo(mat);

        //vez do usuario - pois usuario começa jogando
        vez_usuario = 1;

    }while(1);

    system("cls");
    printf("\n\t JOGO ENCERRADO. \n");

    return 0;
}
