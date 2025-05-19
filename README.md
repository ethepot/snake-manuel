# snake-manuel
Jeu de Snake en langage C
# Snake en C

Ce projet est une implémentation du jeu classique **Snake** en langage C, jouable directement dans un terminal.

## Fonctionnalités

- Déplacement du serpent avec les touches directionnelles
- Apparition aléatoire de la nourriture
- Augmentation de la longueur du serpent à chaque nourriture mangée
- Détection des collisions (murs et corps du serpent)
- Affichage du score et augmentation progressive de la vitesse
- Jeu entièrement en mode texte (terminal)

## Prérequis

- Un compilateur C (GCC recommandé)
- Un terminal compatible (Linux, macOS ou Windows avec un terminal prenant en charge les séquences ANSI)

## Compilation

Dans le dossier du projet, exécutez :

```bash
gcc -o snake snake.c
```

## Lancement du jeu

```bash
./snake
```

## Contrôles

- **Flèches directionnelles** : déplacer le serpent
- **Q** ou **Échap** : quitter le jeu

## Structure du projet

- `snake.c` : code source principal du jeu
- `README.md` : ce fichier d’aide
- `doc/` : documentation éventuelle

## Auteurs

- Ewen Thépot

## Licence

Ce projet est proposé sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus d’informations.
