#pragma once

#include "Datum.h"

// Agilent U1731A
Datum agilentU1731A_resistance(double R, double freq=1e3);
Datum agilentU1731A_capacitance(double C, double freq=1e3);
Datum agilentU1731A_inductance(double L, double freq=1e3);

// Keysight U1733C
Datum keysightU1733C_resistance(double R, double freq=1e3);
Datum keysightU1733C_capacitance(double C, double freq=1e3);
Datum keysightU1733C_inductance(double L, double freq=1e3);

// Amprobe 37XR-A
Datum amprobe37XRA_DCvoltage(double V);
Datum amprobe37XRA_DCcurrent(double I);
Datum amprobe37XRA_ACvoltage(double V, double freq);
Datum amprobe37XRA_ACcurrent(double I);

// SuperTester 680 R
Datum supertester680R_DCvoltage(double V, bool x2sens=false);
Datum supertester680R_ACvoltage(double V, bool x2sens=false);
Datum supertester680R_DCcurrent(double I, bool x2sens=false);
Datum supertester680R_ACcurrent(double I, bool x2sens=false);
