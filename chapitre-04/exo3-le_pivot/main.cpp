#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool IsValidAngle(long long angle, int &cos, int &sin)
{
    angle = (angle % 360 + 360) % 360;

    if (angle % 90 != 0)
        return false;

    switch (angle / 90)
    {
    case 0:    // 0°
        cos = 1;
        sin = 0;
        break;
    case 1:    // 90°
        cos = 0;
        sin = 1;
        break;
    case 2:    // 180°
        cos = -1;
        sin = 0;
        break;
    case 3:    // 270°
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

    if (!(cin >> n))
        return 0;

    long long refusals = 0;

    for (int i = 0; i < n; ++i)
    {
        string name;
        long long w, h, px, py, ox, oy, sx, sy, angle;

        if (!(cin >> name >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle))
            return 0;

        int cos, sin;

        if (!IsValidAngle(angle, cos, sin))
        {
            cout << name << " ANGLE REFUSE\n";
            ++refusals;
            continue;
        }

        long long localX[4] = {0, w, w, 0};
        long long localY[4] = {0, 0, h, h};

        long long cornerX[4];
        long long cornerY[4];

        for (int j = 0; j < 4; ++j)
        {
            long long ax = (localX[j] - ox) * sx;
            long long ay = (localY[j] - oy) * sy;

            long long rx = ax * cos - ay * sin;
            long long ry = ax * cos + ay * sin;

            cornerX[j] = px + rx;
            cornerY[j] = py + ry;
        }

        cout << name << " COINS";
        for (int j = 0; j < 4; ++j)
            cout << ' ' << cornerX[j] << ' ' << cornerY[j];
        cout << '\n';

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
