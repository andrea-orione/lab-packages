#pragma once

#include <ostream>
#include <string>
#include <iostream>

/**
 * The foundamental class of the library.
 *
 * Every instance represents a single point of data.
 */
class Datum
{
private:
  /**
   * The best estimate of the Datum.
   */
  double m_value;

  /**
   * The uncertainty of the Datum.
   */
  double m_uncertainty;

public:
  /**
   * Instanciates a void Datum object.
   */
  Datum();

  /**
   * Instanciates a Datum object.
   *
   * This constructor is used for the known values. The
   * uncertainty is set to zero.
   *
   * @param valuep the best estimate of the datum.
   */
  Datum(double value);

  /**
   * Instanciates a Datum object.
   *
   * This constructor should be used for all the data.
   *
   * @param valuep the to be set to the best estimate
   *     of the datum.
   * @param uncertainty the value to be set to the
   *     uncertainty of the datum.
   */
  Datum(double value, double uncertainty);

  /**
   * Get the value of the datum.
   *
   * @returns the value of the best estimate of the datum.
   */
  double get_value() const;

  /**
   * Get the uncertainty of the datum.
   *
   * @returns the value of the uncertainty of the datum.
   */
  double get_uncertainty() const;

  /**
   * Set the value of the best estimate of the datum.
   *
   * @param value the value to be set to the best estimate
   *     of the datum.
   */
  void set_value(double value);

  /**
   * Set the value of the uncertainty of the datum.
   *
   * @param unceartainty the value to be set to the uncertainty
   *     of the datum.
   */
  void set_uncertainty(double uncertainty);

  /**
   * Add two data together.
   *
   * @param other the other datum to be added.
   */
  Datum operator+ (Datum other) const;

  /**
   * Subtract a datum from another.
   *
   * @param other the datum to be subtracted.
   */
  Datum operator- (Datum other) const;

  /**
   * Multiply two data.
   *
   * @param other the datum to be multiplied.
   */
  Datum operator* (Datum other) const;

  /**
   * Divide a datum by another.
   *
   * @param other the datum to be divided by.
   */
  Datum operator/ (Datum other) const;

  /**
   * Add two data together.
   *
   * @param other the other datum to be added.
   * @param quadrature wheter the unceartainties
   *     should be added in quadrature.
   */
  Datum add(Datum other, bool quadrature=false) const;

  /**
   * Subtract a datum from another.
   *
   * @param other the datum to be subtracted.
   * @param quadrature wheter the unceartainties
   *     should be added in quadrature.
   */
  Datum subtract(Datum other, bool quadrature=false) const;

  /**
   * Subtract a datum from another.
   *
   * @param other the datum to be subtracted.
   * @param quadrature wheter the unceartainties
   *     should be added in quadrature.
   */
  Datum multiply(Datum other, bool quadrature=false) const;

  /**
   * Divide a datum by another.
   *
   * @param other the datum to be divided by.
   * @param quadrature wheter the unceartainties
   *     should be added in quadrature.
   */
  Datum divide(Datum other, bool quadrature=false) const;

  bool operator< (Datum other) const;
  bool operator> (Datum other) const;

  /**
   * Return the string representing the datum.
   *
   * This function creates the string representing
   * the datum. It rounds the unceartainty to one
   * significant figure (2 if the penultimate is 1).
   *
   * @return the string representing the datum.
   */
  std::string to_string() const;

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

  /**
   * Perform a Z test to verify the compatibility of two data.
   *
   * @param dato1, dato2 the data to be compared.
   *
   * @returns the p-value of the performed Z test.
   */
  static double normalCompatible(Datum dato1, Datum dato2);

  /**
   * Perform a Z test to verify the compatibility of two data.
   *
   * @param [in] dato1, dato2 the data to be compared.
   * @param [out] z the value of the Z variable calculated.
   *
   * @returns the p-value of the performed Z test.
   */
  static double normalCompatible(Datum dato1, Datum dato2, double& z);

  // static double studentCompatible(Datum, Datum);
  // static double studentCompatible(Datum, Datum, double&);

  /**
   * Calculate the weighted mean of a list of data.
   *
   * @param dataList a pointer to the list of data.
   * @param numData the number of data in the list.
   *
   * @returns the weighted mean as a Datum object.
   */
  static Datum weightedMean(Datum *dataList, int numData);
};


std::ostream& operator<<(std::ostream& stream, const Datum& other);
