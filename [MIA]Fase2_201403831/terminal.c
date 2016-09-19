#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "Analizadores/Structs.h"
#include "Analizadores/Discos.h"
#include "Analizadores/Comandos.h"
#include "Analizadores/Archivos.h"
#include "Analizadores/Grupos.h"
#include "Analizadores/Reportes.h"
#include "Analizadores/lexico.h"

void RevisarComando(char comando[]);
void Inicializar();

int main()
{
    char comando[256]="";
    while(1)
    {
        printf("FILE SYSTEM EXT2/EXT3 >> ");
        scanf("%[^\n]",&comando);
        fflush(stdin);
        RevisarComando(comando);
        strcpy(comando,"");
        getchar();
    }
    getchar();
    return 0;
}

void RevisarComando(char comando[])
{
    int i;
    int exito = -1;

    for(i = 0; i < strlen(comando); i++)
    {
        if(ModoEntero == 1)
        {
            if(isdigit(comando[i]))
            {
                temporal[contador] = comando[i];
                contador++;
            }
            else
            {
                exito = Analizar();

            }
        }
        else if(ModoString == 0)
        {
            if(comando[i] != ' ')
            {
                if(comando[i] == 'B' && comando[i+1] == 'F')
                {
                    temporal[contador] = comando[i];
                    contador++; i++;
                    temporal[contador] = comando[i];
                }
                else if(comando[i]=='M' || comando[i]=='K' || comando[i] == 'B' || comando[i] == 'P' ||
                comando[i] == 'E' || comando[i] == 'L' || comando[i] == 'F' ||  comando[i] == 'W')
                {
                    temporal[contador] = comando[i];
                }
                else
                {
                    temporal[contador] = tolower(comando[i]);

                }
                contador++;
                exito = Analizar();

            }
            else
            {
                if(exito == 0)
                {
                    printf("Error léxico, comando no reconocido: %s\n\n", temporal);
                    Inicializar();
                    estado = 0; memset(mkdisk_param,0,4);
                    return;
                }
            }
        }
        else
        {
                temporal[contador] = comando[i];
                contador++;
                exito = Analizar();
        }
    }
    if(exito == 0)
    {
        printf("Error léxico, comando no reconocido: %s\n\n", temporal);
        Inicializar();
        estado = 0;
        return;
    }
    exito = Analizar();
    if(estado != 0)
    {
        Automata(-1,"",-1);
    }

    estado = 0;
    Inicializar();
    memset(mkdisk_param,0,4);
    memset(mount_param,0,2);
    SelectorComandos();
    InicializarValores();
    InicializarComandos();

}


