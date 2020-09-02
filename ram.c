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
	char nombreproceso[maxchar];
	int empieza_tam;
	int tam;
	int termina_tam;
	struct nodo *sig;		
	}nodo;

nodo ram[maxr];
int  mapabits[maxf][maxc], hdd[maxr], np=0 , pos=0, total=0; //np=numero de proceso, 

void crear(){
	char c[3], p[]="proceso ";
	printf("Ingrese el tamaño del proceso: ");
	scanf("%d",&ram[np].tam);
	if ((total+ram[np].tam)<80)
	{
		sprintf(c, "%d", np+1);//convierte el numero de proceso a cadena
		strcat(p, c);//concatena las cadenas proceso + np;
		strcpy(ram[np].nombreproceso, p);//copia la cadena que contiene el nombre del proceso al proceso
		ram[np].empieza_tam=total;
			ram[np].termina_tam=total+ram[np].tam-1;
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[np].nombreproceso,ram[np].empieza_tam,ram[np].tam,ram[np].termina_tam); //piensa si mejor int o char //scanf("%s", &);
		for(int i=total+1;i<total+ram[np].tam;i++){
			strcpy(ram[i].nombreproceso, p);//copia la cadena que contiene el nombre del proceso al proceso
			ram[i].empieza_tam=total;
			ram[i].tam=ram[np].tam;
			ram[i].termina_tam=total+ram[np].tam-1;
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[i].nombreproceso,ram[i].empieza_tam,ram[i].tam,ram[i].termina_tam); //piensa si mejor int o char //scanf("%s", &);
		}
		total+=ram[np].tam;
		np++;
	}
	else{
		printf("Error Memoria llena, borre algun programa liberar memoria e intente de nuevo\n");
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

int main(int argc, char const *argv[])
{		
	menu();
	return 0;
}

