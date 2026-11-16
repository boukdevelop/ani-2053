#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

// =====================================================
// STRUCTURES DES DONNEES
// =====================================================

struct Vue {
    double cx;
    double cy;
    double zoom;

    bool themeSombre;
    bool grilleAffichee;
};

struct Image {
    double x;
    double y;
    double echelle;
    double rotation;
    double opacite;

    int miroirX;
    int miroirY;

    uint32_t largeur;
    uint32_t hauteur;
    uint32_t taille;
};

struct Point {
    double x;
    double y;
};

struct Trait {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    double epaisseur;

    vector<Point> points;
};

// =====================================================
// LECTEUR BINAIRE
// ================================================

class LecteurBinaire {
private:
    const vector<uint8_t>& donnees;
    size_t position;

public:
    explicit LecteurBinaire(const vector<uint8_t>& octets)
        : donnees(octets), position(0) {
    }

    // Verifier le nombre d'octets disponibles
    bool disponible(size_t nombre) const {
        return position <= donnees.size()
            && nombre <= donnees.size() - position;
    }

    // Lire un octet non signe
    bool lireU8(uint8_t& valeur) {
        if (!disponible(1)) {
            return false;
        }

        valeur = donnees[position];
        position++;

        return true;
    }

    // Lire un entier non signe de 32 bits en little-endian
    bool lireU32(uint32_t& valeur) {
        if (!disponible(4)) {
            return false;
        }

        valeur =
            static_cast<uint32_t>(donnees[position])
            | (static_cast<uint32_t>(donnees[position + 1]) << 8)
            | (static_cast<uint32_t>(donnees[position + 2]) << 16)
            | (static_cast<uint32_t>(donnees[position + 3]) << 24);

        position += 4;

        return true;
    }

    // Lire un flottant IEEE 754 de 32 bits
    bool lireF32(double& valeur) {
        uint32_t bits;

        if (!lireU32(bits)) {
            return false;
        }

        float resultat;

        static_assert(sizeof(float) == sizeof(uint32_t),
                      "Un float doit occuper 4 octets.");

        std::memcpy(&resultat, &bits, sizeof(float));

        valeur = static_cast<double>(resultat);

        return true;
    }

    // Ignorer un nombre d'octets
    bool ignorer(size_t nombre) {
        if (!disponible(nombre)) {
            return false;
        }

        position += nombre;

        return true;
    }
};

// =============================================
// DECODEUR DU FORMAT NKRF
// ===========================================

class Decodeur {
private:
    LecteurBinaire& lecteur;

public:
    Vue vue;
    vector<Image> images;
    vector<Trait> traits;

    explicit Decodeur(LecteurBinaire& source)
        : lecteur(source) {
    }

    // Lire et verifier la signature NKRF
    bool verifierSignature() {
        const uint8_t signature[4] = {
            0x4E, 0x4B, 0x52, 0x46
        };

        for (int i = 0; i < 4; i++) {
            uint8_t octet;

            if (!lecteur.lireU8(octet)) {
                return false;
            }

            if (octet != signature[i]) {
                return false;
            }
        }

        return true;
    }

    // Lire la version
    bool lireVersion(uint32_t& version) {
        return lecteur.lireU32(version);
    }

    // Lire les informations de la vue
    bool lireVue() {
        uint8_t theme;
        uint8_t grille;
        uint8_t remplissage1;
        uint8_t remplissage2;

        if (!lecteur.lireF32(vue.cx)
            || !lecteur.lireF32(vue.cy)
            || !lecteur.lireF32(vue.zoom)
            || !lecteur.lireU8(theme)
            || !lecteur.lireU8(grille)
            || !lecteur.lireU8(remplissage1)
            || !lecteur.lireU8(remplissage2)) {

            return false;
        }

        vue.themeSombre = (theme != 0);
        vue.grilleAffichee = (grille == 0);

        return true;
    }

    // Lire toutes les images
    bool lireImages() {
        uint32_t nombreImages;

        if (!lecteur.lireU32(nombreImages)) {
            return false;
        }

        for (uint32_t i = 0; i < nombreImages; i++) {
            Image image{};

            uint8_t mx;
            uint8_t my;
            uint8_t remplissage1;
            uint8_t remplissage2;

            if (!lecteur.lireF32(image.x)
                || !lecteur.lireF32(image.y)
                || !lecteur.lireF32(image.echelle)
                || !lecteur.lireF32(image.rotation)
                || !lecteur.lireF32(image.opacite)
                || !lecteur.lireU8(mx)
                || !lecteur.lireU8(my)
                || !lecteur.lireU8(remplissage1)
                || !lecteur.lireU8(remplissage2)
                || !lecteur.lireU32(image.largeur)
                || !lecteur.lireU32(image.hauteur)
                || !lecteur.lireU32(image.taille)) {

                return false;
            }

            image.miroirX = (mx != 0) ? 1 : 0;
            image.miroirY = (my != 0) ? 1 : 0;

            // Ignorer les octets source de l'image
            if (!lecteur.ignorer(image.taille)) {
                return false;
            }

            images.push_back(image);
        }

        return true;
    }

    // Lire tous les traits
    bool lireTraits() {
        uint32_t nombreTraits;

        if (!lecteur.lireU32(nombreTraits)) {
            return false;
        }

        for (uint32_t i = 0; i < nombreTraits; i++) {
            Trait trait{};

            uint32_t nombrePoints;

            if (!lecteur.lireU8(trait.r)
                || !lecteur.lireU8(trait.g)
                || !lecteur.lireU8(trait.b)
                || !lecteur.lireU8(trait.a)
                || !lecteur.lireF32(trait.epaisseur)
                || !lecteur.lireU32(nombrePoints)) {

                return false;
            }

            for (uint32_t j = 0; j < nombrePoints; j++) {
                Point point{};

                if (!lecteur.lireF32(point.x)
                    || !lecteur.lireF32(point.y)) {

                    return false;
                }

                trait.points.push_back(point);
            }

            traits.push_back(trait);
        }

        return true;
    }

    // Decoder le fichier complet
    bool decoder() {
        return lireVue()
            && lireImages()
            && lireTraits();
    }
};

// ==================================================
// FONCTIONS D'AFFICHAGE
// =================================================

// Afficher un flottant avec deux decimales
void afficherFloat(double valeur) {
    if (isfinite(valeur) && abs(valeur) < 0.005) {
        valeur = 0.0;
    }

    cout << fixed << setprecision(2) << valeur;
}

// Afficher toutes les donnees decodees
void afficherResultat(const Decodeur& decodeur) {

    // Vue
    cout << "VUE ";

    afficherFloat(decodeur.vue.cx);
    cout << " ";

    afficherFloat(decodeur.vue.cy);
    cout << " ";

    afficherFloat(decodeur.vue.zoom);
    cout << "\n";

    // Theme
    cout << "THEME "
         << (decodeur.vue.themeSombre ? "SOMBRE" : "CLAIR")
         << "\n";

    // Grille
    cout << "GRILLE "
         << (decodeur.vue.grilleAffichee ? "AFFICHEE" : "CACHEE")
         << "\n";

    // Images
    cout << "IMAGES " << decodeur.images.size() << "\n";

    for (size_t i = 0; i < decodeur.images.size(); i++) {
        const Image& image = decodeur.images[i];

        cout << "IMAGE " << i + 1 << " ";

        afficherFloat(image.x);
        cout << " ";

        afficherFloat(image.y);
        cout << " ";

        afficherFloat(image.echelle);
        cout << " ";

        afficherFloat(image.rotation);
        cout << " ";

        afficherFloat(image.opacite);

        cout << " "
             << image.miroirX << " "
             << image.miroirY << " "
             << image.largeur << " "
             << image.hauteur << " "
             << image.taille << "\n";
    }

    // Traits
    cout << "TRAITS " << decodeur.traits.size() << "\n";

    for (size_t i = 0; i < decodeur.traits.size(); i++) {
        const Trait& trait = decodeur.traits[i];

        cout << "TRAIT " << i + 1 << " "
             << static_cast<int>(trait.r) << " "
             << static_cast<int>(trait.g) << " "
             << static_cast<int>(trait.b) << " "
             << static_cast<int>(trait.a) << " ";

        afficherFloat(trait.epaisseur);

        cout << " " << trait.points.size() << "\n";

        for (const Point& point : trait.points) {
            cout << "POINT ";

            afficherFloat(point.x);
            cout << " ";

            afficherFloat(point.y);
            cout << "\n";
        }
    }
}

// ==============================================
// PROGRAMME PRINCIPAL
// ==============================================

int main() {

    long long T;
    cin >> T;

    if (!cin || T < 0) {
        cout << "TRONQUE\n";
        return 0;
    }

    vector<uint8_t> donnees;
    donnees.reserve(static_cast<size_t>(T));

    // Lecture des octets en hexadecimal
    for (long long i = 0; i < T; i++) {
        string hexadecimal;

        if (!(cin >> hexadecimal)) {
            break;
        }

        try {
            unsigned long valeur = stoul(hexadecimal, nullptr, 16);

            if (valeur > 255) {
                cout << "TRONQUE\n";
                return 0;
            }

            donnees.push_back(static_cast<uint8_t>(valeur));
        }
        catch (...) {
            cout << "TRONQUE\n";
            return 0;
        }
    }

    // Creation du lecteur binaire
    LecteurBinaire lecteur(donnees);

    // Verification de la signature
    Decodeur decodeur(lecteur);

    if (!decodeur.verifierSignature()) {

        if (donnees.size() < 4) {
            cout << "TRONQUE\n";
        }
        else {
            cout << "PAS_UNE_PLANCHE\n";
        }

        return 0;
    }

    // Verification de la version
    uint32_t version;

    if (!decodeur.lireVersion(version)) {
        cout << "TRONQUE\n";
        return 0;
    }

    if (version != 1) {
        cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    // Decodage du contenu
    if (!decodeur.decoder()) {
        cout << "TRONQUE\n";
        return 0;
    }

    // Affichage uniquement si le fichier est valide
    afficherResultat(decodeur);

    return 0;
}
