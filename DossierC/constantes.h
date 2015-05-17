#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef enum erreur Erreur;
enum erreur { 
	PAS_D_ERREUR,
	FICHIER_MEMBRE_INTROUVABLE,
	FICHIER_SHIFTS_INTROUVABLE,
	FICHIER_INSCRIPTIONS_INTROUVABLE,
	PLUS_D_ESPACE_MEMOIRE_AJOUT_SHIFT,
	PLUS_D_ESPACE_MEMOIRE_AJOUT_INSCRIPTION,
	PLUS_D_ESPACE_MEMOIRE_AJOUT_DOUBLETTE,
	SHIFT_INEXISTANT,
	SHIFT_COMPLET,
	SHIFT_VIDE,
	MEMBRE_1_INEXISTANT,
	MEMBRE_2_INEXISTANT,
	DOUBLETTE_EXISTANTE_SHIFT,
	DOUBLETTE_INEXISTANTE_SHIFT
};

typedef enum choix Choix;
enum choix
{
	AJOUT = 1,
	SUPPRESS,
	AFFICHER,
	SAUVER,
	SORTIR
};

typedef enum boolean Boolean;
enum boolean { TRUE, FALSE };

#endif