#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*programa que simula el funcionamiento de la memoria RAM
  Ortega Zitle Ariel
  Aguirre Olvera Jose Manuel
  Sistemas Operativos 2*/
//estrucutura para listas ligadas

int ram[79], mapabits[10][8], recorrido[80], hdd[80];

typedef struct nodo{
	char nombreproceso[10];
	int empieza_tam;
	int termina_tam;
	struct nodo *sig;		
	}nodo;

void menu(){
	
}
void menuA(){
	int op, i=0 ;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Visualizar RAM\n");
		printf("4. Representación RAM disponible\n");
		printf("5. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1: printf("Creando el proceso %d \n", i); //piensa si mejor int o char //scanf("%s", &);
					i++;
					break;
			case 2:
					break;
			case 3:
					vismem();
					break;
			case 4:
					printf("Menu\n");
					printf("1 Mapa de Bits");
					printf("2 Lista libres");
					scanf("%d",&op);
					switch(op){
						case 1:
								mapits();//Llama a función mapa de beats
								break;
						case 2: 
								lises();//Llama a función Lista Libres
								break;		
					}
					break;
			case 5: 
					break;		
		}
	}while(op!=5);
	return;
}
void menuB(){
	int op, i=0 ;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Visualizar RAM\n");
		printf("4. Representación RAM disponible\n");
		printf("5. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1: printf("Creando el proceso %d \n", i); //piensa si mejor int o char //scanf("%s", &);
					i++;
					break;
			case 2:
					break;
			case 3:	
					vismem();//Llama la funcion Visualizar memoria
					break;
			case 4:
					printf("Menu\n");
					printf("1 Mapa de Bits");
					printf("2 Lista libres");
					scanf("%d",&op);
					switch(op){
						case 1:
								mapits();//Llama a función mapa de beats
								break;
						case 2: 
								lises();//Llama a función Lista Libres
								break;		
					}
					break;
			case 5: 
					break;
			case 6:
					break;				
		}
	}while(op!=6);
	return;
}


void vismem(){

}

void mapits(){

}

void lises(){

}

int main(int argc, char const *argv[])
{
		

	return 0;
}

