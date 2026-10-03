#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // Optimisation des entrées/sorties pour éviter les retards d'exécution
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const double PI = 3.141592653589793;

    int N;
    if (!(cin >> N))
    {
        cout << "VISIBLES 0\nREFUSES 0\n";
        return 0;
    }

    long long count_visibles = 0;
    long long count_refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        long long r, n;
        if (!(cin >> r >> n))
            break;

        // Cas 1 : Moins de 3 segments -> REFUSE
        if (n < 3)
        {
            cout << r << ' ' << n << " REFUSE\n";
            ++count_refuses;
            continue;
        }

        // Calcul de l'écart en double précision
        double g = (double)r * (1.0 - cos(PI / (double)n));
        long long ecart = (long long)floor(g * 1000.0);

        // Cas 2 : Rayon nul (g == 0) -> JAMAIS
        if (g == 0.0)
        {
            cout << r << ' ' << n << ' ' << ecart << " JAMAIS\n";
            continue;
        }

        // Cas 3 : Calcul du zoom et du verdict
        long long zoom = (long long)ceil(100.0 / g);

        if (zoom <= 100)
        {
            cout << r << ' ' << n << ' ' << ecart << ' ' << zoom << " VISIBLE\n";
            ++count_visibles;
        }
        else
        {
            cout << r << ' ' << n << ' ' << ecart << ' ' << zoom << " INVISIBLE\n";
        }
    }

    // Sortie finale des compteurs
    cout << "VISIBLES " << count_visibles << '\n';
    cout << "REFUSES " << count_refuses << '\n';

    return 0;
}