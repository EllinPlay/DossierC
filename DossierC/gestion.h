#ifndef GESTION_H
#define GESTION_H

#include "constantes.h"
#include "shifts.h"
#include "membres.h"
#include "inscriptions.h"

Erreur ajoutShift(Shift * * pDebShift, Shift **pShiftSauve, int date, int heure, int nbInscriptions, Inscription *pDebListeIns);
void afficherShiftsReduits(Shift * pDebShift);
Boolean rechercheShift(Shift * pDebShift, int choixDate, int choixHeure, Shift * * pPShift);
int rechercheMembreDansTableau(int num,  Membre * tabMembres);
Boolean verifDoubletteExisteDansShift(Inscription * pDebListeIns, int num1, int num2);
Erreur ajoutInscription(Shift * * pShift, int num1, int num2, int categorie);
void afficherDoublettesShift(Shift * pShift);
Boolean rechercheDoubletteDansShift(Inscription * pDebListeIns, Inscription * * pDoublette, Inscription * * pDoubletteSauve, int id);
Erreur suppressionInscription(Shift * * pShift, Inscription * * pDoublette, Inscription * * pDoubletteSauve);

#endif