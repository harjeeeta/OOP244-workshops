#ifndef SDDS_BUS_H
#define SDDS_BUS_H

namespace sdds {

	const double BusTicketPrice = 125.34; //declares a constant variable BusTicketPrice with a value of 125.34.

	class Bus {
		int m_noOfSeats;
		int m_noOfPassengers;

	    void setOutOfService();
	    void drawBus(int seats, int noOfPassengers, std::ostream& ostr) const;

	public:

		Bus(int noOfSeats = 20, int noOfPassengers = 0);  //constructor of the Bus class, which takes two optional integer parameters.

		std::ostream& display(std::ostream& ostr = std::cout) const;  //outputs the state of the Bus object to an output stream.
		
		std::istream& read(std::istream& istr = std::cin);   //reads input from an input stream

		operator bool() const;  // conversion function, allow the Bus object to be implicitly converted to bool
		operator int() const;   // conversion function, allow the Bus object to be implicitly converted to int
		operator double() const;  // conversion function, allow the Bus object to be implicitly converted to double

		bool operator--();
		bool operator++();
		bool operator--(int);
		bool operator++(int);  // overloaded increment and decrement operators.

		Bus& operator=(int value);  //overloaded assignment operator

		Bus& operator+=(int value);  //overloaded compound assignment operator

	    Bus& operator+=(Bus& other);  //overloaded compound assignment operator  that takes another Bus object as a parameter.

	    bool operator==(const Bus& other) const;  // overloaded equality operator hat compares two Bus objects.

	};


	int operator+(int left, const Bus& right);

	std::ostream& operator<<(std::ostream& ostr, const Bus& right);

	std::istream& operator>>(std::istream& istr, Bus& right);

}
#endif