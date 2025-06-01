#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Detail {
protected:
    string name;
    Detail() {};
    Detail(string name) : name(name) {};
public:
    virtual ~Detail() {
        cout << "Object rip" << endl;
    };
    virtual void show() const {
        cout << "Detal: " << name << endl;
    }
    template<typename T>
    friend void createObject(vector<Detail*>& arr);
};

class Assembly : public Detail {
protected:
    Assembly();
    Assembly(string name) : Detail(name) {};
public:
    ~Assembly() {};
    void show() const override {
        cout << "Sborka: " << name << endl;
    }
    template<typename T>
    friend void createObject(vector<Detail*>& arr);
};

template <typename T>
void createObject(vector<Detail*>& arr) {
    string name;
    cout << "Enter name for object: ";
    cin >> name;
    arr.push_back(new T(name));
}

int main()
{
    vector<Detail*> arr;

    createObject<Detail>(arr);
    createObject<Assembly>(arr);

    for (int i = 0; i < arr.size(); i++) {
        arr[i]->show();
    }

    for (int i = 0; i < arr.size(); i++) {
        delete arr[i];
    }
}