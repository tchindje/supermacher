#define N_MAX_VENDEUR  100

// Client struct
typedef struct {
	char matricule[20];
	char nom[50];
	char addresse[50];
	float salaire;
}Vendeur;




//CRUD OPERATION
void ajouter_vendeur();
void ajouter_vendeurs(int n);
void lecture_fichier_vendeurs(Vendeur vendeurs[N_MAX_VENDEUR],int* n); // read file and inssert into tab
void modifier_info_vendeur(char* matricule);
void supprimer_vendeur(char* matricule);
void afficher_info_vendeur(Vendeur vendeur);
void afficher_info_vendeurs();
int rechercher_vendeur(char* matricule_v);
Vendeur get_vendeur(char* matricule_v);
