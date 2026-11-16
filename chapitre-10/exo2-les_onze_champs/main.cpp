
#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;

    int restent = 0;
    int changes = 0;

    for (int i = 1; i <= N; i++) {
        int id;
        double x, y, echelle, rotation, opacite;
        int miroirX, miroirY;
        int largeur, hauteur;
        int selectionne;
        string chemin;
        long long octets;

        // Lecture des 13 valeurs
        cin >> id >> x >> y >> echelle >> rotation
            >> opacite >> miroirX >> miroirY
            >> largeur >> hauteur >> selectionne
            >> chemin >> octets;

        // Une image sans octets est ignorée
        if (octets == 0) {
            cout << "ITEM " << i << " SAUTE\n";
            continue;
        }

        // Nouvelle position de l'image sur le plateau
        restent++;

        cout << "ITEM " << i << " " << restent;

        int nbChanges = 0;

        // L'identifiant revient à 0
        if (id != 0) {
            cout << " id";
            nbChanges++;
        }

        // La sélection revient à 0
        if (selectionne == 1) {
            cout << " selected";
            nbChanges++;
        }

        // Le chemin revient vide
        if (chemin != "-") {
            cout << " sourcePath";
            nbChanges++;
        }

        // Aucun champ modifié
        if (nbChanges == 0) {
            cout << " AUCUN";
        }

        cout << "\n";

        changes += nbChanges;
    }

    cout << "RESTENT " << restent << "\n";
    cout << "CHANGES " << changes << "\n";

    return 0;
}
