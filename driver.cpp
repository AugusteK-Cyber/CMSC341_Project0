/*#include "hist.h"

class Tester { // Tester class to implement test functions
public:
    bool testCopyConstructor(const Hist& histogram);
    void measureSimulationTime(int numTrials, int items, int students);
};

int main() {
    Tester tester;
    {
        cout << "\nDump of 2 grading items for 35 students:\n" << endl;
        Hist h1(2);
        h1.simulateData(35);
        h1.dump();
    }
    {
        try {
            cout << "Testing exception case for number of items less than 1:\n" << endl;
            Hist h1(0);
            h1.simulateData(40);
        }
        catch (std::out_of_range e) {
            cout << e.what() << endl;
        }
    }
    {
        //test deep copy, object with many members
        Hist h1(20);// 20 items, e.g. exams, quizzes, homeworks
        h1.simulateData(400);// process grades for 400 students
        cout << "\nTest case, Copy Constructor: testing for deep copy with 20 items and 400 students:\n" << endl;
        if (tester.testCopyConstructor(h1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:\n" << endl;
        int M = 4;//number of trials
        int items = 2;//number of items, e.g. exams
        int students = 100000;//original input size, number of students taking tests
        tester.measureSimulationTime(M, items, students);
    }
    cout << endl;
    return 0;
}

bool Tester::testCopyConstructor(const Hist& histogram) {
    Hist aCopy(histogram);
    //the case of empty objects
    if (histogram.m_items == 0 && aCopy.m_items == 0) return true;
    //the case that number of items is the same and the table pointers are not the same
    else if (histogram.m_items == aCopy.m_items && histogram.m_table != aCopy.m_table) {
        for (int i = 0; i < histogram.m_items; i++) {
            // check whether every Data object is a deep copy or not
            if (histogram.m_table[i] == aCopy.m_table[i])
                //if they are the same objects, then is not a deep copy
                return false;
        }
        return true;
    }
    //everthing else
    else return false;
}

void Tester::measureSimulationTime(int numTrials, int items, int students)
{
    // Measuring the efficiency of data simulation algorithm with system clock ticks
    // Clock ticks are units of time of a constant but system-specific length, 
    //  as those returned by function clock().
    // Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size, everytime it will double
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k = 0; k < numTrials - 1; k++)
    {
        Hist h1(items);
        start = clock();
        h1.simulateData(students);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Counting " << items * students << " grades took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
        students = students * a;//increase number of students by increase factor
    }
}
*/