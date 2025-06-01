#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Auto {
protected:
    string name;
    string model;

public:
    Auto(const string model) {
        this->model = model;
    }

    virtual ~Auto() {
        cout << "Automobile: " << name << "-" << model << endl;
    }
};

class Audi : public Auto {
public:
    Audi(const string model) : Auto(model) {
        name = "Audi";
    }

    virtual ~Audi() = default;
};

class Kia : public Auto {
public:
    Kia(const string model) : Auto(model) {
        name = "Kia";
    }

    virtual ~Kia() = default;
};

class Hyundai : public Auto {
public:
    Hyundai(const string model) : Auto(model) {
        name = "Hyundai";
    }

    virtual ~Hyundai() = default;
};

int main() {
    ifstream file("automobiles.txt");
    vector<Auto*> automobiles;

    int linesCount = 0;
    if (file.is_open()) {
        string temp;
        while (getline(file, temp)) linesCount++;
        file.close();
    }
    else {
        cerr << "Unable to open file" << endl;
    }

    file.open("automobiles.txt");
    for (int i = 0; i < linesCount; i++) {
        string automobile;
        getline(file, automobile);
        string name, model;
        bool spaceFound = false;
        for (int i = 0; i < automobile.size(); i++) {
            if (automobile[i] == ' ') {
                spaceFound = true;
                continue;
            }
            if (!spaceFound) name += automobile[i];
            else model += automobile[i];
        }
        if (name == "Audi") automobiles.push_back(new Audi(model));
        if (name == "Kia") automobiles.push_back(new Kia(model));
        if (name == "Hyundai") automobiles.push_back(new Hyundai(model));
    }
    for (int i = 0; i < automobiles.size(); i++) delete automobiles[i];
    return 0;
}