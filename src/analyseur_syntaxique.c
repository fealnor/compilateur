#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"

#define PRINT_SYNTAXE 1
#define PRINT_LEXIQUE 1



void affiche_lexique ()
{
    char nom[100];
    char valeur[100];
    nom_token(uniteCourante, nom, valeur);
    affiche_element(nom, valeur, PRINT_LEXIQUE);
}

//programme -> optDecVariables listeDecFonctions
void programme(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_optDecVariables_, uniteCourante) ||
        est_suivant(uniteCourante, _optDecVariables_))
    {
        optDecVariables();
        listeDecFonctions();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//optDecVariables -> listeDecVariables ';' | EPSILON
void optDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_listeDecVariables_, uniteCourante))
    {
        listeDecVariables();

        if( uniteCourante == POINT_VIRGULE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else
            erreur("Manque un point virgule");
    }
    else if (!est_suivant(uniteCourante, _optDecVariables_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeDecVariables -> declarationVariable listeDecVariablesBis
void listeDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_declarationVariable_, uniteCourante))
    {
        declarationVariable();
        listeDecVariablesBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis | EPSILON
void listeDecVariablesBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        declarationVariable();
        listeDecVariablesBis();
    }
    else if (!est_suivant(uniteCourante, _listeDecVariablesBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//declarationVariable -> ENTIER ID_VAR optTailleTableau
void declarationVariable(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ENTIER)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == ID_VAR)
        {
            affiche_lexique();
            uniteCourante = yylex();
            optTailleTableau();
        }
        else erreur("Manque un nom de variable");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//optTailleTableau -> '[' NOMBRE ']' | EPSILON
void optTailleTableau(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == NOMBRE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            if (uniteCourante == CROCHET_FERMANT)
            {
                affiche_lexique();
                uniteCourante = yylex();
            }
            else erreur("Manque un crochet fermant");
        }
        else erreur("Manque un nombre");
    }
    else if (!est_suivant(uniteCourante, _optTailleTableau_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
void listeDecFonctions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_declarationFonction_, uniteCourante))
    {
        declarationFonction();
        listeDecFonctions();
    }
    else if (!est_suivant(uniteCourante, _listeDecFonctions_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
void declarationFonction(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_FCT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        listeParam();
        optDecVariables();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _declarationFonction_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeParam -> '(' optListeDecVariables ')'
void listeParam(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        optListeDecVariables();
        if (uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque une parenthese fermante");
    }
    else erreur("Manque une parenthese ouvrante");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//optListeDecVariables -> listeDecVariables | EPSILON
void optListeDecVariables(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_listeDecVariables_, uniteCourante))
        listeDecVariables();
    else if (!est_suivant(uniteCourante, _optListeDecVariables_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
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
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
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
    else if (est_premier(_instructionFaire_, uniteCourante))
        instructionFaire();
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionAffect -> var '=' expression ';'
void instructionAffect(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_var_, uniteCourante))
    {
        var();
        if (uniteCourante == EGAL)
        {
            affiche_lexique();
            uniteCourante = yylex();
            expression();
            if (uniteCourante == POINT_VIRGULE)
            {
                affiche_lexique();
                uniteCourante = yylex();
            }

            else erreur("Manque un point virgule");
        }
        else erreur("Manque le signe egal");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionBloc -> '{' listeInstructions '}'
void instructionBloc(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ACCOLADE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        listeInstructions();
        if (uniteCourante == ACCOLADE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque une accolade fermante");
    }
    else erreur("Manque une accolade ouvrante");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeInstructions -> instruction listeInstructions | EPSILON
void listeInstructions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_instruction_, uniteCourante))
    {
        instruction();
        listeInstructions();
    }
    else if (!est_suivant(uniteCourante, _listeInstructions_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionAppel -> appelFct ';'
void instructionAppel(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_appelFct_, uniteCourante))
    {
        appelFct();
        if (uniteCourante == POINT_VIRGULE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque un point virgule");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionSi -> SI expression ALORS instructionBloc optSinon
void instructionSi(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == SI)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        if (uniteCourante == ALORS)
        {
            affiche_lexique();
            uniteCourante = yylex();
            instructionBloc();
            optSinon();
        }
        else erreur("Manque le mot cle : alors");
    }
    else erreur("Manque le mot cle : si");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//optSinon -> SINON instructionBloc | EPSILON
void optSinon(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == SINON)
    {
        affiche_lexique();
        uniteCourante = yylex();
        instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _optSinon_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionTantque -> TANTQUE expression FAIRE instructionBloc
void instructionTantque(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == TANTQUE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        if (uniteCourante == FAIRE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            instructionBloc();
        }
        else erreur("Manque le mot cle : faire");
    }
    else erreur("Manque le mot cle tantque");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionRetour -> RETOUR expression ';'
void instructionRetour(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == RETOUR)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        if (uniteCourante == POINT_VIRGULE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque un point virgule");
    }
    else erreur("Manque le mot cle : retour");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionEcriture -> ECRIRE '(' expression ')' ';'
void instructionEcriture(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ECRIRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            expression();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_lexique();
                uniteCourante = yylex();
                if (uniteCourante == POINT_VIRGULE)
                {
                    affiche_lexique();
                    uniteCourante = yylex();
                }
                else erreur("Manque un point virgule");
            }
            else erreur("Manque une parenthese fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur("Manque le mot cle ecrire");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//instructionVide -> ';'
void instructionVide(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == POINT_VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
    }
    else erreur("Manque un point virgule");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//expression -> conjonction expressionBis
void expression(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_conjonction_, uniteCourante))
    {
        conjonction();
        expressionBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//expressionBis -> '|' conjonction expressionBis | EPSILON
void expressionBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == OU)
    {
        affiche_lexique();
        uniteCourante = yylex();
        conjonction();
        expressionBis();
    }
    else if (!est_suivant(uniteCourante, _expressionBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//conjonction -> comparaison conjonctionBis
void conjonction(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_comparaison_, uniteCourante))
    {
        comparaison();
        conjonctionBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//conjonctionBis -> '&' comparaison conjonctionBis | EPSILON
void conjonctionBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ET)
    {
        affiche_lexique();
        uniteCourante = yylex();
        comparaison();
        conjonctionBis();
    }
    else if (!est_suivant(uniteCourante, _conjonctionBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//comparaison -> expArith comparaisonBis
void comparaison(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_expArith_, uniteCourante))
    {
        expArith();
        comparaisonBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

/*comparaisonBis -> '=' expArith comparaisonBis
                | '<' expArith comparaisonBis
                | EPSILON
*/
void comparaisonBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == EGAL || uniteCourante == INFERIEUR)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//expArith -> terme expArithBis
void expArith(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_terme_, uniteCourante))
    {
        terme();
        expArithBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

/*expArithBis -> '+' terme expArithBis
             | '-' terme expArithBis
             |
*/
void expArithBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PLUS || uniteCourante == MOINS)
    {
        affiche_lexique();
        uniteCourante = yylex();
        terme();
        expArithBis();
    }
    else if (!est_suivant(uniteCourante, _expArithBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//terme -> negation termeBis
void terme(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_negation_, uniteCourante))
    {
        negation();
        termeBis();
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

/*termeBis -> '*' negation termeBis
          | '/' negation termeBis
          | EPSILON
*/
void termeBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == FOIS || uniteCourante == DIVISE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        negation();
        termeBis();
    }
    else if (!est_suivant(uniteCourante, _termeBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//negation -> '!' negation | facteur
void negation(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == NON)
    {
        affiche_lexique();
        uniteCourante = yylex();
        negation();
    }
    else if (est_premier(_facteur_, uniteCourante))
        facteur();
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

/*facteur -> '(' expression ')'
         | NOMBRE
         | appelFct
         | var
         | LIRE '(' ')'
*/
void facteur(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        if (uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque une parenthese fermante");
    }
    else if (uniteCourante == NOMBRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
    }

    else if (est_premier(_appelFct_, uniteCourante))
        appelFct();
    else if (est_premier(_var_, uniteCourante))
        var();
    else if (uniteCourante == LIRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_lexique();
                uniteCourante = yylex();
            }

            else erreur("Manque une parenthese fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//var -> ID_VAR optIndice
void var(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_VAR)
    {
        affiche_lexique();
        uniteCourante = yylex();
        optIndice();
    }
    else erreur("Manque le nom d'une variable");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//optIndice -> '[' expression ']' | EPSILON
void optIndice(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        if (uniteCourante == CROCHET_FERMANT)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque un crochet fermant");
    }
    else if (!est_suivant(uniteCourante, _optIndice_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//appelFct -> ID_FCT '(' listeExpressions ')'
void appelFct(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_FCT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            listeExpressions();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_lexique();
                uniteCourante = yylex();
            }
            else erreur("Manque une parenthse fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur("Manque le nom d'une fonction");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeExpressions -> expression listeExpressionsBis | EPSILON
void listeExpressions(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_expression_, uniteCourante))
    {
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

//listeExpressionsBis -> ',' expression listeExpressionsBis | EPSILON
void listeExpressionsBis(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        expression();
        listeExpressionsBis();
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}

void instructionFaire(void)
{
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == FAIRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        instructionBloc();
        if (uniteCourante == TANTQUE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            expression();
            if (uniteCourante == POINT_VIRGULE)
            {
                affiche_lexique();
                uniteCourante = yylex();
            }
            else erreur("Manque un point virgule");
        }
        else erreur("Manque un tant que");
    }
    else erreur("Manque un faire");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
}
