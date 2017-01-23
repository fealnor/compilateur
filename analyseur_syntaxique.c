#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"
#include <stdlib.h>

void E(void)
{
    T();
    E1();
}

void E1(void)
{
    if (uniteCourante == PLUS)
    {
        printf("+");
        uniteCourante = yylex();
        E();
    }
    else return;
}

void T(void)
{
    F();
    T1();
}

void T1(void)
{
    if (uniteCourante == FOIS)
    {
        printf("*");
        uniteCourante = yylex();
        T();
    }
    else return;
}

void F(void)
{
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        printf("(");
        uniteCourante = yylex();
        E();
        if (uniteCourante == PARENTHESE_FERMANTE)
        {
            printf(")");
            return;
        }
        else
        {
            printf("Erreur de syntaxe");
            exit(-1);
        }
    }
    else if (uniteCourante == NOMBRE)
    {
        printf("n");
        uniteCourante = yylex();
        return;
    }
    else
    {
        printf( "Erreur de syntaxe" );
        exit(-1);
    }
}

