#ifndef INTERFACE_H
#define INTERFACE_H

#include "constantes.h"
#include "lexique.h"
#include "gestion.h"
#include "membres.h"
#include "shifts.h"

void interface (Shift * pDebShift, Membre * tabMembres);
Choix menu(void);
Choix obtentionChoix(void);
Erreur ajoutDoublette(Shift * pDebShift, Membre * tabMembres);
void afficherTableauJoueurs(Membre * tabMembres);
Erreur suppressDoublette(Shift * pDebShift);
void afficherDoublettes(Shift * pDebShift, Membre * tabMembres);
int calculCategorie(int moy1, int moy2);
void viderBuffer(void);

#endif INTERFACE_H