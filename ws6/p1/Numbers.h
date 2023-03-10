/*
*****************************************************************************
                          Workshop - #6
Full Name  : Harjeet Singh
Student ID#: 143232213
Email      : harjeet-singh3@myseneca.ca
Section    : ZRA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been shared 
with any other student. Although, I took a little idea from internet to find the 
errors which I was facing when I was trying to define the functions.
*****************************************************************************
*/


#ifndef SDDS_NUMBERS_H_ // Header guard to prevent multiple includes of the same header
#define SDDS_NUMBERS_H_

#include <iostream>
#include <fstream>

namespace sdds {

   class Numbers {

      double* m_Collection; // Pointer to an array of double numbers
      char* m_filename; // Pointer to a C-style string storing the filename
      int m_Collection_Size; // The number of elements in the array
      bool m_isOriginal; // Flag indicating whether the object created the array
      bool m_isAdded; // Flag indicating whether new elements have been added to the array

      // Private member functions
      bool isEmpty() const; // Checks if the array is empty
      void setEmpty(); // Sets the object to an empty state
      bool load(); // Loads the data from the file into the array
      void save() const; // Saves the data from the array to the file
      double average() const; // Calculates the average of the elements in the array
      double max() const; // Finds the maximum value in the array
      double min() const; // Finds the minimum value in the array
      unsigned int countLines(const char* filename); // Counts the number of lines in the file
      void sort(double* collectionPtr, unsigned int size); // Sorts the array in ascending order

   public:
      // Public member functions
      Numbers(); // Default constructor
      Numbers(const char* filename); // Constructor with filename argument
      ~Numbers(); // Destructor
      Numbers(const Numbers& num); // Copy constructor
      void sort(); // Sorts the array in ascending order
      Numbers& operator+=(const double& value); // Adds a new element to the array
      Numbers& operator=(const Numbers& num); // Copy assignment operator
      std::ostream& display(std::ostream& ostr) const; // Displays the contents of the array

   };

   // Non-member functions
   std::ostream& operator<<(std::ostream& ostr, const Numbers& N); // Overloaded insertion operator
   std::istream& operator>>(std::istream& istr, Numbers& N); // Overloaded extraction operator

}

#endif // !SDDS_NUMBERS_H_
