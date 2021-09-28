//
// Created by florian on 9/20/21.
//

#include "EuclideanVector.h"

#include <algorithm>
#include <iostream>
#include <utility>

// Constructor for one arg (int): Initialises an EV of size 'int', with magnitudes 0
EuclideanVector::EuclideanVector(const int &size) {
    size_ = size;
    magnitudes_ = std::make_unique<double[]>(size);
    for (int i = 0; i <= size; i++) {
        magnitudes_[i] = 0;
    }
}

// Constructor for two args (int, double): Initialises an EV of size 'int', with magnitudes 'double'
EuclideanVector::EuclideanVector(const int &size, const double &magnitudes) {
    size_ = size;
    magnitudes_ = std::make_unique<double[]>(size);
    for (int i = 0; i <= size; i++) {
        magnitudes_[i] = magnitudes;
    }
}

// Constructor for lists: Initialises an EV with the same specifications as that of the list
EuclideanVector::EuclideanVector(const std::vector<double>::iterator &begin,
                                 const std::vector<double>::iterator &end) {
    size_ = end - begin;
    magnitudes_ = std::make_unique<double[]>(size_);
    int counter = 0;
    for (auto i = begin; i != end; ++i) {
        magnitudes_[counter] = *i;
        ++counter;
    }
}

// Copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector &copy) {
    size_ = copy.size_;
    magnitudes_ = std::make_unique<double[]>(size_);
    for (int i = 0; i < copy.size_; ++i) {
        magnitudes_[i] = copy.magnitudes_[i];
    }
}

// Move constructor
EuclideanVector::EuclideanVector(EuclideanVector &&o) noexcept
        : magnitudes_{std::move(o.magnitudes_)}, size_{o.size_} {
    o.size_ = 0;
}

// Copy assignment
EuclideanVector &EuclideanVector::operator=(const EuclideanVector &o) {
    size_ = o.size_;
    magnitudes_ = std::make_unique<double[]>(size_);
    for (int i = 0; i < o.size_; ++i) {
        magnitudes_[i] = o.magnitudes_[i];
    }
    return *this;
}

// Move assignment
EuclideanVector &EuclideanVector::operator=(EuclideanVector &&o) noexcept {
    magnitudes_ = std::move(o.magnitudes_);
    size_ = o.size_;
    o.size_ = 0;
    return *this;
}

// Subscript operator
double &EuclideanVector::operator[](const int &i) {
    return magnitudes_[i];
}

// Subscript operator for a const EV
const double &EuclideanVector::operator[](const int &i) const {
    return magnitudes_[i];
}

// Addition (+=) operator
EuclideanVector &EuclideanVector::operator+=(const EuclideanVector &o) {
    if (this->size_ != o.size_) {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->size_) + ") and RHS(" +
                                   std::to_string(o.size_) + ") do not match");
    }
    for (int i = 0; i < size_; ++i) {
        this->magnitudes_[i] += o.magnitudes_[i];
    }
    return *this;
}

// Subtraction (-=) operator
EuclideanVector &EuclideanVector::operator-=(const EuclideanVector &o) {
    if (this->size_ != o.size_) {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->size_) + ") and RHS(" +
                                   std::to_string(o.size_) + ") do not match");
    }
    for (int i = 0; i < size_; ++i) {
        this->magnitudes_[i] -= o.magnitudes_[i];
    }
    return *this;
}

// Multiplication (*=) operator
EuclideanVector &EuclideanVector::operator*=(const double &multiplier) {
    for (int i = 0; i < this->size_; ++i) {
        this->magnitudes_[i] *= multiplier;
    }
    return *this;
}

// Division (/=) operator
EuclideanVector &EuclideanVector::operator/=(const int &divider) {
    if (divider == 0) {
        throw EuclideanVectorError("Invalid vector division by 0");
    }
    for (int i = 0; i < this->size_; ++i) {
        this->magnitudes_[i] /= divider;
    }
    return *this;
}

// EV -> vector<double> typecast
EuclideanVector::operator std::vector<double>() const {
    std::vector<double> returnVector(this->size_);
    for (int i = 0; i < this->size_; ++i) {
        returnVector[i] = magnitudes_[i];
    }
    return returnVector;
}

// EV -> list<double> typecast
EuclideanVector::operator std::list<double>() const {
    std::list<double> returnList;
    for (int i = 0; i < this->size_; ++i) {
        returnList.push_back(magnitudes_[i]);
    }
    return returnList;
}

// Magnitude in dimension as a double
double EuclideanVector::at(const int &place) const {
    if (place < 0 || place >= this->size_) {
        throw EuclideanVectorError("Index " + std::to_string(place) +
                                   " is not valid for this EuclideanVector object");
    }
    return magnitudes_[place];
}

// Magnitude in dimension as a reference
double &EuclideanVector::at(const int &place) {
    if (place < 0 || place >= this->size_) {
        throw EuclideanVectorError("Index " + std::to_string(place) +
                                   " is not valid for this EuclideanVector object");
    }
    return magnitudes_[place];
}

// size_ getter
int EuclideanVector::GetNumDimensions() const {
    return size_;
}

// Calculates EV's Euclidean normal
double EuclideanVector::GetEuclideanNorm() const {
    if (this->GetNumDimensions() == 0) {
        throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
    }
    double returnValue = 0;
    for (int i = 0; i < size_; ++i) {
        returnValue += (magnitudes_[i]) * (magnitudes_[i]);
    }
    return std::sqrt(returnValue);
}

// Calculates EV's unit vector
EuclideanVector EuclideanVector::CreateUnitVector() const {
    if (this->GetNumDimensions() == 0) {
        throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
    }

    if (this->GetEuclideanNorm() == 0) {
        throw EuclideanVectorError(
                "EuclideanVector with euclidean normal of 0 does not have a unit vector");
    }
    std::vector<double> preVector(this->size_);
    double eucNorm = this->GetEuclideanNorm();
    for (int i = 0; i < size_; ++i) {
        preVector[i] = magnitudes_[i] / eucNorm;
    }
    EuclideanVector resultVector{preVector.begin(), preVector.end()};
    return resultVector;
}

// Friends
// Equals to operator
bool operator==(const EuclideanVector &v1, const EuclideanVector &v2) {
    if (v1.size_ != v2.size_)
        return false;

    for (int i = 0; i < v1.size_; ++i) {
        if (v1.magnitudes_[i] != v2.magnitudes_[i])
            return false;
    }
    return true;
}

// Not equals to operator
bool operator!=(const EuclideanVector &v1, const EuclideanVector &v2) {
    if (v1.size_ != v2.size_)
        return true;

    for (int i = 0; i < v1.size_; ++i) {
        if (v1.magnitudes_[i] != v2.magnitudes_[i])
            return true;
    }
    return false;
}

// Subtraction operator
EuclideanVector operator+(const EuclideanVector &v1, const EuclideanVector &v2) {
    if (v1.size_ != v2.size_) {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(v1.size_) + ") and RHS(" +
                                   std::to_string(v2.size_) + ") do not match");
    }
    // Use a copy constructor here
    EuclideanVector result{v1};
    result += v2;
    return result;
}

// Subtraction operator
EuclideanVector operator-(const EuclideanVector &v1, const EuclideanVector &v2) {
    if (v1.size_ != v2.size_) {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(v1.size_) + ") and RHS(" +
                                   std::to_string(v2.size_) + ") do not match");
    }
    // Use a copy constructor here
    EuclideanVector result{v1};
    result -= v2;
    return result;
}

// Multiplication (Dot product) operator
double operator*(const EuclideanVector &v1, const EuclideanVector &v2) {
    if (v1.size_ != v2.size_) {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(v1.size_) + ") and RHS(" +
                                   std::to_string(v2.size_) + ") do not match");
    }
    int size = v1.size_;
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += (v1.magnitudes_[i] * v2.magnitudes_[i]);
    }
    return result;
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
EuclideanVector operator/(const EuclideanVector &v1, const int &dividedBy) {
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
    os << "[";
    for (int i = 0; i < v.size_; ++i) {
        os << v.magnitudes_[i];
        if (i != v.size_ - 1) {
            os << " ";
        }
    }
    os << "]";
    return os;
}

EuclideanVector::EuclideanVector(std::initializer_list<double> magnitudes, const int &size) {
    size_ = size;
    magnitudes_ = std::make_unique<double[]>(size);
    int i = 0;
    for (const auto &magnitude: magnitudes) {
        magnitudes_[i] = magnitude;
        i++;
    }
}

EuclideanVector crossProduct(const EuclideanVector &v1, const EuclideanVector &v2) {
    std::cout<<v1<<" "<<v2<<std::endl;
    auto tmp = EuclideanVector({v1.at(1) * v2.at(2) - v1.at(2) * v2.at(1),
                            v1.at(2) * v2.at(0) - v1.at(0) * v2.at(2),
                            v1.at(0) * v2.at(1) - v1.at(1) * v2.at(0)});
    return tmp;
}
