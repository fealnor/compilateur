#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"

#define PRINT_SYNTAXE 0
#define PRINT_LEXIQUE 0
#define PRINT_ABSTRAIT 0

void affiche_lexique ()
{
    char nom[100];
    char valeur[100];
    nom_token(uniteCourante, nom, valeur);
    affiche_element(nom, valeur, PRINT_LEXIQUE);
}

char* getValeur()
{
    char nom[100];
    char valeur[100];
    nom_token(uniteCourante, nom, valeur);
    return valeur;
}

//programme -> optDecVariables listeDecFonctions
n_prog* programme(void)
{
    n_prog* $$ = NULL;
    n_l_dec* $1 = NULL;
    n_l_dec* $2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_optDecVariables_, uniteCourante) ||
        est_suivant(uniteCourante, _optDecVariables_))
    {
        $1 = optDecVariables();
        $2 = listeDecFonctions();
        $$ = cree_n_prog($1, $2);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//optDecVariables -> listeDecVariables ';' | EPSILON
n_l_dec* optDecVariables(void)
{
    n_l_dec* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_listeDecVariables_, uniteCourante))
    {
        $$ = listeDecVariables();
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
    return $$;
}

//listeDecVariables -> declarationVariable listeDecVariablesBis
n_l_dec* listeDecVariables(void)
{
    n_l_dec* $$ = NULL;
    n_dec* $1 = NULL;
    n_l_dec* $2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_declarationVariable_, uniteCourante))
    {
        $1 = declarationVariable();
        $2 = listeDecVariablesBis();
        $$ = cree_n_l_dec($1, $2);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis | EPSILON
n_l_dec* listeDecVariablesBis(void)
{
    n_l_dec* $$ = NULL;
    n_dec* $2 = NULL;
    n_l_dec* $3 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = declarationVariable();
        $3 = listeDecVariablesBis();
        $$ = cree_n_l_dec($2, $3);
    }
    else if (!est_suivant(uniteCourante, _listeDecVariablesBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//declarationVariable -> ENTIER ID_VAR optTailleTableau
n_dec* declarationVariable(void)
{
    n_dec* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    int taille = -1;
    if (uniteCourante == ENTIER)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == ID_VAR)
        {
            affiche_lexique();
            char *v = malloc(100);
            strcpy(v, getValeur());
            uniteCourante = yylex();
            taille = optTailleTableau();
            if (taille < 0)
                $$ = cree_n_dec_var(v);
            else
                $$ = cree_n_dec_tab(v, taille);
        }
        else erreur("Manque un nom de variable");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//optTailleTableau -> '[' NOMBRE ']' | EPSILON
int optTailleTableau(void)
{
    int taille = -1;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == NOMBRE)
        {
            affiche_lexique();
            char *v = malloc(100);
            strcpy(v, getValeur());
            taille = atoi(v);
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
    return taille;
}

//listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
n_l_dec* listeDecFonctions(void)
{
    n_l_dec* $$ = NULL;
    n_dec* $1 = NULL;
    n_l_dec* $2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_declarationFonction_, uniteCourante))
    {
        $1 = declarationFonction();
        $2 = listeDecFonctions();
        $$ = cree_n_l_dec($1, $2);
    }
    else if (!est_suivant(uniteCourante, _listeDecFonctions_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
n_dec* declarationFonction(void)
{
    n_dec* $$ = NULL;
    n_l_dec* $2 = NULL;
    n_l_dec* $3 = NULL;
    n_instr* $4 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_FCT)
    {
        affiche_lexique();
        char *v = malloc(100);
        strcpy(v, getValeur());
        uniteCourante = yylex();
        $2 = listeParam();
        $3 = optDecVariables();
        $4 = instructionBloc();
        $$ = cree_n_dec_fonc(v, $2, $3, $4);
    }
    else if (!est_suivant(uniteCourante, _declarationFonction_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//listeParam -> '(' optListeDecVariables ')'
n_l_dec* listeParam(void)
{
    n_l_dec* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = optListeDecVariables();
        if (uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque une parenthese fermante");
    }
    else erreur("Manque une parenthese ouvrante");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//optListeDecVariables -> listeDecVariables | EPSILON
n_l_dec* optListeDecVariables(void)
{
    n_l_dec* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_listeDecVariables_, uniteCourante))
        $$ = listeDecVariables();
    else if (!est_suivant(uniteCourante, _optListeDecVariables_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

/*instruction -> instructionAffect
             | instructionBloc
             | instructionSi
             | instructionTantque
             | instructionAppel
             | instructionRetour
             | instructionEcriture
             | instructionVide*/
n_instr* instruction(void)
{
    n_instr* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_instructionAffect_, uniteCourante))
        $$ = instructionAffect();
    else if (est_premier(_instructionBloc_, uniteCourante))
        $$ = instructionBloc();
    else if (est_premier(_instructionSi_, uniteCourante))
        $$ = instructionSi();
    else if (est_premier(_instructionTantque_, uniteCourante))
        $$ = instructionTantque();
    else if (est_premier(_instructionAppel_, uniteCourante))
        $$ = instructionAppel();
    else if (est_premier(_instructionRetour_, uniteCourante))
        $$ = instructionRetour();
    else if (est_premier(_instructionEcriture_, uniteCourante))
        $$ = instructionEcriture();
    else if (est_premier(_instructionVide_, uniteCourante))
        $$ = instructionVide();
    else if (est_premier(_instructionFaire_, uniteCourante))
        $$ = instructionFaire();
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionAffect -> var '=' expression ';'
n_instr* instructionAffect(void)
{
    n_instr* $$ = NULL;
    n_var* $1 = NULL;
    n_exp* $3 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_var_, uniteCourante))
    {
        $1 = var();
        if (uniteCourante == EGAL)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $3 = expression();
            if (uniteCourante == POINT_VIRGULE)
            {
                affiche_lexique();
                uniteCourante = yylex();
                $$ = cree_n_instr_affect($1, $3);
            }

            else erreur("Manque un point virgule");
        }
        else erreur("Manque le signe egal");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionBloc -> '{' listeInstructions '}'
n_instr* instructionBloc(void)
{
    n_l_instr* $2 = NULL;
    n_instr* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ACCOLADE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = listeInstructions();
        if (uniteCourante == ACCOLADE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $$ = cree_n_instr_bloc($2);
        }
        else erreur("Manque une accolade fermante");
    }
    else erreur("Manque une accolade ouvrante");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//listeInstructions -> instruction listeInstructions | EPSILON
n_l_instr* listeInstructions(void)
{
    n_l_instr* $$ = NULL;
    n_instr* $1 = NULL;
    n_l_instr* $2 = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_instruction_, uniteCourante))
    {
        $1 = instruction();
        $2 = listeInstructions();
        $$ = cree_n_l_instr($1, $2);
    }
    else if (!est_suivant(uniteCourante, _listeInstructions_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionAppel -> appelFct ';'
n_instr* instructionAppel(void)
{
    n_instr* $$ = NULL;
    n_appel* $1 = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_appelFct_, uniteCourante))
    {
        $1 = appelFct();
        if (uniteCourante == POINT_VIRGULE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $$ = cree_n_instr_appel($1);
        }
        else erreur("Manque un point virgule");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionSi -> SI expression ALORS instructionBloc optSinon
n_instr* instructionSi(void)
{
    n_instr* $$ = NULL;
    n_exp* $2 = NULL;
    n_instr* $4 = NULL;
    n_instr* $5 = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == SI)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expression();
        if (uniteCourante == ALORS)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $4 = instructionBloc();
            $5 = optSinon();
            $$ = cree_n_instr_si($2, $4, $5);
        }
        else erreur("Manque le mot cle : alors");
    }
    else erreur("Manque le mot cle : si");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//optSinon -> SINON instructionBloc | EPSILON
n_instr* optSinon(void)
{
    n_instr* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == SINON)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = instructionBloc();
    }
    else if (!est_suivant(uniteCourante, _optSinon_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionTantque -> TANTQUE expression FAIRE instructionBloc
n_instr* instructionTantque(void)
{
    n_instr* $$ = NULL;
    n_exp* $2 = NULL;
    n_instr* $4 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == TANTQUE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expression();
        if (uniteCourante == FAIRE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $4 = instructionBloc();
            $$ = cree_n_instr_tantque($2, $4);
        }
        else erreur("Manque le mot cle : faire");
    }
    else erreur("Manque le mot cle tantque");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionRetour -> RETOUR expression ';'
n_instr* instructionRetour(void)
{
    n_instr* $$ = NULL;
    n_exp* $2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == RETOUR)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expression();
        if (uniteCourante == POINT_VIRGULE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $$ = cree_n_instr_retour($2);
        }
        else erreur("Manque un point virgule");
    }
    else erreur("Manque le mot cle : retour");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionEcriture -> ECRIRE '(' expression ')' ';'
n_instr* instructionEcriture(void)
{
    n_instr* $$ = NULL;
    n_exp* $3 = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ECRIRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $3 = expression();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_lexique();
                uniteCourante = yylex();
                if (uniteCourante == POINT_VIRGULE)
                {
                    affiche_lexique();
                    uniteCourante = yylex();
                    $$ = cree_n_instr_ecrire($3);
                }
                else erreur("Manque un point virgule");
            }
            else erreur("Manque une parenthese fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur("Manque le mot cle ecrire");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//instructionVide -> ';'
n_instr* instructionVide(void)
{
    n_instr* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == POINT_VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = cree_n_instr_vide();
    }
    else erreur("Manque un point virgule");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//expression -> conjonction expressionBis
n_exp* expression(void)
{
    n_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_conjonction_, uniteCourante))
    {
        $1 = conjonction();
        $$ = expressionBis($1);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//expressionBis -> '|' conjonction expressionBis | EPSILON
n_exp* expressionBis(n_exp* herite)
{
    n_exp* $$ = NULL;
    n_exp* $2 = NULL;
    n_exp* herite_fils = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == OU)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = conjonction();
        herite_fils = cree_n_exp_op(ou, herite, $2);
        $$ = expressionBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _expressionBis_))
        $$ = herite;
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//conjonction -> comparaison conjonctionBis
n_exp* conjonction(void)
{
    n_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_comparaison_, uniteCourante))
    {
        $1 = comparaison();
        $$ = conjonctionBis($1);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//conjonctionBis -> '&' comparaison conjonctionBis | EPSILON
n_exp* conjonctionBis(n_exp* herite)
{
    n_exp* $$ = NULL;
    n_exp* $2 = NULL;
    n_exp* herite_fils = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ET)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = comparaison();
        herite_fils = cree_n_exp_op(et, herite, $2);
        $$ = conjonctionBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _conjonctionBis_))
        $$ = herite;
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//comparaison -> expArith comparaisonBis
n_exp* comparaison(void)
{
    n_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_expArith_, uniteCourante))
    {
        $1 = expArith();
        $$ = comparaisonBis($1);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

/*comparaisonBis -> '=' expArith comparaisonBis
                | '<' expArith comparaisonBis
                | EPSILON
*/
n_exp* comparaisonBis(n_exp* herite)
{
    n_exp* $$ = NULL;
    n_exp* $2 = NULL;
    n_exp* herite_fils = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == EGAL)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expArith();
        herite_fils = cree_n_exp_op(egal, herite, $2);
        $$ = comparaisonBis(herite_fils);
    }
    else if (uniteCourante == INFERIEUR)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expArith();
        herite_fils = cree_n_exp_op(inf, herite, $2);
        $$ = comparaisonBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _comparaisonBis_))
        $$ = herite;
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//expArith -> terme expArithBis
n_exp* expArith(void)
{
    n_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_terme_, uniteCourante))
    {
        $1 = terme();
        $$ = expArithBis($1);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

/*expArithBis -> '+' terme expArithBis
             | '-' terme expArithBis
             |
*/
n_exp* expArithBis(n_exp* herite)
{
    n_exp* $$ = NULL;
    n_exp* $2 = NULL;
    n_exp* herite_fils = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PLUS)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = terme();
        herite_fils = cree_n_exp_op(plus, herite, $2);
        $$ = expArithBis(herite_fils);
    }
    else if (uniteCourante == MOINS)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = terme();
        herite_fils = cree_n_exp_op(moins, herite, $2);
        $$ = expArithBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _expArithBis_))
        $$ = herite;
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//terme -> negation termeBis
n_exp* terme(void)
{
    n_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_negation_, uniteCourante))
    {
        $1 = negation();
        $$ = termeBis($1);
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

/*termeBis -> '*' negation termeBis
          | '/' negation termeBis
          | EPSILON
*/
n_exp* termeBis(n_exp *herite)
{
    n_exp* $2;
    n_exp* $$;
    n_exp* herite_fils;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == FOIS)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = negation();
        herite_fils = cree_n_exp_op(fois, herite, $2);
        $$ = termeBis(herite_fils);
    }
    else if (uniteCourante == DIVISE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = negation();
        herite_fils = cree_n_exp_op(divise, herite, $2);
        $$ = termeBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _termeBis_))
        $$ = herite;
    else  erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//negation -> '!' negation | facteur
n_exp* negation(void) ///TODO
{
    n_exp* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == NON)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = negation();
        $$ = cree_n_exp_op(non, $$, NULL);
    }
    else if (est_premier(_facteur_, uniteCourante))
        $$ = facteur();
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

/*facteur -> '(' expression ')'
         | NOMBRE
         | appelFct
         | var
         | LIRE '(' ')'
*/
n_exp* facteur(void)
{
    n_exp* $$ = NULL;
    n_appel* $1 = NULL;
    n_var* $2 = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = expression();
        if (uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque une parenthese fermante");
    }
    else if (uniteCourante == NOMBRE)
    {
        char* v = malloc(100);
        strcpy(v, getValeur());
        affiche_lexique();
        uniteCourante = yylex();
        $$ = cree_n_exp_entier( atoi(v));
    }

    else if (est_premier(_appelFct_, uniteCourante))
    {
        $1 = appelFct();
        $$ = cree_n_exp_appel($1);
    }
    else if (est_premier(_var_, uniteCourante))
    {
        $2 = var();
        $$ = cree_n_exp_var($2);
    }
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
                $$ = cree_n_exp_lire();
            }

            else erreur("Manque une parenthese fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//var -> ID_VAR optIndice
n_var* var(void)
{
    n_var* $$ = NULL;
    n_exp* $2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_VAR)
    {
        affiche_lexique();
        char *v = malloc(100);
        strcpy(v, getValeur());
        uniteCourante = yylex();
        $2 = optIndice();

        if ($2) ///TODO
            $$ = cree_n_var_indicee(v, $2);
        else
            $$ = cree_n_var_simple(v);
    }
    else erreur("Manque le nom d'une variable");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//optIndice -> '[' expression ']' | EPSILON
n_exp* optIndice(void)
{
    n_exp* $$ = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == CROCHET_OUVRANT)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $$ = expression();
        if (uniteCourante == CROCHET_FERMANT)
        {
            affiche_lexique();
            uniteCourante = yylex();
        }
        else erreur("Manque un crochet fermant");
    }
    else if (!est_suivant(uniteCourante, _optIndice_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//appelFct -> ID_FCT '(' listeExpressions ')'
n_appel* appelFct(void)
{
    n_appel* $$ = NULL;
    n_l_exp* $3 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == ID_FCT)
    {
        affiche_lexique();
        char *v = malloc(100);
        strcpy(v, getValeur());
        uniteCourante = yylex();
        if (uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $3 = listeExpressions();
            if (uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_lexique();
                uniteCourante = yylex();
                $$ =  cree_n_appel(v, $3);
            }
            else erreur("Manque une parenthse fermante");
        }
        else erreur("Manque une parenthese ouvrante");
    }
    else erreur("Manque le nom d'une fonction");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//listeExpressions -> expression listeExpressionsBis | EPSILON
n_l_exp* listeExpressions(void)
{
    n_l_exp* $$ = NULL;
    n_exp* $1 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (est_premier(_expression_, uniteCourante))
    {
        $1 = expression();
        $$  = cree_n_l_exp($1, listeExpressionsBis($$)); ///TODO
    }
    else if (!est_suivant(uniteCourante, _comparaisonBis_)) erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}

//listeExpressionsBis -> ',' expression listeExpressionsBis | EPSILON
n_l_exp* listeExpressionsBis(n_l_exp* herite)
{
    n_l_exp* $$ = NULL;
    n_exp* $2 = NULL;
    n_l_exp* herite_fils = NULL;

    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == VIRGULE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = expression();
        herite_fils = cree_n_l_exp($2, herite);
        $$ = listeExpressionsBis(herite_fils);
    }
    else if (est_suivant(uniteCourante, _comparaisonBis_))
        $$ = herite;
    else erreur(__FUNCTION__);
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}


n_instr* instructionFaire(void)
{
    n_instr* $$ = NULL;
    n_instr* $2 = NULL;
    n_exp* $4 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, PRINT_SYNTAXE);
    if (uniteCourante == FAIRE)
    {
        affiche_lexique();
        uniteCourante = yylex();
        $2 = instructionBloc();
        if (uniteCourante == TANTQUE)
        {
            affiche_lexique();
            uniteCourante = yylex();
            $4 = expression();
            if (uniteCourante == POINT_VIRGULE)
            {
                affiche_lexique();
                uniteCourante = yylex();
                $$ = cree_n_instr_faire($2, $4);
            }
            else erreur("Manque un point virgule");
        }
        else erreur("Manque un tant que");
    }
    else erreur("Manque un faire");
    affiche_balise_fermante(__FUNCTION__, PRINT_SYNTAXE);
    return $$;
}
