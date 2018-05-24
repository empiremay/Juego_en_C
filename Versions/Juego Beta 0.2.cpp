//Juego Version Beta 0.2
#include<stdio.h>
#include<stdlib.h>
#define N 6
#define V 600

typedef struct{
	int matriz[N][N];
	int vida;
	int fila,col;
	int objfila,objcol;
}tEstado;

void Aclaracion() {
	printf("Bienvenido a mi juego en C version 0.2\n\n");
	printf("El objetivo de este juego es llegar a la posicion (%d,%d) del tablero\nque se mostrara a continuacion.\n\n",N,N);
	printf("Pero antes de nada debes saber que la ficha que controlaras\nsera la siguiente: %c\n\n",16);
	printf("Presiona cualquier letra para comenzar el juego");
	printf("\n\n");
	system("pause");
}

void dispState(tEstado *estado) {
	int i,j;
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			printf("%d",estado->matriz[i][j]);
		}
		printf("\n");
	}
}

void dispEstado(tEstado *estado) {
	int i,j;
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			switch(estado->matriz[i][j]) {
				case 2: printf("%c",254); break;
				case 1: printf("%c",22); break;
				case 5: printf("%c",16); break;
				case 3: printf("%c",25); break;
				case 4: printf("%c",00); break;
				default: printf("%c",176);
			}
		}
		printf("\n");
	}
}

void dispVida(tEstado *estado) {
	if((estado->vida)<501) {
		if((estado->vida)>400) {
			printf("Vida:%c%c%c%c%c",254,254,254,254,254);
		}
		else {
			if((estado->vida)>300) {
				printf("Vida:%c%c%c%c",254,254,254,254);
			}
			else {
				if((estado->vida)>200) {
					printf("Vida:%c%c%c",254,254,254);
				}
				else {
					if((estado->vida)>100) {
						printf("Vida:%c%c",254,254);
					}
					else {
						if((estado->vida)>0) {
							printf("Vida:%c",254);
						}
						else {
							printf("Vida:");
						}
					}
				}
			}
		}
	}
	else {
		printf("Vida:%c%c%c%c%c%c",254,254,254,254,254,254);
	}
}

int testObjetivo(tEstado *estado) {
	int objetivo=0;
	if(estado->matriz[estado->objfila][estado->objcol]==5) {
		objetivo=1;
	}
	return objetivo;
}

tEstado *crearEstado(int matriz[N][N]) {
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=matriz[i][j];
         estado->matriz[i][j]=ficha;
         estado->fila=i;
         estado->col=j;
      }
   return estado;
}

int esValido(tEstado *estado, int op) {
	int valido;
	switch(op) {
		case 3: valido=(estado->fila)>0 && estado->matriz[estado->fila-1][estado->col]!=4; break;
		case 4: valido=estado->fila<(N-1) && estado->matriz[estado->fila+1][estado->col]!=4; break;
		case 1: valido=estado->col<(N-1) && estado->matriz[estado->fila][estado->col+1]!=4; break;
		case 2: valido=estado->col>0 && estado->matriz[estado->fila][estado->col-1]!=4; break;
		default: valido=0;
	}
	return valido;
}

tEstado *aplicaOperador(tEstado *estado, int op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	switch(op) {
		case 3: nuevo->fila=nuevo->fila-1; break;
		case 4: nuevo->fila=nuevo->fila+1; break;
		case 1: nuevo->col=nuevo->col+1; break;
		case 2: nuevo->col=nuevo->col-1; break;
	}
	switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
		case 2: nuevo->vida=(nuevo->vida)-200; break;
		case 1: nuevo->vida=(nuevo->vida)-100; break;
	}
	nuevo->matriz[estado->fila][estado->col]=0;
	nuevo->matriz[nuevo->fila][nuevo->col]=5;
	return nuevo;
}

int main() {
	tEstado *estado_Inicial=(tEstado *)malloc(sizeof(tEstado));
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
	int estado_inicial[N][N]={{5,1,0,2,0,4},{1,0,2,0,1,4},{1,1,2,2,0,4},{0,1,2,0,2,4},{2,0,1,1,3,4},{4,4,4,4,4,4}};
	int nivel_2[N][N]={{5,0,0,0,0,0},{0,0,1,0,0,0},{0,2,0,2,2,0},{3,0,0,0,0,0},{0,0,0,0,1,0},{0,0,0,0,0,0}};
	int k,op;
	int nivel=0;
	estado_Inicial=crearEstado(estado_inicial);
	estado_Inicial->vida=V;
	estado_Inicial->col=0;
	estado_Inicial->fila=0;
	estado_Inicial->objfila=4;
	estado_Inicial->objcol=4;
	Aclaracion();
	printf("\n");
	dispEstado(estado_Inicial);
	printf("\n");
	dispVida(estado_Inicial);
	estado=estado_Inicial;
	for(k=0;k!=-1;k++) {
		if(estado->vida<=0) {
			printf("\n\tHAS MUERTO");
			return 0;
		}
		if(testObjetivo(estado)) {
			nivel++;
			if(nivel==2) {
				printf("\n\tHAS GANADO");
				return 0;
			}
			printf("\n\n\tNIVEL 2\n\n");
			estado_Inicial=crearEstado(nivel_2);
			estado_Inicial->vida=V-100 ;
			estado_Inicial->col=0;
			estado_Inicial->fila=0;
			estado_Inicial->objfila=3;
			estado_Inicial->objcol=0;
			estado=estado_Inicial;
			dispEstado(estado);
			printf("\n");
			dispVida(estado);
		}
		printf("\n\nIntroduce el movimiento:\t1:DERECHA  2:IZQUIERDA  3:ARRIBA  4:ABAJO\n\t");
		scanf("%d",&op);
		printf("\n");
		if(esValido(estado,op)) {
			nuevo=aplicaOperador(estado,op);
			dispEstado(nuevo);
			printf("\n");
			dispVida(nuevo);
			estado=nuevo;
			printf("\n");
		}
		else {
			printf("No se puede aplicar el operador\n");
		}
	}
	return 0;
}
