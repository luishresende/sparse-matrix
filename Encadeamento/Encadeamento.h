// Arquivo Encadeamento.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

struct elemento{
    struct aluno dados;
    struct elemento *dir;
    struct elemento *esq;
    struct elemento *cima;
    struct elemento *baixo;
    int lin, col;
};
typedef struct elemento Elemento;
typedef struct elemento* Matriz;

void inserir_dados(struct aluno *al);
Matriz* cria_matriz(int lin, int col);
int libera_Matriz(Matriz* matriz);
int quantLinhas_matriz(Matriz* cabeca);
int quantColunas_matriz(Matriz* cabeca);
int insere_matriz_byPos(Matriz* matriz, int l, int c, struct aluno al);
Elemento* consulta_matriz_byPos(Matriz* matriz, int l, int c);
Elemento* consulta_matriz_Matricula(Matriz* matriz, int matricula);
int imprime_matriz(Matriz* matriz);
int imprime_vizinhos(Matriz* matriz, int lin, int col);
void imprime_um_elemento(Matriz* matriz);
