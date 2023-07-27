#define N_MAX_VENTE  200


typedef struct
{
   char matricule_vendeur[50];
   float montant_vendu;
}Vente;

typedef struct
{
   char matricule_vendeur[50];
   float somme_total_vendu;
   float somme_min_vendu;
   float somme_max_vendu;
}Bilan_vente_vendeur;


void ajouter_vente(char *matri_vendeur, float *ttc);
Bilan_vente_vendeur get_bilan_vente_vendeur(char* matricule_vendeur);
void lecture_fichier_ventes(Vente ventes[N_MAX_VENTE], int* n);
float prime_vendeur(float somme_total);
float paiement_vendeur(char* matri_vendeur);
void afficher_vente(Vente vente);
void afficher_liste_ventes();


