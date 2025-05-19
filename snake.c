/**
* \page Général
* \brief Jeu snake codé en C.
* \author Ewen THÉPOT
* \version 4.0
* \date 30 novembre 2024
*
* Ce programme implémente le jeu Snake dans un terminal.
* Le serpent évolue dans un plateau, peut manger des pommes pour grandir.
* Pour survivre et gagner, il doit éviter toute collision avec un obstacle ou une bordure.
*/

// Importation des bibliothèques
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Pour les fonctions sleep et kbhit
#include <termios.h> // Pour la fonction kbhit
#include <fcntl.h> // Pour la fonction kbhit
#include <time.h> // Pour la fonction initPlateau
#include <stdbool.h> // Pour les collisions

// ----------------------------- CONSTANTES -------------------------------------



// Constantes pour la composition du corps du serpent


/**
 * 
 * \def HEAD
 * 
 * \brief constante pour le caractère représentant la tête du serpent
 * 
 */
#define HEAD 'O' // La tête du serpent sera représentée par ce caractère

/**
 * 
 * \def QUEUE
 * 
 * \brief constante pour le caractère représentant le corps du serpent
 * 
 */
#define QUEUE 'X' // La queue du serpent sera représentée par une suite de ce caractère


// Constantes définissant les limites en 0 du terminal

/**
 * 
 * \def LIMITE_GAUCHE_TERMINAL
 * 
 * \brief constante pour la limite du terminal à gauche
 * 
 */
#define LIMITE_GAUCHE_TERMINAL 0 // Limite du terminal à gauche

/**
 * 
 * \def LIMITE_HAUT_TERMINAL
 * 
 * \brief constante pour la limite du terminal en haut
 * 
 */
#define LIMITE_HAUT_TERMINAL 0 // Limite du terminal en haut


// Constante définissant la position initiale du serpent, sa taille et sa vitesse, ainsi que le nombre de pommes

/**
 * 
 * \def X_INITIAL
 * 
 * \brief constante pour la coordonnée X de départ du serpent
 * 
 */
#define X_INITIAL 40 // coordonnée X de départ

/**
 * 
 * \def Y_INITIAL
 * 
 * \brief constante pour la coordonnée Y de départ du serpent
 * 
 */
#define Y_INITIAL 20 // coordonnée Y de départ

/**
 * 
 * \def TAILLE_INITIALE_SERPENT
 * 
 * \brief constante pour la longueur initiale du serpent
 * 
 */
#define TAILLE_INITIALE_SERPENT 10 // Longueur initiale du serpent

/**
 * 
 * \def NOMBRE_DE_POMMES
 * 
 * \brief constante pour le nombre de pommes à manger pour gagner
 * 
 */
#define NOMBRE_DE_POMMES 10 // Nombre de pommes à manger pour gagner

/**
 * 
 * \def TAILLE_MAX_SERPENT
 * 
 * \brief constante pour la taille maximale du serpent qui dépend du nombre de pommes
 * 
 */
#define TAILLE_MAX_SERPENT (TAILLE_INITIALE_SERPENT + NOMBRE_DE_POMMES) // La taille maximale du serpent dépend du nombre de pommes

/**
 * 
 * \def DELAI_MOUVEMENTS_MS
 * 
 * \brief constante pour le temps d'attente entre chaque mouvement en millisecondes, qui définit ainsi la vitesse du serpent
 * 
 */
#define DELAI_MOUVEMENTS_MS 100000 // Temps d'attente entre chaque mouvement en millisecondes, définit la vitesse du serpent

/**
 * 
 * \def DIMINUTION_DELAI_MOUVEMENTS_MS
 * 
 * \brief constante pour le coefficient utilisé lors de la diminution de la vitesse du serpent
 * 
 */
#define DIMINUTION_DELAI_MOUVEMENTS_MS 0.95 // Coefficient utilisé lors de la diminution de la vitesse du serpent


// Constantes utilisées pour contrôler le serpent ou arrêter le jeu

/**
 * 
 * \def RIGHT
 * 
 * \brief constante pour la touche permettant de diriger le serpent vers la droite
 * 
 */
#define RIGHT 'd' // Taper 'd' pour aller vers la droite

/**
 * 
 * \def LEFT
 * 
 * \brief constante pour la touche permettant de diriger le serpent vers la gauche
 * 
 */
#define LEFT 'q' // Taper 'q' pour aller vers la gauche

/**
 * 
 * \def UP
 * 
 * \brief constante pour la touche permettant de diriger le serpent vers le haut
 * 
 */
#define UP 'z' // Taper 'z' pour aller vers le haut

/**
 * 
 * \def DOWN
 * 
 * \brief constante pour la touche permettant de diriger le serpent vers le bas
 * 
 */
#define DOWN 's' // Taper 's' pour aller vers le bas

/**
 * 
 * \def STOP
 * 
 * \brief constante pour la touche permettant l'arrêt du jeu
 * 
 */
#define STOP 'a' // Taper 'a' pour arrêter le jeu

/**
 * 
 * \def DIRECTION_INITIALE
 * 
 * \brief constante pour la direction initiale du serpent
 * 
 */
#define DIRECTION_INITIALE RIGHT; // Le serpent ira dans cette direction au lancement du jeu


// Constantes utilisées lors de la création du plateau de jeu

/**
 * 
 * \def CARACTERE_PLATEAU
 * 
 * \brief constante pour le caractère utilisé pour dessiner le plateau
 * 
 */
#define CARACTERE_PLATEAU '#' // Le plateau du jeu sera dessiné à l'aide de ce caractère

/**
 * 
 * \def CARACTERE_VIDE
 * 
 * \brief constante pour le caractère représentant un espace vide du plateau
 * 
 */
#define CARACTERE_VIDE ' ' // Les positions vides seront représentées par des espaces

/**
 * 
 * \def LARGEUR_PLATEAU
 * 
 * \brief constante pour la largeur du plateau de jeu
 * 
 */
#define LARGEUR_PLATEAU 80 // Largeur du plateau de jeu

/**
 * 
 * \def HAUTEUR_PLATEAU
 * 
 * \brief constante pour la hauteur du plateau de jeu
 * 
 */
#define HAUTEUR_PLATEAU 40 // Hauteur du plateau de jeu

/**
 * 
 * \def DECALAGE
 * 
 * \brief constante pour d'aligner les coordonnées du plateau avec celles du serpent
 * \details Permet d'aligner les coordonées des deux tableaux en ajoutant 1 ligne et 1 colonne et en laissant les colonnes et lignes d'indice 0 du tableau du plateau vides.
 * 
 */
#define DECALAGE 1 // Permet d'aligner les coordonnées du plateau avec celles du serpent en ajoutant laissant les colonnes et lignes d'indice 0 du tableau du plateau vides.

/**
 * 
 * \def LARGEUR_TABLEAU_PLATEAU
 * 
 * \brief constante pour la largeur du tableau des coordonées du plateau
 * 
 * \details On initialise la largeur en y ajoutant un décalage pour le faire correspondre avec les coordonnées du serpent (premiers rangs x vides)
 * 
 */
#define LARGEUR_TABLEAU_PLATEAU (LARGEUR_PLATEAU + DECALAGE) // Largeur du tableau contenant les coordonnées du plateau (+1 pour le faire correspondre avec les coordonnées du serpent (premier rangs x vides)

/**
 * 
 * \def HAUTEUR_TABLEAU_PLATEAU
 * 
 * \brief constante pour la hauteur du tableau des coordonées du plateau
 * 
 * \details On initialise la hauteur en y ajoutant un décalage pour le faire correspondre avec les coordonnées du serpent (premiers rangs y vides)
 * 
 */
#define HAUTEUR_TABLEAU_PLATEAU (HAUTEUR_PLATEAU + DECALAGE) // Hauteur du tableau contenant les coordonnées du plateau (+1 pour le faire correspondre avec les coordonnées du serpent (premier rangs y vides)

/**
 * 
 * \def X_BORDURE_GAUCHE_PLATEAU
 * 
 * \brief constante pour la coordonée X de la bordure gauche du plateau
 * 
 */
#define X_BORDURE_GAUCHE_PLATEAU (LARGEUR_TABLEAU_PLATEAU - LARGEUR_PLATEAU) // coordonnée minimum x du plateau

/**
 * 
 * \def X_BORDURE_DROITE_PLATEAU
 * 
 * \brief constante pour la coordonée X de la bordure droite du plateau
 * 
 */
#define X_BORDURE_DROITE_PLATEAU LARGEUR_PLATEAU // coordonnée maximum x du plateau

/**
 * 
 * \def Y_BORDURE_HAUT_PLATEAU
 * 
 * \brief constante pour la coordonée X de la bordure haute du plateau
 * 
 */
#define Y_BORDURE_HAUT_PLATEAU (HAUTEUR_TABLEAU_PLATEAU - HAUTEUR_PLATEAU) // coordonnée minimum y du plateau

/**
 * 
 * \def Y_BORDURE_BAS_PLATEAU
 * 
 * \brief constante pour la coordonée X de la bordure basse du plateau
 * 
 */
#define Y_BORDURE_BAS_PLATEAU HAUTEUR_PLATEAU // coordonnée maximum y du plateau


// Constantes utilisées lors de la créations des pavés

/**
 * 
 * \def CARACTERE_PAVE
 * 
 * \brief constante pour le caractère utilisé pour dessiner les pavés
 * 
 */
#define CARACTERE_PAVE '#' // Les pavés seront dessinés à l'aide de ce caractère

/**
 * 
 * \def TAILLE_PAVE
 * 
 * \brief constante pour la taille des pavés
 * 
 */
#define TAILLE_PAVE 5 // Taille des pavés dans le plateau

/**
 * 
 * \def NOMBRE_DE_PAVES
 * 
 * \brief constante pour le nombre de pavé
 * 
 */
#define NOMBRE_DE_PAVES 4 // Nombre de pavés à générer

/**
 * 
 * \def ECART_MINIMUM_BORDURE_PLATEAU_PAVE
 * 
 * \brief constante pour l'écrat minimum entre les pavés et les bordures du plateau
 * 
 */
#define ECART_MINIMUM_BORDURE_PLATEAU_PAVE 2 // Ecart minimum entre les pavés et les bordures du plateau

/**
 * 
 * \def X_MIN_PAVE
 * 
 * \brief constante pour la coordonnée minimum x du pavé
 * 
 */
#define X_MIN_PAVE (X_BORDURE_GAUCHE_PLATEAU + ECART_MINIMUM_BORDURE_PLATEAU_PAVE) // coordonnée minimum x du pavé

/**
 * 
 * \def X_MAX_PAVE
 * 
 * \brief constante pour la coordonnée maximum x du pavé
 * 
 */
#define X_MAX_PAVE (X_BORDURE_DROITE_PLATEAU - (ECART_MINIMUM_BORDURE_PLATEAU_PAVE + (TAILLE_PAVE - 1))) // coordonnée maximum x du pavé

/**
 * 
 * \def Y_MIN_PAVE
 * 
 * \brief constante pour la coordonnée minimum y du pavé
 * 
 */
#define Y_MIN_PAVE (Y_BORDURE_HAUT_PLATEAU + ECART_MINIMUM_BORDURE_PLATEAU_PAVE) // coordonnée minimum y du pavé

/**
 * 
 * \def Y_MAX_PAVE
 * 
 * \brief constante pour la coordonnée maximum y du pavé
 * 
 */
#define Y_MAX_PAVE (Y_BORDURE_BAS_PLATEAU - (ECART_MINIMUM_BORDURE_PLATEAU_PAVE + (TAILLE_PAVE - 1))) // coordonnée maximum y du pavé


// Constantes utilisées pour la création des issues

/**
 * 
 * \def Y_ISSUES_GAUCHE_DROITE
 * 
 * \brief constante pour la coordonnée y des issues gauche et droite
 * 
 */
#define Y_ISSUES_GAUCHE_DROITE (HAUTEUR_PLATEAU / 2) // Coordonnée Y des issues gauche et droite

/**
 * 
 * \def X_ISSUE_GAUCHE
 * 
 * \brief constante pour la coordonnée x de l'issue gauche
 * 
 */
#define X_ISSUE_GAUCHE X_BORDURE_GAUCHE_PLATEAU // Coordonnée X de l'issue gauche

/**
 * 
 * \def X_ISSUE_DROITE
 * 
 * \brief constante pour la coordonnée x de l'issue droite
 * 
 */
#define X_ISSUE_DROITE X_BORDURE_DROITE_PLATEAU // Coordonnée X de l'issue droite

/**
 * 
 * \def X_ISSUES_HAUT_BAS
 * 
 * \brief constante pour la coordonnée x des issues haute et basse
 * 
 */
#define X_ISSUES_HAUT_BAS (LARGEUR_PLATEAU / 2) // Coordonnée X des issues du haut et du bas

/**
 * 
 * \def Y_ISSUE_HAUT
 * 
 * \brief constante pour la coordonnée y de l'issue haute
 * 
 */
#define Y_ISSUE_HAUT Y_BORDURE_HAUT_PLATEAU // Coordonnée Y de l'issue du haut

/**
 * 
 * \def Y_ISSUE_BAS
 * 
 * \brief constante pour la coordonnée y de l'issue basse
 * 
 */
#define Y_ISSUE_BAS Y_BORDURE_BAS_PLATEAU // Coordonée Y de l'issue du bas


// Constantes utilisées pour la création des pommes

/**
 * 
 * \def POMME
 * 
 * \brief constante pour le caractère représentant une pomme
 * 
 */
#define POMME '6' // Une pomme sera représentée par ce caractère

/**
 * 
 * \def X_MIN_POMME
 * 
 * \brief constante pour la coordonnée minimum X de la pomme
 * 
 */
#define X_MIN_POMME (X_BORDURE_GAUCHE_PLATEAU + 1) // Coordonnée minimum X de la pomme

/**
 * 
 * \def X_MAX_POMME
 * 
 * \brief constante pour la coordonnée maximum X de la pomme
 * 
 */
#define X_MAX_POMME (X_BORDURE_DROITE_PLATEAU - 1) // Coordonnée maximum X de la pomme

/**
 *Y_MIN_POMME
 * \def X_MIN_POMME
 * 
 * \brief constante pour la coordonnée minimum Y de la pomme
 * 
 */
#define Y_MIN_POMME (Y_BORDURE_HAUT_PLATEAU + 1) // Coordonnée minimum Y de la pomme

/**
 * 
 * \def Y_MAX_POMME
 * 
 * \brief constante pour la coordonnée maximum Y de la pomme
 * 
 */
#define Y_MAX_POMME (Y_BORDURE_BAS_PLATEAU - 1) // Coordonnée maximum Y de la pomme


// Gameplay

/**
 * 
 * \def MESSAGE_FIN
 * 
 * \brief constante pour le message de fin de jeu
 * 
 */
#define MESSAGE_FIN "Snake un au revoir ;)\n" // Message de fin


// Prototypes des fonctions
int kbhit(); // Fonction qui permet de détecter si un caractère est présent dans le terminal
void gotoXY(int x, int y); // Permet de se déplacer dans le terminal
void disableEcho(); // Désactive l'affichage des touches clavier dans le terminal
void enableEcho(); // Active l'affichage des touches clavier dans le terminal
void afficher(int x, int y, char c); // Permet d'afficher un caractère dans le terminal
void effacer(int x, int y); // Permet d'effacer un caractère dans le terminal
void dessinerSerpent(int lesX[], int lesY[], int taille); // Dessine le serpent dans le terminal
bool progresser(int lesX[], int lesY[], char direction, bool *collision, int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int *taille); // Permet de faire progresser le serpent dans le terminal et dans la direction souhaitée
void initPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU]); // Permet de créer un plateau de jeu aux dimensions souhaitées avec le nombre de pavés (obstacles) souhaités
void dessinerPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU]); // Permet de déssiner le plateau du jeu
void ajouterPomme(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int lesX[], int lesY[], int taille); // Permet de faire apparaître une pomme à une position aléatoire sur le plateau de jeu et de l'ajouter au tableau des coordonnées du plateau



// Programme principal

/**
* \fn int main()
* \brief Programme principal du jeu Snake.
*
* Ce programme initialise le jeu, gère la boucle principale du jeu, 
* traite les entrées utilisateur, met à jour l'état du jeu et affiche le résultat final.
*
* **Fonctionnalités principales:**
* - Initialisation du plateau de jeu, du serpent et des pommes.
* - Gestion des mouvements du serpent en fonction des entrées utilisateur.
* - Détection des collisions avec les murs, le corps du serpent et les obstacles.
* - Gestion de la croissance du serpent lorsqu'il mange une pomme.
* - Affichage du jeu à l'écran.
*
* \return 0 en cas de succès, une autre valeur en cas d'erreur.
*/
int main()
{
    // Initialisation des variables
    int taille = TAILLE_INITIALE_SERPENT; // Initialisation de la taille du serpent
    int tempsAttente = DELAI_MOUVEMENTS_MS; // Initialisation du temps entre chaque mouvements, autrement-dit gestion de la vitesse
    int score = 0; // Initialisation du score
    int xHead = X_INITIAL; // Coordonnée x initiale de la tête du serpent
    int yHead = Y_INITIAL; // Coordonnée y initiale de la tête du serpent
    int lesX[TAILLE_MAX_SERPENT]; // Tableau des coordonnées X du serpent
    int lesY[TAILLE_MAX_SERPENT]; // Tableau des coordonnées Y du serpent
    char touche; // Touche entrée par l'utilisateur
    char direction = DIRECTION_INITIALE; // Définir la direction de départ
    bool collision = false; // Définir si une collision a eu lieu
    lesX[0] = xHead; // Initialiser les coordonnées X de la tête du serpent
    lesY[0] = yHead; // Initialiser les coordonnées Y de la tête du serpent
    for (int i = 1; i < TAILLE_INITIALE_SERPENT; i++) // Initialiser les coordonnées X et Y du corps du serpent
    {
        lesX[i] = xHead - i;
        lesY[i] = yHead;
    }
    // Gestion du terminal
    system("clear"); // Effacer le terminal
    disableEcho(); // Désactiver l'affichage des touches clavier dans le terminal
    // Initialisation du jeu
    int coordonneesPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU]; // Initialisation du plateau de jeu
    initPlateau(coordonneesPlateau); // Créer le plateau de jeu
    ajouterPomme(coordonneesPlateau, lesX, lesY, taille); // Faire apparaître la première pomme
    dessinerSerpent(lesX, lesY, taille); // Dessiner le serpent dans le terminal
    //Boucle principale du jeu
    do
    {
        if (kbhit() == 1) // Vérifier la présence d'un caractère
        {
            scanf("%c", &touche); // Stocker ce caractère dans la variable touche
            if ((touche == UP) && (direction != DOWN)) // Vérifier si ce caractère correspond à la direction 'haut' et que la direction actuelle n'est pas 'bas'
            {
                direction = UP; // Changer la direction pour 'haut'
            }
            else if ((touche == DOWN) && (direction != UP)) // Vérifier si ce caractère correspond à la direction 'bas' et que la direction actuelle n'est pas 'haut'
            {
                direction = DOWN; // Changer la direction pour 'bas'
            }
            else if ((touche == LEFT) && (direction != RIGHT)) // Vérifier si ce caractère correspond à la direction 'gauche' et que la direction actuelle n'est pas 'droite'
            {
                direction = LEFT; // Changer la direction pour 'gauche'
            }
            else if ((touche == RIGHT) && (direction != LEFT)) // Vérifier si ce caractère correspond à la direction 'droite' et que la direction actuelle n'est pas 'gauche'
            {
                direction = RIGHT; // Changer la direction pour 'droite'
            }
        }
        bool mangee = progresser(lesX, lesY, direction, &collision, coordonneesPlateau, &taille); // Faire progresser le serpent dans le terminal
        usleep(tempsAttente); // Patienter un certain temps, permet ainsi de définir la vitesse du serpent
        if (mangee) // Si le serpent a mangé une pomme
        {
            score++; // Le score augmente de 1
            tempsAttente = tempsAttente * DIMINUTION_DELAI_MOUVEMENTS_MS; // Diminution du délai -> Augmentation de la vitesse
            if (score < NOMBRE_DE_POMMES) // Si le score est inférieur au nombre de pommes
            {
                ajouterPomme(coordonneesPlateau, lesX, lesY, taille); // Faire apparaître une nouvelle pomme
            }
        }
    } while ((touche != STOP) && (collision == false) && (score != NOMBRE_DE_POMMES)); // Le serpent progresse dans le terminal dans les directions choisies tant qu'on ne tape pas 'a', qu'on ne touche pas de pavé/bordure et qu'on ne gagne pas
    dessinerSerpent(lesX, lesY, taille); // Afficher le serpent dans le terminal
    gotoXY(1, (HAUTEUR_PLATEAU + 1)); // Aller sous le plateau de jeu
    printf("%s", MESSAGE_FIN); // Afficher le message de fin
    enableEcho(); // Réactiver l'affichage des touches clavier dans le terminal
    return EXIT_SUCCESS;
}


// Fonctions

/**
 * \fn int kbhit()
 * \brief Fonction permettant de détecter si un caractère est présent dans le terminal.
 * 
 * Cette fonction permet de vérifier si un caractère a été saisi dans le terminal sans bloquer l'exécution du programme.
 * 
 * \return Retourne 1 si un caractère est présent dans le terminal, sinon 0.
 */
int kbhit() // Fonction qui permet de détecter si un caractère est présent dans le terminal
{
	// la fonction retourne :
	// 1 si un caractere est present
	// 0 si pas de caractere present
	
	int unCaractere=0;
	struct termios oldt, newt;
	int ch;
	int oldf;

	// mettre le terminal en mode non bloquant
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();

	// restaurer le mode du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if(ch != EOF){
		ungetc(ch, stdin);
		unCaractere=1;
	} 
	return unCaractere;
}

/**
 * \fn void gotoXY(int x, int y)
 * \brief Permet de se déplacer dans le terminal.
 * 
 * Cette fonction déplace le curseur du terminal à la position donnée par les coordonnées (x, y).
 * 
 * \param x La position horizontale où déplacer le curseur.
 * \param y La position verticale où déplacer le curseur.
 */
void gotoXY(int x, int y) // Permet de se déplacer dans le terminal
{ 
    printf("\033[%d;%df", y, x);
}

/**
 * \fn void disableEcho()
 * \brief Désactive l'affichage des touches clavier dans le terminal.
 * 
 * Cette fonction désactive l'écho des caractères saisis au niveau du terminal.
 * 
 * \see enableEcho()
 */
void disableEcho() // Désactive l'affichage des touches clavier dans le terminal
{
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Desactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

/**
 * \fn void enableEcho()
 * \brief Active l'affichage des touches clavier dans le terminal.
 * 
 * Cette fonction réactive l'écho des caractères saisis au niveau du terminal.
 * 
 * \see disableEcho()
 */
void enableEcho() // Active l'affichage des touches clavier dans le terminal
{
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Reactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

/**
 * \fn void afficher(int x, int y, char c)
 * \brief Permet d'afficher un caractère à une position donnée dans le terminal.
 * 
 * Cette fonction affiche un caractère dans le terminal à la position spécifiée par (x, y).
 * 
 * \param x La position horizontale où afficher le caractère.
 * \param y La position verticale où afficher le caractère.
 * \param c Le caractère à afficher.
 */
void afficher(int x, int y, char c) // Permet d'afficher un caractère dans le terminal
{
    if ((x > LIMITE_GAUCHE_TERMINAL) && (y > LIMITE_HAUT_TERMINAL)) // Vérifier que les coordonnées sont bien affichables dans le terminal
    {
        gotoXY(x, y); // Aller à la position souhaitée
        printf("%c", c); // Écrire le caractère souhaité
        gotoXY(1, 1); // Revenir au début du terminal
    }
}

/**
 * \fn void effacer(int x, int y)
 * \brief Permet d'effacer un caractère dans le terminal.
 * 
 * Cette fonction efface le caractère à la position spécifiée (x, y) dans le terminal en affichant un espace vide.
 * 
 * \param x La position horizontale où effacer le caractère.
 * \param y La position verticale où effacer le caractère.
 */
void effacer(int x, int y) // Permet d'effacer un caractère dans le terminal
{
    gotoXY(x, y); // Aller à la position souhaitée
    printf("%c", CARACTERE_VIDE); // Écrire le caractère espace
    gotoXY(1, 1); // Revenir au début du terminal
}

/**
 * \fn void dessinerSerpent(int lesX[], int lesY[], int taille)
 * \brief Dessine le serpent dans le terminal.
 * 
 * Cette fonction affiche le serpent dans le terminal en fonction de ses coordonnées (lesX[], lesY[]) et de sa taille.
 * 
 * \param lesX Tableau des coordonnées X des segments du serpent.
 * \param lesY Tableau des coordonnées Y des segments du serpent.
 * \param taille Taille actuelle du serpent.
 */
void dessinerSerpent(int lesX[], int lesY[], int taille) // Dessine le serpent dans le terminal
{
    for (int i = 1; i < taille; i++) // Parcourir les coordonnées corps du serpent
    {
        afficher(lesX[i], lesY[i], QUEUE); // Afficher le caractère correspondant au corps du serpent
    }
    afficher(lesX[0], lesY[0], HEAD); // Afficher la tête du serpent
    fflush(stdout);
}

/**
* \fn bool progresser(int lesX[], int lesY[], char direction, bool *collision, int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int *taille)
* \brief Fait avancer le serpent d'une case dans la direction spécifiée.
*
* Cette fonction met à jour les coordonnées de la tête du serpent, décale les autres segments,
* vérifie les collisions avec les murs, le corps du serpent et les pommes, et met à jour le plateau de jeu en conséquence.
*
* @param lesX Tableau des coordonnées X des segments du serpent.
* @param lesY Tableau des coordonnées Y des segments du serpent.
* @param direction Direction du mouvement (RIGHT, LEFT, UP, DOWN).
* @param collision Pointeur vers un booléen indiquant s'il y a eu collision.
* @param coordPlateau Tableau représentant le plateau de jeu.
* @param taille Pointeur vers la taille du serpent.
* @return true si une pomme a été mangée, false sinon.
*
* **Déroulement:**
* 1. Efface l'ancienne queue du serpent.
* 2. Décale tous les segments du serpent d'une case dans la direction opposée à la tête.
* 3. Met à jour les coordonnées de la tête du serpent selon la direction donnée.
* 4. Vérifie s'il y a une collision avec un mur, le corps du serpent ou un obstacle.
* 5. Vérifie si le serpent a mangé une pomme et met à jour le tableau du plateau en conséquence.
* 6. Met à jour la taille du serpent si une pomme a été mangée.
*/
bool progresser(int lesX[], int lesY[], char direction, bool *collision, int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int *taille) // Permet de faire progresser le serpent dans le terminal et dans la direction souhaitée
{
    bool mangee = false; // Initialisation du bouléen à false
    effacer(lesX[*taille - 1], lesY[*taille - 1]); // Effacer la queue
    for (int i = (TAILLE_MAX_SERPENT - 1); i > 0; i--) // Faire évoluer chaque coordonnées du corps du serpent
    {
        lesX[i] = lesX[i - 1];
        lesY[i] = lesY[i - 1];
    }
    if (direction == RIGHT) // Vérifier si la nouvelle direction est 'droite'
    {
        lesX[0]++; // Faire évoluer la tête d'un rang vers la droite
    }
    else if (direction == LEFT) // Vérifier si la nouvelle direction est 'gauche'
    {
        lesX[0]--; // Faire évoluer la tête d'un rang vers la gauche
    }
    else if (direction == UP)// Vérifier si la nouvelle direction est 'haut'
    {
        lesY[0]--; // Faire évoluer la tête d'un rang vers le haut
    }
    else if (direction == DOWN) // Vérifier si la nouvelle direction est 'bas'
    {
        lesY[0]++; // Faire évoluer la tête d'un rang vers le bas
    }
    for (int i = 1; i < *taille; i++) // Vérifier les collisions entre la tête et le corps du serpent
    {
        if ((lesX[i] == lesX[0]) && (lesY[i] == lesY[0]))
        {
            *collision = true; // Modification de la variable collision
        }
    }
    if ((coordPlateau[(lesX[0])][(lesY[0])] == CARACTERE_PLATEAU) || (coordPlateau[(lesX[0])][(lesY[0])] == CARACTERE_PAVE)) // Vérifier les collision entre la tête du serpent et un pavé ou une bordure du plateau
    {
        *collision = true; // Modification de la variable collision
    }
    if ((lesX[0] > X_ISSUE_DROITE) && (lesY[0] == Y_ISSUES_GAUCHE_DROITE)) // Vérifier si la tête du serpent atteint l'issue droite
    {
        lesX[0] = X_ISSUE_GAUCHE; // Faire rerentrer le serpent sur le plateau en le faisant réapparaître à l'issue gauche
    }
    else if ((lesX[0] < X_ISSUE_GAUCHE) && (lesY[0] == Y_ISSUES_GAUCHE_DROITE)) // Vérifier si la tête du serpent atteint l'issue gauche
    {
        lesX[0] = X_ISSUE_DROITE; // Faire rerentrer le serpent sur le plateau en le faisant réapparaître à l'issue droite
    }
    else if ((lesX[0] == X_ISSUES_HAUT_BAS) && (lesY[0] < Y_ISSUE_HAUT)) // Vérifier si la tête du serpent atteint l'issue d'en haut
    {
        lesY[0] = Y_ISSUE_BAS; // Faire rerentrer le serpent sur le plateau en le faisant réapparaître à l'issue d'en bas
    }
    else if ((lesX[0] == X_ISSUES_HAUT_BAS) && (lesY[0] > Y_ISSUE_BAS)) // Vérifier si la tête du serpent atteint l'issue d'en bas
    {
        lesY[0] = Y_ISSUE_HAUT; // Faire rerentrer le serpent sur le plateau en le faisant réapparaître à l'issue haut
    }
    if (coordPlateau[lesX[0]][lesY[0]] == POMME) // Vérifier si la tête du serpent atteint une pomme
    {
        mangee = true; // Modification du booléen
        coordPlateau[(lesX[0])][(lesY[0])] = CARACTERE_VIDE; // Remplacer la pomme du tableau par un espace vide
        (*taille)++; // Augmentation de la taille du serpent
    }
    dessinerSerpent(lesX, lesY, *taille); // Afficher le serpent à sa nouvelle position
    return mangee; // Transmettre au programme principal si une pomme a été mangée ou non
}

/**
* \fn void initPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU])
* \brief Initialise le plateau de jeu.
*
* Cette fonction crée le plateau de jeu en initialisant chaque case avec la valeur appropriée 
* (bordure, espace vide). Elle ajoute également les obstacles (pavés) de manière aléatoire.
*
* @param coordPlateau Tableau à deux dimensions représentant le plateau de jeu.
* Chaque élément du tableau correspond à une case du plateau et contient un caractère 
* représentant le contenu de la case (mur, espace vide, pomme, etc.).
*/
void initPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU]) // Permert de créer le plateau de jeu aux dimensions souhaitées avec le nombre de pavés (obstacles) souhaités
{
    for (int i = DECALAGE; i < LARGEUR_TABLEAU_PLATEAU; i++) // Pour toute la largeur du plateau
    {
        for (int j = DECALAGE; j < HAUTEUR_TABLEAU_PLATEAU; j++) // Pour toute la hauteur du plateau
        {
            if (((i == X_BORDURE_GAUCHE_PLATEAU || i == X_BORDURE_DROITE_PLATEAU || j == Y_BORDURE_HAUT_PLATEAU || j == Y_BORDURE_BAS_PLATEAU)) && (((i != X_ISSUE_GAUCHE) || (j != Y_ISSUES_GAUCHE_DROITE)) && ((i != X_ISSUE_DROITE) || (j != Y_ISSUES_GAUCHE_DROITE)) && ((i != X_ISSUES_HAUT_BAS) || (j != Y_ISSUE_HAUT)) && ((i != X_ISSUES_HAUT_BAS) || (j != Y_ISSUE_BAS)))) // Vérifier que les coordonnées correspondent aux limites du plateau
            {
                coordPlateau[i][j] = CARACTERE_PLATEAU; // Placer un caractère délimitant le plateau à cette position dans le tableau
            }
            else // Si ces coordonnées apparatiennent à la partie itérieure du plateau de jeu
            {
                coordPlateau[i][j] = CARACTERE_VIDE; // Placer un caractère représentant le vide à cette position dans le tableau
            }
        }
    }
    srand(time(NULL)); // Permet de générer différentes coordonnées aléatoires
    for (int i = 0; i < NOMBRE_DE_PAVES; i++) // Pour chaque pavé souhaité
    {
        int x = (rand() % ((X_MAX_PAVE + 1) - X_MIN_PAVE)) + X_MIN_PAVE; // Générer une coordonnée X aléatoire pour le coin supérieur hauche du pavé, en évitant et en maintenant un écart avec les bords
        int y = (rand() % ((Y_MAX_PAVE + 1) - Y_MIN_PAVE)) + Y_MIN_PAVE; // Générer une coordonnée Y aléatoire pour le coin supérieur hauche du pavé, en évitant et en maintenant un écart avec les bords
        // Conditions pour éviter les chevauchements avec le serpent au départ
        if ((y >= Y_INITIAL - (TAILLE_PAVE - 1)) && (y <= Y_INITIAL)) // Vérifier si la coordonnée Y d'un élément du pavé correspond à une coordonnée Y d'un élément du serpent
        {
            if (((x >= X_INITIAL - (TAILLE_INITIALE_SERPENT - 1)) || ((x + TAILLE_PAVE - 1) >= (X_INITIAL - (TAILLE_INITIALE_SERPENT - 1)))) && (x <= X_INITIAL)) // Vérifier si une coordonnée X d'un élément du pavé correspond à une coordonnée X d'un élément du serpent 
            {
                y += TAILLE_PAVE; // Décaler le pavé vers le bas d'un nombre de rangs correspondant à sa taille pour éviter le chevauchement avec le serpent
            }
        }
        // Remplir les cases du pavé dans le tableau
        for (int j = 0; j < TAILLE_PAVE; j++) // Pour toute la largeur du pavé
        {
            for (int k = 0; k < TAILLE_PAVE; k++) // Pour toute la hauteur du pavé
            {
                coordPlateau[x + j][y + k] = CARACTERE_PAVE; // Placer un caractère représentant un pavé à la position correspondante dans le tableau
            }
        }
    }
    dessinerPlateau(coordPlateau); // Permet de dessiner le plateau à partir du tableau comportant ses éléments aux positions définies
}

/**
 * \fn void dessinerPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU])
 * \brief Dessine le plateau de jeu à partir du tableau des coordonnées.
 * 
 * Cette fonction parcourt le tableau du plateau et affiche chaque élément à sa position respective dans le terminal.
 * 
 * \param coordPlateau Plateau de jeu sous forme de tableau à deux dimensions.
 */
void dessinerPlateau(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU]) // Permet de dessiner le plateau
{
    for (int i = 0; i < LARGEUR_TABLEAU_PLATEAU; i++) // Pour toute la largeur du plateau
    {
        for (int j = 0; j < HAUTEUR_TABLEAU_PLATEAU; j++) // Pour toute la hauteur du plateau
        {
            afficher(i, j, coordPlateau[i][j]); // Afficher chaque élément du plateau à sa position dans le terminal
        }
    }
}

/**
* \fn void ajouterPomme(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int lesX[], int lesY[], int taille)
* \brief Ajoute une pomme à une position aléatoire sur le plateau, en évitant les collisions avec le serpent et les obstacles.
*
* Cette fonction choisit aléatoirement une position libre sur le plateau et y place une pomme.
* Elle vérifie que la position choisie ne correspond ni à une case occupée par le serpent, ni à un obstacle.
* Si toutes les cases du plateau sont occupées, la fonction ne fait rien.
*
* @param coordPlateau Tableau à deux dimensions représentant le plateau de jeu.
* @param lesX Tableau des coordonnées X des segments du serpent.
* @param lesY Tableau des coordonnées Y des segments du serpent.
* @param taille Taille du serpent.
*/
void ajouterPomme(int coordPlateau[LARGEUR_TABLEAU_PLATEAU][HAUTEUR_TABLEAU_PLATEAU], int lesX[], int lesY[], int taille) // Permet de faire apparaître une pomme à une position aléatoire sur le plateau de jeu et de l'ajouter au tableau des coordonnées du plateau
{
    int x = 0; // Initialisation de la coordonée x de la pomme à 0
    int y = 0; // Initialisation de la coordonée y de la pomme à 0
    bool superposition = false; // Initialisation du booléen superposition à false
    while ((coordPlateau[x][y] != CARACTERE_VIDE) || (superposition == true)) // Tant que la position de la pomme ne correspond pas à un espace vide du plateau ou qu'elle se superpose avec le serpent
    {
        superposition = false; // Mettre la variable booléenne superposition à false
        x = (rand() % ((X_MAX_POMME + 1) - X_MIN_POMME)) + X_MIN_POMME; // Générée une position x de la pomme aléatoirement dans le plateau
        y = (rand() % ((Y_MAX_POMME + 1) - Y_MIN_POMME)) + Y_MIN_POMME; // Générée une position y de la pomme aléatoirement dans le plateau
        for (int i = 0; i < taille; i++) // Vérifier la superposition entre le serpent et la pomme
        {
            if ((lesX[i] == x) && (lesY[i] == y))
            {
                superposition = true; // Mettre la variable booléenne superposition à true
            }
        }
    }
    coordPlateau[x][y] = POMME; // Intégrer la pomme au tableau des coordonnées des éléments du plateau
    afficher(x, y, POMME); // afficher la pomme dans le plateau de jeu
}