#include "var_communes.h"

char grille[P4_COLONNES][P4_LIGNES];


void calcule_position(int coup, struct position *pos)
{
    /*
     * Traduit le coup joué en un numéro de colonne et de ligne.
     */

    int lgn;

    pos->colonne = coup;

    for (lgn = P4_LIGNES - 1; lgn >= 0; --lgn)
        if (grille[pos->colonne][lgn] == ' ')
        {
            pos->ligne = lgn;
            break;
        }
}


int choix_diff(void) {
    printf("A quelle difficulté voulez vous jouer?\n");
    printf("\t (1)   ----->  Facile\n");
    printf("\t (2)   ----->  Moyen\n");
    printf("\t (3)   ----->  Difficile\n");
    int choix;
    scanf("%d", &choix);
    return choix;
}


int ia(int difficulte)
{
    /*
     * Fonction mettant en œuvre l'IA présentée.
     * Assigne une valeur pour chaque colonne libre et retourne ensuite le numéro de
     * colonne ayant la plus haute valeur. Dans le cas où plusieurs valeurs égales sont
     * générées, un numéro de colonne est « choisi au hasard » parmi celles-ci.
     */

    unsigned meilleurs_col[P4_COLONNES];
    unsigned nb_meilleurs_col = 0;
    unsigned max = 0;
    unsigned col;

    /** Si la difficulté donnée en paramètre n'est pas prise en charge
      * l'ordinateur se mettra en mode moyen par défaut.
      */
    switch (difficulte)
    {
    case 1 : //Mode Facile
        // Choix aléatoire parmi les colonnes disponibles
        int colonne;
        do {
            colonne = nb_aleatoire_entre(0, P4_COLONNES - 1);
        } while (grille[colonne][0] != ' ');  // Vérifie si la colonne est libre

        return colonne;
        break;

    case 3: //Mode Difficile
        for (col = 0; col < P4_COLONNES; ++col)
        {
            struct position pos;
            unsigned longueur;

            if (grille[col][0] != ' ')
                continue;

            calcule_position(col, &pos);
            longueur = calcule_nb_jetons_depuis(&pos, J2_JETON);

            if (longueur >= 4)
                return col;

            longueur = umax(longueur, calcule_nb_jetons_depuis(&pos, J1_JETON));

            if (longueur >= max)
            {
                if (longueur > max)
                {
                    nb_meilleurs_col = 0;
                    max = longueur;
                }

                meilleurs_col[nb_meilleurs_col++] = col;
            }
        }

        return meilleurs_col[nb_aleatoire_entre(0, nb_meilleurs_col - 1)];
        break;

    default: //Mode Moyen
        for (col = 0; col < P4_COLONNES; ++col)
        {
            struct position pos;
            unsigned longueur;

            if (grille[col][0] != ' ')
                continue;

            calcule_position(col, &pos);
            longueur = calcule_nb_jetons_depuis(&pos, J2_JETON);

            if (longueur >= 3)
                return col;

            longueur = umax(longueur, calcule_nb_jetons_depuis(&pos, J1_JETON));

            if (longueur >= max)
            {
                if (longueur > max)
                {
                    nb_meilleurs_col = 0;
                    max = longueur;
                }

                meilleurs_col[nb_meilleurs_col++] = col;
            }
        }

        return meilleurs_col[nb_aleatoire_entre(0, nb_meilleurs_col - 1)];
    }
}


double nb_aleatoire(void)
{
    /*
     * Retourne un nombre pseudo-aléatoire compris entre zéro inclus et un exclus.
     */

    return rand() / ((double)RAND_MAX + 1.);
}


int nb_aleatoire_entre(int min, int max)
{
    /*
     * Retourne un nombre pseudo-aléatoire entre `min` et `max` inclus.
     */

    return nb_aleatoire() * (max - min + 1) + min;
}


int statut_jeu(struct position *pos, char jeton)
{
    /*
     * Détermine s'il y a lieu de continuer le jeu ou s'il doit être
     * arrêté parce qu'un joueur a gagné ou que la grille est complète.
     */

    if (grille_complete())
        return STATUT_EGALITE;
    else if (calcule_nb_jetons_depuis(pos, jeton) >= 4)
        return STATUT_GAGNE;

    return STATUT_OK;
}


int vider_tampon(FILE *fp)
{
    /*
     * Vide les données en attente de lecture du flux spécifié.
     */

    int c;

    do
        c = fgetc(fp);
    while (c != '\n' && c != EOF);

    return ferror(fp) ? 0 : 1;
}

void afficher_ecran_principal(void) {
    printf("--------------------------------------------------- Ecran Principal ---------------------------------------------------\n");
    printf("\t\t\t\t\t\t   1. Jouer\n");
    printf("\t\t\t\t\t\t   2. Présentation du jeu\n");
    printf("\t\t\t\t\t\t   3. Crédits\n");
    printf("\t\t\t\t\t\t   4. Quitter\n");
}

void afficher_presentation(void) {
    int retour;
    do {
        clear_screen();
        printf("------------------------------------------------- Présentation du Jeu -------------------------------------------------\n");
        // Contenu de la présentation
        printf("\n\n\t\t\t\t\t      Revenir au menu principal : 0\n");
        scanf("%d", &retour);
    } while (retour != 0);
}

void afficher_credits(void) {
    int retour;
    do {
        clear_screen();
        printf("------------------------------------------------------- Crédits -------------------------------------------------------\n");
        // Contenu des crédits
        printf("\t\t\t\t\tMembres du groupe :\n");
        printf("\t\t\t\t\t     - SARR Cheikh Modibo Oumar\n");
        printf("\t\t\t\t\t     - AKKAOUI Mohamed Ali\n");
        printf("\t\t\t\t\t     - BARADOUANE Amine\n");
        printf("\t\t\t\t\t\nSous la tutelle de Mme. GUIBADJ\n");
        printf("\n\nRevenir au menu principal : 0\n");
        scanf("%d", &retour);
    } while (retour != 0);
}


void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void delai(int secondes) {
    printf("Arrêt du programme dans : ");
    fflush(stdout);

    for (int i = secondes; i > 0; --i) {
        printf("%d ", i);
        fflush(stdout);
        sleep(1);
    }

    printf("\n");
}
