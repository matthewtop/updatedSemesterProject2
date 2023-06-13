#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "classes.h"

using namespace std;
extern int global;

int main() {

    int x;
    int index;
    bool dzialanie = true;
    string kontynuacja, s;
    SystemPolicji system = SystemPolicji();
    Wczytaj("dane.txt", system);

    cout << "--------------------------------------------------------------------" << endl;
    cout << "       Witaj w systemie scigania kierowcow drogowych" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    do {
            cout << "--------------------------------------------------------------------" << endl;
            cout << "|      Jaka operacje chcesz wykonac?                               |" << endl;
            cout << "|      1) Dodaj kierowce                                           |" << endl;
            cout << "|      2) Usun kierowce (podaj jego index)                         | " << endl;
            cout << "|      3) Wypisz kierowcow                                         |" << endl;
            cout << "|      4) Zatrzymaj kierowce                                       |" << endl;
            cout << "|      5) Pokaz wykroczenia w systemie                             |" << endl;
            cout << "|      6) Edytuj kierowce:                                         |" << endl;
            cout << "|      7) Wyswietl zawartosc pliku dane.txt                        |" << endl;
            cout << "--------------------------------------------------------------------" << endl;


        string s;
        getline(cin, s);
        x = stoi(s);
        switch (x) {
        case 1:
            system.dodaj();
            break;
        case 2:
            int id;
            cout << "Podaj ID kierowcy: ";
            getline(cin, s);
            id = stoi(s);
            index = id - 1;
            system.usun(id);
            break;
        case 3:
            system.wypiszKierowce();
            break;
        case 4:
            int idKierowcy, idWykroczenia;
            idWykroczenia = rand() % 4;
            cout << "Podaj numer indeksu kierowcy" << endl;
            getline(cin, s);
            idKierowcy = stoi(s);
            system.wykonajTest(idKierowcy, idWykroczenia);
            break;
        case 5:
            system.wypiszWykroczenie();
            break;
        case 6:
            int x;
            cout << "Podaj numer indeksu: " << endl;
            getline(cin, s);
            x = stoi(s);
            system.edytujKierowce(x);
            break;
        case 7:
            WyswietlDaneZPliku("dane.txt");
            break;
        }
        cout << "Czy chcesz kontynuowac dzialanie programu? (t/n)" << endl;
        getline(cin, kontynuacja);
        while (kontynuacja != "t" && kontynuacja != "n") {
            cout << "Niepoprawna odpowiedz. Wpisz 't' lub 'n': ";
            getline(cin, kontynuacja);
        }
        if (kontynuacja == "n") {
            dzialanie = false;
        }

        Zapisz("dane.txt", system);

        } while (dzialanie);

        system.czysc();
        system.Wczysc();
        dzialanie = false;
    }

