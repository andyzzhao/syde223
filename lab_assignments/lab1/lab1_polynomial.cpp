// GROUP 14
// Andrew Zhao 20785698
// Jeffery Ng 20762964

#include <iostream>
#include <vector>
#include "lab1_polynomial.hpp"
#include <fstream> 
#include <cassert>

using namespace std; 

// Parametric constructor 
Polynomial::Polynomial() {
    int degree = rand() % 1001; 
    int coeffs[degree];
    
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = rand() % 2001 + (-1000);
    }
}

Polynomial::Polynomial(int A[], int size) {
    for (int i = 0; i < size; i++) {
        data.push_back(A[i]);
    }
}

Polynomial::Polynomial(string fileName){
    
}

Polynomial::~Polynomial() { 
    // data will be deleted on its own 
}

// Function to test the constructors
bool PolynomialTest::test_constructors1() {
    int A[] = {1, 0, 0, -2, 3, 5};

    Polynomial test_polynomial = new Polynomial();
    Polynomial test_polynomial_parameters = new Polynomial(A[], 6);

    // Get data from test_polynomial
    // vector<int> data = 
    // assert()

}

void PolynomialTest::run() {
    if (test_constructors1()) {
        cout << "Test Constructors1 Passed" << endl;
    } else {
        cout << "Test Constructors1 Failed" << endl;
    }
}


int main(){
    srand(time(0));

    return 0;
}