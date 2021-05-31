/*!
\file main.c
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 15 janvier 2021
\brief Programme d'un jeu de Dames sur console / Test IA sur un jeu de dames / programme non fini
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headerD.h"




/*!
\fn void initialiser(enum case plateau[N][N])
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 3 mai 2021
\brief initialise le plateau de jeu 
\param plateau[N][N] plateau de jeu dans une variable personnalisee
*/

void initialiser(enum case plateau[N][N], struct joueur joueur)
{
    do{
        int choix;
        printf("Voulez vous jouer les blancs (ils commencent) ou les noirs ? Blanc:1, Noir:2");
        scanf("%d", choix);
        if(choix != 1 && choix != 2){
            printf("Faites attention ! Choisisser bien, Blanc;1, Noir:2.");
        }
        else{
            if(choix == 1){
                joueur.humain = pions_blancs;
                joueur.machine = pions_noirs
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        if(i%2 == 0 && j%2 ==0){
                            plateau[i][j] = caseBlanche;
                        }
                        else{
                            if(i>=0 && i<=3){
                                plateau[i][j] = pionNoir;
                            }
                            else if(i==4 || i == 5){
                                plateau[i][j] = caseNoire;
                            }
                            else if(i>=6 && i <=9){
                                plateau[i][j] = pionBlanc
                            }
                        }
                        
                    }
                }
            }
            else{
                joueur.humain = pions_noirs;
                joueur.machine = pions_blancs;
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        if(i%2 == 0 && j%2 ==0){
                            plateau[i][j] = caseBlanche;
                        }
                        else{
                            if(i>=0 && i<=3){
                                plateau[i][j] = pionBlanc;
                            }
                            else if(i==4 || i == 5){
                                plateau[i][j] = caseNoire;
                            }
                            else if(i>=6 && i <=9){
                                plateau[i][j] = pionNoir;
                            }
                        }
                        
                    }
                }
            }
        }
    }while(choix != 1 && choix != 2);
    
}


/*!
\fn void afficher(enum pion plateau[N][N])
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 4 mai 2021
\brief affiche le plateau dans la console 
\param plateau[N][N] plateau de jeu dans une variable personnalisee
*/

void afficher(enum case plateau[N][N])
{
    printf(" |0 |1 |2 |3 |4 |5 |6 |7 |8 |9");
    for(int i = 0; i < N; i++){
        printf(" +--+--+--+--+--+--+--+--+--+--+\n");
        printf("%d", i);
        for(int j = 0; j < N; j++){
            printf("|");
            if(plateau[i][j] == caseBlanche){
                printf("  ");
            }
            else if(plateau[i][j] == caseNoire){
                printf("..");
            }
            else if(plateau[i][j] == pionBlanc){ 
                printf("PB");
            }
            else if(plateau[i][j] == pionNoir){ 
                printf("PN");
            }
            else if(plateau[i][j] == dameBlanche){ 
                printf("DB");
            }
            else if(plateau[i][j] == dameNoire){ 
                printf("DN");
            }
        }
        printf("|\n");
    }
    printf("+--+--+--+--+--+--+--+--+--+--+\n\n");
}


/*!
\fn struct coord coupHumain(enum pion plateau[N][N])
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 15 janvier 2021
\brief recupere les coordonnees saisies par le joueur 
\param plateau[N][N] plateau de jeu dans une variable personnalisee
*/

void coupHumain(enum case plateau[N][N], struct joueur joueur ,struct compte_pion compte){
    struct coord coord_depart;
    struct coord coord_arrivee;
    enum pion sauvegarde;
    int verificationCaseDepart = 0;

    do{
        printf("Saisissez les coordonnées du pion que vous voulez jouer.\n")
        
        coord_depart = entree_coup_humain(plateau);

        if(humain == pions_blancs){
            if(plateau[coord_depart.y][coord_depart.x] == pionBlanc || plateau[coord_depart.y][coord_depart.x] == dameBlanche){
                verificationCaseDepart = 1;
            }
        }
        else{
            if(plateau[coord_depart.y][coord_depart.x] == pionNoir || plateau[coord_depart.y][coord_depart.x] == dameNoire){
                verificationCaseDepart = 1;
            }
        }

        if(verificationCaseDepart == 1){
            int verificationPlacement = 0;
            do{
                verificationEntree = 0;

                coord_arrivee = entree_coup_humain(plateau);

                verificationPlacement = placement_pion(plateau, coord_depart, coord_arrivee);


                if(plateau[coord_arrivee.y][coord_arrivee.x] == caseNoire){

                    if(plateau[coord_depart.y][coord_depart.x] == pionBlanc || plateau[coord_depart.y][coord_depart.x] == pionNoir){
            
                    }
                    else if(plateau[coord_depart.y][coord_depart.x] == dameBlanche || plateau[coord_depart.y][coord_depart.x] == dameNoire){
            
                    }

                }
                else{
                    printf("Case déjà utilisee ou case blanche, recommencez");
                }

                
                if(verificationPlacement == 0){
                    printf("Erreur, Reessayez");
                }
            }while(verificationPlacement == 0);
        }   
        else{
                printf("Case vide, recommencez");
        }
    }while(verificationCaseDepart == 0);

    plateau[coord_arrivee.y][coord_arrivee.x] = plateau[coord_depart.y][coord_depart.x];
    plateau[coord_depart.y][coord_depart.x] = caseNoire;
}


struct coord entree_coup_humain(enum case plateau[N][N]){
    int verificationEntree = 0;
    do{
        printf("Saisir x (0 à 9):");
        scanf("%d", &coord.x);
        if(coord.x >= 0 && coord.x <= 9){
            verificationEntree = 1;
        }
        else{
            printf("Erreur de saisie, recommencez");
        }
    }while(verificationEntree == 0);
    verificationEntree = 0;
    do{
        printf("Saisir y (0 à 9):");
        scanf("%d", &coord.y);
        if(coord.y >= 0 && coord.y <= 9){
            verificationEntree = 1;
        }
        else{
            printf("Erreur de saisie, recommencez");
        }
    }while(verificationEntree == 0);

    return coord;
}

void rafle(enum case plateau[N][N], struct coord coord_pion, struct compte_pion compte, enum joueur humain){

    
    if(humain == pions_blancs){
        if(plateau[coord_pion.y-1][coord_pion.x-1] == pionNoir && plateau[coord_pion.y-2][coord_pion.x-2]){
            plateau[coord_pion.y][coord_pion.x] = caseNoire;
            plateau[coord_pion.y-1][coord_pion.x-1] = caseNoire;
            compte.nb_pion_noirs = compte.nb_pion_noirs - 1;
            plateau[coord_pion.y-2][coord_pion.x-2] = pionBlanc;

            rafle(plateau, coord_pion, compte, humain);
        }
        else if(){

        }

    }
}

void rafleDame(enum case plateau[N][N], struct coord coord_dame, struct compte_pion compte){

}

void verificationDeplacement(enum case plateau[N][N], struct coord coord_depart, struct coord coord_arrivee, struct compte_pion compte, enum joueur humain){
    if(coord_arrivee.y == coord_depart.y-1 && (coord_arrivee.x == coord_depart.x+1 || coord_arrivee.x == coord_depart.x-1)){
        return 1;
    }
    else if(coord_arrivee.y == coord_depart.y-2 && coord_arrivee.x == coord_depart.x+2){
        if(humain == pions_blancs){
            if(plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == pionNoir || plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == dameNoire){
                plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] = caseNoire;
                compte.nb_pion_noirs = compte.nb_pion_noirs - 1;

            }

        }
        else{
            if(plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == pionBlanc || plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == dameBlanche){
                plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] = caseNoire;
                compte.nb_pion_blancs = compte.nb_pion_blancs - 1;

            }
        }
        else if(plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == caseNoire){
            return 0;
        }
    }
    else if(coord_arrivee.y == coord_depart.y-2 && coord_arrivee.x == coord_depart.x-2){
        if(humain == pions_blancs){
            if(plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] == pionNoir || plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] == dameNoire){
                plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] = caseNoire;
                compte.nb_pion_noirs = compte.nb_pion_noirs - 1;
            }
        }
        else{
            if(plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] == pionBlanc || plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] == dameBlanche){
                plateau[coord_arrivee.y + 1][coord_arrivee.x + 1] = caseNoire;
                compte.nb_pion_blancs = compte.nb_pion_blancs - 1;
            }
        }
        if(plateau[coord_arrivee.y + 1][coord_arrivee.x - 1] == caseNoire){
            verification = 0;
        }
    }
    else{
        verification = 0;
    }
}


void coupMachine(enum case oldPlateau[N][N]) {
    
}

int max(enum pion oldPlateau[N][N], int depth) {
    
}

int min(enum pion oldPlateau[N][N], int depth) {
    
}

int eval(enum pion plateau[N][N], enum pion joueur) {
    
}


/*!
\fn enum pion gagnant(enum pion plateau[N][N])
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 15 janvier 2021
\brief Programme d'un jeu de Morpion sur console
\param plateau[N][N] plateau de jeu dans une variable personnalisee
\return le pion du gagnant s'il y en a un et 0 sinon
*/

enum pion gagnant(enum pion plateau[N][N])
{
    int nb_pion_blancs = 0;
    int nb_pion_noirs = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(plateau[i][j] == pionBlanc || plateau[i][j] == dameBlanche){
                nb_pion_blancs++;
            }
            if(plateau[i][j] == pionNoir || plateau[i][j] == dameNoire){
                nb_pion_noirs++;
            }
        }
    }

    if(nb_pion_blancs > 0 && nb_pion_noirs == 0){
        return pionBlanc;
    }
    else if(nb_pion_noirs > 0 && nb_pion_blancs == 0){
        return pionNoir;
    }
    else{
        return 0;
    }
}



/*!
\fn int main (int argc, char** argv)
\author Lucas Velay <velaylucas@cy-tech.fr>
\version 1
\date 15 janvier 2021
\brief fonction principale
\param argc nombre d'arguments en entrée
\param argv valeur des arguments en entrée
*/

int main(int argc, char** argv)
{
    enum case plateau[N][N];
    struct compte_pion compte;
    struct joueur joueur;

    initialiser(plateau, humain, machine);

    do{
        afficher(plateau);

        if(humain == pions_blancs){
            coupHumain();
        }
        else if(machine == pions_blancs){
            coupMachine();
        }

        if(humain == pions_noirs){
            coupHumain();
        }
        else if(machine == pions_noirs){
            coupMachine();
        }


    }while(gagnant(plateau) == 0);

}