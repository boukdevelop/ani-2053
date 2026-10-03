#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Normalise l'angle pour qu'il soit dans [0, 360)
// puis vérifie s'il est multiple de 90.
// Si oui, donne cos/sin correspondants.
bool IsValidAngle(long long angle, int &cos, int &sin)
{
    angle = ((angle % 360) + 360) % 360;

    if (angle % 90 != 0)
        return false;

    switch (angle / 90)
    {
    case 0: // 0°
        cos = 1;
        sin = 0;
        break;
    case 1: // 90°
        cos = 0;
        sin = 1;
        break;
    case 2: // 180°
        cos = -1;
        sin = 0;
        break;
    case 3: // 270°
        cos = 0;
        sin = -1;
        break;
    default:
        return false;
    }

    return true;
}

int main()
{
    int n;

    cout << "Ce programme lit une ligne avec un entier N, puis N lignes nom w h px py ox oy sx sy angle\n"
         << "* w et h : la largeur et la hauteur du rectangle ;\n"
         << "* px py : sa position dans le monde ;\n"
         << "* ox oy : son origine, en coordonnées locales ;\n"
         << "* sx sy : son échelle sur chaque axe ;\n"
         << "* angle : sa rotation, en degrés.\n"
         << "\n============================"
         << "\nExemples d'entrées :\n"
         << "3\ncoin 100 40 300 200 0 0 1 1 90\ncentre 100 40 300 200 50 20 1 1 90\npenche 100 40 300 200 50 20 1 1 45"
         << "\n\nVeuillez entrer le nombre de ligne(entier) : " << endl;

    cin >> n;

    if (!n)
        return 0;

    long long refusals = 0;

    for (int i = 0; i < n; ++i)
    {
        string name;
        long long w, h, px, py, ox, oy, sx, sy, angle;

        cout << "FORMAT ACCEPTE :\nnom w h px py ox oy sx sy angle\n";

        if (!(cin >> name >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle))
            return 0;

        int cos, sin;

        if (!IsValidAngle(angle, cos, sin))
        {
            cout << name << " ANGLE REFUSE\n";
            ++refusals;
            continue;
        }

        // Coins locaux du rectangle dans l'ordre :
        // (0,0), (w,0), (w,h), (0,h)
        long long localX[4] = {0, w, w, 0};
        long long localY[4] = {0, 0, h, h};

        long long cornerX[4];
        long long cornerY[4];

        for (int j = 0; j < 4; ++j)
        {
            // 1) retirer l'origine locale
            long long ax = (localX[j] - ox) * sx;
            long long ay = (localY[j] - oy) * sy;

            // 2) rotation selon l'angle
            long long rx = ax * cos - ay * sin;
            long long ry = ax * cos + ay * sin;

            // 3) translation dans le monde
            cornerX[j] = px + rx;
            cornerY[j] = py + ry;
        }

        // Affichage des 4 coins
        cout << name << " COINS";
        for (int j = 0; j < 4; ++j)
            cout << ' ' << cornerX[j] << ' ' << cornerY[j];
        cout << '\n';

        // Boîte englobante
        long long minX = cornerX[0];
        long long maxX = cornerX[0];
        long long minY = cornerY[0];
        long long maxY = cornerY[0];

        for (int j = 1; j < 4; ++j)
        {
            minX = min(minX, cornerX[j]);
            maxX = max(maxX, cornerX[j]);
            minY = min(minY, cornerY[j]);
            maxY = max(maxY, cornerY[j]);
        }

        cout << name << " BOITE " << minX << ' ' << minY << ' ' << maxX << ' ' << maxY << '\n';
    }

    cout << "REFUSES " << refusals << '\n';
    return 0;
}