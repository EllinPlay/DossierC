/*
	Contient les fonctions liées à l'utilisation du fichier membresFSBB.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include "membres.h"

// Crée un tableau avec les membres du fichier membresFSBB.dat
Erreur creationTableauMembres(Membre * tabMembres)
{
	FILE *fichierMembres;

	fopen_s(&fichierMembres, FICHIER_MEMBRES, "rb");
	if (fichierMembres == NULL)
	{
		return FICHIER_MEMBRE_INTROUVABLE;
	}
	else
	{
		Membre membreLu;
		int iMembre = 0;

		fread_s(&membreLu, sizeof(Membre), sizeof(Membre), 1, fichierMembres);

		while (!feof(fichierMembres))
		{
			tabMembres[iMembre] = membreLu;
			fread_s(&membreLu, sizeof(Membre), sizeof(Membre), 1, fichierMembres);
			iMembre++;
		}

		// S'il y a moins de membres que la valeur de la constante NB_MEMBRES_FICHIER on remplit les numMatricule par 999999
		if (iMembre < NB_MEMBRES_FICHIER)
		{
			while (iMembre < NB_MEMBRES_FICHIER)
			{
				tabMembres[iMembre].numMatricule = 999999;
				iMembre++;
			}
		}

		fclose(fichierMembres);

		return PAS_D_ERREUR;

	}

}