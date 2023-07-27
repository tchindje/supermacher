#define N_MAX_ARTICLE  100

// Client struct
typedef struct {
	char code[20];
	char nom[50];
	int qte_stock;
	int qte_seuil;
	float prix_unit;
}Article;


//CRUD OPERATION
void ajouter_article();
void ajouter_articles(int n);
void lecture_fichier_articles(Article articles[N_MAX_ARTICLE], int* n);
void modifier_info_article(char* code_article);
void supprimer_article(char* code_article);
void afficher_info_article(Article article);
void afficher_info_articles();
int rechercher_article(char* code_article);
Article get_article(char* code);
void maj_quantite_stock(char* code_article,int new_qte);
void afficher_articles_a_apprivisionner();

