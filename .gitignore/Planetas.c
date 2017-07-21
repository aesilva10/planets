#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define PI 3.14159265358979323846
// constante G
double G = 4.0*(pow(PI,2));
#define n_planets 10
// numero de iteracion n
#define n 1000
//matriz de aceleracion para cada componente x,y,z. es la aceleracion del planeta en el tiempo t
int t;
int p;
double matriz[10][7];
double ax(p, t);
double ay(p, t);
double az(p, t);
// funciones
double aceleracionx(int p, int t);
double aceleraciony(int p, int t);
double aceleracionz(int p, int t);

//matriz de posicion y velocidades
double vx[n_planets][n];
double vy[n_planets][n];
double vz[n_planets][n];
double x[n_planets][n];
double y[n_planets][n];
double z[n_planets][n];

//intervalo de tiempo
double dt;
//masas para cada planeta
double masas[n_planets];
//funcion condiciones iniciales
void condicionesiniciales();
//Funcion crea archivos txt
void creartxt();
// masas
double masas[10];

int main(void){
	FILE *file;
	file=fopen("coordinates.csv","r");
	int len=250;
	char line_buffer[len];
	char *split_buffer;
	const char *delimiter;
	delimiter=",";
	int i=0;
	int j=0;
	double matriz[10][7];
	float year_to_seconds = 365.25*24*60*60;
	//ref_time = datetime(1970,1,1, 0, 0);
	//init_time = datetime(2016, 12, 11, 0, 0);		
	while(fgets(line_buffer,len,file)){
		j=0;
		split_buffer=strtok(line_buffer,delimiter);
		while(split_buffer !=NULL){
			if(j!=0){
				matriz[i][j-1]=atof(split_buffer);}
			split_buffer=strtok(NULL, delimiter);
			j+=1;
		}
	i+=1;
	}
	double *masas=malloc(10*sizeof(double));
	//divide las masas de los planetas en la del sol, cambiar de unidades	
	for(i=0;i<10;i++){
		masas[i]=matriz[i][0]/matriz[0][0];
	}
	// funcion de condiciones iniciales
	condicionesiniciales();
	// contadores	
	int l;
	int m;
	for(l=0;l<n-1;l++){
		//calcular xi+1=xi+vi*t+(1/2)ai*t*t, fuentes http://www.uam.es/personal_pdi/ciencias/evelasco/doctorado03-04/prac2/node4.html, http://www.fisica.edu.uy/~sbruzzone/FlexPaper_1.4.2_flash/defensa.pdf
        	for(m=0;m<n_planets;m++){
        	    x[m][l+1]=x[m][l]+vx[m][l]*dt+0.5*aceleracionx(m,l)*pow(dt,2);
        	    y[m][l+1]=y[m][l]+vy[m][l]*dt+0.5*aceleraciony(m,l)*pow(dt,2);
        	    z[m][l+1]=z[m][l]+vz[m][l]*dt+0.5*aceleracionz(m,l)*pow(dt,2);
        	}
    	}
    	for(l=0;l<n-1;l++){
        	for(m=0;m<n_planets;m++){
		//calcular vi+1=vi+(1/2)*(vi+v(i+1))
		// pero a*t =v , fuentes http://www.uam.es/personal_pdi/ciencias/evelasco/doctorado03-04/prac2/node4.html, http://www.fisica.edu.uy/~sbruzzone/FlexPaper_1.4.2_flash/defensa.pdf
        	    vx[m][l+1]=vx[m][l]+0.5*(aceleracionx(m,l)+aceleracionx(m,l+1))*dt;
        	    vy[m][l+1]=vy[m][l]+0.5*(aceleraciony(m,l)+aceleraciony(m,l+1))*dt;
        	    vz[m][l+1]=vz[m][l]+0.5*(aceleracionz(m,l)+aceleracionz(m,l+1))*dt;
            
        	}
    	}
	// crea el txt con los valores de x,y,z
	creartxt();
	
}

void condicionesiniciales(){
	//dt intervalo de tiempo
	double dt=0.0001;
	//constante G
	double G=4*pow(PI,2);
	int i;
	for(i=0;i<n_planets;i++){
		masas[i]=matriz[i][0]/matriz[0][0];
	        //condiciones iniciales
	        x[i][0]=matriz[i][1];
	        y[i][0]=matriz[i][2];
	        z[i][0]=matriz[i][3];
	        vx[i][0]=matriz[i][4];
	        vy[i][0]=matriz[i][5];
	        vz[i][0]=matriz[i][6];        
    }
}
double aceleracionx(int p, int t){
	// contador    	
	int c;
	// distancia    	
	double d;
	// aceleracion x    	
	double ax=0;
    	for(c=0;c<n_planets;c++){
                // no se uede calcular la aceleracion con respecto al planeta propio
        	if(c==p){
            	//segun https://stackoverflow.com/questions/16598222/why-is-continue-statement-ignoring-the-loop-counter-increment-in-while-loop continue se usa para ignoar un loop
            		continue;
        }
    		//d= distancia
        	d=sqrt(pow(x[c][t]-x[p][t],2)+pow(y[c][t]-y[p][t],2)+pow(z[c][t]-z[p][t],2));
        	ax+=G*(masas[c]/pow(d,3))*(x[c][t]-x[p][t]);
    }
    	return ax;
    
}
double aceleraciony(int p, int t){
	// contador    	
	int c;
	// distancia    	
	double d;
	// aceleracion y    	
	double ay=0;
    	for(c=0;c<n_planets;c++){
                // no se uede calcular la aceleracion con respecto al planeta propio
        	if(c==p){
            	//segun https://stackoverflow.com/questions/16598222/why-is-continue-statement-ignoring-the-loop-counter-increment-in-while-loop continue se usa para ignoar un loop
            		continue;
        }
    		//d= distancia
        	d=sqrt(pow(x[c][t]-x[p][t],2)+pow(y[c][t]-y[p][t],2)+pow(z[c][t]-z[p][t],2));
        	ay+=G*(masas[c]/pow(d,3))*(y[c][t]-y[p][t]);
    }
    	return ay;
    
}
double aceleracionz(int p, int t){
	// contador    	
	int c;
	// distancia    	
	double d;
	// aceleracion z    	
	double az=0;
    	for(c=0;c<n_planets;c++){
                // no se uede calcular la aceleracion con respecto al planeta propio
        	if(c==p){
            	//segun https://stackoverflow.com/questions/16598222/why-is-continue-statement-ignoring-the-loop-counter-increment-in-while-loop continue se usa para ignoar un loop
            		continue;
        }
    		//d= distancia
        	d=sqrt(pow(x[c][t]-x[p][t],2)+pow(y[c][t]-y[p][t],2)+pow(z[c][t]-z[p][t],2));
        	az+=G*(masas[c]/pow(d,3))*(z[c][t]-z[p][t]);
    }
    	return az;
    
}
void creartxt(){
    // segun https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm se utiliza fopen w+ para crear archivos de escritura y lectura, 'Creates an empty file for both reading and writing.'
    FILE *rtax;
    FILE *rtay;
    FILE *rtaz;
    rtax=fopen("datosx.txt","w+");
    rtay=fopen("datosy.txt","w+");
    rtaz=fopen("datosz.txt","w+");
    int i;
    for(i=0;i<n;i++){
        fprintf(rtax, "%f %f %f %f %f %f %f %f %f %f \n", x[0][i], x[1][i], x[2][i], x[3][i], x[4][i], x[5][i], x[6][i], x[7][i], x[8][i], x[9][i]);
    }
    for(i=0;i<n;i++){
        fprintf(rtay, "%f %f %f %f %f %f %f %f %f %f \n", y[0][i], y[1][i], y[2][i], y[3][i], y[4][i], y[5][i], y[6][i], y[7][i], y[8][i], y[9][i]);
    }
    
    for(i=0;i<n;i++){
        fprintf(rtaz, "%f %f %f %f %f %f %f %f %f %f \n", z[0][i], z[1][i], z[2][i], z[3][i], z[4][i], z[5][i], z[6][i], z[7][i], z[8][i], z[9][i]);
}
    fclose(rtax);
    fclose(rtay);
    fclose(rtaz);
}
