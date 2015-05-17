#ifndef SHIFTS_H
#define SHIFTS_H

#include "constantes.h"

#define FICHIER_SHIFTS "datesOrgShifts.dat"

typedef struct inscriptionLue InscriptionEnreg;
struct inscriptionLue
{
	int numJoueur1;
	int numJoueur2;
	int categorie; 
};

typedef struct inscription Inscription;
struct inscription
{
	int numJoueur1;
	int numJoueur2;
	int categorie;
	Inscription *pSuiv;
}; 

typedef struct shiftFichier ShiftFichier;
struct shiftFichier
{
	int date;
	int heure;
};

typedef struct shift Shift;
struct shift
{
	int date;
	int heure;
	int nbInscriptions;
	Inscription * pDebListeIns;
	Shift * pSuiv;
};

typedef struct shiftEnreg ShiftEnreg;
struct shiftEnreg
{
	int date;
	int heure;
	int nbInscription;
};

Erreur initListeShift(Shift * * pDebShift);

#endif