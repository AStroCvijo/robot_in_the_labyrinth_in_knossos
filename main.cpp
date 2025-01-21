#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include "constants.h"
#include "GameIntro/GameIntro.h"
#include "Labyrinth/Labyrinth.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Provjera broja argumenata komandne linije
    if (argc != 4) {
        std::cout << "Pogresan broj argumenata! Ocekivana su 3 argumenta: rows, cols, numItems." << endl;
        return 1;
    }

    // Parsiranje argumenata komandne linije
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int numItems = atoi(argv[3]);

    // Provjera da li su dimenzije lavirinta ispravne
    if (rows <= 15 || cols <= 15 || numItems <= 3) {
        std::cout << "Dimenzije lavirinta moraju biti vece od 15x15, a broj predmeta veci od 3." << endl;
        return 1;
    }

    // Projera da li predmeti mogu da stanu u lavirint zadatih dimenzija
    if (numItems > (rows - 2) * (cols - 2) - (2 * (rows + cols))) {
        std::cout << "Odabrani broj predeta ne moze da stane u lavirint." << endl;
        return 1;
    }

    // Projera da li su dimenzije matrica prevelike
    if (rows > 100 || cols > 100) {
        std::cout << "Dimenzije matrice su prevelike." << endl;
        return 1;
    }

    // Pokretanje intro loop-a
    GameIntro intro(introText, helpText);
    intro.runIntro();

    // Generisanje lavirinta
    Labyrinth labyrinth(rows, cols, numItems);
    labyrinth.generateLabyrinth();

    // User interfejs petlja
    while (true) {
        // Provjera uslova za kraj
        if (labyrinth.endCondition()) {
            system("CLS");
            labyrinth.printLabyrinth();
            std::cout << "Pronasli ste izlaz iz lavirinta!!!\nHvala sto ste igrali!" << endl;

            // Cuvanje rezultata igre
            labyrinth.saveGameOutcome("Robot je pronasao izlaz!");

            labyrinth.~Labyrinth();
            return 0;
        }

        // Ispis lavirinta
        system("CLS");
        labyrinth.printLabyrinth();

        // Provjera da li je robot ziv
        if (labyrinth.isDead()) {
            std::cout << "\nMinotaur je unistio robota. Izgubili ste!\n";

            /// Cuvanje rezultata igre
            labyrinth.saveGameOutcome("Minotaur je unistio robota.");

            return 0;
        }

        std::cout << komande;

        // Unos komande koristeći getche()
        std::cout << "Unesite komandu: ";
        char command = _getche();

        switch (tolower(command)) {
        case 'w': // Kretanje na gore
            labyrinth.moveRobot(-1, 0);
            labyrinth.moveMinotaur();
            continue;

        case 'a': // Kretanje na lijevo
            labyrinth.moveRobot(0, -1);
            labyrinth.moveMinotaur();
            continue;

        case 's': // Kretanje na dole
            labyrinth.moveRobot(1, 0);
            labyrinth.moveMinotaur();
            continue;

        case 'd': // Kretanje na desno
            labyrinth.moveRobot(0, 1);
            labyrinth.moveMinotaur();
            continue;

        case 'q': // Izlaz
            std::cout << "\nIzlaz iz igre. Hvala sto ste igrali!" << endl;

            // Cuvanje rezultata igre
            labyrinth.saveGameOutcome("Igrac je napustio igru.");

            labyrinth.~Labyrinth();
            return 0;

        default:
            continue;
        }
    }
    return 0;
}
