//Juego Version Beta 0.4 PRE3
#include<stdio.h>
#include<stdlib.h>
#define N 9
#define V 600

typedef struct{
	int matriz[N][N];
	int vida,llaves,mana,vidaregen,veneno;
	int fila,col;
	int objfila,objcol;
}tEstado;

void Aclaracion() {
	printf("\nBienvenido a mi juego en C versi%cn 0.4 PRE3\n\n\n",162);
	printf("El objetivo de este juego es llegar al bloque %c del tablero\nque se mostrar%c a continuaci%cn.\n\n",25,160,162);
	printf("Pero antes de nada debes saber que la ficha que controlar%cs\nser%c la siguiente: %c\n\n",160,160,41);
	printf("Los bloques %c te quitar%cn 3 puntos de vida, los bloques %c 2 puntos\nde vida y estos bloques %c 1 punto de vida\n\n",219,160,178,177);
	printf("Este bloque te curar%c vida en funci%cn de la que tengas: %c\n\n",160,162,2);
	printf("Las llaves %c te permitir%cn abrir los bloques invisibles\nque est%cn en medio del mapa\n\n",204,160,130);
	printf("Para navegar usa las teclas w,a,s,d\n\n");
	printf("Para usar los Powerups usa la tecla: G %c Escoba  F %c Regeneraci%cn\n\n",62,62,162);
	printf("Presiona cualquier tecla para comenzar el juego");
	printf("\n\n");
	system("pause");
}

void notas() {
	printf("Notas del Parche 0.4 PRE3:\n\n");
	printf("   %c Optimizadas unas cuantas l%cneas de c%cdigo\n",175,161,162);
	printf("   %c Sonido musical al obtener un PowerUp\n",175);
	printf("   %c Cambiados algunos iconos\n",175);
	printf("   %c Nueva mec%cnica de generaci%cn de niveles",175,160,162);
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
				case 5: printf("%c",41); break;
				case 3: printf("%c",25); break;
				case 4: printf("%c",0); break;
				case 6: printf("%c",1); break;
				case 7: printf("%c",2); break;
				case 8: printf("%c",204); break;
				case 9: printf("%c",219); break;
				case 10: printf("%c",0); break;
				case 11: printf("%c",0); break;
				case 12: printf("%c",254); break;
				case 13: printf("%c",220); break;
				case 14: printf("%c",31); break;
				case 15: printf("%c",30); break;
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

void dispAtributo(tEstado *estado) {
	if(estado->vidaregen>0) {
		printf("   REGENERACI%cN",224);
	}
	if(estado->veneno>0) {
		printf("   VENENO");
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

int esValido3(tEstado *estado, char op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	int valido=0;
	int valido1=0;
	switch(op) {
		case 'w': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila-2][estado->col]; break;
		case 'W': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila-2][estado->col]; break;
		case 's': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila+2][estado->col]; break;
		case 'S': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila+2][estado->col]; break;
		case 'd': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col+2]; break;
		case 'D': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col+2]; break;
		case 'a': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col-2]; break;
		case 'A': nuevo->matriz[nuevo->fila][nuevo->col]=estado->matriz[estado->fila][estado->col-2]; break;
		default: valido=0;
	}
	if((nuevo->matriz[nuevo->fila][nuevo->col])==10) {
		switch(op) {
			case 'w': valido1=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-2][nuevo->col]!=4; break;
			case 'W': valido1=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-2][nuevo->col]!=4; break;
			case 's': valido1=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+2][nuevo->col]!=4; break;
			case 'S': valido1=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+2][nuevo->col]!=4; break;
			case 'd': valido1=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+2]!=4; break;
			case 'D': valido1=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+2]!=4; break;
			case 'a': valido1=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-2]!=4; break;
			case 'A': valido1=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-2]!=4; break;
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
			case 'w': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-2][nuevo->col]!=4; break;
			case 'W': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-2][nuevo->col]!=4; break;
			case 's': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+2][nuevo->col]!=4; break;
			case 'S': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+2][nuevo->col]!=4; break;
			case 'd': valido=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+2]!=4; break;
			case 'D': valido=nuevo->col<(N-1) && nuevo->matriz[nuevo->fila][nuevo->col+2]!=4; break;
			case 'a': valido=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-2]!=4; break;
			case 'A': valido=nuevo->col>0 && nuevo->matriz[nuevo->fila][nuevo->col-2]!=4; break;
			default: valido=0;
		}
	}
	return valido;
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
	if((nuevo->matriz[nuevo->fila][nuevo->col])==10 || ((nuevo->matriz[nuevo->fila][nuevo->col])==12 && nuevo->llaves==0) || ((nuevo->matriz[nuevo->fila][nuevo->col])==13 && nuevo->llaves==0)) {
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
		if(nuevo->matriz[nuevo->fila][nuevo->col]==14) {
			switch(op) {
				case 's': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
				case 'S': valido=nuevo->fila<(N-1) && nuevo->matriz[nuevo->fila+1][nuevo->col]!=4; break;
				default: valido=0;
			}
		}
		else {
			if(nuevo->matriz[nuevo->fila][nuevo->col]==15) {
				switch(op) {
					case 'w': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
					case 'W': valido=(nuevo->fila)>0 && nuevo->matriz[nuevo->fila-1][nuevo->col]!=4; break;
					default: valido=0;
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
		}
	}
	return valido;
}

tEstado *aplicaOperador(tEstado *estado, char op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	if((nuevo->vidaregen)>0) {
		nuevo->vida=nuevo->vida+100;
	}
	nuevo->vidaregen=nuevo->vidaregen-1;
	if((nuevo->vidaregen)<0) {
		nuevo->vidaregen=0;
	}
	if((nuevo->veneno)>0) {
		if(nuevo->vida>100) {
			nuevo->vida=nuevo->vida-100;
		}
	}
	nuevo->veneno=nuevo->veneno-1;
	if((nuevo->veneno)<0) {
		nuevo->veneno=0;
	}
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
			case 12: if((nuevo->llaves)>=2) {
					nuevo->llaves=nuevo->llaves-2;
					}
					else {
						if((nuevo->llaves)==1) {
							nuevo->llaves=nuevo->llaves-1;
							nuevo->matriz[nuevo->fila][nuevo->col]=13;
							nuevo->col=estado->col; nuevo->fila=estado->fila;
						}
					}
					break;
			case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
				case 12: if((nuevo->llaves)>=2) {
						nuevo->llaves=nuevo->llaves-2;
						}
						else {
							if((nuevo->llaves)==1) {
								nuevo->llaves=nuevo->llaves-1;
								nuevo->matriz[nuevo->fila][nuevo->col]=13;
								nuevo->col=estado->col; nuevo->fila=estado->fila;
							}
						}
						break;
				case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
				case 12: if((nuevo->llaves)>=2) {
						nuevo->llaves=nuevo->llaves-2;
						}
						else {
							if((nuevo->llaves)==1) {
								nuevo->llaves=nuevo->llaves-1;
								nuevo->matriz[nuevo->fila][nuevo->col]=13;
								nuevo->col=estado->col; nuevo->fila=estado->fila;
							}
						}
						break;
				case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
	if((nuevo->llaves)>3) {
		nuevo->llaves=3;
	}
	return nuevo;
}

tEstado *aplicaOperador2(tEstado *estado, char op, tEstado *nivel) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	if((nuevo->vidaregen)>0) {
		nuevo->vida=nuevo->vida+100;
	}
	nuevo->vidaregen=nuevo->vidaregen-1;
	if((nuevo->vidaregen)<0) {
		nuevo->vidaregen=0;
	}
	if((nuevo->veneno)>0) {
		if(nuevo->vida>100) {
			nuevo->vida=nuevo->vida-100;
		}
	}
	nuevo->veneno=nuevo->veneno-1;
	if((nuevo->veneno)<0) {
		nuevo->veneno=0;
	}
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
			case 12: if((nuevo->llaves)>=2) {
					nuevo->llaves=nuevo->llaves-2;
					}
					else {
						if((nuevo->llaves)==1) {
							nuevo->llaves=nuevo->llaves-1;
							nuevo->matriz[nuevo->fila][nuevo->col]=13;
							nuevo->col=estado->col; nuevo->fila=estado->fila;
						}
					}
					break;
			case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
				case 12: if((nuevo->llaves)>=2) {
						nuevo->llaves=nuevo->llaves-2;
						}
						else {
							if((nuevo->llaves)==1) {
								nuevo->llaves=nuevo->llaves-1;
								nuevo->matriz[nuevo->fila][nuevo->col]=13;
								nuevo->col=estado->col; nuevo->fila=estado->fila;
							}
						}
						break;
				case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
				case 12: if((nuevo->llaves)>=2) {
						nuevo->llaves=nuevo->llaves-2;
						}
						else {
							if((nuevo->llaves)==1) {
								nuevo->llaves=nuevo->llaves-1;
								nuevo->matriz[nuevo->fila][nuevo->col]=13;
								nuevo->col=estado->col; nuevo->fila=estado->fila;
							}
						}
						break;
				case 13: nuevo->llaves=(nuevo->llaves)-1; break;
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
	if(nivel->matriz[estado->fila][estado->col]==9 || nivel->matriz[estado->fila][estado->col]==2 || nivel->matriz[estado->fila][estado->col]==1 || nivel->matriz[estado->fila][estado->col]==0 || nivel->matriz[estado->fila][estado->col]==14 || nivel->matriz[estado->fila][estado->col]==15) {
		nuevo->matriz[estado->fila][estado->col]=nivel->matriz[estado->fila][estado->col];
	}
	else {
		nuevo->matriz[estado->fila][estado->col]=0;
	}
	nuevo->matriz[nuevo->fila][nuevo->col]=5;
	if((nuevo->vida)>700) {
		nuevo->vida=700;
	}
	if((nuevo->llaves)>3) {
		nuevo->llaves=3;
	}
	return nuevo;
}

tEstado *aplicaOperador3(tEstado *estado, char op, tEstado *nivel) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	if((nuevo->vidaregen)>0) {
		nuevo->vida=nuevo->vida+100;
	}
	nuevo->vidaregen=nuevo->vidaregen-1;
	if((nuevo->vidaregen)<0) {
		nuevo->vidaregen=0;
	}
	if((nuevo->veneno)>0) {
		if(nuevo->vida>100) {
			nuevo->vida=nuevo->vida-100;
		}
	}
	nuevo->veneno=nuevo->veneno-1;
	if((nuevo->veneno)<0) {
		nuevo->veneno=0;
	}
	switch(op) {
		case 'w': nuevo->fila=nuevo->fila-2; break;
		case 'W': nuevo->fila=nuevo->fila-2; break;
		case 's': nuevo->fila=nuevo->fila+2; break;
		case 'S': nuevo->fila=nuevo->fila+2; break;
		case 'd': nuevo->col=nuevo->col+2; break;
		case 'D': nuevo->col=nuevo->col+2; break;
		case 'a': nuevo->col=nuevo->col-2; break;
		case 'A': nuevo->col=nuevo->col-2; break;
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

tEstado *cambiaBloque(tEstado *estado, int bloque1, int bloque2) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	tEstado *aux=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	int i,j,ibase,itope,jbase,jtope,extrai,extraj;
	switch(bloque1) {
		case 1: ibase=0; itope=3; jbase=0; jtope=3; break;
		case 2: ibase=0; itope=3; jbase=3; jtope=6; break;
		case 3: ibase=0; itope=3; jbase=6; jtope=9; break;
		case 4: ibase=3; itope=6; jbase=0; jtope=3; break;
		case 5: ibase=3; itope=6; jbase=3; jtope=6; break;
		case 6: ibase=3; itope=6; jbase=6; jtope=9; break;
		case 7: ibase=6; itope=9; jbase=0; jtope=3; break;
		case 8: ibase=6; itope=9; jbase=3; jtope=6; break;
	}
	switch(bloque2) {
		case 2: extrai=0; extraj=3; break;
		case 3: if(bloque1==1) {
					extrai=0; extraj=6;
				}
				else {
					extrai=0; extraj=3;
				} break;
		case 5: if(bloque1==2) {
					extrai=3; extraj=0;
				}
				else {
					extrai=0; extraj=3;
				} break;
		case 6: if(bloque1==3) {
					extrai=3; extraj=0;
				}
				else {
					if(bloque1==4) {
						extrai=0; extraj=6;
					}
					else {
						extrai=0; extraj=3;
					}
				} break;
		case 8: if(bloque1==5) {
					extrai=3; extraj=0;
				}
				else {
					extrai=0; extraj=3;
				} break;
		case 9: if(bloque1==6) {
					extrai=3; extraj=0;
				}
				else {
					if(bloque1==7) {
						extrai=0; extraj=6;
					}
					else {
						extrai=0; extraj=3;
					}
				} break;
	}
	for(i=ibase;i<itope;i++) {
		for(j=jbase;j<jtope;j++) {
			aux->matriz[i][j]=estado->matriz[i][j];
			nuevo->matriz[i][j]=estado->matriz[i+extrai][j+extraj];
			nuevo->matriz[i+extrai][j+extraj]=aux->matriz[i][j];
		}
	}
	return nuevo;
}

tEstado *aplicaPowerup(tEstado *estado, char op) {
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	*nuevo=*estado;
	int i,j;
	nuevo->mana=(nuevo->mana)-1;
	if(op=='g'||op=='G') {
		nuevo->veneno=2;
		for(j=nuevo->col+1;j<N;j++) {
			if(nuevo->matriz[nuevo->fila][j]!=4 && nuevo->matriz[nuevo->fila][j]!=3 && nuevo->matriz[nuevo->fila][j]!=8 && nuevo->matriz[nuevo->fila][j]!=10 && nuevo->matriz[nuevo->fila][j]!=12 && nuevo->matriz[nuevo->fila][j]!=13) {
				nuevo->matriz[nuevo->fila][j]=0;
			}
		}
		for(i=nuevo->fila+1;i<N;i++) {
			if(nuevo->matriz[i][nuevo->col]!=4 && nuevo->matriz[i][nuevo->col]!=3 && nuevo->matriz[i][nuevo->col]!=8 && nuevo->matriz[i][nuevo->col]!=10 && nuevo->matriz[i][nuevo->col]!=12 && nuevo->matriz[i][nuevo->col]!=13) {
				nuevo->matriz[i][nuevo->col]=0;
			}
		}
	}
	if(op=='f'||op=='F') {
		nuevo->vidaregen=3;
		if(nuevo->matriz[nuevo->fila][nuevo->col-1]==1) {
			nuevo->matriz[nuevo->fila][nuevo->col-1]=0;
		}
		else {
			if(nuevo->matriz[nuevo->fila][nuevo->col-1]==2) {
				nuevo->matriz[nuevo->fila][nuevo->col-1]=1;
			}
			else {
				if(nuevo->matriz[nuevo->fila][nuevo->col-1]==9) {
					nuevo->matriz[nuevo->fila][nuevo->col-1]=2;
				}
			}
		}
		if(nuevo->matriz[nuevo->fila][nuevo->col+1]==1) {
			nuevo->matriz[nuevo->fila][nuevo->col+1]=0;
		}
		else {
			if(nuevo->matriz[nuevo->fila][nuevo->col+1]==2) {
				nuevo->matriz[nuevo->fila][nuevo->col+1]=1;
			}
			else {
				if(nuevo->matriz[nuevo->fila][nuevo->col+1]==9) {
					nuevo->matriz[nuevo->fila][nuevo->col+1]=2;
				}
			}
		}
		if(nuevo->matriz[nuevo->fila-1][nuevo->col]==1) {
			nuevo->matriz[nuevo->fila-1][nuevo->col]=0;
		}
		else {
			if(nuevo->matriz[nuevo->fila-1][nuevo->col]==2) {
				nuevo->matriz[nuevo->fila-1][nuevo->col]=1;
			}
			else {
				if(nuevo->matriz[nuevo->fila-1][nuevo->col]==9) {
					nuevo->matriz[nuevo->fila-1][nuevo->col]=2;
				}
			}
		}
		if(nuevo->matriz[nuevo->fila+1][nuevo->col]==1) {
			nuevo->matriz[nuevo->fila+1][nuevo->col]=0;
		}
		else {
			if(nuevo->matriz[nuevo->fila+1][nuevo->col]==2) {
				nuevo->matriz[nuevo->fila+1][nuevo->col]=1;
			}
			else {
				if(nuevo->matriz[nuevo->fila+1][nuevo->col]==9) {
					nuevo->matriz[nuevo->fila+1][nuevo->col]=2;
				}
			}
		}
	}
	return nuevo;
}

int main() {
	tEstado *estado_Inicial=(tEstado *)malloc(sizeof(tEstado));
	tEstado *nuevo=(tEstado *)malloc(sizeof(tEstado));
	tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
	int nivel_1[N][N]={{5,1,1,0,1,4,4,4,4},{2,0,2,4,1,4,4,4,4},{0,1,0,4,0,4,4,4,4},{1,1,2,0,2,4,4,4,4},{0,2,1,1,3,4,4,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_2[N][N]={{5,0,0,1,1,0,4,4,4},{4,4,0,0,0,0,4,4,4},{3,4,2,2,4,0,4,4,4},{1,2,2,0,1,0,4,4,4},{0,2,2,0,4,0,4,4,4},{0,0,1,6,1,0,4,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_3[N][N]={{0,1,2,0,0,1,8,4,4},{0,10,10,7,1,0,6,4,4},{5,1,0,10,10,10,11,4,4},{7,2,0,10,10,10,10,4,4},{1,10,9,8,1,6,3,4,4},{1,9,0,7,9,2,10,4,4},{1,0,2,1,2,0,10,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_extra[N][N]={{7,10,0,2,2,0,8,4,4},{10,1,1,2,1,9,0,4,4},{10,10,2,2,9,0,1,4,4},{10,1,0,1,1,1,2,4,4},{0,0,0,2,1,0,6,4,4},{9,9,0,1,10,0,0,4,4},{5,2,2,2,10,10,3,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_5[N][N]={{0,1,2,0,0,1,8,4,4},{0,10,10,7,1,0,6,4,4},{5,1,0,10,10,10,10,4,4},{7,2,0,10,10,10,10,4,4},{1,10,9,8,1,6,3,4,4},{1,9,0,7,9,2,10,4,4},{1,0,2,1,2,0,10,4,4},{4,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_6[N][N]={{0,0,0,0,0,12,0,0,4},{0,0,0,14,14,15,0,0,4},{0,0,12,0,0,15,14,0,4},{0,0,0,0,0,0,0,0,4},{0,0,0,0,0,0,0,0,4},{0,0,0,0,0,0,0,0,4},{0,0,0,0,0,0,0,0,4},{0,0,0,0,0,0,0,0,4},{4,4,4,4,4,4,4,4,4}};
	int nivel_prueba[N][N]={{0,12,0,1,1,1,2,2,2},{12,12,12,1,1,1,2,2,2},{0,12,0,1,1,1,2,2,2},{0,3,0,7,7,7,8,8,8},{3,3,3,7,7,7,8,8,8},{0,3,0,7,7,7,8,8,8},{5,5,5,9,9,9,0,0,0},{5,5,5,9,9,9,0,0,0},{5,5,5,9,9,9,0,0,0}};
	int k;
	char op;
	int nivel=1;
	estado_Inicial=crearEstado(nivel_1);
	estado_Inicial->vida=V;
	estado_Inicial->llaves=0;
	estado_Inicial->col=0;
	estado_Inicial->fila=0;
	estado_Inicial->objfila=4;
	estado_Inicial->objcol=4;
	estado_Inicial->mana=0;
	estado_Inicial->vidaregen=0;
	estado_Inicial->veneno=0;
	Aclaracion();
	printf("\n");
	notas();
	printf("\n\n");
	dispVida(estado_Inicial);
	displlaves(estado_Inicial);
	dispAtributo(estado_Inicial);
	//dispfilcol(estado_Inicial);//
	printf("\n\n");
	dispEstado(estado_Inicial);
	estado=estado_Inicial;
	for(k=0;k!=-1;k++) {
		if(estado->vida<=0) {
			printf("\n\n\n%c%c%c%c%c%c%c%c HAS MUERTO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
			return 0;
		}
		if(testObjetivo(estado) && nivel==3) {
			nivel=nivel+2;
		}
		if(estado->matriz[2][6]==5 && nivel==3) {
			nivel++;
			printf("\n\n\n%c%c%c%c%c%c%c NIVEL EXTRA %c%c%c%c%c%c%c%c\n\n\n",175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
			estado_Inicial=crearEstado(nivel_extra);
			estado_Inicial->vida=700;
			estado_Inicial->llaves=0;
			estado_Inicial->col=0;
			estado_Inicial->fila=6;
			estado_Inicial->objfila=6;
			estado_Inicial->objcol=6;
			estado=estado_Inicial;
			dispVida(estado);
			displlaves(estado);
			dispAtributo(estado);
			//dispfilcol(estado);//
			printf("\n\n");
			dispEstado(estado);
		}
		else {
			if(testObjetivo(estado)) {
				nivel++;
				if(nivel==2) {
					printf("\n\n\n%c%c%c%c%c%c%c NIVEL 2 %c%c%c%c%c%c%c%c\n\n\n",175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
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
					dispAtributo(estado);
					//dispfilcol(estado);//
					printf("\n\n");
					dispEstado(estado);
				}
				else {
					if(nivel==3) {
						printf("\n\n\n%c%c%c%c%c%c%c NIVEL 3 %c%c%c%c%c%c%c%c\n\n",175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
						printf("En este nivel los bloques da%cinos no se eliminan al\npasar por encima de ellos. Puede que un bloque bajo\nuna cara mort%cfera d%c buena suerte. Ten cuidado\n\n\n",164,161,130);
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
						dispAtributo(estado);
						//dispfilcol(estado);//
						printf("\n\n");
						dispEstado(estado);
					}
					else {
						if(nivel==5) {
							printf("\n\n\n%c%c%c%c%c%c%c NIVEL 3 %c%c%c%c%c%c%c%c\n\n",175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
							printf("Vuelta al pasado...\tPowerUp%c%c\n\n\n",7,24);
							estado_Inicial=crearEstado(nivel_5);
							estado_Inicial->vida=700;
							estado_Inicial->llaves=0;
							estado_Inicial->col=0;
							estado_Inicial->fila=2;
							estado_Inicial->objfila=4;
							estado_Inicial->objcol=6;
							estado_Inicial->mana=estado_Inicial->mana+1;
							estado=estado_Inicial;
							dispVida(estado);
							displlaves(estado);
							dispAtributo(estado);
							//dispfilcol(estado);//
							printf("\n\n");
							dispEstado(estado);
						}
						else {
							if(nivel==6) {
								printf("\n\n\n%c%c%c%c%c%c%c NIVEL 4 %c%c%c%c%c%c%c%c\n\n",175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
								estado_Inicial=crearEstado(nivel_6);
								estado_Inicial->vida=700;
								estado_Inicial->llaves=4;
								estado_Inicial->col=0;
								estado_Inicial->fila=0;
								estado_Inicial->objfila=7;
								estado_Inicial->objcol=7;
								estado=estado_Inicial;
								dispVida(estado);
								displlaves(estado);
								dispAtributo(estado);
								//dispfilcol(estado);//
								printf("\n\n");
								dispEstado(estado);
							}
							else {
								if(nivel==7) {
									printf("\n\n\n%c%c%c%c%c%c%c%c HAS GANADO %c%c%c%c%c%c%c%c\n",175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174);
									return 0;
								}
							}
						}
					}
				}
			}
		}
		scanf("%c",&op);
		fflush(stdin);
		printf("\n");
		if(op=='g'||op=='G'||op=='f'||op=='F') {
			if(estado->mana>0) {
				nuevo=aplicaPowerup(estado,op);
				dispVida(nuevo);
				displlaves(nuevo);
				dispAtributo(nuevo);
				printf("\n\n");
				dispEstado(nuevo);
				estado=nuevo;
			}
			else {
				printf("\tPowerups insuficientes\n\n");
				dispVida(estado);
				displlaves(estado);
				dispAtributo(estado);
				//dispfilcol(estado);//
				printf("\n\n");
				dispEstado(estado);
			}	
		}
		else {
			if(esValido(estado,op) && (nivel==3 || nivel==5 || nivel==6)) {
				nuevo=aplicaOperador2(estado,op,estado_Inicial);
				dispVida(nuevo);
				displlaves(nuevo);
				dispAtributo(nuevo);
				//dispfilcol(nuevo);//
				printf("\n\n");
				dispEstado(nuevo);
				estado=nuevo;
			}
			else {
				if(esValido3(estado,op) && nivel==4) {
					nuevo=aplicaOperador3(estado,op,estado_Inicial);
					dispVida(nuevo);
					displlaves(nuevo);
					dispAtributo(nuevo);
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
						dispAtributo(nuevo);
						//dispfilcol(nuevo);//
						printf("\n\n");
						dispEstado(nuevo);
						estado=nuevo;
					}
					else {
						printf("\tNo se puede aplicar el operador\n\n");
						dispVida(estado);
						displlaves(estado);
						dispAtributo(estado);
						//dispfilcol(estado);//
						printf("\n\n");
						dispEstado(estado);
					}
				}
			}
		}	
	}
	return 0;
}
