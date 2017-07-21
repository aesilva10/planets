import numpy as np
import matplotlib.pyplot as plt
from numpy import *

datosx=np.loadtxt('datosx.txt')
datosy=np.loadtxt('datosy.txt')
datosz=np.loadtxt('datosz.txt')

n_planetas=10
for i in range(n_planetas):
	mx=datosx[:,i]
	my=datosy[:,i]
	
plt.figure()
plt.scatter(mx,my)	
plt.title('Orbitas de los Planetas')
plt.savefig('orbitas_planetas.png')
plt.close()
