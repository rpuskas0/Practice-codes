#include "Ch9-Librarian-Books.h"

namespace Books {
    
/* ====== Isbn_tok section begins ====== */


// [SUB] helper functions of Isbn_tok:
    bool tok_valid (char chksum) {
        if (chksum!='y' || chksum!='n') {return false;}
        else {return true;}
    }
    
    
/* ------ Isbn_tok section ends ------*/
    
/* ====== Isbn section begins ====== */


// [SUB] Main functions of Isbn:
    Isbn::Isbn(std::string isbn) {
        try {
            sisbn=isbn;
            decomp_isbn(sisbn, vdecomp);
            tok_to_int(vdecomp, idecomp);
            isbn_chksum(idecomp);
        } catch(Empty_tok) {
            std::cerr << "Invalid ISBN: Empty group found!\n";
        } catch (Bad_toknum) {
            std::cerr << "Invalid ISBN: Invalid number of groups found!\n";
        } catch (Bad_isbnformat) {
            std::cerr << "Invalid ISBN: Invalid formatting found!\n";
        } catch (Bad_conv) {
            std::cerr << "Invalid ISBN: Invalid characters found!\n";
        } catch (Bad_chksum) {
            std::cerr << "Invalid ISBN: Bad checksum!\n";
        } catch (Bad_charnum) {
            std::cerr << "Invalid ISBN: Invalid number of characters found!\n";
        } catch (...) {
            std::cerr << "Invalid ISBN!\n";
        }
    }
    
    const Isbn default_isbn() {
        static std::string isbn {"0-000-00000-0"};
        return isbn;
    }
    
    
    Isbn::Isbn() {
        sisbn=default_isbn().value();
        decomp_isbn(sisbn, vdecomp);
        tok_to_int(vdecomp, idecomp);
    }
    
// [SUB] helper functions of Isbn:
    
    // decompose string into tokens
    void decomp_isbn(const std::string& input_str, std::vector<Isbn_tok>& output_vec) {
        
        const char delim='-';
        std::string token;
        std::stringstream ss;
        
        ss.str(input_str);
        while (std::getline(ss, token, delim)) {
            if (!token.empty()) {
                Isbn_tok tv{token, 'n'};
                output_vec.push_back(tv);
            }
            if (token.empty()) {throw Isbn::Empty_tok{};}
        }
        output_vec.back().switch_chksum(); // last element is always a checksum token
        
        if (output_vec.size()==4 || output_vec.size()==5) {}
        else {throw Isbn::Bad_toknum{};}
        
     }
     
    // turn vector of tokens into vector of int
    void tok_to_int(const std::vector<Isbn_tok>& vtok, std::vector<int>& out_vi) {
		for (int i=0; i<vtok.size(); ++i) {       // select one token of vector
            for (int j=0; j<vtok[i].value.size(); ++j) {  // select one character of token
                char c=vtok[i].value[j];
                int a;
                if (vtok[i].chksum=='n' && is_convertible(c)) {
                    a=atoi(&c);
                    out_vi.push_back(a);
                }
                else if (vtok[i].chksum=='y' && is_convertible(c)) {
                    a=atoi(&c);
                    out_vi.push_back(a);
                }
                else if (vtok[i].chksum=='y' && c=='x') {// an 'x' in a 10 digit isbn checksum token equals to 10 per definition
                    a=10;
                    out_vi.push_back(a);
                }
                else {throw Isbn::Bad_conv{};}
            }
        }
        
        if (vtok.size()==4 && out_vi.size()==10) {}
        else if (vtok.size()==5 && out_vi.size()==13) {}
        else {throw Isbn::Bad_isbnformat{};}
        
    }
    // check if strings contain numbers only
    bool is_convertible (const char& c) {
        const std::vector<char> check = {'0','1','2','3','4','5','6','7','8','9'};
        for (int i=0; i<check.size(); ++i) {
            if (check[i]==c) {return true;}
        }
        return false;
    }
    
    // calculate checksum of isbn number
    void isbn_chksum(const std::vector<int>& vi) {
        std::vector<int> weight(vi.size());
        int sum=0;
        int char_num=vi.size();
        const int count=char_num-1; // if char_num==13: last digit should not be included into calculation per definition
        switch (char_num) {
            case 10:
                fill_weight(weight);
                for (int i=0; i<char_num; ++i) {
                    sum+=weight[i]*vi[i];
                }
// [DIAG]       std::cout << std::endl << "chksum" << sum << std::endl;                
                if (sum%11!=0) {throw Isbn::Bad_chksum{};}  // as defined by isbn
                break;
            case 13:
                fill_weight(weight);
                for (int i=0; i<count; ++i) {
                    sum+=weight[i]*vi[i];
                }
// [DIAG]       std::cout << std::endl << "10-chksum" << 10-(sum%10) << " sum " << sum << std::endl;
                if (10-(sum%10)!=vi.back()) {throw Isbn::Bad_chksum{};}
                break;
            default:
                throw Isbn::Bad_charnum{};
                break;
        }
    }
    // fills a vector with the proper weight for chksum calculation
    void fill_weight(std::vector<int>& weight) {
        if (weight.size()==10) {
            int vsize=weight.size();
            for (int i=vsize; i>0; --i) {weight[vsize-i]=i;}  // as defined for 10 char isbn
        }
        if (weight.size()==13) {
            int vsize=weight.size();
            for (int i=0; i<vsize; ++i) {   // as defined for 13 char isbn
                if (i%2!=0) {weight[i]=3;}
                else {weight[i]=1;}
            }
        }
    }
    
    // rebuilds the isbn number into a string
    std::string rebuild_isbn(const std::vector<Isbn_tok>& tokdecomp) {
       std::string assembled;
       std::stringstream ss;
       for (int i=0; i<tokdecomp.size(); ++i) {
           if (i!=(tokdecomp.size()-1)) {
               ss << tokdecomp[i].value << '-';
           }
           else if (i==(tokdecomp.size()-1)) {
               ss << tokdecomp[i].value;
           }
       }
       ss >> assembled;
       return assembled;
    }
    
// [SUB] operator overloads of Isbn:
    std::ostream& operator<<(std::ostream& os, const Isbn isbn) {
        return os << isbn.value();
    }
    
    std::istream& operator>>(std::istream& is, Isbn& isbn) {
        std::string s;
        is >> s;
        isbn=Isbn(s);
        return is;
    }
    
    bool operator==(const Isbn& xisbn, const Isbn& yisbn) {
        return xisbn.value()==yisbn.value();
    }
    
    bool operator!=(const Isbn& xisbn, const Isbn& yisbn) {
        return !(xisbn==yisbn);
    }


/* ------ Isbn section ends ------ */
    
/* ====== Book section begins ====== */


    Book::Book(std::string title, std::string author, Chrono::Date year, Books::Isbn isbn, bool chkout)
        :stitle{title}, sauthor{author}, dyear{year}, iisbn{isbn}, bchkout{chkout}
    {
    }
    
    const Book& default_book() {
        Chrono::Date defdate {1900,Chrono::Month::jan,1};
        Isbn defisbn {"0-000-00000-0"};
        bool defchkout {false};
        static Book defbook {"Unknown Title","Unkown Author", defdate, defisbn, defchkout};
        return defbook;
    }
    
    Book::Book()
        :stitle {default_book().title()},
        sauthor {default_book().author()},
        dyear {default_book().year()},
        iisbn {default_book().isbn()},
        bchkout {default_book().is_checkout()}
    {
    }

    void Book::switch_chkout() {
        if (bchkout==false) {bchkout=true;}
        else if (bchkout==true) {bchkout=false;}
    }
    
// [SUB] operator overloads of Book:
    
    std::ostream& operator<<(std::ostream& os, const Book& book) {          
        os << book.title() << std::endl
        << book.author() << std::endl
        << book.year() << std::endl
        << book.isbn().value() << std::endl
        << book.is_checkout() << std::endl;
        return os;
    }
    
    std::istream& operator>>(std::istream& is, Book& book) {
        std::string title, author;
        Chrono::Date year;
        Isbn isbn;
        bool chkout;
        is >> title >> author >> year >> isbn >> chkout;
        book=Book(title, author, year, isbn, chkout);
        return is;
    }
    
    bool operator==(const Book& xbook, const Book& ybook) {
        return xbook.title()==ybook.title()
        && xbook.author()==ybook.author()
        && xbook.year()==ybook.year()
        && xbook.isbn()==ybook.isbn()
        && xbook.is_checkout()==ybook.is_checkout();
    }
    
    bool operator!=(const Book& xbook, const Book& ybook) {
        return !(xbook==ybook);
    }
  
    
/* ------ Book section ends ------ */    

} // end of namespace Books

