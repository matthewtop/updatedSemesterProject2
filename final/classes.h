#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

string imiona[10]{ "Mateusz","Arkadiusz","Dominik","Radoslaw","Jakub","Ziemowit","Nikodem","Radoslaw","Krzysztof","Michal" };

string nazwiska[10]{ "Tolpa","Nowak","Silny","Ostry","Karas","Tyrakowski","Kowalski","Polski","Szybki","Czarniawski", };

string wykroczeniaNazwy[5]{ "Przekroczenie predkosci","Wyprzedzanie na linii ciaglej","Ucieczka","Wylaczone swiatla","Brak badania technicznego" };

int losowaLiczba(int min, int max) {
    random_device rd;
    default_random_engine e{ rd() };
    uniform_int_distribution<unsigned> u(min, max);
    return u(e);
}


class Osoba {
protected:
    string imie;
    string nazwisko;

public:

    virtual void przedstaw_sie() = 0; //funkcja do prezentacji polimorfizmu


    virtual void wylegitymuj() = 0;//--||--


    Osoba() : imie(""), nazwisko("") {}
    Osoba(const string& _imie, const string& _nazwisko) : imie(_imie), nazwisko(_nazwisko) {}

    string getImie() const {
        return imie;
    }

    string getNazwisko() const {
        return nazwisko;
    }


};

class Kierowca : public Osoba {
private:
    int id;
    size_t punktyKarne;

public:

    Kierowca() : id(0), punktyKarne(0) {}

    int getId() const {
        return id;
    }

    size_t getPunktyKarne() const {
        return punktyKarne;
    }

    friend istream& operator>>(istream& in, Kierowca& t) {
        in >> t.id;
        in >> t.imie;
        in >> t.nazwisko;
        in >> t.punktyKarne;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Kierowca& t) {
        out << t.id << endl;
        out << t.imie << endl;
        out << t.nazwisko << endl;
        out << t.punktyKarne << endl;
        return out;
    }

    void gen_data(int ind) {
        id = ind;
        imie = imiona[losowaLiczba(0, 9)];
        nazwisko = nazwiska[losowaLiczba(0, 9)];
        punktyKarne = losowaLiczba(1, 10);
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
        string rozdziel = ";";
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

    virtual void przedstaw_sie() override {
        cout << "Nazywam sie " << imie << " " << nazwisko << "." << std::endl;
    }

    virtual void wylegitymuj() override {
        cout << "Jestem kierowca. Nazywam sie " << imie << " " << nazwisko << " i posiadam " << punktyKarne << " punkt/ow karnych" << endl;
    }
};


class Policjant : public Osoba {
private:
    int id;
    int numerLegitymacji;

public:
    Policjant() : id(0), numerLegitymacji(0) { }

    //Policjant(int id) { gen_data(id); }

    int getId() const {
        return id;
    }

    int getNumerLegitymacji() const {
        return numerLegitymacji;
    }

    friend istream& operator>>(istream& in, Policjant& t) {
        in >> t.numerLegitymacji;
        in >> t.imie;
        in >> t.nazwisko;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Policjant& t) {
        out << t.numerLegitymacji << endl;
        out << t.imie << endl;
        out << t.nazwisko << endl;
        return out;
    }

    void gen_data(int ind) {
        id = ind;
        imie = imiona[losowaLiczba(0, 9)];
        nazwisko = nazwiska[losowaLiczba(0, 9)];
        numerLegitymacji = losowaLiczba(100000, 999999);
    }

    //void wypisz() const override {
    //    cout << "Policjant:" << endl;
    //    cout << "ID: " << id << endl;
    //    cout << "Numer legitymacji: " << numerLegitymacji << endl;
    //    cout << "Imie " << imie << endl;
    //    cout << "Nazwisko: " << nazwisko << endl;
    //}

    void edytuj() {
        string dane;
        string rozdziel = ";";
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
        numerLegitymacji = numerLegitymacji;
    }



    virtual void przedstaw_sie() override {
        cout << "Nazywam sie " << imie << " " << nazwisko << "." << std::endl;
    }

    virtual void wylegitymuj() override {
        cout << "Jestem policjantem. Nazywam sie " << imie << " " << nazwisko << endl;
        cout << "Moj numer legitymacji to " << numerLegitymacji << endl;
    }

};



class SystemPolicji {
private:
    Kierowca** kierowcy;
    Policjant** policjanci;
    vector<Osoba*> osoby;

    size_t rozmiarKierowca;
    size_t rozmiarWykroczenie;
    size_t rozmiarPolicjant;

    class Wykroczenie {

    private:
        int id;
        string nazwa;
        int przyznanePunktyKarne;
        friend class SystemPolicji;

    public:
        Wykroczenie() : id(0), nazwa(""), przyznanePunktyKarne(0) {} // konstruktor domyslny

        Wykroczenie(int _id, const string& _nazwa, int _przyznanePunktyKarne)
            : id(_id), nazwa(_nazwa), przyznanePunktyKarne(_przyznanePunktyKarne) {}

        friend istream& operator>>(istream& in, Wykroczenie& t) {
            in >> t.id;
            in >> t.nazwa;
            in >> t.przyznanePunktyKarne;
            return in;
        }

        friend ostream& operator<<(ostream& out, const Wykroczenie& t) {
            out << t.id << endl;
            out << t.nazwa << endl;
            out << t.przyznanePunktyKarne << endl;
            return out;
        }

        void gen_data(int ind) {
            id = ind;
            nazwa = wykroczeniaNazwy[losowaLiczba(0, 4)];
            przyznanePunktyKarne = losowaLiczba(1, 8);
        }

        void wypisz() {
            cout << "+--------+----------------------+---------------+" << endl;
            cout << "|   ID   |        Nazwa         | Punkty karne  |" << endl;
            cout << "+--------+----------------------+---------------+" << endl;
            cout << "| " << setw(6) << left << id << " | " << setw(20) << left << nazwa << " | " << setw(13) << left << przyznanePunktyKarne << " |" << endl;
            cout << "+--------+----------------------+---------------+" << endl;
        }
    };

    Wykroczenie* wykroczenia;

public:
    SystemPolicji() {
        rozmiarKierowca = losowaLiczba(5, 15);
        rozmiarWykroczenie = 5;
        rozmiarPolicjant = losowaLiczba(5, 15);
        stworz();
        ini();
        Wstworz();
        Wini();
    }

    static string nazwa;

    Kierowca** getKierowcy() const {
        return kierowcy;
    }

    size_t getRozmiarKierowca() const {
        return rozmiarKierowca;
    }

    void wyswietl_osoby() {
        for (int i = 0; i < osoby.size(); i++) {
            cout << "ID: " << i << endl;
            osoby[i]->przedstaw_sie();
            cout << endl;
        }
    }

    void wylegitymuj() {
        int legit;
        cout << "Podaj numer zaczynajac od 0 ktorej chcesz wylegitymowac" << endl;
        cin >> legit;
        osoby[legit]->wylegitymuj();
    }




    //konstruktor kopiujacy
    SystemPolicji& operator=(const SystemPolicji& t) {
        if (this != &t) {

            delete[] kierowcy;
            delete[] wykroczenia;
            delete[] policjanci;

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

            rozmiarPolicjant = t.rozmiarPolicjant;
            policjanci = new Policjant * [rozmiarPolicjant];
            for (int i = 0; i < rozmiarPolicjant; i++) {
                policjanci[i] = new Policjant(*t.policjanci[i]);
            }
        }
        return *this;
    }


    SystemPolicji(int rozmiarKierowca, int rozmiarWykroczenie, int rozmiarPolicjant) {
        rozmiarKierowca = rozmiarKierowca;
        rozmiarWykroczenie = rozmiarWykroczenie;
        rozmiarPolicjant = rozmiarPolicjant;
        stworz();
        ini();
        Wstworz();
        Wini();
    }

    ~SystemPolicji() {
        czysc();
        Wczysc();
    }


    Wykroczenie& operator[](int i) {
        return wykroczenia[i];
    }


    friend istream& operator>>(istream& in, SystemPolicji& t) {
        in >> t.rozmiarKierowca;
        t.kierowcy = new Kierowca * [t.rozmiarKierowca];
        for (int i = 0; i < t.rozmiarKierowca; i++) {
            t.kierowcy[i] = new Kierowca;
            in >> *(t.kierowcy[i]);
        }
        in >> t.rozmiarWykroczenie;
        t.wykroczenia = new Wykroczenie[t.rozmiarWykroczenie];
        for (int i = 0; i < t.rozmiarWykroczenie; i++) {
            t.wykroczenia[i] = t[i];
            in >> t.wykroczenia[i];
        }
        in >> t.rozmiarPolicjant;
        t.policjanci = new Policjant * [t.rozmiarPolicjant];
        for (int i = 0; i < t.rozmiarPolicjant; i++) {
            t.policjanci[i] = new Policjant;
            in >> *(t.policjanci[i]);
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, const SystemPolicji& t) {
        out << t.rozmiarKierowca << endl;
        for (int i = 0; i < t.rozmiarKierowca; i++) {
            out << *(t.kierowcy[i]);
        }
        out << t.rozmiarWykroczenie << endl;
        for (int i = 0; i < t.rozmiarWykroczenie; i++) {
            out << (t.wykroczenia[i]);
        }
        out << t.rozmiarPolicjant << endl;
        for (int i = 0; i < t.rozmiarPolicjant; i++) {
            out << *(t.policjanci[i]);
        }

        return out;
    }

    void stworz() {
        kierowcy = new Kierowca * [rozmiarKierowca];
        for (int ind = 0; ind < rozmiarKierowca; ind++) {
            kierowcy[ind] = new Kierowca;
            osoby.push_back(kierowcy[ind]); // dodaj kierowce do wektora osoby
        }


        policjanci = new Policjant * [rozmiarPolicjant];
        for (int ind = 0; ind < rozmiarPolicjant; ind++) {
            policjanci[ind] = new Policjant;
            osoby.push_back(policjanci[ind]); // dodaj policjanta do wektora osoby
        }
    }

    void ini() {
        for (int ind = 0; ind < rozmiarKierowca; ind++) {
            kierowcy[ind]->gen_data(ind);
        }
        for (int ind = 0; ind < rozmiarPolicjant; ind++) {
            policjanci[ind]->gen_data(ind);
        }

    }

    void dodaj() {
        Kierowca** temp = new Kierowca * [rozmiarKierowca + 1];
        if (rozmiarKierowca == 0) {
            temp[rozmiarKierowca] = new Kierowca;
            osoby.push_back(temp[rozmiarKierowca]);
        }
        else {
            for (size_t i = 0; i < rozmiarKierowca; ++i)
                temp[i] = kierowcy[i];
            temp[rozmiarKierowca] = new Kierowca;
            delete[] kierowcy;
            osoby.push_back(temp[rozmiarKierowca]);
        }
        temp[rozmiarKierowca]->gen_data(rozmiarKierowca);
        kierowcy = temp;
        ++rozmiarKierowca;
    }
    void dodajPolicjanta() {
        Policjant** temp = new Policjant * [rozmiarPolicjant + 1];
        if (rozmiarPolicjant == 0) {
            temp[rozmiarPolicjant] = new Policjant;
            osoby.push_back(temp[rozmiarPolicjant]);
        }
        else {
            for (size_t i = 0; i < rozmiarPolicjant; ++i)
                temp[i] = policjanci[i];
            temp[rozmiarPolicjant] = new Policjant;
            delete[] policjanci;
            osoby.push_back(temp[rozmiarPolicjant]);
        }
        temp[rozmiarPolicjant]->gen_data(rozmiarPolicjant);
        policjanci = temp;
        ++rozmiarPolicjant;

    }


    void wypiszKierowce() {
        cout << "--------------------------------------------------------------" << endl;
        cout << "|   ID   |    Imie    |  Nazwisko  | Punkty karne |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        for (int ind = 0; ind < rozmiarKierowca; ind++) {
            cout << "| " << setw(6) << left << kierowcy[ind]->getId()
                << "| " << setw(11) << left << kierowcy[ind]->getImie()
                << "| " << setw(11) << left << kierowcy[ind]->getNazwisko()
                << "| " << setw(13) << left << kierowcy[ind]->getPunktyKarne()
                << "|" << endl;
        }
        cout << "--------------------------------------------------------------" << endl;
    }

    void wypiszPolicjanta() {
        cout << "--------------------------------------------------------------" << endl;
        cout << "|   ID   |    Imie    |  Nazwisko  | Numer legitymacji  |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        for (int ind = 0; ind < rozmiarPolicjant; ind++) {
            cout << "| " << setw(6) << left << policjanci[ind]->getId()
                << "| " << setw(11) << left << policjanci[ind]->getImie()
                << "| " << setw(11) << left << policjanci[ind]->getNazwisko()
                << "| " << setw(13) << left << policjanci[ind]->getNumerLegitymacji()
                << "|" << endl;
        }
        cout << "--------------------------------------------------------------" << endl;
    }

    void sortujKierowcowBabelkowo(Kierowca** kierowcy, size_t rozmiarKierowcy) {
        for (size_t i = 0; i < rozmiarKierowcy - 1; i++) {
            for (size_t j = 0; j < rozmiarKierowcy - i - 1; j++) {
                if (kierowcy[j]->getPunktyKarne() > kierowcy[j + 1]->getPunktyKarne()) {
                    Kierowca* temp = kierowcy[j];
                    kierowcy[j] = kierowcy[j + 1];
                    kierowcy[j + 1] = temp;
                }
            }
        }
    }


    void usun(int id) {
        for (int i = 0; i < rozmiarKierowca; i++) {
            if (kierowcy[i]->getId() == id) {
                delete kierowcy[i];
                osoby.erase(remove(osoby.begin(), osoby.end(), kierowcy[i]), osoby.end()); // usun kierowcę z wektora osoby
                for (int j = i; j < rozmiarKierowca - 1; j++) {
                    kierowcy[j] = kierowcy[j + 1];
                }
                rozmiarKierowca--;
                return;
            }
        }
        cout << "Kierowca o podanym ID nie istnieje." << endl;
    }
    void usunPolicjanta(int idP) {
        for (int i = 0; i < rozmiarPolicjant; i++) {
            if (policjanci[i]->getId() == idP) {
                delete policjanci[i];
                osoby.erase(remove(osoby.begin(), osoby.end(), policjanci[i]), osoby.end()); // usun kierowcę z wektora osoby
                for (int j = i; j < rozmiarPolicjant - 1; j++) {
                    policjanci[j] = policjanci[j + 1];
                }
                rozmiarPolicjant--;
                return;
            }
        }
        cout << "Policjant o podanym ID nie istnieje." << endl;
    }


    void czysc() {
        for (int ind = 0; ind < rozmiarKierowca; ind++)
            delete kierowcy[ind];
        delete[] kierowcy;
        kierowcy = nullptr;
        rozmiarKierowca = 0;

        for (int ind = 0; ind < rozmiarPolicjant; ind++)
            delete policjanci[ind];
        delete[] policjanci;
        policjanci = nullptr;
        rozmiarPolicjant = 0;

    }

    void wykonajTest(int idKierowcy, int idWykroczenia) {
        if (kierowcy[idKierowcy]->TestKierowcy(wykroczenia[idWykroczenia].przyznanePunktyKarne))usun(idKierowcy);
    }

    void wypiszWykroczenie() {
        for (int ind = 0; ind < rozmiarWykroczenie; ind++) {
            wykroczenia[ind].wypisz();
        }
    }

    void edytujKierowce(int ind) {
        kierowcy[ind]->edytuj();
    }

    void edytujPolicjanta(int ind) {
        policjanci[ind]->edytuj();
    }


    void Wstworz() {
        wykroczenia = new Wykroczenie[rozmiarWykroczenie];
    }

    void Wini() {
        for (int ind = 0; ind < rozmiarWykroczenie; ind++) {
            wykroczenia[ind].gen_data(ind);
        }
    }

    void Wczysc() {
        delete[] wykroczenia;
        wykroczenia = nullptr;
    }


};

void Zapisz(string plik, const SystemPolicji& system) {
    ofstream out(plik);
    if (!out)return;
    out << system;
    out.close();
}

void Wczytaj(string plik, SystemPolicji& system) {
    ifstream in(plik);
    if (!in)return;
    in >> system;
    in.close();
}

void WyswietlDaneZPliku(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik) {
        cout << "Nie mozna otworzyc pliku " << nazwaPliku << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }
    plik.close();
}


