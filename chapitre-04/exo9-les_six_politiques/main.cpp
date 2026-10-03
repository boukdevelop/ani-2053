#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Formule d'arrondi specifiee : round(a / b) = (2 * a + b) / (2 * b)
long long round_div(long long a, long long b) {
    return (2 * a + b) / (2 * b);
}

struct PolicyResult {
    string name;
    long long vx, vy, vw, vh;
    long long mw, mh;
};

int main() {
    // Optimisation des I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long RW, RH, AW, AH, W, H;
    if (!(cin >> RW >> RH >> AW >> AH >> W >> H)) {
        return 0;
    }

    bool has_ref = (RW > 0 && RH > 0);
    PolicyResult results[6];

    // FOLLOW_WINDOW
    results[0] = {"FOLLOW_WINDOW", 0, 0, W, H, W, H};

    // STRETCH
    if (!has_ref) {
        results[1] = {"STRETCH", 0, 0, W, H, W, H};
    } else {
        results[1] = {"STRETCH", 0, 0, W, H, RW, RH};
    }

    // FIT_LETTERBOX
    if (!has_ref) {
        results[2] = {"FIT_LETTERBOX", 0, 0, W, H, W, H};
    } else {
        long long vw, vh;
        if (W * RH <= H * RW) {
            vw = W;
            vh = round_div(RH * W, RW);
        } else {
            vh = H;
            vw = round_div(RW * H, RH);
        }
        long long vx = (W - vw) / 2;
        long long vy = (H - vh) / 2;
        results[2] = {"FIT_LETTERBOX", vx, vy, vw, vh, RW, RH};
    }

    // INTEGER_SCALE
    if (!has_ref) {
        results[3] = {"INTEGER_SCALE", 0, 0, W, H, W, H};
    } else {
        if (W >= RW && H >= RH) {
            long long k = min(W / RW, H / RH);
            long long vw = RW * k;
            long long vh = RH * k;
            long long vx = (W - vw) / 2;
            long long vy = (H - vh) / 2;
            results[3] = {"INTEGER_SCALE", vx, vy, vw, vh, RW, RH};
        } else {
            // Retombe exactement sur FIT_LETTERBOX
            results[3] = results[2];
            results[3].name = "INTEGER_SCALE";
        }
    }

    // FIT_CROP
    if (!has_ref) {
        results[4] = {"FIT_CROP", 0, 0, W, H, W, H};
    } else {
        long long mw, mh;
        if (W * RH > H * RW) {
            mw = RW;
            mh = round_div(RW * H, W);
        } else {
            mw = round_div(RH * W, H);
            mh = RH;
        }
        results[4] = {"FIT_CROP", 0, 0, W, H, mw, mh};
    }

    // MANUAL
    results[5] = {"MANUAL", 0, 0, AW, AH, AW, AH};

    // Décompte des bandes
    int bandes = 0;
    for (int i = 0; i < 6; ++i) {
        if (results[i].vw < W || results[i].vh < H) {
            bandes++;
        }
    }

    // Teste de la deformation
    bool deformation = false;
    if (has_ref && (W * RH != H * RW)) {
        deformation = true;
    }

    // Affichage des resultats
    for (int i = 0; i < 6; ++i) {
        cout << results[i].name << " "
             << results[i].vx << " "
             << results[i].vy << " "
             << results[i].vw << " "
             << results[i].vh << " "
             << results[i].mw << " "
             << results[i].mh << "\n";
    }

    cout << "BANDES " << bandes << "\n";
    cout << "DEFORMATION " << (deformation ? "OUI" : "NON") << "\n";

    return 0;
}
