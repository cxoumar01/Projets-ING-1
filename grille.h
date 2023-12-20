// grille.h
#ifndef GRILLE_H
#define GRILLE_H

#include "var_communes.h"

// D�claration des fonctions li�es � la grille
void affiche_grille(void);
void initialise_grille(void);
int position_valide(struct position *);
int grille_complete(void);
void selection_jetons(void);

#endif

