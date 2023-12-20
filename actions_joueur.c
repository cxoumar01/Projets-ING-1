#include "actions_joueur.h"

int coup_valide(int col)
{
    /*
     * Si la colonne renseignée est inférieur ou égal à zéro
     * ou que celle-ci est supérieure à la longueur du tableau
     * ou que la colonne indiquée est saturée
     * alors le coup est invalide.
     */

    if (col <= 0 || col > P4_COLONNES || grille[col - 1][0] != ' ')
        return 0;

    return 1;
}


int demande_action(int *coup)
{
    /*
     * Demande l'action à effectuer au joueur courant.
     * S'il entre un chiffre, c'est qu'il souhaite jouer.
     * S'il entre la lettre « Q » ou « q », c'est qu'il souhaite quitter.
     * S'il entre autre chose, une nouvelle saisie sera demandée.
     */

    char c;
    int ret = ACT_ERR;

    if (scanf("%d", coup) != 1)
    {
        if (scanf("%c", &c) != 1)
        {
            fprintf(stderr, "Erreur lors de la saisie\n");
            return ret;
        }

        switch (c)
        {
        case 'Q':
        case 'q':
            ret = ACT_QUITTER;
            break;

        case 'C':
        case 'c':
            ret = ACT_CHARGER;
            break;

        case 'S':
        case 's':
            ret = ACT_SAUVEGARDER;
            break;

        default:
            ret = ACT_NOUVELLE_SAISIE;
            break;
        }
    }
    else
        ret = ACT_JOUER;

    if (!vider_tampon(stdin))
    {
         fprintf(stderr, "Erreur lors de la vidange du tampon.\n");
         ret = ACT_ERR;
    }

    return ret;
}


int demande_fichier(char *nom, size_t max)
{
    /*
     * Demande et récupère un nom de fichier.
     */

    char *nl;

    printf("Veuillez entrer un nom de fichier : ");

    if (fgets(nom, max, stdin) == NULL)
    {
         fprintf(stderr, "Erreur lors de la saisie\n");
         return 0;
    }

    nl = strchr(nom, '\n');

    if (nl == NULL && !vider_tampon(stdin))
    {
       fprintf(stderr, "Erreur lors de la vidange du tampon.\n");
       return 0;
    }

    if (nl != NULL)
        *nl = '\0';

    return 1;
}


int demande_nb_joueur(void)
{
    /*
     * Demande et récupère le nombre de joueurs.
     */

    int njoueur = 0;

    while (1)
    {
        printf("\nCombien de joueurs prennent part à cette partie ? ");

        if (scanf("%d", &njoueur) != 1 && ferror(stdin))
        {
                fprintf(stderr, "Erreur lors de la saisie\n");
                return 0;
        }
        else if (!vider_tampon(stdin))
        {
            fprintf(stderr, "Erreur lors de la vidange du tampon.\n");
            return 0;
        }

        if (njoueur != 1 && njoueur != 2)
            fprintf(stderr, "Le nombre de joueurs doit être compris entre 1 et 2.\nRéessayez.\n");
        else
            break;
    }

    return njoueur;
}
