#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct coord {
    int x;
    int y;
};

enum pion {
    VIDE = '-',
    PIONX = 'X',
    PIONO = 'O'
};

struct coord;

void initialiser(enum pion plateau[3][3]);
void afficher(enum pion plateau[3][3]);
struct coord coupHumain(enum pion plateau[3][3]);
struct coord coupMachine(enum pion plateau[3][3]);
void jouer(enum pion plateau[3][3], struct coord coup, enum pion joueur);
enum pion gagnant(enum pion plateau[3][3]);
int plateauPlein(enum pion plateau[3][3]);
int max(enum pion oldPlateau[3][3], int dept);
int min(enum pion oldPlateau[3][3], int depth);
int eval(enum pion plateau[3][3], enum pion joueur);

// RETOURNE LES COORDONEES DE L'ENDROIT OU LE JOUEUR PEUT GAGNER
struct coord peutGagner(enum pion plateau[3][3], enum pion joueur);

enum pion plateau[3][3];
int playerTurn;

int main(void){
    // Pour avoir des chiffres réelement aléatoire
    srand(time(NULL));

    // On initiliaise le plateau avec des pions vides
    initialiser(plateau);

    // On affiche le plateau au joueur
    afficher(plateau);
    playerTurn = rand()%2;
    if(playerTurn == 0) {
        playerTurn = -1;
    }

    // Tant que le plateau n'est pas plein (égalité) ou qu'un joueur à gagné
    while (gagnant(plateau) == VIDE) {

        //Rejouer si égalité
        if (plateauPlein(plateau) == 1 ){
            printf("égalité \n \n");
            //réinitialise le plateau
            initialiser(plateau);
        }
 
        if(playerTurn == 1) {
            jouer(plateau, coupHumain(plateau), PIONX);
        } else {
            jouer(plateau, coupMachine(plateau), PIONO);
        }

        playerTurn = playerTurn * -1;
        afficher(plateau);
    }

    //affichage du gagnant
    if (gagnant(plateau) == PIONX){
        printf("Vous avez gagné \n \n");
    } else {
        printf("Vous avez perdu \n \n");
    }

    
}
// On initialise chaque case à VIDE
void initialiser(enum pion plateau[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            plateau[i][j] = VIDE;
        }
    }
}

// On affiche le plateau
void afficher(enum pion plateau[3][3]) {
    for (int i = 0; i < 3; i++) {
        
        printf("%c %c %c \n", plateau[i][0], plateau[i][1], plateau[i][2]);
    }
    printf("----------------------- \n \n");
}

// Renvoie 0 s'il trouve une case vide sinon renvoie 1
int plateauPlein(enum pion plateau[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (plateau[i][j] == VIDE) {
                return 0;
            }
        }
    }
    return 1;
}

int plateauVide(enum pion plateau[3][3]) {
        for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (plateau[i][j] != VIDE) {
                return 0;
            }
        }
    }
    return 1;
}

struct coord coupHumain(enum pion plateau[3][3]) {
    struct coord coup;

    do {
        // On recupere les coordonnées
        printf("Où voulez-vous jouer ? \n x: ");
        scanf("%d", &coup.y);
        printf("y: ");
        scanf("%d", &coup.x);

        // Car pour la machine la premiere ligne est 0 et la premiere colone est 0
        coup.x--;
        coup.y--;
    } while(plateau[coup.x][coup.y] != VIDE);

    return coup;
}

struct coord coupMachine(enum pion oldPlateau[3][3]) {
    struct coord coup;
    
    int maxV = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            enum pion plateau[3][3];
            for (int ialt = 0; ialt < 3; ialt++) {
                for (int jalt = 0; jalt < 3; jalt++) {
                    plateau[ialt][jalt] = oldPlateau[ialt][jalt];
                }
            }

            if(plateau[i][j] == VIDE) {
                plateau[i][j] = PIONO;
                int tmp = min(plateau, 0);
                //printf(" ------------- i:%d j:%d -----------", i, j);
                //printf(" ------------- tmp:%d maxV:%d -----------", tmp, maxV);
                if(tmp > maxV) {
                    maxV = tmp;
                    coup.x = i;
                    coup.y = j;
                }
                //printf("---- x:%d y:%d ------ \n", coup.x, coup.y);
            }
        }
    }

    return coup;
}

int max(enum pion oldPlateau[3][3], int depth){
    int max = -100000;
    if(plateauPlein(oldPlateau) == 1 || gagnant(oldPlateau) != VIDE) {
        return eval(oldPlateau, PIONO);
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                // Copie le plateau
                enum pion plateau[3][3];
                for (int ialt = 0; ialt < 3; ialt++) {
                    for (int jalt = 0; jalt < 3; jalt++) {
                        plateau[ialt][jalt] = oldPlateau[ialt][jalt];
                    }
                }

                if(plateau[i][j] == VIDE) {
                    plateau[i][j] = PIONO;
                    int tmp = min(plateau, depth+1);
                    if(tmp > max) {
                        max = tmp;
                    }
                }   
            }
        }
        return max;
    }
}

int min(enum pion oldPlateau[3][3], int depth) {
    int min = 100000;

    if(plateauPlein(oldPlateau) == 1 || gagnant(oldPlateau) != VIDE) {
        return eval(oldPlateau, PIONO);
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Copie le plateau
                enum pion plateau[3][3];
                for (int ialt = 0; ialt < 3; ialt++) {
                    for (int jalt = 0; jalt < 3; jalt++) {
                        plateau[ialt][jalt] = oldPlateau[ialt][jalt];
                    }
                }

                if(plateau[i][j] == VIDE) {
                    plateau[i][j] = PIONX;
                    int tmp = max(plateau, depth+1);
                    if(tmp < min) {
                        min = tmp;
                    }
                }   
            }
        }
        return min;
    }
}

int eval(enum pion plateau[3][3], enum pion joueur) {
    if(gagnant(plateau) == joueur) {
        return 1000;
    } else if(gagnant(plateau) == VIDE) {
        return 0;
    } else{
        return -1000;
    }
}

// verifie s'il y a un gagnant
enum pion gagnant(enum pion plateau[3][3]) {
    // Verifier les lignes
    for (int i = 0; i < 3; i++) {
        if(plateau[i][0] == plateau[i][1] && plateau[i][1] == plateau[i][2] && plateau[i][0] != VIDE) {
            return plateau[i][0];
        }
    }

    // Verifier les colones
    for (int i = 0; i < 3; i++) {
        if(plateau[0][i] == plateau[1][i] && plateau[1][i] == plateau[2][i] && plateau[0][i] != VIDE) {
            return plateau[0][i];
        }
    }
    
    // Verifier la diagonale haut gauche -> bas droite
    if(plateau[0][0] == plateau[1][1] && plateau[1][1] == plateau[2][2] && plateau[0][0] != VIDE) {
        return plateau[1][1];
    }

    // Verifier la diagonale bas droite -> haut gauche
    if(plateau[0][2] == plateau[1][1] && plateau[1][1] == plateau[2][0] && plateau[0][2] != VIDE) {
        return plateau[1][1];
    }

    return VIDE;
}

// Ajoute le pion aux coordonnées 
void jouer(enum pion plateau[3][3], struct coord coup, enum pion joueur) {
    plateau[coup.x][coup.y] = joueur;
}
