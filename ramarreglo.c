/*programa que simula el funcionamiento de la memoria RAM
  Ortega Zitle Ariel
  Aguirre Olvera Jose Manuel
  Sistemas Operativos 2
  
  Lo que hace el programa es simular la memoria RAM.
  Apartir de dos opciones donde la opción A) Solo tiene 4 opciones para el manejo de la RAM y 
  La opcion B) tiene 5 opciones, la opcion agregada a B) es la opcion de enviar archivos al disco
  a partir de la memoria RAM y de la RAM al disco.
  
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxr    80 //define el maximo de espacios en la memoria ram y HDD
#define maxchar 12 //define el maximo de caracteres
#define maxf    10 //define el maximo de filas
#define maxc     8 //define el maximo de columnas 

typedef struct nodo{			 //Estructuta que define cada espacio de la ram
	char nombreproceso[maxchar]; //Define el maximo de caracteres en el nombre del proceso
	int empieza_tam;			 //Define en que espacio de la memoria inicia el proceso
	int tam;					 //Define el tamaño de memoria que ocupara el proceso
	int termina_tam;			 //Define en que espacio de la memoria termina el proceso
	}nodo;

typedef struct bus{				 //Estructura para regresar los valores del proceso buscado
	int ini;					 //Define donde inicia el proceso buscado
	int fin;					 //Define donde finaliza el proceso buscado 
}bus;	

nodo ram[maxr];										  //Crea un arreglo de 80 espacios que repesenta la RAM
int  mapabits[maxf][maxc], hdd[maxr], np=0 , total=0; //np=numero de proceso, hdd= Hard Drive Disc(Espacio del disco), total= es la suma de todos los procesos registrados

void crear();         					//Prototipo para la función crear proceso
void eliminar();						//Prototipo para la función eliminar proceso
bus busqueda(char nombre[maxchar]);		//Prototipo para la función busqueda de proceso
void menu();							//Prototipo para la función menu principal
void menuA();							//Prototipo para la función menu opción A
void menuB();							//Prototipo para la función menu opción B
void menuop3();							//Prototipo para la función submenu opción 3
void mapits();							//Prototipo para la función representar mapa de bits
void lises();							//Prototipo para la función representar listas libres

int main(int argc, char const *argv[])  //Inicia el proceso
{		
	menu();								//Llama a la función del menu principal
	return 0;
}

void crear(){
	char c[10], p[12]="proceso ";
	int i, j, f,tamano;

	printf("Ingrese el tamaño del proceso: ");
	scanf("%d",&tamano);
	if ((total+tamano)<=80){		 			//Compara que el total mas el tamaño a ingresar no superen la memoria
		do{
            printf("Ingrese el numero del proceso: ");
            scanf("%d",&np);
            if(np<=0){
                printf("¡Error!, Ingrese un numero valido");
                f=1;
            }
            else{
                f=0;
            }
        }while(f!=0);
        sprintf(c, "%d", np);			 				//convierte el numero de proceso a cadena
		strcat(p, c);                    				//concatena las cadenas proceso + np;
		strcpy(ram[total].nombreproceso, p);			//copia la cadena que contiene el nombre del proceso al proceso
		ram[total].empieza_tam=total;       			//Le asigna el espacio en el que empieza la asignación de memoria al proceso
		ram[total].tam=tamano;							//Le asigna el espacio en el que ocupa de memoria al proceso
		ram[total].termina_tam=total+ram[total].tam-1;	//Le asigna el espacio en el que termina la asignación de memoria al proceso
		for(i= total+1; i < total+ram[total].tam; i++){	//El for se utiliza, cuando el tamaño del proceso es mayor a uno, lo cual hace que haga las asignaciones necesarias.
			strcpy(ram[i].nombreproceso, p);         	//copia la cadena que contiene el nombre del proceso al proceso
			ram[i].empieza_tam=total;				 	//Le asigna el espacio en el que empieza la asignación de memoria al proceso
			ram[i].tam=ram[total].tam;					//Le asigna el espacio asignado de memoria al proceso
			ram[i].termina_tam=total+ram[total].tam-1;  //Le asigna el espacio en el que termina la asignación de memoria al proceso
		}
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[total].nombreproceso,ram[total].empieza_tam,ram[total].tam,ram[total].termina_tam); //Imprime el proceso creado con sus variables asignadas		
		total+=ram[total].tam;
	}
	else{
		for (i= 0; i < total; i++){
			if(strcmp(ram[i].nombreproceso, "Hueco")==0){
				printf("c:%s\n ",ram[i].nombreproceso);
				printf("Tam: %d, AR: %d", i, ram[i].tam);
				if(tamano<=ram[i].tam){
					do{
						printf("Ingrese el numero del proceso: ");
						scanf("%d",&np);
						if(np<=0){
							printf("¡Error!, Ingrese un numero valido");
							f=1;
						}
						else{
							f=0;
						}
        			}while(f!=0);
					sprintf(c, "%d", np);			 				//convierte el numero de proceso a cadena
					strcat(p, c); 
					for (j= i ; j <= i+tamano-1; j++){
						strcpy(ram[j].nombreproceso, p);         	//copia la cadena que contiene el nombre del proceso al proceso
						ram[j].empieza_tam=i;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
						ram[j].tam=tamano;							//Le asigna el espacio asignado de memoria al proceso
						ram[j].termina_tam=i+tamano-1;  			//Le asigna el espacio en el que termina la asignación de memoria al proceso
					}
					printf("n: %s et: %d t: %d tt: %d creado\n", ram[j-1].nombreproceso,ram[j-1].empieza_tam,ram[j-1].tam,ram[j-1].termina_tam); //Imprime el proceso creado con sus variables asignadas
				}
				return;
			}
		}	
			printf("Error Memoria llena, borre algun programa liberar memoria e intente de nuevo\n"); //Imprime un erro ya que si se ingresa el nuevo proceso hay un desbordamiento en la memoria
	}
	return;
}

void eliminar(){
	struct bus busq;			//Variable para el proceso buscado
	char nombre[maxchar];		//Variable para leer el prceso a buscar
	getchar();					//Sirve para limpiar la basura del teclado
	printf("Nombre del proceso a eliminar (Maximo 10 caracteres): ");
	gets(nombre);				//Lee el proceso a buscar
	if(strcmp(nombre, "Hueco")!=0){
		busq=busqueda(nombre);		//Llama la funcion para buscar el nombre, la cual regresa una estructura
		for(busq.ini; busq.ini <= busq.fin; busq.ini++){
			strcpy(ram[busq.ini].nombreproceso, "Hueco");
			printf("n: %s et: %d t: %d tt: %d creado\n", ram[busq.ini].nombreproceso,ram[busq.ini].empieza_tam,ram[busq.ini].tam,ram[busq.ini].termina_tam); //piensa si mejor int o char //scanf("%s", &);
		}
	}
	else{
		printf("¡Error, no se puede liberar la memoria disponible!\n");
	}
	return;
}

bus busqueda(char nombre[maxchar]){
	bus bu;  		//Crea una variables de tipo estructura bus para almacenar el proceso cuando lo encuentre
	int i;			
	printf("%s\n", nombre);
	for(i=0;i<total;i++){							  //Busca en todos los procesos disponibles
		if( strcmp(ram[i].nombreproceso,nombre)==0){  //Compara el nombre del proceso [i], con el proceso a buscar para ver si son iguales
			bu.ini=ram[i].empieza_tam;				  //Le asigna el inicio del proceso en la ram 
			bu.fin=ram[i].termina_tam;				  //Le asigna el fin del proceso en la ram
			return bu;								  //Regresa la estructura para utilizarla en la funcion que hizo el llamado
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