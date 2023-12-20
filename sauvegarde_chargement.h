// sauvegarde_chargement.h
#ifndef SAUVEGARDE_CHARGEMENT_H
#define SAUVEGARDE_CHARGEMENT_H

#include "var_communes.h"

// D�claration des fonctions li�es � la sauvegarde et chargement
/** int sauvegarder_jeu(char *nom, char, int);
int charger_jeu(char *nom, char *, int *);*/
int sauvegarder_jeu(const char *pseudo, char jeton, int njoueur);
int charger_jeu(const char *pseudo, char *jeton, int *njoueur);

//void afficher_sauvegardes(void);

#endif

