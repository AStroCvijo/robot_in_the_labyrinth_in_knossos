#pragma once

class Minotaur {
private:
    int x;
    int y;
    bool alive;

public:
    // Konstruktor
    Minotaur();
    Minotaur(int startX, int startY);

    // Geteri
    int getX();
    int getY();
    bool isAlive();

    // Seteri
    void setX(int newX);
    void setY(int newY);
    void unAlive();
};
