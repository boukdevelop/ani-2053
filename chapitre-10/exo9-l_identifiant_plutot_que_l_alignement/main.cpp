#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class Planche {
private:
    vector<uint64_t> ordre;
    uint64_t prochainIdentifiant = 1;

    uint64_t occasions = 0;
    uint64_t repercutes = 0;
    uint64_t recherches = 0;

public:
    // Ajouter une image à la fin
    void ajouter() {
        ordre.push_back(prochainIdentifiant);
        prochainIdentifiant++;
    }

    // Supprimer plusieurs images
    void supprimer(const vector<size_t>& indices) {
        occasions++;
        repercutes += 2 * indices.size();

        // Suppression de droite à gauche
        for (size_t i = indices.size(); i > 0; i--) {
            ordre.erase(ordre.begin() + indices[i - 1]);
        }
    }

    // Faire monter une image d'un cran
    void monter(size_t index) {
        if (index + 1 >= ordre.size()) {
            return;
        }

        swap(ordre[index], ordre[index + 1]);

        occasions++;
        repercutes += 2;
    }

    // Faire descendre une image d'un cran
    void descendre(size_t index) {
        if (index == 0 || index >= ordre.size()) {
            return;
        }

        swap(ordre[index], ordre[index - 1]);

        occasions++;
        repercutes += 2;
    }

    // Dessiner toutes les images
    void dessiner() {
        recherches += ordre.size();
    }

    // Afficher le résultat final
    void afficher() const {
        cout << "ORDRE";

        if (ordre.empty()) {
            cout << " AUCUN";
        } else {
            for (uint64_t identifiant : ordre) {
                cout << " " << identifiant;
            }
        }

        cout << "\n";
        cout << "OCCASIONS " << occasions << "\n";
        cout << "REPERCUTES " << repercutes << "\n";
        cout << "RECHERCHES " << recherches << "\n";
    }
};

int main() {
    size_t N;
    cin >> N;

    Planche planche;

    for (size_t operation = 0; operation < N; operation++) {
        string commande;
        cin >> commande;

        if (commande == "AJOUTE") {
            planche.ajouter();
        }

        else if (commande == "SUPPRIME") {
            size_t c;
            cin >> c;

            vector<size_t> indices(c);

            for (size_t i = 0; i < c; i++) {
                cin >> indices[i];
            }

            planche.supprimer(indices);
        }

        else if (commande == "MONTE") {
            size_t index;
            cin >> index;

            planche.monter(index);
        }

        else if (commande == "DESCEND") {
            size_t index;
            cin >> index;

            planche.descendre(index);
        }

        else if (commande == "DESSINE") {
            planche.dessiner();
        }
    }

    planche.afficher();

    return 0;
}
