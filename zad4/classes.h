#include <iostream>
#include <string>
#include <random>

extern int global;
using namespace std;

string imiona[10]{ "Mateusz","Arkadiusz","Dominik","Radoslaw","Jakub","Ziemowit","Nikodem","Radoslaw","Krzysztof","Michal" };

string nazwiska[10]{ "Tolpa","Nowak","Silny","Ostry","Karas","Tyrakowski","Kowalski","Polski","Szybki","Czarniawski", };

string wykroczeniaNazwy[5]{ "Przekroczenie predkosci","Wyprzedzanie na ciaglej","Ucieczka","Wylaczone swiatla","Brak badania technicznego" };

int losowaLiczba(int min, int max) {
    random_device rd;
    default_random_engine e{ rd() };
    uniform_int_distribution<unsigned> u(min, max);
    return u(e);
}

class Kierowca {

private:
    int id;
    string imie;
    string nazwisko;
    size_t punktyKarne;

public:

    Kierowca() = default;

    int getId() const {
        return id;
    }


    void gen_data(int ind) {
        id = ind;
        imie = imiona[losowaLiczba(0, 9)];
        nazwisko = nazwiska[losowaLiczba(0, 9)];
        punktyKarne = losowaLiczba(0, 10);
    }

    void wypisz() {
        cout << "ID: " << id << endl;
        cout << "Imie: " << imie << endl;
        cout << "Nazwiskko: " << nazwisko << endl;
        cout << "Punkty karne: " << punktyKarne << endl;
    }

    bool TestKierowcy(int przyznanePunktyKarne) {
        if (punktyKarne + przyznanePunktyKarne > 20) {
            cout << imie << " " << nazwisko << endl;
            cout << "Kierowca stracil prawo jazdy" << endl;
            return true;
        }
        else {
            cout << "Kierowca ma prawo jazdy" << endl;
            punktyKarne += przyznanePunktyKarne;
            cout << imie << " " << nazwisko << endl << "Punkty karne (max 21): " << punktyKarne << endl;
            return false;
        }
    }

    void edytuj() {
        string dane;
        string rozdziel = " ";
        string tab[3];
        int counter = 0, pk;

        getline(cin, dane);
        int pos = 0;
        string token;
        while ((pos = dane.find(rozdziel)) != string::npos) {
            token = dane.substr(0, pos);
            tab[counter] = token;

            dane.erase(0, pos + rozdziel.length());
            counter++;
        }
        tab[2] = dane;
        pk = stoi(tab[2]);

        imie = tab[0];
        nazwisko = tab[1];
        punktyKarne = pk;
    }
};

class SystemPolicji {
private:
    Kierowca** kierowcy;
    size_t rozmiarKierowca;
    size_t rozmiarWykroczenie;

    class Wykroczenie {

    private:
        int id;
        string nazwa;
        int przyznanePunktyKarne;
        friend class SystemPolicji;

    public:
        Wykroczenie() = default;


        void gen_data(int ind) {
            id = ind;
            nazwa = wykroczeniaNazwy[losowaLiczba(0, 4)];
            przyznanePunktyKarne = losowaLiczba(1, 7);
        }

        void wypisz() {
            cout << "ID: " << id << endl;
            cout << "Nazwa: " << nazwa << endl;
            cout << "Punkty karne: " << przyznanePunktyKarne << endl;
        }
    };

    Wykroczenie* wykroczenia;

public:
    SystemPolicji() {
        rozmiarKierowca = 5;
        rozmiarWykroczenie = 5;
        stworz();
        ini();
        Wstworz();
        Wini();
    }


    //konstruktor kopiujacy
    SystemPolicji& operator=(const SystemPolicji& t) {
        if (this != &t) {

            delete[] kierowcy;
            delete[] wykroczenia;

            rozmiarKierowca = t.rozmiarKierowca;
            kierowcy = new Kierowca * [rozmiarKierowca];
            for (int i = 0; i < rozmiarKierowca; i++) {
                kierowcy[i] = new Kierowca(*t.kierowcy[i]);
            }

            rozmiarWykroczenie = t.rozmiarWykroczenie;
            wykroczenia = new Wykroczenie[rozmiarWykroczenie];
            for (int i = 0; i < rozmiarWykroczenie; i++) {
                wykroczenia[i] = t.wykroczenia[i];
            }
        }
        return *this;
    }


    SystemPolicji(int rozmiarKierowca, int rozmiarWykroczenie) {
        rozmiarKierowca = rozmiarKierowca;
        rozmiarWykroczenie = rozmiarWykroczenie;
        stworz();
        ini();
        Wstworz();
        Wini();
    }

    ~SystemPolicji() {
        czysc();
        Wczysc();
    }


    void stworz() {
        kierowcy = new Kierowca * [rozmiarKierowca];
        for (int ind = 0; ind < rozmiarKierowca; ind++)
            kierowcy[ind] = new Kierowca;
    }

    void ini() {
        for (int ind = 0; ind < rozmiarKierowca; ind++) {
            kierowcy[ind]->gen_data(ind);
        }
    }

    void wypiszKierowce() {
        for (int ind = 0; ind < rozmiarKierowca; ind++) {
            kierowcy[ind]->wypisz();
        }
    }

    void czysc() {
        for (int ind = 0; ind < rozmiarKierowca; ind++)
            delete kierowcy[ind];
        delete[] kierowcy;
        kierowcy = nullptr;
        rozmiarKierowca = 0;
    }
    void usun(int id) {
        for (int i = 0; i < rozmiarKierowca; i++) {
            if (kierowcy[i]->getId() == id) {
                delete kierowcy[i];
                for (int j = i; j < rozmiarKierowca - 1; j++) {
                    kierowcy[j] = kierowcy[j + 1];
                }
                rozmiarKierowca--;
                return;
            }
        }
        cout << "Kierowca o podanym ID nie istnieje." << endl;
    }
    void dodaj() {
        Kierowca** temp = new Kierowca * [rozmiarKierowca + 1];
        if (rozmiarKierowca == 0) {
            temp[rozmiarKierowca] = new Kierowca;
        }
        else {
            for (size_t i = 0; i < rozmiarKierowca; ++i)
                temp[i] = kierowcy[i];
            temp[rozmiarKierowca] = new Kierowca;
            delete[] kierowcy;
        }
        temp[rozmiarKierowca]->gen_data(rozmiarKierowca);
        kierowcy = temp;
        ++rozmiarKierowca;
    }
    void wykonajTest(int idKierowcy, int idWykroczenia) {
        if (kierowcy[idKierowcy]->TestKierowcy(wykroczenia[idWykroczenia].przyznanePunktyKarne))usun(idKierowcy);
    }
    void Wstworz() {
        wykroczenia = new Wykroczenie[rozmiarWykroczenie];
    }

    void Wini() {
        for (int ind = 0; ind < rozmiarWykroczenie; ind++) {
            wykroczenia[ind].gen_data(ind);
        }
    }

    void wypiszWykroczenie() {
        for (int ind = 0; ind < rozmiarWykroczenie; ind++) {
            wykroczenia[ind].wypisz();
        }
    }

    void Wczysc() {
        delete[] wykroczenia;
        wykroczenia = nullptr;
    }

    void edytujKierowce(int ind) {
        kierowcy[ind]->edytuj();
    }

};



