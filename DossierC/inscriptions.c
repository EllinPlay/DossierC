/*
	Contient les fonctions liées au fichier inscriptions.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include "inscriptions.h"
#include "shifts.h"
#include "gestion.h"

#define FICHIER_TEMP "temp.dat"

// Charge les shifts et leurs doulettes à partir du fichier inscriptions.dat
Erreur chargerFichierInscriptions(Shift * * pDebShift)
{
	FILE * fichierInscriptions;

	fopen_s(&fichierInscriptions, FICHIER_INSCRIPTIONS, "rb");

	if (fichierInscriptions == NULL)
	{
		return FICHIER_INSCRIPTIONS_INTROUVABLE;
	}
	else
	{
		ShiftEnreg shiftLu;
		Shift *pShiftSauve = NULL;
		Erreur codeErreur;

		fread_s(&shiftLu, sizeof(ShiftEnreg), sizeof(ShiftEnreg), 1, fichierInscriptions);

		while (!feof(fichierInscriptions))
		{
			// from gestion.c
			codeErreur = ajoutShift(pDebShift, &pShiftSauve, shiftLu.date, shiftLu.heure, 0, NULL);
			
			if (codeErreur == PAS_D_ERREUR)
			{
				int i = 0;

				while (i < shiftLu.nbInscription)
				{
					InscriptionEnreg inscriptionLue;

					fread_s(&inscriptionLue, sizeof(InscriptionEnreg), sizeof(InscriptionEnreg), 1, fichierInscriptions);

					if (codeErreur == PAS_D_ERREUR)
					{
						// from gestion.c
						codeErreur = ajoutInscription(&pShiftSauve, inscriptionLue.numJoueur1, inscriptionLue.numJoueur2, inscriptionLue.categorie);
					}
					else
					{
						return codeErreur;
					}

					i++;
				}

				fread_s(&shiftLu, sizeof(ShiftEnreg), sizeof(ShiftEnreg), 1, fichierInscriptions);
			}
			else
			{
				return codeErreur;
			}

		}

		fclose(fichierInscriptions);

		return PAS_D_ERREUR;
	}
}

// Fonction de sauvegarde dans le fichier inscriptions.dat
void sauverFichier(Shift * pDebShift)
{
	FILE *fichierInscriptions;

	fopen_s(&fichierInscriptions, FICHIER_INSCRIPTIONS, "wb");


	Shift *pShift = pDebShift;
	
	while (pShift != NULL)
	{
		Inscription * pInscription = pShift->pDebListeIns;
		ShiftEnreg shiftEnregistrement;
		
		shiftEnregistrement.date = pShift->date;
		shiftEnregistrement.heure = pShift->heure;
		shiftEnregistrement.nbInscription = pShift->nbInscriptions;

		
		fwrite(&shiftEnregistrement, sizeof(ShiftEnreg), 1, fichierInscriptions);
	
		while (pInscription != NULL)
		{
			InscriptionEnreg inscriptionEnregistrement;

			inscriptionEnregistrement.numJoueur1 = pInscription->numJoueur1; 
			inscriptionEnregistrement.numJoueur2 = pInscription->numJoueur2;
			inscriptionEnregistrement.categorie = pInscription->categorie;
	
			fwrite(&inscriptionEnregistrement, sizeof(InscriptionEnreg), 1, fichierInscriptions);

			pInscription = pInscription->pSuiv;
		}
		pShift = pShift->pSuiv;
	}
	fclose(fichierInscriptions);

	put("Sauvegarde effectuee avec succes ! ");
}
