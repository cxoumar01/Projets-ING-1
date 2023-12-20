// calcul_jetons.h
#ifndef CALCUL_JETONS_H
#define CALCUL_JETONS_H

#include "var_communes.h"

// Déclaration des fonctions liées au calcul des jetons
unsigned calcule_nb_jetons_depuis_vers(struct position *, int, int, char);
unsigned calcule_nb_jetons_depuis(struct position *, char);
unsigned umax(unsigned, unsigned);

#endif

