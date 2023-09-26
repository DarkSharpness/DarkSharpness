import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np
import math
from pylab import *
mpl.rcParams['font.sans-serif'] = ['SimHei']
mpl.rcParams['axes.unicode_minus'] = False


lam = np.linspace(400, 1000, 10000)
ms = [0,1,2]
for m in ms:
    theta = np.arcsin(math.sin(70/180 * math.pi) - 1 * m * lam /(740))/math.pi * 180
    plt.plot(theta, lam,color="black")
    y = 400
    x = math.asin(math.sin(70/180 * math.pi) - 1 * m * y/740)/math.pi * 180
    plt.annotate(r"$m={:1}$".format(m), xy=(x,y), xycoords='data', xytext=(-20,-5), textcoords='offset points')
plt.xlabel(r"reflection angle $\theta_r$ $/^\circ$")
plt.ylabel(r"Wavelength $\lambda$ / nm")
x = [-90, 70]
y = [390, 390]
plt.plot(x,y,'r--')
x = [-90, 70]
y = [750, 750]
plt.plot(x,y,'r--')
plt.plot([16.17,12.13,1.72],[450,550,650],'go--')
plt.plot([-12.68,-29.90],[450,550],'go--')
plt.show()