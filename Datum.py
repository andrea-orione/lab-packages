"""The required libraries."""
import math
from scipy.stats import norm


class Datum:
    """
    The foundamental class of the library.

    Every instance represents a single point of data.
    """

    def __init__(self, value, error=0.):
        """
        Initialize the class.

        Parameters:
            value (float): the best esitmate of the data.
            error (float): the uncertainty of the data.
        """
        if not (isinstance(value, (float, int))
                and isinstance(error, (float, int))):
            raise TypeError

        self.value = value
        self.error = abs(error)

    def __add__(self, other, quadrature: bool = False):
        """
        Addition operator.

        This function adds two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to sum.
            quadrature (bool): whether quadrature sum should be used.
        """
        if isinstance(other, (float, int)):
            return Datum(self.value + other, self.error)

        if type(other) != type(self):
            raise TypeError

        if quadrature:
            return Datum(self.value + other.value,
                         math.sqrt(self.error**2 + other.error**2))

        return Datum(self.value + other.value, self.error + other.error)

    def __radd__(self, other, quadrature: bool = False):
        """
        Reversed addition operator.

        This function adds two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to sum.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        return self.__add__(other, quadrature)

    def __sub__(self, other, quadrature: bool = False):
        """
        Subtraction operator.

        This function subtracts two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to subtract.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        if isinstance(other, (float, int)):
            return Datum(self.value - other, self.error)

        if type(other) != type(self):
            raise TypeError

        if quadrature:
            return Datum(self.value - other.value,
                         math.sqrt(self.error**2 + other.error**2))

        return Datum(self.value - other.value, self.error + other.error)

    def __rsub__(self, other, quadrature: bool = False):
        """
        Reversed subtraction operator.

        This function subtracts two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to subtract.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        if isinstance(other, (float, int)):
            other = Datum(other)

        if not isinstance(other, Datum):
            raise TypeError

        return other.__sub__(self, quadrature)

    def __mul__(self, other, quadrature: bool = False):
        """
        Multiplication operator.

        This function multiplies two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to multiply.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        if isinstance(other, (float, int)):
            return Datum(self.value * other, self.error * abs(other))

        if not isinstance(other, Datum):
            raise TypeError

        if quadrature:
            return Datum(self.value * other.value,
                         math.sqrt((self.error*other.value)**2
                                   + (self.value*other.error)**2))

        return Datum(self.value * other.value,
                     self.error*other.value + self.value*other.error)

    def __rmul__(self, other, quadrature: bool = False):
        """
        Reversed multiplication operator.

        This function multiplies two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to multiply.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        return self.__mul__(other, quadrature)

    def __truediv__(self, other, quadrature: bool = False):
        """
        Division operator.

        This function divides two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to divide.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        if isinstance(other, (float, int)):
            return Datum(self.value / other, self.error / abs(other))

        if not isinstance(other, Datum):
            raise TypeError

        if quadrature:
            return Datum(self.value / other.value,
                         math.sqrt((self.error/other.value)**2
                                   + (other.error*self.value/other.value**2)**2
                                   ))

        return Datum(self.value / other.value,
                     self.error/other.value +
                     other.error*self.value/other.value**2)

    def __rtruediv__(self, other, quadrature: bool = False):
        """
        Reversed division operator.

        This function multiplies two data propagating the unceartainty.
        If quadrature is set to true, to propagate the error the quadrature sum
        will be used.

        Parameters:
            other (Datum): the other Datum to multiply.
            quadrature (bool, default False): whether quadrature sum should be
                used.
        """
        if isinstance(other, (float, int)):
            other = Datum(other)

        if not isinstance(other, Datum):
            raise TypeError

        return other.__truediv__(self, quadrature)

    def __repr__(self):
        """
        Represent the datum.

        This function creates a string representing the object.
        """
        magnitude = math.floor(math.log10(self.error))
        if self.error//(10**magnitude) == 1:
            magnitude -= 1
        return str(round(self.value/(10**magnitude))*(10**magnitude)) + " +- "\
            + str(round(self.error/(10**magnitude))*(10**magnitude))

    def __str__(self):
        """
        Convert the datum into a string.

        This function creates a string representing the object.
        """
        return self.__repr__()

    def __lt__(self, other):
        """Less than operator."""
        if isinstance(other, (float, int)):
            return self.value.__lt__(other)

        if not isinstance(other, Datum):
            raise TypeError

        return self.value.__lt__(other.value)

    def __gt__(self, other):
        """Greater than operator."""
        if isinstance(other, (float, int)):
            return self.value.__gt__(other)

        if not isinstance(other, Datum):
            raise TypeError

        return self.value.__gt__(other.value)

    @staticmethod
    def sqrt(datum):
        """
        Calculate the square root of the datum.

        This function calculates the square root propagating the error.

        Parameters:
            datum (Datum): the datum to be taken the square root.
        """
        if isinstance((datum), (float, int)):
            return math.sqrt(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.sqrt(datum.value),
                     0.5*datum.error/math.sqrt(datum.value))

    @staticmethod
    def cbrt(datum):
        """
        Calculate the cube root of datum.

        Parameters:
            datum (Datum): the datum to be taken the cube root.
        """
        if isinstance((datum), (float, int)):
            return math.cbrt(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.cbrt(datum.value),
                     1/3*datum.error/math.cbrt(datum.value**2))

    @staticmethod
    def exp(datum):
        """
        Return e raised to the power x.

        Parameters:
            datum (Datum): the datum to be taken the exponential.
        """
        if isinstance((datum), (float, int)):
            return math.exp(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.exp(datum.value),
                     datum.error*math.exp(datum.value))

    @staticmethod
    def exp2(datum):
        """
        Return 2 raised to the power x.

        Parameters:
            datum (Datum): the datum to be taken the exponential.
        """
        if isinstance((datum), (float, int)):
            return math.exp2(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.exp2(datum.value),
                     datum.error*math.exp2(datum.value)*math.log(datum.value))

    @staticmethod
    def log(datum, base=False):
        """
        Return the logarithm of x.

        This function returns the natural logarithm of a value x if the base is
        not given.
        If the base is given, it returns the logarithm of x in the given base.

        Parameters:
            datum (Datum): the datum to be taken the logarithm.
            base (float, default=False): if given, the base of the logarithm.
        """
        if isinstance((datum), (float, int)):
            if base:
                return math.log(datum, base)
            return math.log(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        if base:
            return Datum(math.log(datum.value, base),
                         datum.error*(datum.value*math.log(base)))
        return Datum(math.log(datum.value),
                     datum.error*(datum.value))

    @staticmethod
    def log2(datum):
        """
        Return the logarithm of x in base 2.

        Parameters:
            datum (Datum): the datum to be taken the logarithm.
        """
        if isinstance((datum), (float, int)):
            return math.log2(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.log2(datum.value),
                     datum.error*(datum.value*math.log(2.0)))

    @staticmethod
    def log10(datum):
        """
        Return the logarithm of x in base 10.

        Parameters:
            datum (Datum): the datum to be taken the logarithm.
        """
        if isinstance((datum), (float, int)):
            return math.log10(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.log10(datum.value),
                     datum.error*(datum.value*math.log(10.0)))

    @staticmethod
    def pow(base, exponent):
        """
        Return the logarithm of x in base 10.

        Parameters:
            datum (Datum): the datum to be taken the logarithm.
        """
        if isinstance(base, (float, int)) and\
           isinstance(exponent, (float, int)):
            return math.pow(base, exponent)

        if isinstance(base, (float, int)):
            base = Datum(base)

        if isinstance(exponent, (float, int)):
            exponent = Datum(exponent)

        if not (isinstance(base, Datum) and isinstance(exponent, Datum)):
            raise TypeError

        return Datum(math.pow(base.value, exponent.value),
                     base.error * exponent.value * math.pow(base.value,
                                                            exponent.value-1)
                     + exponent.error * math.log(exponent.value)
                     * math.pow(base.value, exponent.value))

    @staticmethod
    def acos(datum):
        """
        Calculate the arcocosine of the datum.

        Parameters:
            datum (Datum): the datum to be taken the arcocosine.
        """
        if isinstance((datum), (float, int)):
            return math.acos(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.acos(datum.value),
                     datum.error/math.sqrt(1-datum.value**2))

    @staticmethod
    def asin(datum):
        """
        Calculate the arcosine of the datum.

        Parameters:
            datum (Datum): the datum to be taken the arcosine.
        """
        if isinstance((datum), (float, int)):
            return math.asin(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.asin(datum.value),
                     datum.error/math.sqrt(1-datum.value**2))

    @staticmethod
    def atan(datum):
        """
        Calculate the arcotangent of the datum.

        Parameters:
            datum (Datum): the datum to be taken the arcotangent.
        """
        if isinstance((datum), (float, int)):
            return math.atan(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.atan(datum.value),
                     datum.error/(1+datum.value**2))

    @staticmethod
    def cos(datum):
        """
        Calculate the cosine of the datum.

        Parameters:
            datum (Datum): the datum to be taken the cosine.
        """
        if isinstance((datum), (float, int)):
            return math.cos(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.cos(datum.value),
                     datum.error*math.sin(datum.value))

    @staticmethod
    def sin(datum):
        """
        Calculate the sine of the datum.

        Parameters:
            datum (Datum): the datum to be taken the sine.
        """
        if isinstance((datum), (float, int)):
            return math.sin(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.sin(datum.value),
                     datum.error*math.cos(datum.value))

    @staticmethod
    def tan(datum):
        """
        Calculate the tangent of the datum.

        Parameters:
            datum (Datum): the datum to be taken the tangent.
        """
        if isinstance((datum), (float, int)):
            return math.tan(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.tan(datum.value),
                     datum.error/math.cos(datum.value)**2)

    @staticmethod
    def degrees(datum):
        """
        Convert datum in degrees.

        Parameters:
            datum (Datum): the datum to be converted.
        """
        if isinstance((datum), (float, int)):
            return math.degrees(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.degrees(datum.value), math.degrees(datum.error))

    @staticmethod
    def radians(datum):
        """
        Convert datum in radians.

        Parameters:
            datum (Datum): the datum to be converted.
        """
        if isinstance((datum), (float, int)):
            return math.radians(datum)

        if not isinstance(datum, Datum):
            raise TypeError

        return Datum(math.radians(datum.value), math.radians(datum.error))

    @staticmethod
    def normal_compatible(datum1, datum2, Z: bool = False):
        """
        Perform a normal test.

        This function checks if two data are compatible performing a normal
        test.

        Parameters:
            datum1 (Datum): the first datum.
            datum2 (Datum): the second datum.
            Z (bool, default=False): whether the function should return
                                     also the value of the normal variable.

        Returs:
            pVal (float): the p-value of the result.
            Z (float, optional): the value of the normal variable.
        """
        ZVal = (datum1.value-datum2.value)/math.sqrt(datum1.error**2
                                                     + datum2.error**2)
        pVal = norm.cdf(-abs(ZVal))*2

        if Z:
            return pVal, ZVal
        return pVal

    @staticmethod
    def student_compatible(datum1, datum2, t: bool = False):
        """
        Perform a student test.

        This function checks if two data are compatible performing a student
        test.

        Parameters:
            datum1 (Datum): the first datum.
            datum2 (Datum): the second datum.
            t (bool, default=False): whether the function should return
                                     also the value of the student variable.

        Returs:
            pVal (float): the p-value of the result.
            t (float, optional): the value of the student variable.
        """
        tVal = (datum1.value-datum2.value)/math.sqrt(datum1.error**2
                                                     + datum2.error**2)
        pVal = norm.cdf(-abs(tVal))*2

        if t:
            return pVal, tVal
        return pVal

    @staticmethod
    def weighted_mean(data_list):
        """
        Return the weighted mean of some data.

        This function calculates the weighted mean of some data given
        inside a list. The mean is than returned as a Datum object.

        Parameters:
            data_list ([Datum]): the list of data to be meaned.
        """
        num = 0
        den = 0
        for i in data_list:
            num += (i.value/(i.error**2))
            den += (1/(i.error**2))
        return Datum(num/den, math.sqrt(1/den))


if __name__ == "__main__":
    print("Hi, this is the foundamental class of the library.\n\
           It is used to represent data as an object containing both the\
           value and the uncertainty.\n\
           It also provides some basic mathematical operation (+ - etc.)\
           and some more advanced ones (sin, cos, sqrt, pow, etc.). ")
