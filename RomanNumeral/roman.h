#ifndef ROMAN_H
#define ROMAN_H

#include<iostream>
#include<string>
#include<vector>

namespace Roman {
    
/* ====== Roman_lett section begins ======= */

    // An enum class to define Roman letters and associated values:
    enum class Roman_lett: int {N=0, I=1, V=5, X=10, L=50, C=100, D=500, M=1000}; 
    
    // Helper functions for Roman_lett:
    Roman_lett char_to_num(char& c);    // convert chars to Roman_lett
    char num_to_char(Roman_lett& l);            
    
    // Exception class(es) for Roman_lett
    class Not_rom_lett{};
    class Invalid_format{};
 
/* ------ Roman_lett section ends ------ */
    
/* ====== Roman_int section begins ======= */
    
    struct Token {
        std::vector<Roman_lett> digit;
        int value;
    };

    // a class to store roman "digits"
    class Roman_int {
    public:    
        Roman_int(std::string str);
        Roman_int();
        
        class Buffer_full{};
        
        std::string rom_value() const {return sroman;}
        int int_value() const {return ival;}
    private:
        std::string sroman;
        std::vector<Token> vtok;
        int ival=0;
        
        int icount=0;
        Roman_lett lettbuff;
        bool lettfull;
        
        Roman_lett get_letter();
        Token digit();
        int numeral();
        void putback(Roman_lett& tok);
        Token evaluate(Roman_lett& lett1);
        bool valid_sub(Roman_lett& lett1, Roman_lett& lett2);
    };
    
    
    // operator overloads for Roman_int:
    std::istream& operator>>(std::istream& is, Roman_int& ri);
    std::ostream& operator<<(std::ostream& os, const Roman_int& ri);
    
    
/* ------ Roman_int section ends ------ */


} // End of namespace Roman
#endif
