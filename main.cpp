#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv){

    int tamano, procesador;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamano); //obtenemos el tamaño del procesador
	MPI_Comm_rank(MPI_COMM_WORLD, &procesador);

    int numero=1;
    string frase;
    int suma=0;
    ifstream ficheroEntrada;
    ficheroEntrada.open("utem.csv");
    while(!ficheroEntrada.eof()){
        if(procesador==0){
            int receptor = 1;
            getline(ficheroEntrada, frase);
            MPI_Send(&numero, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }else if(procesador == 1){
                int proc= 0;
                MPI_Recv(&numero, 1, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                suma=suma+1;
                printf("procesador 1 recv numero %d desde el procesador numero 0",numero);
            }
        if(procesador==2){
            int receptor = 3;
            getline(ficheroEntrada, frase);
            MPI_Send(&numero, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }else if(procesador == 3){
                int proc= 2;
                MPI_Recv(&numero, 1, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                suma=suma+1;
                printf("procesador 3 recv numero %d desde el procesador numero 2",numero);
            }
        }
    ficheroEntrada.close();
    suma= suma-1;
    cout << "La cantidad de lineas del fichero es: "<< suma << endl;
    MPI_Finalize();
    return 0;
}
