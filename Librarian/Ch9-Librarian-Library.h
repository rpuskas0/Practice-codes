#ifndef LIBRAR_LIBRARY_H
#define LIBRAR_LIBRARY_H

#include "Ch9-Librarian.h"
#include "Ch9-Chrono.h"
#include "Ch9-Librarian-Books.h"

namespace Library {
    
/* ====== Patron section begins ====== */


    class Patron {
    public:
        
        class Bad_fee{};
        
        Patron(std::string usrname, int cardnum, int fees);
        Patron();
        
    //non-modifying functions:
        std::string user() const {return susrname;}
        int cardnum() const {return icardnum;}
        int fees() const {return ifees;}
        bool has_fees() {if (ifees==0) {return false;} else {return true;}}
    
    //modifying functions:
        void set_fee(int x);
        
    private:
        std::string susrname;
        int icardnum;
        int ifees;
    };
    
// [SUB] operator overloads of Patron:
    std::ostream& operator<<(std::ostream& os, const Patron& ptr);

    
/* ------ Patron section ends ------ */

/* ====== Library section begins ====== */


    struct Transaction {
        Books::Book book;
        Patron patron;
        Chrono::Date date;
    };


    class Library {
    public:
        
        class Chkd_out{};
        class Has_fees{};
        class Not_member{};
        
        
    // non-modifying functions:
        std::vector<Books::Book> book_list() const {return vbook;}
        std::vector<Patron> patron_list() const {return vpatron;}
        std::vector<Transaction> trans_list() const {return vtransaction;}
        
        bool is_member(Patron& ptrn);
        
    // modifying functions:
        void add_book(Books::Book bk);
        void add_patron(Patron ptrn);
        void chkout_book(Books::Book& bk, Patron& ptrn, Chrono::Date& date);
        void add_transact (Transaction trnsctn);
        
    private:
        std::vector<Books::Book> vbook;
        std::vector<Patron> vpatron;
        std::vector<Transaction> vtransaction;
    };
    
// [SUB] operator overloads of Library:
        std::ostream& operator<<(std::ostream& os, const Library& libr);

/* ------ Library section ends ------ */


} // end of namespace Library

#endif
