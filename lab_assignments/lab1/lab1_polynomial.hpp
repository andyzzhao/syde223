#ifndef LAB1_POLYNOMIAL
#define LAB1_POLYNOMIAL

#include <vector>

using namespace std;

class Polynomial {
    vector<int> data;

public:
    Polynomial();
    Polynomial(int A[], int size);

    // Destructor
    ~Polynomial();

    // Setters and Getters
    void get_data() {
        return data;
    }
};

class PolynomialTest {

public:
    bool test_constructors1();
    void run();
}

#endif