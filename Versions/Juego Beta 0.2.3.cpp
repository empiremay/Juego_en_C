//Juego Version Beta 0.2.3
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
	printf("Bienvenido a mi juego en C versi%cn 0.2.3\n\n",162);
	printf("El objetivo de este juego es llegar al bloque %c del tablero\nque se mostrar%c a continuaci%cn.\n\n",25,160,162);
	printf("Pero antes de nada debes saber que la ficha que controlar%cs\nser%c la siguiente: %c\n\n",160,160,16);
	printf("Para navegar usa las teclas w,a,s,d\n\n");
	printf("Presiona cualquier tecla para comenzar el juego");
	printf("\n\n");
	system("pause");
}

void notas() {
	printf("Notas del Parche 0.2.3:\n\n");
	printf("   %c A%cadido sistema m%cs visual y menos repetitivo\n",175,164,160);
	printf("   %c Algunos cambios de caracteres\n",175);
	printf("   %c Nuevo sistema de navegaci%cn w,a,s,d",175,162);
	printf("\n\n");
	system("pause");
}

void dispEstado(tEstado *estado) {
	int i,j;
	for(i=0;i<N;i++) {
		printf("\t");
		for(j=0;j<N;j++) {
			switch(estado->matriz[i][j]) {
				case 2: printf("%c",254); break;
				case 1: printf("%c",22); break;
				case 5: printf("%c",16); break;
				case 3: printf("%c",25); break;
				case 4: printf("%c",00); break;
				case 6: printf("%c",1); break;
				default: printf("%c",176);
			}
		}
		printf("\n");
	}
}

void dispVida(tEstado *estado) {
	printf("\t");
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

int esValido(tEstado *estado, char op) {
	int valido;
	switch(op) {
		case 'w': valido=(estado->fila)>0 && estado->matriz[estado->fila-1][estado->col]!=4; break;
		case 's': valido=estado->fila<(N-1) && estado->matriz[estado->fila+1][estado->col]!=4; break;
		case 'd': valido=estado->col<(N-1) && estado->matriz[estado->fila][estado->col+1]!=4; break;
		case 'a': valido=estado->col>0 && estado->matriz[estado->fila][estado->col-1]!=4; break;
		default: valido=0;
	}
	return valido;
}

tEstado *aplicaOperador(tEstado *estado, char op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	switch(op) {
		case 'w': nuevo->fila=nuevo->fila-1; break;
		case 's': nuevo->fila=nuevo->fila+1; break;
		case 'd': nuevo->col=nuevo->col+1; break;
		case 'a': nuevo->col=nuevo->col-1; break;
	}
	switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
		case 6: nuevo->vida=0; break;
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
	int estado_inicial[N][N]={{5,1,1,0,1,4},{2,0,2,4,1,4},{0,1,0,4,0,4},{1,1,2,0,2,4},{0,2,1,1,3,4},{4,4,4,4,4,4}};
	int nivel_2[N][N]={{5,0,0,1,1,0},{4,4,0,0,0,0},{3,4,2,2,4,0},{1,2,2,0,1,0},{0,2,2,0,4,0},{0,0,1,6,1,0}};
	int k;
	char op;
	int nivel=0;
	estado_Inicial=crearEstado(estado_inicial);
	estado_Inicial->vida=V;
	estado_Inicial->col=0;
	estado_Inicial->fila=0;
	estado_Inicial->objfila=4;
	estado_Inicial->objcol=4;
	Aclaracion();
	printf("\n");
	notas();
	printf("\n\n");
	dispEstado(estado_Inicial);
	printf("\n");
	dispVida(estado_Inicial);
	printf("\n");
	estado=estado_Inicial;
	for(k=0;k!=-1;k++) {
		if(estado->vida<=0) {
			printf("\n\n\n%c%c%c%c%c%c%c%c HAS MUERTO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
			return 0;
		}
		if(testObjetivo(estado)) {
			nivel++;
			if(nivel==2) {
				printf("\n\n\n%c%c%c%c%c%c%c%c HAS GANADO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
				return 0;
			}
			printf("\n\n\n\tNIVEL 2\n\n\n");
			estado_Inicial=crearEstado(nivel_2);
			estado_Inicial->vida=V;
			estado_Inicial->col=0;
			estado_Inicial->fila=0;
			estado_Inicial->objfila=2;
			estado_Inicial->objcol=0;
			estado=estado_Inicial;
			dispEstado(estado);
			printf("\n");
			dispVida(estado);
			printf("\n");
		}
		scanf("%c",&op);
		fflush(stdin);
		printf("\n\n");
		if(esValido(estado,op)) {
			nuevo=aplicaOperador(estado,op);
			dispEstado(nuevo);
			printf("\n");
			dispVida(nuevo);
			estado=nuevo;
			printf("\n");
		}
		else {
			printf("No se puede aplicar el operador\n\n\n");
			dispEstado(estado);
			printf("\n");
			dispVida(estado);
			printf("\n");
		}
	}
	return 0;
}
