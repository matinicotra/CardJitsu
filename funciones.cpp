#include <iostream>
#include <ctime>
#include <fstream>
#include "funciones.h"
#include "rlutil.h"

using namespace std;

void escribirEstadisticas(char *nombre, int pdvJugador, int pdvCPU)
{
    ofstream archivo;

    archivo.open("puntuaciones.txt", ios::app);
    
    if (archivo.fail()) {
        std::cout << "No se puede abrir el archivo...";
        exit(1);
    }

    archivo << nombre << ": " << pdvJugador << "PDV    CPU: " << pdvCPU << "PDV    ||    " << std::endl;

    archivo.close();
}

void leerEstadisticas()
{
    rlutil::cls();

    ifstream archivo;
    string texto;

    archivo.open("puntuaciones.txt", ios::in);
    if (archivo.fail()) {
        std::cout << "No se puede abrir el archivo...";
        exit(1);
    }

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl << std::endl;
    std::cout << "ESTADÍSTICAS: " << std::endl;
    
    while (!archivo.eof()) {
        getline(archivo, texto);
        std::cout << texto;
    }

    archivo.close();

    std::cout << std::endl << std::endl << "Presione cualquier tecla para volver al menú principal...";
    rlutil::anykey();
}

void creditos()
{
    rlutil::cls();

    rlutil::setColor(5);

    std::cout << std::endl << "JUEGO REALIZADO POR MATÍAS NICOTRA" << std::endl << "ENERO 2023";

    rlutil::resetColor();

    std::cout << std::endl << std::endl << "Presione cualquier tecla para volver al menú principal...";
    rlutil::anykey();
}

void reglas()
{
    rlutil::cls();
    rlutil::setColor(6);

    cout << "El objetivo del juego es lograr una combinación de cartas de elementos y cumplir con la carta objetivo obtenida al comienzo de la partida. \n";
    cout << "El primer jugador en cumplir ambos hitos gana el juego.\n";
    cout << endl;
    cout << "Dispone de dos tipos de mazos distintos que intervienen en distintas etapas del juego: \n";
    cout << endl;
    cout << "MAZO DE CARTAS DESAFÍO.\n";
    cout << "Las CARTAS DESAFÍO simplemente contienen un texto con el desafío a cumplir. En total existen diez cartas en el mazo de desafíos.\n"; 
    cout << "Antes de comenzar una partida, cada jugador debe robar una carta del mazo de desafío y plantearse como objetivo cumplirlo cuanto antes.\n";
    cout << endl;
    cout << "MAZO DE CARTAS DE ELEMENTOS.\n";
    cout << "Las cartas de elementos son las que hacen posible el transcurso de la partida. \n";
    cout << "En primer lugar, son las que pueden marcar un desafío como cumplido y por otro lado, cumplir el segundo hito que finalice la partida.\n";
    cout << "Estas cartas se caracterizan por tener un elemento (fuego, nieve o agua), un color (rojo, amarillo, verde y azul) y un número (de 1 a 5).\n";
    cout << endl;

    rlutil::setColor(11);

    cout << "JUEGO\n";
    cout << "Cada jugador comienza la partida con tres cartas de elementos repartidas al azar. \n";
    cout << "A continuación cada jugador juega una carta de elementos de su preferencia y se determina quien gana esa ronda. \n";
    cout << endl;
    cout << "Para determinar esto se siguen las siguientes reglas:\n";
    cout << "- EL FUEGO VENCE A LA NIEVE\n";
    cout << "- LA NIEVE VENCE AL AGUA\n";
    cout << "- EL AGUA VENCE AL FUEGO\n";
    cout << endl;
    cout << "En cada ronda, deberá jugar una carta para competir con la juegue su adversario. \n";
    cout << "Esto quiere decir que puede recuperar la carta jugada y ganar la del adversario o bien perderla.\n";
    cout << endl;
    cout << "Las anteriores reglas se cumplen indistintamente del color y número que tenga el naipe.\n";
    cout << "Si las cartas jugadas en la ronda son del mismo elemento, se resuelve el ganador de la ronda con el valor numérico más alto.\n";
    cout << endl;
    cout << "Obtener una combinación de elementos ganadora\n";
    cout << endl;
    cout << "Para obtener una combinación de elementos ganadora, un jugador debe lograr alguna de las siguientes situaciones:\n";
    cout << "- Tener tres cartas de distinto elemento y distinto color.\n";
    cout << "- Tener tres cartas del mismo elemento.\n";
    cout << endl;
    cout << "Obtener una combinación de elementos ganadora, sin embargo, no es sinónimo de haber ganado la partida. \n";
    cout << "Para ganar la partida es necesario también cumplir el objetivo de la carta desafío. \n";
    cout << endl;
    cout << "El primer jugador en obtener una combinación de elementos ganadora y cumplir el objetivo de su carta desafío gana la partida.\n";
    cout << endl;

    rlutil::setColor(12);

    cout << "Una vez finalizada la partida, se determinan los puntos de victoria de la misma. Los mismos se calculan de la siguiente manera:\n";
    cout << "+3 PDV por haber ganado la partida\n";
    cout << "-1 PDV si el contrario obtuvo una combinación de elementos ganadora\n";
    cout << "-1 PDV si el contrario cumplió el objetivo de su carta desafío\n";
    cout << "+1 PDV por cada ronda ganada en el juego al adversario\n";
    cout << "+5 PDV por cada ronda ganada en el juego con un elemento igual al del adversario\n";

    rlutil::resetColor();

    std::cout << std::endl << std::endl << "Presione cualquier tecla para volver al menú principal...";
    rlutil::anykey();
}

void solicitarNombre(char *nombre)
{
    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "INGRESE NOMBRE DEL JUGADOR: ";
    std::cin >> nombre;
}

void partida(char *nombre, int &pdvJugador, int &pdvCPU)
{
    //ETAPA DESAFIOS
    int desafioJugador = repartirDesafio(0);
    int desafioCPU = repartirDesafio(desafioJugador);
    mostrarDesafioJugador(nombre, desafioJugador);
    rlutil::anykey();

    //ETAPA ELEMENTOS
    int mazoElementos[60] = {};
    int mazoJugador[60] = {};
    int mazoCPU[60] = {};
    barajarElementos(mazoElementos);
    repartirElementos(mazoJugador, mazoCPU, mazoElementos);
    mostrarElementosJugador(nombre, mazoJugador);

    //ETAPA DE RONDAS
    int nRonda = 0;                 //contador de ronda
    int resultadoRonda;             //1 gana jugador, 0 gana cpu, -1 empate
    int naipeJugador, naipeCPU;     //variable de codigo de naipe a jugar (1 - 60)

    //variables de condiciones para victoria
    bool hayGanador = false;
    bool ganador; // 0 - cpu, 1 - jugador
    bool bandCombinacion_Jugador, bandCombinacion_CPU;
    bool bandDesafio_Jugador, bandDesafio_CPU;
    int resultadoAnterior = 0;  //para desafio 10

    //variables de puntajes
    int pdvRonda_Jugador = 0, pdvRonda_CPU = 0;
    int pdvElementos_Jugador = 0, pdvElementos_CPU = 0;
    bool pdvCombinacion_Jugador = false, pdvCombinacion_CPU = false;
    bool pdvDesafio_Jugador = false, pdvDesafio_CPU = false;

    do {
        nRonda++;

        //menu de opciones
        opcionesRobar(nombre, nRonda, desafioJugador, mazoElementos, mazoJugador);
        robarElemento(mazoJugador, mazoElementos);
        robarElemento(mazoCPU, mazoElementos);
        opcionesJugar(nombre, nRonda, desafioJugador, mazoElementos, mazoJugador);
        naipeJugador = jugarJugador(mazoJugador);
        naipeCPU = jugarCPU(naipeJugador, mazoCPU);

        //verificar ganador ronda, repartir e imprimir resultado
        resultadoRonda = verificarJugada(naipeJugador, naipeCPU);
        sumarNaipesGanador(resultadoRonda, naipeJugador, naipeCPU, mazoJugador, mazoCPU);
        imprimirResultadoRonda(nombre, resultadoRonda, naipeJugador, naipeCPU);
        rlutil::anykey();

        //puntuaciones parciales
        puntuarRondaGanada(resultadoRonda, pdvRonda_Jugador, pdvRonda_CPU);
        puntuarRondaElementos(resultadoRonda, pdvElementos_Jugador, pdvElementos_CPU, naipeJugador, naipeCPU);
        
        //verificar condiciones para victoria
        bandCombinacion_Jugador = verificarCombinacion(mazoJugador);
        bandCombinacion_CPU = verificarCombinacion(mazoCPU);
        
        bandDesafio_Jugador = verificarDesafio(1, resultadoAnterior, resultadoRonda, naipeJugador, naipeCPU, desafioJugador);
        bandDesafio_CPU = verificarDesafio(0, resultadoAnterior, resultadoRonda, naipeJugador, naipeCPU, desafioCPU);

        if (resultadoRonda == 1 && bandCombinacion_Jugador && bandDesafio_Jugador) {
            ganador = 1;
            hayGanador = true;
        }
        if (resultadoRonda == 0 && bandCombinacion_CPU && bandDesafio_CPU) {
            ganador = 0;
            hayGanador = true;
        }

        resultadoAnterior = resultadoRonda;

    } while(!hayGanador);
    
    if (ganador) 
    {
        mostrarGanador(1, nombre, desafioJugador, desafioCPU, mazoJugador, mazoCPU);
        pdvJugador = puntuarGanador(bandCombinacion_CPU, bandDesafio_CPU, pdvRonda_Jugador, pdvElementos_Jugador);
        mostrarPuntuacion(1, nombre, bandCombinacion_CPU, bandDesafio_CPU, pdvRonda_Jugador, pdvElementos_Jugador, pdvJugador);
    }
    else if (!ganador) {
        mostrarGanador(0, nombre, desafioJugador, desafioCPU, mazoJugador, mazoCPU);
        pdvCPU = puntuarGanador(bandCombinacion_Jugador, bandDesafio_Jugador, pdvRonda_CPU, pdvElementos_CPU);
        mostrarPuntuacion(0, nombre, bandCombinacion_Jugador, bandDesafio_Jugador, pdvRonda_CPU, pdvElementos_CPU, pdvCPU);
    }
}

int repartirDesafio(int anterior)
{
    srand(time(NULL));
    int desafio;

    do {
        desafio = rand()%10;
    } while (desafio == anterior);

    return desafio;
}

void imprimirDesafio(int carta)
{
    std::string desafio[10] = {"GANAR UNA CARTA DE NIEVE", 
                                "GANAR UNA CARTA DE FUEGO",
                                "GANAR UNA CARTA DE AGUA", 
                                "GANAR DOS CARTAS ROJAS",
                                "GANAR DOS CARTAS AMARILLAS", 
                                "GANAR DOS CARTAS VERDES",
                                "GANAR DOS CARTAS AZULES", 
                                "GANAR UNA CARTA CON EL MISMO ELEMENTO QUE EL ADVERSARIO",
                                "GANAR DOS CARTAS CON EL MISMO NÚMERO", 
                                "GANAR DOS RONDAS DE MANERA CONSECUTIVA"};
    rlutil::setColor(1);
    std::cout << desafio[carta - 1];
    rlutil::resetColor();
}

void mostrarDesafioJugador(char *nombre, int naipe)
{
    rlutil::cls();
        
    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "ETAPA DESAFÍOS" << std::endl << std::endl;
    std::cout << nombre << " has obtenido una carta con el siguiente desafío:  ";

    imprimirDesafio(naipe);

    std::cout << std::endl << std::endl;
    std::cout << "PRESIONA CUALQUIER TECLA PARA REGRESAR...";
    rlutil::anykey();
}

void barajarElementos(int mazo[])
{
    srand(time(NULL));
    int naipe, posicion;
    
    for (naipe = 1; naipe <= 60; naipe++)
    {
        do {
            posicion = rand()%60;
        } while (mazo[posicion] != 0);
        mazo[posicion] = naipe;
    }
}

void ordenarMazo(int mazo[])
{
    int i, x, aux;

    for (i = 0; i < 60; i++) 
    {
        for (x = 0; x < 59; x++)
        {
            if (mazo[x] < mazo[x+1]) {
                aux = mazo[x];
                mazo[x] = mazo[x+1];
                mazo[x+1] = aux;
            }
        }
    }
}

int robarMazo(int mazo[])
{
    int i = 60;

    do {
        i--;
    } while (mazo[i] == 0);
    int naipe = mazo[i];

    mazo[i] = 0;

    return naipe;
}

void repartirElementos(int mazoJugador[], int mazoCPU[], int mazoElementos[])
{
    for (int i = 0; i < 3; i++) {
        mazoJugador[i] = robarMazo(mazoElementos);
        mazoCPU[i] = robarMazo(mazoElementos);
    }
    ordenarMazo(mazoJugador);
}

void imprimirElemento(int carta)
{
    int vNaipe[3];
    int numero;
    char elemento[3][6] = {"FUEGO", "NIEVE", "AGUA"};
    char color[4][9] = {"ROJO", "AMARILLO", "VERDE", "AZUL"};

    vectorElemento(carta, vNaipe);

    if (vNaipe[1] == 1) {
        rlutil::setColor(4);
        std::cout << elemento[vNaipe[0] - 1];
        std::cout << " #" << vNaipe[2] << " " << color[vNaipe[1] - 1];
        rlutil::resetColor();
    }

    if (vNaipe[1] == 2) {
        rlutil::setColor(14);
        std::cout << elemento[vNaipe[0] - 1];
        std::cout << " #" << vNaipe[2] << " " << color[vNaipe[1] - 1];
        rlutil::resetColor();
    }

    if (vNaipe[1] == 3) {
        rlutil::setColor(2);
        std::cout << elemento[vNaipe[0] - 1];
        std::cout << " #" << vNaipe[2] << " " << color[vNaipe[1] - 1];
        rlutil::resetColor();
    }

    if (vNaipe[1] == 4) {
        rlutil::setColor(3);
        std::cout << elemento[vNaipe[0] - 1];
        std::cout << " #" << vNaipe[2] << " " << color[vNaipe[1] - 1];
        rlutil::resetColor();
    }
}

void mostrarElementosJugador(char *nombre, int mazo[])
{
    rlutil::cls();
        
    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "ETAPA DE ELEMENTOS" << std::endl << std::endl;
    std::cout << nombre << " has obtenido las siguientes cartas de elementos:  ";

    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            std::cout << std::endl;
            imprimirElemento(mazo[i]);
        }
    }

    std::cout << std::endl << std::endl;
    std::cout << "PRESIONA CUALQUIER TECLA PARA REGRESAR...";
    rlutil::anykey();
}

void menuMostrarDesafio(int carta)
{
    rlutil::cls();

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "DESAFÍO: ";
    imprimirDesafio(carta);

    std::cout << endl << endl << "PRESIONA CUALQUIER TECLA PARA REGRESAR...";
    rlutil::anykey();
}

void menuMostrarElementos(int mazo[])
{
    rlutil::cls();
    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "CARTAS DE ELEMENTOS: " << std::endl;
    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            std::cout << std::endl;
            imprimirElemento(mazo[i]);
        }
    }
    std::cout << std::endl << std::endl;
    std::cout << "PRESIONA CUALQUIER TECLA PARA REGRESAR...";
    rlutil::anykey();
}

void robarElemento(int mazoJugador[], int mazoElementos[])
{
    int naipe, i = 0;

    do {
        i++;
    } while (mazoJugador[i] != 0);
    mazoJugador[i] = robarMazo(mazoElementos);

    ordenarMazo(mazoJugador);
}

int menuRobar(char *nombre, int ronda)
{
    rlutil::cls();

    int opcion;

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << nombre << " VS CPU" << "                                        RONDA #" << ronda << std::endl;
    std::cout << std::endl;
    std::cout << "1 - VER CARTA DESAFÍO" << std::endl;
    std::cout << "2 - VER CARTAS DE ELEMENTOS" << std::endl;
    std::cout << "3 - ROBAR CARTA ELEMENTO DE LA PILA" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "OPCIÓN: ";

    do {
        std::cin >> opcion; 
    } while (opcion < 1 && opcion > 3);

    return opcion;
}

void opcionesRobar(char *nombre, int ronda, int desafioJugador, int mazoElementos[], int mazoJugador[])
{
    int opcion;
    do {
        opcion = menuRobar(nombre, ronda);
        switch (opcion)
        {
        case 1:
            menuMostrarDesafio(desafioJugador);
            rlutil::anykey();
        break;
        case 2:
            menuMostrarElementos(mazoJugador);
            rlutil::anykey();
        break;
        }
    } while (opcion != 3);
}

int menuJugar(char *nombre, int ronda)
{
    rlutil::cls();

    int opcion;

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << nombre << " VS CPU" << "                                        RONDA #" << ronda << std::endl;
    std::cout << std::endl;
    std::cout << "1 - VER CARTA DESAFÍO" << std::endl;
    std::cout << "2 - VER CARTAS DE ELEMENTOS" << std::endl;
    std::cout << "3 - JUGAR UNA CARTA" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "OPCIÓN: ";

    do {
        std::cin >> opcion; 
    } while (opcion < 1 && opcion > 3);

    return opcion;
}

void opcionesJugar(char *nombre, int ronda, int desafioJugador, int mazoElementos[], int mazoJugador[])
{
    int opcion;
    do {
        opcion = menuJugar(nombre, ronda);
        switch (opcion)
        {
        case 1:
            menuMostrarDesafio(desafioJugador);
            rlutil::anykey();
        break;
        case 2:
            menuMostrarElementos(mazoJugador);
            rlutil::anykey();
        break;
        }
    } while (opcion != 3);
}

void vectorElemento(int naipe, int vNaipe[])
{
    int elemento, color, numero;

    //fuego
    if (naipe >= 1 && naipe <= 20) 
    {
        elemento = 1;

        if (naipe <= 5) {
            color = 1;
            numero = naipe;
        }
        else if (naipe >= 6 && naipe <= 10) {
            color = 2;
            numero = naipe - 5;
        }
        else if (naipe >= 11 && naipe <= 15) {
            color = 3;
            numero = naipe - 10;
        }
        else if (naipe >= 16 && naipe <= 20) {
            color = 4;
            numero = naipe - 15;
        }
    }

    //nieve
    if (naipe >= 21 && naipe <= 40) 
    {
        elemento = 2;
        naipe -= 20;
        if (naipe <= 5) {
            color = 1;
            numero = naipe;
        }
        else if (naipe >= 6 && naipe <= 10) {
            color = 2;
            numero = naipe - 5;
        }
        else if (naipe >= 11 && naipe <= 15) {
            color = 3;
            numero = naipe - 10;
        }
        else if (naipe >= 16 && naipe <= 20) {
            color = 4;
            numero = naipe - 15;
        }
    }

    //agua
    if (naipe >= 41 && naipe <= 60) 
    {
        elemento = 3;
        naipe -= 40;
        if (naipe <= 5) {
            color = 1;
            numero = naipe;
        }
        else if (naipe >= 6 && naipe <= 10) {
            color = 2;
            numero = naipe - 5;
        }
        else if (naipe >= 11 && naipe <= 15) {
            color = 3;
            numero = naipe - 10;
        }
        else if (naipe >= 16 && naipe <= 20) {
            color = 4;
            numero = naipe - 15;
        }
    }

    vNaipe[0] = elemento;
    vNaipe[1] = color;
    vNaipe[2] = numero;
}

int jugarJugador(int mazo[])
{
    rlutil::cls();

    int naipe, opcion;

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "CARTAS DE ELEMENTOS: " << std::endl;

    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            std::cout << std::endl << i + 1 << ": ";
            imprimirElemento(mazo[i]);
        }
    }

    std::cout << std::endl << std::endl;
    std::cout << "JUGAR CARTA: ";
    std::cin >> opcion;

    naipe = mazo[opcion-1];
    mazo[opcion-1] = 0;

    return naipe;
}

int jugarCPU(int naipeJugador, int mazo[])
{
    //1 fuego
    //2 nieve
    //3 agua

    srand(time(NULL));

    bool naipeOk = false;
    int i, c = 0;
    int naipeCPU;
    int vNaipeJugador[3], vNaipeCPU[3];

    for (i = 0; i < 60; i++) {
        if (mazo[i] != 0) c++;
    }

    vectorElemento(naipeJugador, vNaipeJugador);

    //defensa contra fuego
    if (vNaipeJugador[0] == 1) {
        i = 0;
        do {
            vectorElemento(mazo[i], vNaipeCPU);
            if (vNaipeCPU[0] == 3) {
                naipeCPU = mazo[i];
                naipeOk = true;
            }
            i++;
        } while (i < c && !naipeOk);

        //si no tiene agua busca fuego
        if (!naipeOk) {
            i = 0;
            do {
                vectorElemento(mazo[i], vNaipeCPU);
                if (vNaipeCPU[0] == 1) {
                    naipeCPU = mazo[i];
                    naipeOk = true;
                }
                i++;
            } while (i < c && !naipeOk); 
        }
        else naipeCPU = mazo[rand()%3];
    }

    //defensa contra nieve
    if (vNaipeJugador[0] == 2) {
        i = 0;
        do {
            vectorElemento(mazo[i], vNaipeCPU);
            if (vNaipeCPU[0] == 1) {
                naipeCPU = mazo[i];
                naipeOk = true;
            }
            i++;
        } while (i < c && !naipeOk);

        //si no tiene fuego busca nieve
        if (!naipeOk) {
            i = 0;
            do {
                vectorElemento(mazo[i], vNaipeCPU);
                if (vNaipeCPU[0] == 2) {
                    naipeCPU = mazo[i];
                    naipeOk = true;
                }
                i++;
            } while (i < c && !naipeOk); 
        }
        else naipeCPU = mazo[rand()%3];
    }

    //defensa contra agua
    if (vNaipeJugador[0] == 3) {
        i = 0;
        do {
            vectorElemento(mazo[i], vNaipeCPU);
            if (vNaipeCPU[0] == 2) {
                naipeCPU = mazo[i];
                naipeOk = true;
            }
            i++;
        } while (i < c && !naipeOk);

        //si no tiene nieve busca agua
        if (!naipeOk) {
            i = 0;
            do {
                vectorElemento(mazo[i], vNaipeCPU);
                if (vNaipeCPU[0] == 3) {
                    naipeCPU = mazo[i];
                    naipeOk = true;
                }
                i++;
            } while (i < c && !naipeOk); 
        }
        else naipeCPU = mazo[rand()%3];
    }

    //borra el naipe jugado del mazo
    for (i = 0; i < 60; i++) {
        if (mazo[i] == naipeCPU) {
            mazo[i] = 0;
        }
    }
    i = 0;
    while (mazo[i] != 0) {
        i++;
    }
    for (int x = i; x < 59; x++) {
        mazo[x] = mazo[x + 1];
    }

    return naipeCPU;
}

int verificarJugada(int naipeJugador, int naipeCPU)
{
    int jugador[3], cpu[3];

    vectorElemento(naipeJugador, jugador);
    vectorElemento(naipeCPU, cpu);

    if (jugador[0] == 1 && cpu[0] == 2) {
        return 1;
    }
    if (jugador[0] == 1 && cpu[0] == 3) {
        return 0;  
    }
    if (jugador[0] == 1 && cpu[0] == 1) {
        if (jugador[2] > cpu[2]) {
            return 1;
        }
        else if (jugador[2] < cpu[2]) {
            return 0;
        }
    }

    if (jugador[0] == 2 && cpu[0] == 3) {
        return 1;
    }
    if (jugador[0] == 2 && cpu[0] == 1) {
        return 0;
    }
    if (jugador[0] == 2 && cpu[0] == 2) {
        if (jugador[2] > cpu[2]) {
            return 1;
        }
        else if (jugador[2] < cpu[2]) {
            return 0;
        }
    }

    if (jugador[0] == 3 && cpu[0] == 1) {
        return 1;
    }
    if (jugador[0] == 3 && cpu[0] == 2) {
        return 0;
    }
    if (jugador[0] == 3 && cpu[0] == 3) {
        if (jugador[2] > cpu[2]) {
            return 1;
        }
        else if (jugador[2] < cpu[2]) {
            return 0;
        }
    }
    return -1;
}

void sumarNaipesGanador(int resultado, int naipeJugador, int naipeCPU, int mazoJugador[], int mazoCPU[])
{
    int i = 0;

    if (resultado == 1) {
        while (mazoJugador[i] != 0) {
            i++;
        }
        mazoJugador[i] = naipeJugador;
        mazoJugador[i + 1] = naipeCPU;
        ordenarMazo(mazoJugador);
    }
    if (!resultado) {
        while (mazoCPU[i] != 0) {
            i++;
        }
        mazoCPU[i] = naipeCPU;
        mazoCPU[i + 1] = naipeJugador;
    }
    if (resultado == -1) {
        while (mazoJugador[i] != 0) {
            i++;
        }
        mazoJugador[i] = naipeJugador;
        ordenarMazo(mazoJugador);

        i = 0;

        while (mazoCPU[i] != 0) {
            i++;
        }
        mazoCPU[i] = naipeCPU;
    }

}

void descripcionJugada(int naipeA, int naipeB)
{
    int jugador[3], cpu[3];

    vectorElemento(naipeA, jugador);
    vectorElemento(naipeB, cpu);
    
    if (jugador[0] == 1 && cpu[0] == 2 || jugador[0] == 2 && cpu[0] == 1) {
        std::cout << "FUEGO VENCE A NIEVE";
    }
    if (jugador[0] == 1 && cpu[0] == 3 || jugador[0] == 3 && cpu[0] == 1) {
        std::cout << "AGUA VENCE A FUEGO";
    }
    if (jugador[0] == 2 && cpu[0] == 3 || jugador[0] == 3 && cpu[0] == 2) {
        std::cout << "NIEVE VENCE A AGUA";
    }
    if (jugador[0] == cpu[0]) {
        if (jugador[2] != cpu[2]) {
            std::cout << "TIENE LA CARTA MAS ALTA";
        }
    }
}

void imprimirResultadoRonda(char *nombre, int resultado, int naipeJugador, int naipeCPU)
{
    rlutil::cls();

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "RESULTADO DE LA RONDA:" << std::endl << std::endl; 
    std::cout << nombre << " JUEGA ";
    imprimirElemento(naipeJugador);

    std::cout << std::endl << "CPU JUEGA ";
    rlutil::msleep(1000);
    imprimirElemento(naipeCPU);

    std::cout << std::endl;
    std::cout << std::endl;

    rlutil::msleep(500);

    if (resultado == 1) {
        rlutil::setColor(1);
        std::cout << "GANA " << nombre << "!   ";
        rlutil::resetColor();
        descripcionJugada(naipeJugador, naipeCPU);
    }
    else if (!resultado) {
        rlutil::setColor(1);
        std::cout << "GANA CPU!   ";
        rlutil::resetColor();
        descripcionJugada(naipeJugador, naipeCPU);
    }
    else if (resultado == -1) {
        rlutil::setColor(1);
        std::cout << "EMPATE";
        rlutil::resetColor();
    }
    
    std::cout << std::endl << std::endl;
    std::cout << "PRESIONA CUALQUIER TECLA PARA CONTINUAR...";
    rlutil::anykey();
}

bool combElementos(int mazo[])
{
    //3 cartas del mismo elemento devuelve true
    int vNaipe[3];

    int cont = 0;
    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            vectorElemento(mazo[i], vNaipe);
            if (vNaipe[0] == 1) cont++;
        }
    }
    if (cont >= 3) {
        return true;
    }

    cont = 0;
    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            vectorElemento(mazo[i], vNaipe);
            if (vNaipe[0] == 2) cont++;
        }
    }
    if (cont >= 3) {
        return true;
    }

    cont = 0;
    for (int i = 0; i < 60; i++) {
        if (mazo[i] != 0) {
            vectorElemento(mazo[i], vNaipe);
            if (vNaipe[0] == 3) cont++;
        }
    }
    if (cont >= 3) {
        return true;
    }

    return false;
}

bool combDistintas(int mazo[])
{
    int naipeA[3], naipeB[3], naipeC[3];
    int a, b, c;
    bool bandB;

    a = 0;
    while (a < 60 && mazo[a] != 0) 
    {
        vectorElemento(mazo[a], naipeA);
        b = 0;
        while (b < 60 && mazo[b] != 0) 
        {
            vectorElemento(mazo[b], naipeB);
            if (naipeB[0] != naipeA[0] && naipeB[1] != naipeA[1]) 
            {
                c = 0;
                while (c < 60 && mazo[c] != 0)
                {
                    vectorElemento(mazo[c], naipeC);
                    if (naipeC[0] != naipeB[0] && naipeC[0] != naipeA[0] && naipeC[1] != naipeB[1] && naipeC[1] != naipeA[1]) {
                        return true;
                    }
                    c++;
                }
            }
            b++;
        }
        a++;
    }
    return false;
}

bool verificarCombinacion(int mazo[])
{
    bool tresElementos = combElementos(mazo);
    bool tresDistintos = combDistintas(mazo);

    if (tresElementos || tresDistintos) {
        return true;
    }
    return false;
}

bool verificarDesafio(bool id, int rondaAnt, int resultado, int naipeA, int naipeB, int desafio)
{
    int vNaipeA[3], vNaipeB[3];

    if (resultado == id) 
    {
        vectorElemento(naipeA, vNaipeA);
        vectorElemento(naipeB, vNaipeB);

        switch(desafio)
        {
            case 1: 
                if (vNaipeA[0] == 2 || vNaipeB[0] == 2) return true;                        //ganar una carta de nieve
            break;
            case 2:
                if (vNaipeA[0] == 1 || vNaipeB[0] == 1) return true;                        //ganar una carta de fuego
            break;
            case 3:
                if (vNaipeA[0] == 3 || vNaipeB[0] == 3) return true;                        //ganar una carta de agua
            break;
            case 4:
                if (vNaipeA[1] == 1 && vNaipeB[1] == 1) return true;                        //ganar dos cartas rojas
            break;
            case 5:
                if (vNaipeA[1] == 2 && vNaipeB[1] == 2) return true;                        //ganar dos cartas amarillas
            break;
            case 6:
                if (vNaipeA[1] == 3 && vNaipeB[1] == 3) return true;                        //ganar dos cartas verdes
            break;
            case 7:
                if (vNaipeA[1] == 4 && vNaipeB[1] == 4) return true;                        //ganar dos cartas azules
            break;
            case 8:
                if (vNaipeA[0] == vNaipeB[0]) return true;                                  //ganar dos cartas del mismo elemento
            break;
            case 9:
                if (vNaipeA[2] == vNaipeB[2]) return true;                                  //ganar dos cartas del mismo numero
            break;
            case 10:
                if (rondaAnt == resultado) return true;                                     //ganar dos rondas seguidas
            break;
        }
    }
    return false;
}

void mostrarGanador(bool ganador, char *nombre, int desafioJugador, int desafioCPU, int mazoElementosJugador[], int mazoElementosCPU[])
{
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    
    if (ganador) 
    {
        std::cout << "¡¡¡" << nombre << " GANA LA PARTIDA!!!" << std::endl;
        std::cout << std::endl << "DESAFÍO CUMPLIDO: ";
        imprimirDesafio(desafioJugador);

        std::cout << std::endl << "COMBINACIÓN DE ELEMENTOS: ";
        if (combElementos(mazoElementosJugador) && combDistintas(mazoElementosJugador)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas del mismo elemento y tres cartas de distinto elemento y color." << std::endl;
            rlutil::resetColor();
        }
        else if (combElementos(mazoElementosJugador)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas del mismo elemento." << std::endl;
            rlutil::resetColor();
        }
        else if (combDistintas(mazoElementosJugador)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas de distinto elemento y distitno color" << std::endl;
            rlutil::resetColor();
        }

        std::cout << std::endl << "CARTAS DE ELEMENTOS: ";
        for (int i = 0; i < 60; i++) {
            if (mazoElementosJugador[i] != 0) {
                std::cout << std::endl;
                imprimirElemento(mazoElementosJugador[i]);
            }
        }
    }
    else {
        std::cout << "¡¡¡CPU GANA LA PARTIDA!!!" << std::endl;
        std::cout << std::endl << "DESAFÍO CUMPLIDO: ";
        imprimirDesafio(desafioCPU);

        std::cout << std::endl << "COMBINACIÓN DE ELEMENTOS: ";
        if (combElementos(mazoElementosCPU) && combDistintas(mazoElementosCPU)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas del mismo elemento y tres cartas de distinto elemento y color." << std::endl;
            rlutil::resetColor();
        }
        else if (combElementos(mazoElementosCPU)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas del mismo elemento." << std::endl;
            rlutil::resetColor();
        }
        else if (combDistintas(mazoElementosCPU)) {
            rlutil::setColor(1);
            std::cout << "Tres cartas de distinto elemento y distitno color" << std::endl;
            rlutil::resetColor();
        }

        std::cout << std::endl << "CARTAS DE ELEMENTOS: " << std::endl;
        for (int i = 0; i < 60; i++) {
            if (mazoElementosCPU[i] != 0) {
                std::cout << std::endl;
                imprimirElemento(mazoElementosCPU[i]);
            }
        }
    }

    std::cout << std::endl << std::endl << "PRESIONE CUALQUIER TECLA PARA CONTINUAR...";
    rlutil::anykey();
}

void puntuarRondaGanada(int resultado, int &pRondaJugador, int &pRondaCPU)
{
    if (resultado == 1) {
        pRondaJugador++;
    }
    else if (resultado == 0) {
        pRondaCPU++;
    }
}

void puntuarRondaElementos(int resultado, int &pElementosJugador, int &pElementosCPU, int naipeA, int naipeB)
{
    int vNaipeA[3], vNaipeB[3];
    
    vectorElemento(naipeA, vNaipeA);
    vectorElemento(naipeB, vNaipeB);

    if (vNaipeA[0] == vNaipeB[0] && resultado != -1) 
    {
        if (resultado == 1) {
            pElementosJugador += 5;
        }
        else if (resultado == 0) {
            pElementosCPU += 5;
        }
    }
}

void mostrarPuntuacion(bool ganador, char *nombre, bool combAdversario, bool objAdversario, int rondasGanadas, int rondasElementos, int pdvTotalGanador)
{
    rlutil::cls();

    std::cout << "CARD-JITSU++" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl << std::endl;
    if (ganador) {
        std::cout << "HITO                                                            " << nombre << std::endl;
    }
    if (!ganador) {
        std::cout << "HITO                                                            CPU" << std::endl;
    }
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ganar la partida                                                " << 3 << " PDV" << std::endl;
    std::cout << "Combinación de elementos cumplida por el oponente               " << - combAdversario << " PDV" << std::endl;
    std::cout << "Carta desafío cumplida por el oponente                          " << - objAdversario << " PDV" << std::endl;
    std::cout << "Rondas ganadas al adversario                                    " << rondasGanadas << " PDV" << std::endl;
    std::cout << "Rondas ganadas al adversario con igual elemento                 " << rondasElementos << " PDV" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "TOTAL                                                           " << pdvTotalGanador << " PDV";

    std::cout << std::endl << std::endl;
    std::cout << "PRESIONA CUALQUIER TECLA PARA CONTINUAR...";
    rlutil::anykey();

}

int puntuarGanador(bool combAdversario, bool objAdversario, int rondasGanadas, int rondasElementos)
{
    int totalGanador = 0;

    totalGanador += 3;
    totalGanador += rondasGanadas;
    totalGanador += rondasElementos;
    if (combAdversario) totalGanador -= 1;
    if (objAdversario) totalGanador -= 1;

    return totalGanador;
}
