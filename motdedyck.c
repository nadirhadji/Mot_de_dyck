#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAILLE 100
#define TAILLE_MOT 40
#define RETOUR_CHARIOT_ASCII 10
#define FIN_DE_TEXT_ASCII 3
#define ETOILE 42
#define SLASH 47
#define BACK_SLASH 92

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

        if (nbParametre == 0 ) 
            verifierLettre(token,mot,haut);
        else if (nbParametre == 1) 
            verifierLettre(token,mot,bas);
        else if (nbParametre == 2) 
            strcpy(mot->mot,token);
        else 
            terminerExecution(ERREUR_DONNEES_INVALIDES);

         nbParametre++;
     }
}

int estMotDeDyck(struct motDeDyck *mot, int *hauteur_max, int *index) {
    char *buffer_mot = mot->mot;
    int hauteur_courante = 0;
    int nb_haut = 0;
    int nb_bas = 0;
    
    while ( *buffer_mot != RETOUR_CHARIOT_ASCII && *buffer_mot != FIN_DE_TEXT_ASCII) {

        printf("%d \n",*index);
        printf("mot : %d\n",*buffer_mot);    

        if (*buffer_mot == mot->haut ) {
            hauteur_courante++;
            nb_haut++;
            printf("Hauteur courante : %d \n",hauteur_courante);
            printf("nb haut : %d \n",nb_haut);
            if ( *hauteur_max < hauteur_courante)
                *hauteur_max = ++*hauteur_max;
        }
        else if (*buffer_mot == mot->bas) {
            hauteur_courante--;
            nb_bas++;
            printf("Hauteur courante : %d \n",hauteur_courante);
            printf("nb bas : %d \n",nb_bas);
        }
        else
            return ERREUR_LETTRE_INTERDITE;

        if (hauteur_courante < 0)
            return ERREUR_MOT_NON_EQUILIBRE;

        *index = ++*index;
        buffer_mot++;
    }

    if ( nb_bas != nb_haut)
        return ERREUR_MOT_NON_EQUILIBRE;

    if (*index == TAILLE_MOT-1 && buffer_mot != "\0")
        return ERREUR_MOT_TROP_LONG;

    return OK;
}

void afficherMatrice(char *matrice, int *hauteur_max) {

    for ( int i = 0 ; i <= 20 ; i++) {
        printf("%d\n",*matrice);
        matrice++;
    }
}

void dessiner(struct motDeDyck *mot, int *hauteur_max, int *taille_mot) {

    char matrice[*hauteur_max][*taille_mot];

    int hauteur_courante = 0;
    int buffer_hauteur_courante = hauteur_courante;

    char *buffer_mot_courant = mot->mot;
    char *buffer_mot_precedent;

    for ( int i = 0 ; i < *taille_mot ; i++) {
        for (int j = 0 ; j <= *hauteur_max ; j++) {

            printf("hauteur courante : %d \n",hauteur_courante);

            if ( j != hauteur_courante) {
                matrice[i][j] = ETOILE;
                printf("%c\n",matrice[i][j]);
            }
            else {

                if (buffer_mot_precedent == NULL) {
                    matrice[i][j] = SLASH;
                }

                else if (*buffer_mot_courant == mot->haut && *buffer_mot_precedent == mot->haut) {
                    buffer_hauteur_courante++;
                    matrice[i][j] = SLASH;
                    printf("%c \n",matrice[i][j]);
                }
                else if (*buffer_mot_courant == mot->bas && *buffer_mot_precedent == mot->bas) {
                    buffer_hauteur_courante--;
                    matrice[i][j] = BACK_SLASH;
                    printf("%c \n",matrice[i][j]);
                }
                else if (*buffer_mot_courant == mot->bas && *buffer_mot_precedent == mot->haut) {
                    matrice[i][j] = BACK_SLASH;
                }
                else if (*buffer_mot_courant == mot->haut && *buffer_mot_precedent == mot->bas) {
                    matrice[i][j] = SLASH;
                }
            }
        }
        printf("%c\n",*buffer_mot_courant);
        printf("%c\n",*buffer_mot_precedent);

        hauteur_courante = buffer_hauteur_courante;
        *buffer_mot_precedent = *buffer_mot_courant;
        buffer_mot_courant = buffer_mot_courant + 1;
    } 

    afficherMatrice(*matrice, hauteur_max);
}

 int main(int argc, char *argv[]) {

    //Affichage des arguments
    //printf("argc = %d\n", argc);
    //for (unsigned int i = 0; i < argc; ++i) {
    //    printf("argv[%d] = %s\n", i, argv[i]);
    //}

    //Variable globale 
    char entree[MAX_TAILLE];    //chaine de caractere brute
    struct motDeDyck mot;       
    int hauteur_max = 0;
    int nombre_lettre = 0;

    printf("hauteur max = %d\n",hauteur_max);
    printf("taille mot = %d\n",nombre_lettre);

    fgets(entree,MAX_TAILLE,stdin);
    initiliserMotDeDyck(&mot,entree);
    int status = estMotDeDyck(&mot,&hauteur_max,&nombre_lettre);
    if ( status != OK ) 
        terminerExecution(status);
    else {
        printf("hauteur max = %d\n",hauteur_max);
        printf("taille mot = %d\n",nombre_lettre);
        dessiner(&mot,&hauteur_max,&nombre_lettre);
    }

    printf("Haut : %c\n",mot.haut);
    printf("Bas : %c\n",mot.bas);
    printf("Mot : %s\n",mot.mot);

    return 0;
}

void afficherUsage() {
    printf("%s",USAGE);
}