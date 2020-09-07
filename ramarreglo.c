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
	int defesp;
	}nodo;

typedef struct bus{				 //Estructura para regresar los valores del proceso buscado
	int ini;					 //Define donde inicia el proceso buscado
	int fin;					 //Define donde finaliza el proceso buscado 
}bus;	

nodo ram[maxr];							//Crea un arreglo de 80 espacios que repesenta la RAM
nodo HDD[maxr];							//hdd= Hard Drive Disc(Espacio del disco
int  np=0 , total=0, totalHDD=0; 					//np=numero de proceso, total= es la suma de todos los procesos registrados

void crear();         					//Prototipo para la función crear proceso
void eliminar();						//Prototipo para la función eliminar proceso
bus busqueda(char nombre[maxchar]);		//Prototipo para la función busqueda de proceso
void menu();							//Prototipo para la función menu principal
void menuop3();							//Prototipo para la función submenu opción 3
void mapits();							//Prototipo para la función representar mapa de bits
void lises();							//Prototipo para la función representar listas libres
void cambRAM();                         //Prototipo para la función cambiar de RAM a HDD
void cambHDD();                         //Prototipo para la función cambiar de HDD a RAM

int main(int argc, char const *argv[])  //Inicia el proceso
{		
	menu();								//Llama a la función del menu principal
	return 0;
}

void crear(){
	char c[10], p[12];
	int i, j, k, f,tamano;

	printf("Ingrese el tamaño del proceso: ");
	scanf("%d",&tamano);
	if ((total+tamano)<=80){		 			//Compara que el total mas el tamaño a ingresar no superen la memoria
		do{														//Empieza el do/while
			printf("Ingrese el numero del proceso: ");
			scanf("%d",&np);									//Escanea el numero del proceso
			if(np<=0){											//Compara que el numero sea mayor a 0
				printf("¡Error!, Ingrese un numero valido");
				f=1;											//Bandera para hacer bucle do/while
			}
			else{
				strcpy(c,"");									//Limpia la variable c
				strcpy(p,"proceso ");							//Pone el texto predeterminado a p
				f=0;											//Bandera para pasar el do/while
				sprintf(c, "%d", np);			 				//convierte el numero de proceso a cadena
				strcat(p, c);									//Concatena las cadenas c y p en p
				for(i=0; i<total; i++){
					if(strcmp(p, ram[i].nombreproceso)==0 && f==0){
						f=1;									//Bandera para hacer bucle do/while
						printf("¡Error! proceso existente, intente con otro numero\n");
					}
				}
			}
		}while(f!=0);											//termina do/while
		strcpy(ram[total].nombreproceso, p);			//copia la cadena que contiene el nombre del proceso al proceso
		ram[total].empieza_tam=total;       			//Le asigna el espacio en el que empieza la asignación de memoria al proceso
		ram[total].tam=tamano;							//Le asigna el espacio en el que ocupa de memoria al proceso
		ram[total].termina_tam=total+ram[total].tam-1;	//Le asigna el espacio en el que termina la asignación de memoria al proceso
		ram[total].defesp=1;							//Le asigna la variable 1 para definir que hay un proceso
		for(i= total+1; i < total+ram[total].tam; i++){	//El for se utiliza, cuando el tamaño del proceso es mayor a uno, lo cual hace que haga las asignaciones necesarias.
			strcpy(ram[i].nombreproceso, p);         	//copia la cadena que contiene el nombre del proceso al proceso
			ram[i].empieza_tam=total;				 	//Le asigna el espacio en el que empieza la asignación de memoria al proceso
			ram[i].tam=ram[total].tam;					//Le asigna el espacio asignado de memoria al proceso
			ram[i].termina_tam=total+ram[total].tam-1;  //Le asigna el espacio en el que termina la asignación de memoria al proceso
			ram[i].defesp=1;							//Le asigna la variable 1 para definir que hay un proceso
		}
		printf("n: %s et: %d t: %d tt: %d creado\n", ram[total].nombreproceso,ram[total].empieza_tam,ram[total].tam,ram[total].termina_tam); //Imprime el proceso creado con sus variables asignadas		
		total+=ram[total].tam;
	}
	else{
		for (i= 0; i < total; i++){
			if(strcmp(ram[i].nombreproceso, "Hueco")==0){
				if(tamano<=ram[i].tam){
					do{														//Empieza el do/while
						printf("Ingrese el numero del proceso: ");
						scanf("%d",&np);									//Escanea el numero del proceso
						if(np<=0){											//Compara que el numero sea mayor a 0
							printf("¡Error!, Ingrese un numero valido");
							f=1;											//Bandera para hacer bucle do/while
						}
						else{
							strcpy(c,"");									//Limpia la variable c
							strcpy(p,"proceso ");							//Pone el texto predeterminado a p
							f=0;											//Bandera para pasar el do/while
							sprintf(c, "%d", np);			 				//convierte el numero de proceso a cadena
							strcat(p, c);									//Concatena las cadenas c y p en p
							for(k=0; k<total; k++){
								if(strcmp(p, ram[k].nombreproceso)==0 && f==0){
									f=1;									//Bandera para hacer bucle do/while
									printf("¡Error! proceso existente, intente con otro numero\n");
								}
							}
						}
					}while(f!=0);											//termina do/while
					strcpy(ram[total].nombreproceso, p);
					for (j= i ; j <= i+tamano-1; j++){
						strcpy(ram[j].nombreproceso, p);         	//copia la cadena que contiene el nombre del proceso al proceso
						ram[j].empieza_tam=i;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
						ram[j].tam=tamano;							//Le asigna el espacio asignado de memoria al proceso
						ram[j].termina_tam=i+tamano-1;  			//Le asigna el espacio en el que termina la asignación de memoria al proceso
						ram[j].defesp= 1;							//Le asigna la variable 1 para definir que hay un proceso
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
			strcpy(ram[busq.ini].nombreproceso, "Hueco");	//Le asigna la cadena "Hueco" para definir que hay un hueco
			ram[busq.ini].defesp= 0;						//Le asigna la variable 0 para definir que hay un hueco
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
		printf("----- Menu -----\n");
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

void menuop4(){
	int op;
	do{
		printf("----- Menu Opcion 4 -----\n");
		printf("1. Cambiar de RAM a HDD\n");
		printf("2. Cambiar de HDD a RAM\n");
		printf("3. Salir\n");
		printf("Opcion a elegir: ");
		scanf("%d",&op);
		switch(op){
			case 1:
					cambRAM();//Llama a función mapa de beats
					break;
			case 2: 
					cambHDD();//Llama a función Lista Libres
					break;
			case 3: break;		
			default: break;				
		}
	}while(op!=3);
	return;
}

void mapits(){
	int i, j, cont=0; 
	for ( i = 0; i < 10; i++){
		for ( j = 0; j < 8; j++){
			if (cont<total)
				printf(" %d ",ram[cont].defesp);
			else
				printf(" 0 ");
			cont++;	
		}
		printf("\n");
	}
	return;
}

void lises(){
	int i;
	if(total==0){
		printf(" H 0 80\n");
	}
	else{
		for (i = 0; i < total; i++){
			if(ram[i].defesp==1){
				printf(" P %d %d\n", ram[i].empieza_tam, ram[i].tam);
				i=ram[i].termina_tam;
			}
			else{
				printf(" H %d %d\n", ram[i].empieza_tam, ram[i].tam);
				i=ram[i].termina_tam;
			}	
		}
		if (i<80){
			printf(" H %d %d\n", i, 80-i);
		}
	}
	return;
}

void cambRAM(){
	bus bu;  		//Crea una variables de tipo estructura bus para almacenar el proceso cuando lo encuentre
	char nombre[maxchar];	//Variable para leer el prceso a buscar
	int i, j, f=1;
	do{
		getchar();			//Sirve para limpiar la basura del teclado
		printf("Nombre del proceso a eliminar (Maximo 10 caracteres): ");
		gets(nombre);
		if(strcmp(nombre, "Hueco")!=0){			
			for(i=0;i<total;i++){							  //Busca en todos los procesos disponibles
				if( strcmp(ram[i].nombreproceso,nombre)==0){  //Compara el nombre del proceso [i], con el proceso a buscar para ver si son iguales
					bu.ini=ram[i].empieza_tam;				  //Le asigna el inicio del proceso en la ram 
					bu.fin=ram[i].termina_tam;				  //Le asigna el fin del proceso en la 
					f=0;
				}
			} /*Buscar Posición del proceso*/
			if(f==0){
				for(i=0;i<totalHDD;i++){							  //Busca en todos los procesos disponibles
					if( strcmp(HDD[i].nombreproceso,nombre)==0 && f==0){  //Compara el nombre del proceso [i], con el proceso a buscar para ver si son iguales
							f=1;
							printf("¡Error! proceso existente, intente con otro proceso\n");										  
					}
				}
				if(f==0){
					if ((totalHDD+ram[bu.ini].tam)<=80){
						strcpy(HDD[totalHDD].nombreproceso, ram[bu.ini].nombreproceso);		//copia la cadena que contiene el nombre del proceso al proceso
						HDD[totalHDD].empieza_tam=ram[bu.ini].empieza_tam;       			//Le asigna el espacio en el que empieza la asignación de memoria al proceso
						HDD[totalHDD].tam=ram[bu.ini].tam;									//Le asigna el espacio en el que ocupa de memoria al proceso
						HDD[totalHDD].termina_tam=ram[bu.ini].termina_tam;					//Le asigna el espacio en el que termina la asignación de memoria al proceso
						HDD[totalHDD].defesp=ram[bu.ini].defesp;												//Le asigna la variable 1 para definir que hay un proceso
						for(i= totalHDD+1; i < totalHDD+HDD[totalHDD].tam; i++){			//El for se utiliza, cuando el tamaño del proceso es mayor a uno, lo cual hace que haga las asignaciones necesarias.
							strcpy(HDD[i].nombreproceso, ram[bu.ini].nombreproceso);        //copia la cadena que contiene el nombre del proceso al proceso
							HDD[i].empieza_tam=ram[bu.ini].empieza_tam;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
							HDD[i].tam=ram[bu.ini].tam;										//Le asigna el espacio asignado de memoria al proceso
							HDD[i].termina_tam=ram[bu.ini].termina_tam;  					//Le asigna el espacio en el que termina la asignación de memoria al proceso
							HDD[i].defesp=ram[bu.ini].defesp;								//Le asigna la variable 1 para definir que hay un proceso
						}
						printf("n: %s et: %d t: %d tt: %d creado\n", HDD[totalHDD].nombreproceso,HDD[totalHDD].empieza_tam,HDD[totalHDD].tam,HDD[totalHDD].termina_tam); //Imprime el proceso creado con sus variables asignadas		
						totalHDD+=HDD[totalHDD].tam;
					}
					else{
						for (i= 0; i < totalHDD; i++){
							if(strcmp(HDD[i].nombreproceso, "Hueco")==0){
								if(ram[bu.ini].tam<=HDD[i].tam){
									for (j= i ; j <= i+ram[bu.ini].tam-1; j++){
										strcpy(HDD[i].nombreproceso, ram[bu.ini].nombreproceso);        //copia la cadena que contiene el nombre del proceso al proceso
										HDD[i].empieza_tam=ram[bu.ini].empieza_tam;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
										HDD[i].tam=ram[bu.ini].tam;										//Le asigna el espacio asignado de memoria al proceso
										HDD[i].termina_tam=ram[bu.ini].termina_tam;  					//Le asigna el espacio en el que termina la asignación de memoria al proceso
										HDD[i].defesp=ram[bu.ini].defesp;								//Le asigna la variable 1 para definir que hay un proceso
									}
									printf("n: %s et: %d t: %d tt: %d creado\n", HDD[j-1].nombreproceso,HDD[j-1].empieza_tam,HDD[j-1].tam,HDD[j-1].termina_tam); //Imprime el proceso creado con sus variables asignadas
								}
								return;
							}
						}	
							printf("Error Memoria llena, borre algun programa liberar memoria e intente de nuevo\n"); //Imprime un erro ya que si se ingresa el nuevo proceso hay un desbordamiento en la memoria
					}//Agregar termina
					for(bu.ini; bu.ini <= bu.fin; bu.ini++){
						strcpy(ram[bu.ini].nombreproceso, "Hueco");	//Le asigna la cadena "Hueco" para definir que hay un hueco
						ram[bu.ini].defesp= 0;						//Le asigna la variable 0 para definir que hay un hueco
						printf("n: %s et: %d t: %d tt: %d creado\n", ram[bu.ini].nombreproceso,ram[bu.ini].empieza_tam,ram[bu.ini].tam,ram[bu.ini].termina_tam); //piensa si mejor int o char //scanf("%s", &);
					}
				}
			}
			else
				printf("¡Error! Proceso no encontrado");
		}
		else{
		printf("¡Error, no se puede liberar la memoria disponible!\n");
		}
	}while(f!=0);
	return;
}

void cambHDD(){
	bus bu;  		//Crea una variables de tipo estructura bus para almacenar el proceso cuando lo encuentre
	char nombre[maxchar];	//Variable para leer el prceso a buscar
	int i, j, f=1;
	do{
		getchar();			//Sirve para limpiar la basura del teclado
		printf("Nombre del proceso a eliminar (Maximo 10 caracteres): ");
		gets(nombre);
		if(strcmp(nombre, "Hueco")!=0){			
			for(i=0;i<totalHDD;i++){							  //Busca en todos los procesos disponibles
				if( strcmp(HDD[i].nombreproceso,nombre)==0){  //Compara el nombre del proceso [i], con el proceso a buscar para ver si son iguales
					bu.ini=HDD[i].empieza_tam;				  //Le asigna el inicio del proceso en la HDD 
					bu.fin=HDD[i].termina_tam;				  //Le asigna el fin del proceso en la 
					f=0;
				}
			} /*Buscar Posición del proceso*/
			if(f==0){
				for(i=0;i<total;i++){							  //Busca en todos los procesos disponibles
					if( strcmp(ram[i].nombreproceso,nombre)==0 && f==0){  //Compara el nombre del proceso [i], con el proceso a buscar para ver si son iguales
							f=1;
							printf("¡Error! proceso existente, intente con otro proceso\n");										  
					}
				}
				if(f==0){
					if ((total+HDD[bu.ini].tam)<=80){
						strcpy(ram[total].nombreproceso, HDD[bu.ini].nombreproceso);		//copia la cadena que contiene el nombre del proceso al proceso
						ram[total].empieza_tam=HDD[bu.ini].empieza_tam;       			//Le asigna el espacio en el que empieza la asignación de memoria al proceso
						ram[total].tam=HDD[bu.ini].tam;									//Le asigna el espacio en el que ocupa de memoria al proceso
						ram[total].termina_tam=HDD[bu.ini].termina_tam;					//Le asigna el espacio en el que termina la asignación de memoria al proceso
						ram[total].defesp=HDD[bu.ini].defesp;												//Le asigna la variable 1 para definir que hay un proceso
						for(i= total+1; i < total+ram[total].tam; i++){			//El for se utiliza, cuando el tamaño del proceso es mayor a uno, lo cual hace que haga las asignaciones necesarias.
							strcpy(ram[i].nombreproceso, HDD[bu.ini].nombreproceso);        //copia la cadena que contiene el nombre del proceso al proceso
							ram[i].empieza_tam=HDD[bu.ini].empieza_tam;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
							ram[i].tam=HDD[bu.ini].tam;										//Le asigna el espacio asignado de memoria al proceso
							ram[i].termina_tam=HDD[bu.ini].termina_tam;  					//Le asigna el espacio en el que termina la asignación de memoria al proceso
							ram[i].defesp=HDD[bu.ini].defesp;								//Le asigna la variable 1 para definir que hay un proceso
						}
						printf("n: %s et: %d t: %d tt: %d creado\n", ram[total].nombreproceso,ram[total].empieza_tam,ram[total].tam,ram[total].termina_tam); //Imprime el proceso creado con sus variables asignadas		
						total+=ram[total].tam;
					}
					else{
						for (i= 0; i < total; i++){
							if(strcmp(ram[i].nombreproceso, "Hueco")==0){
								if(HDD[bu.ini].tam<=ram[i].tam){
									for (j= i ; j <= i+HDD[bu.ini].tam-1; j++){
										strcpy(ram[i].nombreproceso, HDD[bu.ini].nombreproceso);        //copia la cadena que contiene el nombre del proceso al proceso
										ram[i].empieza_tam=HDD[bu.ini].empieza_tam;				 		//Le asigna el espacio en el que empieza la asignación de memoria al proceso
										ram[i].tam=HDD[bu.ini].tam;										//Le asigna el espacio asignado de memoria al proceso
										ram[i].termina_tam=HDD[bu.ini].termina_tam;  					//Le asigna el espacio en el que termina la asignación de memoria al proceso
										ram[i].defesp=HDD[bu.ini].defesp;								//Le asigna la variable 1 para definir que hay un proceso
									}
									printf("n: %s et: %d t: %d tt: %d creado\n", ram[j-1].nombreproceso,ram[j-1].empieza_tam,ram[j-1].tam,ram[j-1].termina_tam); //Imprime el proceso creado con sus variables asignadas
								}
								return;
							}
						}	
							printf("Error Memoria llena, borre algun programa liberar memoria e intente de nuevo\n"); //Imprime un erro ya que si se ingresa el nuevo proceso hay un desbordamiento en la memoria
					}//Agregar termina
					for(bu.ini; bu.ini <= bu.fin; bu.ini++){
						strcpy(HDD[bu.ini].nombreproceso, "Hueco");	//Le asigna la cadena "Hueco" para definir que hay un hueco
						HDD[bu.ini].defesp= 0;						//Le asigna la variable 0 para definir que hay un hueco
						printf("n: %s et: %d t: %d tt: %d creado\n", HDD[bu.ini].nombreproceso,HDD[bu.ini].empieza_tam,HDD[bu.ini].tam,HDD[bu.ini].termina_tam); //piensa si mejor int o char //scanf("%s", &);
					}
				}
			}
			else
				printf("¡Error! Proceso no encontrado");
		}
		else{
		printf("¡Error, no se puede liberar la memoria disponible!\n");
		}
	}while(f!=0);
	return;
}