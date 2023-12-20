#include "var_communes.h"
#include "grille.h"

void initialise_grille(void)
{
    /*
     * Initalise les caractères de la grille.
     */

    unsigned col;
    unsigned lgn;

    for (col = 0; col < P4_COLONNES; ++col)
        for (lgn = 0; lgn < P4_LIGNES; ++lgn)
            grille[col][lgn] = ' ';
}


void affiche_grille(void) {
    int col, lgn;
    int largeur_console = 120;

    // Calcul de l'espacement avant l'affichage des colonnes pour centrer la grille
    int espacement_avant_colonnes = (largeur_console - (4 * P4_COLONNES + 1)) / 2;

    putchar('\n');

    // Affichage de l'espacement avant les colonnes
    for (int espace = 0; espace < espacement_avant_colonnes; ++espace) {
        printf(" ");
    }

    for (col = 1; col <= P4_COLONNES; ++col)
        printf("  %d ", col);

    putchar('\n');
    // Ligne de séparation
    for (int espace = 0; espace < espacement_avant_colonnes; ++espace) {
        printf(" ");
    }

    putchar('+');

    for (col = 1; col <= P4_COLONNES; ++col)
        printf("---+");

    putchar('\n');

    for (lgn = 0; lgn < P4_LIGNES; ++lgn) {
        // Affichage de l'espacement avant la ligne
        for (int espace = 0; espace < espacement_avant_colonnes; ++espace) {
            printf(" ");
        }

        putchar('|');

        for (col = 0; col < P4_COLONNES; ++col)
            if (isalpha(grille[col][lgn]))
                printf(" %c |", grille[col][lgn]);
            else
                printf(" %c |", ' ');

        putchar('\n');
        // Ligne de séparation
        for (int espace = 0; espace < espacement_avant_colonnes; ++espace) {
            printf(" ");
        }

        putchar('+');

        for (col = 1; col <= P4_COLONNES; ++col)
            printf("---+");

        putchar('\n');
    }

    // Affichage de l'espacement avant les colonnes
    for (int espace = 0; espace < espacement_avant_colonnes; ++espace) {
        printf(" ");
    }

    for (col = 1; col <= P4_COLONNES; ++col)
        printf("  %d ", col);

    putchar('\n');
}


int position_valide(struct position *pos)
{
    /*
     * Vérifie que la position fournie est bien comprise dans la grille.
     */

    int ret = 1;

    if (pos->colonne >= P4_COLONNES || pos->colonne < 0)
        ret = 0;
    else if (pos->ligne >= P4_LIGNES || pos->ligne < 0)
        ret = 0;

    return ret;
}

int grille_complete(void)
{
    /*
     * Détermine si la grille de jeu est complète.
     */

    unsigned col;
    unsigned lgn;

    for (col = 0; col < P4_COLONNES; ++col)
        for (lgn = 0; lgn < P4_LIGNES; ++lgn)
            if (grille[col][lgn] == ' ')
                return 0;

    return 1;
}

/**void selection_jetons(void) {
    int choix;
    printf("JOUEUR 1 : Veuillez choisir votre jeton.\n1. X\n2. O\n3. #\n4. @\n5. $\n6. €\n");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1:
            J1_JETON = 'X';
            break;

        case 2:
            J1_JETON = 'O';
            break;

        case 3:
            J1_JETON = '#';
            break;

        case 4:
            J1_JETON = '@';
            break;

        case 5:
            J1_JETON = '$';
            break;

        case 6:
            J1_JETON = '€';
            break;

        default:
            J1_JETON = 'X';
    }


    printf("JOUEUR 2 : Veuillez choisir votre jeton.\n1. X\n2. O\n3. #\n4. @\n5. $\n6. €\n");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1:
            J2_JETON = 'X';
            break;

        case 2:
            J2_JETON = 'O';
            break;

        case 3:
            J2_JETON = '#';
            break;

        case 4:
            J2_JETON = '@';
            break;

        case 5:
            J2_JETON = '$';
            break;

        case 6:
            J2_JETON = '€';
            break;

        default:
            J2_JETON = 'O';
    }
}**/
