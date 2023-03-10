#include <iostream>
#include "Bus.h"
using namespace std;
using namespace sdds;

namespace sdds {

	Bus::Bus(int noOfSeats, int noOfPassengers) : m_noOfSeats(noOfSeats), m_noOfPassengers(noOfPassengers) {       //The constructor initializes the member variables with the values passed as arguments
	if (((noOfSeats % 2) != 0) || noOfSeats < 10 || noOfSeats > 40 || noOfPassengers < 0 || noOfPassengers > noOfSeats) {
		setOutOfService();
	}
}

	void Bus::setOutOfService() {       //  sets the number of seats and passengers to zero, indicating that the bus is out of service.
    m_noOfSeats = 0;
    m_noOfPassengers = 0;

}


	ostream& Bus::display(std::ostream& ostr) const {   // displays the bus information
	if (*this) {
		drawBus(m_noOfSeats, m_noOfPassengers, ostr);
		ostr.setf(ios::fixed);
		ostr.precision(2);
		ostr << "Total Fare Price: " << double(*this) << endl;
		ostr.unsetf(ios::fixed);
	} else {
		ostr << "Out of service!" << endl;
	}
	return ostr;
}



void Bus::drawBus(int seats, int noOfPassengers, ostream& ostr) const {    // draws the ASCII art representation of the bus.
  int i, p;
  ostr.fill('_');
  ostr.width((seats / 2) * 3 + 4);
  ostr << "_";
  ostr << endl << "| ";
  for (i = 0, p = -1; i < (seats / 2); i++, ostr << "[" << ((p += 2) < noOfPassengers ? '2' : ((p == noOfPassengers) ? '1' : ' ')) << "]");
  ostr << "|_\\_" << endl;
  ostr << "| ";
  ostr.fill(' ');
  ostr.width(((seats / 2) * 3 - 14) / 2);
  ostr << " " << "Seneca College";
  ostr.width(((seats / 2) * 3 - 14) / 2 + (seats % 4 != 0));
  ostr << " " << "    )" << endl;
  ostr << "`---OO";
  ostr.fill('-');
  ostr.width((seats / 2) * 3 - 5);
  ostr << "-" << "O---'" << endl;
}


istream& Bus::read(std::istream& istr) {    //reads the bus information from the input stream and validates it.
    int seatNum;
    int passengerNum;
    bool success = true;

    istr >> seatNum;
    istr.ignore();
    istr >> passengerNum;

    if (seatNum % 2 == 0 && seatNum >= 10 && seatNum <= 40 && passengerNum >= 0 && passengerNum <= seatNum) {
        m_noOfSeats = seatNum;
        m_noOfPassengers = passengerNum;
    }
    else {
        success = false;
    }

    if (!success) {
        setOutOfService();
    }

    return istr;
}





Bus::operator bool() const {    //returns true if the bus is in service,
	return m_noOfSeats > 0;
}

Bus::operator int() const {                 //returns the number of passengers in the bus if the bus is in service
	return (*this) ? m_noOfPassengers : -1;  
}

Bus::operator double() const {                      //returns the fare price of the bus if the bus is in service
	return (*this) ? m_noOfPassengers * BusTicketPrice : -1.0;
}



	bool Bus::operator--(int) {
	if (m_noOfSeats <= 0 || m_noOfPassengers <= 0) {
		return false;
	}
	Bus temp = *this;
	--(*this);
	return temp;
}
                 
bool Bus::operator++(int) {                    //returns the old value of the bus object.
	if (m_noOfSeats <= 0 || m_noOfPassengers >= m_noOfSeats) {
		return false;
	}
	Bus temp = *this;
	++(*this);
	return temp;
}

bool Bus::operator--() {                  //decrement the number of passengers by 1 if the bus is in service and the number of passengers is greater than 0.
	if (m_noOfSeats <= 0 || m_noOfPassengers <= 0) {
		return false;
	}
	--m_noOfPassengers;
	return true;
}

bool Bus::operator++() {            // increment the number of passengers by 1 if the bus is in service and the number of passengers is less than the number of seats. 
	if (m_noOfSeats <= 0 || m_noOfPassengers >= m_noOfSeats) {
		return false;
	}
	++m_noOfPassengers;
	return true;
}



	Bus& Bus::operator=(int value) {             //sets the number of passengers to the value passed as an argument if it is greater than or equal to 0 and less than or equal to the number of seats
		if (value < 0) {
			value = 0;
		} else if (value > m_noOfSeats) {
			value = m_noOfSeats;
			setOutOfService();
		}
		m_noOfPassengers = value;
		return *this;
	}

Bus& Bus::operator+=(int value) {     //an overload that adds the number of passengers of the other bus to the current bus
	if (m_noOfSeats > 0 && m_noOfPassengers + value <= m_noOfSeats) {
		m_noOfPassengers += value;
	}
	else {
		// Adjust the number of passengers to fill up the bus
		m_noOfPassengers = m_noOfSeats;
		setOutOfService();
	}
	return *this;
}

	Bus& Bus::operator+=(Bus& other) {
    if (!(*this) || !(other)) {
        return *this;
    }

    int combinedPassengers = m_noOfPassengers + other.m_noOfPassengers;
    if (combinedPassengers > m_noOfSeats) {
        int overflow = combinedPassengers - m_noOfSeats;
        m_noOfPassengers = m_noOfSeats;
        other.m_noOfPassengers = overflow;
    } else {
        m_noOfPassengers = combinedPassengers;
        other.m_noOfPassengers = 0;
    }

    return *this;
}



bool Bus::operator==(const Bus& other) const {
	if (!(*this) || !(other)) {
		return false;
	}
	return m_noOfPassengers == other.m_noOfPassengers;
}




int operator+(int left, const Bus& right) {
	return left + int(right);
}


ostream& operator<<(ostream& ostr, const Bus& right) {
    return right.display(ostr);
}

istream& operator>>(istream& istr, Bus& right) {
    return right.read(istr);
}

};