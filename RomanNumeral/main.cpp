#include "roman.h"

int main() {
    Roman::Roman_int rom;
    std::cout << "Please type a roman numeral: ";
    std::cin >> rom;
    std::cout << std::endl << "Int value of " << rom << " is: " << rom.int_value() << std::endl;
}
