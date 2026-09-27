# Le glisser qui sort

> ***Énoncé :***
Faites un glisser qui commence dans la fenêtre et continue à l'extérieur, une fois sans capture, une fois avec. Décrivez la différence du point de vue de l'utilisateur.

---

Cette zone me peret de tester comme bon me semble:

```cpp
///////////////////////////
            bool capturerPendantGlisser = false; // premier essai : sans capture
            bool enGlisser = false;
```

---

Dans cette zone, il s'agit presque du même procédé qu'à lexercice précédent, où l'on vérifie l'évènement de la sourie avant de capturer sa position :

```cpp

            if (auto *press = event->As<NkMouseButtonPressEvent>())
            {
                if (press->IsLeft())
                {
                    enGlisser = true;

                    if (capturerPendantGlisser)
                    {
                        window.CaptureMouse(true);
                    }

                    logger.Info("[drag] debut");
                }
            }
            else if (auto *release = event->As<NkMouseButtonReleaseEvent>())
            {
                if (release->IsLeft())
                {
                    if (capturerPendantGlisser)
                    {
                        window.CaptureMouse(false);
                    }

                    enGlisser = false;
                    logger.Info("[drag] fin");
                }
            }
```

***REMARQUE :*** Lorsque la souris fais un glisser sur la fenêtre, le code renvoit le code `"[drag] debut"` et lorsqu'il s'arrête en lachant le ``click gauche`` un message `"[drag] fin"` est inscrit.Mais si par mégarde la souris est laché pendant le glissé hors de la zône, le message reste debut pour signifier que le processus est toujours en cours.