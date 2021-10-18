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

    EuclideanVector(double x, double y, double z);

    EuclideanVector();

    constexpr EuclideanVector(const std::initializer_list<double> &);

    constexpr EuclideanVector(const EuclideanVector &);

    ~EuclideanVector() = default;

    // Operators
    EuclideanVector &operator=(const EuclideanVector &);

    double &operator[](const int &);

    const double &operator[](const int &) const;

    EuclideanVector &operator+=(const EuclideanVector &);

    EuclideanVector &operator-=(const EuclideanVector &);

    EuclideanVector &operator*=(const double &);

    EuclideanVector &operator/=(const double &);

    explicit operator std::vector<double>() const;

    // Methods
    [[nodiscard]] double at(const int &) const;

    double &at(const int &);

    [[nodiscard]] double GetEuclideanNorm() const;

    [[nodiscard]] EuclideanVector CreateUnitVector() const;

    // Friends
    friend bool operator==(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector crossProduct(const EuclideanVector &, const EuclideanVector &);

    friend bool operator!=(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator+(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator-(const EuclideanVector &, const EuclideanVector &);

    friend double operator*(const EuclideanVector &, const EuclideanVector &);

    friend EuclideanVector operator/(const EuclideanVector &, const double &);

    friend EuclideanVector operator*(const EuclideanVector &, const double &);

    friend EuclideanVector operator*(const double &, const EuclideanVector &);

    friend std::ostream &operator<<(std::ostream &, const EuclideanVector &);

private:
    double x;
    double y;
    double z;
};

#endif //TUMORSIMULATION_EUCLIDEANVECTOR_H
