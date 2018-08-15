#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){

  int tamano, procesador;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamano); //obtenemos el tamaño del procesador
	MPI_Comm_rank(MPI_COMM_WORLD, &procesador);

    int numero=1;
    string frase;
    int suma=-2;
    ifstream ficheroEntrada;
    ficheroEntrada.open("utem.csv");
    if(!ficheroEntrada.eof()){
    while(!ficheroEntrada.eof()){
        if(procesador==0){
            int receptor = 1;
            getline(ficheroEntrada, frase);
            MPI_Send(&numero, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }else if(procesador == 1){
                int proc= 0;
                MPI_Recv(&numero, 1, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                suma=suma+numero;
                printf("procesador 1 recv 1 linea %d desde el procesador numero 0\n",numero);
                cout << "La cantidad de lineas que van sumadas en el procesador"<<procesador<< "del fichero es: "<< suma << endl;
            }
        /*if(procesador==2){
            int receptor = 3;
            getline(ficheroEntrada, frase);
            MPI_Send(&numero, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }else if(procesador == 3){
                int proc= 2;
                MPI_Recv(&numero, 1, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                suma=suma+numero;
                printf("procesador 3 recv numero %d desde el procesador numero 2\n",numero);
                cout << "La cantidad de lineas que van sumadas en el procesador"<<procesador<< "del fichero es: "<< suma << endl;
            }
            cout << "La cantidad total de lineas son: "<< suma << endl;*/
          }
        }else{
          suma=0;
          cout << "La cantidad de lineas del fichero es: "<< suma << endl;
        }
    ficheroEntrada.close();
    MPI_Finalize();
    cout << "La cantidad total de lineas son: "<< suma << endl;
    return 0;
}
