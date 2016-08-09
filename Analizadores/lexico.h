char mkdisk[10] = "mkdisk"; int mkdisk_e = 1; char mkdisk_param[4] = "";
char rmdisk[10] = "rmdisk"; int rmdisk_e = 2;
char fdisk[10] = "fdisk"; int fdisk_e = 3;
char mount[10] = "mount"; int mount_e = 4; char mount_param[2] = "";
char umount[10] = "umount"; int umount_e = 5;

char sizec[10] = "-size";   int sizec_e = 6;
char unit[10] = "+unit"; int unit_e = 7;
char path[10] = "-path"; int path_e = 8;
char namec[10] = "-name"; int namec_e = 9;

char type[10] = "+type"; int type_e = 10;
char fit[10] = "+fit"; int fit_e = 11;
char delet[10] = "+delete"; int delet_e = 12;
char add[10] = "+add"; int add_e = 13;
char idn[10] = "-id"; int idn_e = 14;
char puntos[10] = "::"; int puntos_e = 15;
char kbytes[10] = "K"; int kbytes_e = 16;
char mega[10] = "M"; int mega_e = 17;
int cadena = 18; int entero = 19;
char vda[10] = "vd"; int vda_e = 20;
char bytes[10] = "B"; int bytes_e = 21;

char rep[10] = "rep"; int rep_e = 22;
char rmbr[10] = "mbr"; int mbr_e = 23;
char disk[10] = "disk"; int disk_e = 24;
char exec[10] = "exec"; int exec_e = 25;

char primaria[10] = "P"; int primaria_e = 26;
char extendida[10] = "E"; int extendida_e = 27;
char logica[10] = "L"; int logica_e = 28;

char BestFit[10] = "BF"; int BestFit_e = 29;
char FirstFit[10] = "FF"; int FirstFit_e = 30;
char WorstFit[10] = "WF"; int WorstFit_e = 31;
char Fast[10] = "Fast"; int Fast_e = 32;
char Full[10] = "Full"; int Full_e = 33;

//Variables globales
int contador = 0; //contador de caracteres
char temporal[100]=""; //Guarda Token
int ModoString = 0; //Entra en modo cadena
int ModoEntero = 0; //Entra en modo entero;
int estado = 0; //Se posiciona en el estado correspondiente en el automata finito.

void Inicializar()
{
    contador = 0;
    memset(temporal,0,100);
    ModoString = 0;
    ModoEntero = 0;

}


int Analizar()
{
    if(ModoEntero == 1)
    {
        if(!isdigit(temporal[contador]))
        {
            Automata(atoi(temporal),temporal,entero);
            Inicializar();
        }
        return 1;
    }
    else if(ModoString == 1)
    {
        if(temporal[contador-1] == '\"')
        {
            Automata(0,temporal,cadena);

            Inicializar();
        }

        return 1;
    }

    else
    {
        if(strcmp(temporal,mkdisk)==0)
        {
            Automata(0,temporal,mkdisk_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,sizec)==0)
        {
            Automata(0,temporal,sizec_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,unit)==0)
        {
            Automata(0,temporal,unit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,path)==0)
        {
            Automata(0,temporal,path_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,namec)==0)
        {
            Automata(0,temporal,namec_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,rmdisk)==0)
        {
            Automata(0,temporal,rmdisk_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,fdisk)==0)
        {
            Automata(0,temporal,fdisk_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,type)==0)
        {
            Automata(0,temporal,type_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,fit)==0)
        {
            Automata(0,temporal,fit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,delet)==0)
        {
            Automata(0,temporal,delet_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,add)==0)
        {
            Automata(0,temporal,add_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mount)==0)
        {
            Automata(0,temporal,mount_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,umount)==0)
        {
            Automata(0,temporal,umount_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,idn)==0)
        {
            Automata(0,temporal,idn_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,vda)==0)
        {
            Automata(0,temporal,vda_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,exec) == 0)
        {
            Automata(0,temporal,exec_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,puntos)==0)
        {
            Automata(0,temporal,puntos_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,kbytes)==0)
        {
            Automata(0,temporal,kbytes_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mega)==0)
        {
            Automata(0,temporal,mega_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,bytes) == 0)
        {
            Automata(0,temporal,bytes_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,primaria) == 0)
        {
            Automata(0,temporal,primaria_e);
            Inicializar();
            return 1;;
        }
        else if(strcmp(temporal,extendida) == 0)
        {
            Automata(0,temporal,extendida_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,logica) == 0)
        {
            Automata(0,temporal,logica_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,BestFit) == 0)
        {
            Automata(0,temporal,BestFit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,FirstFit) == 0)
        {
            Automata(0,temporal,FirstFit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,WorstFit) == 0)
        {
            Automata(0,temporal,WorstFit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,Fast) == 0)
        {
            Automata(0,temporal,Fast_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,Full) == 0)
        {
            Automata(0,temporal,Full);
            Inicializar();
            return 1;
        }
        else if(temporal[0]=='\"')
        {
            ModoString = 1;
            return 1;
        }
        else if(isdigit(temporal[0]))
        {
            ModoEntero = 1;
            return 1;
        }
        else
        {
            return 0;
        }

    }
}


void Automata(int entero, char token[], int id_token)
{
  //printf("estado: %d, token %d\n",estado,id_token);
    switch(estado)
    {
        case 0:
            switch(id_token)        //Estado inicial, para seleccionar un comando
            {
                case 1: estado = 1; //mkdisk
                break;
                case 2: estado = 2; //rmdisk
                break;
                case 3: estado = 3; //fdisk
                break;
                case 4: estado = 4; //mount
                break;
                case 5: estado = 5; //umount
                break;
                case 25: estado = 24; //exec
                break;
                default:
                printf("Se esperaba el inicio de un comando\n\n");
                return;
            }
        break;
        case 1: //Comandos de mkdisk
            switch(id_token)
            {
                case 6: estado = 6;
                break;
                case 7: estado = 7;
                break;
                case 8: estado = 8;
                break;
                case 9: estado = 9;
                break;
                default:
                if(mkdisk_param[0]=='*' && mkdisk_param[2]=='*' && mkdisk_param[3]=='*')
                {estado = 0; c_mkdisk = 1;}
                else
                {  // printf("%c - %c - %c",mkdisk_param[0],mkdisk_param[2],mkdisk_param[3]);
                    printf("Faltan parámetros del comando mkdisk\n\n");
                }
                return;
            }
        break;
        case 2: //Comandos de rmdisk
            switch(id_token)
            {
                case 8: estado = 14;
                break;
                default:
                printf("Se esperaba la palabra reservada -path\n\n");
                return;
            }
        break;
        case 3: //Comandos de fdisk
            switch(id_token)
            {
                case 6: estado = 27;//size-
                break;
                case 7: estado = 29; //unit-
                break;
                case 8: estado = 31; //path-
                break;
                case 9: estado = 33; //name-
                break;
                case 10: estado = 35; //type-
                break;
                case 11: estado = 37; //fit-
                break;
                case 12: estado = 39; //delete-
                break;
                case 13: estado = 41; //add
                break;
                default:
                    if(crear == 1)
                    {estado = 0; c_fdisk = 1;}
                    else if(eliminar == 1)
                    {estado = 0; c_fdisk = 1;}
                    else if(agregar == 1)
                    {estado = 0; c_fdisk = 1;}
                    else
                    { printf("Faltan parámetros del comando fdisk.\n\n"); }
                return;
            }
        break;
        case 4: //Comandos de mount
            switch(id_token)
            {
                case 8: estado = 16;
                break;
                case 9: estado = 18;
                break;
                default:
                if(mount_param[0] == '*' && mount_param[1] == '*')
                {estado = 0; c_mount = 1;}
                else if(mount_param[0] == '*' || mount_param[1] == '*')
                {
                    printf("Faltan parámetros para el comando mount.\n\n");
                }
                else
                {
                    printf("Mostrando Particiones...\n\n");
                }
                return;
            }
        break;
        case 5: //Comandos de umount
            switch(id_token)
            {
                case 14: estado = 20;
                break;
                default:
                estado = 0;
                return;
            }
        break;
        case 6: //Comandos de mkdisk
            switch(id_token)
            {
                case 15: estado = 10;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 7: //Comandos de mkdisk
            switch(id_token)
            {
                case 15: estado = 11;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 8: //Comandos de mkdisk
            switch(id_token)
            {
                case 15: estado = 12;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 9: //Comandos de mkdisk
            switch(id_token)
            {
                case 15: estado = 13;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 10: //Comandos de mkdisk parametro size
            switch(id_token)
            {
                case 19: estado = 1; mkdisk_param[0]='*'; tamanio = entero;
                break;
                default:
                printf("Se esperaba un entero que defina el tamaño\n\n");
                return;
            }
        break;
        case 11: //Comandos de mkdisk parametro unit
            switch(id_token)
            {
                case 16: estado = 1; mkdisk_param[1]='*'; unidad = token[0];
                break;
                case 17: estado = 1; mkdisk_param[1]='*'; unidad = token[0];
                break;
                default:
                printf("Se esperaba un K o M que defina la unidad de megas o kilobytes\n\n");
                return;
            }
        break;
        case 12: //Comandos de mkdisk parametro path
            switch(id_token)
            {
                case 18: estado = 1; mkdisk_param[2]='*'; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con path válido\n\n");
                return;
            }
        break;
        case 13: //Comandos de mkdisk parametro name
            switch(id_token)
            {
                case 18: estado = 1; mkdisk_param[3]='*'; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con nombre válido extensión .dsk\n\n");
                return;
            }
        break;
        case 14:
            switch(id_token)
            {
                case 15: estado = 15;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 15:
            switch(id_token)
            {
                case 18: estado = 0; strcpy(fichero,token); c_rmdisk = 1;
                break;
                default:
                printf("Se esperaba una cadena con el path del disco a eliminar.\n\n");
                break;
            }
        break;
        case 16:
            switch(id_token)
            {
                case 15: estado = 17;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 17:
            switch(id_token)
            {
                case 18: estado = 4; strcpy(fichero,token); mount_param[0] = '*';
                break;
                default:
                printf("Se esperaba una cadena con el path del disco a montar.\n\n");
                return;
            }
        break;
        case 18:
            switch(id_token)
            {
                case 15: estado = 19;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 19:
            switch(id_token)
            {
                case 18: estado = 4; strcpy(nombre,token); mount_param[1] = '*';
                break;
                default:
                printf("Se esperaba una cadena con el nombre de la partición a montar.\n\n");
                return;
            }
        break;
        case 20:
            switch(id_token)
            {
                case 19: estado = 21;
                break;
                default:
                printf("Se esperaba un número que indique el número dél parámetro.\n\n");
                return;
            }
        break;
        case 21:
            switch(id_token)
            {
                case 15: estado = 22;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 22:
            switch(id_token)
            {
                case 20: estado = 23; strcpy(particion,token);
                break;
                default:
                printf("Se esperaba la palabra vd.\n\n");
                return;
            }
        break;
        case 23:
            switch(id_token)
            {
                case 19: estado = 5; strcat(particion,token);
                break;
                default:
                printf("Se esperaba un número.\n\n");
                return;
            }
        break;
        case 24: //Para ejecutar scripts con exec, path
            switch(id_token)
            {
                case 8: estado = 25;
                break;
                default:
                printf("Se esperaba la palabra -path.\n\n");
                return;
            }
        break;
        case 25: //Comando exec, ::
            switch(id_token)
            {
                case 15: estado = 26;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 26: //Comando exec, cadena que trae el path
            switch(id_token)
            {
                case 18: estado = 0; strcpy(fichero,temporal); c_exec = 1;
                break;
                default:
                printf("Se esperaba una cadena con el path del script.\n\n");
                return;
            }
        break;
        case 27: //:: para size
            switch(id_token)
            {
                case 15: estado = 28;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 28: //numero para size
            switch(id_token)
            {
                case 19: estado = 3; crear = 1;
                break;
                default:
                printf("Se esperaba un numero que indique el tamaño de la partición.\n\n");
                return;
            }
        break;
        case 29: //:: para unit
            switch(id_token)
            {
                case 15: estado = 30;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 30: //unidades para unit
            switch(id_token)
            {
                case 16: estado = 3;
                break;
                case 17: estado = 3;
                break;
                case 21: estado = 3;
                break;
                default:
                printf("Se esparaba K, B o M para el tipo de unidades.\n\n");
                return;
            }
        break;
        case 31: // :: para path
            switch(id_token)
            {
                case 15: estado = 32;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 32: //cadena para path
            switch(id_token)
            {
                case 18: estado = 3;
                break;
                default:
                printf("Se esperaba una cadena que represente el path.\n\n");
                return;
            }
        break;
        case 33: //:: para name
            switch(id_token)
            {
                case 15: estado = 34;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 34: //cadena para name
            switch(id_token)
            {
                case 18: estado = 3;
                break;
                default:
                printf("Se esperaba una cadena que represente el nombre de la partición.\n\n");
                return;
            }
        break;
        case 35: //:: para type
            switch(id_token)
            {
                case 15: estado = 36;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 36: //tipos para type
            switch(id_token)
            {
                case 26: estado = 3;
                break;
                case 27: estado = 3;
                break;
                case 28:  estado = 3;
                break;
                default:
                printf("Se esperaba P, E o L para el tipo de partición.\n\n");
                return;
            }
        break;
        case 37: //:: para fit
            switch(id_token)
            {
                case 15: estado = 38;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 38: // ajustes para fit
            switch(id_token)
            {
                case 29: estado = 3;
                break;
                case 30: estado = 3;
                break;
                case 31: estado = 3;
                break;
                default:
                printf("Se esperaba BF, FF o WF para indicar el tipo de ajuste.\n\n");
                break;
            }
        break;
        case 39: //:: para delete
            switch(id_token)
            {
                case 15: estado = 40;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 40: //tipos para delete
            switch(id_token)
            {
                case 32: estado = 3; eliminar = 1;
                break;
                case 33: estado = 3; eliminar = 1;
                break;
                default:
                printf("Se esperaba Fast o Full para el tipo de eliminado.\n\n");
                break;
            }
        break;
        case 41: //:: para add
            switch(id_token)
            {
                case 15: estado = 42;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break; //numero para add
        case 42:
            switch(id_token)
            {
                case 19: estado = 3; agregar = 1;
                break;
                default:
                printf("Se esperaba un númeroo para agregar a la partición.\n\n");
                return;
            }
        break;
    }
}








