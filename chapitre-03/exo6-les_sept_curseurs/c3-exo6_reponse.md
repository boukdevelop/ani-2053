# Les septs curseurs

> ***Énoncé :***
Découpez la fenêtre en sept zones et changez la forme du curseur selon la zone survolée. Puis ne posez le curseur qu'une seule fois, au démarrage, et décrivez ce qui se passe.

---

Cette partie du code listes les septs états du curseurs tout en stockant leur nom, le tout dans des tableau spécifique de dim = 7 chacun :

```cpp

    // Les septs bandes de gauche à droite
    const NkWindow::NkCursorType curseurs[7] = {
        NkWindow::NkCursorType::Arrow,
        NkWindow::NkCursorType::TextInput,
        NkWindow::NkCursorType::Hand,
        NkWindow::NkCursorType::ResizeNS,
        NkWindow::NkCursorType::ResizeWE,
        NkWindow::NkCursorType::ResizeNWSE,
        NkWindow::NkCursorType::ResizeNESW};

    const char *nomsCurseurs[7] = {
        "Arrow", "TextInput", "Hand", "ResizeNS", "ResizeWE", "ResizeNWSE", "ResizeNESW"};

```

---

CEtte partie vérifie si l'évènement courant est un évènement de sourie, si oui le code donne accès aux coordonnées de la souries :

```cpp
if (auto *mouvement = event->As<NkMouseMoveEvent>())
{...}
```

---

Cette zone est a titre de sécurité, car elle permet d'ignorer la position du curseur si la taille de la fenêtre est trop petite ou si le curseur dépasse la zone limite. Et passe à l'itération suivante :

```cpp
                if (taille.x == 0 || taille.y == 0 || x < 0 || y < 0 ||
                    static_cast<uint32>(x) >= taille.x || static_cast<uint32>(y) >= taille.y)
                {
                    continue;
                }
```

---

Je ne saurais passer sasn toutes fois parler de la fonction qui divise les septs zones en question :

```cpp
                uint32 zone = static_cast<uint32>(
                    (static_cast<float32>(x) * 7.0f) / static_cast<float32>(taille.x));
```

---

Etant donné qu'au démarrage de la fenêtre, la souris ne changeait pas de forme(juste le message), il a fallut récupérer changer réellement la forme de la souries à chaque évènement(même si la souries est dans la même zône).
