#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"
#include <stdlib.h>

#define XML 0

char nom[100];
char valeur[100];

void exitProgramme(char* functionName)
{
    printf("Erreur de syntaxe %s", functionName);
    exit(-1);
}

//programme -> optDecVariables listeDecFonctions
void programme(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_optDecVariables_, uniteCourante))
    {
        optDecVariables();
        listeDecFonctions();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//optDecVariables -> listeDecVariables ';' | EPSILON
void optDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_listeDecVariables_, uniteCourante))
    {
        listeDecVariables();

        if( uniteCourante == POINT_VIRGULE)
            uniteCourante = yylex();
        else
            exitProgramme(__FUNCTION__);
    }
    else if (!est_suivant(uniteCourante, _optDecVariables_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeDecVariables -> declarationVariable listeDecVariablesBis
void listeDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_declarationVariable_, uniteCourante))
    {
        declarationVariable();
        listeDecVariablesBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis | EPSILON
void listeDecVariablesBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == VIRGULE)
    {
        uniteCourante = yylex();
        declarationVariable();
        listeDecVariablesBis();
    }
    else if (!est_suivant(uniteCourante, _listeDecVariablesBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//declarationVariable -> ENTIER ID_VAR optTailleTableau
void declarationVariable(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ENTIER)
    {
        nom_token(uniteCourante, nom, valeur);
        affiche_balise_ouvrante(nom, XML);

        affiche_balise_fermante(nom, XML);
        uniteCourante = yylex();
        if (uniteCourante == ID_VAR)
        {
            uniteCourante = yylex();
            optTailleTableau();
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//optTailleTableau -> '[' NOMBRE ']' | EPSILON
void optTailleTableau(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        uniteCourante = yylex();
        if (uniteCourante == NOMBRE)
        {
            uniteCourante = yylex();
            if (uniteCourante == CROCHET_FERMANT)
                uniteCourante = yylex();
            else exitProgramme(__FUNCTION__);
        }
        else exitProgramme(__FUNCTION__);
    }
    else if (!est_suivant(uniteCourante, _optTailleTableau_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
void listeDecFonctions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_declarationFonction_, uniteCourante))
    {
        declarationFonction();
        listeDecFonctions();
    }
    else if (!est_suivant(uniteCourante, _listeDecFonctions_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
void declarationFonction(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ID_FCT)
    {
        uniteCourante = yylex();
        listeParam();
        optDecVariables();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _declarationFonction_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeParam -> '(' optListeDecVariables ')'
void listeParam(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        uniteCourante = yylex();
        optListeDecVariables();
        if (uniteCourante == PARENTHESE_FERMANTE)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//optListeDecVariables -> listeDecVariables | EPSILON
void optListeDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_listeDecVariables_, uniteCourante))
        listeDecVariables();
    else if (!est_suivant(uniteCourante, _optListeDecVariables_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

/*instruction -> instructionAffect
             | instructionBloc
             | instructionSi
             | instructionTantque
             | instructionAppel
             | instructionRetour
             | instructionEcriture
             | instructionVide*/
void instruction(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_instructionAffect_, uniteCourante))
        instructionAffect();
    else if (est_premier(_instructionBloc_, uniteCourante))
        instructionBloc();
    else if (est_premier(_instructionSi_, uniteCourante))
        instructionSi();
    else if (est_premier(_instructionTantque_, uniteCourante))
        instructionTantque();
    else if (est_premier(_instructionAppel_, uniteCourante))
        instructionAppel();
    else if (est_premier(_instructionRetour_, uniteCourante))
        instructionRetour();
    else if (est_premier(_instructionEcriture_, uniteCourante))
        instructionEcriture();
    else if (est_premier(_instructionVide_, uniteCourante))
        instructionVide();
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionAffect -> var '=' expression ';'
void instructionAffect(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_var_, uniteCourante))
    {
        var();
        if (uniteCourante == EGAL)
        {
            uniteCourante = yylex();
            expression();
            if (uniteCourante == POINT_VIRGULE)
                uniteCourante = yylex();
            else exitProgramme(__FUNCTION__);
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionBloc -> '{' listeInstructions '}'
void instructionBloc(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ACCOLADE_OUVRANTE)
    {
        uniteCourante = yylex();
        listeInstructions();
        if (uniteCourante == ACCOLADE_FERMANTE)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeInstructions -> instruction listeInstructions | EPSILON
void listeInstructions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_instruction_, uniteCourante))
    {
        instruction();
        listeInstructions();
    }
    else if (!est_suivant(uniteCourante, _listeInstructions_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionAppel -> appelFct ';'
void instructionAppel(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_appelFct_, uniteCourante))
    {
        appelFct();
        if (uniteCourante == POINT_VIRGULE)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionSi -> SI expression ALORS instructionBloc optSinon
void instructionSi(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == SI)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == ALORS)
        {
            uniteCourante = yylex();
            instructionBloc();
            optSinon();
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//optSinon -> SINON instructionBloc | EPSILON
void optSinon(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == SINON)
    {
        uniteCourante = yylex();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _optSinon_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionTantque -> TANTQUE expression FAIRE instructionBloc
void instructionTantque(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == TANTQUE)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == FAIRE)
        {
            uniteCourante = yylex();
            instructionBloc();
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionRetour -> RETOUR expression ';'
void instructionRetour(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == RETOUR)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == POINT_VIRGULE)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionEcriture -> ECRIRE '(' expression ')' ';'
void instructionEcriture(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ECRIRE)
    {
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            expression();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                uniteCourante = yylex();
                if (uniteCourante == POINT_VIRGULE)
                    uniteCourante = yylex();
                else exitProgramme(__FUNCTION__);
            }
            else exitProgramme(__FUNCTION__);
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//instructionVide -> ';'
void instructionVide(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == POINT_VIRGULE)
        uniteCourante = yylex();
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//expression -> conjonction expressionBis
void expression(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_conjonction_, uniteCourante))
    {
        conjonction();
        expressionBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//expressionBis -> '|' conjonction expressionBis | EPSILON
void expressionBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == OU)
    {
        uniteCourante = yylex();
        conjonction();
        expressionBis();
    }
    else if (!est_suivant(uniteCourante, _expressionBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//conjonction -> comparaison conjonctionBis
void conjonction(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_comparaison_, uniteCourante))
    {
        comparaison();
        conjonctionBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//conjonctionBis -> '&' comparaison conjonctionBis | EPSILON
void conjonctionBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ET)
    {
        uniteCourante = yylex();
        comparaison();
        conjonctionBis();
    }
    else if (!est_suivant(uniteCourante, _conjonctionBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//comparaison -> expArith comparaisonBis
void comparaison(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_expArith_, uniteCourante))
    {
        expArith();
        comparaisonBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

/*comparaisonBis -> '=' expArith comparaisonBis
                | '<' expArith comparaisonBis
                | EPSILON
*/
void comparaisonBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == EGAL || uniteCourante == INFERIEUR)
    {
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//expArith -> terme expArithBis
void expArith(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_terme_, uniteCourante))
    {
        terme();
        expArithBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

/*expArithBis -> '+' terme expArithBis
             | '-' terme expArithBis
             |
*/
void expArithBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == PLUS || uniteCourante == MOINS)
    {
        uniteCourante = yylex();
        terme();
        expArithBis();
    }
    else if (!est_suivant(uniteCourante, _expArithBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//terme -> negation termeBis
void terme(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_negation_, uniteCourante))
    {
        negation();
        termeBis();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

/*termeBis -> '*' negation termeBis
          | '/' negation termeBis
          | EPSILON
*/
void termeBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == FOIS || uniteCourante == DIVISE)
    {
        uniteCourante = yylex();
        negation();
        termeBis();
    }
    else if (!est_suivant(uniteCourante, _termeBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//negation -> '!' negation | facteur
void negation(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == NON)
    {
        uniteCourante = yylex();
        negation();
    }
    else if (est_premier(_facteur_, uniteCourante))
        facteur();
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

/*facteur -> '(' expression ')'
         | NOMBRE
         | appelFct
         | var
         | LIRE '(' ')'
*/
void facteur(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == PARENTHESE_FERMANTE)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else if (uniteCourante == NOMBRE)
        uniteCourante = yylex();
    else if (est_premier(_appelFct_, uniteCourante))
        appelFct();
    else if (est_premier(_var_, uniteCourante))
        var();
    else if (uniteCourante == LIRE)
    {
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            if (uniteCourante == PARENTHESE_FERMANTE)
                uniteCourante = yylex();
            else exitProgramme(__FUNCTION__);
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//var -> ID_VAR optIndice
void var(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ID_VAR)
    {
        uniteCourante = yylex();
        optIndice();
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//optIndice -> '[' expression ']' | EPSILON
void optIndice(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == CROCHET_FERMANT)
            uniteCourante = yylex();
        else exitProgramme(__FUNCTION__);
    }
    else if (!est_suivant(uniteCourante, _optIndice_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//appelFct -> ID_FCT '(' listeExpressions ')'
void appelFct(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == ID_FCT)
    {
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            listeExpressions();
            if (uniteCourante == PARENTHESE_FERMANTE)
                uniteCourante = yylex();
            else exitProgramme(__FUNCTION__);
        }
        else exitProgramme(__FUNCTION__);
    }
    else exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeExpressions -> expression listeExpressionsBis | EPSILON
void listeExpressions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (est_premier(_expression_, uniteCourante))
    {
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//listeExpressionsBis -> ',' expression listeExpressionsBis | EPSILON
void listeExpressionsBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, XML);
    if (uniteCourante == VIRGULE)
    {
        uniteCourante = yylex();
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) exitProgramme(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, XML);
}

//afficheBaliseOuvrante(__FUNCTION__, tracexml)
