#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "testsunitaires.h"

// Interface du programme
void interface (Shift * pDebShift, Membre * tabMembres)
{
	Choix choix;
	Erreur codeErreur;
	char sauveAuto = 'N';

	printf("Bonjour, souhaitez-vous activer la sauvegarde automatique lors de la fermeture du programme O/N ? ");
	// from interface.c (description en commentaire au dessus de la définition de la fonction dans interface.c)
	scanf_s("%c", &sauveAuto);
	while ((sauveAuto != 'N') && (sauveAuto != 'O'))
	{
		printf("Veuillez entrer une valeur correcte (O)ui/(N)on : ");
		// from interface.c (Description en commentaire au-dessus de la définition de la fonction dans interface.c)
		viderBuffer();
		scanf_s("%c", &sauveAuto);
	}

	puts("");

	puts("Info : Vous pouvez stopper une action a tout moment en entrant la valeur 0 lors d'une demande de saisie.");
	puts("");

	// from interface.c
	choix = menu();

	while (choix != SORTIR)
	{

		codeErreur = PAS_D_ERREUR;

		switch (choix)
		{

			case AJOUT : 
				// from interface.c
				codeErreur = ajoutDoublette(pDebShift, tabMembres);
				break;
			case SUPPRESS :
				// from interface.c
				codeErreur = suppressDoublette(pDebShift);
				break;
			case AFFICHER:
				// from interface.c
				afficherDoublettes(pDebShift, tabMembres);
				break;
			case SAUVER:
				// from inscriptions.c
				sauverFichier(pDebShift);
				break;
		}

		lexique(codeErreur);

		puts("");

		choix = menu();

	}

	if (sauveAuto == 'O')
	{
		sauverFichier(pDebShift);
	}

}

// Affiche le menu principal
Choix menu(void)
{
	Choix choix;
	puts("1) Ajouter une doublette");
	puts("2) Supprimer une doublette");
	puts("3) Afficher les shifts et leurs doublettes");
	puts("4) Sauver fichier");
	puts("5) Quitter le programme");
	printf("Faites votre choix : ");

	choix = obtentionChoix();

	return choix;
}

// Fonction d'obtention et validation du choix du menu
Choix obtentionChoix(void)
{

	Choix choix = 0;

	while (choix < AJOUT || choix > SORTIR)
	{
		scanf_s("%d", &choix);
		if (choix < AJOUT || choix > SORTIR)
		{
			printf("Votre choix doit etre compris entre 1 et 5 : ");
		}
	}

	return choix;
	
}

// Partie du code regroupant l'ajout d'une doublette
Erreur ajoutDoublette(Shift * pDebShift, Membre * tabMembres)
{
	Shift * pShift;
	Boolean trouve;
	int choixDate, choixHeure;

	// from gestion.c 
	afficherShiftsReduits(pDebShift);

	printf("Veuillez entrer la date desiree sous la forme AAAAMMJJ : ");
	scanf_s("%d", &choixDate);
	printf("\n");

	if (choixDate == 0) {
		return ARRET_ACTION;
	}

	printf("Veuillez entrer l'heure desiree sous la forme HHMM : ");
	scanf_s("%d", &choixHeure);
	printf("\n");

	if (choixHeure == 0) {
		return ARRET_ACTION;
	}

	/*
		pShiftSauve à NULL car pas besoin de pShiftSauve dans le cas d'un ajout, utile lors de suppression
		permet seulement la réutilisation de la meme fonction lors de la suppression
		*/
	// from gestion.c
	trouve = rechercheShift(pDebShift, choixDate, choixHeure, &pShift);

	if (trouve == FALSE)
	{
		return SHIFT_INEXISTANT;
	}
	else
	{
		if (pShift->nbInscriptions < 16)
		{
			int num1, num2, iRMembre1, iRMembre2;
			int moy1 = 0;
			int moy2 = 0;
			char afficheListeJoueurs = 'N';

			printf("Souhaitez-vous affichez la liste des joueurs et leur numero de matricule O/N ? ");
			// from interface.c
			viderBuffer();
			scanf_s("%c", &afficheListeJoueurs);
			while ((afficheListeJoueurs != 'N') && (afficheListeJoueurs != 'O'))
			{
				printf("(O)ui / (N)on : ");
				// from interface.c
				viderBuffer();
				scanf_s("%c", &afficheListeJoueurs);
			}
			

			if (afficheListeJoueurs == 'O')
			{
				// from interface.c
				afficherTableauJoueurs(tabMembres);
			}

			puts("");

			printf("Veuillez entrer le numero de matricule du joueur 1 : ");
			scanf_s("%d", &num1);

			if (num1 == 0) {
				return ARRET_ACTION;
			}

			printf("\nVeuillez entrer le numero de matricule du joueur 2 : ");
			scanf_s("%d", &num2);

			if (num2 == 0) {
				return ARRET_ACTION;
			}

			// from gestion.c
			iRMembre1 = rechercheMembreDansTableau(num1, tabMembres);
			iRMembre2 = rechercheMembreDansTableau(num2, tabMembres);

			if ((iRMembre1 < NB_MEMBRES_FICHIER) && (iRMembre2 < NB_MEMBRES_FICHIER) && (tabMembres[iRMembre1].numMatricule == num1) && (tabMembres[iRMembre2].numMatricule == num2))
			{
				Boolean doubletteExiste;

				moy1 = tabMembres[iRMembre1].moyenne;
				moy2 = tabMembres[iRMembre2].moyenne;

				// from gestion.c
				doubletteExiste = verifDoubletteExisteDansShift(pShift->pDebListeIns, num1, num2);

				if (doubletteExiste == FALSE)
				{
					Erreur codeErreur;
					// from interface.c
					int categorie = calculCategorie(moy1, moy2);

					// from gestion.c
					codeErreur = ajoutInscription(&pShift, num1, num2, categorie);

					// from testunitaires.c
					// afficherShift(pShift);

					if (codeErreur == PAS_D_ERREUR)
					{
						printf("\nAjout effectue avec succes ! \n");
					}

					return codeErreur;

					puts("");
				}
				else
				{
					return DOUBLETTE_EXISTANTE_SHIFT;
				}
			}
			else
			{
				if (iRMembre1 >= NB_MEMBRES_FICHIER)
				{
					return MEMBRE_1_INEXISTANT;
				}
				else
				{
					return MEMBRE_2_INEXISTANT;
				}
			}
		}
		else
		{
			return SHIFT_COMPLET;
		}
	}
}

// Affiche le tableau des joueurs
void afficherTableauJoueurs(Membre * tabMembres)
{
	int i = 0;

	while (tabMembres[i].numMatricule < 999999)
	{
		printf("%d", tabMembres[i].numMatricule);
		printf(" ");
		printf("%s", tabMembres[i].nom);
		printf(" ");
		printf("%s", tabMembres[i].prenom);
		puts("");
		i++;
	}
}

// Partie du code regroupant la supression d'une doublette
Erreur suppressDoublette(Shift * pDebShift)
{
	Shift * pShift;
	Boolean trouve;
	int choixDate, choixHeure;
	char afficheShifts = 'N';

	printf("\nSouhaitez-vous afficher les shifts O/N ? ");
	// from interface.c
	viderBuffer();
	scanf_s("%c", &afficheShifts);
	while ((afficheShifts != 'N') && (afficheShifts != 'O'))
	{ 
		printf("(O)ui / (N)on : ");
		// from interface.c
		viderBuffer();
		scanf_s("%c", &afficheShifts);
	}

	puts("");

	if (afficheShifts == 'O')
	{
		afficherShiftsReduits(pDebShift);
	}

	printf("Veuillez entrer la date desiree sous la forme AAAAMMJJ : ");
	scanf_s("%d", &choixDate);

	if (choixDate == 0) {
		return ARRET_ACTION;
	}

	printf("\nVeuillez entrer l'heure desiree sous la forme HHMM : ");
	scanf_s("%d", &choixHeure);

	if (choixHeure == 0) {
		return ARRET_ACTION;
	}

	trouve = rechercheShift(pDebShift, choixDate, choixHeure, &pShift);

	if (trouve == FALSE)
	{
		return SHIFT_INEXISTANT;
	}
	else
	{
		if (pShift->nbInscriptions > 0)
		{
			Boolean trouveDoublette;
			Inscription * pDoublette;
			Inscription * pDoubletteSauve = NULL;
			char afficherDoublettesSupp = 'N';
			int id;

			printf("\nSouhaitez-vous afficher la liste des doublettes inscrites a ce shift O/N ? ");
			afficherDoublettesSupp = getchar(); // On se débarasse des \n indésirables
			scanf_s("%c", &afficherDoublettesSupp);
			while ((afficherDoublettesSupp != 'N') && (afficherDoublettesSupp != 'O')) 
			{
				printf("(O)ui / (N)on : ");
				// from interface.c
				viderBuffer();
				scanf_s("%c", &afficherDoublettesSupp);
			}
			viderBuffer();

			puts("");

			if (afficherDoublettesSupp == 'O')
			{
				// from gestion.c
				afficherDoublettesShift(pShift);
			}

			puts("");

			printf("Quel est l'id de la doublette a supprimer ? ");
			scanf_s("%d", &id);

			while ((id > pShift->nbInscriptions) || (id < 0))
			{
				printf("Cet id est incorrect, entrez un id : ");
				scanf_s("%d", &id);
			}

			if (id == 0) {
				return ARRET_ACTION;
			}

			// from gestion.c
			trouveDoublette = rechercheDoubletteDansShift(pShift->pDebListeIns, &pDoublette, &pDoubletteSauve, id);

			if (trouveDoublette == TRUE)
			{
				Erreur codeErreur;

				codeErreur = suppressionInscription(&pShift, &pDoublette, &pDoubletteSauve);

				if (codeErreur == PAS_D_ERREUR)
				{
					printf("\nSuppression effectuee avec succes ! \n");
				}

				return codeErreur;

				puts("");
			}
			else
			{
				return DOUBLETTE_INEXISTANTE_SHIFT;
			}

		}
		else
		{
			return SHIFT_VIDE;
		}
	}
}

// Affiche les doublettes inscrites à un shift
void afficherDoublettes(Shift * pDebShift, Membre * tabMembres)
{
	Shift * pShift = pDebShift;
	Shift * pShiftSauve = pShift;

	int jour = ((pShift->date) % 100);
	int mois = ((pShift->date) / 100) % 100;
	int annee = (pShift->date) / 10000;


	puts("");
	
	printf("-> Shift du ");
	(jour < 10) ? printf("0%d/", jour) : printf("%d/", jour);
	(mois < 10) ? printf("0%d/", mois) : printf("%d/", mois);
	printf("%d \n", annee);

	while (pShift != NULL)
	{
		jour = ((pShift->date) % 100);
		mois = ((pShift->date) / 100) % 100;
		annee = (pShift->date) / 10000;

		puts("");

		if (pShift->date != pShiftSauve->date)
		{
			printf("-> Shift du ");
			(jour < 10) ? printf("0%d/", jour) : printf("%d/", jour);
			(mois < 10) ? printf("0%d/", mois) : printf("%d/", mois);
			printf("%d \n", annee);
		}

		int heure = (pShift->heure) / 100;
		int minutes = (pShift->heure) % 100;

		printf("Heure : ");
		(heure < 10) ? printf("0%d:", heure) : printf("%d:", heure);
		(minutes < 10) ? printf("0%d\n", minutes) : printf("%d\n", minutes);

		Inscription * pInscription = pShift->pDebListeIns;

		if (pInscription != NULL)
		{
			while (pInscription != NULL)
			{
				// from gestion.c
				int iRMembre1 = rechercheMembreDansTableau(pInscription->numJoueur1, tabMembres);
				int iRMembre2 = rechercheMembreDansTableau(pInscription->numJoueur2, tabMembres);
				printf("Joueur 1 : %s %s, Joueur 2 : %s %s, categorie : %d\n",
					tabMembres[iRMembre1].nom, tabMembres[iRMembre1].prenom,
					tabMembres[iRMembre2].nom, tabMembres[iRMembre2].prenom,
					pInscription->categorie);

				pInscription = pInscription->pSuiv;
			}
		}
		else
		{
			printf("Ce shift ne contient pas d'inscription !");
		}

		puts("");

		pShiftSauve = pShift;
		pShift = pShift->pSuiv;

	}

	puts("");
}

// Calcule la categorie selon la doublette des joueurs
int calculCategorie(int moy1, int moy2)
{
	int moyenne = (moy1 + moy2) / 2 ;

	if (moyenne < 159)
	{
		return 6;
	}
	else {
		if (moyenne < 169)
		{
			return 5;
		}
		else {
			if (moyenne < 179)
			{
				return 4;
			}
			else {
				if (moyenne < 189)
				{
					return 3;
				}
				else {
					if (moyenne < 199)
					{
						return 2;
					}
					else {
						return 1;
					}
				}
			}
		}
	}
}

// Fonction permettant de vider le buffer des \n et eof indésirables lors d'obtention de char, récupérée sur le SdZ
void viderBuffer(void)
{
	int c = 0;

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}

}