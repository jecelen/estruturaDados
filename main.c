#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"
#include <assert.h>


int main(){
    int op;
    int opcid;

    do{
        printf("1. Encontrar o vizinho mais próximo de um município.\n");
        printf("2. Encontrar os cinco vizinhos mais próximos de um restaurante de fast food.\n");
        printf("3. Encerrar.\n");

        scanf("%d", &op);

        if(op == 1){
            do{
               municipiosControler();
               printf("Deseja buscar o vizinho de um novo município?/n");
               printf("1. Sim./n2. Não. Retornar ao menu principal./n");
               scanf("%d", &opcid);
            }while(opcid != 2);
        }
        else if(op == 2){
            do{
               fastFoodControler();
               printf("Deseja buscar os vizinhos de outro restaurante?/n");
               printf("1. Sim./n2. Não. Retornar ao menu principal./n");
               scanf("%d", &opcid);
            }while(opcid != 2);
        }

    }while(op!=3);

    return 0;
}
