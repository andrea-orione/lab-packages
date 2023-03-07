#include <cmath>
#include <cstdlib>
#include <iterator>
#include <math.h>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <iostream>
#include "Datum.h"


Datum::Datum() : m_value(0.), m_uncertainty(0.) {}

Datum::Datum(double value) : m_value(value), m_uncertainty(0.) {}

Datum::Datum(double value, double uncertainty)
  : m_value(value),
    m_uncertainty(std::abs(uncertainty)) {}

double Datum::get_value() const { return m_value; }

double Datum::get_uncertainty() const { return m_uncertainty; }

void Datum::set_value(double value) { m_value = value; }

void Datum::set_uncertainty(double uncertainty) { m_uncertainty = uncertainty; }

Datum Datum::operator+(Datum other) const
{
  return Datum(m_value + other.m_value, m_uncertainty + other.m_uncertainty);
}

Datum Datum::operator-(Datum other) const
{
  return Datum(m_value - other.m_value, m_uncertainty + other.m_uncertainty);
}

Datum Datum::operator*(Datum other) const
{
  return Datum(m_value * other.m_uncertainty,
               m_uncertainty * other.m_value + other.m_uncertainty * m_value);
}

Datum Datum::operator/(Datum other) const
{
  return Datum(m_value/other.m_value,
               m_uncertainty/other.m_value +
               other.m_uncertainty*m_value/(other.m_value*other.m_value));
}

Datum Datum::add(Datum other, bool quadrature) const
{
  if (quadrature)
    return Datum(m_value + other.m_value,
                 std::sqrt(std::pow(m_uncertainty,2) +
                           std::pow(other.m_uncertainty,2)));
  return Datum(m_value + other.m_value, m_uncertainty + other.m_uncertainty);
}

Datum Datum::subtract(Datum other, bool quadrature) const
{
  if (quadrature)
    return Datum(m_value - other.m_value,
                 std::sqrt(std::pow(m_uncertainty,2) +
                           std::pow(other.m_uncertainty,2)));
  return Datum(m_value - other.m_value, m_uncertainty + other.m_uncertainty);
}

Datum Datum::multiply(Datum other, bool quadrature) const
{
  if (quadrature)
    return Datum(m_value * other.m_value,
                 std::sqrt(std::pow(m_uncertainty,2)*std::pow(other.m_value,2) +
                           std::pow(other.m_uncertainty,2)*std::pow(m_value,2)));
  return Datum(m_value * other.m_value,
               m_uncertainty * other.m_value + other.m_uncertainty * m_value);
}

Datum Datum::divide(Datum other, bool quadrature) const
{
  if (quadrature)
    return Datum(m_value / other.m_value,
                 std::sqrt(std::pow(m_uncertainty/other.m_value,2) +
                           std::pow(other.m_uncertainty*m_value,2)/
                           std::pow(other.m_value, 4)));
  return Datum(m_value / other.m_value,
               m_uncertainty/other.m_value +
               other.m_uncertainty*m_value/std::pow(other.m_value, 2));
}

bool Datum::operator<(Datum other) const { return m_value < other.m_value; }

bool Datum::operator>(Datum other) const { return m_value > other.m_value; }

std::string Datum::to_string() const
{
  int magnitude = std::floor(std::log10(m_uncertainty));
  if (std::floor(m_uncertainty/std::pow(10,magnitude)) == 1)
    magnitude --;
  return std::to_string(std::round(m_value/std::pow(10,magnitude))*
                        std::pow(10,magnitude))
    + " +- " + std::to_string(std::round(m_uncertainty/std::pow(10,magnitude))*
                              std::pow(10,magnitude));
}

Datum Datum::sqrt(const Datum& dato)
{
  return Datum(std::sqrt(dato.m_value),
               0.5*dato.m_uncertainty/std::sqrt(dato.m_value));
}

Datum Datum::cbrt(const Datum& dato)
{
  return Datum(std::cbrt(dato.m_uncertainty),
               1./3.*dato.m_uncertainty/std::pow(dato.m_value,2./3.));
}

Datum Datum::exp(const Datum& dato)
{
  return Datum(std::exp(dato.m_value),
               dato.m_uncertainty*std::exp(dato.m_value));
}

Datum Datum::exp2(const Datum& dato)
{
  return Datum(std::exp2(dato.m_value),
               dato.m_uncertainty*std::exp2(dato.m_value)*std::log(dato.m_value));
}

Datum Datum::log(const Datum& dato)
{
  return Datum(std::log(dato.m_value), dato.m_uncertainty/dato.m_value);
}

Datum Datum::log10(const Datum& dato)
{
  return Datum(std::log10(dato.m_value),
               dato.m_uncertainty/(dato.m_value*std::log(10.)));
}

Datum Datum::log2(const Datum& dato)
{
  return Datum(std::log2(dato.m_value),
               dato.m_uncertainty/(dato.m_value*std::log(2.)));
}

Datum Datum::log(const Datum& dato, double base)
{
  return Datum(std::log(dato.m_value)/std::log(base),
               dato.m_uncertainty/(dato.m_value*std::log(base)));
}

Datum Datum::log(const Datum& dato, const Datum& base, bool quadrature)
{
  if (quadrature)
    return Datum(std::log(dato.m_value)/std::log(base.m_value),
                 std::sqrt(std::pow(dato.m_uncertainty/
                                    (dato.m_value*std::log(base.m_value)),2) +
                           std::pow(base.m_uncertainty*std::log(dato.m_value)/
                                    (std::pow(std::log(base.m_value),2)*
                                     base.m_value),2)));
  return Datum(std::log(dato.m_value)/std::log(base.m_value),
               dato.m_uncertainty/(dato.m_value*std::log(base.m_value)) +
               base.m_uncertainty*std::log(dato.m_value)/
               (std::pow(std::log(base.m_value),2) * base.m_value));
}

Datum Datum::pow(const Datum& base, const Datum& exponent, bool quadrature)
{
  if (quadrature)
    return Datum(std::pow(base.m_value, exponent.m_value),
                 std::sqrt(std::pow(base.m_uncertainty*exponent.m_value*
                                    std::pow(base.m_value,exponent.m_value-1),2) +
                           std::pow(exponent.m_uncertainty*std::log(base.m_value)*
                                    std::pow(base.m_value, exponent.m_value),2)));
  return Datum(std::pow(base.m_value, exponent.m_value),
               base.m_uncertainty*exponent.m_value*
               std::pow(base.m_value,exponent.m_value-1) +
               exponent.m_uncertainty*std::log(base.m_value)*
               std::pow(base.m_value, exponent.m_value));
}

Datum Datum::acos(const Datum& dato)
{
  return Datum(std::acos(dato.m_value),
               dato.m_uncertainty/std::sqrt(1-dato.m_value*dato.m_value));
}

Datum Datum::asin(const Datum& dato)
{
  return Datum(std::asin(dato.m_value),
               dato.m_uncertainty/std::sqrt(1-dato.m_value*dato.m_value));
}

Datum Datum::atan(const Datum& dato)
{
  return Datum(std::atan(dato.m_value),
               dato.m_uncertainty/(1+dato.m_value*dato.m_value));
}

Datum Datum::atan2(const Datum& opposite, const Datum& adjacent)
{
  return Datum(std::atan2(opposite.m_value, adjacent.m_value),
               atan(opposite/adjacent).m_uncertainty);
}

Datum Datum::cos(const Datum& dato)
{
  return Datum(std::cos(dato.m_value),
               dato.m_uncertainty*std::sin(dato.m_value));
}

Datum Datum::sin(const Datum& dato)
{
  return Datum(std::sin(dato.m_value),
               dato.m_uncertainty*std::cos(dato.m_value));
}

Datum Datum::tan(const Datum& dato)
{
  return Datum(std::tan(dato.m_value),
               dato.m_uncertainty/std::pow(std::cos(dato.m_value),2));
}

Datum Datum::degrees(const Datum& dato)
{
  return Datum(dato.m_value*360./M_2_PI,
               dato.m_uncertainty*360./M_2_PI);
}

Datum Datum::radians(const Datum& dato)
{
  return Datum(dato.m_value*M_2_PI/360.,
               dato.m_uncertainty*M_2_PI/360.);
}

double Datum::normalCompatible(Datum dato1, Datum dato2)
{
  double z = (dato1.m_value-dato2.m_value)/
    std::sqrt(std::pow(dato1.m_uncertainty,2)+std::pow(dato2.m_uncertainty,2));
  return std::erfc(abs(z*M_SQRT1_2));
}

double Datum::normalCompatible(Datum dato1, Datum dato2, double& z)
{
  z = (dato1.m_value-dato2.m_value)/
    std::sqrt(std::pow(dato1.m_uncertainty,2)+std::pow(dato2.m_uncertainty,2));
  return std::erfc(abs(z*M_SQRT1_2));
}

Datum Datum::weightedMean(Datum *dataList, int numData)
{
  double numerator = 0.;
  double denominator = 0.;
  for (int i = 0; i < numData; i++) {
    numerator += (dataList[i].m_value/(std::pow(dataList[i].m_uncertainty,2)));
    denominator += (1./(std::pow(dataList[i].m_uncertainty,2)));
  }
  return Datum(numerator/denominator, std::sqrt(1./denominator));
}

std::ostream& operator<<(std::ostream& stream, const Datum& other)
{
  stream << other.to_string();
  return stream;
}
