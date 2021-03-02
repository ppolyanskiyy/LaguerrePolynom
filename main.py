from sympy import *
from ipywidgets import interact, interactive, fixed, interact_manual
import ipywidgets as widgets
import matplotlib.pyplot as plt
import numpy as np
import math


class Laguerre:
    def __init__(self, function, alpha, beta, N, T):
        self.function = function
        self.alpha = alpha
        self.beta = beta
        self.N = N
        self.T = T
        self.processes()

    @property
    def function(self):
        return self._function

    @function.setter
    def function(self, value):
        self._function = value

    @property
    def alpha(self):
        return self._alpha

    @alpha.setter
    def alpha(self, value):
        self._alpha = value

    @property
    def beta(self):
        return self._beta

    @beta.setter
    def beta(self, value):
        self._beta = value

    @property
    def N(self):
        return self._N

    @N.setter
    def N(self, value):
        self._N = value

    @property
    def T(self):
        return self._T

    @T.setter
    def T(self, value):
        self._T = value

    @property
    def sigma(self):
        return self._alpha + self._beta

    def __str__(self):
        return f'Alpha:{self.alpha} \nBeta:{self.beta} \nSigma:{self.sigma}'

    def fx(self, x):
        return float(eval(self.function))

    def lk(self, t, k):
        if k == 0:
            return np.sqrt(self.sigma) * np.exp((-self.beta / 2) * t)
        elif k == 1:
            return np.sqrt(self.sigma) * (1 - self.sigma * t) * np.exp((-self.beta / 2) * t)
        else:
            return ((2 * k - 1 - t) / k) * self.lk(t, k - 1) - ((k - 1) / k) * self.lk(t, k - 2)

    def f(self, t, k):
        return self.fx(t) * self.lk(t, k) * np.exp(-(self.sigma - self.beta) * t)

    def sum_rectangle(self, n, right, left, k):
        smt_value = n
        all_sum = 0
        add_h = (right - left) / n
        while smt_value >= 1:
            all_sum += self.f(left + ((smt_value - 0.5) * add_h), k)
            smt_value -= 1
        return all_sum

    def integral(self, right, left, k):
        h = right - left
        value1_rct = h * self.f(left + h / 2, k)  # n=1
        value2_rct = (h / 2) * self.sum_rectangle(2, right, left, k)  # n=2

        n = 4
        coef = h / (2 * n)

        while np.abs((value1_rct - value2_rct) / value2_rct) > 0.01:
            value1_rct = value2_rct
            value2_rct = coef * self.sum_rectangle(n, right, left, k)

            n = n * 2
            coef = h / n

        return value2_rct

    def processes(self):
        try:
            add_func = ''
            for i in range(len(self.function)):
                if self.function[i] == '^':
                    add_func += '**'
                else:
                    add_func += self.function[i]
            self.function = add_func

            step = 0.01
            appr = np.exp(-10)

            right = 0
            while np.exp(-self.alpha * right) >= appr:
                right += 0.5

            left = 0

            xs = [i for i in np.arange(0, self.T, step)]
            ys = [self.fx(i) for i in np.arange(0, self.T, step)]
            hs_x = [i for i in np.arange(0, self.T, step)]

            #         print("Right border:", right)
            fig, ax = plt.subplots()
            plt.axhline(color="black")
            plt.axvline(color="black")

            fk = []
            for i in range(0, self.N):
                fk.append(self.integral(right, left, i))
            print('Інтеграл:')
            [print(i) for i in fk]
            hs = []
            for t_i in np.arange(0, self.T, step):
                sum_k = 0
                for k_i in fk:
                    sum_k += k_i * self.lk(t_i, fk.index(k_i))
                hs.append(sum_k)

            print('Наближені поліноми:', hs)

            plt.plot(xs, ys)
            plt.plot(hs_x, hs)

            fig.canvas.set_window_title('Апроксимацiя функцiями Лагерра - графік')  # заголовок вікна з графіками


            del xs, ys, fk, hs
            plt.show(block=False)
        except:
            print('Помилка: перевірте введені дані.')

def chooseParametrs(function, alpha, beta, N, T):
    temp = Laguerre(function, float(alpha), float(beta), int(N), float(T))
    del temp

print('Введіть необхідні параметри:')
chooseParametrs('x**2', 1, 2, 15, 2)
#interactive(chooseParametrs, {'manual': True}, function='', alpha='', beta='', N='', T='')