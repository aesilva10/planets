import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

#constants
n_points=300
min_x = 0.0
min_y = 0.0
max_x = 30.0
max_y = 30.0
min_t = 0.0
max_t = 30.0
c=1.0 
dy=(max_y-min_y)/n_points
dx=(max_x-min_x)/n_points
dt=0.5*dx/c
#arrays variables
x=np.linspace(min_x,max_x,n_points)
y=np.linspace(min_y,max_y,n_points)
t=np.linspace(min_t,max_t,n_points)
r=c*dt/dx
#Matriz inicial
u_inicial=np.zeros((n_points,n_points))
#initial conditions t=0
u_inicial[n_points/3][n_points/2]=-0.5
#create the mask
mask=np.ones((n_points,n_points))
mask[:,0]=0
mask[:,n_points-1]=0
mask[0,:]=0
mask[n_points-1,:n_points-1]=0
mask[-n_points/3][0:n_points/2-10]=0
mask[-n_points/3][n_points/2+10:]=0
mask[-n_points/3][-n_points/2:n_points/2]=1
#create the grilla
grilla=[]
grilla.append(u_inicial)
#Matriz future
u_future=np.zeros((n_points,n_points))
#Primera iteracion t=1
for i in range(n_points-1):
	for j in range(n_points-1):	
		u_future[i,j] = u_inicial[i,j]-(0.5*(r**2))*(u_inicial[i+1,j]+u_inicial[i-1,j]+u_inicial[i,j+1]+u_inicial[i,j-1]-4*u_inicial[i,j])

upast=u_inicial.copy()
upresent=np.copy(u_future)
upresent=upresent*mask
grilla.append(upresent)
#Iteracion para todo los t
for n in range(n_points):
	for i in range(1,n_points-1):
		for j in range(1,n_points-1):        	
			u_future[i,j] = 2.0*upresent[i,j]-upast[i,j]+ (r**2)*(upresent[i+1,j]+upresent[i-1,j]+upresent[i,j+1]+upresent[i,j-1]-4*upresent[i,j])	
	upast=upresent.copy()	
	upresent=u_future.copy()
	upresent=upresent*mask
	grilla.append(upresent)

#Figure for t=60s
plt.figure(1)
plt.subplot(1,2,1)
plt.imshow(grilla[-1])
plt.title("60 seg")
plt.tight_layout()
plt.subplot(1,2,2)
#figure to t=30s
plt.imshow(grilla[n_points/2])
plt.title("30 seg")
plt.tight_layout()
plt.savefig("Resultados_hw3.pdf")
plt.close()

#animacion

fig=plt.figure(2)
lista=plt.imshow(abs(grilla[0]),cmap='flag',extent=(30+dx,30-dx,30+dy,30-dy))

def animate(i):
	lista.set_array(abs(grilla[i]))
	return lista,
animacion = animation.FuncAnimation(fig, animate, np.arange(1,len(grilla)),interval=20,blit=False)
#Guardar en mp4
animacion.save('onda.mp4',fps =20)
