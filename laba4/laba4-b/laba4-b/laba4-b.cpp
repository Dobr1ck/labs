#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>

auto sortAscending = [](std::string s1, std::string s2) {
    return s1 < s2;
    };

class BD {
private:
    std::vector<std::string> references_ru;
    std::vector<std::string> references_en;
    std::string fileName;

    std::vector<std::string> getSorted(std::vector<std::string> arr, std::function<bool(std::string, std::string)> sortFunction) {
        auto a = arr;
        sort(a.begin(), a.end(), sortFunction);
        return a;
    }

    void display(std::vector<std::string> arr, bool withNumber) {
        for (int i = 0; i < arr.size(); i++) {
            std::cout << (withNumber ? std::to_string(i + 1) + ".\t" : "") << arr[i] << "\n";
        }
    }

public:
    BD(const std::string& fName) {
        fileName = fName;
        loadFile();
    };

    void loadFile() {
        std::ifstream file(fileName);
        if (!file.is_open()) return;
        references_ru.clear();
        references_en.clear();
        std::string line;
        std::string number;
        while (getline(file, line)) {
            auto index = line.find(".") + 2;
            auto str = line.substr(index, line.size() - index);
            if (str[0] > 65 && str[0] < 122) references_en.push_back(str);
            else references_ru.push_back(str);
        }
    };

    void display(std::function<bool(std::string, std::string)> sortFunction, bool withNumber) {
        std::vector<std::string> commonArr = getSorted(references_ru, sortFunction);
        for (auto el : getSorted(references_en, sortFunction)) commonArr.push_back(el);
        display(commonArr, withNumber);
    }

    ~BD() = default;
};

int main() {
    setlocale(LC_ALL, "Russian");
    BD db("data.txt");
    std::cout << "References with numbers: \n";
    db.display(sortAscending, true);

    std::cout << "\nReferences: \n";
    db.display(sortAscending, false);
    return 0;
}
