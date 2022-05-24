/******************************************************************************
 *
 * File Name: Admissivel.c
 Author:    Ana Catarina Grilo & Tomás Salgueiro
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admissivel.h"

typedef struct _t_Parque {
    int L;
    int C;
    int *Linhas;
    int *Colunas;
    char **Matriz;
} Campismo;

typedef struct _t_Tendas {
    int N;
    int S;
    int E;
    int O;
    int V;
    int Tenda_l0;
    int Tenda_c0;
    int Arvore_l0;
    int Arvore_c0;
} Vect_Tendas;

/** \brief Soma as componentes dos vectores linha/coluna
 *
 * \param dim: dimensão do vetor
 * \param vetor: vector de inteiros das tendas linhas/colunas
 * \param espaco: dimensão linhas/colunas na matriz
 *
 * \return: soma
 *
 */
int Soma_vect(int dim,int *vetor, int espaco){

    int soma=0, i;

    /*verifica se o espaco é par ou impar, porque cada linha/coluna só pode ter metade de tendas em relacao
      dimensão da coluna/linha*/
    if(espaco%2 == 0){
        espaco = espaco/2;
    }else{
        espaco = (espaco/2) + 1;
    }
    for(i=0; i<dim; i++){
        if(vetor[i]<0 || vetor[i]>espaco){
            return -1;
        }
        soma += vetor[i];
    }

    return(soma);
}

/** \brief Compara dois inteiros
 *
 * \param A: inteiro
 * \param B: inteiro
 *
 * \return: 1 se forem iguais se não devolve -1
 *
 */
int Compara(int A, int B){

    if(A == B){
        return (1);
    }else{
        return (-1);
    }
}

/** \brief Verifica o número de árvores chegam para as tendas pedidas
 *
 * \param L/C: número de linhas/colunas
 * \param Tendas: tentas pedidas
 * \param Matriz: Mapa do problema
 * \return: -1 ,se o número de árvores for insuficiente
 * \return: 1 ,menos tendas que arvores, época baixa
 * \return: 2 ,tendas igual a arvores, época alta
 *
 */
int Arv_Sufi(int L, int C, int Tendas, char **Matriz){

    int i, j, soma_Ar=0;

    for(i=0; i<L; i++){
        for(j=0; j<C; j++){
            if(Matriz[i][j] == 'A')
                soma_Ar++;
        }
    }
    if( Tendas > soma_Ar)
        return(-1);
    if(Tendas < soma_Ar)
        return (1);

    return (2);
}

/** \brief Verifica se um dada elemento dos vetores de tendas é nulo
 *
 * \param l0/c0: posição na Matriz (linha/coluna)
 * \param Linhas/Colunas: vetores de tendas
 * \return: 1 se o elemento dos vetores for nulo e 0 se não
 *
 */
int Verifica_Vect(int l0, int c0, int *Linhas, int *Colunas){

    int Tend_Linha, Tend_Coluna;

    Tend_Linha = Linhas[l0];
    Tend_Coluna = Colunas[c0];
    if(Tend_Linha == 0 || Tend_Coluna ==0)
        return (1);

    return (0);
}

/** \brief Verifica se existem árvores adjacentes a uma tenda
 *
 * \param l0/c0: posição na Matriz (linha/coluna)
 * \param L/C: dimensão das Linhas/Colunas
 * \param Matriz: Mapa do problema
 * \return: 1 se não existirem árvores e 0 se existirem
 *
 */
int Verifica_Arv(int l0, int c0, int L, int C, char **Matriz){

    int conta=0, i;

    if(l0 > 0){
        i = l0 - 1;
        if(Matriz[i][c0] == 'A')
            conta++;
    }
    if(l0 < (L-1)){
        i = l0 + 1;
        if(Matriz[i][c0] == 'A')
            conta++;
    }
    if(c0 > 0){
        i = c0 - 1;
        if(Matriz[l0][i] == 'A')
            conta++;
    }
    if(c0 < (C-1)){
        i = c0 + 1;
        if(Matriz[l0][i] == 'A')
            conta++;
    }
    if(conta == 0)
        return (1);

    return (0);
}

/** \brief "Elimina" as arvores que não tem espaço para colocar tendas
 *
 * \param l0/c0: posição na Matriz (linha/coluna)
 * \param L/C: dimensão das Linhas/Colunas
 * \param Matriz: Mapa do problema
 *
 */
void Verifica_Arv_ARV(int l0, int c0, int L, int C, char **Matriz){

    int conta=0, i;

    if(l0 > 0){
        i = l0 - 1;
        if(Matriz[i][c0] == 'A' || Matriz[i][c0] == 'I' || Matriz[i][c0] == 'N')
            conta++;
    }else{
        conta++;
    }
    if(l0 < (L-1)){
        i = l0 + 1;
        if(Matriz[i][c0] == 'A' || Matriz[i][c0] == 'I' || Matriz[i][c0] == 'N')
            conta++;
    }else{
        conta++;
    }
    if(c0 > 0){
        i = c0 - 1;
        if(Matriz[l0][i] == 'A' || Matriz[l0][i] == 'I' || Matriz[l0][i] == 'N')
            conta++;
    }else{
        conta++;
    }
    if(c0 < (C-1)){
        i = c0 + 1;
        if(Matriz[l0][i] == 'A' || Matriz[l0][i] == 'I' || Matriz[l0][i] == 'N')
            conta++;
    }else{
        conta++;
    }

    if(conta == 4)
        Matriz[l0][c0] = 'I';

}

/** \brief Verifica se existem tendas adjacentes a uma tenda
 *
 * \param l0/c0: posição na Matriz (linha/coluna)
 * \param L/C: dimensão das Linhas/Colunas
 * \param Matriz: Mapa do problema
 * \return: 1 se existirem tendas e 0 se não existirem
 *
 */
int Verifica_Tend(int l0, int c0, int L, int C, char **Matriz){

    int i, j;

    if(l0 > 0){
        i = l0 - 1;
        if(Matriz[i][c0] == 'T')
            return (1);
    }
    if(l0 < (L-1)){
        i = l0 + 1;
        if(Matriz[i][c0] == 'T')
            return (1);
    }
    if(c0 > 0){
        i = c0 - 1;
        if(Matriz[l0][i] == 'T')
            return (1);
    }
    if(c0 < (C-1)){
        i = c0 + 1;
        if(Matriz[l0][i] == 'T')
            return (1);
    }
    if(l0 > 0 && c0 > 0){
        i = l0 - 1;
        j =c0 - 1;
        if(Matriz[i][j] == 'T')
            return (1);
    }
    if(l0 <(L-1) && c0 < (C-1)){
        i = l0 + 1;
        j = c0 + 1;
        if(Matriz[i][j] == 'T')
            return (1);
    }
    if(l0 <(L-1) && c0 > 0){
        i = l0 + 1;
        j = c0 - 1;
        if(Matriz[i][j] == 'T')
            return (1);
    }
    if(l0 > 0 && c0 < (C-1)){
        i = l0 - 1;
        j = c0 + 1;
        if(Matriz[i][j] == 'T')
            return (1);
    }
    return (0);
}

/** \brief Conta quantas tendas existem numa linha
 *
 * \param pos0: posição na Matriz (linha)
 * \param dim: dimensão das Linhas, ou seja numero de colunas
 * \param vect: vetor das linhas
 * \param Matriz: Mapa do problema
 * \param flag: verificação do problema B ou C
 * \return: 1 se existirem mais tendas do que o permitido 0 se estiver correto
 *
 */
int tend_VectLinha(int pos0, int dim, int *Vect, char **Matriz){

    int i, soma_tend=0;

    for(i=0; i<dim; i++){
        if(Matriz[pos0][i] == 'T')
            soma_tend++;
    }
    if(soma_tend > Vect[pos0])
        return (1);

    return (0);
}

/** \brief Conta quantas tendas existem numa linha
 *
 * \param pos1: posição na Matriz (coluna)
 * \param dim: dimensão das colunas, ou seja numero de linhas
 * \param vect: vetor das colunas
 * \param Matriz: Mapa do problema
 * \param flag: verificação do problema B ou C
 * \return: 1 se existirem mais tendas do que o permitido 0 se estiver correto
 *
 */
int tend_VectColuna(int pos1, int dim, int *Vect, char **Matriz){

    int i, soma_tend=0;

    for(i=0; i<dim; i++){
        if(Matriz[i][pos1] == 'T')
            soma_tend++;
    }
    if(soma_tend > Vect[pos1])
        return (1);

    return (0);
}

/** \brief Dá uma respota ao problema A
 *
 * \param dados: apontador para estrutura
 * \return: variavel sim, respota ao problema
 *
 */
int ProblemaA(Campismo *dados){

    int soma1=0, soma2=0, sim=0;
    soma1 = Soma_vect(dados->L, dados->Linhas, dados->C);
    if(soma1 == -1){
        return -1;
    }
    soma2 = Soma_vect(dados->C, dados->Colunas, dados->L);
    if(soma2 == -1){
        return -1;
    }
    sim = Compara(soma1, soma2);
    if(sim == 1){
        sim = Arv_Sufi(dados->L, dados->C, soma1, dados->Matriz);
    }
    return sim;
}

/** \brief Dá uma respota ao problema B, para todas as celulas da matriz
 *
 * \param dados: apontador para estrutura
 * \param i, j : posição na matriz
 * \param conta_livre: lugares que provavelmente podem ter tenda
 * \return: conta_livre
 *
 */
int ProblemaB(Campismo *dados, int i, int  j, int conta_livre ){

    int Tenda=0;

    if (Tenda != 1){
        Tenda = Verifica_Vect(i, j, dados->Linhas, dados->Colunas);
        if (Tenda != 1){
            Tenda =tend_VectLinha(i, dados->C, dados->Linhas , dados->Matriz);
            if (Tenda !=1){
                Tenda =tend_VectColuna(j, dados->L, dados->Colunas , dados->Matriz);
                if(Tenda != 1){
                    Tenda = Verifica_Arv(i, j, dados->L, dados->C, dados->Matriz);
                    if (Tenda != 1){
                        Tenda = Verifica_Tend(i, j, dados->L, dados->C, dados->Matriz);
                    }
                }
            }
        }
    }
    if(Tenda ==1){
        dados->Matriz[i][j] = 'N';
        conta_livre--;
    }
    return conta_livre;
}

/** \brief Tenda colocar uma tenda ao pé de uma certa árvore
 *
 * \param dados: apontador para estrutura
 * \param Tendas: apontadaor para vetor de estrutura que guarda arvore, flags dos lugares dessa arvore, e colocação da tenda
 * \param n: numero da arvore em que estamos
 * \param epoca: se estamos em epoca alta ou baixa
 * \param vazio: quantas arvores podem estar em vazio
 * \param conta: quantas arvores estão em vazio num determinado momento -> este parametro é passado por referencia
 * \return: 1: Se conseguiu um lugar(incluindo vazio em epoca baixa) para por um tenda
 * \return: 0: Se não conseguiu um lugar(incluindo vazio em epoca baixa) para por um tenda
 */
int Colocar_Tenda(Campismo *dados, Vect_Tendas *Tendas, int n, int epoca, int vazio, int *conta){

    int i, possivel=0;

    if(Tendas[n].N== 0){
        if(Tendas[n].Arvore_l0 > 0){
            i = Tendas[n].Arvore_l0 - 1;
            if(dados->Matriz[i][Tendas[n].Arvore_c0] == '.'){
                possivel = Verifica_Tend(i, Tendas[n].Arvore_c0, dados->L, dados->C, dados->Matriz);
                if (possivel !=1){
                    dados->Matriz[i][Tendas[n].Arvore_c0] = 'T';
                    possivel = tend_VectLinha(i, dados->C, dados->Linhas , dados->Matriz);}
                if (possivel !=1)
                    possivel = tend_VectColuna(Tendas[n].Arvore_c0, dados->L, dados->Colunas , dados->Matriz);
                if(possivel ==1)
                    dados->Matriz[i][Tendas[n].Arvore_c0] = '.';
                if(possivel == 0){
                    Tendas[n].Tenda_l0 = i;
                    Tendas[n].Tenda_c0 = Tendas[n].Arvore_c0;
                    Tendas[n].N = 1;
                    return 1;
                }
            }
        }
        Tendas[n].N = 1;
    }

    if(Tendas[n].S==0){
        if(Tendas[n].Arvore_l0 < (dados->L-1)){
            i = Tendas[n].Arvore_l0 + 1;
            if(dados->Matriz[i][Tendas[n].Arvore_c0] == '.'){
                possivel = Verifica_Tend(i, Tendas[n].Arvore_c0, dados->L, dados->C, dados->Matriz);
                if (possivel !=1){
                    dados->Matriz[i][Tendas[n].Arvore_c0] = 'T';
                    possivel = tend_VectLinha(i, dados->C, dados->Linhas , dados->Matriz);}
                if (possivel !=1)
                    possivel =tend_VectColuna(Tendas[n].Arvore_c0, dados->L, dados->Colunas , dados->Matriz);
                if(possivel ==1)
                    dados->Matriz[i][Tendas[n].Arvore_c0] = '.';
                if(possivel == 0){
                    Tendas[n].Tenda_l0 = i;
                    Tendas[n].Tenda_c0 = Tendas[n].Arvore_c0;
                    Tendas[n].S = 1;
                    return 1;
                }
            }
        }
        Tendas[n].S = 1;
    }

    if(Tendas[n].O ==0 ){
        if(Tendas[n].Arvore_c0 > 0){
            i = Tendas[n].Arvore_c0 - 1;
            if(dados->Matriz[Tendas[n].Arvore_l0][i] == '.'){
                possivel = Verifica_Tend(Tendas[n].Arvore_l0, i, dados->L, dados->C, dados->Matriz);
                if (possivel !=1){
                    dados->Matriz[Tendas[n].Arvore_l0][i] = 'T';
                    possivel = tend_VectLinha(Tendas[n].Arvore_l0, dados->C, dados->Linhas, dados->Matriz);}
                if (possivel !=1)
                    possivel =tend_VectColuna(i, dados->L, dados->Colunas , dados->Matriz);
                if(possivel ==1)
                    dados->Matriz[Tendas[n].Arvore_l0][i] = '.';
                if(possivel == 0){
                    Tendas[n].Tenda_l0 = Tendas[n].Arvore_l0;
                    Tendas[n].Tenda_c0 = i;
                    Tendas[n].O = 1;
                    return 1;
                }
            }
        }
        Tendas[n].O = 1;
    }

    if(Tendas[n].E == 0){
        if(Tendas[n].Arvore_c0  < (dados->C-1)){
            i = Tendas[n].Arvore_c0 + 1;
            if(dados->Matriz[Tendas[n].Arvore_l0][i] == '.'){
                possivel = Verifica_Tend(Tendas[n].Arvore_l0, i, dados->L, dados->C, dados->Matriz);
                if (possivel !=1){
                    dados->Matriz[Tendas[n].Arvore_l0][i] = 'T';
                    possivel = tend_VectLinha(Tendas[n].Arvore_l0, dados->C, dados->Linhas, dados->Matriz);}
                if (possivel !=1)
                    possivel =tend_VectColuna(i, dados->L, dados->Colunas , dados->Matriz);
                if(possivel ==1)
                    dados->Matriz[Tendas[n].Arvore_l0][i] = '.';
                if(possivel == 0){
                    Tendas[n].Tenda_l0 = Tendas[n].Arvore_l0;
                    Tendas[n].Tenda_c0 = i;
                    Tendas[n].E = 1;
                    return 1;
                }
            }
        }
        Tendas[n].E = 1;
    }
    if( (epoca == 1) && (vazio >= (*conta)) ){
        if(Tendas[n].V == 0){
            (*conta)++;
            if((*conta)>vazio){
                (*conta)--;
                return 0;
            }else{
                Tendas[n].V = 1;
                return 1;
            }

        }
    }
    if(epoca == 1){
        (*conta)--;}
    return 0;
}

/** \brief Dá a resposta se existe solução ou não do mapa, fazendo combinações
 *
 * \param dados: apontador para estrutura
 * \param total_arvores: quantas arvores existem no mapa
 * \param epoca: se estamos em epoca alta ou baixa
 * \param vazio: quantas arvores podem estar em vazio
 * \return: 1: Se Existe uma solução para o mapa
 * \return: -1: Se não existe uma solução para o mapa
 */
int Solucao(Campismo *dados, int total_arvores, int epoca, int vazio){

    int i, j, n=0, triunfante = 1, conta=0;
    Vect_Tendas *Tendas;

    Tendas = (Vect_Tendas*)malloc(total_arvores*sizeof(Vect_Tendas));
    if (Tendas==NULL)
        exit(0);

    for(i=0; i<dados->L; i++){
        for(j=0; j<dados->C; j++){
            if(dados->Matriz[i][j]== 'A'){
                Tendas[n].Arvore_l0 = i;
                Tendas[n].Arvore_c0 = j;
                Tendas[n].N = 0;
                Tendas[n].S = 0;
                Tendas[n].E = 0;
                Tendas[n].O = 0;
                Tendas[n].V = 0;
                n++;
            }
        }
    }
    n = 0;
    while(1){

        triunfante = Colocar_Tenda(dados, Tendas, n, epoca, vazio, &conta);

        if ( (triunfante==0) && (n==0) ){
            free(Tendas);
            return -1;
        }
        if(triunfante == 0){
            if(Tendas[n-1].V != 1 && epoca==1){
                dados->Matriz[Tendas[n-1].Tenda_l0][Tendas[n-1].Tenda_c0] = '.';
            }
            if(epoca==2){
                dados->Matriz[Tendas[n-1].Tenda_l0][Tendas[n-1].Tenda_c0] = '.';
            }
            Tendas[n].N = 0;
            Tendas[n].S = 0;
            Tendas[n].E = 0;
            Tendas[n].O = 0;
            Tendas[n].V = 0;
            n--;
        }
        if (triunfante == 1)
            n++;

        if (n == total_arvores){
            free(Tendas);
            return 1;}
    }
    return 0;
}

/** \brief Dá a resposta se existe solução ou não do mapa, fazendo combinações
 *
 * \param dados: apontador para estrutura
 * \param FicheiroIn: Feicheiro de saída
 *
 */
void resolucao(Campismo *dados, FILE *fpOut){

    int epoca=0, conta_arv=0,soma=0, vazio, existe, conta_livre, flag, i, j;

    conta_livre = dados->L * dados->C;
    epoca = ProblemaA(dados);
    if(epoca == -1){
        fprintf(fpOut,"%d %d %d\n\n", dados->L, dados->C, epoca);
        return;
    }
    for(i=0; i<dados->L; i++){
        for(j=0; j<dados->C; j++){
            flag=0;
            if(dados->Matriz[i][j]== 'A'){
                flag = 1;
                Verifica_Arv_ARV(i, j, dados->L, dados->C, dados->Matriz);
                if(dados->Matriz[i][j]== 'A'){
                conta_livre--;}
                if(dados->Matriz[i][j]== 'I'){
                conta_livre--;}
            }
            if(flag ==0){
                conta_livre = ProblemaB(dados, i, j, conta_livre);
            }
        }
    }
    for(i=0; i<dados->L; i++){
        for(j=0; j<dados->C; j++){
            flag=0;
            if(dados->Matriz[i][j]== 'A'){
                conta_arv++;
                Verifica_Arv_ARV(i, j, dados->L, dados->C, dados->Matriz);
                if(dados->Matriz[i][j]== 'I'){
                conta_arv--;}
            }
        }
    }
    soma = Soma_vect(dados->L, dados->Linhas, dados->C);
    if(conta_livre < soma){
        fprintf(fpOut,"%d %d -1\n\n", dados->L, dados->C);
        return;
    }

    vazio = conta_arv - soma;
    if(vazio<0){ // as arvores que tem espacos possiseis nao chegam para o numero de tendas pedidas!!!
        fprintf(fpOut,"%d %d -1\n\n", dados->L, dados->C);
        return;
    }
    existe = Solucao(dados, conta_arv, epoca, vazio);

    if (existe == 1){
        for(i=0; i<dados->L; i++){
            for(j=0; j<dados->C; j++){
                    if(dados->Matriz[i][j]== 'N'){
                        dados->Matriz[i][j] = '.';
                    }
                    if(dados->Matriz[i][j]== 'I'){
                        dados->Matriz[i][j] = 'A';
                    }
            }
        }
        fprintf(fpOut,"%d %d %d\n", dados->L, dados->C, existe);
        for(i=0; i<dados->L; i++){
            fprintf(fpOut,"%s\n", dados->Matriz[i]);
        }
        fprintf(fpOut,"\n");
    }else{
        fprintf(fpOut,"%d %d %d\n\n", dados->L, dados->C, existe);
        }


}

/** \brief Liberta a estrutura
 *
 * \param dados: apontador para a estrutura
 *
 */
Campismo *Liberta(Campismo *dados){

    int i;

    for(i=0; i<dados->L; i++){
        free(dados->Matriz[i]);
    }
    free(dados->Matriz);
    free(dados->Linhas);
    free(dados->Colunas);
    return dados;
}

/** \brief le ficheiro
 *
 * \param FicheiroIn: Feicheiro de leitura
 *
 */
void Ficheiro(char *FicheiroIn){

    int i, dimensao, soma1, soma2, flag=1, flag0_res=0;
    char Out[] = ".tents";
    char *FicheiroOut, *String_lixo;
    Campismo *dados;
    FILE *fp, *fpOut;

    fp = fopen(FicheiroIn, "r");
    if (fp == (FILE*) NULL) {
        exit(0);
    }
    dimensao = strlen(FicheiroIn);
    FicheiroIn[dimensao-5]='\0';

    FicheiroOut =(char*)malloc((strlen(FicheiroIn)+strlen(Out)+1)*sizeof(char));
    if(FicheiroOut == NULL){
        exit(0);
    }
    strcpy(FicheiroOut, FicheiroIn);
    strcat(FicheiroOut, Out);

    fpOut = fopen (FicheiroOut, "w");
    if(fpOut == NULL) {
        exit(0);
    }
    dados = (Campismo*)malloc(1*sizeof(Campismo));
    if (dados==NULL){
            exit(0);
    }
    while (fscanf(fp," %d",&dados->L) != EOF){

        if(fscanf(fp, " %d", &dados->C) == 0)
            exit(0);

        dados->Linhas = (int*)malloc(dados->L*sizeof(int));
        dados->Colunas = (int*)malloc(dados->C*sizeof(int));
        for(i=0; i<(dados->L); i++){
            if(fscanf(fp, " %d", &dados->Linhas[i]) ==0){
                exit(0);}
        }
        for(i=0; i<(dados->C); i++){
            if(fscanf(fp, " %d", &dados->Colunas[i]) ==0){
                exit(0);}
        }

        soma1 = Soma_vect(dados->L, dados->Linhas, dados->C);
        soma2 = Soma_vect(dados->C, dados->Colunas, dados->L);
        if( soma1==-1 || soma2==-1){
            flag = -1;
        }
        if(flag!=-1){
            flag = Compara(soma1, soma2);
            if(flag == 1 && soma1 == 0){
                flag0_res = 1;
                flag = -1;
            }

        }
        if(flag == 1){
            dados->Matriz = (char**)malloc((dados->L)*sizeof(char*));
            for(i=0; i<(dados->L); i++){
                dados->Matriz[i] = (char*)malloc(((dados->C)+1)*sizeof(char));
                if(fscanf(fp, " %s", dados->Matriz[i])==0)
                    exit(0);
            }
            resolucao(dados,fpOut);
            dados = Liberta(dados);
        }else{
            String_lixo = (char*)malloc((dados->C +1)*sizeof(char));
            if(flag0_res==1){
                fprintf(fpOut,"%d %d 1\n", dados->L, dados->C);}
            for(i=0; i<(dados->L); i++){
                if(fscanf(fp, " %s", String_lixo)==0)
                        exit(0);
                if(flag0_res == 1){
                    fprintf(fpOut,"%s\n", String_lixo);
                    if(i == dados->L-1){
                        fprintf(fpOut,"\n");
                    }
                }
            }
            free(String_lixo);
            free(dados->Colunas);
            free(dados->Linhas);
            if(flag0_res!=1){
                fprintf(fpOut,"%d %d -1\n\n", dados->L, dados->C);}

        }
        flag=1;
        flag0_res=0;
    }
    fclose(fp);
    fclose(fpOut);
    free(FicheiroOut);
    free(dados);
}
