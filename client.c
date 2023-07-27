
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"


//global variable to manipulate stream file
FILE* f = NULL;
char* nom_fichier = "fichier_clients.dat";

void ouverture_fichier(const char* m){
    f=fopen(nom_fichier, m);
    if(f == NULL){
        printf("erreur lors de l'ouverture du fichier client .Verifiez svp\n");
        exit(1);
    }
}

void fermeture_fichier(){
    fclose(f);
}



//CRUD OPERATION
void ajouter_client(){

    //open the file to add client information
    ouverture_fichier("a");
    Client client;
	printf("\n\nVeuillez inserrer les Informations du client.\n");
	printf("Nom: ");
	scanf("%s", client.nom);
    printf("Adresse : ");
    scanf("%s", client.addresse);
    printf("Numero Telephone : ");
    scanf("%s", client.telephone);

    //generate unique client number
    char code_[100] = "id_";
    strncat(code_, client.telephone, 4);
    strcat(code_, "_");
    strncat(code_, client.nom, 3);
    strcpy(client.id, code_);
    //Enregistrement des données saisies dans le fichier
    fprintf(f,"%s %s %s %s\n", client.id, client.nom, client.telephone, client.addresse);
    fermeture_fichier();
}

void ajouter_clients(int n){

    if (n <= 0 ){
        printf("Erreur. Le nombre de client doit etre superieur a 0.");
        exit(1);
    }

    for (int i = 0 ; i < n; i++ ){
        ajouter_client();
    }

    printf("Les information de vos clients ont ete enregistre avec du sucess.\n");

};


void lecture_fichier_clients(Client clients[N_MAX_CLIENT], int* n){
    //open the file
    ouverture_fichier("r");
    //printf("Ouverture reussie\n");

    Client client;
	int i=0;
	while (fscanf(f,"%s %s %s %s\n", client.id, client.nom, client.telephone, client.addresse)!= EOF ){
        clients[i] = client;
        i++;
	}

	*n=i;
    fermeture_fichier();

}

void modifier_info_client(char* id_client){

    int i,j,n;
    Client clients[N_MAX_CLIENT];
    lecture_fichier_clients(clients, &n);

	for(i=0;i<n;i++){
	    if(strcmp(clients[i].id, id_client)==0){
			//printf("client trouve\n");
			j=i;
			break;
        }
	}


	if(i >= n ){
        printf("Id du client Inexistant. Veillez saisir un Id valide");
        exit(1);
	}

    ouverture_fichier("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
	    fprintf(f,"%s %s %s %s\n", clients[i].id, clients[i].nom, clients[i].telephone, clients[i].addresse);
    }

    for(i=j+1;i<n;i++){
     fprintf(f,"%s %s %s %s\n", clients[i].id, clients[i].nom, clients[i].telephone, clients[i].addresse);
	}

    Client client;
	printf("\n\nMise a jour des information du client :  %s \n", clients[j].id);
	printf("Nom: ");
	scanf("%s", client.nom);
    printf("Adresse : ");
    scanf("%s", client.addresse);
    printf("Numero Telephone : ");
    scanf("%s", client.telephone);

    strcpy(client.id, clients[j].id);

    //Enregistrement des données saisies dans le fichier
    fprintf(f,"%s %s %s %s\n", client.id, client.nom, client.telephone, client.addresse);

    printf("Mise a jour du client d'ID  %s reussi.\n", client.id);
    fermeture_fichier();
};


void supprimer_client(char* id_client){
    int i,j,n;
    Client clients[N_MAX_CLIENT];
    lecture_fichier_clients(clients, &n);

	for(i=0;i<n;i++){
	    if(strcmp(clients[i].id, id_client)==0){
			//printf("client trouve\n");
			j=i;
			break;
        }
	}


	if(i >= n ){
        printf("Id du client Inexistant. Veillez saisir un Id valide");
        exit(1);
	}

    ouverture_fichier("w"); //overwritting the curent contains of file

    // suppression des anciennes donnees de l'etudiant dont on veut modifier les donnees
	for(i=0;i<=j-1;i++){
	    fprintf(f,"%s %s %s %s\n", clients[i].id, clients[i].nom, clients[i].telephone, clients[i].addresse);
    }

    for(i=j+1;i<n;i++){
     fprintf(f,"%s %s %s %s\n", clients[i].id, clients[i].nom, clients[i].telephone, clients[i].addresse);
	}

    printf("Suppression du client d'ID  %s reussi.\n", id_client);
    fermeture_fichier();
};


void afficher_info_client(Client client){
        printf("\t\t___________________________________________\n");
        printf("\t\tId client : %s \n", client.id);
        printf("\t\tNom : %s\n", client.nom);
        printf("\t\tAdresse : %s\n", client.addresse);
        printf("\t\tNumero Telephone : %s\n", client.telephone);
        printf("\t\t___________________________________________\n");
}

void afficher_info_clients(){
    int i,j,n=0;
    Client clients[N_MAX_CLIENT];
    lecture_fichier_clients(clients, &n);

    if( n == 0){
        printf("Liste des clients vide");
        exit(1);
    }

    printf("\t\t********  Information des Clients  ************\n");
	for(i=0;i<n;i++){
       afficher_info_client(clients[i]);
	}
}

int rechercher_client(char* id_client){
    int i,j,k,n=0;

    int trouver = 0;

    Client clients[N_MAX_CLIENT];
    lecture_fichier_clients(clients, &n);

    for(i=0;i<n;i++){
	    if(strcmp(clients[i].id, id_client)==0){
			//printf("client trouve\n");
			trouver = 1;
        }
	}
    return trouver;
}

Client get_client(char* id_client){
      int i,j,k,n=0;
    Client clients[N_MAX_CLIENT];
    lecture_fichier_clients(clients, &n);
    for(i=0;i<n;i++){
	    if(strcmp(clients[i].id, id_client) == 0){
			//printf("client trouve\n");
			j = i;
			break;
        }
	}
    return clients[j];
}
