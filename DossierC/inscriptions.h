#ifndef INSCRIPTIONS_H
#define INSCRIPTIONS_H

#define FICHIER_INSCRIPTIONS "inscriptions.dat"

#include "shifts.h"

Erreur chargerFichierInscriptions(Shift * * pDebShift);
void sauverFichier(Shift * pDebShift);

#endif