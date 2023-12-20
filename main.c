#include <stdio.h>
#include <stdlib.h>
#include "var_communes.h"
#include "grille.h"
#include "calcul_jetons.h"
#include "actions_joueur.h"
#include "sauvegarde_chargement.h"
#include "jeu.h"

int main()
{
    int choix;

    do {
        clear_screen();
        afficher_ecran_principal();

        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                jeu();
                break;
            case 2:
                afficher_presentation();
                break;
            case 3:
                afficher_credits();
                break;
            case 4:
                // Option pour quitter le programme
                printf("Merci d'avoir joué. Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir à nouveau.\n");
                break;
        }
    } while (choix != 4);

    return 0;
}
