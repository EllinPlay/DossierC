/*

	Fichier main

*/

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "testsunitaires.h"

void main(void)
{

	Erreur codeErreur = PAS_D_ERREUR;
	Shift *pDebShift = NULL;
	Membre tabMembres[NB_MEMBRES_FICHIER];
	FILE *fichierInscriptions;

	// From membres.c
	codeErreur = creationTableauMembres(tabMembres);

	if (codeErreur == PAS_D_ERREUR)
	{
		// On ouvre le fichier afin de voir s'il y a du contenu (si ce n'est pas le 1er lancement)
		fopen_s(&fichierInscriptions, FICHIER_INSCRIPTIONS, "rb");

		if (fichierInscriptions == NULL)
		{
			// from shifts.c
			codeErreur = initListeShift(&pDebShift);
		}
		else
		{
			fclose(fichierInscriptions);
			// from inscriptions.c
			codeErreur = chargerFichierInscriptions(&pDebShift);
		}
	}

	if (codeErreur == PAS_D_ERREUR)
	{
		// from interface.c
		interface(pDebShift, tabMembres);
	}

	lexique(codeErreur);


	// Fonction pour tester (afficher) le contenu de tabMembres
	// testTableauMembres(tabMembres);	

	// Fonction pour tester le contenu de la liste chainée des shifts
	// testListeShifts(pDebShift);

	system("pause");
}