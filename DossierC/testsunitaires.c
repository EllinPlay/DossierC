/*

	Tests unitaires pour chaque fonction

*/

#include <stdio.h>
#include <stdlib.h>
#include "testsunitaires.h"

// Test le contenu de tabMembres
void testTableauMembres(Membre * tabMembres)
{
	int iTest = 0;

	while (tabMembres[iTest].numMatricule < 999999)
	{
		printf("%d", tabMembres[iTest].numMatricule);
		printf(" ");
		printf("%s", tabMembres[iTest].nom);
		printf(" ");
		printf("%s", tabMembres[iTest].prenom);
		printf(" ");
		printf("%d", tabMembres[iTest].moyenne);
		puts("");
		iTest++;
	}
}

// Test le contenu de la liste chainée Shift
void testListeShifts(Shift *pDebShift)
{
	Shift *pShift = pDebShift;

	while (pShift != NULL)
	{
		printf("%p", pShift);
		printf(" ");
		printf("%d", pShift->date);
		printf(" ");
		printf("%d", pShift->heure);
		printf(" ");
		printf("%d", pShift->nbInscriptions);
		printf(" ");
		printf("%p", pShift->pDebListeIns);
		printf(" ");
		printf("%p", pShift->pSuiv);
		puts("");
		pShift = pShift->pSuiv;
	}
}

// Test le contenu d'un chainon Shift
void afficherShift(Shift * pShift)
{
	Inscription * pInscription = pShift->pDebListeIns;

	while (pInscription != NULL)
	{
		printf("%p ", pInscription);
		printf("%d ", pInscription->numJoueur1);
		printf("%d ", pInscription->numJoueur2);
		printf("%p \n", pInscription->pSuiv);
		pInscription = pInscription->pSuiv;
	}
}