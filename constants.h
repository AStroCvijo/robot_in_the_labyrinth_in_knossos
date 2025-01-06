#pragma once

#include <string>

using namespace std;

// Game Intro
const string introText = "Dobrodosli u igru 'Robot u lavirintu u Knososu'"
"\n"
"\n"
"Komande: P(pocetak igre), U(uputstva)"
"\n"
"\n"
"Unesite komandu: ";

// Uputstva
const string helpText = "Uputstvo:"
"\n"
"Vi ste robot (R), ganja vas minotaur (M)"
"\n"
"Vas cilj je da zivi izadjete iz lavirinta tako sto pronadjete put do izlaza (I)"
"\n"
"\n"
"Predmeti:"
"\n"
"Efekat svakog predmeta traje 3 poteza"
"\n"
"Kada robot stane na predmet (P), nasumicno se bira efekat koji predmet donosi"
"\n"
"\n"
"Magla rata - smanjuje vidjlivost robota na matricu dimenzija 3x3"
"\n"
"Mac - ovim predmetom moguce je ubiti minotaura"
"\n"
"Stit - ovim predmetom moguce je odbraniti se od minotaura"
"\n"
"Cekic - omogucava prolaz kroz zid"
"\n"
"\n"
"Komande:"
"\n"
"W(gore), A(levo), S(dole), D(desno), Q(izlaz)"
"\n"
"\n"
"Unesite bilo koju komandu da se vratite: ";

// Komande
const string komande = "\nKomande: W(gore), A(levo), S(dole), D(desno), Q(izlaz)\n\n";

// Konstante za lavirint
const char WALL = '#';
const char ENTRY = 'U';
const char ROBOT = 'R';
const char EXIT = 'I';
const char PASSAGE = '.';
const char MINOTAUR = 'M';
const char ITEM = 'P';

// Konstante za kretanje
const int moves[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}
};

// Konstante za efekte
const string efekti[4] = {"Magla rata", "Mac", "Stit", "Cekic"};