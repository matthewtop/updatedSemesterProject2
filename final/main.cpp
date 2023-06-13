#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "classes.h"
#include <vector>

using namespace std;
extern int global;

string SystemPolicji::nazwa = "ZUT DROGOWKA";

int main() {

    int x;
    int index;
    bool dzialanie = true;
    string kontynuacja, s;
    SystemPolicji system = SystemPolicji();
    vector<Osoba*> osoby;
    Zapisz("dane.txt", system);
    Wczytaj("dane.txt", system);



    cout << "--------------------------------------------------------------------" << endl;
    cout << "       Witaj w systemie scigania kierowcow " << SystemPolicji::nazwa << endl;
    cout << "--------------------------------------------------------------------" << endl;

    do {
        cout << "--------------------------------------------------------------------" << endl;
        cout << "|      Jaka operacje chcesz wykonac?                               |" << endl;
        cout << "|      1) Dodaj kierowce                                           |" << endl;
        cout << "|      2) Usun kierowce (podaj jego index)                         | " << endl;
        cout << "|      3) Wypisz kierowcow                                         |" << endl;
        cout << "|      4) Zatrzymaj kierowce                                       |" << endl;
        cout << "|      5) Edytuj kierowce:                                         |" << endl;
        cout << "|      6) Pokaz wykroczenia w systemie                             |" << endl;
        cout << "|      7) Wyswietl zawartosc pliku dane.txt                        |" << endl;
        cout << "|      8) Dodaj policjanta                                         |" << endl;
        cout << "|      9) Edytuj policjanta                                        |" << endl;
        cout << "|      10) Usun policjanta                                         |" << endl;
        cout << "|      11)Wypisz policjantow                                       |" << endl;
        cout << "|      12)Wypisz osoby                                             |" << endl;
        cout << "|      13)Wylegitymuj osobe i sprawdz kim jest                     |" << endl;
        cout << "|      14)Posortuj kierowcow wg ilosci pkt karnych                 |" << endl;
        cout << "--------------------------------------------------------------------" << endl;


        string s;
        getline(cin, s);
        x = stoi(s);
        switch (x) {
        case 1:
            system.dodaj();
            Zapisz("dane.txt", system);
            break;
        case 2:
            int id;
            cout << "Podaj ID kierowcy: ";
            getline(cin, s);
            id = stoi(s);
            index = id - 1;
            system.usun(id);
            Zapisz("dane.txt", system);
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
            Zapisz("dane.txt", system);
            break;
        case 5:
            int e;
            cout << "Podaj numer indeksu: " << endl;
            getline(cin, s);
            e = stoi(s);
            system.edytujKierowce(e);
            Zapisz("dane.txt", system);
            break;
        case 6:
            system.wypiszWykroczenie();
            Zapisz("dane.txt", system);
            break;
        case 7:
            WyswietlDaneZPliku("dane.txt");
            break;
        case 8:
            system.dodajPolicjanta();
            Zapisz("dane.txt", system);
            break;
        case 9:
            int eP;
            cout << "Podaj numer id policjanta, by edytowac jego atrybuty: " << endl;
            getline(cin, s);
            eP = stoi(s);
            system.edytujPolicjanta(eP);
            Zapisz("dane.txt", system);
            break;
        case 10:
            int idP;
            cout << "Podaj ID policjanta, ktorego chcesz usunac: ";
            getline(cin, s);
            idP = stoi(s);
            index = idP - 1;
            system.usunPolicjanta(idP);
            Zapisz("dane.txt", system);
            break;
        case 11:
            system.wypiszPolicjanta();
            break;
        case 12:
            system.wyswietl_osoby();
            break;
        case 13:
            system.wylegitymuj();
            break;
        case 14:
            system.sortujKierowcowBabelkowo(system.getKierowcy(), system.getRozmiarKierowca());
            cout << "Kierowcy zostali posortowani";
            Zapisz("dane.txt", system);
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

