#pragma once

#include <string>

using namespace std;

class GameIntro {
private:
    string intro;
    string help;

public:
    // Konstruktor
    GameIntro(const string& introText, const string& helpText);

    // Metoda za ispis nitro-a
    void showIntro() const;

    // Metoda za ispis uputstva
    void showHelp() const;

    // Glavna metoda za intro
    void runIntro();
};