

**Compter le nombre de lignes de code**

Pour compter le nombre total de lignes de code pour les extensions `.cpp` et `.h` dans un dossier et tous ses sous-dossiers :

* **Commande standard (Linux/macOS) :**
`find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +`
*(Cette commande affiche le nombre de lignes par fichier ainsi qu'une ligne `total` à la fin).*
* **Alternative avec l'outil `cloc` (recommandé) :**
`cloc .`
*(Installez-le via `sudo apt install cloc` ou `brew install cloc`. Il est plus intelligent car il exclut automatiquement les commentaires et les lignes vides).*

---

**Compter le nombre de fichiers ayant une extension précise**

Pour compter exactement combien de fichiers `.cpp` et `.h` sont présents dans le projet :

* **Pour les deux extensions combinées :**
`find . -type f \( -name "*.cpp" -o -name "*.h" \) | wc -l`
* **Pour une extension spécifique (ex: uniquement les fichiers `.cpp`) :**
`find . -type f -name "*.cpp" | wc -l`
* **Pour les fichiers `.h` uniquement :**
`find . -type f -name "*.h" | wc -l`

---

**Linux et macOS (Bash)**

* **Fichiers `.cpp` et `.h` combinés :**
`find . -type f \( -name "*.cpp" -o -name "*.h" \) | wc -l`
* **Fichiers `.cpp` uniquement :**
`find . -type f -name "*.cpp" | wc -l`
* **Fichiers `.h` uniquement :**
`find . -type f -name "*.h" | wc -l`

**Windows (PowerShell)**

* **Fichiers `.cpp` et `.h` combinés :**
`(Get-ChildItem -Recurse -Include *.cpp, *.h).Count`
* **Fichiers `.cpp` uniquement :**
`(Get-ChildItem -Recurse -Filter *.cpp).Count`
* **Fichiers `.h` uniquement :**
`(Get-ChildItem -Recurse -Filter *.h).Count`

---
# Compter le nombre de ligne de code

**Linux et macOS (Bash)**

* **Méthode standard (compte toutes les lignes, y compris les vides et les commentaires) :**
`find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +`
*(Cette commande affiche le nombre de lignes de chaque fichier individuel ainsi qu'une ligne `total` à la fin).*
* **Méthode recommandée avec l'outil `cloc` (exclut automatiquement les commentaires et les lignes vides) :**
`cloc .`
*(Nécessite d'installer l'outil au préalable via `sudo apt install cloc` sur Ubuntu/Debian ou `brew install cloc` sur macOS).*

---

**Windows (PowerShell)**

* **Compter le nombre total de lignes (fichiers `.cpp` et `.h` combinés) :**
`(Get-ChildItem -Recurse -Include *.cpp, *.h | Get-Content).Count`
* **Pour un fichier spécifique ou une seule extension (ex: uniquement `.cpp`) :**
`(Get-ChildItem -Recurse -Filter *.cpp | Get-Content).Count`

# Trouver un dossie rspécifique

**Linux et macOS (Bash)**

* **Recherche par nom exact :**
`find . -type d -name "nom_du_dossier"`
* **Recherche insensible à la casse (ignore les majuscules/minuscules) :**
`find . -type d -iname "nom_du_dossier"`
* **Recherche partielle (contient un mot) :**
`find . -type d -name "*mot_cle*"`

---

**Windows (PowerShell)**

* **Recherche par nom exact ou partiel :**
`(Get-ChildItem -Recurse -Directory -Filter "*nom_du_dossier*").FullName`