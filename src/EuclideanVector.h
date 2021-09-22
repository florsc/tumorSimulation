//
// Created by florian on 9/20/21.
//

#ifndef TUMORSIMULATION_EUCLIDEANVECTOR_H
#define TUMORSIMULATION_EUCLIDEANVECTOR_H


#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
public:
    explicit EuclideanVectorError(const std::string &ErrorException) : ErrorException_(ErrorException) {}

    const char *ErrorException() const noexcept { return ErrorException_.c_str(); }

private:
    std::string ErrorException_;
};

class EuclideanVector {
public:
    // Constructors
    explicit EuclideanVector(const int &);

    explicit EuclideanVector(std::initializer_list<double>, const int &size = 3);

    explicit EuclideanVector(const int &, const double &);

    explicit EuclideanVector(const std::vector<double>::iterator &,
                             const std::vector<double>::iterator &);

    EuclideanVector(const EuclideanVector &);

    EuclideanVector(EuclideanVector &&) noexcept;

    // Destructor (is this correct?)
    ~EuclideanVector() = default;

    // Operators
    EuclideanVector &operator=(const EuclideanVector &);

    EuclideanVector &operator=(EuclideanVector &&) noexcept;

    double &operator[](const int &);

    const double &operator[](const int &) const;

    EuclideanVector &operator+=(const EuclideanVector &);

    EuclideanVector &operator-=(const EuclideanVector &);

    EuclideanVector &operator*=(const double &);

    EuclideanVector &operator/=(const int &);

    explicit operator std::vector<double>() const;

    explicit operator std::list<double>() const;

    // Methods
    double at(const int &) const;

    double &at(const int &);

    int GetNumDimensions() const;

    double GetEuclideanNorm() const;

    EuclideanVector CreateUnitVector() const;

    // Friends
    friend bool operator==(const EuclideanVector &, const EuclideanVector &);

    friend bool operator!=(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator+(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator-(const EuclideanVector &, const EuclideanVector &);

    friend double operator*(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator/(const EuclideanVector &, const int &);

    friend EuclideanVector operator*(const EuclideanVector &, const double &);

    friend EuclideanVector operator*(const double &, const EuclideanVector &);

    friend std::ostream &operator<<(std::ostream &, const EuclideanVector &);

private:
    std::unique_ptr<double[]> magnitudes_;
    int size_;
};

#endif //TUMORSIMULATION_EUCLIDEANVECTOR_H
