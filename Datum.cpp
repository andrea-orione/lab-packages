#include <cmath>
#include <cstdlib>
#include <iterator>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include "Datum.h"


Datum::Datum(double valuep) : value(valuep), error(0.) {}

Datum::Datum(double valuep, double errorp)
  : value(valuep),
    error(std::abs(errorp)) {}

double Datum::get_value() { return value; }

double Datum::get_error() { return error; }

void Datum::set_value(double valuep) { value = valuep; }

void Datum::set_error(double errorp) { error = errorp; }

Datum Datum::operator+(Datum other)
{
  return Datum(value + other.value, error + other.error);
}

Datum Datum::operator-(Datum other)
{
  return Datum(value - other.value, error + other.error);
}

Datum Datum::operator*(Datum other)
{
  return Datum(value * other.value, error * other.value + other.error * value);
}

Datum Datum::operator/(Datum other)
{
  return Datum(value/other.value,
               error/other.value + other.error*value/(other.value*other.value));
}

Datum Datum::add(Datum other, bool quadrature)
{
  if (quadrature)
    return Datum(value + other.value,
                 std::sqrt(error*error + other.error*other.error));
  return Datum(value + other.value, error + other.error);
}

Datum Datum::subtract(Datum other, bool quadrature)
{
  if (quadrature)
    return Datum(value - other.value,
                 std::sqrt(error * error + other.error * other.error));
  return Datum(value - other.value, error + other.error);
}

Datum Datum::multiply(Datum other, bool quadrature)
{
  if (quadrature)
    return Datum(value * other.value,
                 std::sqrt(error*error*other.value*other.value +
                           other.error*other.error*value*value));
  return Datum(value * other.value, error * other.value + other.error * value);
}

Datum Datum::divide(Datum other, bool quadrature)
{
  if (quadrature)
    return Datum(value / other.value,
                 std::sqrt(std::pow(error/other.value,2) +
                           std::pow(other.error*value,2)/std::pow(other.value, 4)));
  return Datum(value / other.value,
               error/other.value + other.error*value/std::pow(other.value, 2));
}

bool Datum::operator<(Datum other) { return value < other.value; }

bool Datum::operator>(Datum other) { return value > other.value; }

std::string Datum::to_string()
{
  int magnitude = std::floor(std::log10(error));
  if (std::floor(error/std::pow(10,magnitude)) == 1)
    magnitude --;
  return std::to_string(std::round(value/std::pow(10,magnitude))*std::pow(10,magnitude))
    + " +- " + std::to_string(std::round(error/std::pow(10,magnitude))*std::pow(10,magnitude));
}

Datum Datum::sqrt(Datum dato)
{
  return Datum(std::sqrt(dato.value),
               0.5*dato.error/std::sqrt(dato.value));
}

Datum Datum::cbrt(Datum dato)
{
  return Datum(std::cbrt(dato.value),
               1./3.*dato.error/std::cbrt(dato.value*dato.value));
}

Datum Datum::exp(Datum dato)
{
  return Datum(std::exp(dato.value),
               dato.error*std::exp(dato.value));
}

Datum Datum::exp2(Datum dato)
{
  return Datum(std::exp2(dato.value),
               dato.error*std::exp2(dato.value)*std::log(dato.value));
}

Datum Datum::log(Datum dato)
{
  return Datum(std::log(dato.value), dato.error/dato.value);
}

Datum Datum::log10(Datum dato)
{
  return Datum(std::log10(dato.value), dato.error/(dato.value*std::log(10.)));
}

Datum Datum::log2(Datum dato)
{
  return Datum(std::log2(dato.value), dato.error/(dato.value*std::log(2.)));
}

Datum Datum::log(Datum dato, double base)
{
  return Datum(std::log(dato.value)/std::log(base),
               dato.error/(dato.value*std::log(base)));
}

Datum Datum::log(Datum dato, Datum base, bool quadrature)
{
  if (quadrature)
    return Datum(std::log(dato.value)/std::log(base.value),
                 std::sqrt(std::pow(dato.error/(dato.value*std::log(base.value)),2)
                           + std::pow(base.error*std::log(dato.value)
                                      /(std::pow(std::log(base.value),2)
                                        *base.value),2)));
  return Datum(std::log(dato.value)/std::log(base.value),
               dato.error/(dato.value*std::log(base.value))
               + base.error*std::log(dato.value)/(std::pow(std::log(base.value),2)
                                                  *base.value));
}

Datum Datum::pow(Datum base, Datum exponent, bool quadrature)
{
  if (quadrature)
    return Datum(std::pow(base.value, exponent.value),
                 std::sqrt(std::pow(base.error*exponent.value*std::pow(base.value,exponent.value-1),2) +
                           std::pow(exponent.error*std::log(base.value)*std::pow(base.value, exponent.value),2)));
  return Datum(std::pow(base.value, exponent.value),
                 base.error*exponent.value*std::pow(base.value,exponent.value-1) +
                 exponent.error*std::log(base.value)*std::pow(base.value, exponent.value));
}

Datum Datum::acos(Datum dato)
{
  return Datum(std::acos(dato.value),
               dato.error/std::sqrt(1-dato.value*dato.value));
}

Datum Datum::asin(Datum dato)
{
  return Datum(std::asin(dato.value),
               dato.error/std::sqrt(1-dato.value*dato.value));
}

Datum Datum::atan(Datum dato)
{
  return Datum(std::atan(dato.value),
               dato.error/(1+dato.value*dato.value));
}

Datum Datum::atan2(Datum opposite, Datum adjacent)
{
  return Datum(std::atan2(opposite.value, adjacent.value),
               atan(opposite/adjacent).error);
}

Datum Datum::cos(Datum dato)
{
  return Datum(std::cos(dato.value),
               dato.error*std::sin(dato.value));
}

Datum Datum::sin(Datum dato)
{
  return Datum(std::sin(dato.value),
               dato.error*std::cos(dato.value));
}

Datum Datum::tan(Datum dato)
{
  return Datum(std::tan(dato.value),
               dato.error/std::pow(std::cos(dato.value),2));
}

Datum Datum::degrees(Datum dato)
{
  return Datum(dato.value*360./M_2_PI,
               dato.error*360./M_2_PI);
}

Datum Datum::radians(Datum dato)
{
  return Datum(dato.value*M_2_PI/360.,
               dato.error*M_2_PI/360.);
}

double Datum::normalCompatible(Datum dato1, Datum dato2)
{
  double z = (dato1.value-dato2.value)/
    std::sqrt(dato1.error*dato1.error+dato2.error*dato2.error);
  return std::erfc(abs(z*M_SQRT1_2));
}

double Datum::normalCompatible(Datum dato1, Datum dato2, double& z)
{
  z = (dato1.value-dato2.value)/
    std::sqrt(dato1.error*dato1.error+dato2.error*dato2.error);
  return std::erfc(abs(z*M_SQRT1_2));
}

Datum Datum::weightedMean(Datum *dataList, int numData)
{
  double numerator = 0.;
  double denominator = 0.;
  for (int i = 0; i < numData; i++) {
    numerator += (dataList[i].value/(dataList[i].error*dataList[i].error));
    denominator += (1./(dataList[i].error*dataList[i].error));
  }
  return Datum(numerator/denominator, std::sqrt(1./denominator));
}
