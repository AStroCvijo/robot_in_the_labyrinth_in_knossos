#include "Robot.h"
#include "Labyrinth.h"
#include "constants.h"

// Konstuktor
Robot::Robot() {
    this->x = 0;
    this->y = 0;
    this->effect = 0;
    this->effectTimer = 0;
}

Robot::Robot(int startX, int startY) {
    this->x = startX;
    this->y = startY;
    this->effect = 0;
    this->effectTimer = 0;
}

// Geter za X robota
int Robot::getX() {
    return this->x;
}

// Geter za Y robota
int Robot::getY() {
    return this->y;
}

// Geter za efekat
int Robot::getEffect() {
    return this->effect;
}

// Geter za tajmer efekta
int Robot::getEffectTimer() {
    return this->effectTimer;
}

// Seter za X robota
void Robot::setX(int newX) {
    this->x = newX;
}

// Seter za Y robota
void Robot::setY(int newY) {
    this->y = newY;
}

// Seter za efekat
void Robot::setEffect(int newEffect) {
    this->effect = newEffect;
}

// Seter za tajmer efekta
void Robot::setEffectTimer() {
    this->effectTimer = 4;
}

// Metoda za resetovanje tajmera efekta
void Robot::resetEffectTimer() {
    this->effectTimer = 0;
}

// Tick za tajmer efekta
void Robot::tick() {
    if (effectTimer != 0) {
        --effectTimer;
        return;
    }
    effect = 0;
}