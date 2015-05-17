#ifndef MEMBRES_H
#define MEMBRES_H

#include "constantes.h"

#define FICHIER_MEMBRES "membresFSBB.dat"
#define NB_MEMBRES_FICHIER 100
#define TAILLE_NOM_MEMBRE 80
#define TAILLE_PRENOM_MEMBRE 30

typedef struct membre Membre;
struct membre
{
	int numMatricule;
	char nom[TAILLE_NOM_MEMBRE];
	char prenom[TAILLE_PRENOM_MEMBRE];
	int moyenne;
};

Erreur creationTableauMembres(Membre * tabMembres);

#endif