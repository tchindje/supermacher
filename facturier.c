#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandes.h"
#include "client.h"
#include "vendeur.h"
#include "article.h"

#define TVA  0.10

void etablir_facture(char* num_cmd){

    Commande commande = lecture_fichier_commande(num_cmd);
    Vendeur vendeur = get_vendeur(commande.matricule_vendeur);
    Client client = get_client(commande.id_client);
    float ttc = 0.0;

    int nbr_article = commande.nbre_aticle;

    //afficher_info_commande(commande);


    //get list  (code, qte) of article commande
    Article_cmde art_cmdes[nbr_article];
    for (int i = 0 ; i < nbr_article; i++){
        strcpy(art_cmdes[i].code , commande.articles_cmdes[i].code);
        art_cmdes[i].qte = commande.articles_cmdes[i].qte;
    }


    //get list of artiles in command
     Article articles_cmdes[nbr_article];

     for (int i = 0 ; i < nbr_article; i++){
        articles_cmdes[i] = get_article(art_cmdes[i].code);
    }

    // check if articles is avallable
    int article_est_dispo[nbr_article];
    int j = 0;
     for (int i = 0 ; i < nbr_article; i++){
            if( art_cmdes[i].qte <= articles_cmdes[i].qte_stock){
                article_est_dispo[i] = 1;  //article est en stock
            }else{
                article_est_dispo[i] = 0;
            }
    }



    printf("\t\t Edition Facture de la  commande : %s \n\n", num_cmd);

    printf("\t\t------------------------------------\n\n");
    printf("\t\t -----  Info du Client ----\n");
    afficher_info_client(client);

    printf("\n");
    printf("\t\t ---- Produits commandes ----\n");

    printf("\t\t________________________________________________________________________\n");
    printf("\n\t\t|   Code    |  Designation  | Qte |  Prix Unit  | Prix Total | Statut |\n");
    printf("\t\t________________________________________________________________________\n");

    float somme_total = 0.0;
    for(int i =0 ; i < nbr_article; i++){
        if( article_est_dispo[i] == 1){
            somme_total += articles_cmdes[i].prix_unit*art_cmdes[i].qte;
            printf("\t\t| %s | %s |   %d   |  %.2f  |  %.2f |  %s |\n", art_cmdes[i].code, articles_cmdes[i].nom, art_cmdes[i].qte, articles_cmdes[i].prix_unit, articles_cmdes[i].prix_unit*art_cmdes[i].qte, article_est_dispo[i]==1 ? "en stock" : "pas en Stock");
            printf("\t\t________________________________________________________________________\n");

        }
    }


    printf("\n\t\t----------------------------------------------------\n");
    printf("\n\t\t Montant Total des article en stock  : %2.f  FCFA      TVA :  %.2f\n", somme_total, TVA);
    printf("\n\t\t-----------------------------------------------------\n");


    ttc = (TVA + 1.0)*somme_total;
    printf("\n\t\t Montant Total Taxe Comprise  : %.2f  FCFA\n", ttc);
    printf("\n\t\t------------------------------------------------\n\n");

    printf("\t\tMatricule vendeur : %s      Nom  Vendeur : %s\n", vendeur.matricule, vendeur.nom);
    printf("\n\t\t---------------------------------------------------\n");


    int choix = 0;
    printf("\n\n\t\t1 : Pour valider la facture ( Effectuer la vente)\n");
    printf("\t\t0 : pour annuler la facture\n\n");
    printf("\nEntre votre choix : ");

    scanf("%d", &choix);
    if(choix == 0){
        printf("\t\tLa facture a ete annule avec success.");
        exit(1);
    }
    if (choix ==1){

        // destockage of articles sale
        for(int j = 0 ; j < nbr_article; j++ ){
            if (article_est_dispo[j] == 1){
                maj_quantite_stock(articles_cmdes[j].code, articles_cmdes[j].qte_stock - art_cmdes[j].qte);
            }
        }

        //enregistrer la vente : matri_ven
        ajouter_vente(vendeur.matricule, &ttc);
        printf("\t\tFacture valide avec succes.\n");
    }
}
