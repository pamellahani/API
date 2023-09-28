#include <stdio.h>

#include "arbrebin.h"
#include "assert.h"
#include "bfile.h"

/*
Decoder
description: Cette fonction lit chaque caractère du message codé bit par bit et suit le chemin 
correspondant dans l'arbre de Huffman. Lorsqu'il atteint une feuille, il affiche le caractère 
stocké dans cette feuille et retourne à la racine de l'arbre pour commencer à rechercher le 
caractère suivant.
parametres : fichier encode et l'arbre huffman
effet de bord: lecture du fichier encode 

Complexite: O(N) ou n correspond au nombre de bits dans fichier_encode. 
*/
void Decoder(FILE *fichier_encode, Arbre ArbreHuffman) {
    AfficherArbre(ArbreHuffman); 
    Arbre current = ArbreHuffman;  
    BFILE *fichier = bstart(fichier_encode,"r");
    while (!beof(fichier)){
        int bit = bitread(fichier);
            if (current->fg == NULL && current->fd==NULL){
                    //on atteint une feuille, on a donc trouve le caractere du message original. 
                    printf("%c", (unsigned char)current->etiq); 
                    //on retourne ensuite a la racine de l'arbre pour la lettre suivante. 
                    current=ArbreHuffman; 
            }
            if (bit == 0) {
                if(FilsGauche(current)!=NULL)
                    current = current->fg;
            } else {
                if(FilsDroit(current)!=NULL)
                    current = current->fd;
            }
    }
    bstop(fichier);
}

int main(int argc, char *argv[]) {
    FILE *fichier_encode = fopen(argv[1], "r");

    Arbre ArbreHuffman = LireArbre(fichier_encode);

   //AfficherArbre(ArbreHuffman); 

    Decoder(fichier_encode, ArbreHuffman);

    fclose(fichier_encode);

    return 0;
}
