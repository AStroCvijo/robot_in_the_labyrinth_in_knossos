#pragma once

#include <vector>
#include <queue>
#include <string>
#include "constants.h"
#include "robot.h"
#include "minotaur.h"

class Labyrinth {
private:
    int rows;
    int cols;
    int numItems;
    Robot robot;
    Minotaur minotaur;
    char** labyrinth;

    // Pomocne strukture za kretanje
    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    // Helper funkcije
    bool isValid(int x, int y, std::vector<std::vector<bool>>& visited) const;
    int randInRange(int min, int max) const;
    void allocateLabyrinth();
    void initializeLabyrinth();
    void setOuterWalls();
    void placeEntryExit();
    void placeRobot(int entryLocation);
    void placeMinotaur();
    void placeItems();
    void placeInnerWalls();

public:
    // Konstruktor i destruktor
    Labyrinth(int rows, int cols, int numItems);
    ~Labyrinth();

    // Glavne metode
    void generateLabyrinth();
    bool isPathPossible() const;
    void printLabyrinth();
    void saveGameOutcome(string outcome);

    // Metode za manipulaciju lavirintom
    char getLabyrinthField(int x, int y);
    void setLabyrinthField(char newChar, int x, int y);

    // Metoda za pomjeranje robota
    void moveRobot(int dx, int dy);

    // Metoda za nasumicno pomjeranje minotaura
    void moveMinotaur();

    // Uslovi za kraj
    bool endCondition();
    bool isDead();
};
