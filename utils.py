import numpy as np
import math
import matplotlib.pyplot as plt
from scipy.odr import ODR, Model, RealData
from scipy.stats import chi2, norm


class Risultati_fit:
    def __init__(self, dati, risultato, model_function, nu, range_fit):
        self.x, self.y, self.sx, self.sy = dati
        self.risultato = risultato
        self.model_fu = model_function
        self.dof = nu
        self.begin_fit, self.end_fit = range_fit
        self.chi2 = risultato.sum_square
        self.valori, self.errori = risultato.beta, risultato.sd_beta
        self.pval = pValChi2(self.chi2, nu)

    def to_string(self, nome=None):
        stringa = ""
        if nome:
            stringa += f"{nome}\n"
        stringa = f"Fit fatto con x da {self.begin_fit} a {self.end_fit}\n"
        for indice, (val, err) in enumerate(zip(self.valori, self.errori)):
            stringa += f"    par{indice} = {val} ± {err}\n"
        stringa += f"Chi2 = {self.chi2}; n_dof = {self.dof}; pvalue = {self.pval}"
        return stringa
    
    def graph(self, file_name, x_label, y_label):
        figure, ax = plt.subplots()
        ax.grid()
        ax.errorbar(self.x, self.y, xerr=self.sx, yerr=self.sy, ls=" ", fmt="o", elinewidth=1, capsize=2)
        ax.set_xlabel(x_label)
        ax.set_ylabel(y_label)
        fx = np.linspace(self.begin_fit, self.end_fit, num=5000)
        fy = np.array([self.model_function(self.valori, c) for c in fx])
        ax.plot(fx, fy)
        figure.savefig(file_name)
        return figure, ax


linear_model = lambda pars, x: pars[0] * x + pars[1]
constant_model = lambda pars, x: pars[0] + 0 * x
gaussian_model = lambda pars, x: pars[0] / np.sqrt(2 * math.pi * pars[2] ** 2) * np.exp(-0.5 * ((x - pars[1]) / pars[2]) ** 2)


def fitta_funzione(x, y, sx, sy, function_model, range_fit, par_init):
    x, y, sx, sy = np.array(x), np.array(y), np.array(sx), np.array(sy)
    begin_fit, end_fit = range_fit
    indici = (x > begin_fit) & (x < end_fit)
    dati = RealData(x[indici], y[indici], sx[indici], sy[indici])
    modello = Model(function_model)
    par_init = np.array(par_init)
    result_object = ODR(dati, modello, par_init).run()
    return Risultati_fit((x, y, sx, sy), result_object, function_model, indici[0].size - par_init.size, range_fit)


def grafica_funzione(ax, funzione, range_fit):
    begin, end = range_fit
    fx = np.linspace(begin, end, num=5000)
    fy = np.array([funzione(c) for c in fx])
    ax.plot(fx, fy)
    return ax


def grafica_funzioni_singolo_set(
    x, y, sx, sy, range_fits, funzioni, colori, xLabel, yLabel, filename
):
    figure, ax = plt.subplots()
    ax.grid()
    ax.errorbar(x, y, xerr=sx, yerr=sy, ls=" ", fmt="o", elinewidth=1, capsize=2)
    ax.set_xlabel(xLabel)
    ax.set_ylabel(yLabel)
    for range_fit, funzione, colore in zip(range_fits, funzioni, colori):
        begin, end = range_fit
        fx = np.linspace(begin, end, num=5000)
        fy = np.array([funzione(c) for c in fx])
        ax.plot(fx, fy, color=colore)
    figure.savefig(filename)


def grafica_cose(xs, ys, sxs, sys, colori_dati, range_fits, funzioni, colori, xLabel, yLabel, filename):
    figure, ax = plt.subplots()
    ax.grid()
    for x, y, sx, sy, col in zip(xs, ys, sxs, sys, colori_dati):
        ax.errorbar(
            x, y, xerr=sx, yerr=sy, ls=" ", fmt="o", color=col, elinewidth=1, capsize=2
        )
    ax.set_xlabel(xLabel)
    ax.set_ylabel(yLabel)
    for range_fit, funzione, colore in zip(range_fits, funzioni, colori):
        begin, end = range_fit
        fx = np.linspace(begin, end, num=5000)
        fy = np.array([funzione(c) for c in fx])
        ax.plot(fx, fy, color=colore)
    figure.savefig(filename)


def pValChi2(chi_2, dof):
    return 1 - chi2.cdf(chi_2, dof)


def testNormale(x1, x2, sx1, sx2):
    Z = (x1 - x2) / np.sqrt(sx1**2 + sx2**2)
    pvalue = 2 * (1 - norm.cdf(abs(Z)))
    return Z, pvalue


def mediaPesata(valori, errori):
    valori, errori = np.array(valori), np.array(errori)
    pesi = 1 / errori**2
    somma_pesi = pesi.sum()
    media = (valori * pesi).sum() / somma_pesi
    return media, np.sqrt(1 / somma_pesi)


def carica_dati(filename):
    return np.loadtxt(filename, skiprows=1, unpack=True, delimiter=",", dtype=float)


def graficaDati(x, y, sx, sy, xLabel, yLabel, fileName):
    figure, ax = plt.subplots()
    ax.grid()
    ax.errorbar(x, y, xerr=sx, yerr=sy, ls=" ", fmt="o", elinewidth=1, capsize=2)
    ax.set_xlabel(xLabel)
    ax.set_ylabel(yLabel)
    figure.savefig(fileName)


def graficoVolante(x, y, fileName):
    figure, ax = plt.subplots()
    ax.grid()
    ax.errorbar(x, y, ls=" ", fmt="o", elinewidth=1, capsize=2)
    ax.set_xlabel("Quantità [suppongo SI]")
    ax.set_ylabel("Quantità [suppongo SI]")
    figure.savefig(fileName)
