# Mesurer avant de croire

## Coordonnées du chapitre
|Fichiers source, |nbre|
|--|--|
|``*.cpp`` & ``*.h``|2641|
|Ligne de code|1 193 385|

---

## Coordonnées trouvées

|Fichiers source|Nbre|nbre de ligne||
|--|--|--|--|
|``*.cpp``|1613|175148|
|``*.h``|2762|144265|
||4 375|319 413|**Total**|

``Remarque:`` Je constate qu'il y'a moins de ligne de code et de fichier que ce qui est mentionné dans le chapitre.

# Commande CLI

Ces différentes commande ont été taper dans le MINGW:
* ``find . -type f \( -name "*.cpp" \) | wc -l`` : Commande pour afficher le nombre de fichier ``*.cpp``

* ``find . -type f \( -name "*.h" \) | wc -l``  : Commande pour afficher le nombre de fichier ``*.h``

* ``find . -type f \( -name "*.h" \) -exec wc -l {} +`` : Commande pour afficher le nombre de ligne de code total de tous les fichiers `*.h`;

* ``find . -type f \( -name "*.cpp" \) -exec wc -l {} +`` : Commande pour afficher le nombre de ligne de code total de tous les fichiers `*.cpp`;