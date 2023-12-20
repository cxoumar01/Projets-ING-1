#include "jeu.h"
#include "var_communes.h"
#include "grille.h"
#include "calcul_jetons.h"
#include "actions_joueur.h"
#include "sauvegarde_chargement.h"


/**int jeu(void) {
    static char nom[MAX_NOM];
    int statut, difficulte;
    char jeton = J1_JETON;
    int njoueur;

    printf("\t\t\t\t\t\t   1. Nouvelle partie\n");
    printf("\t\t\t\t\t\t   2. Charger une partie\n");
    printf("Choisissez une option : ");

    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        initialise_grille();
        affiche_grille();
        difficulte = choix_diff();
        njoueur = demande_nb_joueur();

        if (!njoueur)
            return EXIT_FAILURE;
    } else if (choix == 2) {
        printf("Entrez le nom du fichier de sauvegarde : ");
        if (!demande_fichier(nom, sizeof nom) || !charger_jeu(nom, &jeton, &njoueur))
            return EXIT_FAILURE;
        affiche_grille();
    } else {
        fprintf(stderr, "Option invalide. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        struct position pos;
        int action;
        int coup;

        if (njoueur == 1 && jeton == J2_JETON)
        {
            coup = ia(difficulte);
            printf("Joueur 2 : %d\n", coup + 1);
            calcule_position(coup, &pos);
        }
        else
        {
            printf("Entrez 'q' pour quitter la partie.\n");
            printf("Joueur %d : ", (jeton == J1_JETON) ? 1 : 2);
            action = demande_action(&coup);

            if (action == ACT_ERR)
                return EXIT_FAILURE;
            else if (action == ACT_QUITTER)
                return 0;
            else if (action == ACT_SAUVEGARDER)
            {
                if (!demande_fichier(nom, sizeof nom) || !sauvegarder_jeu(nom, jeton, njoueur))
                //if (!sauvegarder_jeu(nom, jeton, njoueur))
                    return EXIT_FAILURE;
                else
                    return 0;
            }
            else if (action == ACT_NOUVELLE_SAISIE || !coup_valide(coup))
            {
                fprintf(stderr, "Vous ne pouvez pas jouer à cet endroit\n");
                continue;
            }

            calcule_position(coup - 1, &pos);
        }

        grille[pos.colonne][pos.ligne] = jeton;
        affiche_grille();
        statut = statut_jeu(&pos, jeton);

        if (statut != STATUT_OK)
            break;

        jeton = (jeton == J1_JETON) ? J2_JETON : J1_JETON;
    }

    if (statut == STATUT_GAGNE)
        printf("Le joueur %d a gagné\n", (jeton == J1_JETON) ? 1 : 2);
    else if (statut == STATUT_EGALITE)
        printf("Égalité\n");

    return 0;
}*/



int jeu(void) {
    int statut, difficulte;
    char jeton = J1_JETON;
    int njoueur;

    printf("\t\t\t\t\t\t   1. Nouvelle partie\n");
    printf("\t\t\t\t\t\t   2. Charger une partie\n");
    printf("Choisissez une option : ");

    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        initialise_grille();
        affiche_grille();
        difficulte = choix_diff();
        njoueur = demande_nb_joueur();

        if (!njoueur)
            return EXIT_FAILURE;
    } else if (choix == 2) {
        char pseudo[25];
        printf("Entrez votre pseudo : ");
        if (scanf("%s", pseudo) != 1) {
            fprintf(stderr, "Erreur lors de la saisie du pseudo. Fin du programme.\n");
            return EXIT_FAILURE;
        }

        // Charger la partie correspondant au pseudo
        if (!charger_jeu(pseudo, &jeton, &njoueur)) {
            fprintf(stderr, "Impossible de charger la partie. Fin du programme.\n");
            return EXIT_FAILURE;
        }

        affiche_grille();
    } else {
        fprintf(stderr, "Option invalide. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    while (1) {
        struct position pos;
        int action;
        int coup;

        if (njoueur == 1 && jeton == J2_JETON) {
            coup = ia(difficulte);
            printf("Joueur 2 : %d\n", coup + 1);
            calcule_position(coup, &pos);
        } else {
            printf("Entrez 'q' pour quitter la partie.\n");
            printf("Joueur %d : ", (jeton == J1_JETON) ? 1 : 2);
            action = demande_action(&coup);

            if (action == ACT_ERR)
                return EXIT_FAILURE;
            else if (action == ACT_QUITTER) {
                char sauvegarder;
                printf("Voulez-vous sauvegarder la partie ? (o/n) : ");
                scanf(" %c", &sauvegarder);

                if (sauvegarder == 'o' || sauvegarder == 'O') {
                    char pseudo[25];
                    printf("Entrez votre pseudo pour la sauvegarde : ");
                    if (scanf("%s", pseudo) != 1) {
                        fprintf(stderr, "Erreur lors de la saisie du pseudo. Fin du programme.\n");
                        return EXIT_FAILURE;
                    }

                    // Sauvegarder la partie avec le pseudo
                    if (!sauvegarder_jeu(pseudo, jeton, njoueur)) {
                        fprintf(stderr, "Impossible de sauvegarder la partie. Fin du programme.\n");
                        return EXIT_FAILURE;
                    }
                }

                return 0;
            } else if (action == ACT_SAUVEGARDER) {
                char pseudo[25];
                printf("Entrez votre pseudo pour la sauvegarde : ");
                if (scanf("%s", pseudo) != 1) {
                    fprintf(stderr, "Erreur lors de la saisie du pseudo. Fin du programme.\n");
                    return EXIT_FAILURE;
                }

                // Sauvegarder la partie avec le pseudo
                if (!sauvegarder_jeu(pseudo, jeton, njoueur)) {
                    fprintf(stderr, "Impossible de sauvegarder la partie. Fin du programme.\n");
                    return EXIT_FAILURE;
                }

                printf("Partie sauvegardée avec succès.\n");
                continue;
            } else if (action == ACT_NOUVELLE_SAISIE || !coup_valide(coup)) {
                fprintf(stderr, "Vous ne pouvez pas jouer à cet endroit\n");
                continue;
            }

            calcule_position(coup - 1, &pos);
        }

        grille[pos.colonne][pos.ligne] = jeton;
        affiche_grille();
        statut = statut_jeu(&pos, jeton);

        if (statut != STATUT_OK)
            break;

        jeton = (jeton == J1_JETON) ? J2_JETON : J1_JETON;
    }

    if (statut == STATUT_GAGNE)
        printf("Le joueur %d a gagné\n", (jeton == J1_JETON) ? 1 : 2);
    else if (statut == STATUT_EGALITE)
        printf("Égalité\n");

    delai(3);
    return 0;
}
