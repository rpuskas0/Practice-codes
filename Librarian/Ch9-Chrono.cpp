#include "Ch9-Chrono.h"

namespace Chrono {

// [SUB] Main functions of Date:
	Date::Date(int yy, Month mm, int dd)
		: iyear{yy}, mmonth{mm}, iday{dd}
	{
		try {
            is_date(yy,mm,dd);
        } catch (Invalid_day) {
            std::cerr << "Invalid day is provided!";
        } catch (Invalid_month) {
            std::cerr << "Invalid month is provided!";
        } catch (Bad_month) {
            std::cerr << "Invalid month is detected!";
        } catch (...) {
            std::cerr << "Invalid date or operation!\n";
        }
	} 
	
	const Date& default_date() {
		static Date dd {1900,Month::jan,1};
		return dd;
	}
	
	Date::Date()
		:iyear{default_date().year()},
		mmonth{default_date().month()},
		iday{default_date().day()}
	{}
	
	// modifying functions of Date:
	
	void Date::add_day(int n) {
        if (n<0) {throw Date::No_subtract{};}
        int nn=abs(n);
        int day=iday;
        for (int i=0; i<nn; ++i) {
            int month=static_cast<int>(mmonth);
            switch(month) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    ++day;
                    if (day>31) {day=1; add_month(1);}
                    break;
                case 4: case 6: case 9: case 11:
                    ++day;
                    if (day>30) {day=1; add_month(1);}
                    break;
                default: // This handles February
                    ++day;
                    if (leapyear(iyear) && day>29) {day=1; add_month(1);}
                    else if (!leapyear((iyear) && day>28)) {day=1; add_month(1);}
            }
        }
        iday=day;
	}
	
	// adding months safely
	void Date::add_month(int n) {
        if (n<0) {throw Date::No_subtract{};}
        int nn=abs(n);
		int m=static_cast<int>(mmonth);
        int added_years=0;
        for (int i=0; i<nn; ++i) {
            ++m;
            if (m>12) {m=1; ++added_years;}
        }
        mmonth=int_to_month(m);
        add_year(added_years);
	}
	
	// adding years safely
	void Date::add_year(int n) {
        if (n<0) {throw Date::No_subtract{};}
        int nn=abs(n);
        // this will advance the calendar day to march 1. if we stepped from a leap year to a not leap year
		if (mmonth==Month::feb && iday==29 && !leapyear(iyear+nn)) {
			mmonth=Month::mar;
			iday=1;
		}
		iyear+=nn;
	}
	
// [SUB] Helper functions of Date:
    
    // checking if date is valid
	void is_date(int y, Month m, int d) {
		if (d<=0) {throw Date::Invalid_day{};}
		if (m<Month::jan || Month::dec<m) {throw Date::Invalid_month{};}
		
		int days_in_month;
		
		switch (m) {
			case Month::feb:
				days_in_month=(leapyear(y))? 29:28;
				break;
            case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				days_in_month=30;
				break;
            default:
                days_in_month=31;
		}
		if (days_in_month<d) {throw Date::Invalid_day{};}
	}
	
	// checking if we have a leap year
	bool leapyear(int y) {
		if (y==1600 || y==2000 || y==2400) {return true;} // these are special leap years
		else if (y%100==0) {return false;} // last year of a century is usually not a leap year
		else if (y%4==0) {return true;} // years divisible by 4 are leap years
		else {return false;}
	}
	
	Month int_to_month (int x) {
        if (x<int(Month::jan) || int(Month::dec)<x) {throw Date::Bad_month{};}
        return Month(x);
    }

	
// [SUB] Operator overloads of Date:

	bool operator==(const Date& a, const Date& b) {
		return a.year()==b.year()
		&& a.month()==b.month()
		&& a.day()==b.day();
	}
	
	bool operator!=(const Date& a, const Date& b) {
		return !(a==b);
	}
	
	std::ostream& operator<<(std::ostream& os, const Date& d) {
		int temp_month = static_cast<int>(d.month()); //static_cast is needed as strongly typed enums cannot be impicintly casted
        os << '(' << d.year();
        os << ',' << temp_month;
        os << ',' << d.day() << ')';
        return os;
	}
	
	std::istream& operator>>(std::istream& is, Date& dd) {
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') {
			is.clear(std::ios_base::failbit);
		return is;
		}
		dd=Date(y,Month(m),d);
		
		return is;
	}

} // end of namespace Chrono
