#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tris.h"
#include <math.h>

#define NMAX 50000 /* peut etre modifie si necessaire */
#define XMAX 50000

// la structure cout nous permet de globaliser les variables qui calculent le cout d'un algo et de 
//sa somme. De ce fait on pourra utiliser ces variables dans plusieurs fonctions sans modifier leur
//valeur
struct _cout{
   int cpt_comp;      //compteur du cout 
   int somme_comp;    //somme de cout (pour calculer la moyenne f_moy)
};
 
typedef struct _cout Cout;

Cout c; 

//comp_sup: 
//donnees: 2 entiers a et b 
//permet d'incrementer le compteur de cout et retourne la condition a>b
int comp_sup(int a, int b)
{
  c.cpt_comp++;
  return a > b;
}

//init_cout: initialisation du compteur dde cout a 0. 
void init_cout()
{
  c.cpt_comp = 0;
}

/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    t[i] = rand();
  };
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n)
{
  int i;
  int x = 0;

  for (i = 0; i < n; i++)
  {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_insertion(int t[], int n)
{
  init_cout();
  int i, j;
  int Clef;

  for (i = 1; i < n; i++){
    Clef = t[i];
    j = i - 1;

    /* Decalage des valeurs du tableau */
    while ((j >= 0) && comp_sup(t[j], Clef)){
      t[j + 1] = t[j];
      j = j - 1;
    }

    /* insertion de la clef */
    t[j + 1] = Clef;
  }
  c.somme_comp += c.cpt_comp;
}

//echange :
//donnees: deux pointeurs a et b 
//echanger 2 valeurs pointes par a et b 
void echange(int *a, int *b){
  int t = *a; 
  *a=*b;
  *b=t; 
}


//partition:
//Donnees: un tableau, indice de depart et indice de fin du tableau t
//Resulltat: cette fonction prend le dernier element comme pivot et le place a la bonne position dans 
// la liste triee. Ensuite elle place tous les elements plus petits que le pivot a la partie gauche 
//de la liste et les elements les plus grands sont places a la droite de la liste. 

int partition(int t[], int first, int last){
  int pivot = t[last]; 
  int i = first -1; //position du pivot trouvee

  //si l'element courant est <= au pivot 
  for (int j = first; j<=last-1;j++){ 
    if(comp_sup(pivot,t[j])){
      i++; 
      echange(&t[i],&t[j]);  
    }
  }
  echange(&t[i+1],&t[last]); 

  //retourne l'indice du pivot 
  return(i+1); 
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_segmentation(int t[], int n){
  //droite = indice de depart de t  
  //gauche = indice de fin de t 
  int droite = n-1; 
  int gauche = 0; 

  //creation d'un tableau auxiliaire ou on stockera le tableau t trie. 
  int t_tmp[n]; 

  //on stocke l'indice de depart de t au debut de t_tmp et on stocke l'indice de fin de t a l'indice
  //d'apres. 
  int elem = 0;  
  t_tmp[elem]= gauche; 
  t_tmp[++elem]= droite; 

  while (elem>=0){
    droite= t_tmp[elem--]; 
    gauche= t_tmp[elem--]; 

    int pivot = partition(t,gauche,droite); 

    if (droite>pivot+1){
     t_tmp[++elem]=pivot+1; 
     t_tmp[++elem]=droite; 
    }

    if(pivot-1 > gauche){
     t_tmp[++elem]=gauche;
     t_tmp[++elem]=pivot-1; 
    }
  }
  c.somme_comp += c.cpt_comp;
}

//moyenne : 
//Donnees: un tableau de reels de taille n>0
//cette fonction renvoi la moyenne de tous les elements du tableau donne en argument. 
double moyenne(double *tab, int taille){
  int moy = 0; 
  int somme = 0; 
    for (int k = 0; k < taille; k++)
  {
    somme += tab[k];
  }
  moy = somme / taille;
  return moy; 
}

//ecart-type
// Donnees:un tableau de reels taille n>0
//renvoi l'ecart type de tous les elements du tableau. 
double ecart_type(double *tab, int taille)
{
  double moy_fmoy = moyenne(tab,taille); 
  double sigma = 0;

  for (int l = 0; l < taille; l++)
  {
    sigma += (tab[l] - moy_fmoy) * (tab[l] - moy_fmoy);
  }

  double ecart_type = (sigma / taille );
  ecart_type = sqrt(ecart_type);
  return ecart_type;
}

//exercice 3

//graph_insertion :
//creation d'un fichier res_insertion.dat qui permettra de generer la courbe de l'evolution du cout 
//moyen de la fonction tri_insertion en fonction de N avec gnuplot. 
void graph_insertion()
{
  FILE *f= fopen ("res_insertion.dat","w"); 
  unsigned int germe = 463; 
  int T[NMAX];
  int N = 0; 
  int X = 5000; 
  double *tab_f = (double *)malloc(sizeof(double) * XMAX); 
  double *tab_fmoy = (double *)malloc(sizeof(double) * XMAX); 
  double fmoy = 0;

  srand(germe);

  while(N<=500){
    for (int i = 0; i < X; i++)
    {
      generation_aleatoire(T, N); /* initialisation du tableau T */
      tri_insertion(T, N);        /* tri de T */
      tab_f[i]=c.cpt_comp;
      c.cpt_comp=0;
    }

    int j =0;
    fmoy = c.somme_comp / X;
    tab_fmoy[j]=fmoy;
    fprintf(f,"%d   %5.1f, %5.1f\n",N,fmoy,ecart_type(tab_fmoy,N));    
    c.somme_comp = 0; 
    fmoy = 0; 
    N = N+50; 
    j++; 
  }
  fclose(f); 
}


//graph segmentation:
//creation d'un fichier res_segmentation.dat qui permettra de generer la courbe de l'evolution du 
//cout moyen de la fonction tri_segmentation en fonction de N avec gnuplot. 
void graph_segmentation(){
FILE *f= fopen ("res_segmentation.dat","w"); 
  unsigned int germe = 463; 
  int T[NMAX];
  int N = 0; 
  int X = 5000; 
  double *tab_f = (double *)malloc(sizeof(double) * XMAX); 
  double *tab_fmoy = (double *)malloc(sizeof(double) * XMAX); 
  double fmoy = 0;

  srand(germe);

  while(N<=500){
    for (int i = 0; i < X; i++)
    {
      generation_aleatoire(T, N); /* initialisation du tableau T */
      tri_segmentation(T, N);        /* tri de T */
      tab_f[i]=c.cpt_comp;
      c.cpt_comp=0;
    }

    int j = 0; 
    fmoy = c.somme_comp / X;
    tab_fmoy[j]=fmoy; 
    fprintf(f,"%d   %5.1f, %5.1f\n",N,fmoy,ecart_type(tab_fmoy,N));  
    c.somme_comp = 0; 
    fmoy = 0; 
    N=N+50;
    j++;
  }
  fclose(f); 
}

//exercice 2

//lancer_mesures:
//cette fonction permet de demander a l'utilisateur les valeurs de la germe ainsi que 
//N,X et Y et affiche sur la sortie standard pour chaque Y, la valeur de fmoy et 
//l'ecart type des Y valeurs de fmoy 
void lancer_mesures(){
  unsigned int germe; 
  int T[NMAX];
  int N = 500; 
  int res = 1;
  int X;
  double *tab_fmoy = (double *)malloc(sizeof(double) * XMAX);
  double *tab_f = (double *)malloc(sizeof(double) * XMAX);
  int Y; 
  double fmoy = 0;

  printf("Valeur du germe pour la fonction de tirage aleatoire ? ");
  res = scanf("%d", &germe);
  assert(res == 1);
  srand(germe);

  do
  {
    printf("Valeur de N ? ");
    res = scanf("%d", &N);
    assert(res == 1);
  } while (N < 1 || N > NMAX);

  do
  {
    printf("Valeur de X ?");
    res = scanf("%d", &X);
    assert(res == 1);
  } while (X < 1 || X > XMAX);

  do
  {
    printf("Valeur de Y ?");
    res = scanf("%d", &Y);
    assert(res == 1);
  } while (Y < 1 || Y > XMAX);
  
  for (int j = 0; j<Y; j++){
    for (int i = 0; i < X; i++)
    {
      generation_aleatoire(T, N); /* initialisation du tableau T */
      tri_segmentation(T, N);        /* tri de T */
      tab_f[i]=c.cpt_comp;
      c.cpt_comp=0;
    }

    fmoy = c.somme_comp / X;
    printf("Y=%d   fmoy=%f\n",j,fmoy);  
    c.somme_comp = 0;
    tab_fmoy[j] = fmoy;
    printf("\n"); 
  }
  double ecart = ecart_type(tab_fmoy, Y);
  printf("ecart type des Y valeurs de fmoy = %f\n", ecart);

}


