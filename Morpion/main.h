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

