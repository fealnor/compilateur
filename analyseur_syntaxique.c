#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"
#include <stdlib.h>

void exitProgramme()
{
    printf("Erreur de syntaxe");
    exit(-1);
}

//programme -> optDecVariables listeDecFonctions
void programme(void)
{
    if (est_premier(_optDecVariables_, uniteCourante))
    {
        optDecVariables();
        listeDecFonctions();
    }
    else exitProgramme();
}

//optDecVariables -> listeDecVariables ';' | EPSILON
void optDecVariables(void)
{
    if (est_premier(_listeDecFonctions_, uniteCourante))
    {
        listeDecVariables();
        if( uniteCourante ==';')
            uniteCourante = yylex();
        else exitProgramme();
    }
    else if (!est_suivant(uniteCourante, _optDecVariables_) exitProgramme();
}

//listeDecVariables -> declarationVariable listeDecVariablesBis
void listeDecVariables(void)
{
    if (est_premier(_declarationVariable_, uniteCourante))
    {
        declarationVariable();
        listeDecVariablesBis();
    }
    else exitProgramme();
}

//listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis | EPSILON
void listeDecVariablesBis(void)
{
    if (uniteCourante == ',')
    {
        uniteCourante = yylex();
        declarationVariable();
        listeDecVariablesBis();
    }
    else if (!est_suivant(uniteCourante, _listeDecVariablesBis_) exitProgramme();
}

//declarationVariable -> ENTIER ID_VAR optTailleTableau
void declarationVariable(void)
{
    if (uniteCourante == ENTIER)
    {
        uniteCourante = yylex();
        if (uniteCourante == ID_VAR)
        {
            uniteCourante = yylex();
            optTailleTableau();
        }
        else exitProgramme();
    }
    else exitProgramme();
}

//optTailleTableau -> '[' NOMBRE ']' | EPSILON
void optTailleTableau(void)
{
    if (uniteCourante == '[')
    {
        uniteCourante = yylex();
        if (uniteCourante == NOMBRE)
        {
            uniteCourante = yylex();
            if (uniteCourante == ']')
                uniteCourante = yylex();
            else exitProgramme();
        }
        else exitProgramme();
    }
    else if (!est_suivant(uniteCourante, _optTailleTableau_) exitProgramme();
}

//listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
void listeDecFonctions(void)
{
    if (est_premier(_declarationFonction_, uniteCourante))
    {
        declarationFonction();
        listeDecFonctions();
    }
    else if (!est_suivant(uniteCourante, _listeDecFonctions_) exitProgramme();
}

//declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
void declarationFonction(void)
{
    if (uniteCourante == ID_FCT)
    {
        uniteCourante = yylex();
        listeParam();
        optDecVariables();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _declarationFonction_) exitProgramme();
}

//listeParam -> '(' optListeDecVariables ')'
void listeParam(void)
{
    if (uniteCourante == '(')
    {
        uniteCourante = yylex();
        optListeDecVariables();
        if (uniteCourante == ')')
            uniteCourante = yylex();
        else exitProgramme();
    }
    else exitProgramme();
}

//optListeDecVariables -> listeDecVariables | EPSILON
void optListeDecVariables(void)
{
    if (est_premier(_listeDecVariables_, uniteCourante))
        listeDecVariables();
    else if (!est_suivant(uniteCourante, _optListeDecVariables_) exitProgramme();
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
    else exitProgramme();
}

//instructionAffect -> var '=' expression ';'
void instructionAffect(void)
{
    if (est_premier(_var_, uniteCourante))
    {
        var();
        if (uniteCourante == '=')
        {
            uniteCourante = yylex();
            expression();
            if (uniteCourante == ';')
                uniteCourante = yylex();
            else exitProgramme();
        }
        else exitProgramme()
    }
    else exitProgramme();
}

//instructionBloc -> '{' listeInstructions '}'
void instructionBloc(void)
{
    if (uniteCourante == '{')
    {
        uniteCourante = yylex();
        listeInstructions();
        if (uniteCourante == '}')
            uniteCourante = yylex();
        else exitProgramme();
    }
    else exitProgramme();
}

//listeInstructions -> instruction listeInstructions | EPSILON
void listeInstructions(void)
{
    if (est_premier(_instruction_, uniteCourante))
    {
        instruction();
        listeInstructions();
    }
    else if (!est_suivant(uniteCourante, _listeInstructions_) exitProgramme();
}

//instructionAppel -> appelFct ';'
void instructionAppel(void)
{
    if (est_premier(_appelFct_, uniteCourante))
    {
        appelFct();
        if (uniteCourante == ';')
            uniteCourante = yylex();
        else exitProgramme()
    }
    else exitProgramme();
}

//instructionSi -> SI expression ALORS instructionBloc optSinon
void instructionSi(void)
{
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
        else exitProgramme();
    }
    else exitProgramme();
}

//optSinon -> SINON instructionBloc | EPSILON
void optSinon(void)
{
    if (uniteCourante == SINON)
    {
        uniteCourante = yylex();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _optSinon_) exitProgramme();
}

//instructionTantque -> TANTQUE expression FAIRE instructionBloc
void instructionTantque(void)
{
    if (uniteCourante == TANTQUE)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == FAIRE)
        {
            uniteCourante = yylex();
            instructionBloc();
        }
        else exitProgramme();
    }
    else exitProgramme();
}

//instructionRetour -> RETOUR expression ';'
void instructionRetour(void)
{
    if (uniteCourante == RETOUR)
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == ';')
            uniteCourante = yylex();
        else exitProgramme();
    }
    else exitProgramme();
}

//instructionEcriture -> ECRIRE '(' expression ')' ';'
void instructionEcriture(void)
{
    if (uniteCourante == ECRIRE)
    {
        uniteCourante = yylex();
        if (uniteCourante == '(')
        {
            uniteCourante = yylex();
            expression();
            if (uniteCourante == ')')
            {
                uniteCourante = yylex();
                if (uniteCourante == ';')
                    uniteCourante = yylex();
                else exitProgramme();
            }
            else exitProgramme();
        }
        else exitProgramme();
    }
    else exitProgramme();
}

//instructionVide -> ';'
void instructionVide(void)
{
    if (uniteCourante == ';')
        uniteCourante = yylex();
    else exitProgramme();
}

//expression -> conjonction expressionBis
void expression(void)
{
    if (est_premier(_conjonction_, uniteCourante))
    {
        conjonction();
        expressionBis();
    }
    else exitProgramme();
}

//expressionBis -> '|' conjonction expressionBis | EPSILON
void expressionBis(void)
{
    if (uniteCourante == '|')
    {
        uniteCourante = yylex();
        conjonction();
        expressionBis();
    }
    else if (!est_suivant(uniteCourante, _expressionBis_) exitProgramme();
}

//conjonction -> comparaison conjonctionBis
void conjonction(void)
{
    if (est_premier(_comparaison_, uniteCourante))
    {
        comparaison();
        conjonctionBis();
    }
    else exitProgramme();
}

//conjonctionBis -> '&' comparaison conjonctionBis | EPSILON
void conjonctionBis(void)
{
    if (uniteCourante == '&')
    {
        uniteCourante = yylex();
        comparaison();
        conjonctionBis();
    }
    else if (!est_suivant(uniteCourante, _conjonctionBis_) exitProgramme();
}

//comparaison -> expArith comparaisonBis
void comparaison(void)
{
    if (est_premier(_expArith_, uniteCourante))
    {
        expArith();
        comparaisonBis();
    }
    else exitProgramme();
}

/*comparaisonBis -> '=' expArith comparaisonBis
                | '<' expArith comparaisonBis
                | EPSILON
*/
void comparaisonBis(void)
{
    if (uniteCourante == '=' || uniteCourante == '<')
    {
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_) exitProgramme();
}

//expArith -> terme expArithBis
void expArith(void)
{
    if (est_premier(_terme_, uniteCourante))
    {
        terme();
        expArithBis();
    }
    else exitProgramme();
}

/*expArithBis -> '+' terme expArithBis
             | '-' terme expArithBis
             |
*/
void expArithBis(void)
{
    if (uniteCourante == )
    {
        uniteCourante = yylex();
    }
    else if (!est_suivant(uniteCourante, _expArithBis_) exitProgramme();
}

//terme -> negation termeBis
void terme(void)
{
    if (est_premier(_negation_, uniteCourante))
    {
        negation();
        termeBis();
    }
    else exitProgramme();
}

/*termeBis -> '*' negation termeBis
          | '/' negation termeBis
          | EPSILON
*/
void termeBis(void)
{
    if (uniteCourante == '*' || uniteCourante == '/')
    {
        uniteCourante = yylex();
        negation();
        termeBis();
    }
    else if (!est_suivant(uniteCourante, _termeBis_) exitProgramme();
}

//negation -> '!' negation | facteur
void negation(void)
{
    if (uniteCourante == '!')
    {
        uniteCourante = yylex();
        negation();
    }
    else if (est_premier(_facteur_, uniteCourante))
        facteur();
    else exitProgramme();
}

/*facteur -> '(' expression ')'
         | NOMBRE
         | appelFct
         | var
         | LIRE '(' ')'
*/
void facteur(void)
{
    if (uniteCourante == '(')
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == ')')
            uniteCourante = yylex();
        else exitProgramme();
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
        if (uniteCourante == '(')
        {
            uniteCourante = yylex();
            if (uniteCourante == ')')
                uniteCourante = yylex();
            else exitProgramme();
        }
        else exitProgramme();
    }
    else exitProgramme();
}

//var -> ID_VAR optIndice
void var(void)
{
    if (uniteCourante == ID_VAR)
    {
        uniteCourante = yylex();
        optIndice();
    }
    else exitProgramme();
}

//optIndice -> '[' expression ']' | EPSILON
void optIndice(void)
{
    if (uniteCourante == '[')
    {
        uniteCourante = yylex();
        expression();
        if (uniteCourante == ']')
            uniteCourante = yylex();
        else exitProgramme();
    }
    else if (!est_suivant(uniteCourante, _optIndice_) exitProgramme();
}

//appelFct -> ID_FCT '(' listeExpressions ')'
void appelFct(void)
{
    if (uniteCourante == ID_FCT)
    {
        uniteCourante = yylex();
        if (uniteCourante == '(')
        {
            uniteCourante = yylex();
            listeExpressions();
            if (uniteCourante == ')')
                uniteCourante = yylex();
            else exitProgramme();
        }
        else exitProgramme();
    }
    else exitProgramme();
}

//listeExpressions -> expression listeExpressionsBis | EPSILON
void listeExpressions(void)
{
    if (est_premier(_expression_, uniteCourante))
    {
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_) exitProgramme();
}

//listeExpressionsBis -> ',' expression listeExpressionsBis | EPSILON
void listeExpressionsBis(void)
{
    if (uniteCourante == ',')
    {
        uniteCourante = yylex();
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_) exitProgramme();
}

//afficheBaliseOuvrante(__FUNCTION__, tracexml)
