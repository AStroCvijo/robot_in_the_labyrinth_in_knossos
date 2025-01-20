#include "Labyrinth.h"
#include "../constants.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../Robot/robot.h"
#include "../Minotaur/minotaur.h"

using namespace std;

// Konstruktor
Labyrinth::Labyrinth(int rows, int cols, int numItems){
    this->rows = rows;
    this->cols = cols;
    this->numItems = numItems;
    this->labyrinth = nullptr;
    this->robot = Robot(0, 0);
    this->minotaur = Minotaur(0, 0);
    srand(time(0));
}

// Destruktor
Labyrinth::~Labyrinth() {
    if (labyrinth) {
        for (int i = 0; i < rows; i++) {
            delete[] labyrinth[i];
        }
        delete[] labyrinth;
        labyrinth = nullptr;
    }
}

//  Metoda za alociranje memorije za lavirint
void Labyrinth::allocateLabyrinth() {
    labyrinth = new char* [rows];
    for (int i = 0; i < rows; i++) {
        labyrinth[i] = new char[cols];
    }
}

// Metoda za inicijalizaciju lavirinta na prolaz (.)
void Labyrinth::initializeLabyrinth() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            labyrinth[i][j] = PASSAGE;
        }
    }
}

// Metoda za postavljanje vanjskih zidova (#)
void Labyrinth::setOuterWalls() {
    for (int i = 0; i < rows; i++) {
        labyrinth[i][0] = WALL;
        labyrinth[i][cols - 1] = WALL;
    }
    for (int j = 0; j < cols; j++) {
        labyrinth[0][j] = WALL;
        labyrinth[rows - 1][j] = WALL;
    }
}

// Metoda za postavljanje ulaza (U) i izlaza (I)
void Labyrinth::placeEntryExit() {
    int entryLocation = randInRange(1, cols - 2);
    labyrinth[0][entryLocation] = ENTRY;
    labyrinth[rows - 1][randInRange(1, cols - 2)] = EXIT;
    placeRobot(entryLocation);
}

// Metoda za postavljanje robota (R)
void Labyrinth::placeRobot(int entryLocation) {
    robot = Robot(1, entryLocation);
    labyrinth[1][entryLocation] = ROBOT;
}

// Metoda za postavljanje minotaura (M)
void Labyrinth::placeMinotaur() {
    int tempX = randInRange(1, rows - 2);
    int tempY = randInRange(1, cols - 2);
    minotaur = Minotaur(tempX, tempY);
    labyrinth[tempX][tempY] = MINOTAUR;
}

// Metoda za postavljanje predmeta (P)
void Labyrinth::placeItems() {
    for (int i = 0; i < numItems; i++) {
        int r, c;
        do {
            r = randInRange(1, rows - 2);
            c = randInRange(1, cols - 2);
        } while (labyrinth[r][c] != PASSAGE);
        labyrinth[r][c] = ITEM;
    }
}


// Metoda za postavljanje unutrasnjih zidova (#)
void Labyrinth::placeInnerWalls() {
    int minWalls = 2 * (rows + cols);  // Minimalni broj zidova
    int maxWalls = rows * cols / 2;    // Maksimalni broj zidova
    int wallCount = 0;

    // Nasumicno odredi broj zidova
    int requiredWalls = randInRange(minWalls, maxWalls);

    // Dodajemo zidove dok broj zidova ne dostigne requiredWalls
    while (wallCount < requiredWalls) {
        int r = randInRange(1, rows - 2);
        int c = randInRange(1, cols - 2);

        // Proveravamo da li je prostor prazan za zid
        if (labyrinth[r][c] == PASSAGE) {
            labyrinth[r][c] = WALL;
            wallCount++;
        }
    }
}


// Metoda za nasumicnu vrijednost u [min - max] rasponu
int Labyrinth::randInRange(int min, int max) const {
    return min + rand() % (max - min + 1);
}

// Pomocna metoda za isPathPossible
bool Labyrinth::isValid(int x, int y, std::vector<std::vector<bool>>& visited) const {
    return x >= 0 && x < rows && y >= 0 && y < cols &&
        labyrinth[x][y] != WALL && !visited[x][y];
}

// BFS algoritam za provjeru postojanja puta od ulaza do izlaza
bool Labyrinth::isPathPossible() const {
    int startX = -1, startY = -1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (labyrinth[i][j] == ENTRY) {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) break;
    }

    if (startX == -1 || startY == -1) return false;

    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    q.push({ startX, startY });
    visited[startX][startY] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (labyrinth[x][y] == EXIT) return true;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny, visited)) {
                visited[nx][ny] = true;
                q.push({ nx, ny });
            }
        }
    }

    return false;
}

// Glavna metoda za generisanje lavirinta
void Labyrinth::generateLabyrinth() {
    do {
        // Dealokacija prethodne memorije
        if (labyrinth) {
            for (int i = 0; i < rows; i++) {
                delete[] labyrinth[i];
            }
            delete[] labyrinth;
            labyrinth = nullptr;
        }

        // Alociranje i inicijalizacija novog lavirinta
        allocateLabyrinth();
        initializeLabyrinth();
        setOuterWalls();
        placeEntryExit();
        placeMinotaur();
        placeItems();
        placeInnerWalls();
    } while (!isPathPossible());
}

// Metoda za ispis lavirinta
void Labyrinth::printLabyrinth() {
    if (robot.getEffect() == 1 && robot.getEffectTimer() != 0) {
        int robotX = robot.getX();
        int robotY = robot.getY();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (abs(i - robotX) <= 1 && abs(j - robotY) <= 1) {
                    cout << labyrinth[i][j] << " ";
                }
                else {
                    cout << "? ";
                }
            }
            cout << endl;
        }
    }
    else {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << labyrinth[i][j] << " ";
            }
            cout << endl;
        }
    }
    if (robot.getEffectTimer() != 0) {
        cout << "\nTrenutni efekat: " << efekti[robot.getEffect()-1];
        cout << "\nEfekat istice za " << robot.getEffectTimer() <<" potez\n";
    }
}

// Funkcija za ispis konacnog stanja lavirinta
void Labyrinth::saveGameOutcome(string outcome) {
    ofstream resultFile("game_result.txt");

    if (resultFile.is_open()) {
        // Ispisi rezultat
        resultFile << outcome << endl;

        // Ispisi konacno stanje lavirinta
        resultFile << "Konacno stanje Lavirinta: " << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                resultFile << getLabyrinthField(i, j) << " ";
            }
            resultFile << endl;
        }

        resultFile.close();
        cout << "Rezultat igre je sacuvan u game_result.txt." << endl;
    }
    else {
        cout << "Greska prilikom otvaranja fajla za ispis konacnog rezultata igre!" << endl;
    }
}

// Metoda za pomjeranje robota
void Labyrinth::moveRobot(int dx, int dy) {
    // Trenutna lokacija robota
    int x = robot.getX();
    int y = robot.getY();

    // Provjera da li je kretanje van granica lavirinta
    if ((x + dx < 1 || x + dx >= rows - 1 || y + dy < 1 || y + dy >= cols - 1) && getLabyrinthField(x + dx, y + dy) != 'I') {
        // tick za robota
        robot.tick();
        return;
    }

    // Provjera da li robot moze da stane na izabrano polje
    if (getLabyrinthField(x + dx, y + dy) == '#' && !(robot.getEffect() == 4 && robot.getEffectTimer() != 0)) {
        return;
    }

    if (getLabyrinthField(x + dx, y + dy) == '#' && robot.getEffect() == 4 && robot.getEffectTimer() != 0) {
        robot.setEffect(0);
        robot.resetEffectTimer();
    }

    if (getLabyrinthField(x + dx, y + dy) == 'U') {
        return;
    }

    // Provjera da li robot staje na neki predmet
    if (getLabyrinthField(x + dx, y + dy) == 'P') {
        int effect = randInRange(1, 4);
        robot.setEffect(effect);
        robot.setEffectTimer();
    }

    // tick za robota
    robot.tick();

    // Izmjene lavirinta
    setLabyrinthField(PASSAGE, x, y);
    setLabyrinthField(ROBOT, x + dx, y + dy);
    robot.setX(x + dx);
    robot.setY(y + dy);
}

// Metoda za pomjeranje robota
void Labyrinth::moveMinotaur() {
    // Provjera da li je minotaur ziv
    if (minotaur.isAlive() == false) {
        return;
    }

    // Trenutna lokacija minotaura
    int x = minotaur.getX();
    int y = minotaur.getY();

    // Generisinje nasumicnog smjera kretanja
    int direction = randInRange(0, 3);
    int dx = moves[direction][0];
    int dy = moves[direction][1];

    // Provjera da li minotaur moze da stane na izabrano polje
    if (getLabyrinthField(x + dx, y + dy) == '#' || getLabyrinthField(x + dx, y + dy) == 'U' || getLabyrinthField(x + dx, y + dy) == 'I' || getLabyrinthField(x + dx, y + dy) == 'R') {
        return;
    }

    // Izmjene lavirinta
    setLabyrinthField(PASSAGE, x, y);
    setLabyrinthField(MINOTAUR, x + dx, y + dy);
    minotaur.setX(x + dx);
    minotaur.setY(y + dy);
}

// Metoda za provjeru uslova za kraj
bool Labyrinth::endCondition() {
    if (robot.getX() == rows - 1) {
        return true;
    }
    return false;
}

// Metod za provjeru smrti
bool Labyrinth::isDead() {
    int robotX = robot.getX();
    int robotY = robot.getY();
    int minotaurX = minotaur.getX();
    int minotaurY = minotaur.getY();

    // Provjera da li je robot unisten
    if (((abs(robotX - minotaurX) == 1 && robotY == minotaurY) ||
        (abs(robotY - minotaurY) == 1 && robotX == minotaurX)) && minotaur.isAlive()) {

        // Provjera da li je minotaur unisten
        if (robot.getEffect() == 2 && robot.getEffectTimer() != 0) {
            setLabyrinthField(PASSAGE, minotaurX, minotaurY);
            minotaur.unAlive();
            return false;
        }

        if (robot.getEffect() == 3 && robot.getEffectTimer() != 0) {
            robot.setEffect(0);
            robot.resetEffectTimer();
            return false;
        }
        return true;
    }

    return false;
}

// Geter za polja lavirinta
char Labyrinth::getLabyrinthField(int x, int y) {
    return labyrinth[x][y];
}

// Seter za polja lavirinta
void Labyrinth::setLabyrinthField(char newChar, int x, int y) {
    labyrinth[x][y] = newChar;
}