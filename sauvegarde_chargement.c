#include "var_communes.h"
/**
int sauvegarder_jeu(char *nom, char jeton, int njoueur)
{
    FILE *fp;
    unsigned col;
    unsigned lgn;

    fp = fopen(nom, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", nom);
        return 0;
    }
    else if (fprintf(fp, "%c%d", jeton, njoueur) < 0)
    {
        fprintf(stderr, "Impossible de sauvegarder le joueur courant\n");
        return 0;
    }

    if (fputc('|', fp) == EOF)
    {
        fprintf(stderr, "Impossible de sauvegarder la grille\n");
        return 0;
    }

    for (col = 0; col < P4_COLONNES; ++col)
    {
        for (lgn = 0; lgn < P4_LIGNES; ++lgn)
        {
            if (fprintf(fp, "%c|", grille[col][lgn]) < 0)
            {
                fprintf(stderr, "Impossible de sauvegarder la grille\n");
                return 0;
            }
        }
    }

    if (fputc('\n', fp) == EOF)
    {
        fprintf(stderr, "Impossible de sauvegarder la grille\n");
        return 0;
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Impossible de fermer le fichier %s\n", nom);
        return 0;
    }

    printf("La partie a bien été sauvegardée dans le fichier %s\n", nom);
    return 1;
}


int charger_jeu(char *nom, char *jeton, int *njoueur)
{
    FILE *fp;
    unsigned col;
    unsigned lgn;

    fp = fopen(nom, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", nom);
        return 0;
    }
    else if (fscanf(fp, "%c%d", jeton, njoueur) != 2)
    {
        fprintf(stderr, "Impossible de récupérer le joueur et le nombre de joueurs\n");
        return 0;
    }

    for (col = 0; col < P4_COLONNES; ++col)
        for (lgn = 0; lgn < P4_LIGNES; ++lgn)
        {
            if (fscanf(fp, "|%c", &grille[col][lgn]) != 1)
            {
                fprintf(stderr, "Impossible de récupérer la grille\n");
                return 0;
            }
        }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Impossible de fermer le fichier %s\n", nom);
        return 0;
    }

    return 1;
}
*/
int sauvegarder_jeu(const char *pseudo, char jeton, int njoueur) {
    FILE *fp;
    struct sauvegarde partie;

    // Charger le fichier de sauvegarde existant dans la mémoire
    fp = fopen("sauvegarde_p4.txt", "r");
    int partie_existe = 0;

    if (fp != NULL) {
        while (fscanf(fp, "%s %c %d", partie.pseudo, &partie.jeton, &partie.njoueur) == 3) {
            if (strcmp(partie.pseudo, pseudo) == 0) {
                // La partie existe déjà, mettre à jour
                partie_existe = 1;
                break;
            }
        }
        fclose(fp);
    }

    // Ouvrir le fichier de sauvegarde pour écriture
    fp = fopen("sauvegarde_p4.txt", "a");
    if (fp == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de sauvegarde.\n");
        delai(3); // délai de 3 secondes
        return 0;
    }

    // Si la partie existe, supprimer la ligne existante
    if (partie_existe) {
        FILE *tmp_fp = fopen("temp_sauvegarde_p4.txt", "w");
        if (tmp_fp == NULL) {
            fprintf(stderr, "Impossible de créer le fichier temporaire.\n");
            fclose(fp);
            delai(3); // délai de 3 secondes
            return 0;
        }

        rewind(fp);
        while (fscanf(fp, "%s %c %d", partie.pseudo, &partie.jeton, &partie.njoueur) == 3) {
            if (strcmp(partie.pseudo, pseudo) != 0) {
                fprintf(tmp_fp, "%s %c %d\n", partie.pseudo, partie.jeton, partie.njoueur);
            }
        }

        fclose(fp);
        fclose(tmp_fp);

        // Renommer le fichier temporaire en fichier de sauvegarde
        if (rename("temp_sauvegarde_p4.txt", "sauvegarde_p4.txt") != 0) {
            fprintf(stderr, "Impossible de renommer le fichier temporaire.\n");
            delai(3); // délai de 3 secondes
            return 0;
        }
    }

    // Ajouter la nouvelle partie à la fin du fichier
    fprintf(fp, "%s %c %d\n", pseudo, jeton, njoueur);

    fclose(fp);
    delai(3); // délai de 3 secondes
    return 1;
}

int charger_jeu(const char *pseudo, char *jeton, int *njoueur) {
    FILE *fp;
    struct sauvegarde partie;

    fp = fopen("sauvegarde_p4.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de sauvegarde.\n");
        delai(3); // délai de 3 secondes
        return 0;
    }

    int partie_trouvee = 0;

    while (fscanf(fp, "%s %c %d", partie.pseudo, &partie.jeton, &partie.njoueur) == 3) {
        if (strcmp(partie.pseudo, pseudo) == 0) {
            // Partie trouvée, mettre à jour les valeurs
            *jeton = partie.jeton;
            *njoueur = partie.njoueur;
            partie_trouvee = 1;
            break;
        }
    }

    fclose(fp);

    if (!partie_trouvee) {
        fprintf(stderr, "Partie introuvable pour le pseudo : %s\n", pseudo);
        delai(3); // délai de 3 secondes
        return 0;
    }

    return 1;
}

