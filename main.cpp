#include <iostream>
#include <ctime>
#include <fstream>
#include "funciones.h"
#include "funciones.cpp"
#include "rlutil.h"

using namespace std;

int main()
{
    int opcion;
    char nombreJugador[10];
    int pdvJugador = 0, pdvCPU = 0;

    //MENU PRINCIPAL
    do {
        rlutil::cls();
        
        std::cout << "CARD-JITSU++" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "1 - JUGAR" << std::endl;
        std::cout << "2 - ESTADÍSTICAS" << std::endl;
        std::cout << "3 - CRÉDITOS" << std::endl;
        std::cout << "4 - REGLAS DEL JUEGO" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "0 - SALIR" << std::endl;
        std::cout << std::endl << "OPCIÓN: ";
        do {
            std::cin >> opcion; 
        } while (opcion < 0 && opcion > 4);

        switch (opcion)
        {
            case 1: 
                rlutil::cls();
                solicitarNombre(nombreJugador);
                partida(nombreJugador, pdvJugador, pdvCPU);
                escribirEstadisticas(nombreJugador, pdvJugador, pdvCPU);
            break;
            case 2:
                leerEstadisticas();
                rlutil::anykey();
            break;
            case 3:
                creditos();
                rlutil::anykey();
            break;
            case 4:
                reglas();
                rlutil::anykey();
            break;
        }

    } while (opcion != 0);
    
    return 0;
}