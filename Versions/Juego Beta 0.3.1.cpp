//Juego Version Beta 0.3.1
#include<stdio.h>
#include<stdlib.h>
#define N 7
#define V 600

typedef struct{
	int matriz[N][N];
	int vida,llaves;
	int fila,col;
	int objfila,objcol;
}tEstado;

void Aclaracion() {
	printf("Bienvenido a mi juego en C versi%cn 0.3.1\n\n\n",162);
	printf("El objetivo de este juego es llegar al bloque %c del tablero\nque se mostrar%c a continuaci%cn.\n\n",25,160,162);
	printf("Pero antes de nada debes saber que la ficha que controlar%cs\nser%c la siguiente: %c\n\n",160,160,16);
	printf("Los bloques %c te quitar%cn 3 puntos de vida, los bloques %c 2 puntos\nde vida y estos bloques %c 1 punto de vida\n\n",219,160,178,177);
	printf("Este bloque te curar%c vida en funci%cn de la que tengas: %c\n\n",160,162,2);
	printf("Las llaves %c te permitir%cn abrir los bloques invisibles\nque est%cn en medio del mapa\n\n",204,160,130);
	printf("Para navegar usa las teclas w,a,s,d\n\n");
	printf("Presiona cualquier tecla para comenzar el juego");
	printf("\n\n");
	system("pause");
}

void notas() {
	printf("Notas del Parche 0.3.1:\n\n");
	printf("   %c Modificaci%cn del nivel 3 (WORK IN PROGRESS)\n",175,162);
	printf("   %c El bloque de curaci%cn cura de forma m%cs adecuada en funci%cn\n     de la vida restante",175,162,160,162);
	printf("\n\n");
	system("pause");
}

void dispfilcol(tEstado *estado) {
	printf("\tFila: %d\tCol: %d",estado->fila,estado->col);
}

void dispEstado(tEstado *estado) {
	int i,j;
	for(i=0;i<N;i++) {
		printf("\t");
		for(j=0;j<N;j++) {
			switch(estado->matriz[i][j]) {
				case 2: printf("%c",178); break;
				case 1: printf("%c",177); break;
				case 5: printf("%c",16); break;
				case 3: printf("%c",25); break;
				case 4: printf("%c",0); break;
				case 6: printf("%c",1); break;
				case 7: printf("%c",2); break;
				case 8: printf("%c",204); break;
				case 9: printf("%c",219); break;
				case 10: printf("%c",0); break;
				default: printf("%c",176);
			}
		}
		printf("\n");
	}
}

void displlaves(tEstado *estado) {
	printf("  ");
	switch(estado->llaves) {
		case 1: printf("Llaves:%c",254); break;
		case 2: printf("Llaves:%c%c",254,254); break;
		case 3: printf("Llaves:%c%c%c",254,254,254); break;
		default: printf("Llaves:");
	}
}

void dispVida(tEstado *estado) {
	printf("\t");
	if((estado->vida)<601) {
		if((estado->vida)>500) {
			printf("Vida:%c%c%c%c%c%c%c",254,254,254,254,254,254,0);
		}
		else {
			if((estado->vida)>400) {
				printf("Vida:%c%c%c%c%c%c%c",254,254,254,254,254,0,0);
			}
			else {
				if((estado->vida)>300) {
					printf("Vida:%c%c%c%c%c%c%c",254,254,254,254,0,0,0);
				}
				else {
					if((estado->vida)>200) {
						printf("Vida:%c%c%c%c%c%c%c",254,254,254,0,0,0,0);
					}
					else {
						if((estado->vida)>100) {
							printf("Vida:%c%c%c%c%c%c%c",254,254,0,0,0,0,0);
						}
						else {
							if((estado->vida)>0) {
								printf("Vida:%c%c%c%c%c%c%c",254,0,0,0,0,0,0);
							}
							else {
								printf("Vida:%c%c%c%c%c%c%c",0,0,0,0,0,0,0);
							}
						}
					}
				}
			}
		}
	}
	else {
		printf("Vida:%c%c%c%c%c%c%c",254,254,254,254,254,254,254);
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
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	int valido=0;
	int valido1=0;
	switch(op) {
		case 'w': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila-1][estado->col]; break;
		case 'W': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila-1][estado->col]; break;
		case 's': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila+1][estado->col]; break;
		case 'S': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila+1][estado->col]; break;
		case 'd': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col+1]; break;
		case 'D': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col+1]; break;
		case 'a': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col-1]; break;
		case 'A': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col-1]; break;
		default: valido=0;
	}
	if((nuevo->matriz[nuevo->fila][nuevo->col])==10) {
		switch(op) {
			case 'w': valido1=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
			case 'W': valido1=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
			case 's': valido1=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
			case 'S': valido1=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
			case 'd': valido1=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+1]!=4; break;
			case 'D': valido1=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+1]!=4; break;
			case 'a': valido1=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-1]!=4; break;
			case 'A': valido1=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-1]!=4; break;
			default: valido1=0;
		}
		if((nuevo->llaves)>0 && valido1==1) {
			valido=1;
		}
		else {
			valido=0;
		}
	}
	else {
		switch(op) {
			case 'w': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
			case 'W': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
			case 's': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
			case 'S': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
			case 'd': valido=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+1]!=4; break;
			case 'D': valido=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+1]!=4; break;
			case 'a': valido=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-1]!=4; break;
			case 'A': valido=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-1]!=4; break;
			default: valido=0;
		}
	}
	return valido;
}

tEstado *aplicaOperador(tEstado *estado, char op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	switch(op) {
		case 'w': nuevo->fila=nuevo->fila-1; break;
		case 'W': nuevo->fila=nuevo->fila-1; break;
		case 's': nuevo->fila=nuevo->fila+1; break;
		case 'S': nuevo->fila=nuevo->fila+1; break;
		case 'd': nuevo->col=nuevo->col+1; break;
		case 'D': nuevo->col=nuevo->col+1; break;
		case 'a': nuevo->col=nuevo->col-1; break;
		case 'A': nuevo->col=nuevo->col-1; break;
	}
	if(nuevo->vida>=500) {
		switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
			case 8: nuevo->llaves=(nuevo->llaves)+1; break;
			case 10: nuevo->llaves=(nuevo->llaves)-1; break;
			case 6: nuevo->vida=0; break;
			case 9: nuevo->vida=(nuevo->vida)-300; break;
			case 2: nuevo->vida=(nuevo->vida)-200; break;
			case 1: nuevo->vida=(nuevo->vida)-100; break;
			case 7: nuevo->vida=(nuevo->vida)+100; break;
		}
	}
	else {
		if(nuevo->vida>=300) {
			switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
				case 8: nuevo->llaves=(nuevo->llaves)+1; break;
				case 10: nuevo->llaves=(nuevo->llaves)-1; break;
				case 6: nuevo->vida=0; break;
				case 9: nuevo->vida=(nuevo->vida)-300; break;
				case 2: nuevo->vida=(nuevo->vida)-200; break;
				case 1: nuevo->vida=(nuevo->vida)-100; break;
				case 7: nuevo->vida=(nuevo->vida)+200; break;
			}
		}
		else {
			switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
				case 8: nuevo->llaves=(nuevo->llaves)+1; break;
				case 10: nuevo->llaves=(nuevo->llaves)-1; break;
				case 6: nuevo->vida=0; break;
				case 9: nuevo->vida=(nuevo->vida)-300; break;
				case 2: nuevo->vida=(nuevo->vida)-200; break;
				case 1: nuevo->vida=(nuevo->vida)-100; break;
				case 7: nuevo->vida=(nuevo->vida)+300; break;
			}
		}
	}
	nuevo->matriz[estado->fila][estado->col]=0;
	nuevo->matriz[nuevo->fila][nuevo->col]=5;
	if((nuevo->vida)>700) {
		nuevo->vida=700;
	}
	return nuevo;
}

tEstado *aplicaOperador2(tEstado *estado, char op, tEstado *nivel) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	switch(op) {
		case 'w': nuevo->fila=nuevo->fila-1; break;
		case 'W': nuevo->fila=nuevo->fila-1; break;
		case 's': nuevo->fila=nuevo->fila+1; break;
		case 'S': nuevo->fila=nuevo->fila+1; break;
		case 'd': nuevo->col=nuevo->col+1; break;
		case 'D': nuevo->col=nuevo->col+1; break;
		case 'a': nuevo->col=nuevo->col-1; break;
		case 'A': nuevo->col=nuevo->col-1; break;
	}
	if(nuevo->vida>=500) {
		switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
			case 8: nuevo->llaves=(nuevo->llaves)+1; break;
			case 10: nuevo->llaves=(nuevo->llaves)-1; break;
			case 6: nuevo->vida=0; break;
			case 9: nuevo->vida=(nuevo->vida)-300; break;
			case 2: nuevo->vida=(nuevo->vida)-200; break;
			case 1: nuevo->vida=(nuevo->vida)-100; break;
			case 7: nuevo->vida=(nuevo->vida)+100; break;
		}
	}
	else {
		if(nuevo->vida>=300) {
			switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
				case 8: nuevo->llaves=(nuevo->llaves)+1; break;
				case 10: nuevo->llaves=(nuevo->llaves)-1; break;
				case 6: nuevo->vida=0; break;
				case 9: nuevo->vida=(nuevo->vida)-300; break;
				case 2: nuevo->vida=(nuevo->vida)-200; break;
				case 1: nuevo->vida=(nuevo->vida)-100; break;
				case 7: nuevo->vida=(nuevo->vida)+200; break;
			}
		}
		else {
			switch(nuevo->matriz[nuevo->fila][nuevo->col]) {
				case 8: nuevo->llaves=(nuevo->llaves)+1; break;
				case 10: nuevo->llaves=(nuevo->llaves)-1; break;
				case 6: nuevo->vida=0; break;
				case 9: nuevo->vida=(nuevo->vida)-300; break;
				case 2: nuevo->vida=(nuevo->vida)-200; break;
				case 1: nuevo->vida=(nuevo->vida)-100; break;
				case 7: nuevo->vida=(nuevo->vida)+300; break;
			}
		}
	}
	if(nivel->matriz[estado->fila][estado->col]==9 || nivel->matriz[estado->fila][estado->col]==2 || nivel->matriz[estado->fila][estado->col]==1 || nivel->matriz[estado->fila][estado->col]==0) {
		nuevo->matriz[estado->fila][estado->col]=nivel->matriz[estado->fila][estado->col];
	}
	else {
		nuevo->matriz[estado->fila][estado->col]=0;
	}
	nuevo->matriz[nuevo->fila][nuevo->col]=5;
	if((nuevo->vida)>700) {
		nuevo->vida=700;
	}
	return nuevo;
}

int main() {
	tEstado *estado_Inicial=(tEstado *)malloc(sizeof(tEstado));
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
	int nivel_1[N][N]={{5,1,1,0,1,4,4},{2,0,2,4,1,4,4},{0,1,0,4,0,4,4},{1,1,2,0,2,4,4},{0,2,1,1,3,4,4},{4,4,4,4,4,4,4},{4,4,4,4,4,4,4}};
	int nivel_2[N][N]={{5,0,0,1,1,0,4},{4,4,0,0,0,0,4},{3,4,2,2,4,0,4},{1,2,2,0,1,0,4},{0,2,2,0,4,0,4},{0,0,1,6,1,0,4},{4,4,4,4,4,4,4}};
	int nivel_3[N][N]={{0,1,2,0,0,1,8},{0,10,10,7,1,0,6},{5,1,0,10,10,10,10},{7,1,0,10,10,10,10},{1,10,9,8,6,10,3},{1,9,0,7,2,2,10},{1,0,2,1,2,0,10}};
	//int nivel_prueba[N][N]={{1,1,1,0,0,1,8},{0,4,4,7,4,4,4},{5,0,0,0,0,0,0},{1,1,1,1,7,7,7},{0,0,0,0,0,0,7},{7,7,7,7,7,2,1},{7,7,7,7,7,7,7}};
	int k;
	char op;
	int nivel=0;
	estado_Inicial=crearEstado(nivel_1);
	estado_Inicial->vida=V;
	estado_Inicial->llaves=0;
	estado_Inicial->col=0;
	estado_Inicial->fila=0;
	estado_Inicial->objfila=4;
	estado_Inicial->objcol=4;
	Aclaracion();
	printf("\n");
	notas();
	printf("\n\n");
	dispVida(estado_Inicial);
	displlaves(estado_Inicial);
	//dispfilcol(estado_Inicial);//
	printf("\n\n");
	dispEstado(estado_Inicial);
	estado=estado_Inicial;
	for(k=0;k!=-1;k++) {
		if(estado->vida<=0) {
			printf("\n\n\n%c%c%c%c%c%c%c%c HAS MUERTO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
			return 0;
		}
		if(testObjetivo(estado)) {
			nivel++;
			if(nivel==3) {
				printf("\n\n\n%c%c%c%c%c%c%c%c HAS GANADO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
				return 0;
			}
			else {
				if(nivel==2) {
					printf("\n\n\n\tNIVEL 3\n\n");
					printf("En este nivel los bloques da%cinos no se eliminan al\npasar por encima de ellos. Ten cuidado\n\n",164);
					estado_Inicial=crearEstado(nivel_3);
					estado_Inicial->vida=700;
					estado_Inicial->llaves=0;
					estado_Inicial->col=0;
					estado_Inicial->fila=2;
					estado_Inicial->objfila=4;
					estado_Inicial->objcol=6;
					estado=estado_Inicial;
					dispVida(estado);
					displlaves(estado);
					//dispfilcol(estado);//
					printf("\n\n");
					dispEstado(estado);
				}
				else {
					printf("\n\n\n\tNIVEL 2\n\n\n");
					estado_Inicial=crearEstado(nivel_2);
					estado_Inicial->vida=V;
					estado_Inicial->llaves=0;
					estado_Inicial->col=0;
					estado_Inicial->fila=0;
					estado_Inicial->objfila=2;
					estado_Inicial->objcol=0;
					estado=estado_Inicial;
					dispVida(estado);
					displlaves(estado);
					//dispfilcol(estado);//
					printf("\n\n");
					dispEstado(estado);
				}
			}
		}
		scanf("%c",&op);
		fflush(stdin);
		printf("\n");
		if(esValido(estado,op) && nivel==2) {
			nuevo=aplicaOperador2(estado,op,estado_Inicial);
			dispVida(nuevo);
			displlaves(nuevo);
			//dispfilcol(nuevo);//
			printf("\n\n");
			dispEstado(nuevo);
			estado=nuevo;
		}
		else {
			if(esValido(estado,op)) {
				nuevo=aplicaOperador(estado,op);
				dispVida(nuevo);
				displlaves(nuevo);
				//dispfilcol(nuevo);//
				printf("\n\n");
				dispEstado(nuevo);
				estado=nuevo;
			}
			else {
				printf("\tNo se puede aplicar el operador\n\n");
			dispVida(estado);
			displlaves(estado);
			//dispfilcol(estado);//
			printf("\n\n");
			dispEstado(estado);
			}
		}
	}
	return 0;
}
