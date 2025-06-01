#include <iostream>
#include <vector>
#include <typeinfo>
#include<crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using namespace std;

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
};


class Class1 {
public:
    virtual ~Class1() {}

    virtual Class1* copy() const {
        return new Class1(*this);
    }
};


class Class2 : public Class1 {
public:


    Class1* copy() const override {
        return new Class2(*this);
    }
};


void COPY(vector<Class1*>& db, const Class1& obj) {
    db.push_back(obj.copy());
}

int main() {
    Class1 volk;
    Class1 lisa;
    Class2 kolobok;
    vector<Class1*> database;

    COPY(database, volk);
    COPY(database, lisa);
    COPY(database, kolobok);
    for (int i = 0; i < database.size(); ++i) {
        cout << "Object " << i + 1 << " HAS type: " << typeid(*database[i]).name() << endl;

    }
    for (int i = 0; i < database.size(); ++i) {
        delete database[i];
    }
    database.clear();
    return 0;
}