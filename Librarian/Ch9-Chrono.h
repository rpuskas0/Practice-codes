#include "Ch9-Librarian.h"

#ifndef CHRONO_H
#define CHRONO_H

/* IMPORTANT INFORMATION: The contents of the Chrono namespace are heavily based on B. Stroustrup's code found in "Programming: Principles and Practice Using C++". All modifications or additions are my work though. */

namespace Chrono {

/* ====== Calendar specific constant definitions begins ====== */


	enum class Month: int { // the ": int" part lets to manually set the underlying type
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
       
/* ------ Calendar specific constant definitions ends ------ */

/* ====== Date class definition begins ====== */
    

class Date {
	public:
		class Invalid_day{};
        class Invalid_month{};
        class Bad_month{};
        class No_subtract{};
		
		Date(int y, Month m, int d);
		Date();
		
		//nonmodifying functions:
		int day() const {return iday;}
		Month month() const {return mmonth;}
		int year() const {return iyear;}
		
		//modifying functions:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
        int iyear;
        Month mmonth;
        int iday;
};

// [SUB] Helper functions of Date:

void is_date(int y, Month m, int d); // check date validity
bool leapyear(int y);	// true if iyear is a leap year
Month int_to_month(int x);

// [SUB] Operator overloads of Date:

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

std::ostream& operator<<(std::ostream& os, const Date& d);

std::istream& operator>>(std::istream& is, Date& dd);


/* ------ Date class definition ends ------ */

} // end of namespace Chrono

#endif
