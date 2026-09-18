> # La règle du dépôt

***Énoncé :***
Rédigez, pour un groupe de quatre étudiants, les règles git du projet : nommage des branches, contenu d'un commit, qui relit quoi, ce qui est interdit, et ce qu'on fait quand quelqu'un casse la branche principale. Une page, applicable dès demain.
--

# Protocole Git : Règles du Projet (Équipe de 4)

Ces règles entrent en vigueur dès demain pour garantir un historique propre, faciliter le travail en équipe et éviter les conflits bloquants.

## 1. Nommage des branches

Chaque nouvelle tâche doit être développée sur une branche dédiée (jamais sur `main`). Utilisez un préfixe standard suivi d'une description courte en minuscules, séparée par des tirets :

* **`feat/`** : Pour une nouvelle fonctionnalité (ex: `feat/page-connexion`)
* **`fix/`** : Pour corriger un bug (ex: `fix/bouton-invisible`)
* **`docs/`** : Pour la documentation ou le README (ex: `docs/ajout-schema-bdd`)
* **`refactor/`** : Pour du nettoyage de code sans ajout de fonctionnalité.

## 2. Contenu et message d'un commit

Un commit doit raconter une histoire claire de l'évolution du projet.

* **Une idée = Un commit :** Ne mélangez pas la création de la page d'accueil avec la correction d'un bug sur le menu dans le même commit. Bien dire ce qui a été fait avec description à la clé si possible.
* **Le message :** Il doit être court, clair, et commencer par un verbe d'action à l'infinitif ou au présent (ex: `Ajoute le formulaire de contact` ou `Corrige le crash sur la page profil`). Du genre:
    * ce commit fait telle chose, 
    * ce commit Ecris ceci,
    * etc,...
* **Tester avant de commit :** Ne commitez jamais un code qui ne compile pas ou qui fait planter l'application en local. ⚠⚠

## 3. Revue de code (Qui relit quoi ?)

Le travail d'équipe implique de ne pas fusionner son propre code seul.

* **Processus :** Quand une branche est terminée, ouvrez une *Pull Request (PR)* (ou *Merge Request*) vers la branche `main`.
* **La règle de validation :** Au moins **un des trois autres membres** de l'équipe doit relire et approuver le code avant la fusion.
* **Le rôle du relecteur :** Vérifier que le code fonctionne en local, qu'il est lisible, et qu'il respecte ce qui a été demandé. Si tout est bon, le relecteur valide (Approve) et l'auteur de la PR clique sur *Merge*.

## 4. Les interdits absolus

Pour la survie du projet, les actions suivantes sont formellement interdites :

* ⚠ **Pousser (push) directement sur `main` :** La branche principale est sacrée et ne reçoit du code que via des Pull Requests validées.
* **Le `git push -f` (Force Push) :** Totalement interdit sur `main` et sur les branches partagées par plusieurs personnes. Cela écrase l'historique des autres.
* ⚠ **Commiter des secrets ou des fichiers lourds :** Mots de passe, clés d'API, bases de données locales, et dossiers générés (comme `node_modules` ou `__pycache__`) doivent être ignorés via le fichier `.gitignore` dès le premier jour.

## 5. Protocole de crise : La branche `main` est cassée

Si quelqu'un fusionne du code qui fait planter la branche principale, voici la marche à suivre immédiate :

1. **Alerter l'équipe :** Signalez immédiatement le problème sur votre canal de communication (Discord, WhatsApp, etc.). Les autres membres **ne doivent plus pull/merge** sur `main` tant que ce n'est pas résolu.
2. **Ne pas paniquer (ni bidouiller à l'aveugle) :** N'essayez pas de faire un *force push* pour revenir en arrière.
3. **Appliquer la solution propre :**
* Si le bug est petit et évident : L'auteur (aidé de son relecteur) crée une branche `hotfix/nom-du-bug`, corrige le tir en 10 minutes, et fait une PR express.
* Si le bug est complexe : Utilisez la commande `git revert <id-du-mauvais-commit>` pour créer un nouveau commit qui annule proprement les changements cassés, puis poussez cette réparation. La fonctionnalité pourra être retravaillée calmement sur une autre branche.