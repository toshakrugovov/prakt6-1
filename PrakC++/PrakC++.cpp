#include <iostream>
#include <list>
#include <string>
#include <Windows.h>

using namespace std;

class Book {
public:
    string title;
    string author;
    string genre;
    bool reserved;

    Book(string _title, string _author, string _genre) : title(_title), author(_author), genre(_genre), reserved(false) {}
};

class User {
public:
    string username;
    list<Book*> reservedBooks;

    User(string _username) : username(_username) {}
};

class Library {
public:
    list<Book*> catalog;
    list<User*> users;

    void addBook(string title, string author, string genre) {
        catalog.push_back(new Book(title, author, genre));
    }

    void addUser(string username) {
        users.push_back(new User(username));
    }

    Book* findBookByTitle(string title) {
        for (Book* book : catalog) {
            if (book->title == title) {
                return book;
            }
        }
        return nullptr;
    }

    void reserveBook(User* user, Book* book) {
        if (book->reserved) {
            cout << "Извините, книга уже зарезервирована." << endl;
            return;
        }
        book->reserved = true;
        user->reservedBooks.push_back(book);
        cout << "Книга успешно зарезервирована." << endl;
    }

    void cancelReservation(User* user, Book* book) {
        if (!book->reserved) {
            cout << "Извините, книга не зарезервирована." << endl;
            return;
        }
        book->reserved = false;
        for (auto it = user->reservedBooks.begin(); it != user->reservedBooks.end(); ++it) {
            if (*it == book) {
                user->reservedBooks.erase(it);
                cout << "Резервация успешно отменена." << endl;
                return;
            }
        }
    }

    void searchByTitle(string title) {
        bool found = false;
        for (Book* book : catalog) {
            if (book->title == title) {
                found = true;
                cout << "Название: " << book->title << endl;
                cout << "Автор: " << book->author << endl;
                cout << "Жанр: " << book->genre << endl;
                cout << "Статус: " << (book->reserved ? "Зарезервирована" : "Доступна") << endl;
            }
        }
        if (!found) {
            cout << "Книга с названием '" << title << "' не найдена." << endl;
        }
    }

    void searchByAuthor(string author) {
        bool found = false;
        for (Book* book : catalog) {
            if (book->author == author) {
                found = true;
                cout << "Название: " << book->title << endl;
                cout << "Автор: " << book->author << endl;
                cout << "Жанр: " << book->genre << endl;
                cout << "Статус: " << (book->reserved ? "Зарезервирована" : "Доступна") << endl;
            }
        }
        if (!found) {
            cout << "Книги автора '" << author << "' не найдены." << endl;
        }
    }

    void searchByGenre(string genre) {
        bool found = false;
        for (Book* book : catalog) {
            if (book->genre == genre) {
                found = true;
                cout << "Название: " << book->title << endl;
                cout << "Автор: " << book->author << endl;
                cout << "Жанр: " << book->genre << endl;
                cout << "Статус: " << (book->reserved ? "Зарезервирована" : "Доступна") << endl;
            }
        }
        if (!found) {
            cout << "Книги в жанре '" << genre << "' не найдены." << endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    Library library;

    library.addBook("Война и мир", "Лев Толстой", "Роман");
    library.addBook("Преступление и наказание", "Фёдор Достоевский", "Роман");
    library.addUser("Иван");
    int choice;
    do {
        cout << "Добро пожаловать в библиотеку '123 и всё готово'" << endl;
        cout << "Меню:" << endl;
        cout << "1. Поиск книги по названию" << endl;
        cout << "2. Поиск книги по автору" << endl;
        cout << "3. Поиск книги по жанру" << endl;
        cout << "4. Добавить новую книгу" << endl;
        cout << "5. Резервирование книги" << endl;
        cout << "6. Просмотр списка зарезервированных книг" << endl;
        cout << "7. Отмена резервации книги" << endl;
        cout << "8. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка: введите число." << endl;
            cin.clear();
            cin.ignore(10000, '\n'); // Используем большое число в качестве аргумента
            continue;
        }


        switch (choice) {
        case 1: {
            string title;
            cout << "Введите название книги: ";
            cin.ignore();
            getline(cin, title);
            cout << endl;
            library.searchByTitle(title);
            cout << endl;
            break;
        }
        case 2: {
            string author;
            cout << "Введите автора книги: ";
            cin.ignore();
            getline(cin, author);
            cout << endl;
            library.searchByAuthor(author);
            cout << endl;
            break;
        }
        case 3: {
            string genre;
            cout << "Введите жанр книги: ";
            cin.ignore();
            getline(cin, genre);
            cout << endl;
            library.searchByGenre(genre);
            cout << endl;
            break;
        }
        case 4: {
            string title, author, genre;
            cout << "Введите название книги: ";
            cin >> title;
            cout << "Введите автора книги: ";
            cin >> author;
            cout << "Введите жанр книги: ";
            cin >> genre;
            cout << endl;
            library.addBook(title, author, genre);
            cout << "Книга успешно добавлена в каталог." << endl << endl;
            break;
        }
        case 5: {
            string title;
            cout << "Введите название книги для резервирования: ";
            cin >> title;
            Book* book = library.findBookByTitle(title);
            if (book == nullptr) {
                cout << "Книга не найдена." << endl << endl;
            }
            else {
                library.reserveBook(library.users.front(), book);
                cout << endl;
            }
            break;
        }
        case 6: {
            User* user = library.users.front();
            cout << "Список зарезервированных книг для пользователя " << user->username << ":" << endl;
            for (Book* book : user->reservedBooks) {
                cout << "Название: " << book->title << endl;
                cout << "Автор: " << book->author << endl;
                cout << "Жанр: " << book->genre << endl << endl;
            }
            break;
        }
        case 7: {
            string title;
            cout << "Введите название книги для отмены резервации: ";
            cin >> title;
            Book* book = library.findBookByTitle(title);
            if (book == nullptr) {
                cout << "Книга не найдена." << endl << endl;
            }
            else {
                library.cancelReservation(library.users.front(), book);
                cout << endl;
            }
            break;
        }
        case 8:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неверный ввод. Попробуйте снова." << endl << endl;
        }
    } while (choice != 8);




    return 0;
}