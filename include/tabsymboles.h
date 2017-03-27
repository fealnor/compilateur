#ifndef __TABSYMBOLES__
#define __TABSYMBOLES__

#include "tabsymboles.h"

// Nombre maximum d'identificateurs (globaux + locaux dans 1 fonction)
#define MAX_IDENTIF 1000

// PORTÉES
#define P_VARIABLE_GLOBALE 1
#define P_VARIABLE_LOCALE 2
#define P_ARGUMENT 3

// TYPES
#define T_ENTIER 1
#define T_TABLEAU_ENTIER 2
#define T_FONCTION 3

// Enregistrement décrivant une entrée de la table des symboles
typedef struct {
  char *identif;  // Nom de l'identificateur
  int portee;     // Valeurs possibles P_VARIABLE_GLOBALE, P_VARIABLE_LOCALE, P_ARGUMENT
  int type;       // Valeurs possibles T_ENTIER, T_TABLEAU_ENTIER et T_FONCTION
  int adresse;    // décalage �  partir de $fp ou .data nombre d'octets
  int complement; // taille d'un tableau OU nombre d'arguments d'une fonction
} desc_identif;

// Type 'table des symboles' avec le tableau et deux pointeurs pour le contexte
typedef struct {
  desc_identif tab[MAX_IDENTIF];
  int base;   // base=0 : contexte global, base=sommet contexte local
  int sommet; // pointe toujours vers la prochaine ligne disponible du tableau
} tabsymboles_;

void entreeFonction(void);
void sortieFonction(void);
int ajouteIdentificateur(char *identif,  int portee, int type, int adresse, int complement);
int rechercheExecutable(char *identif);
int rechercheDeclarative(char *identif);
void afficheTabsymboles(void);

// Déclaré dans tabsymboles.c
extern tabsymboles_ tabsymboles;
// À déclarer dans votre module de génération de code
extern int portee;
extern int adresseLocaleCourante;
extern int adresseArgumentCourant;
// adresseGlobaleCourante n'est pas utilisée dans tabsymboles.c
// elle peut être locale �  votre module de génération de code
#endif
