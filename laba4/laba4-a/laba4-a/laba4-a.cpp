#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>

struct Employee {
    std::string name;
    std::string birthYear;
    std::string profession;
    std::string structure;
};

auto split = [](const std::string& baseString, const std::string& separator) {
    std::vector<std::string> splittedValue;
    size_t start = 0, end = baseString.find(separator);
    while (end != std::string::npos) {
        splittedValue.push_back(baseString.substr(start, end - start));
        start = end + separator.length();
        end = baseString.find(separator, start);
    }
    splittedValue.push_back(baseString.substr(start));
    return splittedValue;
    };

auto sortAscendingByBirthYear = [](const Employee& e1, const Employee& e2) {
    return e1.birthYear < e2.birthYear;
    };

auto isEngineer = [](const Employee& e) {
    return e.profession == "engineer";
    };

auto isNotChairman = [](const Employee& e) {
    return e.profession != "chairman";
    };

class BD {
private:
    std::vector<Employee> employees;
    std::string fileName;

    std::vector<Employee> getSorted(std::vector<Employee> arr, std::function<bool(const Employee&, const Employee&)> sortFunction) {
        std::sort(arr.begin(), arr.end(), sortFunction);
        return arr;
    }

    std::vector<Employee> getWithExceptions(const std::vector<Employee>& arr, const std::vector<std::function<bool(const Employee&)>> exceptions) {
        std::vector<Employee> result = arr;
        result.erase(std::remove_if(result.begin(), result.end(), [&](const Employee& e) {
            for (auto& ex : exceptions) {
                if (!ex(e)) return true;
            }
            return false;
            }), result.end());
        return result;
    }

    void display(const std::vector<Employee>& arr) {
        for (const auto& employee : arr) {
            std::cout << "Employee: " << "\n";
            std::cout << '\t' << employee.name << "\n";
            std::cout << '\t' << employee.birthYear << "\n";
            std::cout << '\t' << employee.profession << "\n";
            std::cout << '\t' << employee.structure << "\n";
        }
    }

public:
    BD(const std::string& fName) : fileName(fName) {
        loadFile();
    }

    void loadFile() {
        std::ifstream file(fileName);
        if (!file.is_open()) return;
        employees.clear();
        std::string line;
        while (std::getline(file, line)) {
            auto employeeData = split(line, ", ");
            if (employeeData.size() < 4) continue;
            employees.push_back(Employee{ employeeData[0], employeeData[1], employeeData[2], employeeData[3] });
        }
    }

    void display(std::function<bool(const Employee&, const Employee&)> sortFunction, const std::vector<std::function<bool(const Employee&)>>& exceptions) {
        display(getSorted(getWithExceptions(employees, exceptions), sortFunction));
    }

    void display(const std::vector<std::function<bool(const Employee&)>>& exceptions) {
        display(getWithExceptions(employees, exceptions));
    }

    void display(std::function<bool(const Employee&, const Employee&)> sortFunction) {
        display(getSorted(employees, sortFunction));
    }
};

int main() {
    BD db("data.txt");
    std::cout << "Engineers: \n";
    db.display({ isEngineer });

    std::cout << "\nNot chairmen with ascending sort: \n";
    db.display(sortAscendingByBirthYear, { isNotChairman });
    return 0;
}