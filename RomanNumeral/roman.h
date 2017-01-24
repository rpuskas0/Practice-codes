#ifndef ROMAN_H
#define ROMAN_H

#include<string>
#include<vector>

namespace Roman {
    // Literal values of Roman numerals:
    enum class Roman_num: int {I=1, V=5, X=10, L=50, C=100, D=500, M=1000};
    // Sequential priority of Roman numerals:
    enum class Roman_seq: int {M=1, D=2, C=3, L=4, X=5, V=6, I=7};

    struct Rom_arab_tok {
        std::string roman;
        int arab;
    };

    class Roman_int {
    public:
        Roman_int(std::string romnum);
        Roman_int();
        
        // return Roman numeral as int:
        int as_int();
    
    private:
        std::vector<Rom_arab_tok> vtok;
    };
    
    // Helper functions for Roman_int:
    bool is_valid_char(); // check if Roman numeral contains characters specified in Roman_num only
    bool is_valid_num(); // check if Roman numeral is in the right format
    Rom_arab_tok decomp_num(std::string romin); // decompose Roman numeral string into tokens
    std::string recomp_num(std::vector<Rom_arab_tok> romout);
    

} // End of namespace Roman
#endif
