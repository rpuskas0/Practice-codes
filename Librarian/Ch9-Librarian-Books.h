#ifndef LIBRAR_BOOK_H
#define LIBRAR_BOOK_H

#include "Ch9-Librarian.h"
#include "Ch9-Chrono.h"

namespace Books {

/* ====== Isbn_tok section begins ====== */


// [SUB] Main functions of Isbn_tok:
    class Isbn_tok {
    public:
        std::string value;
        char chksum; 
        
        // modifying functions:
        void switch_chksum() {
            if (chksum=='y') {chksum='n';}
            else if (chksum=='n') {chksum='y';}
        }
	};

// [SUB] helper functions of Isbn_tok:
    bool tok_valid (char chksum);

    
/* ------ Isbn_tok section ends ------*/
    
/* ====== Isbn section begins ====== */


// [SUB] Main functions of Isbn:    
    class Isbn {
    public:
        class Empty_tok{};
        class Bad_toknum{};
        class Bad_isbnformat{};
        class Bad_conv{};
        class Bad_chksum{};
        class Bad_charnum{};
        
        Isbn(std::string isbn);
        Isbn();
        
        // non-modifying functions of Isbn:
        
        std::string value() const {return sisbn;}
        std::vector<Isbn_tok> tokens() const {return vdecomp;}
        std::vector<int> ints() const {return idecomp;}
              
    private:
        std::string sisbn; // the complete isbn in string format
        std::vector<Isbn_tok> vdecomp;  // isbn stored in separate groups
        std::vector<int> idecomp; // isbn stored as ints
    };
    
    
// [SUB] helper functions of Isbn:
    void decomp_isbn(const std::string& input_str, std::vector<Isbn_tok>& output_vec);
    void tok_to_int(const std::vector<Isbn_tok>& vtok, std::vector<int>& out_vi);
    bool is_convertible(const char& c);
    void isbn_chksum(const std::vector<int>& vi);
    void fill_weight(std::vector<int>& weight);
    std::string rebuild_isbn(const std::vector<Isbn_tok>& tokdecomp);

// [SUB] operator overloads of Isbn:    
    std::ostream& operator<<(std::ostream& os, const Isbn& isbn);
    std::istream& operator>>(std::istream& is, Isbn& isbn);
    bool operator==(const Isbn& xisbn, const Isbn& yisbn);
    bool operator!=(const Isbn& xisbn, const Isbn& yisbn);
    
 
    
/* ------ Isbn section ends ------ */  

/* ====== Book section begins ====== */ 


    class Book {
    public:
        class Invalid {};
        
        Book(std::string title, std::string author, Chrono::Date year, Books::Isbn isbn, bool chkout);
        Book();
        
        // non-modifying operations:
        std::string title() const {return stitle;}
        std::string author() const {return sauthor;}
        Chrono::Date year() const {return dyear;}
        Books::Isbn isbn() const {return iisbn;}
        bool is_checkout() const {return bchkout;}
        
        // modifying operations:
        void switch_chkout();
        
        
    private:
        std::string stitle;
        std::string sauthor;
        Chrono::Date dyear;
        Books::Isbn iisbn;
        bool bchkout;
    };
    
// [SUB] operator overloads of Book:
    std::ostream& operator<<(std::ostream& os, const Book& book);
    std::istream& operator>>(std::istream& is, Book& book);
    bool operator==(const Book& xbook, const Book& ybook);
    bool operator!=(const Book& xbook, const Book& ybook);

    
/* ------ Book section ends ------ */
    
} // end of namespace Books

#endif
