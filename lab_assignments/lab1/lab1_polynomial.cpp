// GROUP 14
// Andrew Zhao 20785698
// Jeffery Ng 20762964

#include <iostream>
#include <vector>
#include "lab1_polynomial.hpp"
#include <fstream> 
#include <cassert>
#include <cmath>

using namespace std; 

// class Polynomial Functions
// Parametric constructor 
Polynomial::Polynomial() {
    int degree = rand() % 1001; 
    
    for (int i = 0; i <= degree; i++) {
        data.push_back(rand() % 2001 + (-1000));
    }
}

Polynomial::Polynomial(int A[], int size) {
    for (int i = 0; i < size; i++) {
        data.push_back(A[i]);
    }
}

Polynomial::Polynomial(string fileName){
    ifstream in_file(fileName);

    string value; 
    string size_str;
    getline(in_file, size_str);

    size = stoi(size_str);
    while(getline(in_file, value)){
        if (value == ""){
            data.push_back(0);
        } else{
            data.push_back(stoi(value));
        }
    }

    in_file.close();
}

// Destructor
Polynomial::~Polynomial() { 
    // data will be deleted on its own 
}

// Operators
bool Polynomial::operator==(const Polynomial& target) {
    bool isEqual = true;
    if (data.size() == 0 && target.get_data().size() == 0) {
        return true;
    } else if (data.size() != target.get_data().size()) {
        return false;
    }
    for (int i = 0; i < data.size(); i++) {
        if (target.get_data().at(i) == data.at(i)) {
            isEqual = isEqual && true;
        } else {
            isEqual = isEqual && false;
        }
    }
    return isEqual;
}

Polynomial Polynomial::operator+(const Polynomial& target) {
    int new_size;
    int small_array_len;
    vector<int> new_poly_array;

    if (data.size() < target.get_data().size()) {
        small_array_len = data.size();
        new_poly_array = target.get_data();
    } else {
        small_array_len = target.get_data().size();
        new_poly_array = data;
    }

    for (int i = 0; i < small_array_len; i++) {
        new_poly_array.at(i) = (target.get_data().at(i) + data.at(i));
    }
    new_size = new_poly_array.size();

    Polynomial new_polynomial = Polynomial(new_poly_array.data(), new_size);
    return new_polynomial;
}

Polynomial Polynomial::operator-(const Polynomial& target) {
    int new_size;
    int small_array_len;
    vector<int> new_poly_array;

    if (data.size() < target.get_data().size()) {
        small_array_len = data.size();
        new_poly_array = target.get_data();
    } else {
        small_array_len = target.get_data().size();
        new_poly_array = data;
    }

    for (int i = 0; i < small_array_len; i++) {
        new_poly_array.at(i) = (data.at(i) - target.get_data().at(i));
    }
    new_size = new_poly_array.size();

    Polynomial new_polynomial = Polynomial(new_poly_array.data(), new_size);
    return new_polynomial;
}

Polynomial Polynomial::operator*(const Polynomial& target) {
    int new_size;
    vector<int> new_poly_array;

    // fill new array with zeros
    for (int i = 0; i < (data.size() + target.get_data().size() - 1); i++){
        new_poly_array.push_back(0);
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < target.get_data().size(); j++){
            new_poly_array.at(i+j) = new_poly_array.at(i+j) + (data.at(i) * target.get_data().at(j));
        }
    }
    new_size = new_poly_array.size();
    
    Polynomial new_polynomial = Polynomial(new_poly_array.data(), new_size);
    return new_polynomial;
}

// Setters & Getters
vector<int> Polynomial::get_data() const {
    return data; 
}

// Helper functions
Polynomial Polynomial::derivative() {
    int new_size;
    vector<int> new_poly_array;

    for (int i = 1; i < data.size(); i++) {
        new_poly_array.push_back(data.at(i) * i);
    }

    new_size = new_poly_array.size();

    Polynomial new_polynomial = Polynomial(new_poly_array.data(), new_size);
    return new_polynomial;
}

void Polynomial::print() {
    for (int i = data.size() - 1; i >= 0; i--) {
        if (i < data.size() - 1 && data.at(i) >= 0) {
            cout << " + " << data.at(i) << "x^" << i;
        } else if (data.at(i) < 0) {
            cout << " - " << abs(data.at(i)) << "x^" << i;
        } else if (i == data.size() - 1 && data.at(i) >= 0) {
            cout << data.at(i) << "x^" << i;
        }
    }
    cout << endl;
}


// class PolynomialTest functions
// constructor tests
bool PolynomialTest::test_constructor1() {
    int array1[] = {1, 2, 10, -10, -100, 100};
    int array2[] = {55, 20, 33, 23, 892, 1000};
    int array3[] = {-1000};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    bool passTests = true;

    for (int i = 0; i < size1; i++) {
        if (poly1.get_data().at(i) == array1[i]) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < size2; i++) {
        if (poly2.get_data().at(i) == array2[i]) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < size3; i++) {
        if (poly3.get_data().at(i) == array3[i]) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }
    return passTests;
}

bool PolynomialTest::test_constructor2() {
    Polynomial poly1 = Polynomial();
    Polynomial poly2 = Polynomial();
    Polynomial poly3 = Polynomial();

    bool passTests = true;

    poly1.print();
    poly2.print();
    poly3.print();

    return passTests;
}

bool PolynomialTest::test_constructor3() {
    bool passTests = true;

    Polynomial poly1 = Polynomial("test.txt");
    Polynomial poly2 = Polynomial("test2.txt");
    Polynomial poly3 = Polynomial("test3.txt");

    vector<int> array1{-2, 3, 0, 1, 4};
    vector<int> array2{-10, 0, 0, 1, 4, 2, -1, -9};
    vector<int> array3{3, 4, 23, 7, 436, -111, 52, 3, 3};

    for (int i = 0; i < array1.size(); i++) {
        if (poly1.get_data().at(i) == array1.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array2.size(); i++) {
        if (poly2.get_data().at(i) == array2.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array3.size(); i++) {
        if (poly3.get_data().at(i) == array3.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }
    return passTests;
}

// operator tests
bool PolynomialTest::test_operator1() {
    int array1[] = {1, 2, 10, -10, -100, 100};
    int array2[] = {55, 20, 33, 23, 892, 1000};
    int array3[] = {};

    int size1 = 6;
    int size2 = 6;
    int size3 = 0;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly1_check = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly2_check = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);
    Polynomial poly3_check = Polynomial(array3, size3);

    if (poly1 == poly1_check && poly2 == poly2_check && poly3 == poly3_check) {
        return true;
    }
    return false;
}

//testing (+) operator
bool PolynomialTest::test_operator2() {
    bool passTests = true;
    
    int array1[] = {1, 2, 3, 4, 5, 6};
    int array2[] = {4, 5, 6, 7, 8, -100};
    int array3[] = {50};

    vector<int> array1_check{5, 7, 9, 11, 13, -94};
    vector<int> array2_check{51, 2, 3, 4, 5, 6};
    vector<int> array3_check{54, 5, 6, 7, 8, -100};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    Polynomial poly1_check = poly1 + poly2;
    Polynomial poly2_check = poly1 + poly3;
    Polynomial poly3_check = poly2 + poly3;

    for (int i = 0; i < array1_check.size(); i++) {
        if (poly1_check.get_data().at(i) == array1_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array2_check.size(); i++) {
        if (poly2_check.get_data().at(i) == array2_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array3_check.size(); i++) {
        if (poly3_check.get_data().at(i) == array3_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }
    return passTests;
}

bool PolynomialTest::test_operator3() {
    bool passTests = true;
    
    int array1[] = {1, 2, 3, 4, 5, 6};
    int array2[] = {4, 5, 6, 7, 8, -100};
    int array3[] = {50};

    vector<int> array1_check{-3, -3, -3, -3, -3, 106};
    vector<int> array2_check{-49, 2, 3, 4, 5, 6};
    vector<int> array3_check{-46, 5, 6, 7, 8, -100};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    Polynomial poly1_check = poly1 - poly2;
    Polynomial poly2_check = poly1 - poly3;
    Polynomial poly3_check = poly2 - poly3;

    for (int i = 0; i < array1_check.size(); i++) {
        if (poly1_check.get_data().at(i) == array1_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array2_check.size(); i++) {
        if (poly2_check.get_data().at(i) == array2_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array3_check.size(); i++) {
        if (poly3_check.get_data().at(i) == array3_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }
    return passTests;
}

bool PolynomialTest::test_operator4() {
    bool passTests = true;
    
    int array1[] = {1, 2, 3};
    int array2[] = {4, 5, 6};
    int array3[] = {50};

    vector<int> array1_check{4, 13, 28, 27, 18}; // poly1 * poly2
    vector<int> array2_check{50, 100, 150}; // poly1 * poly3
    vector<int> array3_check{200, 250, 300}; // poly2 * poly3

    int size1 = 3;
    int size2 = 3;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    Polynomial poly1_check = poly1 * poly2;
    Polynomial poly2_check = poly1 * poly3;
    Polynomial poly3_check = poly2 * poly3;

    for (int i = 0; i < array1_check.size(); i++) {
        if (poly1_check.get_data().at(i) == array1_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array2_check.size(); i++) {
        if (poly2_check.get_data().at(i) == array2_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }

    for (int i = 0; i < array3_check.size(); i++) {
        if (poly3_check.get_data().at(i) == array3_check.at(i)) {
            passTests = passTests && true;
        } else {
            return false;
        }
    }
    return passTests;
}

// getter test
bool PolynomialTest::test_getter() {
    int array1[] = {1, 2, 3, 4, 5, 6};
    int array2[] = {4, 5, 6, 7, 8, -100};
    int array3[] = {50};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    vector<int> result1 = poly1.get_data();
    vector<int> result2 = poly2.get_data();
    vector<int> result3 = poly3.get_data();    

    for(int i = 0; i < result1.size(); i++){
        if(result1.at(i) != array1[i]){
            return false;
        }
    }
    for(int i = 0; i < result2.size(); i++){
        if(result2.at(i) != array2[i]){
            return false;
        }
    }
    for(int i = 0; i < result3.size(); i++){
        if(result3.at(i) != array3[i]){
            return false;
        }
    }
    return true;
}

// helper function tests
bool PolynomialTest::test_derivative() {
    int array1[] = {1, 2, 3, 4, 5, 6};
    int array2[] = {4, 5, 6, 7, 8, -100};
    int array3[] = {50};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);

    vector<int> array1_check{2, 6, 12, 20, 30};
    vector<int> array2_check{5, 12, 21, 32, -500};
    vector<int> array3_check{};

    Polynomial poly1_prime = poly1.derivative();
    Polynomial poly2_prime = poly2.derivative();
    Polynomial poly3_prime = poly3.derivative();

    for(int i = 0; i < array1_check.size(); i++){
        if(poly1_prime.get_data().at(i) != array1_check[i]){
            return false;
        }
    }

    for(int i = 0; i < array2_check.size(); i++){
        if(poly2_prime.get_data().at(i) != array2_check[i]){
            return false;
        }
    }

    for(int i = 0; i < array3_check.size(); i++){
        if(poly3_prime.get_data().at(i) != array3_check[i]){
            return false;
        }
    }

    return true;
}

bool PolynomialTest::test_print() {
    int array1[] = {1, 2, 3, 4, 5, 6};
    int array2[] = {4, 5, 6, 7, 8, -100};
    int array3[] = {50};

    int size1 = 6;
    int size2 = 6;
    int size3 = 1;

    Polynomial poly1 = Polynomial(array1, size1);
    Polynomial poly2 = Polynomial(array2, size2);
    Polynomial poly3 = Polynomial(array3, size3);
   
    cout << "poly1: ";
    poly1.print();
    cout << "poly2: ";
    poly2.print();
    cout << "poly3: ";
    poly3.print();

    return true;
}

void PolynomialTest::run() {
    if (test_constructor1()) {
        cout << "Test Constructor1 Passed" << endl;
    } else {
        cout << "Test Constructor1 Failed" << endl;
    }

    if (test_constructor2()) {
        cout << "Test Constructor2 Passed" << endl;
    } else {
        cout << "Test Constructor2 Failed" << endl;
    }

    if (test_constructor3()) {
        cout << "Test Constructor3 Passed" << endl;
    } else {
        cout << "Test Constructor3 Failed" << endl;
    }

    if (test_operator1()) {
        cout << "Test Operator1 (==) Passed" << endl;
    } else {
        cout << "Test Operator1 (==) Failed" << endl;
    }

    if (test_operator2()) {
        cout << "Test Operator2 (+) Passed" << endl;
    } else {
        cout << "Test Operator2 (+) Failed" << endl;
    }

    if (test_operator3()) {
        cout << "Test Operator3 (-) Passed" << endl;
    } else {
        cout << "Test Operator3 (-) Failed" << endl;
    }

    if (test_operator4()) {
        cout << "Test Operator4 (*) Passed" << endl;
    } else {
        cout << "Test Operator4 (*) Failed" << endl;
    }

    if (test_getter()) {
        cout << "Test Getter Passed" << endl;
    } else {
        cout << "Test Getter Failed" << endl;
    }

    if (test_derivative()) {
        cout << "Test Derivative Passed" << endl;
    } else {
        cout << "Test Derivative Failed" << endl;
    }

    if (test_print()) {
        cout << "Test Print Passed" << endl;
    } else {
        cout << "Test Print Failed" << endl;
    }
}


// Main Function
int main() {
    PolynomialTest my_test;
    my_test.run();

    return 0;
}
