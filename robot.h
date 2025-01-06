#pragma once

class Robot {
private:
    int x;
    int y;
    int effect;
    int effectTimer;

public:
    // Konstruktor
    Robot();
    Robot(int startX, int startY);

    // Geteri
    int getX();
    int getY();
    int getEffect();
    int getEffectTimer();

    // Seteri
    void setX(int newX);
    void setY(int newY);
    void setEffect(int newEffect);
    void setEffectTimer();
    void resetEffectTimer();

    // Tick
    void tick();
};
