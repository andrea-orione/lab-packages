#pragma once

#include <string>

/**
 * The foundamental class of the library.
 *
 * Every instance represents a single point of data.
 */
class Datum
{
private:
  double value;
  double error;
public:
  Datum(double valuep);
  Datum(double valuep, double errorp);

  double get_value();
  double get_error();
  void set_value(double);
  void set_error(double);

  Datum operator+ (Datum other);
  Datum operator- (Datum other);
  Datum operator* (Datum other);
  Datum operator/ (Datum other);

  Datum add(Datum other, bool quadrature=false);
  Datum subtract(Datum other, bool quadrature=false);
  Datum multiply(Datum other, bool quadrature=false);
  Datum divide(Datum other, bool quadrature=false);

  bool operator< (Datum other);
  bool operator> (Datum other);

  std::string to_string();

  static Datum sqrt(Datum dato);
  static Datum cbrt(Datum dato);
  static Datum exp(Datum dato);
  static Datum exp2(Datum dato);
  static Datum log(Datum dato);
  static Datum log10(Datum dato);
  static Datum log2(Datum dato);
  static Datum log(Datum dato, Datum base, bool quadrature=false);
  static Datum log(Datum dato, double base);
  static Datum pow(Datum base, Datum exponent, bool quadrature=false);

  static Datum acos(Datum dato);
  static Datum asin(Datum dato);
  static Datum atan(Datum dato);
  static Datum atan2(Datum opposite, Datum adjacent);
  static Datum cos(Datum dato);
  static Datum sin(Datum dato);
  static Datum tan(Datum dato);

  static Datum degrees(Datum dato);
  static Datum radians(Datum dato);

  static double normalCompatible(Datum dato1, Datum dato2);
  static double normalCompatible(Datum dato1, Datum dato2, double& z);

  // static double studentCompatible(Datum, Datum);
  // static double studentCompatible(Datum, Datum, double&);

  static Datum weightedMean(Datum *dataList, int numData);
};
