# 🐍 Snake en C

Ce projet est une implémentation du jeu classique **Snake** en langage C, jouable directement dans un terminal.

![Langage C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Terminal](https://img.shields.io/badge/Terminal-black?style=for-the-badge&logo=windows-terminal&logoColor=white)
![Licence MIT](https://img.shields.io/badge/Licence-MIT-green?style=for-the-badge)

---

## ✨ Fonctionnalités

- 🎮 Déplacement du serpent avec les touches directionnelles
- 🍏 Apparition aléatoire de la nourriture
- 🐍 Augmentation de la longueur du serpent à chaque nourriture mangée
- 💥 Détection des collisions (murs et corps du serpent)
- 🏆 Affichage du score et augmentation progressive de la vitesse
- 🖥️ Jeu entièrement en mode texte (terminal)

## ⚙️ Prérequis

- Un compilateur C ([GCC](https://gcc.gnu.org/) recommandé)
- Un terminal compatible (Linux, macOS ou Windows avec un terminal prenant en charge les séquences ANSI)

## 🛠️ Compilation

```bash
gcc -o snake snake.c
```

## ▶️ Lancement du jeu

```bash
./snake
```

## 🎯 Contrôles

- ⬅️ ➡️ ⬆️ ⬇️ : déplacer le serpent
- `Q` ou `Échap` : quitter le jeu

## 📁 Structure du projet

- `snake.c` : code source principal du jeu
- `README.md` : ce fichier d’aide
- `doc/` : documentation éventuelle

## 👤 Auteur

- Ewen Thépot
