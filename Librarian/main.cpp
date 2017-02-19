#include "Ch9-Librarian.h"
#include "Ch9-Chrono.h"
#include "Ch9-Librarian-Books.h"
#include "Ch9-Librarian-Library.h"

using namespace std;

/* Main only contains some code to allow me to test the classes #include-d above,
   thus the contents of it can be chenged drastically at any moment. This is dirty,
   uncommented, ugly code here! You were warned! */
int main() {
    
    cout << "Welcome to the test of the library program!\n";
    
    Books::Isbn test;
    string title, author;
    Chrono::Date date;
    Books::Isbn isbn;
    char chkout;
    bool bchkout;
    
    Library::Library new_librar;
    
    Library::Patron testpatron;
    string patname;
    int cardnum;
    
    cout << "Now, we will add a book to the library.\n" ;
    
    Books::Book testbook;
    cout << "Please provide a book title: ";
    cin >> title;
    cout << "\nPlease provide an author: ";
    cin >> author;
    cout << "\nPlease provide a publication date: ";
    cin >> date;
    cout << "\nPlease provide an ISBN number: ";
    cin >> isbn;
    testbook = {title, author, date, isbn, false};
    
    new_librar.add_book(testbook);
    cout << "\nBook added to library\n";
    
    cout << "Please provide a name & card number for new patron:\n";
    
    cin >> patname >> cardnum;
    testpatron = {patname, cardnum, 0};
    new_librar.add_patron(testpatron);
    cout << "Patron added to library\n";
    
    cout << "Listing library database:\n" << new_librar;

    
    return 0;
}
