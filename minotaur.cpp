#include "minotaur.h"
#include "constants.h"

// Konstruktor
Minotaur::Minotaur() {
    this->x = 0;
    this->y = 0;
    this->alive = true;
}

Minotaur::Minotaur(int startX, int startY) {
    this->x = startX;
    this->y = startY;
    this->alive = true;
}

// Geteri za X minotaura
int Minotaur::getX() {
    return this->x;
}

// Geteri za Y minotaura
int Minotaur::getY() {
    return this->y;
}

// Provjera da li je minotaur ziv
bool Minotaur::isAlive() {
    if (alive == true) {
        return true;
    }
    return false;
}

// Seteri za X minotaura
void Minotaur::setX(int newX) {
    this->x = newX;
}

// Seteri za Y minotaura
void Minotaur::setY(int newY) {
    this->y = newY;
}

// Metoda za ubijanje minotaura
void Minotaur::unAlive() {
    this->alive = false;
}