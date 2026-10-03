#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Structure pour conserver les transformations absolues dans le monde
struct ObjectWorld {
    long long x;
    long long y;
    long long angle;    // Entre 0 et 270 (0, 90, 180, 270)
    long long echelle;
    long long niveau;
};

// Fonction utilitaire pour obtenir cos et sin pour les angles multiples de 90
void getCosSin(long long angle, long long &c, long long &s) {
    long long norm = (angle % 360 + 360) % 360;
    switch (norm) {
        case 0:   c = 1;  s = 0;  break;
        case 90:  c = 0;  s = 1;  break;
        case 180: c = -1; s = 0;  break;
        case 270: c = 0;  s = -1; break;
        default:  c = 1;  s = 0;  break;
    }
}

int main()
{
    // Acceleration des entrees/sorties C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
    {
        cout << "PROFONDEUR 0\n";
        return 0;
    }

    unordered_map<string, ObjectWorld> world_objects;
    vector<string> order;    // Pour conserver l'ordre d'affichage
    long long max_profondeur = 0;

    for (int i = 0; i < n; ++i)
    {
        string name, parent;
        long long tx, ty, angle, echelle;

        if (!(cin >> name >> parent >> tx >> ty >> angle >> echelle))
            break;

        ObjectWorld obj;

        if (parent == "-")
        {
            // Objet racine (sans parent)
            obj.x = tx;
            obj.y = ty;
            obj.angle = (angle % 360 + 360) % 360;
            obj.echelle = echelle;
            obj.niveau = 1;
        }
        else
        {
            // Objet avec parent
            const ObjectWorld &p = world_objects[parent];

            // Echelle du parent appliquee a la position locale
            long long ax = tx * p.echelle;
            long long ay = ty * p.echelle;

            // Rotation du point selon l'angle du parent
            long long c, s;
            getCosSin(p.angle, c, s);

            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            // Translation par la position du parent
            obj.x = p.x + rx;
            obj.y = p.y + ry;

            // Composition de l'angle et de l'echelle
            obj.angle = ((p.angle + angle) % 360 + 360) % 360;
            obj.echelle = p.echelle * echelle;
            obj.niveau = p.niveau + 1;
        }

        world_objects[name] = obj;
        order.push_back(name);

        if (obj.niveau > max_profondeur)
        {
            max_profondeur = obj.niveau;
        }
    }

    // Affichage des resultats dans l'ordre de lecture
    for (const string &name : order)
    {
        const ObjectWorld &obj = world_objects[name];
        cout << name << ' ' << obj.x << ' ' << obj.y << ' ' 
             << obj.angle << ' ' << obj.echelle << '\n';
    }

    // Affichage de la profondeur maximale
    cout << "PROFONDEUR " << max_profondeur << '\n';

    return 0;
}
