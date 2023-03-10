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


#define _CRT_SECURE_NO_WARNINGS // disable warnings related to fopen and other functions

#include "Numbers.h"

#include <algorithm> // needed for std::sort
#include <iomanip> // needed for std::setprecision and std::fixed
#include <cstring> // needed for strcpy
#include <string> // needed for std::getline
#include <numeric> // needed for std::accumulate

using namespace std;

namespace sdds {

   Numbers::Numbers() { 
      setEmpty();
   } 

   Numbers::Numbers(const char* filename) {
      // Set initial values
      m_isOriginal = true;
      m_filename = new char[strlen(filename) + 1];
      strcpy(m_filename, filename);
      m_Collection_Size = 0;
      m_Collection = nullptr;

      // Attempt to load the numbers from the file
      if (load()) {
         m_Collection_Size = countLines(m_filename);
      } else {
         // If load fails, reset the object to its empty state
         delete[] m_Collection;
         m_Collection = nullptr;
         delete[] m_filename;
         m_filename = nullptr;
         m_isOriginal = false;
      }
   }

   Numbers::~Numbers() {
      save();
      delete[] m_filename;
      delete[] m_Collection;
   }

   void Numbers::sort(double* nums, unsigned int size) {
      unsigned int i, j;
      double temp;
      for(i = size - 1; size && i > 0; i--) {
         for(j = 0; j < i; j++) {
            if(nums[j] > nums[j + 1]) {
               temp = nums[j];
               nums[j] = nums[j + 1];
               nums[j + 1] = temp;
            }
         }
      }
   }

   void Numbers::sort() {
      std::sort(m_Collection, m_Collection + m_Collection_Size);
   }

   unsigned int Numbers::countLines(const char* filename) {
     unsigned int lines = 0u;
      ifstream nums(filename);
      while(nums) {
         lines += (nums.get() == '\n');
      }
      return lines;
   }

   bool Numbers::load() {
      // This function loads the numbers from a file.
      // It returns true if successful and false otherwise.
      // If the load fails, the object is reset to its empty state.

      // Free the memory of the current array, if any
      if (m_Collection != nullptr) {
         delete[] m_Collection;
         m_Collection = nullptr;
      }

      // Reset the size and flags
      m_Collection_Size = 0;
      m_isOriginal = false;
      m_isAdded = false;

      // Open the file for reading
      std::ifstream inFile(m_filename);
      if (!inFile) {
         return false;
      }

      // Count the number of lines in the file
      int numLines = 0;
      std::string line;
      while (std::getline(inFile, line)) {
         numLines++;
      }

      // Allocate memory for the array
      m_Collection = new double[numLines];

      // Reset the file position to the beginning
      inFile.clear();
      inFile.seekg(0, std::ios::beg);

      // Read the values from the file
      int i = 0;
      double value;
      while (inFile >> value) {
         m_Collection[i] = value;
         i++;
      }

     


    // Check if all the values were read
    if (i != numLines) {
        delete[] m_Collection;
        m_Collection = nullptr;
        return false;
    }

    // Set the size and flags
    m_Collection_Size = numLines;
    m_isOriginal = true;

    return true;
}





 bool Numbers::isEmpty() const {
    return m_Collection_Size == 0;
}



   void Numbers::setEmpty() { 
      m_Collection = nullptr;
      m_filename = nullptr;
     m_isAdded = false;
      m_Collection_Size = 0;
     m_isOriginal = false;

   }

 
 



double Numbers::average() const {
    if (isEmpty()) {
        return 0.0;
    } else {
        double sum = 0.0;
        for (int i = 0; i < m_Collection_Size; i++) {
            sum += m_Collection[i];
        }
        return sum / m_Collection_Size;
    }
}



double Numbers::min() const {
    if (isEmpty()) {
        return 0.0;
    } else {
        double min = m_Collection[0];
        for (int i = 1; i < m_Collection_Size; i++) {
            if (m_Collection[i] < min) {
                min = m_Collection[i];
            }
        }
        return min;
    }
}




double Numbers::max() const {
    if (isEmpty()) {
        return 0.0;
    } else {
        double max = m_Collection[0];
        for (int i = 1; i < m_Collection_Size; i++) {
            if (m_Collection[i] > max) {
                max = m_Collection[i];
            }
        }
        return max;
    }
}


  
Numbers::Numbers(const Numbers& num) {
    setEmpty();

    m_isAdded = num.m_isAdded;
    m_Collection_Size = num.m_Collection_Size;
    if (num.m_Collection) {
        m_Collection = new double[m_Collection_Size];
        std::copy(num.m_Collection, num.m_Collection + m_Collection_Size, m_Collection);
    }
}







void Numbers::save() const {
  if (m_isOriginal && m_isAdded) {
    std::ofstream ostr(m_filename);
    for (int i = 0; i < m_Collection_Size; i++) {
      ostr << std::setprecision(2) << std::fixed << m_Collection[i] << std::endl;
    }
    ostr.close();
  }
}



Numbers& Numbers::operator+=(const double& value) {
  if (isEmpty()) {
    m_Collection = new double[1];
    m_Collection[0] = value;
    m_Collection_Size = 1;
    m_isAdded = true;
  } else {
    double* temp = new double[m_Collection_Size + 1];
    for (int i = 0; i < m_Collection_Size; i++) {
      temp[i] = m_Collection[i];
    }
    temp[m_Collection_Size] = value;
    delete[] m_Collection;
    m_Collection = temp;
    m_Collection_Size++;
    m_isAdded = true;
  }
  return *this;
}

Numbers& Numbers::operator=(const Numbers& num) {
  if (this != &num) {  
    double* new_numbers = nullptr;
    if (!num.isEmpty()) {
      new_numbers = new double[num.m_Collection_Size];
      for (int i = 0; i < num.m_Collection_Size; i++) {
        new_numbers[i] = num.m_Collection[i];
      }
    }
    delete[] m_Collection;

    // update object state with new values
    m_Collection = new_numbers;
    m_Collection_Size = num.m_Collection_Size;
    m_isOriginal = num.m_isOriginal;
    m_isAdded = num.m_isAdded;
  }
  return *this;
}



std::ostream& Numbers::display(std::ostream& ostr) const {
  if (isEmpty()) {
    ostr << "Empty list" ;
  } else {
    if (m_isOriginal) {
      ostr << m_filename << std::endl;
    } else {
      ostr << "Copy of numbers.txt" << std::endl;
    }
    ostr << std::fixed << std::setprecision(2);
    for (int i = 0; i < m_Collection_Size; i++) {
      ostr << m_Collection[i];
      if (i < m_Collection_Size - 1) {
        ostr << ", ";
      }
    }
    ostr << std::endl << "----------------------------------------------------------------------------" << std::endl;
    ostr << "Total of " << m_Collection_Size << " number(s), ";
    ostr << "Largest: " << max() << ", ";
    ostr << "Smallest: " << min() << ", ";
    ostr << "Average: " << average() << std::endl << "============================================================================";
  }
  return ostr;
}


   std::ostream& operator<<(std::ostream& ostr, const Numbers& N) {
   
      return N.display(ostr);
   }

 std::istream& operator>>(std::istream& istr, Numbers& N) {
  double add;
  if (istr >> add) {
    N += add;
  }
  return istr;
}




}
