# le temps que ça prend

Pour la construction complète de `NKMath` via la commande **jenga b --project NKMath** il fallut `2.93s`.

Afin de reconstruire **NKMath**n j'ai du faire un `jenga c --project NKMath`. Puis j'ai réconstruit le projet pour une durée de `37.90s`

`Remarque:` A l'exercice 3 **Le module seul** j'ai eu à construire NKMath. Dans cete exercice, afin d'analyser les différents temps d'exécution j'ai du faire un `jenga c --project NKMath` afin de supprimer de fichier `*.obj` & `*.lib` qui sont des librairies et objets necessaire à la construction d'un projet.

**CONCLUSION :** Ce qui explique cet écart temporelle est l'existence de ces fichiers.