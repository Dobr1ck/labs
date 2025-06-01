#include <iostream>
#include <vector>
#include <crtdbg.h>
#include <string>
using namespace std;

enum BookType { ARTISTIC, TECHNICAL };

struct Book {
    string author;
    string title;
    BookType type;

    Book(const string& author, const string& title, BookType type)
        : author(author), title(title), type(type) {
    }
};

class Library {
private:
    vector<Book*> books;

public:
    Library() {}

    ~Library() {
        for (int i = 0; i < books.size(); i++) delete books[i];
    }

    void addBook(const string& author, const string& title, BookType type) {
        if (author.empty() || title.empty()) return;
        books.push_back(new Book(author, title, type));
    }

    void displayBySwitch() {
        cout << "Display count of books by switch:\n";
        int aCount = 0, tCount = 0;
        for (int i = 0; i < books.size(); i++) {
            switch (books[i]->type) {
            case ARTISTIC:
                aCount++;
                break;
            case TECHNICAL:
                tCount++;
                break;
            }
        }
        cout << "\tArtistic books count: " << aCount << endl;
        cout << "\tTechnical books count: " << tCount << endl;
    }

    void display() {
        cout << "Display count of books:\n";
        int aCount = 0, tCount = 0;
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->type == ARTISTIC) aCount++;
            if (books[i]->type == TECHNICAL) tCount++;
        }
        cout << "\tArtistic books count: " << aCount << endl;
        cout << "\tTechnical books count: " << tCount << endl;
    }
};

int main() {
    Library library; // использован конструктор по умолчанию
    library.addBook("AUTHOR-0", "BOOK-0", ARTISTIC);
    for (int i = 0; i < 20; i++) {
        library.addBook("AUTHOR-" + to_string(i + 1), "BOOK-" + to_string(i + 1), i % 2 == 0 ? ARTISTIC : TECHNICAL);
    }
    library.display();
    library.displayBySwitch();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
}