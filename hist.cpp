#include "hist.h"
#include <iostream>
#include <assert.h>

// Constructor. It allocates memory to m_data with the lenght of DATAARRAYSIZE
Data::Data() :m_arraySize(DATAARRAYSIZE) {
    //array<int, DATAARRAYSIZE> m_data; // Don't use that library.
    m_data = new int[m_arraySize];
    // Dereference the pointer array
    for (int i = 0; i < m_arraySize; i++) {
        *(m_data + i) = 0; // Initialize the memory block allocated. This will initialize all the blocks of the array to 0 starting by block 0.
    }
}
// Copy constructor
Data::Data(const Data& copyData) : m_arraySize(copyData.m_arraySize) {
    m_data = copyData.m_data;
    //m_data = new int[m_arraySize];
}
// Destructor. Deallocates the memory
Data::~Data() {
    delete[] m_data;
}
// This function assigns the random grades obtained by the students to their corresponding category. 
// The students parameter indicates the number of grades this function generates, counts, and stores the 
// counts in the m_data cells. Every cell of m_data array stores the count of grades in a specific category.
void Data::simulateData(int students) {
    int grades;
    Random* random = new Random(MINGRADE, MAXGRADE); // Pointer variable for the random numbers
    for (int count = 0; count < students; count++) {
        grades = random->getNormRand(); // Get the grades from the random numbers generated

        if (grades >= 0 && grades <= 9) {
            m_data[0] += 1;
        }
        if (grades >= 10 && grades <= 19) {
            m_data[1] += 1;
        }
        if (grades >= 20 && grades <= 29) {
            m_data[2] += 1;
        }
        if (grades >= 30 && grades <= 39) {
            m_data[3] += 1;
        }
        if (grades >= 40 && grades <= 49) {
            m_data[4] += 1;
        }
        if (grades >= 50 && grades <= 59) {
            m_data[5] += 1;
        }
        if (grades >= 60 && grades <= 69) {
            m_data[6] += 1;
        }
        if (grades >= 70 && grades <= 79) {
            m_data[7] += 1;
        }
        if (grades >= 80 && grades <= 89) {
            m_data[8] += 1;
        }
        if (grades >= 90 && grades <= 100) {
            m_data[9] += 1;
        } 
    }
    delete random; // Free memory allocated
}
// Display the number of asterix corresponding to each category of grades by students
string Data::asterixDisplay(string str, int number) {
    string output = "";
    while (number--) {
        output += str;
    }
    return output;
}
// This function outputs the histogram. For every cell in m_data the function prints out 
// stars using the number stored in the cell. The item parameter indicates the item number.
void Data::dump(int item) {
    int i = 10;
    int arraySize = Data::getArraySize();
    cout << "Histogram for item " << item << ":" << endl;
    for (int j = 0; j < arraySize; j++) {
        cout << right << setw(3) << i << " " << right << asterixDisplay("*", getData(j)) << endl;
        i += 10;
    }
}
// Return the data corresponding to the specified index on the array
int Data::getData(int index) {
    return m_data[index];
}
// Return the size of the array, which equals the value of the variable DATAARRAYSIZE (m_arraySize).
int Data::getArraySize() {
    return m_arraySize;
}
// Overloaded equality operator. It returns true if two objects are the same.
// The "same objects" means they are the same pointers and carry the same value  
// in every correpsonding cell.
// For testing inequality we can simply negate the return value of this operator.
bool operator==(const Data& lhs, const Data& rhs) {
    if (&lhs == &rhs)
    {
        for (int i = 0; i < lhs.m_arraySize; i++) {
            if (lhs.m_data[i] != rhs.m_data[i])
                return false;
        }
        return true;
    }
    else return false;
}

// Constructor. It allocates memory to m_table with the length of items. If user passes a value less than 1, 
// the number of items should be set to zero. In such a case we do not need to allocate memory.
Hist::Hist(int items):m_items(items) {
    if (m_items < 1) {
        m_items = 0;
        //cout << "No memory will be allocated for items less than 1." << endl;
    }
    m_table = new Data[m_items];
}
// Destructor. Deallocates the memory
Hist::~Hist() {
    delete[] m_table;
}
// Output data
void Hist::dump() {
    for (int i = 0; i < m_items; i++) {
        m_table[i].dump(i);
        cout << endl;
    }
}
// This function calls Data::simulateData(int students) to populate every cell of m_table. Every cell of m_table
// represents a grading item. The parameter students indicate the number of grades. If the number of items is less 
// than 1, this function throws a std::out_of_range exception.
void Hist::simulateData(int students) {
    try{
        if (m_items < 1) {
            throw out_of_range("Error at simulate: number of items is out of range!");
        }
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
    }
    for (int i = 0; i < m_items; i++) {
        m_table[i].simulateData(students);
    }
}
// This is the copy constructor. It creates a deep copy of the rhs object.
Hist::Hist(const Hist& rhs) : m_items(rhs.m_items) {
    if (m_items < 1) {
        m_items = 0;
        //cout << "No memory will be allocated for items less than 1." << endl;
    }
    m_table = new Data[m_items];
}

// This is the assignment operator. It creates a deep copy of rhs.
const Hist& Hist::operator=(const Hist& rhs) {
    if (this != &rhs)
    {
        delete[] m_table;
        m_table = new Data[m_items];
        m_table = rhs.m_table;
        delete[] m_table;
    }
    return *this;
}
/*delete[] m_table;
        m_table = new Data[m_items];
        m_table = rhs.m_table;
        delete[] m_table;
        return *this;
*/