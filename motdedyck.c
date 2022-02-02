#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAILLE 100
#define TAILLE_MOT 40

#define USAGE "\
Usage: %s [HEIGHT,AREA] <LETTER 1> <LETTER 2> <WORD>\n\
\n\
Draws on an ASCII path of dycks word. The dycks word is provided on stdin and\n\
the result is printed on stdout. The length of the word must not exceed 40 characters.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Program parameters :\n\
  HEIGHT                    Optional parameter to calculate the height of the\n\
                            path under the word of dyck.\n\
  AREA                      Optional parameter to calculate the height of\n\
                            the path under the word of dyck.\n\
  LETTER 1, LETTER 2        Define the alphabet of the word.\n\
  WORD                      Word of dyck to draw.\n\
  "

struct motDeDyck {
    char mot[TAILLE_MOT];   //Le mot saisi
    char haut;              //Caractere ascendant
    char bas;               //Caractere descendant
};

enum error {
    OK                          = 0,
    ERREUR_ARGUMENTS_INVALIDES  = 1,
    ERREUR_DONNEES_INVALIDES    = 2,
    ERREUR_MOT_TROP_LONG        = 3,
    ERREUR_LETTRE_INTERDITE     = 4,
    ERREUR_MOT_NON_EQUILIBRE    = 5
};

void afficherMessageErreur(int code) {
    if (code == ERREUR_ARGUMENTS_INVALIDES)
        fprintf(stderr,"argument invalide");
    else if (code == ERREUR_DONNEES_INVALIDES)
        fprintf(stderr,"donnees invalides");
    else if (code == ERREUR_MOT_TROP_LONG)
        fprintf(stderr,"mot trop long");
    else if (code == ERREUR_LETTRE_INTERDITE)
        fprintf(stderr,"lettre interdite");
    else if (code == ERREUR_MOT_NON_EQUILIBRE)
        fprintf(stderr,"mot non equilibre");
}

void terminerExecution( int codeErreur) {
    afficherMessageErreur(codeErreur);
    exit(-1);
}

void verifierLettre( char *lettre, struct motDeDyck *mot, void (*f)(char*,struct motDeDyck*) ) {
    int taille_token = strlen(lettre);
    printf("Fonction taille lettre : %d\n",taille_token);
    if (taille_token != 1 ) 
        terminerExecution(ERREUR_DONNEES_INVALIDES);
    else 
        (*f)(lettre,mot);
}

void haut(char *lettre, struct motDeDyck *mot) {
    mot->haut = *lettre;
}

void bas(char *lettre, struct motDeDyck *mot) {
    mot->bas = *lettre;
}

void initiliserMotDeDyck(struct motDeDyck *mot, char *entree) {

    int nbParametre = 0;
    char* token;
    char* rest = entree;

     while ( (token = strtok_r(rest, " ", &rest)) ) {

         if (nbParametre == 0 ) {
            verifierLettre(token,mot,haut);
         }

         else if (nbParametre == 1) {
            verifierLettre(token,mot,bas);
         }

         else if (nbParametre == 2) {
             printf("%s\n", token);
             strcpy(mot->mot,token);
        }
        
        else {
            terminerExecution(ERREUR_DONNEES_INVALIDES);
        }

         nbParametre++;
     }

}

int estMotValide(struct motDeDyck *mot, int *hauteur_max) {
    char *buffer_mot = mot->mot;
    int hauteur_courrante = 0;
    int nb_haut = 0;
    int nb_bas = 0;
    int index = 0;
    
    while ( index < 40 && *buffer_mot != "\0") {

        if (*buffer_mot == mot->haut ) {
            hauteur_courrante++;
            nb_haut++;
            if ( *hauteur_max < hauteur_courrante)
                *hauteur_max++;
        }
        else if (*buffer_mot == mot->bas) {
            hauteur_courrante--;
            nb_bas--;
        }
        else
            return ERREUR_LETTRE_INTERDITE;

        if (hauteur_courrante < 0)
            return ERREUR_MOT_NON_EQUILIBRE;
    }

    if (index == 40 && *buffer_mot != "\0")
        return ERREUR_MOT_TROP_LONG;

    return OK;
}

void dessiner(struct motDeDyck *mot, int *hauteur_max) {
    
}

int main(int argc, char *argv[]) {

    //Affichage des arguments
    //printf("argc = %d\n", argc);
    //for (unsigned int i = 0; i < argc; ++i) {
    //    printf("argv[%d] = %s\n", i, argv[i]);
    //}

    //Test Initialisation
    struct motDeDyck mot;
    char entree[MAX_TAILLE];
    fgets(entree,MAX_TAILLE,stdin);
    int hauteur_max = 0;

    initiliserMotDeDyck(&mot,entree);
    int status = estMotValide(&mot,&hauteur_max);
    if ( status != OK )
        terminerExecution(status);
    else {
        dessiner(&mot);
    }

    printf("%d \n",index);    
    printf("Haut : %c\n",mot.haut);
    printf("Bas : %c\n",mot.bas);
    printf("Mot : %s\n",mot.mot);

    return 0;
}

void afficherUsage() {
    printf("%s",USAGE);
}

