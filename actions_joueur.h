// actions_joueur.h
#ifndef ACTIONS_JOUEUR_H
#define ACTIONS_JOUEUR_H

#include "var_communes.h"

// D�claration des fonctions li�es aux actions du joueur
int coup_valide(int);
int demande_action(int *);
int demande_fichier(char *, size_t);
int demande_nb_joueur(void);

#endif

