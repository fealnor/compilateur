#include <stdio.h>
#include <stdlib.h>
#include "analyseur_lexical.h"
#include "symboles.h"
#include "analyseur_syntaxique.h"
#include"analyseur_xml.h"

char yytext[100];
FILE *yyin;

int analyse_lexicale(int argc, char *argv[])
{
    yyin = fopen(argv[2], "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }
    test_yylex_internal(yyin);
    return 0;
}



int compare_syntaxe(int argc, char *argv[])
 {
   noeud *racine1;
   noeud *racine2;
   int resultat;
   int verbose;

   if((argc != 4) && (argc != 5)){
     fprintf(stderr, "usage: %s c fichier_xml fichier_xml [v]\n", argv[0]);
     exit(1);

   }
   verbose = (argc == 5);

   yyin = fopen(argv[2], "r");
   if(yyin == NULL){
     fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[2]);
     return 1;
   }

   fprintf(stderr, "analyse du fichier : %s\n", argv[2]);
   racine1 = analyseur_xml();


   fclose(yyin);

   yyin = fopen(argv[3], "r");
   if(yyin == NULL){
     fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[3]);
     return 1;
   }

   fprintf(stderr, "analyse du fichier : %s\n", argv[3]);
   racine2 = analyseur_xml();

   fclose(yyin);

   fprintf(stderr, "comparaison des arbres\n");
   resultat = compare_arbres(racine1, racine2, verbose);
   libere_arbre(racine1);
   libere_arbre(racine2);


   if(resultat){
     printf("arbres egaux\n");
     return 0;
   }
   else{
     printf("arbres différents\n");
     return 1;
   }

 }

int analyse_syntaxique(int argc, char **argv) {
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s fichier_l\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[2], "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }

    char xml_file_name[60];
    int i;
    for(i = 0; argv[2][i] != '.'; ++i)
        xml_file_name[i] = argv[2][i];
    xml_file_name[i] = '\0';
    sprintf(xml_file_name, "%s_xml", xml_file_name);

    initialise_premiers();
    initialise_suivants();
    if (!initialise_file_xml(xml_file_name))
        return 1;
    uniteCourante = yylex();
    affiche_n_prog(programme());

}

int analyse_abstrait(int argc, char **argv) {
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s fichier_l\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[2], "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }

    char xml_file_name[60];
    int i;
    for(i = 0; argv[2][i] != '.'; ++i)
        xml_file_name[i] = argv[2][i];
    xml_file_name[i] = '\0';
    sprintf(xml_file_name, "%s2_xml", xml_file_name);

    initialise_premiers();
    initialise_suivants();
    if (!initialise_file_xml(xml_file_name))
        return 1;
    uniteCourante = yylex();
    parcours_n_prog(programme());

}

int main(int argc, char **argv) {
    if (!strcmp(argv[1], "s"))
        return analyse_syntaxique(argc, argv);
    if (!strcmp(argv[1], "c"))
        compare_syntaxe(argc, argv);
    if (!strcmp(argv[1], "l"))
        return analyse_lexicale(argc, argv);
    if (!strcmp(argv[1], "a"))
        return analyse_abstrait(argc, argv);
    return 1;
}
