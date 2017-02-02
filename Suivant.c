/* symboles non terminaux */

#define EPSILON 0

#define NB_NON_TERMINAUX 41

#define _listeDecVariables_ 1
#define _listeDecFonctions_ 2
#define _declarationVariable_ 3
#define _declarationFonction_ 4
#define _listeParam_ 5
#define _listeInstructions_ 6
#define _instruction_ 8
#define _instructionAffect_ 9
#define _instructionBloc_ 10
#define _instructionSi_ 11
#define _instructionTantque_ 12
#define _instructionAppel_ 13
#define _instructionRetour_ 14
#define _instructionEcriture_ 15
#define _instructionVide_ 16
#define _var_ 17
#define _expression_ 18
#define _appelFct_ 19
#define _conjonction_ 20
#define _negation_ 21
#define _comparaison_ 22
#define _expArith_ 23
#define _terme_ 24
#define _facteur_ 25
#define _argumentsEffectifs_ 26
#define _listeExpressions_ 27
#define _listeExpressionsBis_ 7
#define _programme_ 28
#define _conjonctionBis_ 29
#define _optTailleTableau_ 30
#define _expArithBis_ 31
#define _optSinon_ 32
#define _comparaisonBis_ 33
#define _optDecVariables_ 34
#define _optIndice_ 35
#define _listeDecVariablesBis_ 36
#define _instructionPour_ 37
#define _termeBis_ 38
#define _expressionBis_ 39
#define _instructionFaire_ 40
#define _optListeDecVariables_ 41



/* symboles terminaux */
#define NB_TERMINAUX 31

#define POINT_VIRGULE 1
#define PLUS 2
#define MOINS 3
#define FOIS 4
#define DIVISE 5
#define PARENTHESE_OUVRANTE 6
#define PARENTHESE_FERMANTE 7
#define CROCHET_OUVRANT 8
#define CROCHET_FERMANT 9
#define ACCOLADE_OUVRANTE 10
#define ACCOLADE_FERMANTE 11
#define EGAL 12
#define INFERIEUR 13
#define ET 14
#define OU 15
#define NON 16
#define SI 17
#define ALORS 18
#define SINON 19
#define TANTQUE 20
#define FAIRE 21
#define ENTIER 22
#define RETOUR 23
#define LIRE 24
#define ECRIRE 25
#define ID_VAR 26
#define ID_FCT 27
#define NOMBRE 28
#define FIN 29
#define VIRGULE 30


#include"symboles.h"
#include"suivants.h"

void initialise_suivants(void){
  int i,j;

  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      suivants[i][j] = 0;

  //exemple

  suivants[_listeDecVariables_][PARENTHESE_FERMANTE] = 1;

  suivants[_listeDecVariablesBis_][PARENTHESE_FERMANTE] = 1;

  suivants[_declarationVariable_][PARENTHESE_FERMANTE] = 1;

  suivants[_optTailleTableau_][PARENTHESE_FERMANTE] = 1;

  suivants[_listeParam_][FIN] = 1;
  suivants[_listeParam_][ACCOLADE_FERMANTE] = 1;

  suivants[_optDecVariables_][FIN] = 1;
  suivants[_optDecVariables_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionBloc_][ACCOLADE_FERMANTE] = 1;



  suivants[_declarationFonction_][FIN] = 1;

  suivants[_listeDecFonctions_][FIN] = 1;

  suivants[_instruction_][ACCOLADE_FERMANTE] = 1;

  suivants[_optListeDecVariables_][PARENTHESE_FERMANTE] = 1;

  suivants[_optSinon_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionVide_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionEcriture_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionAppel_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionSi_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionRetour_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionTantque_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionAffect_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionTantque_][ACCOLADE_FERMANTE] = 1;

  suivants[_instruction_][ACCOLADE_FERMANTE] = 1;

  suivants[_listeInstructions_][ACCOLADE_FERMANTE] = 1;


  suivants[_appelFct_][POINT_VIRGULE] = 1;
  suivants[_appelFct_][ALORS] = 1;
  suivants[_appelFct_][FAIRE] = 1;
  suivants[_appelFct_][PARENTHESE_FERMANTE] = 1;
  suivants[_appelFct_][CROCHET_FERMANT] = 1;

  suivants[_optIndice_][POINT_VIRGULE] = 1;
  suivants[_optIndice_][ALORS] = 1;
  suivants[_optIndice_][FAIRE] = 1;
  suivants[_optIndice_][PARENTHESE_FERMANTE] = 1;
  suivants[_optIndice_][CROCHET_FERMANT] = 1;

  suivants[_var_][POINT_VIRGULE] = 1;
  suivants[_var_][ALORS] = 1;
  suivants[_var_][FAIRE] = 1;
  suivants[_var_][PARENTHESE_FERMANTE] = 1;
  suivants[_var_][CROCHET_FERMANT] = 1;

  suivants[_facteur_][POINT_VIRGULE] = 1;
  suivants[_facteur_][ALORS] = 1;
  suivants[_facteur_][FAIRE] = 1;
  suivants[_facteur_][PARENTHESE_FERMANTE] = 1;
  suivants[_facteur_][CROCHET_FERMANT] = 1;

  suivants[_negation_][POINT_VIRGULE] = 1;
  suivants[_negation_][ALORS] = 1;
  suivants[_negation_][FAIRE] = 1;
  suivants[_negation_][PARENTHESE_FERMANTE] = 1;
  suivants[_negation_][CROCHET_FERMANT] = 1

  suivants[_termeBis_][POINT_VIRGULE] = 1;
  suivants[_termeBis_][ALORS] = 1;
  suivants[_termeBis_][FAIRE] = 1;
  suivants[_termeBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_termeBis_][CROCHET_FERMANT] = 1

  suivants[_terme_][POINT_VIRGULE] = 1;
  suivants[_terme_][ALORS] = 1;
  suivants[_terme_][FAIRE] = 1;
  suivants[_terme_][PARENTHESE_FERMANTE] = 1;
  suivants[_terme_][CROCHET_FERMANT] = 1

  suivants[_expArithBis_][POINT_VIRGULE] = 1;
  suivants[_expArithBis_][ALORS] = 1;
  suivants[_expArithBis_][FAIRE] = 1;
  suivants[_expArithBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expArithBis_][CROCHET_FERMANT] = 1

  suivants[_expArith_][POINT_VIRGULE] = 1;
  suivants[_expArith_][ALORS] = 1;
  suivants[_expArith_][FAIRE] = 1;
  suivants[_expArith_][PARENTHESE_FERMANTE] = 1;
  suivants[_expArith_][CROCHET_FERMANT] = 1

  suivants[_comparaisonBis_][POINT_VIRGULE] = 1;
  suivants[_comparaisonBis_][ALORS] = 1;
  suivants[_comparaisonBis_][FAIRE] = 1;
  suivants[_comparaisonBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaisonBis_][CROCHET_FERMANT] = 1;


  suivants[_comparaison_][POINT_VIRGULE] = 1;
  suivants[_comparaison_][ALORS] = 1;
  suivants[_comparaison_][FAIRE] = 1;
  suivants[_comparaison_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaison_][CROCHET_FERMANT] = 1;

  suivants[_conjonctionBis_][POINT_VIRGULE] = 1;
  suivants[_conjonctionBis_][ALORS] = 1;
  suivants[_conjonctionBis_][FAIRE] = 1;
  suivants[_conjonctionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonctionBis_][CROCHET_FERMANT] = 1;

  suivants[_conjonction_][POINT_VIRGULE] = 1;
  suivants[_conjonction_][ALORS] = 1;
  suivants[_conjonction_][FAIRE] = 1;
  suivants[_conjonction_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonction_][CROCHET_FERMANT] = 1;

  suivants[_expressionBis_][POINT_VIRGULE] = 1;
  suivants[_expressionBis_][ALORS] = 1;
  suivants[_expressionBis_][FAIRE] = 1;
  suivants[_expressionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expressionBis_][CROCHET_FERMANT] = 1;

  suivants[_expression_][POINT_VIRGULE] = 1;
  suivants[_expression_][ALORS] = 1;
  suivants[_expression_][FAIRE] = 1;
  suivants[_expression_][PARENTHESE_FERMANTE] = 1;
  suivants[_expression_][CROCHET_FERMANT] = 1;


  suivants[_listeExpressions_][PARENTHESE_FERMANTE] = 1;

  suivants[_listeExpressionsBis_][PARENTHESE_FERMANTE] = 1;

  // TODO: Compléter le tableau suivants ici
}

int est_suivant(int terminal, int non_terminal)
{
  return suivants[non_terminal][terminal];
}
