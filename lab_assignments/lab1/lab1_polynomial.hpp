#ifndef LAB1_POLYNOMIAL
#define LAB1_POLYNOMIAL

#include <vector>

using namespace std;

class Polynomial {
    vector<int> data;
    int size; 

public:
    Polynomial();
    Polynomial(int A[], int size);
    Polynomial(string fileName);

    // Destructor
    ~Polynomial();

    // Operator
    bool operator==(const Polynomial& target); // performs *this == target
    Polynomial operator+(const Polynomial& target); // performs *this + target
    Polynomial operator-(const Polynomial& target); // performs *this - target
    Polynomial operator*(const Polynomial& target); // performs *this * target

    // Setters and Getters
    vector<int> get_data() const;

    // Helper functions
    Polynomial derivative(); // computers derivative of *this
    void print();
};

class PolynomialTest {

public:
    // constructor tests
    bool test_constructor1();
    bool test_constructor2();
    bool test_constructor3();

    // operator tests
    bool test_operator1();
    bool test_operator2();
    bool test_operator3();
    bool test_operator4();

    // getter test
    bool test_getter();

    // helper function tests
    bool test_derivative();
    bool test_print();

    void run();
};

#endif
