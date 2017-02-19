# include "Ch9-Librarian-Library.h"

namespace Library {
    
/* ====== Patron section begins ====== */


    Patron::Patron(std::string usrname, int cardnum, int fees)
        :susrname{usrname}, icardnum{cardnum}, ifees{fees} 
    {
        try {
        } catch (Bad_fee) {
            std::cerr << "Negative fees are not permitted!";
        } catch (...) {
            std::cerr << "Patron: Unknown exception!";
        }
    }
    
    Patron default_patron() {
        std::string defusr {"Unknown Patron"};
        int defcardnum {0};
        int deffees {0};
        Patron default_patron {defusr, defcardnum, deffees};
        return default_patron;
    }
    
    Patron::Patron() {
        susrname=default_patron().user();
        icardnum=default_patron().cardnum();
        ifees=default_patron().fees();
    }

    // modifying functions of Patron:
    void Patron::set_fee (int x) {
        ifees=x;
        if (ifees<0) {throw Bad_fee{};}
    }
    
// [SUB] operator overloads of Patron:
    std::ostream& operator<<(std::ostream& os, const Patron& ptr) {
        os << ptr.user() << std::endl
            << ptr.cardnum() << std::endl
            << ptr.fees() << std::endl;
        return os;
    }
    

/* ------ Patron section ends ------ */

/* ====== Library section begins ====== */

    // non-modifying functions of Library:    
    bool Library::is_member(Patron& ptrn) {
        for (Patron x : vpatron) {
            if (x.cardnum()==ptrn.cardnum() && x.user()==ptrn.user()) {return true;}
            else {return false;}
        }
    }

    // modifying functions of Library:
    void Library::add_book(Books::Book bk) {
        vbook.push_back(bk);
    }
    
    void Library::add_patron(Patron ptrn) {
        vpatron.push_back(ptrn);
    }
    
    void Library::chkout_book(Books::Book& bk, Patron& ptrn, Chrono::Date& date) {
        if (bk.is_checkout()==true) {throw Chkd_out{};}
        else if (is_member(ptrn)==false) {throw Not_member{};}
        else if (ptrn.has_fees()==true) {throw Has_fees{};}
        else {
            Transaction new_trnsct;
            new_trnsct.book=bk;
            new_trnsct.patron=ptrn;
            new_trnsct.date=date;
            
            vtransaction.push_back(new_trnsct);
            bk.switch_chkout();
        }
    }

// [SUB] operator overloads of Library:
        std::ostream& operator<<(std::ostream& os, const Library& libr) {
            for (Books::Book x : libr.book_list()) {
                os << "Book list:\n" << x << std::endl;
            }
            for (Patron x : libr.patron_list()) {
                os << "Patron list:\n" << x << std::endl;
            }
            for (Transaction x : libr.trans_list()) {
                os << "Transactions:\n"
                    << x.book << ", " << x.patron << ", " << x.date << std::endl;
            }
            return os;
        }

/* ------ Library section ends ------ */


} // end of namespace Library
