#include "GameIntro.h"
#include <iostream>

using namespace std;

// Konstruktor
GameIntro::GameIntro(const string& introText, const string& helpText) {
    this->intro = introText;
    this->help = helpText;
}

// Metoda za ispis intro-a
void GameIntro::showIntro() const {
    system("CLS");
    cout << intro;
}

// Metoda za ispis uputstva
void GameIntro::showHelp() const {
    system("CLS");
    cout << help;
    char temp;
    cin >> temp;
}

// Glavna metoda za intro
void GameIntro::runIntro() {
    while (true) {
        showIntro();
        char command;
        cin >> command;

        if (tolower(command) == 'u') {
            showHelp();
        }
        else if (tolower(command) == 'p') {
            break;
        }
        else {
            continue;
        }
    }
}