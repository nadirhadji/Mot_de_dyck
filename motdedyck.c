/**
 * @file motdedyck.c
 * @author Nadir Hadji (HADN08069703)
 * @brief INF3135 - Construction et Maintenance de logiciel
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TAILLE 100
#define TAILLE_MOT 40
#define RETOUR_CHARIOT_ASCII 10
#define FIN_DE_TEXT_ASCII 3
#define ETOILE 42
#define SLASH 47
#define BACK_SLASH 92
#define HAUTEUR "hauteur"
#define AIRE "aire"

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

/**
 * @brief Ecrire sur la sortie standard la cause du message d'erreur
 */
void afficher_message_erreur(int code);

/**
 * @brief Affiche l'erreur en appelant afficher_message_erreur(code) et stop 
 * l'éxecution du programme suite a une erreur. Le code de sortie est -1;
 */
int terminer_execution( int codeErreur);

/**
 * @brief Placer lettre dans le champ haut de la structure motDeDyck;
 * Passage de motDeDyck par adresse.
 */
void haut(char lettre, struct motDeDyck *mot);

/**
 * @brief Placer lettre dans le champ bas de la structure motDeDyck;
 * Passage de motDeDyck par adresse.
 */
void bas(char lettre, struct motDeDyck *mot);

/**
 * @brief Verifie si le parametre dans agrv contient un seul caractere.
 * si oui passage en parametre de la fonction 'haut' ou 'bas' afin de placer
 * le contenu de lettre dans le champ apropriée de mot.
 */
void verifier_lettre( char *lettre, struct motDeDyck *mot, void (*f)(char,struct motDeDyck*) );

/**
 * @brief Verifie la taille du mot. Si la longeur est plus de 40 interuption avec le 
 * code d'erreur ERREUR_MOT_TROP_LONG sinon retourne la taille du mot. Cette infomation 
 * servira au autre méthodes.
 */
int verifier_mot (char *chaine, struct motDeDyck *mot);

/**
 * @brief Lecture dans l'entrée standard et decoupages de la chaine de caracteres pour en tirer 
 * uniquement les caractères utile sans espace ni tabulation ni retour chariot. Si pas d'erreur,
 * initialisation du mot de dyck par adresse.
 */
int initiliser_mot_de_dyck(struct motDeDyck *mot);

/**
 * @brief Algorithme qui verifie que les propriété du mot de dyck sont respecté.
 * Retourne le status de la verification.
 */
int est_mot_de_dyck(struct motDeDyck *mot, int *hauteur_max, int *taille_mot);

/**
 * @brief Lecture du parametre a la position 1 dans agrv et comparaison avec les 
 * nom d'option supporté.
 * Retourne 1 pour 'hauteur' et 2 pour 'aire'.
 * Interruption du programme avec un status -1 si donnée non prévu.
 */
int valider_parametre_optionnel(char *argv[]);

/**
 * @brief Verifie le contenur de l'entrée standard.
 * Retourne 1 si STDIN est  sinon 0;
 */
int entree_standard_vide();

/**
 * @brief Lectures des parametres dans agrv a partir de argv[2] et initalisation de la struc motDeDyck
 * si pas d'erreur. 
 * Retourne la taille du mot si verification ok.
 */
int valider_parametres_avec_options(char *argv[], struct motDeDyck *mot);

/**
 * @brief Lectures des parametres dans agrv a partir de argv[1] et initalisation de la struc motDeDyck
 * si pas d'erreur. 
 * Retourne la taille du mot si verification ok.
*/
int valider_parametres_sans_options(char *argv[], struct motDeDyck *mot);

/**
 * @brief Initialisation de la stuct motDeDyck via les parametres de agrv si ils suivent 
 * le format demandé.
 * Si argc = 1 , affichage des consignes a suivre.
 */
int initialisation_STDIN_vide(int argc, char *argv[], struct motDeDyck *mot, int *option);

/**
 * @brief Initialisation de la stuct motDeDyck via l'entrée standart si ils suivent 
 * le format demandé.
 * Si argc = 1 , affichage des consignes a suivre.
 */
int initialisation_via_STDIN(int argc, char *argv[], struct motDeDyck *mot, int *option);

/**
 * @brief Orchestration des méthodes.
 */
void executer(struct motDeDyck *mot, int *option, int *taille_mot);

/**
 * @brief Dessin de la représentation ASCII du mot de dyck dans une matrice
 * de taille hauteur_max * taille_mot.
 */
void dessiner(struct motDeDyck *mot, int *hauteur_max, int *taille_mot);

/**
 * @brief Affichage de la matrice
 */
void afficher_matrice(char *matrice, int *hauteur_max, int *taille_mot);


void afficher_message_erreur(int code) {
    if (code == ERREUR_ARGUMENTS_INVALIDES)
        printf("argument invalide");
    else if (code == ERREUR_DONNEES_INVALIDES)
        printf("donnees invalides");
    else if (code == ERREUR_MOT_TROP_LONG)
        printf("mot trop long");
    else if (code == ERREUR_LETTRE_INTERDITE)
        printf("lettre interdite");
    else if (code == ERREUR_MOT_NON_EQUILIBRE)
        printf("mot non equilibre");
}

int terminer_execution( int codeErreur) {
    afficher_message_erreur(codeErreur);
    exit(-1);
    return -1;
}

void haut(char lettre, struct motDeDyck *mot) {
    mot->haut = lettre;
}

void bas(char lettre, struct motDeDyck *mot) {
    mot->bas = lettre;
}

void verifier_lettre( char *lettre, struct motDeDyck *mot, void (*f)(char,struct motDeDyck*) ) {
    int taille_lettre = strlen(lettre);

    if (taille_lettre != 1 ) {
        terminer_execution(ERREUR_DONNEES_INVALIDES);
    }
    else {
            (*f)(lettre[0],mot);
    } 
}

//Retrourne la taille du mot ci celle-ci est valide
int verifier_mot (char *chaine, struct motDeDyck *mot) {

    int taille_m = strlen(chaine);

    if (taille_m > TAILLE_MOT)
        terminer_execution(ERREUR_MOT_TROP_LONG);
    else {
        strcpy(mot->mot,chaine);
    }
    return taille_m;
}

//Retroune la taille du mot si les instructions sont valide
int initiliser_mot_de_dyck(struct motDeDyck *mot) {

    int taille;
    char entree[MAX_TAILLE];            //chaine de caractere brute  
    fgets(entree,MAX_TAILLE,stdin);     //copie de STDIN dans entree
     
    int nbParametre = 0;
    char *delimiter = " \t\r\n\v\f";
    char* token = strtok(entree,delimiter);

     while ( token != NULL) {

        if (nbParametre == 0 ) 
            verifier_lettre(token,mot,haut);
        else if (nbParametre == 1) 
            verifier_lettre(token,mot,bas);
        else if (nbParametre == 2) 
            taille = verifier_mot(token,mot);
        else 
            terminer_execution(ERREUR_DONNEES_INVALIDES);

         nbParametre++;
         token = strtok(NULL,delimiter);
     }
     return taille;
}

int est_mot_de_dyck(struct motDeDyck *mot, int *hauteur_max, int *taille_mot) {
    char *iterateur_mot = mot->mot;
    int hauteur_courante = 0;
    int nb_haut = 0;
    int nb_bas = 0;

    for (int i = 0 ; i < *taille_mot; i++) {
        if (*iterateur_mot == mot->haut ) {
            hauteur_courante++;
            nb_haut++;
            if ( *hauteur_max < hauteur_courante)
                *hauteur_max = ++*hauteur_max;
        }
        else if (*iterateur_mot == mot->bas) {
            hauteur_courante--;
            nb_bas++;
        }
        else
            return ERREUR_LETTRE_INTERDITE;

        if (hauteur_courante < 0)
            return ERREUR_MOT_NON_EQUILIBRE;
        
        iterateur_mot++;
    }

    if ( nb_bas != nb_haut)
        return ERREUR_MOT_NON_EQUILIBRE;

    return OK;
}

void afficher_matrice(char *matrice, int *hauteur_max, int *taille_mot) {

    int position = *taille_mot * (*hauteur_max - 1);

    while (position >= 0) {

        for ( int i = position ; i < position + *taille_mot; i++) {
            printf("%c",matrice[i]);
        }
        printf("\n");
        position = position - *taille_mot;
    }
}

void dessiner(struct motDeDyck *mot, int *hauteur_max, int *taille_mot) {

    char matrice[*hauteur_max-1][*taille_mot];

    int hauteur_courante = 0;
    int buffer_hauteur_courante = hauteur_courante;

    char *mot_courant = mot->mot;
    char *mot_suivant = (mot->mot + 1);

    for ( int i = 0 ; i < *taille_mot ; i++) {
        for (int j = 0 ; j < *hauteur_max ; j++) {

            if ( j != hauteur_courante) {
                matrice[j][i] = ETOILE;
            }
            else {
                if (*mot_courant == mot->haut ) {
                    matrice[j][i] = SLASH;
                    if (*mot_suivant == mot->haut)
                        buffer_hauteur_courante++;
                }
                else if (*mot_courant == mot->bas) {
                    matrice[j][i] = BACK_SLASH;
                    if (*mot_suivant == mot->bas)
                        buffer_hauteur_courante--;
                }
            }
        }

        hauteur_courante = buffer_hauteur_courante;
        mot_courant = mot_suivant;
        mot_suivant++;
    } 

    afficher_matrice(*matrice, hauteur_max, taille_mot);
}

int valider_parametre_optionnel(char *argv[]) {
    if (strcmp(argv[1],HAUTEUR) == 0) 
        return 1;
    else if (strcmp(argv[1],AIRE) == 0) 
        return 2;
    else    
        return terminer_execution(ERREUR_ARGUMENTS_INVALIDES);
}

//Retroune la taille du mot si les parametres sont valides
int valider_parametres_avec_options(char *argv[], struct motDeDyck *mot) {
        verifier_lettre(argv[2],mot,haut);
        verifier_lettre(argv[3],mot,bas);
        return verifier_mot(argv[4],mot);
}

//Retroune la taille du mot si les parametres sont valides
int valider_parametres_sans_options(char *argv[], struct motDeDyck *mot) {
        verifier_lettre(argv[1],mot,haut);
        verifier_lettre(argv[2],mot,bas);
        return verifier_mot(argv[3],mot);
}

int entree_standard_vide() {
    if ( (fseek(stdin,0,SEEK_END), ftell(stdin)) > 0 ) {
        rewind(stdin);
        return 0;
    }
     return 1;
}

//Retourne la taille du mot
int initialisation_STDIN_vide(int argc, char *argv[], struct motDeDyck *mot, int *option) {

    if ( argc == 1) {
        printf(USAGE,argv[0]);
        exit(0);
    }
    else if ( argc == 4) {
        return valider_parametres_sans_options(argv,mot);
    }
    else if ( argc == 5) {
        *option = valider_parametre_optionnel(argv);
         return valider_parametres_avec_options(argv,mot);
    }
    else
        return terminer_execution(ERREUR_ARGUMENTS_INVALIDES);

}

//Retourne la taille du mot
int  initialisation_via_STDIN(int argc, char *argv[], struct motDeDyck *mot, int *option) {

    if (argc == 1) {
        return initiliser_mot_de_dyck(mot);
    }
    else if ( argc == 2) {
        *option = valider_parametre_optionnel(argv);
         return initiliser_mot_de_dyck(mot);
    }
    else 
        return terminer_execution(ERREUR_ARGUMENTS_INVALIDES);
}

void executer(struct motDeDyck *mot, int *option, int *taille_mot) {
    int hauteur_max = 0;

    int status = est_mot_de_dyck(mot,&hauteur_max,taille_mot);

    if ( status != OK ) 
        terminer_execution(status);
    else {
        if (*option == 0){
            dessiner(mot,&hauteur_max,taille_mot);
        }
        else if (*option == 1)
            printf("%d\n",hauteur_max);
        else if (*option == 2)
            printf("%s\n","Affichage de l'air");
    }
}

int main(int argc, char *argv[]) {

     int stdin_vide = entree_standard_vide();
     struct motDeDyck mot;
     int option;       //0 = classique ; 1 = hauteur ; 2 = aire   
     int taille_mot;

    if (stdin_vide) {
        taille_mot = initialisation_STDIN_vide(argc, argv, &mot, &option);
    } 
    else{
        taille_mot = initialisation_via_STDIN(argc, argv, &mot, &option);
    }

    executer(&mot,&option,&taille_mot);
    return 0;
}