#include <iostream>

/*
 * In these following few example functions I play around with
 * pointers by using both subscrpiting and pointer arithcmetic.
 * Some additional functions using STL facilites are also provided
 * to demonstrate the difference between implementation difficulty.
 * 
 * Note: As 'new' is constantly used outside class constructors/destructors
 * (which in most cases is not recommended at all), memory deallocation
 * is deliberately not dealt with this time.
 * A lot of this code WILL leak memory, so don't use it in production software!
 */


//---------------------------------------------------------------

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

//---------------------------------------------------------------

/*
 * This function counts the length of an array using SUBSCRIPTING.
 */

int cntarrlen(const char* x) {
    int xlen=0;
    while (true) {
        if (x[xlen]!='\0') {++xlen;}
        else break;
    }
    return xlen;
}

//---------------------------------------------------------------

/*
 * This function counts the length of an array using POINTER ARITHMETIC.
 */

int cntarrlen2(const char* carr) {
    int len=0;
    while(*carr) {++len; ++carr;};
    return len;
}

//---------------------------------------------------------------

/*
 * This function duplicates an array of char using SUBSCRIPTING.
 * It also allows to copy (and truncate) an array into a smaller one.
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

//---------------------------------------------------------------

/*
 * This function duplicates an array of char using POINTER ARITHMETIC.
 * This one does not allow truncation and copying into smaller arrays.
 */

char* strdup2(const char* carr) {
    char* p = new char[cntarrlen2(carr)];
    char* origp=p;                          // saving the beginning of the new array
    while (*carr) {*p=*carr; ++carr; ++p;}; // p is now at the end of the array!
    return origp;                           // so we return origp instead of p
}

//---------------------------------------------------------------

/*
 * This function concatenates two C-style strings with a dot character
 * as a separator using POINTER ARITHMETIC.
 */
char* pcat_dot(const char* s1, const char* s2) {
    const char divider {'.'};
    int arrlen=2;
    arrlen+=cntarrlen(s1);
    arrlen+=cntarrlen(s2);
    
    char* p = new char[arrlen];
    char* origp=p;
    while(*s1) {*p=*s1; ++p; ++s1;}
    *p=divider; ++p;
    while(*s2) {*p=*s2; ++p; ++s2;}
    
    return origp;
}

//---------------------------------------------------------------

/*
 * This function also concatenates two strings, but it is implemented
 * with std::string instead. It is here to demonstrate the difference
 * in implementation difficulty between the two.
 */
std::string cat_dot(const std::string& s1, const std::string& s2) {
    const char divider {'.'};
    std::string concstr=s1;
    concstr.push_back(divider);
    concstr+=s2;
    return concstr;
}

//---------------------------------------------------------------

/*
 * This function does also concatenates two C-style strings, but this
 * time we can choose the divider ourselves through a 3rd string.
 * Also uses POINTER ARITHMETIC.
 */

char* pcat_str(const char* s1, const char* s2, const char* div) {
    int arrlen=1;
    arrlen+=cntarrlen(s1);
    arrlen+=cntarrlen(s2);
    arrlen+=cntarrlen(div);
    
    char* p = new char[arrlen];
    char* origp=p;
    while(*s1) {*p=*s1; ++p; ++s1;}
    while(*div) {*p=*div; ++p; ++div;}
    while(*s2) {*p=*s2; ++p; ++s2;}
    
    return origp;
}

//---------------------------------------------------------------

/*
 * This function also concatenates two strings, but it is implemented
 * with std::string instead, and also allows a 3rd string to be used
 * as user defined divider. Also uses POINTER ARITHMETIC.
 * Note: Notice how this one looks the most simple of all four "concatenators".
 */

std::string cat_str(const std::string& s1, const std::string& s2, const std::string& div) {
    std::string concstr=s1;
    concstr+=div;
    concstr+=s2;
    return concstr;
}

//---------------------------------------------------------------

/*  
 * This function finds x in s and returns the address of
 * the first character of the first true match (aka.
 * the entirety of x needs to match, not just one character)
 * found in s. If no match is found, a nullptr is returned.
 */

const char* findx(const char* s, const char* x) {
    int i=0;
    int j=0;
    int xlen=0;
    int simlen=0;
    int xstart=0;
    const char* cstart=nullptr;
    
    xlen=cntarrlen(x);                  // count x length:
   
    while (true) {                      // compare s with x:
        if (s[i]!=x[j]) {++i;}          // find first match from x in s, then
        else if(s[i]==x[j]) {           // if first similar charater is found,
            while (true) {              // check if the entirety of x is in s or just a single char was similar
                if (s[i]==x[j]) {++simlen; ++i; ++j;}   // iterating through both arrays...
                else {simlen=0; j=0; break;}            // if mismatch found, set array x back to start position
                if(simlen==xlen) {xstart=i-simlen; cstart=&s[xstart]; break;}   // set start position of true match to a pointer
            }
        }
        if (s[i]=='\0') break;          // exit loop if end of s is reached
    }
    
    return cstart;
}

//---------------------------------------------------------------

/*
 * This funtion compares s1 and s2 lexicographically.
 * If they are equal, the function returns 0,
 * if s1 comes before s2, the function returns -1,
 * if s1 comes after s2, the function returns 1.
 * A shorter, but up to that point identical string
 * is considered to lexicographically come first.
 */

int strcmp(const char* s1, const char* s2) {
    int retval=0;
        
    while (*s1 || *s2) {                    // checking letters
        if (*s1==*s2) {++s1; ++s2;}
        else if (*s1<*s2) {retval=-1; break;}
        else if (*s1>*s2) {retval=1; break;}
    }
    
    if (!retval) {                          // checking string length of (so far) identical strings
        if (!*s1 && *s2) {return retval=-1;}
        else if (*s1 && !*s2) {return retval=1;}
        else return retval;
    }
    else return retval;
}

//---------------------------------------------------------------

/*
 * This function collects and stores all user input into a single char array.
 * An ! mark terminates data collection and returns a pointer to the array.
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

//---------------------------------------------------------------

/*
 * Same function as istoarr, but implemented with std::string instead.
 * It is much simpler, isn't it? Additionally, note that memory management is
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

//---------------------------------------------------------------
//---------------------------------------------------------------

int main() {
// tolower() test:
    std::cout << "--== tolower() test: ==--" << std::endl;
    char cstr[] = "Hello World!";
    char* cptr=&cstr[0];
    
    std::cout << cstr << std::endl;
    
    std::cout << "converting to lower case..." << std::endl;
    to_lower(cptr);
    
    std::cout << cstr << std::endl << std::endl;
    
    
// strdup() test:
    std::cout << "--== strdup() test: ==--" << std::endl;
    int newstrlen=10;
    char carray[] {"Test_String Yeah"};
    
    std::cout << "Original string: " << carray << std::endl;
    
    std::cout << "Copying c-string into new c-string with max size of " << newstrlen << " chars." << std::endl;
    char* cptr2=strdup(carray,newstrlen);
    
    std::cout << "Copied c-string: " << cptr2 << std::endl << std::endl;

    
// findx() test:
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
 
    
// istoarr() test:
    std::cout << "Please provide strings to store in array. A ! mark will terminate input." << std::endl;
    char* isarr=istoarr(std::cin);
    
    std::cout << "Stored string is: " << isarr << std::endl;
    
    
// istoarr() to be done with std::string instead of arrays
    std::cout << "Please provide strings to store in std::string. A ! mark will terminate input." << std::endl;
    std::string str1=istostr(std::cin);
    
    std::cout << "Stored string is: " << str1 << std::endl;

    
// strcmp() test:    
    const char carr1[] {"ApPs"};
    const char carr2[] {"App"};
    int lexi=strcmp(carr1,carr2);
    
    if (lexi<0) std::cout << "carr1 comes before carr2" << std::endl;
    else if (lexi>0) std::cout << "carr1 comes after carr2" << std::endl;
    else std::cout << "carr1 and carr2 are equal" << std::endl;


// pcat_dot() and pcat_str() test:
    char cs1[] {"Nicola"};
    char cs2[] {"Tesla"};
    char cdiv1[] {" . "};
    char* comb=pcat_dot(cs1,cs2);
    char* comb2=pcat_str(cs1,cs2,cdiv1);
    
    std::cout << comb << std::endl;
    std::cout << comb2 << std::endl;
}
