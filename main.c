#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "article.h"
#include "vendeur.h"
#include "commandes.h"
#include "facturier.h"
#include "vente.h"

int main(void){


    int choix_menu;

    do {
        system("cls");
        printf("\n\n\n");
        printf("\t**************************************************************************\n");
        printf("\t\t ItGestMarket Votre Programme de Gestion du SuperMarche DOVV \n\n");
        printf("\t**************************************************************************\n");

        printf("\n\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t0  :   Quiter le programme\n");
        printf("\t\t1  :   Gestion des Articles\n");
        printf("\t\t2  :   Gestion des Clients\n");
        printf("\t\t3  :   Gestion des Vendeurs\n");
        printf("\t\t4  :   Gestion des Commandes\n");
        printf("\t\t5  :   Gestion des Ventes et paiements Vendeurs\n");
        printf("\t\t-------------------------------------\n");

        printf("\nEntrer votre choix : ");
        scanf("%d", &choix_menu);

        int choix = 0 ;

        if (choix_menu == 1 ){
            do{
                printf("\n\n\n");
                printf("\t\t********* Gestion  Articles *********\n");
                printf("\t\t-------------------------------------\n");
                printf("\t\t1 :  Afficher articles\n");
                printf("\t\t2 :  Ajouter articles\n");
                printf("\t\t3 :  Modifier article\n");
                printf("\t\t4 :  Supprimer article\n");
                printf("\t\t5 :  Rechercher article\n");
                printf("\t\t6 :  Liste  articles a approvisionner\n");
                printf("\t\t0 :  Quitter la gestion des articles!\n");
                printf("\t\t-------------------------------------\n");

                printf("\nEntrer votre choix : ");
                scanf("%d",&choix);

                switch(choix){

                case 0 : break;

                case 1 : {
                    system("cls");
                    afficher_info_articles(); break;
                }

                case 2 : {
                    system("cls");
                    int n = 0;
                    printf("Entrer le nombre d'article a ajouter :");
                    scanf("%d",&n);
                    ajouter_articles(n);
                    break;

                }

                case 3 : {
                    system("cls");
                    char code_article[15];
                    printf("Entrer le code de l'article a modifier : ");
                    scanf("%s", code_article);
                    modifier_info_article(code_article);
                    break;
                }

                case 4 : {
                    system("cls");
                    char code_article[15];
                    printf("Entrer le code de l'article a supprimer :");
                    scanf("%s", code_article);
                    supprimer_article(code_article);
                    break;
                }

                case 5 : {
                   system("cls");
                    char code_article[15];
                    printf("Entrer le code de l'article a rechercher :");
                    scanf("%s", code_article);
                    int statut =  rechercher_article(code_article);
                    if (statut == 1 ){
                        Article article = get_article(code_article);
                        afficher_info_article(article);
                    }
                    else{
                        printf("Article n'existe pas. Veuillez saisir un code valide!\n");
                    }
                    break;
                }

                case 6 :{
                    system("cls");
                    afficher_articles_a_apprivisionner();
                    break;
                }

            }

        }while(choix != 0);

    }//end if

     if ( choix_menu == 2 ){

        do {
            printf("\n\n\n");
            printf("\t\t********* Gestion  Clients *********\n");
            printf("\t\t-------------------------------------\n");
            printf("\t\t0 :  Quitter la gestion des clients!\n");
            printf("\t\t1 :  Afficher Info clients\n");
            printf("\t\t2 :  Ajouter clients\n");
            printf("\t\t3 :  Modifier client\n");
            printf("\t\t4 :  Supprimer client\n");
            printf("\t\t5 :  Rechercher client\n");
            printf("\t\t-------------------------------------\n");

            printf("\nEntrer votre choix : ");
            scanf("%d",&choix);

            switch(choix){

                case 0 : break;

                case 1 : {
                    system("cls");
                    afficher_info_clients(); break;
                }

                case 2 : {
                    system("cls");
                    int n = 0;
                    printf("Entrer le nombre de client a ajouter :");
                    scanf("%d",&n);
                    ajouter_clients(n);
                    break;
                }

                case 3 : {
                    system("cls");
                    char id_client[15];
                    printf("Entrer le ID du client a modifier : ");
                    scanf("%s", id_client);
                    modifier_info_client(id_client);
                    break;
                }

                case 4 : {
                    system("cls");
                    char id_client[15];
                    printf("Entrer le ID du client a supprimer : ");
                    scanf("%s", id_client);
                    supprimer_client(id_client);
                    break;
                }

                case 5 : {
                   system("cls");
                    char id_client[15];
                    printf("Entrer le code du client  a rechercher :");
                    scanf("%s", id_client);
                    int statut =  rechercher_client(id_client);
                    if (statut == 1 ){
                        Client client = get_client(id_client);
                        afficher_info_client(client);
                    }
                    else{
                        printf("Client n'existe pas. Veuillez saisir ID valide!\n");
                    }
                    break;
                }
            }

        }while(choix != 0);

     }

      if ( choix_menu == 3 ){

        do {
            printf("\n\n\n");
            printf("\t\t********* Gestion  Vendeurs *********\n");
            printf("\t\t-------------------------------------\n");
            printf("\t\t0 :  Quitter la gestion des vendeurs!\n");
            printf("\t\t1 :  Afficher Info vendeurs\n");
            printf("\t\t2 :  Ajouter vendeurs\n");
            printf("\t\t3 :  Modifier vendeur\n");
            printf("\t\t4 :  Supprimer vendeur\n");
            printf("\t\t5 :  Rechercher vendeur\n");
            printf("\t\t-------------------------------------\n");

            printf("\nEntrer votre choix : ");
            scanf("%d",&choix);

            switch(choix){

                case 0 : break;

                case 1 : {
                    system("cls");
                    afficher_info_vendeurs(); break;
                }

                case 2 : {
                    system("cls");
                    int n = 0;
                    printf("Entrer le nombre de vendeur a ajouter :");
                    scanf("%d",&n);
                    ajouter_vendeurs(n);
                    break;
                }

                case 3 : {
                    system("cls");
                    char mat_vend[15];
                    printf("Entrer le matricule du vendeur a modifier : ");
                    scanf("%s", mat_vend);
                    modifier_info_vendeur(mat_vend);
                    break;
                }

                case 4 : {
                    system("cls");
                    char mat_vend[15];
                    printf("Entrer le matricule du vendeur a supprimer : ");
                    scanf("%s", mat_vend);
                    supprimer_vendeur(mat_vend);
                    break;
                }

                case 5 : {
                   system("cls");
                    char mat_vend[15];
                    printf("Entrer le code du vendeur  a rechercher :");
                    scanf("%s", mat_vend);
                    int statut =  rechercher_vendeur(mat_vend);
                    if (statut == 1 ){
                        Vendeur vendeur = get_vendeur(mat_vend);
                        afficher_info_vendeur(vendeur);
                    }
                    else{
                        printf("Vendeur n'existe pas. Veuillez saisir un matricule valide!\n");
                    }
                    break;
                }
            }

        }while(choix != 0);

     }

       if ( choix_menu == 4 ){

        do {
            printf("\n\n\n");
            printf("\t\t********* Gestion  Commandes *********\n");
            printf("\t\t-------------------------------------\n");
            printf("\t\t0 :  Quitter la gestion des commandes!\n");
            printf("\t\t1 :  Afficher liste des commandes\n");
            printf("\t\t2 :  Afficher detail commande\n");
            printf("\t\t3 :  Ajouter une commande\n");
            printf("\t\t4 :  Etablir Facture\n");
            printf("\t\t-------------------------------------\n");

            printf("\nEntrer votre choix : ");
            scanf("%d",&choix);

            switch(choix){

                case 0 : break;

                case 1 : {
                    system("cls");
                    afficher_info_commandes(); break;
                }

                case 2 : {
                    system("cls");
                    char numero_cmd[120];
                    printf("Entrer le numero de la commande a afficher:");
                    scanf("%s",numero_cmd);
                    Commande commande = get_commande(numero_cmd);
                    afficher_info_commande(commande);
                    break;
                }

                case 3 : {
                    system("cls");
                    ajouter_commande();
                    break;
                }


                case 4 : {
                    system("cls");
                    char num_cmd[100];
                    printf("Entrer le numero de la commande a etablir la facture :");
                    scanf("%s",num_cmd);
                    etablir_facture(num_cmd);
                    break;
                }
            }

        }while(choix != 0);

     }

      if ( choix_menu == 5 ){

        do {
            printf("\n\n\n");
            printf("\t\t********* Gestion  Ventes et Paiements *********\n");
            printf("\t\t-------------------------------------\n");
            printf("\t\t0 :  Quitter la gestion des ventes et paiements!\n");
            printf("\t\t1 :  Afficher liste des ventes\n");
            printf("\t\t2 :  Calculer  la paye d'un vendeur\n");
            printf("\t\t-------------------------------------\n");

            printf("\nEntrer votre choix : ");
            scanf("%d",&choix);

            switch(choix){

                case 0 : break;

                case 1 : {
                    system("cls");
                    afficher_liste_ventes(); break;
                }

                case 2 : {
                    system("cls");
                    char matri_vend[120];
                    printf("Entrer le matricule du vendeur :");
                    scanf("%s",matri_vend);

                    Vendeur vendeur =  get_vendeur(matri_vend);
                    Bilan_vente_vendeur bilan_vente = get_bilan_vente_vendeur(matri_vend);

                    afficher_info_vendeur(vendeur);
                    printf("\n");
                    printf("\t\t--------------------------------------\n");
                    printf("\t\tSomme Max vendue : %.2f FCFA\n", bilan_vente.somme_max_vendu);
                    printf("\t\tSomme Min vendue : %.2f FCFA\n", bilan_vente.somme_min_vendu);
                    printf("\t\tSomme Totale vendue : %.2f FCFA\n", bilan_vente.somme_total_vendu);
                    printf("\t\t--------------------------------------\n");
                    float prime = prime_vendeur(bilan_vente.somme_total_vendu);
                    printf("\t\tPrime :  %.2f FCFA\n", prime);
                    printf("\t\t--------------------------------------\n");
                    printf("\t\tTOTAL Paiement Vendeur : %.2f FCFA\n", (prime+vendeur.salaire));
                    printf("\t\t--------------------------------------\n");
                    break;
                }
            }

        }while(choix != 0);

     }

    } while (choix_menu != 0);

    return 0;

}
