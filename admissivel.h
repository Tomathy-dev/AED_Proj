/******************************************************************************
 *
 * File Name: Admissivel.c
 Author:    Ana Catarina Grilo & Tomás Salgueiro
 *
 * NAME
 *     Admissivel.h - biblioteca de implementação para os testes de admissibilidade
 *
 *****************************************************************************/

#ifndef _ADMISSIVEL_H

#define _ADMISSIVEL_H

#include <stdio.h>

#include <stdlib.h>

typedef struct _t_Parque Campismo;

typedef struct _t_Tendas Vect_Tendas;

int Soma_vect(int, int*, int);

int Compara(int, int);

int Arv_Sufi(int, int, int, char**);

int Verifica_Vect(int, int, int*, int*);

int Verifica_Arv(int, int, int, int, char**);

void Verifica_Arv_ARV(int, int, int, int, char**);

int Verifica_Tend(int, int, int, int, char**);

int tend_VectLinha(int, int, int*, char**);

int tend_VectColuna(int, int, int*, char**);

int Encontra_tenda(Campismo*);

int ProblemaA(Campismo*);

int ProblemaB(Campismo*, int, int, int);

int Colocar_Tenda(Campismo*, Vect_Tendas*, int, int, int, int*);

int Solucao(Campismo*, int, int, int);

void resolucao(Campismo*, FILE*);

void Atribuicao(int, int, int, Campismo*);

int ProblemaC(Campismo*);

void Variante(Campismo*, FILE*);

Campismo *Liberta(Campismo*);

void Ficheiro(char*);

#endif
