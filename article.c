#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "article.h"

char* nom_fichier_a = "fichier_articles.dat";
FILE* f_a = NULL;

void ouverture_fichier_article(const char* m){
    f_a=fopen(nom_fichier_a, m);
    if(f_a == NULL){
        printf("erreur lors de l'ouverture du fichier articles .Verifiez svp\n");
        exit(1);
    }
}

void fermeture_fichier_article(){
    fclose(f_a);
}

//CRUD OPERATION
void ajouter_article(){
	int qte_stock;
	int qte_seuil;
	float prix_unit;

    //open the file to add client information
    ouverture_fichier_article("a");
    Article article;
	printf("\n\nVeuillez inserrer les Informations!\n");
	printf("Labele : ");
	scanf("%s", article.nom);
    printf("Quantite en stock : ");
    scanf("%d", &qte_stock);
    printf("Quantite Seuil :");
    scanf("%d", &qte_seuil);
    printf("Prix unitaire : ");
    scanf("%f", &prix_unit);

    if (prix_unit <= 0.0){
        printf("Erreur. Le prix unitaire doit etre positif");
        exit(1);
    }

    if (qte_seuil <= 0 ||  qte_stock <= 0){
         printf("Erreur. La quantite en Stock et la quantite seuil doivent etre positif");
        exit(1);
    }

    article.prix_unit = prix_unit;
    article.qte_seuil = qte_seuil;
    article.qte_stock = qte_stock;


    //generate unique article number
    char code_[15] = "a_cod_";
    strncat(code_, article.nom, 4);
    strcpy(article.code, code_);

    //Enregistrement des données saisies dans le fichier
    fprintf(f_a,"%s %s %f %d %d\n", article.code, article.nom, article.prix_unit, article.qte_seuil, article.qte_stock);
    fermeture_fichier_article();

}

void ajouter_articles(int n){

    if (n <= 0 ){
        printf("Erreur. Le nombre d'articles doit etre superieur a 0");
        exit(1);
    }

    for (int i = 0 ; i < n; i++ ){
        ajouter_article();
    }

    printf("Vos articles ont ete enregistre avec du sucess.");
};

void lecture_fichier_articles(Article articles[N_MAX_ARTICLE], int* n){
    //open the file
    ouverture_fichier_article("r");
    //printf("Ouverture reussie.\n");

    Article article;
	int i=0;
    while (fscanf(f_a,"%s %s %f %d %d\n", article.code, article.nom, &article.prix_unit, &article.qte_seuil, &article.qte_stock) != EOF){
        articles[i] = article;
        i++;
    }
	*n=i;
    fermeture_fichier_article();
}

void modifier_info_article(char* code_article){

    int i,j,k,n;
    Article articles[N_MAX_ARTICLE];

    lecture_fichier_articles(articles, &n);

	for(i=0;i<n;i++){
	    if(strcmp(articles[i].code, code_article)==0){
			//printf("article trouve\n");
			j=i;
			break;
        }
	}

	if(i >= n ){
        printf("code de l'artice  Inexistant. Veillez saisir un code dvalide");
        exit(1);
	}

    ouverture_fichier_article("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
	   fprintf(f_a,"%s %s %f %d %d\n", articles[i].code, articles[i].nom, articles[i].prix_unit, articles[i].qte_seuil, articles[i].qte_stock);
    }

    for(i=j+1;i<n;i++){
	   fprintf(f_a,"%s %s %f %d %d\n", articles[i].code, articles[i].nom, articles[i].prix_unit, articles[i].qte_seuil, articles[i].qte_stock);
	}

    Article article;
    int qte_stock = 0;
	int qte_seuil = 0;
	float prix_unit = 0.0;


	printf("\n\nMise a jour des information de l'article :  %s \n", articles[j].code);
	printf("Nom : ");
	scanf("%s", article.nom);
    printf("Quantite en stock : ");
    scanf("%d", &qte_stock);
    printf("Quantite Seuil :");
    scanf("%d", &qte_seuil);
    printf("Prix unitaire : ");
    scanf("%f", &prix_unit);

    if ( prix_unit <= 0.0){
        printf("Erreur. Le prix unitaire doit etre positif");
        exit(1);
    }
    if (qte_seuil <= 0 ||  qte_stock <= 0){
         printf("Erreur. La quantite en Stock et la quantite seuil doivent etre positif");
        exit(1);
    }

    article.prix_unit = prix_unit;
    article.qte_seuil = qte_seuil;
    article.qte_stock = qte_stock;

    strcpy(article.code, articles[j].code);

    //Enregistrement des données saisies dans le fichier
    fprintf(f_a,"%s %s %f %d %d\n", article.code, article.nom, article.prix_unit, article.qte_seuil, article.qte_stock);

    printf("Mise a jour de l'artide  %s reussi.\n", article.code);
    fermeture_fichier_article();
};


void supprimer_article(char* code_article){

    int i,j,k,n;
    Article articles[N_MAX_ARTICLE];

    lecture_fichier_articles(articles, &n);

    for(i=0;i<n;i++){
	    if(strcmp(articles[i].code, code_article)==0){
			//printf("article trouve\n");
			j=i;
			break;
        }
	}


	if(i >= n ){
        printf("code de l'artice  Inexistant. Veillez saisir un code valide.\n");
        exit(1);
	}

    ouverture_fichier_article("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
	   fprintf(f_a,"%s %s %f %d %d\n", articles[i].code, articles[i].nom, articles[i].prix_unit, articles[i].qte_seuil, articles[i].qte_stock);
    }

    for(i=j+1;i<n;i++){
	   fprintf(f_a,"%s %s %f %d %d\n", articles[i].code, articles[i].nom, articles[i].prix_unit, articles[i].qte_seuil, articles[i].qte_stock);
	}

    printf("Suppression de l'article de code %s reussi.\n" , code_article);
    fermeture_fichier_article();
};


void afficher_info_article(Article article){
    printf("\t\t___________________________________________\n");
    printf("\t\tCode Article : %s \n", article.code);
    printf("\t\tNom : %s\n", article.nom);
    printf("\t\tQte Stock : %d\n", article.qte_stock);
    printf("\t\tQte Seuil : %d\n", article.qte_seuil);
    printf("\t\tPrix unitaire : %.2f FCFA\n", article.prix_unit);
    printf("\n");
}



void afficher_info_articles(){
    int i,j,k,n;
    Article articles[N_MAX_ARTICLE];
    lecture_fichier_articles(articles, &n);

    if( n == 0){
        printf("Liste des articles vide.\n");
        exit(0);
    }

    printf("\t\t---- Information Articles  ----\n");
	for(i=0;i<n;i++){
        afficher_info_article(articles[i]);
	}
}

int rechercher_article(char* code_article){
    int i,j,k,n=0;
    int trouver = 0;

    Article articles[N_MAX_ARTICLE];
    lecture_fichier_articles(articles, &n);

    for(i=0;i<n;i++){
	    if(strcmp(articles[i].code, code_article) ==0){
			//printf("article trouve!\n");
			trouver = 1;
        }
	}
    return trouver;
}

Article get_article(char* code_article){
    int i,j,n=0;
    Article articles[N_MAX_ARTICLE];
    lecture_fichier_articles(articles, &n);

    Article article;
    for(i=0;i<n;i++){
	    if(strcmp(articles[i].code, code_article) ==0){
			//printf("article trouve\n");
			j = i ;
			break;
        }
	}

	if (i >= n){
        printf("Code article %s enexistant", code_article);
        exit(1);
	}

    return articles[j];
}

void maj_quantite_stock(char* code_article,int new_qte){
    if (new_qte < 0){
     printf("La quante en stock ne peut pas etre negatif. Veuillez saisir une quantite de stock valide");
     exit(1);
	}

    int i,j,k,n;
    Article articles[N_MAX_ARTICLE];
    lecture_fichier_articles(articles, &n);

	for(i=0;i<n;i++){
	    if(strcmp(articles[i].code, code_article)==0){
			//printf("article trouve\n");
			articles[i].qte_stock = new_qte;
			break;
        }
	}

	if(i >= n ){
        printf("code de l'artice  Inexistant. Veillez saisir un code valide");
        exit(1);
	}

    ouverture_fichier_article("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<n ;i++){
	   fprintf(f_a,"%s %s %f %d %d\n", articles[i].code, articles[i].nom, articles[i].prix_unit, articles[i].qte_seuil, articles[i].qte_stock);
    }

    printf("\t\tMise a jour du stock de l'artide de code ( %s  ) reussi.\n", code_article);
    fermeture_fichier_article();
}


void lecture_fichier_articles_a_approvisionner(Article articles_stock_unsif[N_MAX_ARTICLE], int* m){
    //open the file
    ouverture_fichier_article("r");
    //printf("Ouverture reussie.\n");

    Article article;
	int i=0;
    while (fscanf(f_a,"%s %s %f %d %d\n", article.code, article.nom, &article.prix_unit, &article.qte_seuil, &article.qte_stock) != EOF){
       //find article which stosk is insufficent
       if( article.qte_stock < article.qte_seuil ){
        articles_stock_unsif[i] = article;
        i++;
       }
    }
	*m=i;
    fermeture_fichier_article();
}


void afficher_articles_a_apprivisionner(){

    int n=0;
    Article articles[N_MAX_ARTICLE];
    lecture_fichier_articles(articles, &n);

    if( n == 0){
        printf("\t\tListe des articles vide.");
        exit(0);
    }

    Article articles_appr[N_MAX_ARTICLE];
    int j = 0;
    for (int i = 0 ; i < n ; i++){
        if(articles[i].qte_stock < articles[i].qte_seuil){
            articles_appr[j++] = articles[i];
        }
    }

    if (j == 0 ){
        printf("\t\tAucun article a approsionner.");
        exit(0);
    }

	printf("\t\t -------- Liste des Articles a approvisionner ---------\n\n");
	printf("\t\t-------------------------------------\n");
	for( int i = 0; i < j ; i++ ){
        afficher_article_a_app(articles_appr[i]);
	}
    printf("\t\t-------------------------------------\n\n");

	int choix = 0 ;
	printf("\t\tVoulez-vous augmenter le stock des articles en dessous du seuil\?\n\n");
	printf("\t\t1 : Oui\n");
	printf("\t\t0 : Non\n");
	printf("Entrer votre choix : ");
	scanf("%d", &choix);

	if (choix == 0 ){
        printf("\t\tstocke inchange.\n");
        exit(1);
	}

	if (choix == 1){

	    int ch = 0;
	    printf("\t\t----- choisissez votre mode d'approvisionnent du stock ----\n");
        printf("\t\t1 : Augmentation automatique de 50.\n");
        printf("\t\t2 : Augmentation automatique 100.\n");
        printf("\t\t3 : Augmentation du manuelle.\n");
        printf("Entrer votre choix : ");
        scanf("%d", &ch);

        if (ch == 1 ){
            for (int i = 0 ;i < j ; i++ ){
                maj_quantite_stock(articles_appr[i].code, articles_appr[i].qte_stock + 50);
                printf("\t\tStocke apprivisionner avec succes.\n");
                exit(1);
            }
        }

        if (ch == 2 ){
            for (int i = 0 ;i < j ; i++ ){
                maj_quantite_stock(articles_appr[i].code, articles_appr[i].qte_stock + 100);
                printf("\t\tStocke apprivisionner avec succes.\n");
                exit(1);
            }
        }
        if (ch == 3 ){
            for (int i = 0 ;i < j ; i++ ){
                int qte = 0;
                printf("\t\tEntre la quantite a approvisionner l'article %s :", articles_appr[i].code);
                scanf("%d", &qte);
                if (qte > 0 ){
                    maj_quantite_stock(articles_appr[i].code, articles_appr[i].qte_stock + qte);
                    printf("\t\tstocke apprivisionner avec succes.\n");
                    exit(1);
                }
                printf("\t\tQte saisie incorect.\n");
                exit(1);
            }
        }
	}
}


void afficher_article_a_app(Article article){
    printf("\t\t%s  ---  %s\n", article.code, article.nom);
}

