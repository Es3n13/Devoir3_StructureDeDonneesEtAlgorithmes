# Devoir 3 — Liste Doublement Chaînée avec Suppression Paresseuse

**Cours :** Structures de données et algorithmes (INF21307)
**Université :** UQAR
**Date limite :** 14 avril 2026

## 📋 Description

Ce projet implémente une **liste doublement chaînée** avec **suppression paresseuse** (lazy deletion). Cette technique permet de marquer les nœuds comme supprimés sans les retirer physiquement de la mémoire, ce qui améliore les performances pour les opérations fréquentes de suppression.

### Fonctionnalités

- ✅ **Ajout (`O(1)`)** : Ajout rapide à la fin de la liste
- ✅ **Recherche (`O(n)`)** : Recherche de la première occurrence d'une valeur
- ✅ **Suppression paresseuse (`O(n)`)** : Marque logiquement le nœud comme supprimé sans le retirer
- ✅ **Compactage (`O(n)`)** : Retire physiquement tous les nœuds marqués libres
- ✅ **Itérateur intelligent** : Parcourt automatiquement les nœuds actifs (saute les nœuds supprimés)
- 🎁 **Nœuds sentinelles (bonus)** : Élimine les vérifications de nullité et simplifie le code

## 📁 Structure du projet

```
Devoir3_StructureDeDonneesEtAlgorithmes/
├── listechainee.h          # Définitions des classes et structures
├── listechainee.cpp        # Implémentation complète des méthodes
├── main.cpp                # Interface console en français
├── README.md               # Ce fichier
└── Devoir3_ListesDoublementChainees.*    # Fichiers de projet Visual Studio
```

## 🏗️ Architecture

### Structure de nœud

```cpp
struct Node {
    int data;        // Données du nœud
    bool isFree;     // Drapeau de suppression paresseuse
    Node* prev;      // Pointeur vers le nœud précédent
    Node* next;      // Pointeur vers le nœud suivant
};
```

### Classe principale

**Méthodes publiques :**
- `void ajouter(int value)` — Ajoute un nœud à la fin
- `Node* trouver(int value)` — Retourne le premier nœud actif contenant la valeur
- `bool supprimer(int value)` — Marque le nœud comme supprimé
- `void compacter()` — Retire physiquement tous les nœuds libres
- `void afficher() const` — Affiche l'état de la liste (avec les nœuds libres)
- `Iterator begin()` — Retourne un itérateur sur le premier élément actif

### Itérateur

L'itérateur traverse uniquement les nœuds actifs :
```cpp
auto it = list.begin();
while (it.hasNext()) {
    int valeur = it.next();  // Sauté automatiquement les nœuds [FREE]
}
```

## 🚀 Compilation et Exécution

### Compilation (Linux/macOS)

```bash
g++ -std=c++17 -o devoir3 main.cpp listechainee.cpp
```

### Exécution

```bash
./devoir3
```

### Visual Studio (Windows)

Ouvrir le fichier `Devoir3_ListesDoublementChainees.slnx` et compiler.

## 📖 Utilisation

Le programme offre un menu interactif en français :

```
=== Liste doublement chainee ===
1. Ajouter une valeur
2. Trouver une valeur
3. Supprimer une valeur
4. Compacter la liste
5. Afficher la liste
6. Quitter
Choix :
```

### Exemple d'utilisation

```
1. Ajouter 10  →  Valeur 10 ajoutée.
1. Ajouter 20  →  Valeur 20 ajoutée.
1. Ajouter 30  →  Valeur 30 ajoutée.
5. Afficher    →  [HEAD] <-> 10 <-> 20 <-> 30 <-> [TAIL]

3. Supprimer 20 →  Valeur 20 marquée comme supprimée.
5. Afficher    →  [HEAD] <-> 10 <-> [FREE:20] <-> 30 <-> [TAIL]

Itérateur : 10 30   // 20 est automatiquement sauté

4. Compacter   →  Tous les nœuds libres ont été retirés.
5. Afficher    →  [HEAD] <-> 10 <-> 30 <-> [TAIL]
```

## 🎓 Concepts théoriques

### Avantages de la suppression paresseuse

- ✅ **Performance** : Marquer un nœud comme supprimé est `O(1)` (après recherche)
- ✅ **Batch processing** : Plusieurs suppressions peuvent être regroupées dans un compactage
- ✅ **Utilisation mémoire** : Les nœuds peuvent être réutilisés si nécessaire

### Complexité des opérations

| Opération | Complexité | Description |
|----------|------------|-------------|
| `ajouter` | `O(1)` | Insertion constante à la fin |
| `trouver` | `O(n)` | Recherche linéaire dans la liste |
| `supprimer` | `O(n)` | Recherche + marquage |
| `compacter` | `O(n)` | Parcours complet + suppression |
| Itérateur | `O(n)` | Saute les nœuds libres automatiquement |

### Bonus : Nœuds Sentinelles

Les nœuds sentinelles (`headSentinel` et `tailSentinel`) :
- Simplifient le code en éliminant les vérifications de nullité
- Rendent les insertions/suppressions aux extrémités uniformes
- Permettent un itérateur plus robuste

## 🧪 Tests effectués

- ✅ Ajout de plusieurs valeurs
- ✅ Recherche de valeurs existantes et inexistantes
- ✅ Suppression paresseuse (marquage)
- ✅ Vérification que l'itérateur saute les nœuds supprimés
- ✅ Compactage après plusieurs suppressions
- ✅ Gestion d'une liste vide
- ✅ Destruction propre (tous les nœuds libérés)

## 👨‍🎓 Auteur

**Étudiants :** Émile Santerre & Léa Esso-Solam Bikassa
**Cours :** INF21307 — Structures de données et algorithmes
**Session :** Hiver 2026

## 📄 Configuration recommandée

- **Compilateur** : `g++` (GCC) ou `clang++` avec support C++17
- **Visual Studio** : 2019 ou plus récent
- **Système** : Linux, macOS, Windows

---
