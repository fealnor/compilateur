#include <stdio.h>
#include <stdlib.h>
#include "analyseur_lexical.h"
#include "symboles.h"
#include "analyseur_syntaxique.h"

char yytext[100];
FILE *yyin;

int main(int argc, char **argv) {
    yyin = fopen("C:\\Users\\Loic\\Desktop\\Compilateur\\affect.l.txt", "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", "C:\\Users\\Loic\\Desktop\\Compilateur\\affect.l");
        exit(1);
    }
    uniteCourante = yylex();

    E();
    uniteCourante = yylex();
    if (uniteCourante == FIN)
        printf("GOOD");
    return 0;
}
