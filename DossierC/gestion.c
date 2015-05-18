/*
	Contient les fonctions de manipulation des pointeurs
*/

#include <stdio.h>
#include <stdlib.h>
#include "gestion.h"

// Ajoute un shift (lancement du programme)
Erreur ajoutShift(Shift * * pDebShift, Shift * * pShiftSauve, int date, int heure, int nbInscriptions, Inscription *pDebListeIns)
{
	Shift *pShift = (Shift *)malloc(sizeof(Shift));

	if (pShift == NULL)
	{
		return PLUS_D_ESPACE_MEMOIRE_AJOUT_SHIFT;
	}
	else
	{
		pShift->date = date;
		pShift->heure = heure;
		pShift->nbInscriptions = nbInscriptions;
		pShift->pDebListeIns = pDebListeIns;
		pShift->pSuiv = NULL;

		if (*pDebShift == NULL)
		{
			*pDebShift = pShift;
		}
		else
		{
			(*pShiftSauve)->pSuiv = pShift;
		}

		*pShiftSauve = pShift;
		
		return PAS_D_ERREUR;
	}

}

// Affiche les shifts sous format réduit (places disponibles restantes, pour une plus grande clarté lors de l'ajout d'une doublette
void afficherShiftsReduits(Shift * pDebShift)
{
	Shift * pShift = pDebShift;

	puts("");
	puts("Voici les differents shifts et le nombre de places disponibles : ");

	while (pShift != NULL)
	{
		// Affichage date
		int jour = (pShift->date) % 100;
		int mois = ((pShift->date) / 100) % 100;
		int annee = (pShift->date) / 10000;

		(jour < 100) ? printf("0%d/", jour) : printf("%d/", jour);
		(mois < 100) ? printf("0%d/", mois) : printf("%d/", mois);
		printf("%d ", annee);

		// Affichage heure
		int minutes = (pShift->heure) % 100;
		(minutes < 10) ? printf("%d:0%d", (pShift->heure) / 100, (pShift->heure) % 100) : printf("%d:%d", (pShift->heure) / 100, (pShift->heure) % 100);

		// Affichage places restantes
		printf(" %d place(s) restante(s)", 16 - (pShift->nbInscriptions));

		puts("");

		pShift = pShift->pSuiv;

	}

	puts("");
}

// Recherche d'un shift
Boolean rechercheShift(Shift * pDebShift, int date, int heure, Shift * * pPShift)
{
	*pPShift = pDebShift;

	while ((*pPShift != NULL) && (((*pPShift)->date != date) || ((*pPShift)->heure != heure)))
	{
		*pPShift = (*pPShift)->pSuiv;
	}

	if (*pPShift != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// Recherche de l'indice du membre dans le tableau des membres
int rechercheMembreDansTableau(int num, Membre * tabMembres)
{
	int i = 0;

	while (i < NB_MEMBRES_FICHIER && num > tabMembres[i].numMatricule)
	{
		i++;
	}

	return i;
}

// Verifie que la doublette n'est pas déjà inscrite au shift
Boolean verifDoubletteExisteDansShift(Inscription * pDebListeIns, int num1, int num2)
{
	Inscription * pDoublette = pDebListeIns;

	while (pDoublette != NULL && !((pDoublette->numJoueur1 == num1) && (pDoublette->numJoueur2 == num2)))
	{
		pDoublette = pDoublette->pSuiv;
	}

	if (pDoublette == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

// Ajout d'une doublette dans le shift
Erreur ajoutInscription(Shift * * pShift, int num1, int num2, int categorie)
{
	Inscription * pInscription = (Inscription *)malloc(sizeof(Inscription));

	if (pInscription == NULL)
	{
		return PLUS_D_ESPACE_MEMOIRE_AJOUT_DOUBLETTE;
	}
	else
	{
		pInscription->numJoueur1 = num1;
		pInscription->numJoueur2 = num2;
		pInscription->categorie = categorie;
		pInscription->pSuiv = (*pShift)->pDebListeIns;
		(*pShift)->pDebListeIns = pInscription;
		(*pShift)->nbInscriptions++;

		return PAS_D_ERREUR;
	}
}

// Affichage des doublettes d'un shift et leur "id"
void afficherDoublettesShift(Shift * pShift)
{
	Inscription * pInscription = pShift->pDebListeIns;
	int id = 1;

	while (pInscription != NULL)
	{
		printf("ID %d : ", id);
		printf("Matricule 1 : %d,  ", pInscription->numJoueur1);
		printf("Matricule 2 : %d \n", pInscription->numJoueur2);
		pInscription = pInscription->pSuiv;
		id++;
	}
}

// Recherche l'existence de la doublette dans le shift suivant l'id obtenu
Boolean rechercheDoubletteDansShift(Inscription * pDebListeIns, Inscription * * pDoublette, Inscription * * pDoubletteSauve, int id)
{
	int i = 1;

	*pDoublette = pDebListeIns;

	while ((*pDoublette != NULL) && (i < id))
	{
		*pDoubletteSauve = *pDoublette;
		*pDoublette = (*pDoubletteSauve)->pSuiv;
		i++;
	}

	if (*pDoublette == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

// Suppression d'une inscription dans un shift
Erreur suppressionInscription(Shift * * pShift, Inscription * * pDoublette, Inscription * * pDoubletteSauve)
{
	if (*pDoublette == (*pShift)->pDebListeIns)
	{
		(*pShift)->pDebListeIns = NULL;
	}
	else
	{
		(*pDoubletteSauve)->pSuiv = (*pDoublette)->pSuiv;
	}

	(*pShift)->nbInscriptions--;

	free(*pDoublette);
	*pDoublette = NULL; // Après quelques recherches, cette ligne serait conseillée car free() supprime l'allocation mémoire mais ne met pas le pointeur a NULL par défaut

	return PAS_D_ERREUR;
}