
#include "arbrebin.h"
#include "bfile.h"
#include "fap.h"
#include "huffman_code.h"
#include <assert.h>
#include <stdio.h>

typedef struct {
    int tab[256];
} TableOcc_t;

struct code_char HuffmanCode[256];

/*
ConstruireTableOcc
description: construction d'une table d'occurences des caracteres a partir d'un fichier txt
on parcours le fichier a encoder et on incremente TabOcc->tab a la position ou se trouve le caractere
lu.  
effet de bord: modification de la table d'occurences TableOcc. 
Complexite: O(n)ou n correspond au nombre de caraccteres dans le fichier txt. 
*/
void ConstruireTableOcc(FILE *fichier, TableOcc_t *TableOcc) {

    //mettre toutes les occurences a 0
    for (int i = 0; i<256; i++){
        TableOcc->tab[i]=0;
    }

    int c;
    c = fgetc(fichier);
    while (c != EOF) {
        if (TableOcc->tab[c]==0){
            TableOcc->tab[c]=1; 
        }
        else{
            TableOcc->tab[c]++; 
        }
        c = fgetc(fichier); 
    }
    int i;
    for (i = 0; i < 256; i++) {
        if (TableOcc->tab[i] != 0)
            printf("Occurences du caractere %c (code %d) : %d\n", i, i,
                   TableOcc->tab[i]);
    }

}

/*
InitHuffman
descriptionin :initialisation d'une file a priorite a partir de la table d'occurence.  
valeur de retour: file a priorite contenant le nombre d'occurences des caracteres dans le texte. 
effet de bord: aucun
Complexite: O(n log n) où n est le nombre de caractères dans la table qui ont une occurrence 
différente de zéro.
*/ 
fap InitHuffman(TableOcc_t *TableOcc) {
    fap new_fap = creer_fap_vide(); 
    for (int i = 0; i<256; i++){
        if (TableOcc->tab[i]!=0){                                       //O(1)
            Arbre a = NouveauNoeud(ArbreVide(),(char)i,ArbreVide());    //O(n*log(n))
            new_fap = inserer(new_fap,a,TableOcc->tab[i]);
      }
    }
    return new_fap;
}

/*
ConstruireArbre 
description: Cette fonction construit l'arbre de Huffman a partir de la file a priorite. On commence
avec les deux caracteres les moins occurents, on les extrait et on les relie par un nouveau noeud dont sa 
priorite est la somme des 2 nombres. on insere ensuite ce nouveau noeud dans la fap. 
parametres : file a priorite contenant le nombre d'occurences des caracteres
effet de bord: modification de la fap.
valeur de retour: Arbre de Huffman. 
Complexite: O((n-1) log n) (n = nombre d'elements presents dans la file a priorite)
*/
Arbre ConstruireArbre(fap file) {
    Arbre new_arbre = ArbreVide(); 
    Arbre element1 = ArbreVide(); 
    Arbre element2 =  ArbreVide(); 
    int priorite1;
    int priorite2; 
    while (file->prochain){ //cette boucle est iteree n-1 fois 
        file=extraire(file,&element1,&priorite1);
        file=extraire(file,&element2,&priorite2); 
        new_arbre = NouveauNoeud(element1,' ',element2); 
        file = inserer(file,new_arbre,priorite1+priorite2); 
    }
    return new_arbre; 
}

/*
ConstruireCoderec
description: fonction auxiliaire de ConstruireCode
Complexite: O(n) ou n correspond au nombre de noeuds dans l'arbre donnee en parametres
*/
void ConstruireCode_rec(Arbre huff, int code[], int longueur){
     if (EstVide(FilsGauche(huff)) && EstVide(FilsDroit(huff))){
        HuffmanCode[huff->etiq].lg = longueur;
        for (int i = 0; i < longueur; i++){
            HuffmanCode[huff->etiq].code[i] = code[i];
        }
    }
    else{
        if (huff->fg!=NULL){
            code[longueur] = 0;
            ConstruireCode_rec(FilsGauche(huff), code, longueur+1);
        }
        if (huff->fd!=NULL){
            code[longueur] = 1;
            ConstruireCode_rec(FilsDroit(huff), code, longueur+1);
        }
    }
}

/*
ConstruireCode
description: fonction qui associe a chaque caractere du texte, un code binaire a partir de l'arbre 
de Huffman donnee en parametre. 
effet de bord: Modification du tableau HuffmanCode. 
Complexite: O(n) ou n correspond au nombre de noeuds dans l'arbre donnee en parametres
*/
void ConstruireCode(Arbre huff) {
    int code [256]; 
    ConstruireCode_rec(huff,code,0); 
}

/*
Encoder
description: encodage du fichier d'entrée en remplaçant chaque caractère par son code Huffman 
correspondant. L'arbre de Huffman est également écrit dans le fichier de sortie afin que
l'algorithme de décompression puisse reconstruire l'arbre et l'utiliser pour décoder le fichier encodé.
effet de bord: ecriture dans le fichier fic_out. 
Complexite: O(n) ou n correspond au nombre de caracteres dans le fichier fic_in
*/
void Encoder(FILE *fic_in, FILE *fic_out, Arbre ArbreHuffman) {  
    EcrireArbre(fic_out,ArbreHuffman);
    BFILE *fichier = bstart(fic_out,"w"); 
    int taille; 
    char c; 
    int* code; 
    //on recupere chaque lettre et obtenir son code du tableau HuffmanCode 
    while ((c = fgetc(fic_in))!=EOF)
    {  
        taille = HuffmanCode[(unsigned char)c].lg; 
        code = HuffmanCode[(unsigned char)c].code; 
        for (int i = 0; i<taille;i++){
            bitwrite(fichier,code[i]); 
        } 
    }
    bstop(fichier); 
}

int main(int argc, char *argv[]) {

    TableOcc_t TableOcc;
    FILE *fichier;
    FILE *fichier_encode;

    fichier = fopen(argv[1], "r");
    /* Construire la table d'occurences */
    ConstruireTableOcc(fichier, &TableOcc);
    fclose(fichier);

    /* Initialiser la FAP */
    fap file = InitHuffman(&TableOcc);

    /* Construire l'arbre d'Huffman */
    Arbre ArbreHuffman = ConstruireArbre(file);

        AfficherArbre(ArbreHuffman);

    /* Construire la table de codage */
    ConstruireCode(ArbreHuffman);
    
    /* Encodage */
    fichier = fopen(argv[1], "r");
    fichier_encode = fopen(argv[2], "w");

    Encoder(fichier, fichier_encode, ArbreHuffman);

    fclose(fichier_encode);
    fclose(fichier);

    return 0;
}
