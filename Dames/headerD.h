#define N 10

enum case{
    caseBlanche,
    caseNoire,
    pionBlanc,
    pionNoir,
    dameBlanche,
    dameNoire
};

struct compte_pion{
    int nb_pions_blancs = 20,
    int nb_pions_noirs = 20
}

enum type_joueur{
    pions_blancs,
    pions_noirs
}

struct joueur{
    enum type_joueur humain;
    enum type_joueur machine;
}

struct coord{
    int x;
    int y;
};

void initialiser(enum case plateau[N][N]);
void afficher(enum case plateau[N][N]);
void coupHumain(enum case plateau[N][N]);
void coupMachine(enum case plateau[N][N]);
enum case gagnant(enum case plateau[N][N]);
int plateauPlein(enum case plateau[N][N]);

