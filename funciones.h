#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void escribirEstadisticas(char *nombre, int pdvJugador, int pdvCPU);
void leerEstadisticas();
void creditos();
void reglas();
//JUGAR
void solicitarNombre(char *nombre);
void partida(char *nombre, int &pdvJugador, int &pdvCPU);
//inicializar partida
int repartirDesafio(int anterior);
void imprimirDesafio(int carta);
void mostrarDesafioJugador(char *nombre, int naipe);
void barajarElementos(int mazo[]);
int robarMazo(int mazo[]);
void repartirElementos(int mazoJugador[], int mazoCPU[], int mazoElementos[]);
void ordenarMazo(int mazo[]);
void imprimirElemento(int carta);
void mostrarElementosJugador(char *nombre, int mazo[]);
//menu de opciones
void menuMostrarDesafio(int carta);
void menuMostrarElementos(int mazo[]);
void robarElemento(int mazoJugador[], int mazoElementos[]);
int menuRobar(char *nombre, int ronda);
void opcionesRobar(char *nombre, int ronda, int desafioJugador, int mazoElementos[], int mazoJugador[]);
int menuJugar(char *nombre, int ronda);
void opcionesJugar(char *nombre, int ronda, int desafioJugador, int mazoElementos[], int mazoJugador[]);
//inicio de ronda
void vectorElemento(int naipe, int vNaipe[]);
int jugarJugador(int mazo[]);
int jugarCPU(int naipeJugador, int mazo[]);
//resultado de ronda
int verificarJugada(int naipeJugador, int naipeCPU);
void sumarNaipesGanador(int resultado, int naipeJugador, int naipeCPU, int mazoJugador[], int mazoCPU[]);
void descripcionJugada(int naipeJugador, int naipeCPU);
void imprimirResultadoRonda(char *nombre, int resultado, int naipeJugador, int naipeCPU);
//verificar combinacion y desafio
bool combElementos(int mazo[]);
bool combDistintas(int mazo[]);
bool verificarCombinacion(int mazo[]);
bool verificarDesafio(bool id, int rondaAnt, int resultado, int naipeA, int naipeB, int desafio);
//condicion ganadora
bool verificarCondicion(bool combinacion, bool desafio);
void mostrarGanador(bool ganador, char *nombre, int desafioJugador, int desafioCPU, int mazoElementosJugador[], int mazoElementosCPU[]);
//puntuacion
void puntuarRondaGanada(int resultado, int &pRondaJugador, int &pRondaCPU);
void puntuarRondaElementos(int resultado, int &pElementosJugador, int &pElementosCPU, int naipeA, int naipeB);
void mostrarPuntuacion(bool ganador, char *nombre, bool combAdversario, bool objAdversario, int rondaGanada, int rondaElementos, int pdvTotalGanador);
int puntuarGanador(bool combAdversario, bool objAdversario, int rondasGanadas, int rondasElementos);

#endif 