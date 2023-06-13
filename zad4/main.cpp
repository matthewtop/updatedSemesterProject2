#include <iostream>
#include <string>
#include <random>-
#include "classes.h"

using namespace std;
extern int global;

int main() {

    int  x;
    int index;
    bool z = true;
    string kontynuacja, s;
    SystemPolicji system = SystemPolicji();


    cout << "--------------------------------------------------------------------" << endl;
    cout << "       Witaj w systemie scigania kierowcow drogowych" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    do {
        cout << "Jaka operacje chcesz wykonac?" << endl;
        cout << "1) Dodaj kierowce" << endl;
        cout << "2) Usun kierowce (podaj jego index)" << endl;
        cout << "3) Wypisz kierowcow" << endl;
        cout << "4) Zatrzymaj kierowce" << endl;
        cout << "5) Pokaz wykroczenia w systemie" << endl;
        cout << "6) Edytuj kierowce: " << endl;
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
            cout << "Podaj numer indexu: " << endl;
            getline(cin, s);
            x = stoi(s);
            system.edytujKierowce(x);
            break;
        }

        cout << "Czy chcesz kontynuowac dzialanie programu? (tak/nie)" << endl;
        getline(cin, kontynuacja);
        if (kontynuacja == "nie") {
            z = false;
        }

    } while (z);

    system.czysc();
    system.Wczysc();
}

