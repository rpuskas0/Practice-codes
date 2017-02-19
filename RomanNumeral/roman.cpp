#include "roman.h"

namespace Roman {
 
/* ====== Roman_lett section begins ======= */

    Roman_lett char_to_num(char& c) {
        switch (c) {
            case 'N':
                return Roman_lett::N;
                break;
            case 'I':
                return Roman_lett::I;
                break;
            case 'V':
                return Roman_lett::V;
                break;
            case 'X':
                return Roman_lett::X;
                break;
            case 'L':
                return Roman_lett::L;
                break;
            case 'C':
                return Roman_lett::C;
                break;
            case 'D':
                return Roman_lett::D;
                break;
            case 'M':
                return Roman_lett::M;
                break;
            default:
                throw Not_rom_lett{};
        }
    }
    
    char num_to_char(Roman_lett& l) {
        switch (l) {
            case Roman_lett::N:
                return 'N';
                break;
            case Roman_lett::I:
                return 'I';
                break;
            case Roman_lett::V:
                return 'V';
                break;
            case Roman_lett::X:
                return 'X';
                break;
            case Roman_lett::L:
                return 'L';
                break;
            case Roman_lett::C:
                return 'C';
                break;
            case Roman_lett::D:
                return 'D';
                break;
            case Roman_lett::M:
                return 'M';
                break;
            default:
                throw Not_rom_lett{};
        }
    }

/* ------ Roman_lett section ends ------ */
    
/* ====== Roman_int section begins ======= */
    
    
    Roman_int::Roman_int(std::string str) {
        try {
            sroman=str;
            ival=numeral();
        } catch (...) {
            std::cerr << "\nInvalid Roman numeral!\n";
        }
    }
    
    Roman_int default_val() {
        static std::string val="N";
        return val;
    }
    
    Roman_int::Roman_int() {
        sroman=default_val().rom_value();
        ival=default_val().int_value();
    }
    

    Roman_lett Roman_int::get_letter() {
        if (lettfull) {lettfull=false; return lettbuff;}
        else {
            char ch;
            ch=sroman[icount];
            ++icount;
            return char_to_num(ch);
        }
    }
      
    Token Roman_int::digit() {
       Token tok;
       Roman_lett lett1=get_letter();
        
       if (lett1==Roman_lett::N) {
           tok.digit.push_back(lett1);
           tok.value=static_cast<int>(lett1);
           return tok;
       }
        
       else {
           tok=evaluate(lett1);
           return tok;
       }
    }
    
    
    int Roman_int::numeral() {
        Token tok=digit();
        vtok.push_back(tok);
        int sum=0;
        sum+=tok.value;
        sum+=numeral();
        return sum;
    }
    
    void Roman_int::putback(Roman_lett& lett) {
        if (lettfull) throw Buffer_full{};
        lettbuff=lett;
        lettfull=true;
    }
    
    
    Token Roman_int::evaluate(Roman_lett& lett1) {
        Token tok;
        int sum=0;
        
        Roman_lett lett2;
        lett2=get_letter();
            
        if (lett1==lett2) {     // Step 1: Check if it is MM?
            Roman_lett lett3;
            lett3=get_letter();
            
            if (lett2==lett3) { // Step 2: Check if it is MMM? If true: M+M+M
                sum+=static_cast<int>(lett1); tok.digit.push_back(lett1);
                sum+=static_cast<int>(lett2); tok.digit.push_back(lett2);
                sum+=static_cast<int>(lett3); tok.digit.push_back(lett3);
            }
            else {              // If Step 2 false (S1 is true): M+M
                putback(lett3); // Return unused character
                sum+=static_cast<int>(lett1); tok.digit.push_back(lett1);
                sum+=static_cast<int>(lett2); tok.digit.push_back(lett2);
            }
        }
        else if (lett1<lett2) { // Step 3 (S1 is false): check if it is CM? If true: M-C
            if (valid_sub(lett1, lett2)) { // check for valid subtraction
                sum-=static_cast<int>(lett1); tok.digit.push_back(lett1);
                sum+=static_cast<int>(lett2); tok.digit.push_back(lett2);
            }
            else {throw Invalid_format{};}
        }
        else {                  // Step 4 (S1 && S3 are false): It is M, thus return M
            putback(lett2);
            sum+=static_cast<int>(lett1); tok.digit.push_back(lett1);
        }
        
        tok.value=sum;
        return tok;
    }
    
    
    bool Roman_int::valid_sub(Roman_lett& lett1, Roman_lett& lett2) {
        int num1=static_cast<int>(lett1);
        int num2=static_cast<int>(lett2);
        if (num1<(num2/10)) {return false;} // Cannot subtract values more than 10x smaller
        else if (lett1==Roman_lett::D || lett1==Roman_lett::L) {return false;} // D && L are not subtractable values
        else {return true;}
    }
    
    
    
    // operator overloads for Roman_int:
    std::istream& operator>>(std::istream& is, Roman_int& ri) {
        std::string str;
        is >> str;
        ri=Roman_int(str);
        return is;
    }
    std::ostream& operator<<(std::ostream& os, const Roman_int& ri) {
        std::string str=ri.rom_value();
        os << str;
        return os;
    }
    
/* ------ Roman_int section ends ------ */
    
} // End of namespace Roman
