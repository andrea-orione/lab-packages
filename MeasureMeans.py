"""Importing the Datum class."""
from Datum import Datum


# Agilent U1731A
def agilentU1731A_resistance(R, freq=1e3):
    """
    Return the resistance Datum measured whith the Agilent RLC bridge.

    Parameters:
        R (float): the value of the resistance.
        freq (float): the frequency at which was taken the measure.
    """
    if not (freq == 1e3 or freq == 120):
        raise ValueError("Invalid frequency error.")
    if (R < 20):
        sR = 1.2*R/100. + 40e-3
    elif (R < 200):
        sR = 0.8*R/100. + 5e-2
    elif (R < 2e3):
        sR = 0.5*R/100. + 3e-1
    elif (R < 20e3):
        sR = 0.5*R/100. + 3.
    elif (R < 200e3):
        sR = 0.5*R/100. + 30.
    elif (R < 2e6):
        sR = 0.5*R/100. + 5e2
    elif (R < 10e6):
        sR = 2.*R/100. + 8e3
    else:
        raise ValueError("Invalid value of R. Exceedes the range.")
    return Datum(R, sR)


def agilentU1731A_capacitance(C, freq=1e3):
    """
    Return the capacitance Datum measured whith the Agilent RLC bridge.

    Parameters:
        C (float): the value of the capacitance.
        freq (float): the frequency at which was taken the measure.
    """
    if freq == 1e3:
        factor = 1
    elif freq == 120:
        factor = 10
    else:
        raise ValueError("Invalid frequency value.")
    if (C < 2e-9*factor):
        sC = 1.*C/100. + 5e-13
    elif (C < 20e-9*factor):
        sC = 0.7*C/100. + 5e-12
    elif (C < 200e-9*factor):
        sC = 0.7*C/100. + 3e-11
    elif (C < 2e-6*factor):
        sC = 0.7*C/100. + 3e-10
    elif (C < 20e-6*factor):
        sC = 0.7*C/100. + 3e-9
    elif (freq == 1e3 and C < 200e-6) or (freq == 120e3 and C < 1e-3):
        sC = 1.*C/100. + 5e-8
    elif (freq == 1e3 and C < 1e-3) or (freq == 120e3 and C < 10e-3):
        sC = 3.*C/100. + 5e-6
    else:
        return ValueError("Invalid value of C. Exceedes the range.")
    return Datum(C, sC)


def agilentU1731A_inductance(L, freq=1e3):
    """
    Return the inductance Datum measured whith the Agilent RLC bridge.

    Parameters:
        L (float): the value of the inductance.
        freq (float): the frequency at which was taken the measure.
    """
    if freq == 1e3:
        factor = 1
    elif freq == 120:
        factor = 10
    else:
        raise ValueError("Invalid frequency value.")
    if (L < 2e-3*factor):
        sL = 2.*L/100. + 1e7*L*L/1e6 + 5e-7
    elif (L < 20e-3*factor):
        sL = 1.*L/100. + 1e6*L*L/1e6 + 5e-6
    elif (L < 200e-3*factor):
        sL = 0.7*L/100. + 1e5*L*L/1e6 + 5e-5
    elif (L < 2*factor):
        sL = 0.7*L/100. + 1e4*L*L/1e6 + 5e-4
    elif (L < 20*factor):
        sL = 0.7*L/100. + 1e3*L*L/1e6 + 5e-3
    elif (L < 100*factor):
        sL = 1.*L/100. + 1e2*L*L/1e6 + 5e-2
    else:
        raise ValueError("Invalid value of L. Exceedes the range.")
    return Datum(L, sL)


# Keysight U1733C
def keysightU1733C_resistance(R, freq=1e3):
    """
    Return the resistance Datum measured whith the Keysight RLC bridge.

    Parameters:
        R (float): the value of the resistance.
        freq (float): the frequency at which was taken the measure.
    """
    if (freq == 100 or freq == 120 or freq == 1e3):
        status = 0
    elif freq == 10e3:
        status = 1
    elif freq == 100e3:
        status == 2
    else:
        raise ValueError("Invalid frequency value")

    if (R < 2):
        if status == 2:
            sR = 1.0*R/100. + 50e-4
        else:
            sR = 0.7*R/100. + 50e-4
    elif (R < 20):
        sR = 0.7*R/100. + 8e-3
    elif (R < 200):
        if status == 2:
            sR = 0.5*R/100. + 5e-2
        else:
            sR = 0.2*R/100. + 3e-2
    elif (R < 2e3):
        if status == 2:
            sR = 0.5*R/100. + 5e-1
        else:
            sR = 0.2*R/100. + 3e-1
    elif (R < 20e3):
        if status == 2:
            sR = 0.5*R/100. + 5.
        else:
            sR = 0.2*R/100. + 3.
    elif (R < 200e3):
        if status == 2:
            sR = 0.7*R/100. + 80.
        else:
            sR = 0.5*R/100. + 50.
    elif (R < 2e6):
        if status == 0:
            sR = 0.5*R/100. + 5e2
        elif status == 1:
            sR = 0.7*R/100. + 5e2
        else:
            raise ValueError("Invalid value of R.\
                              Exceedes the range for this frequency.")
    elif (R < 20e6):
        if status == 0:
            sR = 2.*R/100. + 8e3
        elif status == 1:
            sR = 5.*R/100. + 8e3
        else:
            raise ValueError("Invalid value of R.\
                              Exceedes the range for this frequency.")
    elif (R < 200e6):
        if status == 0:
            sR = 6.*R/100. + 80e4
        else:
            raise ValueError("Invalid value of R.\
                              Exceedes the range for this frequency.")
    else:
        raise ValueError("Invalid value of R. Exceedes the range.")
    return Datum(R, sR)


def keysightU1733C_capacitance(C, freq=1e3):
    """
    Return the capacitance Datum measured whith the Keysight RLC bridge.

    Parameters:
        C (float): the value of the capacitance.
        freq (float): the frequency at which was taken the measure.
    """
    if freq == 1e3:
        factor = 1
    elif freq == 120e3:
        factor = 10
    else:
        raise ValueError("Invalid frequency value.")
    if (C < 2e-9*factor):
        sC = 1.*C/100. + 5e-13
    elif (C < 20e-9*factor):
        sC = 0.7*C/100. + 5e-12
    elif (C < 200e-9*factor):
        sC = 0.7*C/100. + 3e-11
    elif (C < 2e-6*factor):
        sC = 0.7*C/100. + 3e-10
    elif (C < 20e-6*factor):
        sC = 0.7*C/100. + 3e-9
    elif (freq == 1e3 and C < 200e-6) or (freq == 120e3 and C < 1e-3):
        sC = 1.*C/100. + 5e-8
    elif (freq == 1e3 and C < 1e-3) or (freq == 120e3 and C < 10e-3):
        sC = 3.*C/100. + 5e-6
    else:
        return ValueError("Invalid value of C. Exceedes the range.")
    return Datum(C, sC)


def keysightU1733C_inductance(L, freq=1e3):
    """
    Return the inductance Datum measured whith the Keysight RLC bridge.

    Parameters:
        L (float): the value of the inductance.
        freq (float): the frequency at which was taken the measure.
    """
    if freq == 1e3:
        factor = 1
    elif freq == 120e3:
        factor = 10
    else:
        raise ValueError("Invalid frequency value.")
    if (L < 2e-3*factor):
        sL = 2.*L/100. + 1e7*L*L/1e6 + 5e-7
    elif (L < 20e-3*factor):
        sL = 1.*L/100. + 1e6*L*L/1e6 + 5e-6
    elif (L < 200e-3*factor):
        sL = 0.7*L/100. + 1e5*L*L/1e6 + 5e-5
    elif (L < 2*factor):
        sL = 0.7*L/100. + 1e4*L*L/1e6 + 5e-4
    elif (L < 20*factor):
        sL = 0.7*L/100. + 1e3*L*L/1e6 + 5e-3
    elif (L < 100*factor):
        sL = 1.*L/100. + 1e2*L*L/1e6 + 5e-2
    else:
        raise ValueError("Invalid value of L. Exceedes the range.")
    return Datum(L, sL)


# Amprobe 37XR-A
def amprobe37XRA_DCvoltage(V):
    """
    Return the DC voltage Datum measured whith the Amprobe multimetre.

    Parameters:
        V (float): the value of the DC voltage.
    """
    if (V < 1):
        sV = 0.1*V/100 + 5e-4
    elif (V < 10):
        sV = 0.1*V/100. + 5e-3
    elif (V < 100):
        sV = 0.1*V/100. + 5e-2
    elif (V < 1e3):
        sV = 0.1*V/100. + 5e-1
    else:
        raise ValueError("Invalid value of V. Exceedes the range.")
    return Datum(V, sV)


def amprobe37XRA_DCcurrent(J):
    """
    Return the DC current Datum measured whith the Amprobe multimetre.

    Parameters:
        J (float): the value of the DC current.
    """
    if (J < 100e-6):
        sJ = 0.5*J/100 + 10e-8
    elif (J < 1e-3):
        sJ = 0.5*J/100. + 5e-7
    elif (J < 10e-3):
        sJ = 0.5*J/100. + 5e-6
    elif (J < 100e-3):
        sJ = 0.5*J/100. + 5e-5
    elif (J < 400e-3):
        sJ = 0.5*J/100. + 5e-4
    elif (J < 10):
        sJ = 1.5*J/100. + 10e-3
    else:
        raise ValueError("Invalid value of I. Exceedes the range.")
    return Datum(J, sJ)


def amprobe37XRA_ACvoltage(V, freq):
    """
    Return the AC voltage Datum measured whith the Amprobe multimetre.

    Parameters:
        V (float): the value of the AC voltage.
        freq (float): the frequency of the voltage.
    """
    if (V < 100 and freq >= 500 and freq < 2e3):
        perc = 2.0
    elif (V < 100 and freq >= 45 and freq < 500):
        perc = 1.2
    elif (V >= 100 and V < 750 and freq >= 45 and freq < 1e3):
        perc = 2.0
    else:
        raise ValueError("Invalide value of V.\
                          Exceedes the range for this frequency")
    if (V < 1):
        sV = perc*V/100 + 10e-4
    elif (V < 10):
        sV = perc*V/100. + 10e-3
    elif (V < 100):
        sV = perc*V/100. + 10e-2
    elif (V < 750):
        sV = perc*V/100. + 10e-1
    else:
        raise ValueError("Invalid value of V. Exceedes the range.")
    return Datum(V, sV)


def amprobe37XRA_ACcurrent(J):
    """
    Return the AC current Datum measured whith the Amprobe multimetre.

    Parameters:
        J (float): the value of the AC current.
    """
    if (J < 100e-6):
        sJ = 1.5*J/100 + 10e-8
    elif (J < 1e-3):
        sJ = 1.5*J/100. + 10e-7
    elif (J < 10e-3):
        sJ = 1.5*J/100. + 10e-6
    elif (J < 100e-3):
        sJ = 1.5*J/100. + 10e-5
    elif (J < 400e-3):
        sJ = 2.0*J/100. + 5e-4
    elif (J < 10):
        sJ = 2.5*J/100. + 10e-3
    else:
        raise ValueError("Invalid value of I. Exceedes the range.")
    return Datum(J, sJ)


# SuperTester 680 R
def supertester680R_DCvoltage(V, x2sens=False):
    """
    Return the DC voltage Datum measured whith the SuperTester.

    Parameters:
        V (float): the value of the DC voltage.
        x2sens (bool, default=False): whether the 2x sesisbility butto
            was pressed down.
    """
    if x2sens:
        factor = 2
    else:
        factor = 1
    if (V < 100e-3*factor):
        sV = 100e-3*factor*1./100.
    elif (V < 2*factor):
        sV = 2*factor*1./100.
    elif (V < 10*factor):
        sV = 10*factor*1./100.
    elif (V < 50*factor):
        sV = 50*factor*1./100.
    elif (V < 200*factor):
        sV = 200*factor*1./100.
    elif (V < 500*factor):
        sV = 500*factor*1./100.
    elif (V < 1000*factor):
        sV = 1000*factor*1./100.
    else:
        raise ValueError("Invalid value of V. Exceedes the range.")
    return Datum(V, sV)


def supertester680R_ACvoltage(V, x2sens=False):
    """
    Return the AC voltage Datum measured whith the SuperTester.

    Parameters:
        V (float): the value of the AC voltage.
        x2sens (bool, default=False): whether the 2x sesisbility butto
            was pressed down.
    """
    if x2sens:
        factor = 2
    else:
        factor = 1
    if (V < 10*factor):
        sV = 10*factor*1./100.
    elif (V < 50*factor):
        sV = 50*factor*1./100.
    elif (V < 250*factor):
        sV = 250*factor*1./100.
    elif (V < 750*factor):
        sV = 750*factor*1./100.
    else:
        raise ValueError("Invalid value of V. Exceedes the range.")
    return Datum(V, sV)


def supertester680R_DCcurrent(J, x2sens=False):
    """
    Return the DC current Datum measured whith the SuperTester.

    Parameters:
        J (float): the value of the DC current.
        x2sens (bool, default=False): whether the 2x sesisbility butto
            was pressed down.
    """
    if x2sens:
        factor = 2
    else:
        factor = 1
    if (J < 50e-6*factor):
        sJ = 50e-6*factor*1./100.
    elif (J < 500e-6*factor):
        sJ = 500e-6*factor*1./100.
    elif (J < 5e-3*factor):
        sJ = 5e-3*factor*1./100.
    elif (J < 50e-3*factor):
        sJ = 50-3*factor*1./100.
    elif (J < 500e-3*factor):
        sJ = 500e-3*factor*1./100.
    elif (J < 5*factor):
        sJ = 5*factor*1./100.
    else:
        raise ValueError("Invalid value of J. Exceedes the range.")
    return Datum(J, sJ)


def supertester680R_ACcurrent(J, x2sens=False):
    """
    Return the AC current Datum measured whith the SuperTester.

    Parameters:
        J (float): the value of the AC current.
        x2sens (bool, default=False): whether the 2x sesisbility butto
            was pressed down.
    """
    if x2sens:
        factor = 2
    else:
        factor = 1
    if (J < 250e-6*factor):
        sJ = 250e-6*factor*1./100.
    elif (J < 2.5e-3*factor):
        sJ = 2.5e-3*factor*1./100.
    elif (J < 25e-3*factor):
        sJ = 25e-3*factor*1./100.
    elif (J < 250e-3*factor):
        sJ = 250e-3*factor*1./100.
    elif (J < 2.5*factor):
        sJ = 2.5*factor*1./100.
    else:
        raise ValueError("Invalid value of J. Exceedes the range.")
    return Datum(J, sJ)
