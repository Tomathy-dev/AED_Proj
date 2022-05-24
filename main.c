/******************************************************************************
 *
 * File Name: campista.c
 * Author:    Ana Catarina Grilo & Tomás Salgueiro
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "admissivel.h"

int main(int argc, char *argv[])
{
    char *FicheiroIn;

    if (argc < 2 || argc > 2) {
    exit(0);
    }

  /* Abrir ficheiro*/
    FicheiroIn = argv[1];
    Ficheiro(FicheiroIn);

    exit(0);
}
