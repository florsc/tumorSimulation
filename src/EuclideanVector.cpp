//
// Created by florian on 9/20/21.
//

#include "EuclideanVector.h"

#include <algorithm>
#include <iostream>
#include <utility>

// Constructor for one arg (int): Initialises an EV of size 'int', with magnitudes 0
EuclideanVector::EuclideanVector(const int &size) {
    x = 0;
    y = 0;
    z = 0;
}

// Constructor for two args (int, double): Initialises an EV of size 'int', with magnitudes 'double'
EuclideanVector::EuclideanVector(const int &size, const double &magnitudes) {
    x = magnitudes;
    y = magnitudes;
    z = magnitudes;
}


// Copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector &copy) {
x = copy.x;
y = copy.y;
z = copy.z;
}

// Copy assignment
EuclideanVector &EuclideanVector::operator=(const EuclideanVector &o) {
    x = o.x;
    y = o.y;
    z = o.z;
    return *this;
}

// Subscript operator
double &EuclideanVector::operator[](const int &i) {
    switch(i){
        case(0): return x;
    case(1): return y;
    case(2): return z;}
}

// Subscript operator for a const EV
const double &EuclideanVector::operator[](const int &i) const {
    switch(i){
        case(0): return x;
        case(1): return y;
        case(2): return z;}
}

// Addition (+=) operator
EuclideanVector &EuclideanVector::operator+=(const EuclideanVector &o) {
    x +=o.x;
    y +=o.y;
    z +=o.z;
    return *this;
}

// Subtraction (-=) operator
EuclideanVector &EuclideanVector::operator-=(const EuclideanVector &o) {
    x -=o.x;
    y -=o.y;
    z -=o.z;
    return *this;
}

// Multiplication (*=) operator
EuclideanVector &EuclideanVector::operator*=(const double &multiplier) {
    x *=multiplier;
    y *=multiplier;
    z *=multiplier;
    return *this;
}

// Division (/=) operator
EuclideanVector &EuclideanVector::operator/=(const double &divider) {
    x /=divider;
    y /=divider;
    z /=divider;
    return *this;
}

// EV -> vector<double> typecast
EuclideanVector::operator std::vector<double>() const {
    std::vector<double> returnVector(3);
    returnVector[0]=x;
    returnVector[1]=y;
    returnVector[2]=z;
    return returnVector;
}

// Magnitude in dimension as a double
double EuclideanVector::at(const int &place) const {
    switch(place){
        case(0): return x;
        case(1): return y;
        case(2): return z;}
}

// Magnitude in dimension as a reference
double &EuclideanVector::at(const int &place) {
    if (place < 0 || place > 2) {
        throw EuclideanVectorError("Index " + std::to_string(place) +
                                   " is not valid for this EuclideanVector object");
    }
    switch(place){
        case(0): return x;
        case(1): return y;
        case(2): return z;}
}

// Calculates EV's Euclidean normal
double EuclideanVector::GetEuclideanNorm() const {
    double returnValue = x*x+y*y+z*z;
    return std::sqrt(returnValue);
}

// Calculates EV's unit vector
EuclideanVector EuclideanVector::CreateUnitVector() const {
    if (this->GetEuclideanNorm() == 0) {
        throw EuclideanVectorError(
                "EuclideanVector with euclidean normal of 0 does not have a unit vector");
    }
    double eucNorm = this->GetEuclideanNorm();
    return *this/eucNorm;
}

// Friends
// Equals to operator
bool operator==(const EuclideanVector &v1, const EuclideanVector &v2) {
    return v1.x==v2.x&&v1.y==v2.y&&v1.z==v2.z;
}

// Not equals to operator
bool operator!=(const EuclideanVector &v1, const EuclideanVector &v2) {
    return v1.x!=v2.x&&v1.y!=v2.y&&v1.z!=v2.z;
}

// Subtraction operator
EuclideanVector operator+(const EuclideanVector &v1, const EuclideanVector &v2) {
    // Use a copy constructor here
    EuclideanVector result{v1};
    result += v2;
    return result;
}

// Subtraction operator
EuclideanVector operator-(const EuclideanVector &v1, const EuclideanVector &v2) {
    // Use a copy constructor here
    EuclideanVector result{v1};
    result -= v2;
    return result;
}

// Multiplication (Dot product) operator
double operator*(const EuclideanVector &v1, const EuclideanVector &v2) {
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

// Scalar multiplication operator
EuclideanVector operator*(const EuclideanVector &v1, const double &multipliedBy) {
    // Use a copy constructor here
    EuclideanVector result{v1};
    result *= multipliedBy;
    return result;
}

// Scalar multiplication operator
EuclideanVector operator*(const double &multipliedBy, const EuclideanVector &v1) {
    // Use a copy constructor here
    EuclideanVector result{v1};
    result *= multipliedBy;
    return result;
}

// Scalar division operator
EuclideanVector operator/(const EuclideanVector &v1, const double &dividedBy) {
    if (dividedBy == 0) {
        throw EuclideanVectorError("Invalid vector division by 0");
    }
    // Use a copy constructor here
    EuclideanVector result{v1};
    result /= dividedBy;
    return result;
}

// Output stream operator
std::ostream &operator<<(std::ostream &os, const EuclideanVector &v) {
    // Output is [x, x2, x3, ...]
    os << "["<<v.x<<", "<<v.y<<" ,"<<v.z<<"]";
    return os;
}

EuclideanVector::EuclideanVector(std::initializer_list<double> magnitudes) {
    auto it = magnitudes.begin();
    x = *it++;
    y = *it++;
    z = *it;
}

EuclideanVector crossProduct(const EuclideanVector &v1, const EuclideanVector &v2) {
    auto tmp = EuclideanVector({v1.at(1) * v2.at(2) - v1.at(2) * v2.at(1),
                                v1.at(2) * v2.at(0) - v1.at(0) * v2.at(2),
                                v1.at(0) * v2.at(1) - v1.at(1) * v2.at(0)});
    return tmp;
}

EuclideanVector::EuclideanVector(double xi, double yi, double zi):x(xi),y(yi),z(zi) {

}
