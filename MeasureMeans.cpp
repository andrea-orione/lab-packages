#include "MeasureMeans.h"
#include "Datum.h"
#include <stdexcept>


// Agilent U1731A
Datum agilentU1731A_resistance(double R, double freq)
{
  if (!(freq == 1e3 || freq == 120))
    throw std::out_of_range("Invalid frequency error.");
  double sR;
  if (R < 20)
    sR = 1.2*R/100. + 40e-3;
  else if (R < 200)
    sR = 0.8*R/100. + 5e-2;
  else if (R < 2e3)
    sR = 0.5*R/100. + 3e-1;
  else if (R < 20e3)
    sR = 0.5*R/100. + 3.;
  else if (R < 200e3)
    sR = 0.5*R/100. + 30.;
  else if (R < 2e6)
    sR = 0.5*R/100. + 5e2;
  else if (R < 10e6)
    sR = 2.*R/100. + 8e3;
  else
    throw std::out_of_range("Invalid value of R. Exceedes the range.");
  return Datum(R, sR);
}

Datum agilentU1731A_capacitance(double C, double freq)
{
  double factor;
  if (freq == 1e3)
    factor = 1.;
  else if (freq == 120)
    factor = 10.;
  else
    throw std::out_of_range("Invalid frequency value.");
  double sC;
  if (C < 2e-9*factor)
    sC = 1.*C/100. + 5e-13;
  else if (C < 20e-9*factor)
    sC = 0.7*C/100. + 5e-12;
  else if (C < 200e-9*factor)
    sC = 0.7*C/100. + 3e-11;
  else if (C < 2e-6*factor)
    sC = 0.7*C/100. + 3e-10;
  else if (C < 20e-6*factor)
    sC = 0.7*C/100. + 3e-9;
  else if ((freq == 1e3 && C < 200e-6) || (freq == 120e3 && C < 1e-3))
    sC = 1.*C/100. + 5e-8;
  else if ((freq == 1e3 && C < 1e-3) || (freq == 120e3 && C < 10e-3))
    sC = 3.*C/100. + 5e-6;
  else
    throw std::out_of_range("Invalid value of C. Exceedes the range.");
  return Datum(C, sC);
}

Datum agilentU1731A_inductance(double L, double freq){
  double factor;
  if (freq == 1e3)
    factor = 1.;
  else if (freq == 120)
    factor = 10.;
  else
    throw std::out_of_range("Invalid frequency value.");
  double sL;
  if (L < 2e-3*factor)
    sL = 2.*L/100. + 1e7*L*L/1e6 + 5e-7;
  else if (L < 20e-3*factor)
    sL = 1.*L/100. + 1e6*L*L/1e6 + 5e-6;
  else if (L < 200e-3*factor)
    sL = 0.7*L/100. + 1e5*L*L/1e6 + 5e-5;
  else if (L < 2*factor)
    sL = 0.7*L/100. + 1e4*L*L/1e6 + 5e-4;
  else if (L < 20*factor)
    sL = 0.7*L/100. + 1e3*L*L/1e6 + 5e-3;
  else if (L < 100*factor)
    sL = 1.*L/100. + 1e2*L*L/1e6 + 5e-2;
  else
    throw std::out_of_range("Invalid value of L. Exceedes the range.");
  return Datum(L, sL);
}

// Keysight U1733C
Datum keysightU1733C_resistance(double R, double freq)
{
  double frequencies[] = {100, 120, 1e3, 10e3, 100e3};
  int i=0;
  while (i < 5){
    if (freq==frequencies[i]) break;
    i++;
  }
  if (i == 5)
    throw std::out_of_range("Invalid frequency value");

  double ranges[] = {2, 20, 200, 2e3, 20e3, 200e3, 2e6, 20e6, 200e6};

  double errors[5][9][2] = {{{0.7, 50e-4}, {0.7, 8e-3}, {0.2, 3e-2}, {0.2, 3e-1}, {0.2, 3.},
                             {0.5, 5e1}, {0.5, 5e2}, {2.0, 8e3}, {6.0, 80e4}},
                            {{0.7, 50e-4}, {0.7, 8e-3}, {0.2, 3e-2}, {0.2, 3e-1}, {0.2, 3.},
                             {0.5, 5e1}, {0.5, 5e2}, {2.0, 8e3}, {6.0, 80e4}},
                            {{0.7, 50e-4}, {0.7, 8e-3}, {0.2, 3e-2}, {0.2, 3e-1}, {0.2, 3.},
                             {0.5, 5e1}, {0.5, 5e2}, {2.0, 8e3}, {6.0, 80e4}},
                            {{0.7, 50e-4}, {0.7, 8e-3}, {0.2, 3e-2}, {0.2, 3e-1}, {0.2, 3.},
                             {0.5, 5e1}, {0.7, 5e2}, {5.0, 8e3}, {false, false}},
                            {{1.0, 50e-4}, {0.7, 8e-3}, {0.5, 5e-2}, {0.5, 5e-1}, {0.5, 5.},
                             {0.7, 8e1}, {false, false}, {false, false}, {false, false}}};
  for (int j = 0; j < 9; j++){
    if (R >= ranges[j])
      continue;
    if (!errors[i][j][0])
      throw std::out_of_range("Invalid value of R.\
                               Exceedes the range for this frequency.");
    double error0 = errors[i][j][0];
    double error1 = errors[i][j][1];
    return Datum(R, error0*R/100. + error1);
  }
  throw std::out_of_range("Invalid value of R. Exceedes the range.");
}

Datum keysightU1733C_capacitance(double C, double freq)
{
  double frequencies[] = {100, 120, 1e3, 10e3, 100e3};
  int i=0;
  while (i < 5){
    if (freq==frequencies[i]) break;
    i++;
  }
  if (i == 5)
    throw std::out_of_range("Invalid frequency value");

  double ranges[] = {20e-12, 200e-12, 2e-9, 20e-9, 200e-9, 2e-6, 20e-6,
    200e-6, 2e-3, 20e-3};

  double errors[5][10][2] = {{{false, false}, {false, false}, {0.5, 10e-13}, {0.5, 5e-12},
                              {0.2, 3e-11}, {0.2, 3e-10}, {0.2, 3e-9},
                              {0.3, 3e-8}, {0.5, 5e-7}, {0.5, 8e-6}},
                             {{false, false}, {false, false}, {0.5, 10e-13}, {0.5, 5e-12},
                              {0.2, 3e-11}, {0.2, 3e-10}, {0.2, 3e-9},
                              {0.3, 3e-8}, {0.5, 5e-7}, {0.5, 8e-6}},
                             {{false, false}, {0.5, 10e-14}, {0.5, 5e-13}, {0.2, 3e-12},
                              {0.2, 3e-11}, {0.2, 3e-10}, {0.2, 3e-9},
                              {0.5, 5e-8}, {0.5, 8e-7}, {false, false}},
                             {{1.0, 20e-15}, {0.8, 10e-14}, {0.5, 3e-13}, {0.5, 3e-12},
                              {0.5, 3e-11}, {0.2, 3e-10}, {0.5, 5e-9},
                              {0.5, 8e-8}, {false, false}, {false, false}},
                             {{2.5, 10e-15}, {2.0, 10e-14}, {2.0, 10e-13}, {0.7, 10e-12},
                              {0.7, 10e-11}, {0.7, 10e-10}, {5.0, 10e-9},
                              {false, false}, {false, false}, {false, false}}};
  for (int j=0; j < 10; j++){
    if (C >= ranges[j])
      continue;
    if (!errors[i][j][0])
      throw std::out_of_range("Invalid value of C.\
                               Exceedes the range for this frequency.");
    double error0 = errors[i][j][0];
    double error1 = errors[i][j][1];
    return Datum(C, error0*C/100. + error1);
  }
  throw std::out_of_range("Invalid value of C. Exceedes the range.");
}

Datum keysightU1733C_inductance(double L, double freq)
{
  double frequencies[] = {100, 120, 1e3, 10e3, 100e3};
  int i=0;
  while (i < 5){
    if (freq==frequencies[i]) break;
    i++;
  }
  if (i == 5)
    throw std::out_of_range("Invalid frequency value");

  double ranges[] = {20e-6, 200e-6, 2e-3, 20e-3, 200e-3, 2., 20., 200., 2e3};

  double errors[5][9][2] = {{{false, false}, {false, false}, {0.7, 10e-7}, {0.5, 3e-6}, {0.5, 3e-5},
                             {0.2, 3e-4}, {0.2, 3e-3}, {0.7, 5e-2}, {1.0, 5e-1}},
                            {{false, false}, {false, false}, {0.7, 10e-7}, {0.5, 3e-6}, {0.5, 3e-5},
                             {0.2, 3e-4}, {0.2, 3e-3}, {0.7, 5e-2}, {1.0, 5e-1}},
                            {{false, false}, {1.0, 5e-8}, {0.5, 5e-7}, {0.2, 3e-6}, {0.2, 3e-5},
                             {0.2, 3e-4}, {0.5, 5e-3}, {1.0, 5e-2}, {2.0, 8e-1}},
                            {{1.0, 5e-9}, {0.7, 3e-8}, {0.5, 3e-7}, {0.3, 3e-6}, {0.2, 3e-5},
                             {0.5, 5e-4}, {1.0, 5e-3}, {2.0, 8e-2}, {false, false}},
                            {{2.5, 20e-9}, {2.5, 20e-8}, {0.8, 20e-7}, {0.8, 10e-6},
                             {1.0, 10e-5}, {1.0, 10e-4}, {2.0, 10e-3}, {false, false}, {false, false}}};
  for (int j=0; j < 9; j++){
    if (L >= ranges[j])
      continue;
    if (!errors[i][j][0])
      throw std::out_of_range("Invalid value of L.\
                               Exceedes the range for this frequency.");
    double error0 = errors[i][j][0];
    double error1 = errors[i][j][1];
    return Datum(L, error0*L/100. + error1);
  }
  throw std::out_of_range("Invalid value of L. Exceedes the range.");
}


// Amprobe 37XR-A
Datum amprobe37XRA_DCvoltage(double V)
{
  double sV;
  if (V < 1)
    sV = 0.1*V/100 + 5e-4;
  else if (V < 10)
    sV = 0.1*V/100. + 5e-3;
  else if (V < 100)
    sV = 0.1*V/100. + 5e-2;
  else if (V < 1e3)
    sV = 0.1*V/100. + 5e-1;
  else
    throw std::out_of_range("Invalid value of V. Exceedes the range.");
  return Datum(V, sV);
}

Datum amprobe37XRA_DCcurrent(double I)
{
  double sI;
  if (I < 100e-6)
    sI = 0.5*I/100 + 10e-8;
  else if (I < 1e-3)
    sI = 0.5*I/100. + 5e-7;
  else if (I < 10e-3)
    sI = 0.5*I/100. + 5e-6;
  else if (I < 100e-3)
    sI = 0.5*I/100. + 5e-5;
  else if (I < 400e-3)
    sI = 0.5*I/100. + 5e-4;
  else if (I < 10)
    sI = 1.5*I/100. + 10e-3;
  else
    throw std::out_of_range("Invalid value of I. Exceedes the range.");
  return Datum(I, sI);
}

Datum amprobe37XRA_ACvoltage(double V, double freq)
{
  double perc;
  if (V < 100 && freq >= 500 && freq < 2e3)
    perc = 2.0;
  else if (V < 100 && freq >= 45 && freq < 500)
    perc = 1.2;
  else if (V >= 100 && V < 750 && freq >= 45 && freq < 1e3)
    perc = 2.0;
  else
    throw std::out_of_range("Invalide value of V.\
                             Exceedes the range for this frequency");
  double sV;
  if (V < 1)
    sV = perc*V/100 + 10e-4;
  else if (V < 10)
    sV = perc*V/100. + 10e-3;
  else if (V < 100)
    sV = perc*V/100. + 10e-2;
  else if (V < 750)
    sV = perc*V/100. + 10e-1;
  else
    throw std::out_of_range("Invalid value of V. Exceedes the range.");
  return Datum(V, sV);
}

Datum amprobe37XRA_ACcurrent(double I)
{
  double sI;
  if (I < 100e-6)
    sI = 1.5*I/100 + 10e-8;
  else if (I < 1e-3)
    sI = 1.5*I/100. + 10e-7;
  else if (I < 10e-3)
    sI = 1.5*I/100. + 10e-6;
  else if (I < 100e-3)
    sI = 1.5*I/100. + 10e-5;
  else if (I < 400e-3)
    sI = 2.0*I/100. + 5e-4;
  else if (I < 10)
    sI = 2.5*I/100. + 10e-3;
  else
    throw std::out_of_range("Invalid value of I. Exceedes the range.");
  return Datum(I, sI);
}


// SuperTester 680 R
Datum supertester680R_DCvoltage(double V, bool x2sens)
{
  double sV;
  double factor = (x2sens) ? 2. : 1.;
  if (V < 100e-3*factor)
    sV = 100e-3*factor*1./100.;
  else if (V < 2*factor)
    sV = 2*factor*1./100.;
  else if (V < 10*factor)
    sV = 10*factor*1./100.;
  else if (V < 50*factor)
    sV = 50*factor*1./100.;
  else if (V < 200*factor)
    sV = 200*factor*1./100.;
  else if (V < 500*factor)
    sV = 500*factor*1./100.;
  else if (V < 1000*factor)
    sV = 1000*factor*1./100.;
  else
    throw std::out_of_range("Invalid value of V. Exceedes the range.");
  return Datum(V, sV);
}

Datum supertester680R_ACvoltage(double V, bool x2sens)
{
  double sV;
  double factor = (x2sens) ? 2. : 1.;
  if (V < 10*factor)
    sV = 10*factor*1./100.;
  else if (V < 50*factor)
    sV = 50*factor*1./100.;
  else if (V < 250*factor)
    sV = 250*factor*1./100.;
  else if (V < 750*factor)
    sV = 750*factor*1./100.;
  else
    throw std::out_of_range("Invalid value of V. Exceedes the range.");
  return Datum(V, sV);
}

Datum supertester680R_DCcurrent(double I, bool x2sens)
{
  double sI;
  double factor = (x2sens) ? 2. : 1.;
  if (I < 50e-6*factor)
    sI = 50e-6*factor*1./100.;
  else if (I < 500e-6*factor)
    sI = 500e-6*factor*1./100.;
  else if (I < 5e-3*factor)
    sI = 5e-3*factor*1./100.;
  else if (I < 50e-3*factor)
    sI = 50-3*factor*1./100.;
  else if (I < 500e-3*factor)
    sI = 500e-3*factor*1./100.;
  else if (I < 5*factor)
    sI = 5*factor*1./100.;
  else
    throw std::out_of_range("Invalid value of I. Exceedes the range.");
  return Datum(I, sI);
}

Datum supertester680R_ACcurrent(double I, bool x2sens)
{
  double sI;
  double factor = (x2sens) ? 2. : 1.;
  if (I < 250e-6*factor)
    sI = 250e-6*factor*1./100.;
  else if (I < 2.5e-3*factor)
    sI = 2.5e-3*factor*1./100.;
  else if (I < 25e-3*factor)
    sI = 25e-3*factor*1./100.;
  else if (I < 250e-3*factor)
    sI = 250e-3*factor*1./100.;
  else if (I < 2.5*factor)
    sI = 2.5*factor*1./100.;
  else
    throw std::out_of_range("Invalid value of I. Exceedes the range.");
  return Datum(I, sI);
}
