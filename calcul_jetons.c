#include "calcul_jetons.h"

unsigned calcule_nb_jetons_depuis_vers(struct position *pos, int dpl_hrz, int dpl_vrt, char jeton)
{
    /*
     * Calcule le nombre de jetons adajcents identiques depuis une position donnée en se
     * déplaçant de `dpl_hrz` horizontalement et `dpl_vrt` verticalement.
     * La fonction s'arrête si un jeton différent ou une case vide est rencontrée ou si
     * les limites de la grille sont atteintes.
     */

    struct position tmp;
    unsigned nb = 1;

    tmp.colonne = pos->colonne + dpl_hrz;
    tmp.ligne = pos->ligne + dpl_vrt;

    while (position_valide(&tmp))
    {
        if (grille[tmp.colonne][tmp.ligne] == jeton)
            ++nb;
        else
            break;

        tmp.colonne += dpl_hrz;
        tmp.ligne += dpl_vrt;
    }

    return nb;
}


unsigned calcule_nb_jetons_depuis(struct position *pos, char jeton)
{
    /*
     * Calcule le nombre de jetons adjacents en vérifant la colonne courante,
     * de la ligne courante et des deux obliques courantes.
     * Pour ce faire, la fonction calcule_nb_jeton_depuis_vers() est appelé à
     * plusieurs reprises afin de parcourir la grille suivant la vérification
     * à effectuer.
     */

    unsigned max;

    max = calcule_nb_jetons_depuis_vers(pos, 0, 1, jeton);
    max = umax(max, calcule_nb_jetons_depuis_vers(pos, 1, 0, jeton) + \
    calcule_nb_jetons_depuis_vers(pos, -1, 0, jeton) - 1);
    max = umax(max, calcule_nb_jetons_depuis_vers(pos, 1, 1, jeton) + \
    calcule_nb_jetons_depuis_vers(pos, -1, -1, jeton) - 1);
    max = umax(max, calcule_nb_jetons_depuis_vers(pos, 1, -1, jeton) + \
    calcule_nb_jetons_depuis_vers(pos, -1, 1, jeton) - 1);

    return max;
}


unsigned umax(unsigned a, unsigned b)
{
    /*
     * Retourne le plus grand des deux arguments.
     */

    return (a > b) ? a : b;
}
