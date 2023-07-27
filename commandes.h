#define N_MAX_CMD  100
#define N_MAX_ARTICLE_PAR_CMD 5
#define N_MAX_QTE_CMDE_PAR_ARTICLE 50

typedef struct {
    char code[20];
    int qte;
}Article_cmde;



// Client struct
typedef struct {
	char numero[150];
	char id_client[50];
	char matricule_vendeur[50];
	Article_cmde articles_cmdes[N_MAX_ARTICLE_PAR_CMD];
	int nbre_aticle;
}Commande;


//CRUD OPERATION
void ajouter_commande();
Commande lecture_fichier_commande(char* numero_cmd);
void afficher_info_commande(Commande commande);
void afficher_info_commandes();
void lecture_fichier_commandes(Commande commandes[N_MAX_CMD], int* n);
Commande get_commande(char* numero_cmd);





