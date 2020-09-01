#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*programa que simula el funcionamiento de la memoria RAM
  Ortega Zitle Ariel
  Aguirre Olvera Jose Manuel
  Sistemas Operativos 2*/
//estrucutura para listas ligadas

int ram[79], mapabits[7][79], recorrido[79], hdd[79];

typedef struct nodo{
	char nombreproceso[10];
	int empieza_tam;
	int termina_tam;
	struct nodo *sig;		
	}nodo;

void menu(){
	
}
void menuA(){
	int f=0, op, i=0 ;
	do{
		printf("Menu\n");
		printf("1.Crear proceso\n");
		printf("2. Eliminar proceso\n");
		printf("3. Visualizar RAM\n");
		printf("4. Intercambio(Aun no programar)\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1: printf("Creando el proceso %d \n", i); //piensa si mejor int o char //scanf("%s", &);
					i++;
					break;
			case 2:
					break;
			case 3:
					break;
			case 4:
					break;
		}
	}while(op!=4);
	return;
}
void menuB(){

}

int main(int argc, char const *argv[])
{
		

	return 0;
}

