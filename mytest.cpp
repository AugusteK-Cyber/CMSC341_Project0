/**
 * File:    mytest.cpp
 * Author:  Auguste Kiendrebeogo
 * Section: 4
 * Created: 09/08/21
 * Date due: 09/14/21
 * E-mail:  akiendr1@umbc.edu
 *
 * Description:
 * File withe the different tests in it.
 */

#include "hist.h"

class Tester { // Tester class to implement test functions
public:
    bool testOperator(const Hist& histogram, const Hist& histogram1);
    bool testCopyConstructor(const Hist& histogram);
    void measureSimulationTime(int numTrials, int items, int students);
};

int main() {
    Tester tester;
    {
        // Testing error case with a Hist object h1 created with -1 item:
        cout << "\nDump of -1 grading items for 40 students:\n" << endl;
        Hist h1(-1);
        h1.simulateData(40);
        h1.dump();

        // Testing edge case with a Hist object h2 created with 0 item
        cout << "\nDump of 0 grading items for 40 students:\n" << endl;
        Hist h2(0);
        h2.simulateData(40);
        h2.dump();

        // Testing edge case with a Hist object h3 created with 1 item
        cout << "\nDump of 1 grading items for 40 students:\n" << endl;
        Hist h3(1);
        h3.simulateData(40);
        h3.dump();

        // Testing normal case with a Hist object h4 created with 100 item
        cout << "\nDump of 100 grading items for 40 students:\n" << endl;
        Hist h4(3);
        h4.simulateData(40);
        h4.dump();
    }
    {
        try {
            cout << "Testing exception case for number of items less than 1:\n" << endl;
            Hist h1(0);
            h1.simulateData(30);
        }
        catch (std::out_of_range e) {
            cout << e.what() << endl;
        }
    }
    {
        //test deep copy, object with many members
        Hist h1(27);// 27 items, e.g. exams, quizzes, homeworks
        h1.simulateData(348);// process grades for 348 students
        cout << "\nTest case, Copy Constructor: testing for deep copy with 27 items and 348 students:\n" << endl;
        if (tester.testCopyConstructor(h1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //Measuring the efficiency of insertion functionality test case 1
        cout << "\nMeasuring the efficiency of insertion functionality:\n" << endl;
        int M = 5;//number of trials
        int items = 3;//number of items, e.g. exams
        int students = 200000;//original input size, number of students taking tests
        tester.measureSimulationTime(M, items, students);
    }

    {
        //Measuring the efficiency of insertion functionality test case 2
        cout << "\nMeasuring the efficiency of insertion functionality:\n" << endl;
        int M = 7;//number of trials
        int items = 5;//number of items, e.g. exams
        int students = 200000;//original input size, number of students taking tests
        tester.measureSimulationTime(M, items, students);
    }

    {
        //Measuring the efficiency of insertion functionality test case 3
        cout << "\nMeasuring the efficiency of insertion functionality:\n" << endl;
        int M = 9;//number of trials
        int items = 7;//number of items, e.g. exams
        int students = 200000;//original input size, number of students taking tests
        tester.measureSimulationTime(M, items, students);
    }

    {
        //Ensuring the assignment operator does not self-assign
        cout << "\nEnsuring the assignment operator does not self-assign:\n" << endl;
        Hist h1(20);// 20 items, e.g. exams, quizzes, homeworks
        Hist h2(20);// 20 items, e.g. exams, quizzes, homeworks
        bool test = tester.testOperator(h1, h2);
        if (test == false) cout << "Test succeed! Assignment operator does not self-assign" << endl;
        else cout << "Test failed! Assignment operator does self-assign" << endl;
    }
    cout << endl;
    return 0;
}

bool Tester::testOperator(const Hist& lhs, const Hist& rhs) {
    // Test to make sure the assignment operator does not self-assign
    if (&lhs == &rhs)
    {
        for (int i = 0; i < lhs.m_items; i++) {
            if (lhs.m_table[i].m_data != rhs.m_table[i].m_data)
                return false; // Test succeed
        }
        return true; // Test failed
    }
    else return false; // Test succeed
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
        items = items * a;//increase number of items by increase factor
    }
}