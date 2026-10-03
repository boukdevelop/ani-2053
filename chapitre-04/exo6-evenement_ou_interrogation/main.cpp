#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Optimisation des entrées/sorties
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long v;
    int n;

    if (!(cin >> v >> n))
    {
        cout << "SAUTS EVENEMENTS 0\n";
        cout << "SAUTS INTERROGATION 0\n";
        cout << "MANQUES 0\n";
        return 0;
    }

    // États des touches (maintenus d'une image à l'autre)
    bool space_pressed = false;
    bool right_pressed = false;
    bool left_pressed = false;

    // Positions des carrés
    long long xe = 0;   // Par événements
    long long xi = 0;   // Par interrogation

    // Compteurs
    long long sauts_events = 0;
    long long sauts_interrogation = 0;
    long long manques = 0;

    for (int i = 1; i <= n; ++i)
    {
        int k;
        cin >> k;

        bool space_pressed_in_frame = false;

        for (int j = 0; j < k; ++j)
        {
            string ev;
            cin >> ev;

            if (ev.length() < 2)
                continue;

            char action = ev[0];
            string name = ev.substr(1);

            if (name == "SPACE")
            {
                if (action == '+')
                {
                    ++sauts_events;
                    space_pressed = true;
                    space_pressed_in_frame = true;
                }
                else if (action == '-')
                {
                    space_pressed = false;
                }
            }
            else if (name == "RIGHT")
            {
                if (action == '+')
                {
                    xe += v;
                    right_pressed = true;
                }
                else if (action == '-')
                {
                    right_pressed = false;
                }
            }
            else if (name == "LEFT")
            {
                if (action == '+')
                {
                    xe -= v;
                    left_pressed = true;
                }
                else if (action == '-')
                {
                    left_pressed = false;
                }
            }
        }

        // Interrogation à la fin de l'image
        if (space_pressed)
        {
            ++sauts_interrogation;
        }
        if (right_pressed)
        {
            xi += v;
        }
        if (left_pressed)
        {
            xi -= v;
        }

        // Vérification des appuis manqués par l'interrogation
        if (space_pressed_in_frame && !space_pressed)
        {
            ++manques;
        }

        // Affichage de la ligne pour l'image courante
        cout << i << ' ' << xe << ' ' << xi << '\n';
    }

    // Bilan final
    cout << "SAUTS EVENEMENTS " << sauts_events << '\n';
    cout << "SAUTS INTERROGATION " << sauts_interrogation << '\n';
    cout << "MANQUES " << manques << '\n';

    return 0;
}
