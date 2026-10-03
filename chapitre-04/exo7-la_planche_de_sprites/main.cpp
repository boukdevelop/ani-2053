#include <iostream>

using namespace std;

int main()
{
    // Acceleration des entrees/sorties C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long C, R, W, H, F, D, P;
    if (!(cin >> C >> R >> W >> H >> F >> D >> P))
    {
        cout << "AVANCES 0\n";
        cout << "PLAFONNES 0\n";
        return 0;
    }

    int N;
    if (!(cin >> N))
    {
        cout << "AVANCES 0\n";
        cout << "PLAFONNES 0\n";
        return 0;
    }

    long long current_frame = 0;
    long long accumulated_time = 0;
    long long avances = 0;
    long long plafonnes = 0;

    for (int i = 0; i < N; ++i)
    {
        long long dt;
        if (!(cin >> dt))
            break;

        // Plafonnement du dt si strictement superieur a P
        if (dt > P)
        {
            dt = P;
            ++plafonnes;
        }

        // Accumulation du temps
        accumulated_time += dt;

        // Traitement des passages de case
        while (accumulated_time >= D)
        {
            accumulated_time -= D;
            current_frame = (current_frame + 1) % F;
            ++avances;
        }

        // Calcul de la position dans la planche de sprites
        long long col = current_frame % C;
        long long row = current_frame / C;

        long long x = col * W;
        long long y = row * H;

        // Affichage du rectangle
        cout << current_frame << ' ' << x << ' ' << y << ' ' << W << ' ' << H << '\n';
    }

    // Bilan final
    cout << "AVANCES " << avances << '\n';
    cout << "PLAFONNES " << plafonnes << '\n';

    return 0;
}
