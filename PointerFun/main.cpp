#include <iostream>

/*
 * This function converts all characters to lower case in 
 * the provided array of char.
 */
void to_lower(char* s) {
    int i=0;
    while (true) {
        if (s[i]!='\0') {
            s[i]=tolower(s[i]);
            ++i;
        }
        else break;
    }
}

/*
 * This function duplicates an array of char
 */
char* strdup(const char* s, int strlen) {
    char* cptr = new char[strlen];
    int i=0;
    while (true) {
        if (s[i]!='\0') {
            cptr[i]=s[i];
            ++i;
        }
        else break;
        if (i==strlen) {cptr[i]='\0'; break;}
    }
    return cptr;
}

/*
 * This function counts the length of an array
 */
int cntarrlen(const char* x) {
    int xlen=0;
    while (true) {
        if (x[xlen]!='\0') {++xlen;}
        else break;
    }
    return xlen;
}

/*  
 * This function finds x in s and returns the address of
 * the first character of the first true match (aka.
 * the entirety of x needs to match, not just a character)
 * found in s. If no match is found, a nullptr is returned.
 */
const char* findx(const char* s, const char* x) {
    int i=0;
    int j=0;
    int xlen=0;
    int simlen=0;
    int xstart=0;
    const char* cstart=nullptr;
    
    // count x length:
    xlen=cntarrlen(x);
   
    // compare s with x:
    while (true) {
        // find first match from x in s:
        if (s[i]!=x[j]) {++i;}
        // if first similar charater found:
        else if(s[i]==x[j]) {
            //check if the entire x is in s or just a single char was similar
            while (true) {
                if (s[i]==x[j]) {++simlen; ++i; ++j;}
                else {simlen=0; j=0; break;}
                if(simlen==xlen) {xstart=i-simlen; cstart=&s[xstart]; break;}
            }
        }
        // exit loop if end of s is reached:
        if (s[i]=='\0') break;
    }
    
    return cstart;
}

/*
 * This function collects and stores all user input into a single char array.
 * An ! mark terminates data collection and returns a pointer to the array.
 * Note: Memory deallocation is deliberately not dealt with this time.
 */

char* istoarr(std::istream& is) {
    char* carray = new char;
    char* termchar = new char {'!'};
    
    while (true) {
        char* addarr = new char;
        is >> addarr;
        const char* isterm = findx(addarr,termchar);
        
        if (isterm==nullptr) {
            int carraylen=cntarrlen(carray);
            int addarrlen=cntarrlen(addarr);
            
            char* tmparr= new char[carraylen+addarrlen+1];
            
            for (int i=0; i<=carraylen; ++i) {
                tmparr[i]=carray[i];
            }
            for (int i=0; i<=addarrlen; ++i) {
                tmparr[carraylen+i]=addarr[i];
            }
            
            carray=tmparr;
        }
        else break;
    }
    return carray;
}


/*
 * Same function as istoarr, but implemented with std::string instead.
 * It is much simpler, isn't it? Additionally, memory management is
 * automatic, which makes life even simpler (an more efficient).
 */
std::string istostr(std::istream& is) {
    std::string outstr;
    char termchar {'!'};
    
    while (true) {
        std::string addstr;
        std::cin >> addstr;
        int isterm=addstr.find(termchar);
        
        if (isterm<0) {outstr+=addstr;}
        else break;
    }
    return outstr;
}



int main() {
// tolower test:
    std::cout << "--== tolower() test: ==--" << std::endl;
    char cstr[] = "Hello World!";
    char* cptr=&cstr[0];
    
    std::cout << cstr << std::endl;
    
    std::cout << "converting to lower case..." << std::endl;
    to_lower(cptr);
    
    std::cout << cstr << std::endl << std::endl;
    
    
// strdup test:
    std::cout << "--== strdup() test: ==--" << std::endl;
    int newstrlen=10;
    char carray[] {"Test_String Yeah"};
    
    std::cout << "Original string: " << carray << std::endl;
    
    std::cout << "Copying c-string into new c-string with max size of " << newstrlen << " chars." << std::endl;
    char* cptr2=strdup(carray,newstrlen);
    
    std::cout << "Copied c-string: " << cptr2 << std::endl << std::endl;

    
// findx test:
    std::cout << "--== findx() test: ==--" << std::endl;
    char xarray[] {"_Str"};
    char* cptr3=&carray[0];
    char* cptrx=&xarray[0];
    
    const char* simptr=findx(cptr3, cptrx);
    
    std::cout << "Find this: " << xarray << std::endl;
    std::cout << "In this array: " << cptr3 << std::endl;
    
    if (simptr==nullptr) {std::cout << "There was no match!";}
    else {std::cout << "Starting from true match: " << simptr;}
    
    std::cout << std::endl;
 
    
// istoarr test:
    std::cout << "Please provide strings to store in array. A ! mark will terminate input." << std::endl;
    char* isarr=istoarr(std::cin);
    
    std::cout << "Stored string is: " << isarr << std::endl;
    
    
// istoarr to be done with std::string instead of arrays
    std::cout << "Please provide strings to store in std::string. A ! mark will terminate input." << std::endl;
    std::string str1=istostr(std::cin);
    
    std::cout << "Stored string is: " << str1 << std::endl;
}
