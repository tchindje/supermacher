#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vente.h"
#include "vendeur.h"


char* nom_fichier_vte = "fichier_ventes.dat";
FILE* f_vte = NULL;

void ouverture_fichier_ventes(const char* m){
    f_vte=fopen(nom_fichier_vte, m);
    if(f_vte == NULL){
        printf("erreur lors de l'ouverture du fichier des ventes .Verifiez svp\n");
        exit(1);
    }
}

void fermeture_fichier_ventes(){
    fclose(f_vte);
}

void ajouter_vente(char *matri_vendeur, float *ttc){

  //open the file to add client information
    ouverture_fichier_ventes("a");
    Vente vente;
    strcpy(vente.matricule_vendeur, matri_vendeur);
    vente.montant_vendu = *ttc;
    fprintf(f_vte,"%s %.2f\n", vente.matricule_vendeur, vente.montant_vendu);
    fermeture_fichier_ventes();
}


void lecture_fichier_ventes(Vente ventes[N_MAX_VENTE], int* n){
    //open the file
    ouverture_fichier_ventes("r");
    //printf("Ouverture reussie.\n");

    Vente vente;
	int i=0;
    while (fscanf(f_vte,"%s %f\n", vente.matricule_vendeur, &vente.montant_vendu) != EOF){
        ventes[i] = vente;
        i++;
    }
	*n=i;
    fermeture_fichier_ventes();
}


void afficher_liste_ventes(){

    int i,j,n=0;
    Vente ventes[N_MAX_VENTE];
    lecture_fichier_ventes(ventes, &n);

    if( n == 0){
        printf("\t\tListe des ventes vide");
        exit(0);
    }

    printf("\t\t-----Liste des  Ventes ( nbre vente %d )--------- \n\n", n);
	for(i=0;i<n;i++){
       afficher_vente(ventes[i]);
	}
}

void afficher_vente(Vente vente){
    printf("\t\t--------------------------------------------\n");
    printf("\t\tMatricule Vendeur  : %s\n", vente.matricule_vendeur);
    printf("\t\tMontant Vendu : %.2f FCFA\n", vente.montant_vendu);

}


Bilan_vente_vendeur get_bilan_vente_vendeur(char* matricule_vendeur){

    int i,j,n=0;
    Vente ventes[N_MAX_VENTE];
    lecture_fichier_ventes(ventes, &n);

    float total_ven=0.0, min_vente= 1e34 , max_vente= 0.0;

    if (rechercher_vendeur(matricule_vendeur) == 1){
        Bilan_vente_vendeur bilan_v;
        for(i=0;i<n;i++){
            if(strcmp(ventes[i].matricule_vendeur, matricule_vendeur) == 0){
                strcpy(bilan_v.matricule_vendeur, ventes[i].matricule_vendeur);
                total_ven += ventes[i].montant_vendu;
                if ( ventes[i].montant_vendu < min_vente)
                    min_vente = ventes[i].montant_vendu;

                if ( ventes[i].montant_vendu > max_vente)
                    max_vente = ventes[i].montant_vendu;
            }
        }

        bilan_v.somme_max_vendu = max_vente;
        bilan_v.somme_min_vendu = min_vente;
        bilan_v.somme_total_vendu = total_ven;
        return bilan_v;

    }else{
        printf("Matricule du vendeur %s invalidde. Veullez entre un matricule valide", matricule_vendeur);
        exit(1);
    }
}

float prime_vendeur(float somme_total){
    float prime = 0.0;
    if(somme_total > 200000 ){
        prime = 0.3 * somme_total;
   }else if (somme_total > 100000 && somme_total <=200000) {
        prime = 0.2 * somme_total;
   }else if (somme_total > 100000){
        prime = 0.1 * somme_total;
   }
   return prime;
}


float paiement_vendeur(char* matri_vendeur){
    Bilan_vente_vendeur bilan_vente = get_bilan_vente_vendeur(matri_vendeur);

    float prime=0.0;
    prime = prime_vendeur(bilan_vente.somme_total_vendu);
    float salaire = get_vendeur(matri_vendeur).salaire;
    float paiement = prime + salaire;

    return paiement;
}



