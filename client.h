

#define N_MAX_CLIENT  100

// Client struct
typedef struct {
	char id[20];
	char nom[50];
	char telephone[50];
	char addresse[50];
}Client;




//CRUD OPERATION
void ajouter_client();
void ajouter_clients(int n);
void lecture_fichier_clients(Client clients[N_MAX_CLIENT],int* n); // read file and insert into tab
void modifier_info_client(char* id_client);
void supprimer_client(char* id_client);
void afficher_info_client(Client client);
void afficher_info_clients();
int rechercher_client(char* id_client);
Client get_client(char* id_client);
