#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandes.h"
#include "client.h"
#include "vendeur.h"
#include "article.h"


char* nom_fichier_cmd = "fichier_commandes.dat";
FILE* f_cmd = NULL;

void ouverture_fichier_cmd(const char* m){

    f_cmd=fopen(nom_fichier_cmd, m);
    if(f_cmd == NULL){
        printf("erreur lors de l'ouverture du fichier des commandes .Verifiez svp\n");
        exit(1);
    }
    return;
}



void fermeture_fichier_cmd(){
    fclose(f_cmd);
}

//CRUD OPERATION
void ajouter_commande(){

    char id_client[50];
    printf("Entre le ID du client : ");
    scanf("%s", id_client);
    int test_existance_client =  rechercher_client(id_client);

    if(test_existance_client == 0){
        printf("Client avec le ID %s Inexistant. Veuillez saisir un id client valide.", id_client);
        exit(1);
    }

    char matricule_vendeur[40];
    printf("Entre le matricule du vendeur : ");
    scanf("%s", matricule_vendeur);

    int test_existance_vendeur =  rechercher_vendeur(matricule_vendeur);

    if(test_existance_vendeur == 0){
        printf("Vendeur avec le matricle %s Inexistant. Veuillez saisir un matricule valide.", matricule_vendeur);
        exit(1);
    }

    int nbre_article = 0;
    do {
        printf("Combien d'article Souhaitez-vous commande (entre 1 a 5)\? : ");
        scanf("%d", &nbre_article);

        if (nbre_article > N_MAX_ARTICLE_PAR_CMD ){
            printf("Nombre d'artice doit etre inferieur ou egal a %d", N_MAX_ARTICLE_PAR_CMD);
        }
         if (nbre_article <= 0 ){
            printf("Nombre d'artice doit etre strictement positif");
        }
    }while(nbre_article > N_MAX_ARTICLE_PAR_CMD || nbre_article <= 0 );


    Article_cmde art_cmd[nbre_article];
    for( int i = 0 ; i < nbre_article; i++){
        printf("Entrer le code de l'article %d :", i+1);
        scanf("%s", art_cmd[i].code );
        // test if code article is present
        int test_existance_article =  rechercher_article(art_cmd[i].code);
        if(test_existance_article == 0){
            printf("code article inexistant.");
            exit(1);
        }
        do {
            printf("Entrer la quantite de l'artice %d :", i+1);
            scanf("%d", &art_cmd[i].qte);

            if (art_cmd[i].qte > N_MAX_QTE_CMDE_PAR_ARTICLE){
                 printf("La Quantite pour chaque article doit etre inferieur ou egal a %d", N_MAX_QTE_CMDE_PAR_ARTICLE);
            }

            if (art_cmd[i].qte <= 0){
                 printf("La Quantite pour chaque article doit etre strictement positif.");
            }

        }while(art_cmd[i].qte > N_MAX_QTE_CMDE_PAR_ARTICLE || art_cmd[i].qte <= 0 );
    }

    Commande commande;
    //generate unique commande number
    char code_[150] = "cmd_";
    strcat(code_, matricule_vendeur);
    strcat(code_, "_");
    strcat(code_, id_client);

    //copy information into the command type
    strcpy(commande.id_client, id_client);
    strcpy(commande.matricule_vendeur, matricule_vendeur);
    strcpy(commande.numero, code_);
    commande.nbre_aticle = nbre_article;

    for(int i =0 ; i < nbre_article; i++){
        strcpy(commande.articles_cmdes[i].code, art_cmd[i].code);
        commande.articles_cmdes[i].qte  = art_cmd[i].qte;
    }

    ouverture_fichier_cmd("a");
    //Enregistrement des données saisies dans le fichier

    for(int i =0 ; i < nbre_article; i++){
        fprintf(f_cmd,"%s %s %s %d %s %d\n", commande.numero, id_client, commande.matricule_vendeur, commande.nbre_aticle, commande.articles_cmdes[i].code,commande.articles_cmdes[i].qte);
    }

    printf("Commande enrigistree avec success.\n");
    fermeture_fichier_cmd();
}



void lecture_fichier_commandes(Commande commandes[N_MAX_CMD], int* n){
    //open the file
    ouverture_fichier_cmd("r");
    //printf("Ouverture reussie\n");

    Commande commande;
	int i=0;
    while (fscanf(f_cmd,"%s %s %s %d %s %d\n", commande.numero, commande.id_client, commande.matricule_vendeur, &commande.nbre_aticle, commande.articles_cmdes[i].code, &commande.articles_cmdes[i].qte) != EOF){
        commandes[i] = commande;
        i++;
	}

	*n=i;
    fermeture_fichier_cmd();

}


Commande lecture_fichier_commande(char* numero_cmd ){

    ouverture_fichier_cmd("r");
    //printf("Ouverture reussie.\n");

    Article_cmde art_cmdes[N_MAX_QTE_CMDE_PAR_ARTICLE];

    Commande commande_;
    Commande commande;
    int i=0;
    while (fscanf(f_cmd,"%s %s %s %d %s %d\n", commande.numero, commande.id_client, commande.matricule_vendeur, &commande.nbre_aticle, commande.articles_cmdes[i].code, &commande.articles_cmdes[i].qte) != EOF){
        if( strcmp(commande.numero, numero_cmd) == 0){
            strcpy(commande_.numero, numero_cmd);
            strcpy(commande_.id_client, commande.id_client);
            commande_.nbre_aticle = commande.nbre_aticle;
            strcpy(commande_.matricule_vendeur , commande.matricule_vendeur);
            strcpy(art_cmdes[i].code , commande.articles_cmdes[i].code);
            art_cmdes[i].qte = commande.articles_cmdes[i].qte;
            i++;
        }
    }

    if (i == 0 ){
        printf("Numemro de commande introuvable. Veillez entre un numero valid.\n");
        exit(1);
    }

    for(int j = 0; j <i ; j++){
            strcpy(commande_.articles_cmdes[j].code,  art_cmdes[j].code);
            commande_.articles_cmdes[j].qte = art_cmdes[j].qte;
    }

    fermeture_fichier_cmd();
    return commande_;
}


Commande get_commande(char* numero_cmd){
    int i,j,k,n=0;
    Commande commandes[N_MAX_CMD];
    lecture_fichier_commandes(commandes, &n);
    for(i=0;i<n;i++){
	    if(strcmp(commandes[i].numero, numero_cmd) ==0){
			//printf("commade  trouve\n");
			j = i;
			break;
        }
	}
	if (i >= n ){
        printf("commande avec le numero %s inexistant", numero_cmd);
        exit(1);
	}
    return commandes[j];
}



void afficher_info_commande(Commande commande){
    printf("\n\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\tNumero commande : %s \n", commande.numero);
    printf("\t\tMatricule vendeur : %s\n", commande.matricule_vendeur);
    printf("\t\tID client : %s\n", commande.id_client);
    printf("\t\tNombre article cmde : %d\n", commande.nbre_aticle);
    for (int i = 0 ; i < commande.nbre_aticle; i++){
        printf("\t\tCode Article : %s\n", commande.articles_cmdes[i].code);
        printf("\t\tqte : %d\n", commande.articles_cmdes[i].qte);
    }
    printf("\t\t-----------------------------------------------\n");
}


void afficher_info_commandes(){
    int i,j,n=0;
    Commande commandes[N_MAX_CMD];
    lecture_fichier_commandes(commandes, &n);

    if( n == 0){
        printf("t\tListe des commandes vide.\n");
        exit(0);
    }

    printf("\t\t------ Liste des Commandes ( nbre commande : %d )-----\n", n);
	for(i=0;i<n;i++){
       afficher_info_commande(commandes[i]);
	}

}
