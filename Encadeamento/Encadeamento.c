//
// Created by Luis Resende on 5/8/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "Encadeamento.h"
//Definição do tipo matriz

// Função para inserir os dados da struct aluno
void inserir_dados(struct aluno *al){
    system("cls");
    printf("\n\tMatricula...: ");
    scanf("%d", &al->matricula);
    printf("\tNome...: ");
    scanf(" %[^\n]", al->nome);
    printf("\tNota 1...: ");
    scanf("%f", &al->n1);
    printf("\tNota 2...: ");
    scanf("%f", &al->n2);
    printf("\tNota 3...: ");
    scanf("%f", &al->n3);
/* função que recebe como parâmetro um struct, e pede para p usuário inserir os dados */
}

Matriz* cria_matriz(int lin, int col){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    if(matriz != NULL){
        *matriz = NULL;
    }
    Elemento *aux;

    //Alocando as linhas
    for(int l = -1; l < lin; l++){
        Elemento *no = (Elemento*) malloc(sizeof(Elemento));
        if(l == -1){
            (*matriz) = no;
            no->lin =  l;
            no->col = -1;
            no->cima = NULL;
            no->baixo = NULL;
            no->dir = no;
            no->esq = no;
            aux = no;
        }else if(l == lin-1){
            no->lin =  l;
            no->col = -1;
            no->cima = aux;
            no->baixo = *matriz;
            (*matriz)->cima = no;
            aux->baixo = no;
            no->esq = no;
            no->dir = no;
        } else {
            no->lin =  l;
            no->col = -1;
            no->cima = aux;
            no->cima->baixo = no;
            aux = no;
            no->dir = no;
            no->esq = no;
        }
    }

    //Alocando as colunas
    aux = *matriz;
    for(int c = 0; c < col; c++){
        Elemento *no = (Elemento*) malloc(sizeof(Elemento));
        if(c == col-1){
            no->esq = aux;
            no->dir = *matriz;
            (*matriz)->esq = no;
            aux->dir = no;
            no->cima = no;
            no->baixo = no;
            no->col = c;
            no->lin = -1;
        } else {
            no->col = c;
            no->lin = -1;
            no->esq = aux;
            no->esq->dir = no;
            aux = no;
            no->baixo = no;
            no->cima = no;
        }
    }
    return matriz;
}

int libera_Matriz(Matriz* matriz) {
    int libera_Matriz(Matriz* matriz) {
    if(matriz != NULL) {
        Elemento *linhaAtual = (*matriz)->baixo; // RECEBE A CABEÇA APOTANDO PARA BAIXO
        Elemento *colunaAtual;
        Elemento *remover;

        while (linhaAtual != *matriz) { // PERCORRE LINHA POR LINHA
            colunaAtual = linhaAtual->dir; // RECEBE A LINHA PARA QUE POSSA PERCORRER ELA
            while (colunaAtual != linhaAtual) { // PERCORRE TODA A LINHA COLUNA POR COLUNA E VAI IMPRIMINDO AS INFORMAÇÕES
                remover = colunaAtual;
                colunaAtual = colunaAtual->dir;
                free(remover);
            }
            linhaAtual = linhaAtual->baixo;
            free(linhaAtual);
        }
        free(matriz);
    }
}
}

int quantLinhas_matriz(Matriz* cabeca){
    Elemento *no = *cabeca;
    int quant = 0;
    while(no->baixo != *cabeca){
        quant++;
        no = no->baixo;
    }

    return quant;
}

int quantColunas_matriz(Matriz* cabeca){
    Elemento *no = *cabeca;
    int quant = 0;
    while(no->dir != *cabeca){
        quant++;
        no = no->dir;
    }

    return quant;
}

int insere_matriz_byPos(Matriz* matriz, int l, int c, struct aluno al){
    int maxL = quantLinhas_matriz(matriz); // ARAMAZENA A QUANTIDADE DE LINHAS QUE A MATRIZ TEM
    int maxC = quantColunas_matriz(matriz); // ARAMAZENA A QUANTIDADE DE COLUNAS QUE A MATRIZ TEM

    // VERIFICA SE AS POSIÇÕES INFORMADAS PELO USUÁRIO NÃO UTRAPASSARAM O LIMITE OU FORAM MENOR QUE O LIMITE DA MATRIZ
    if((l+1 > maxL || c+1 > maxC) || (l < 0 || c < 0)){
        return 0;
    }

    Elemento *no = *matriz; //DEFININDO O NÓ = CABEÇA DA MATRIZ
    Elemento *noNovo = (Elemento*) malloc(sizeof(Elemento)); //ALOCANDO MEMÓRIA PARA O NOVO NÓ
    Elemento *aux = NULL; //APONTANDO AUX PARA NULL

    int linha = l, coluna = c;

    while(aux == NULL){// OBTENDO O ELEMENTO QUE FICARÁ ACIMA DO NOVO NÓ QUE ESTÁ SENDO INSERIDO
        linha--;
        aux = (Elemento*) consulta_matriz_byPos(matriz, linha, coluna); // BUSCANDO O ELEMENTO
    }
    noNovo->cima = aux; // O NOVO NÓ APONTA PARA O ELEMENTO QUE FICA EM CIMA DELE QUE FOI ACABADO DE ENCONTRAR

    linha = l; // LINHA VOLTA A RECEBER O VALOR INSERIDO PELO USUÁRIO
    aux = NULL; // VOLTA A RECEBER NULO PARA PODER AGORA VERIFICAR QUEM VAI FICAR A BAIXO DO NOVO NÓ

    while(aux == NULL){ // OBTENDO O ELEMENTO QUE FICARÁ ABAIXO DO NÓ
        linha++;
        aux = (Elemento*) consulta_matriz_byPos(matriz, linha, coluna);
        if(aux == NULL && linha == maxL){
            aux = (Elemento*) consulta_matriz_byPos(matriz, -1, coluna);
        }
    }

    noNovo->baixo = aux; // O PONTEIRO DE BAIXO DO NOVO NÓ APONTA PARA ELEMENTO ENCONTRADO ABAIXO DO DESSA POSIÇÃO
    noNovo->dados = al;
    noNovo->lin = l; // ARMAZENA A COORDENADA DA LINHA
    noNovo->col = c; // ARMAZENA A COORDENADA DA COLUNA

    aux = *matriz; // APONTA PARA CABEÇA
    linha = -1; // LINHA RECEBE A POSIÇÃO DE REFERÊNCIA

    while(no->baixo != aux){ // ANDANDO AS POSIÇÕES PARA BAIXO DA MATRIZ (LINHAS)
        if(linha == l){
            break;
        }
        no = no->baixo;
        linha++;
    }

    aux = no;
    coluna = -1;
    while(no->dir != aux && no->dir->col < noNovo->col){ // PERCORRENDO AS COLUNAS ATÉ A POSIÇÃO DESEJADA
        if(coluna == c){
            break;
        }
        no = no->dir;
        coluna++;
    }

    if(no == aux) { // APONTAMENTOS PARA CASO O NO SEJA A PRÓPRIA CABEÇA
        noNovo->esq = no;
        noNovo->dir = no;
        no->dir = noNovo;
        if(no->esq == no){
            no->esq = noNovo;
        }
    }else if(noNovo->lin == no->lin && noNovo->col == no->col){ // SOBRESCREVENDO OS DADOS DO ALUNO, CASO A LINHA E A COLUNA INFORMADA JÁ EXISTIREM
        no->dados = noNovo->dados;
    } else { // APONTAMENTO PARA CASOS NORMAIS
        noNovo->esq = no;
        noNovo->dir = no->dir;
        no->dir = noNovo;
    }
    return 1;
}

Elemento* consulta_matriz_byPos(Matriz* matriz, int l, int c){
    Elemento *no = *matriz;

    int maxL = quantLinhas_matriz(matriz); //RECEBENDO O TAMANHO MAXIMO DA MATRIZ
    int maxC = quantColunas_matriz(matriz);
    if(l+1 > maxL || c+1 > maxC){ //RETORNANDO CASO AS COORDENADAS EXCEDEREM O LIMITE
        return NULL;
    }
    int linha = -1, coluna = -1; //LINHA E COLUNA INICIAIS

    while(no->baixo != *matriz){ //PERCORRENDO A LINHA
        if(linha == l){
            break;
        }
        no = no->baixo;
        linha++;
    }

    Elemento *aux = no; //CABEÇA SE TORNA O PRIMEIRO ELEMENTO DA LINHA
    while(no->dir != aux){ //PERCORRENDO A COLUNA
        if(coluna == c){
            break;
        }
        coluna++;
        no = no->dir;
    }

    if(c == no->col){ //SE A COLUNA DO NÓ FOR IGUAL A COLUNA SOLICITADA, RETORNO O NÓ
        return no;
    } else {
        return NULL;
    }

}

Elemento* consulta_matriz_Matricula(Matriz* matriz, int matricula){ // DO TIPO ELEMENTO PARA RETORNAR UM ELEMENTO
    if(matriz == NULL) // TESTE DE CRIAÇÃO DA MATRIZ
        return NULL;
    Elemento* linhaAtual = (*matriz)->baixo; // RECEBE A CABEÇA APOTANDO PARA BAIXO
    Elemento* colunaAtual;

    while (linhaAtual != *matriz) { // PERCORRE LINHA POR LINHA
        colunaAtual = linhaAtual->dir; // RECEBE A LINHA PARA QUE POSSA PERCORRER ELA
        while (colunaAtual != linhaAtual) { // PERCORRE TODA A LINHA COLUNA POR COLUNA
            if(colunaAtual->dados.matricula == matricula) { // CASO ENCONTRE A MATRICULA QUE O USUÁRIO INFORMOU
                return colunaAtual;
            }
            colunaAtual = colunaAtual->dir;
        }
        linhaAtual = linhaAtual->baixo;
    }
    return NULL;
}

int imprime_matriz(Matriz* matriz) {
    if(matriz == NULL) // TESTE DE CRIAÇÃO DA MATRIZ
        return 0;
    Elemento* linhaAtual = (*matriz)->baixo; // RECEBE A CABEÇA APOTANDO PARA BAIXO
    Elemento* colunaAtual;

    while (linhaAtual != *matriz) { // PERCORRE LINHA POR LINHA
        colunaAtual = linhaAtual->dir; // RECEBE A LINHA PARA QUE POSSA PERCORRER ELA
        while (colunaAtual != linhaAtual) { // PERCORRE TODA A LINHA COLUNA POR COLUNA E VAI IMPRIMINDO AS INFORMAÇÕES
            printf("\n\tCoordenada [%d][%d]", linhaAtual->lin, colunaAtual->col);
            printf("\n\tMatricula: %d\n", colunaAtual->dados.matricula);
            printf("\tNome: %s\n", colunaAtual->dados.nome);
            printf("\tNotas: %.2f %.2f %.2f\n", colunaAtual->dados.n1,
                   colunaAtual->dados.n2,
                   colunaAtual->dados.n3);
            printf("\t-------------------------------\n");
            colunaAtual = colunaAtual->dir;
        }
        linhaAtual = linhaAtual->baixo;
    }
    return 0; // CASO A MATRIZ ESTEJA VAZIA
}

int imprime_vizinhos(Matriz* matriz, int lin, int col) {
    if(matriz == NULL) // TESTE DE CRIAÇÃO
        return 0;
    Elemento* linhaAtual = (*matriz)->baixo; // RECEBE A CABEÇA APOTANDO PARA BAIXO
    Elemento* colunaAtual;

    while (linhaAtual != *matriz) { // PERCORRE LINHA POR LINHA
        colunaAtual = linhaAtual->dir; // RECEBE A LINHA PARA QUE POSSA PERCORRER ELA
        while (colunaAtual != linhaAtual) { // PERCORRE TODA A LINHA COLUNA POR COLUNA E VAI IMPRIMINDO AS INFORMAÇÕES
            if(colunaAtual->lin == lin && colunaAtual->col == col) { // VERIFICA SE A COORDENADA INFORMADA PELO USUÁRIO EXISTE
                // VERIFICA SE CADA VIZINHO PARA VER SE EXITEM
                if(colunaAtual->esq->lin > -1 && colunaAtual->esq->col > -1) {
                    printf("\n\tVizinho da esquerda: ");
                    imprime_um_elemento(&colunaAtual->esq);
                } else { printf("\n\tNão tem vizinho há esquerda\n"); }

                if(colunaAtual->cima->lin > -1 && colunaAtual->cima->col > -1) {
                    printf("\n\tVizinho de cima: ");
                    imprime_um_elemento(&colunaAtual->cima);
                } else { printf("\n\tNão tem vizinho há cima\n"); }

                if(colunaAtual->dir->lin > -1 && colunaAtual->dir->col > -1) {
                    printf("\n\tVizinho da direita: ");
                    imprime_um_elemento(&colunaAtual->dir);
                } else { printf("\n\tNão tem vizinho há direita\n"); }

                if(colunaAtual->baixo->lin > -1 && colunaAtual->baixo->col > -1) {
                    printf("\n\tVizinho da baixo: ");
                    imprime_um_elemento(&colunaAtual->baixo);
                } else { printf("\n\tNão tem vizinho há baixo\n"); }

            }
            colunaAtual = colunaAtual->dir;
        }
        linhaAtual = linhaAtual->baixo;
    }
    return 0;
}

void imprime_um_elemento(Matriz* matriz) {
    Elemento* aux = *matriz;
    printf("\n\tCoordenada [%d][%d]", aux->lin, aux->col);
    printf("\n\tMatricula: %d\n", aux->dados.matricula);
    printf("\tNome: %s\n", aux->dados.nome);
    printf("\tNotas: %.2f %.2f %.2f\n", aux->dados.n1,
           aux->dados.n2,
           aux->dados.n3);
    printf("\t-------------------------------\n");
}


