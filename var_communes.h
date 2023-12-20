// p4_common.h
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#ifndef P4_COMMON_H
#define P4_COMMON_H

#define P4_COLONNES (7)
#define P4_LIGNES (6)


#define ACT_ERR (0)
#define ACT_JOUER (1)
#define ACT_NOUVELLE_SAISIE (2)
#define ACT_SAUVEGARDER (3)
#define ACT_CHARGER (4)
#define ACT_QUITTER (5)

#define STATUT_OK (0)
#define STATUT_GAGNE (1)
#define STATUT_EGALITE (2)

#define MAX_NOM (255)

struct position
{
    int colonne;
    int ligne;
};

#define J1_JETON ('X')
#define J2_JETON ('O')

extern char grille[P4_COLONNES][P4_LIGNES];

struct sauvegarde {
    char pseudo[25];
    char jeton;
    int njoueur;
    char grille[P4_COLONNES][P4_LIGNES];
};

extern int sauvegarder_jeu(const char *pseudo, char jeton, int njoueur);
extern int charger_jeu(const char *pseudo, char *jeton, int *njoueur);

// Fonctions déclarées mais définies dans les fichiers sources
extern void afficher_ecran_principal(void);
extern void afficher_presentation(void);
extern void afficher_credits(void);
extern void afficher_statistiques(void);
void clear_screen(void);
extern void affiche_grille(void);
extern void calcule_position(int, struct position *);
extern unsigned calcule_nb_jetons_depuis_vers(struct position *, int, int, char);
extern unsigned calcule_nb_jetons_depuis(struct position *, char);
///extern int charger_jeu(char *nom, char *, int *);
extern int coup_valide(int);
extern int demande_action(int *);
extern int demande_fichier(char *, size_t);
extern int demande_nb_joueur(void);
extern int grille_complete(void);
extern int choix_diff(void);
extern int ia(int difficulte);
extern void initialise_grille(void);
extern double nb_aleatoire(void);
extern int nb_aleatoire_entre(int, int);
extern int position_valide(struct position *);
///extern int sauvegarder_jeu(char *nom, char, int);
extern int statut_jeu(struct position *pos, char);
extern unsigned umax(unsigned, unsigned);
extern int vider_tampon(FILE *);
extern void selection_jetons(void);

#endif
