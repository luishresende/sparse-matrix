#include <stdio.h>
#include <stdlib.h>
#include "Encadeamento.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    int linhas, colunas;
    printf("\n\tInforme a quantidade de linhas e a quantidade de colunas que você quer que a matriz tenha: \n\tLinhas: ");
    scanf("%d", &linhas);
    printf("\tColunas: ");
    scanf("%d", &colunas);
    Matriz* matriz = cria_matriz(linhas, colunas);
    Elemento *aux;
    struct aluno al;
    int l, c, matricula;
    int opcao;
    char y;

    do{
        printf("\n\t|---------- MENU ENCADEAMENTO -----------|"
               "\n\t|0 - Sair do programa                    |"
               "\n\t|1 - Insere dados na matriz              |"
               "\n\t|2 - Consulta por Coordenadas            |"
               "\n\t|3 - Consulta por Matricula              |"
               "\n\t|4 - Imprime os dados da Matriz          |"
               "\n\t|5 - Imprime os vizinhos                 |"
               "\n\t|----------------------------------------|"
               "\n\tOpcao........");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                system("cls");
                printf("\n\tInforme as coordenadas que deseja inserir o aluno: \n\tLinha: ");
                scanf("%d", &l);
                printf("\tColuna: ");
                scanf("%d", &c);
                inserir_dados(&al); // pede ao usuário para inserir os dados do aluno
                insere_matriz_byPos(matriz, l, c, al);

                break;

            case 2:
                system("cls");
                printf("\n\tInforme as coordenadas que deseja consultar: \n\tLinha: ");
                scanf("%d", &l);
                printf("\tColuna: ");
                scanf("%d", &c);

                aux = consulta_matriz_byPos(matriz, l, c);

                if(aux)
                    imprime_um_elemento(&aux);
                else
                    printf("\n\tPosição não contém dados!!");

                aux = NULL;
                break;

            case 3:
                system("cls");
                printf("\n\tInforme a matricula que deseja encontrar: ");
                scanf("%d", &matricula);
                aux = consulta_matriz_Matricula(matriz, matricula);

                if(aux)
                    imprime_um_elemento(&aux);
                else
                    printf("\n\tMatricula não encontrada!!\n");

                aux = NULL;
                break;

            case 4:
                system("cls");
                if(imprime_matriz(matriz)){
                    imprime_matriz(matriz);
                    break;
                } else
                    printf("\n\tMatriz vazia!!\n");
                break;

            case 5:
                system("cls");
                printf("\n\tInforme as coordenadas que deseja consultar: \n\tLinha: ");
                scanf("%d", &l);
                printf("\tColuna: ");
                scanf("%d", &c);
                if(imprime_vizinhos(matriz, l, c)){
                    imprime_vizinhos(matriz, l, c);
                } else
                    printf("\n\tPosição não econtrada!!\n");
                break;

            default:
                if(opcao == 0){
                    libera_Matriz(matriz);
                }
        }
        system("pause");
        system("cls");
    }while(opcao != 0);
    return 0;
}
