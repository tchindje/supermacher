#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendeur.h"


//global variable to manipulate stream file
FILE* f_v = NULL;
char* nom_fichier_v = "fichier_vendeurs.dat";

void ouverture_fichier_v(const char* m){
    f_v=fopen(nom_fichier_v, m);
    if(f_v == NULL){
        printf("erreur lors de l'ouverture du fichier client .Verifiez svp\n");
        exit(1);
    }
}

void fermeture_fichier_v(){
    fclose(f_v);
}


//CRUD OPERATION
void ajouter_vendeur(){

    //open the file to add client information
    ouverture_fichier_v("a");

    Vendeur vendeur;
	printf("\n\nVeuillez inserrer les Informations du vendeur.\n");
	printf("Nom: ");
	scanf("%s", vendeur.nom);
    printf("Adresse : ");
    scanf("%s", vendeur.addresse);
    printf("Salaire  : ");
    scanf("%f", &vendeur.salaire);

    //generate unique client number
    char code_[15] = "v_mat_";
    strncat(code_, vendeur.nom, 4);
    strcat(code_, "_");
    strncat(code_, vendeur.addresse, 2);
    strcpy(vendeur.matricule, code_);

    //Enregistrement des données saisies dans le fichier
    fprintf(f_v,"%s %s %s %f\n", vendeur.matricule, vendeur.nom, vendeur.addresse, vendeur.salaire);
    fermeture_fichier_v();
}

void ajouter_vendeurs(int n){

    if (n <= 0 ){
        printf("Erreur. Le nombre de vendeur doit etre superieur a 0");
        exit(1);
    }

    for (int i = 0 ; i < n; i++ ){
        ajouter_vendeur();
    }

    printf("Les information du vendeur ont ete enregistre avec du sucess.");
};


void lecture_fichier_vendeurs(Vendeur vendeurs[N_MAX_VENDEUR], int* n){
    //open the file
    ouverture_fichier_v("r");
    //printf("Ouverture reussie\n");

    Vendeur vendeur;
	int i=0;
	while (fscanf(f_v,"%s %s %s %f\n", vendeur.matricule, vendeur.nom, vendeur.addresse ,&vendeur.salaire)!= EOF ){
        vendeurs[i] = vendeur;
        i++;
	}

	*n=i;
    fermeture_fichier_v();

}

void modifier_info_vendeur(char* matri_vendeur){

    int i,j,k,n;
    Vendeur vendeurs[N_MAX_VENDEUR];
    lecture_fichier_vendeurs(vendeurs, &n);

	for(i=0;i<n;i++){
	    if(strcmp(vendeurs[i].matricule, matri_vendeur)==0){
			//printf("vendeur trouve\n");
			j=i;
			break;
        }
	}


	if(i >= n ){
        printf("Matricule du vendeur Inexistant. Veillez saisir un matricule valide");
        exit(1);
	}

    ouverture_fichier_v("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
        fprintf(f_v,"%s %s %s %f\n", vendeurs[i].matricule, vendeurs[i].nom, vendeurs[i].addresse ,vendeurs[i].salaire);
    }

    for(i=j+1;i<n;i++){
        fprintf(f_v,"%s %s %s %f\n", vendeurs[i].matricule, vendeurs[i].nom, vendeurs[i].addresse ,vendeurs[i].salaire);
	}

    Vendeur vendeur;
	printf("\n\nMise a jour des information du vendeur :  %s \n", vendeurs[j].matricule);
	printf("Nom: ");
	scanf("%s", vendeur.nom);
    printf("Adresse : ");
    scanf("%s", vendeur.addresse);
    printf("Salaire : ");
    scanf("%f", &vendeur.salaire);

    strcpy(vendeur.matricule, vendeurs[j].matricule);

    //Enregistrement des données saisies dans le fichier
    fprintf(f_v,"%s %s %s %f\n", vendeur.matricule, vendeur.nom, vendeur.addresse ,vendeur.salaire);

    printf("Mise a jour du vendeur de matricule  %s reussi.\n", vendeur.matricule);
    fermeture_fichier_v();
};


void supprimer_vendeur(char* matri_vendeur){

    int i,j,k,n;
    Vendeur vendeurs[N_MAX_VENDEUR];
    lecture_fichier_vendeurs(vendeurs, &n);

	for(i=0;i<n;i++){
	    if(strcmp(vendeurs[i].matricule, matri_vendeur)==0){
			//printf("vendeur trouve\n");
			j=i;
			break;
        }
	}


	if(i >= n ){
        printf("Matricule du vendeur Inexistant. Veillez saisir un matricule valide");
        exit(1);
	}

    ouverture_fichier_v("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
        fprintf(f_v,"%s %s %s %f\n", vendeurs[i].matricule, vendeurs[i].nom, vendeurs[i].addresse ,vendeurs[i].salaire);
    }

    for(i=j+1;i<n;i++){
        fprintf(f_v,"%s %s %s %f\n", vendeurs[i].matricule, vendeurs[i].nom, vendeurs[i].addresse ,vendeurs[i].salaire);
	}

    printf("Supppression du vendeur de matricule  %s reussi.\n", vendeurs[j].matricule);
    fermeture_fichier_v();
};


void afficher_info_vendeur(Vendeur vendeur){
    printf("\t\t___________________________________________\n");
    printf("\t\tMatricule vendeur : %s \n", vendeur.matricule);
    printf("\t\tNom : %s\n", vendeur.nom);
    printf("\t\tAdresse : %s\n", vendeur.addresse);
    printf("\t\tSalaire : %.2f FCFA\n", vendeur.salaire);

}


void afficher_info_vendeurs(){
    int i,j,k,n=0;
    Vendeur vendeurs[N_MAX_VENDEUR];

    lecture_fichier_vendeurs(vendeurs, &n);

    if( n == 0){
        printf("Liste des vendeurs vide.");
        exit(1);
    }

    printf("\t\t---- Information des Vendeurs -----\n");
	for(i=0;i<n;i++){
        afficher_info_vendeur(vendeurs[i]);
	}
}


int rechercher_vendeur(char* matricule_v){
    int i,j,k,n=0;
    int trouver = 0;
    Vendeur vendeurs[N_MAX_VENDEUR];
    lecture_fichier_vendeurs(vendeurs, &n);

    for(i=0;i<n;i++){
	    if(strcmp(vendeurs[i].matricule, matricule_v) ==0){
			//printf("vendeur trouve\n");
			trouver = 1;
        }
	}
    return trouver;
}

Vendeur get_vendeur(char* matricule_v){
    int i,j,k,n=0;

    Vendeur vendeurs[N_MAX_VENDEUR];
    lecture_fichier_vendeurs(vendeurs, &n);
    for(i=0;i<n;i++){
	    if(strcmp(vendeurs[i].matricule, matricule_v) ==0){
			//printf("vendeur trouve\n");
			j = i;
			break;
        }
	}
	if (i >= n ){
        printf("Vendeur avec le matricule %s inexistant", matricule_v);
        exit(1);
	}
    return vendeurs[j];
}
