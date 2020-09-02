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

int ram[79], mapabits[10][8], recorrido[80], hdd[80], i=0;

typedef struct nodo{
	char nombreproceso[10];
	int empieza_tam;
	int tam;
	int termina_tam;
	struct nodo *sig;		
	}nodo;





void menu(){
	int op;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Salir");
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
	int op, tam;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Representación RAM disponible\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1: 
					printf("Ingrese el tamaño del proceso: ");
					scanf("%d",&tam);
					printf("\n");
					printf("Creando el proceso %d \n", i); //piensa si mejor int o char //scanf("%s", &);
					i++;
					break;
			case 2:
					break;
			case 3:
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
			case 4: break;	
			default: break;

		}
	}while(op!=4);
	return;
}

void menuB(){
	int op, i=0 ;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Representación RAM disponible\n");
		printf("4. Intercambio\n");
		printf("5. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1: printf("Creando el proceso %d \n", i); //piensa si mejor int o char //scanf("%s", &);
					i++;
					break;
			case 2:
					break;
			case 3:
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
			case 4: 
					break;
			case 5:
					break;	
			default: break;					
		}
	}while(op!=5);
	return;
}

void mapits(){

}

void lises(){

}

int main(int argc, char const *argv[])
{		
	menu();
	return 0;
}

