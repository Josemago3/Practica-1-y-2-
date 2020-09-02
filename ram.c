#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*programa que simula el funcionamiento de la memoria RAM
  Ortega Zitle Ariel
  Aguirre Olvera Jose Manuel
  Sistemas Operativos 2
  
  Lo que hace el programa es simular la memoria ram.
  Apartir de dos opciones donde la opción A) Solo tiene 4 opciones para el manejo de la ram y 
  La opcion B) tiene 5 opciones, la opcion agregada a B) es la opcion de enviar archivos al disco
  a partir de la memoria RAM y de la RAM al disco.
  
  */
//estrucutura para listas ligadas

#define maxr    80 //define el maximo de espacios en la memoria ram y HDD
#define maxchar 12 //define el maximo de caracteres
#define maxf    10 //define el maximo de filas
#define maxc     8 //define el maximo de columnas 

typedef struct nodo{
	char nombreproceso[maxchar]; //Define el maximo de caracteres en el nombre del proceso
	int empieza_tam;			 //Define en que espacio de la memoria inicia el proceso
	int tam;					 //Define el tamaño de memoria que ocupara el proceso
	int termina_tam;			 //Define en que espacio de la memoria termina el proceso
	}nodo;

typedef struct bus{
	int ini;
	int fin;
}bus;	

nodo ram[maxr];
int  mapabits[maxf][maxc], hdd[maxr], np=0 , total=0; //np=numero de proceso, hdd= Hard Drive Disc(Espacio del disco), total= es la suma de todos los procesos registrados

void crear();
void eliminar();
bus busqueda(char nombre[maxchar]);
void menu();
void menuA();
void menuB();
void menuop3();
void mapits();
void lises();

int main(int argc, char const *argv[])
{		
	menu();
	return 0;
}

void crear(){
	char c[3], p[]="proceso ";
	int i, j;

	printf("Ingrese el tamaño del proceso: ");
	scanf("%d",&ram[total].tam);
	if ((total+ram[total].tam)<80){		 //Compara que el total mas el tamaño a ingresar no superen la memoria
		sprintf(c, "%d", np+1);			 //convierte el numero de proceso a cadena
		strcat(p, c);                    //concatena las cadenas proceso + np;
		strcpy(ram[total].nombreproceso, p);//copia la cadena que contiene el nombre del proceso al proceso
		ram[total].empieza_tam=total;       //Le asigna el espacio en el que empieza la asignación de memoria al proceso
		ram[total].termina_tam=total+ram[total].tam-1;	//Le asigna el espacio en el que termina la asignación de memoria al proceso
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[total].nombreproceso,ram[total].empieza_tam,ram[total].tam,ram[total].termina_tam); //piensa si mejor int o char //scanf("%s", &);
		for(i= total+1; i < total+ram[total].tam; i++){	 //El for se utiliza, cuando el tamaño del proceso es mayor a uno, lo cual hace que haga las asignaciones necesarias.
			strcpy(ram[i].nombreproceso, p);         //copia la cadena que contiene el nombre del proceso al proceso
			ram[i].empieza_tam=total;				 //Le asigna el espacio en el que empieza la asignación de memoria al proceso
			ram[i].tam=ram[total].tam;					 //Le asigna el espacio asignado de memoria al proceso
			ram[i].termina_tam=total+ram[total].tam-1;  //Le asigna el espacio en el que termina la asignación de memoria al proceso
			printf("n: %s et: %d t: %d tt: %d creado\n", ram[i].nombreproceso,ram[i].empieza_tam,ram[i].tam,ram[i].termina_tam); //piensa si mejor int o char //scanf("%s", &);
		}		
		total+=ram[total].tam;
		np++;
	}
	else{
		printf("Error Memoria llena, borre algun programa liberar memoria e intente de nuevo\n"); //Imprime un erro ya que si se ingresa el nuevo proceso hay un desbordamiento en la memoria
	} 
	return;
}

void eliminar(){
	struct bus busq;
	char nombre[maxchar];
	getchar();
	printf("Nombre del proceso a eliminar (Maximo 10 caracteres): ");
	fgets(nombre, 12, stdin);
	busq=busqueda(nombre);
	for(busq.ini; busq.ini < busq.fin; busq.ini++){
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[busq.ini].nombreproceso,ram[busq.ini].empieza_tam,ram[busq.ini].tam,ram[busq.ini].termina_tam); //piensa si mejor int o char //scanf("%s", &);
	}
	return;
}

bus busqueda(char nombre[maxchar]){
	bus bu;
	int i;
	printf("%s\n", nombre);
	strcat(nombre, "\n");
	for(i=0;i<total;i++){
		printf("n: %d creado\n", strcmp(ram[i].nombreproceso,nombre));
		if( strcmp(ram[i].nombreproceso,nombre)==0){
			bu.ini=ram[i].empieza_tam;
			bu.fin=ram[i].termina_tam;
			printf("i:%d, f:%d", bu.ini, bu.fin);
			return bu;
		}
	}
}

void menu(){
	int op;
	do{
		printf("-----Menu-----\n");
		printf("1. Practica A\n");
		printf("2. Practica B\n");
		printf("3. Salir\n");
		printf("Opcion a elegir: ");
		scanf("%d",&op);
		switch(op){
			case 1: menuA();
					break;
			case 2: menuB();
					break;
			case 3: break;		
			default: break;				
		}
	}while(op!=3);
	return;
}

void menuA(){
	int op;
	do{
		printf("----- Menu Practica A -----\n");
		printf("1. Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Representación RAM disponible\n");
		printf("4. Salir\n");
		printf("Opcion a elegir: ");
		scanf("%d",&op);
		switch(op){
			case 1: 
					crear();
					break;
			case 2:
					eliminar();
					break;
			case 3:
					menuop3();
					break;
			case 4: break;	
			default: break;

		}
	}while(op!=4);
	return;
}

void menuB(){
	int op;
	do{
		printf("----- Menu Practica B -----\n");
		printf("1. Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Representación RAM disponible\n");
		printf("4. Intercambio\n");
		printf("5. Salir\n");
		printf("Opcion a elegir: ");
		scanf("%d",&op);
		switch(op){
			case 1: crear();
					break;
			case 2:
					eliminar();
					break;
			case 3:
					menuop3();
					break;
			case 4: 
					break;
			case 5:
					break;	
			default: break;					
		}
	}while(op!=5);
	return;
}

void menuop3(){
	int op;
	do{
		printf("----- Menu Opcion 3 -----\n");
		printf("1. Mapa de Bits\n");
		printf("2. Lista libres\n");
		printf("3. Salir\n");
		printf("Opcion a elegir: ");
		scanf("%d",&op);
		switch(op){
			case 1:
					mapits();//Llama a función mapa de beats
					break;
			case 2: 
					lises();//Llama a función Lista Libres
					break;
			case 3: break;		
			default: break;				
		}
	}while(op!=3);
	return;
}

void mapits(){
	return;
}

void lises(){
	return;
}