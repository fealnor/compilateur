#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"

#define PRINT_X86 1

void parcours_n_prog(n_prog *n);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
void parcours_l_exp(n_l_exp *n);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var(n_var *n);
void parcours_var_simple(n_var *n);
void parcours_var_indicee(n_var *n);
void parcours_appel(n_appel *n);

/*-------------------------------------------------------------------------*/

void parcours_n_prog(n_prog *n)
{
    if (PRINT_X86)
    {
        printf("%%include\t'io.asm'\n");
        printf("section\t.bss\n");
        printf("sinput:\tresb\t255\n");
    }
    parcours_l_dec(n->variables);
    if (PRINT_X86)
    {
        printf("\nsection\t.text\n");
        printf("global _start\n");
        printf("_start:\n");
        printf("\tcall\tmain\n");
        printf("\tmov\teax, 1\n");
        printf("\tint\t0x80\n");
    }
    parcours_l_dec(n->fonctions);
    if (PRINT_X86)
        printf("\tpop\tebp\n\tret");
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n)
{
  if(n){
    parcours_instr(n->tete);
    parcours_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) parcours_l_instr(n->u.liste);
    else if(n->type == affecteInst) parcours_instr_affect(n);
    else if(n->type == siInst) parcours_instr_si(n);
    else if(n->type == tantqueInst) parcours_instr_tantque(n);
    else if(n->type == appelInst) parcours_instr_appel(n);
    else if(n->type == retourInst) parcours_instr_retour(n);
    else if(n->type == ecrireInst) parcours_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n)
{
  parcours_exp(n->u.si_.test);
  parcours_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    parcours_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{
  parcours_exp(n->u.tantque_.test);
  parcours_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n) ///TODO
{
  parcours_var(n->u.affecte_.var);
  parcours_exp(n->u.affecte_.exp);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  parcours_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

int count_nb_args(n_l_exp *l) {
  if (l) return 1 + count_nb_args(l->queue);
  return 0;
}

void parcours_appel(n_appel *n)
{
  int args = count_nb_args(n->args);
  int result = rechercheExecutable(n->fonction);
  if (result == -1) erreur("fonction pas déclaré\n");
  else if (args != tabsymboles.tab[result].complement) erreur("mauvais nombre d'argument\n");
  else afficheTabsymboles();
  parcours_l_exp(n->args);

}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  parcours_exp(n->u.retour_.expression);

}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
    parcours_exp(n->u.ecrire_.expression);
}

/*-------------------------------------------------------------------------*/

void parcours_l_exp(n_l_exp *n)
{
  if(n){
    parcours_exp(n->tete);
    parcours_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_exp(n_exp *n)
{

  if(n->type == varExp) parcours_varExp(n);
  else if(n->type == opExp) parcours_opExp(n);
  else if(n->type == intExp) parcours_intExp(n);
  else if(n->type == appelExp) parcours_appelExp(n);
  else if(n->type == lireExp) parcours_lireExp(n);
}

/*-------------------------------------------------------------------------*/
void parcours_varExp(n_exp *n)
{

    parcours_var(n->u.var);

}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n)
{
  if( n->u.opExp_.op1 != NULL ) {
    parcours_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    parcours_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/
void parcours_intExp(n_exp *n)
{
}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n)
{
}

/*-------------------------------------------------------------------------*/
void parcours_appelExp(n_exp *n)
{
  parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void parcours_l_dec(n_l_dec *n)
{
  if( n ){
    parcours_dec(n->tete);
    parcours_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      parcours_foncDec(n);
    }
    else if(n->type == varDec) {
      parcours_varDec(n);
    }
    else if(n->type == tabDec) {
      parcours_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

int count_nb_dec(n_l_dec *l) {
  if (l) return 1 + count_nb_dec(l->queue);
  return 0;
}

void parcours_foncDec(n_dec *n)
{
  if (rechercheDeclarative(n->nom) == -1) {
    int args = count_nb_dec(n->u.foncDec_.param);
    ajouteIdentificateur(n->nom, portee, T_FONCTION, 0, args);
    tabsymboles.base++;
    entreeFonction();
    parcours_l_dec(n->u.foncDec_.param);
    parcours_l_dec(n->u.foncDec_.variables);
    parcours_instr(n->u.foncDec_.corps);
    afficheTabsymboles();
    sortieFonction();
  }
  else erreur("fonction deja declare");
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{
  if (rechercheExecutable(n->nom) == -1) { //pas utiliser rechercheDeclarative car que locale
    if (portee == P_VARIABLE_GLOBALE)
    {
        ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 0);
        tabsymboles.base++;
        adresseLocaleCourante++;
        printf("%s:\trest\t1\n", n->nom);
    }
    else if (portee == P_VARIABLE_LOCALE)
    {
        ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 0);
        adresseLocaleCourante++;
    }
    else if (portee == P_ARGUMENT)
    {
      ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 0);
      adresseArgumentCourant++;
    }
    afficheTabsymboles();
  }
  else erreur("var deja declare");
}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n)
{
  int result = rechercheDeclarative(n->nom);
  if (result == -1) {
    if (portee != P_VARIABLE_GLOBALE) erreur("Les tableaux sont toujours des var globales");
    ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, adresseLocaleCourante, n->u.tabDec_.taille);
    tabsymboles.base++;
    adresseLocaleCourante += n->u.tabDec_.taille;
    if (PRINT_X86)
    {
        printf("%s:\trest\t%d\n", n->nom, n->u.tabDec_.taille);
    }
  }
  else erreur("tableau déjà déclaré\n");
}

/*-------------------------------------------------------------------------*/

void parcours_var(n_var *n)
{
  if(n->type == simple) {
    parcours_var_simple(n);
  }
  else if(n->type == indicee) {
    parcours_var_indicee(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_var_simple(n_var *n)
{
  int result = rechercheExecutable(n->nom);
  if (result == -1) erreur("var non déclaré");
  else afficheTabsymboles();
}

/*-------------------------------------------------------------------------*/

void parcours_var_indicee(n_var *n)
{
  int result = rechercheExecutable(n->nom);
  if (result == -1) erreur("var non déclaré");
  else if (tabsymboles.tab[result].type == T_ENTIER) erreur("la var n'est pas un tableau");
  else afficheTabsymboles();

}


