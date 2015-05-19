#include <stdio.h>
#include <stdlib.h>
#include "lexique.h"

// Affiche un message selon l'erreur reçue
void lexique(Erreur codeErreur)
{
	switch (codeErreur)
	{
		case ARRET_ACTION:
			printf("\nArret de l'action en cours ! \n");
			break;
		case FICHIER_MEMBRE_INTROUVABLE:
			printf("\nFichier membresFSBB.dat introuvable !\n");
			break;
		case FICHIER_SHIFTS_INTROUVABLE:
			printf("\nFichier datesOrgShifts.dat introuvable !\n");
			break;
		case FICHIER_INSCRIPTIONS_INTROUVABLE:
			printf("\nFichier inscriptions.dat introuvable !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_SHIFT:
			printf("\nEspace memoire insuffisant lors de l'ajout d'un shift !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_INSCRIPTION:
			printf("\nEspace memoire insuffisant lors de l'ajout d'un shift a partir du fichier de sauvegarde !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_DOUBLETTE:
			printf("\nEspace memoire insuffisant lors de l'ajout d'une doublette !\n");
			break;
		case SHIFT_INEXISTANT:
			printf("\nShift inexistant !\n");
			break;
		case SHIFT_COMPLET:
			printf("\nShift complet !\n");
			break;
		case SHIFT_VIDE:
			printf("\nShift vide !\n");
			break;
		case MEMBRE_INEXISTANT:
			printf("\nMembre inexistant !\n");
			break;
		case DOUBLETTE_EXISTANTE_SHIFT:
			printf("\nDoublette existante dans le shift !\n");
			break;
		case DOUBLETTE_INEXISTANTE_SHIFT:
			printf("\nDoublette inexistante dans le shift !\n");
			break;
	}
}