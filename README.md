# Analyseur Syntaxique

Ce projet permet de lire une expression mathématique sous forme de texte, de vérifier qu'elle est correctement écrite, et d'en calculer le résultat.

Les opérations supportées sont : l'addition (`+`), la multiplication (`*`), les entiers, et les parenthèses.

Exemple : `(1+36)*123*2`

---

## Structure du projet

### `lexer` — Le découpeur de texte
Le lexer lit la chaîne de caractères et la découpe en **symboles** : un entier, un `+`, un `*`, une parenthèse, etc.  
Il avance dans la chaîne au fur et à mesure de l'analyse.

### `symbole` — Les types de symboles
Définit les différents types de symboles reconnus :
- `Entier` : un nombre entier (ex: `42`)
- `Expr` : le résultat d'une expression déjà analysée
- Ainsi que les symboles spéciaux : `PLUS`, `MULT`, `OPENPAR`, `CLOSEPAR`, `FIN`

### `automate` — La machine d'analyse
L'automate est le moteur principal. Il maintient deux piles :
- Une **pile d'états** : indique à quelle étape de l'analyse on se trouve
- Une **pile de symboles** : stocke les symboles lus en attente d'être réduits

Il effectue deux types d'actions :
- **Décalage (shift)** : lire le prochain symbole et avancer
- **Réduction (reduce)** : remplacer plusieurs symboles de la pile par le résultat d'une règle

### `state` — Les états de l'automate
Chaque état (`E0` à `E9`) définit quoi faire selon le prochain symbole lu

---

## Comment ça marche ?

1. Le `main` crée un `Lexer` avec la chaîne à analyser.
2. Il crée un `Automate` et lui place l'état initial `E0`.
3. Dans une boucle, il consulte le prochain symbole via le lexer, et appelle la méthode `transition` de l'état courant.
4. L'état décide de faire un **décalage** ou une **réduction**.
5. Quand `E1` reçoit le symbole de fin (`FIN`), l'analyse est terminée et le résultat est récupéré depuis la pile.

---

## Compilation et exécution

```bash
make
./main
```

La sortie affiche étape par étape l'exécution de l'automate. Ensuite, on affiche soit le résultat de l'expression, soit un message d'erreur de syntaxe.

---

## Tests

```bash
make tests
./tests
```

Le fichier `tests.cpp` vérifie le bon fonctionnement de l'analyseur sur deux catégories de cas.
