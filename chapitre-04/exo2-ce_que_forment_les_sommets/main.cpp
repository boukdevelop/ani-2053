#include <iostream>
#include <string>

int main() {
	int entries;

	std::cerr << "Veuillez entrer le nombre d'entrees : ";
	if (!(std::cin >> entries)) {
		return 0;
	}

	long long points = 0;
	long long segments = 0;
	long long triangles = 0;
	long long refusals = 0;

	for (int i = 0; i < entries; ++i) {
		std::string type;
		long long vertices;
		std::cerr << "Entrez le type et le nombre de sommets : ";
		if (!(std::cin >> type >> vertices)) {
			return 0;
		}

		if (type == "POINTS") {
			points += vertices;
			std::cout << type << ' ' << vertices << ' ' << vertices << " POINTS 0\n";
		} else if (type == "LINES") {
			const long long formed = vertices / 2;
			const long long remaining = vertices % 2;
			segments += formed;
			std::cout << type << ' ' << vertices << ' ' << formed << " SEGMENTS " << remaining << '\n';
		} else if (type == "LINE_STRIP") {
			const long long formed = vertices >= 2 ? vertices - 1 : 0;
			const long long remaining = vertices >= 2 ? 0 : vertices;
			segments += formed;
			std::cout << type << ' ' << vertices << ' ' << formed << " SEGMENTS " << remaining << '\n';
		} else if (type == "TRIANGLES") {
			const long long formed = vertices / 3;
			const long long remaining = vertices % 3;
			triangles += formed;
			std::cout << type << ' ' << vertices << ' ' << formed << " TRIANGLES " << remaining << '\n';
		} else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN") {
			const long long formed = vertices >= 3 ? vertices - 2 : 0;
			const long long remaining = vertices >= 3 ? 0 : vertices;
			triangles += formed;
			std::cout << type << ' ' << vertices << ' ' << formed << " TRIANGLES " << remaining << '\n';
		} else {
			++refusals;
			std::cout << type << ' ' << vertices << " REFUSE\n";
		}
	}

	std::cout << "POINTS " << points << '\n';
	std::cout << "SEGMENTS " << segments << '\n';
	std::cout << "TRIANGLES " << triangles << '\n';
	std::cout << "REFUSES " << refusals << '\n';
}