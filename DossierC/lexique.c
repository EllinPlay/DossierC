#include <stdio.h>
#include <stdlib.h>
#include "lexique.h"

// Affiche un message selon l'erreur reçue
void lexique(Erreur codeErreur)
{
	switch (codeErreur)
	{
		case FICHIER_MEMBRE_INTROUVABLE:
			printf("Fichier membresFSBB.dat introuvable !\n");
			break;
		case FICHIER_SHIFTS_INTROUVABLE:
			printf("Fichier datesOrgShifts.dat introuvable !\n");
			break;
		case FICHIER_INSCRIPTIONS_INTROUVABLE:
			printf("Fichier inscriptions.dat introuvable !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_SHIFT:
			printf("Espace memoire insuffisant lors de l'ajout d'un shift !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_INSCRIPTION:
			printf("Espace memoire insuffisant lors de l'ajout d'un shift a partir du fichier de sauvegarde !\n");
			break;
		case PLUS_D_ESPACE_MEMOIRE_AJOUT_DOUBLETTE:
			printf("Espace memoire insuffisant lors de l'ajout d'une doublette !\n");
			break;
		case SHIFT_INEXISTANT:
			printf("Shift inexistant !\n");
			break;
		case SHIFT_COMPLET:
			printf("Shift compet !\n");
		case SHIFT_VIDE:
			printf("Shift vide !\n");
			break;
		case MEMBRE_1_INEXISTANT:
			printf("Membre 1 inexistant !");
			break;
		case MEMBRE_2_INEXISTANT:
			printf("Membre 2 inexistant !");
			break;
		case DOUBLETTE_EXISTANTE_SHIFT:
			printf("Doublette existante dans le shift !\n");
			break;
		case DOUBLETTE_INEXISTANTE_SHIFT:
			printf("Doublette inexistante dans le shift !\n");
			break;
	}
}