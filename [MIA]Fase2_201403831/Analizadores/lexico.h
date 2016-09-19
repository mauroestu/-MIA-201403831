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
////////////////////////////////////////////fase 2//////////////////
char mkfs[10] = "mkfs"; int mkfs_e = 34;
char FS[10] = "+Fs"; int fs_e = 35;
char login[10] = "login"; int login_e = 36;
char usr[10] = "-usr"; int usr_e = 37;
char pwd[10] = "-pwd"; int pwd_e = 38;
char logout[10] = "logout"; int logout_e = 39;
char tunefs[10] = "tune2fs"; int tunefs_e = 40;
char loss[10] = "loss"; int loss_e = 41;
char recovery[10] = "recovery"; int recovery_e = 42;
///////////////Administracion de usuarios y grupos//////////////////
char mkgrp[10] = "mkgrp"; int mkgrp_e = 43;
char rmgrp[10] = "rmgrp"; int rmgrp_e = 44;
char mkusr[10] = "mkusr"; int mkusr_e = 45;
char rmusr[10] = "rmusr"; int rmusr_e = 46;
char grp[10] = "-grp"; int grp_e = 47;
/////////////////Archivos y Carpetas////////////////////////
char mkdirs[10] = "mkdir"; int mkdir_e = 48;
char p[10] = "+p"; int p_e = 49;
////////////////Reportes////////////////////////////////////
char inode[10] = "inode"; int inode_e = 50;
char journal[10] = "journaling"; int journal_e = 51;
char block[10] = "block"; int block_e = 52;
char bm_inode[10] = "bm_inode"; int bm_inode_e = 53;
char bm_block[10] = "bm_block"; int bm_block_e = 54;
char tree[10] = "tree"; int tree_e = 55;
char sb[10] = "sb"; int sb_e = 56;
char file[10] = "file"; int file_e = 57;
char lsi[10] = "ls+i"; int lsi_e = 58;
char lsl[10] = "ls+l"; int lsl_e = 59;
/////////////////////////////////////////////////////////////
char mkfile[10] = "mkfile"; int mkfile_e = 60;
char nsize[10] = "+size"; int nsize_e = 61;
char chgrp[10] = "chgrp"; int chgrp_e = 62;
char ren[10] = "ren"; int ren_e = 63;
char cat[10] = "cat"; int cat_e = 64;
char filen[10] = "-file"; int filen_e = 65;
char mv[10] = "mv"; int mv_e = 66;
char dest[10] = "-dest"; int dest_e = 67;
char ruta[10] = "+ruta"; int ruta_e = 68;
/**************Permisos prro*****************************/
char chmodd[10] = "chmod"; int chmod_e = 69;
char ugo[10] ="-ugo"; int ugo_e = 70;
char r[10] = "+r"; int r_e = 71;
char chown[10] = "chown"; int chown_e = 72;
/*****************Ediciones y eliminaciones lince :'v**************/
char edit[10] = "edit"; int edit_e = 73;


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
        else if(strcmp(temporal,ruta)==0)
        {
            Automata(0,temporal,ruta_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mkusr)==0)
        {
            Automata(0,temporal,mkusr_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,edit)==0)
        {
            Automata(0,temporal,edit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,chown)==0)
        {
            Automata(0,temporal,chown_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,chmodd)==0)
        {
            Automata(0,temporal,chmod_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,ugo)==0)
        {
            Automata(0,temporal,ugo_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,dest)==0)
        {
            Automata(0,temporal,dest_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,cat)==0)
        {
            Automata(0,temporal,cat_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mv)==0)
        {
            Automata(0,temporal,mv_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,ren)==0)
        {
            Automata(0,temporal,ren_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,filen)==0)
        {
            Automata(0,temporal,filen_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,chgrp)==0)
        {
            Automata(0,temporal,chgrp_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mkfile)==0)
        {
            Automata(0,temporal,mkfile_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,nsize)==0)
        {
            Automata(0,temporal,nsize_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mkdirs)==0)
        {
            Automata(0,temporal,mkdir_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,p)==0)
        {
            Automata(0,temporal,p_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,grp)==0)
        {
            Automata(0,temporal,grp_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,rmusr)==0)
        {
            Automata(0,temporal,rmusr_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,mkgrp)==0)
        {
            Automata(0,temporal,mkgrp_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,rmgrp)==0)
        {
            Automata(0,temporal,rmgrp_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,unit)==0)
        {
            Automata(0,temporal,unit_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,tunefs)==0)
        {
            Automata(0,temporal,tunefs_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,logout)==0)
        {
            Automata(0,temporal,logout_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,login)==0)
        {
            Automata(0,temporal,login_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,usr)==0)
        {
            Automata(0,temporal,usr_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,pwd)==0)
        {
            Automata(0,temporal,pwd_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,path)==0)
        {
            Automata(0,temporal,path_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,rep) == 0)
        {
            Automata(0,temporal,rep_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,rmbr) == 0)
        {
            Automata(0,temporal,mbr_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,loss) == 0)
        {
            Automata(0,temporal,loss_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,recovery) == 0)
        {
            Automata(0,temporal,recovery_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,disk) == 0)
        {
            Automata(0,temporal,disk_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,inode) == 0)
        {
            Automata(0,temporal,inode_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,journal) == 0)
        {
            Automata(0,temporal,journal_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,block) == 0)
        {
            Automata(0,temporal,block_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,bm_inode) == 0)
        {
            Automata(0,temporal,bm_inode_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,bm_block) == 0)
        {
            Automata(0,temporal,bm_block_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,tree) == 0)
        {
            Automata(0,temporal,tree_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,sb) == 0)
        {
            Automata(0,temporal,sb_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,file) == 0)
        {
            Automata(0,temporal,file_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,lsi) == 0)
        {
            Automata(0,temporal,lsi_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,lsl) == 0)
        {
            Automata(0,temporal,lsl_e);
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
        else if(strcmp(temporal,mkfs) == 0)
        {
            Automata(0,temporal,mkfs_e);
            Inicializar();
            return 1;
        }
        else if(strcmp(temporal,FS) == 0)
        {
            Automata(0,temporal,fs_e);
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
            Automata(0,temporal,Full_e);
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
                case 22: estado = 43; //rep
                break;
                case 25: estado = 24; //exec
                break;
                case 34: estado = 50; //mkfs
                break;
                case 36: estado = 61; //login
                break;
                case 39: estado = 0; c_logout = 1;//logout
                break;
                case 40: estado = 66; //Tunefs
                break;
                case 41: estado = 69;//loss
                break;
                case 42: estado = 72;//recovery
                break;
                case 43: estado = 75; //mkgrp
                break;
                case 44: estado = 80; //rmgrp
                break;
                case 45: estado = 90;//mkusr
                break;
                case 46: estado = 85; //rmusr
                break;
                case 48: estado = 99;//mkdir
                break;
                case 60: estado = 104; //mkfile
                break;
                case 62: estado = 111; //chgrp
                break;
                case 63: estado = 116; //ren
                break;
                case 64: estado = 123; //cat
                break;
                case 66: estado = 129; //mv
                break;
                case 69: estado = 138;//chmod
                break;
                case 72: estado = 145;//chown
                break;
                case 73: estado = 152; //edit
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
                    mostrarParticiones();
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
                comando_umount();
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
        case 20: //mount, numero para id
            switch(id_token)
            {
                case 19: estado = 21;
                break;
                default:
                printf("Se esperaba un número que indique el número dél parámetro.\n\n");
                return;
            }
        break;
        case 21: //mount, :: para mount
            switch(id_token)
            {
                case 15: estado = 23;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 23:
            switch(id_token)
            {
                case 18: estado = 5; memset(cadId,0,30); strcat(cadId,token); comando_umount();
                break;
                default:
                printf("Se esperaba un path con el id a desmontar.\n\n");
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
                case 19: estado = 3; tamanio = entero; crear = 1;
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
                case 16: estado = 3; unidad = 'K';
                break;
                case 17: estado = 3; unidad = 'M';
                break;
                case 21: estado = 3; unidad = 'B';
                break;
                default:
                printf("Se esparaba K, M o B para el tipo de unidades.\n\n");
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
                case 18: estado = 3; strcpy(fichero,token);
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
                case 18: estado = 3; strcpy(nombre,token);
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
                case 26: estado = 3; tipo = 'P';
                break;
                case 27: estado = 3; tipo = 'E';
                break;
                case 28:  estado = 3; tipo = 'L';
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
                case 29: estado = 3; strcpy(ajustefit,token);
                break;
                case 30: estado = 3; strcpy(ajustefit,token);
                break;
                case 31: estado = 3; strcpy(ajustefit,token);
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
                case 32: estado = 3; eliminar = 1; strcpy(tEliminacion,"Fast");
                break;
                case 33: estado = 3; eliminar = 1; strcpy(tEliminacion,"Full");
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
        case 43: //parametros para rep
            switch(id_token)
            {
                case 8: estado = 44; //path
                break;
                case 9: estado = 46;//name
                break;
                case 14: estado = 48;//id
                break;
                case 68: estado = 136; //ruta
                break;
                default:
                    if(strcmp(tReport,"\0") != 0 && strcmp(fichero,"\0") != 0 && strcmp(cadId,"\0") != 0)
                    { estado = 0; reportes(); }
                    else
                    {
                        printf("Faltan parametros para el comando rep.\n\n");
                    }
                return;
            }
        break;
        case 44: //rep, :: para path
            switch(id_token)
            {
                case 15: estado = 45;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 45: //rep, cadena para path
            switch(id_token)
            {
                case 18: estado = 43; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena que indique donde se guardará el reporte.\n\n");
                return;
            }
        break;
        case 46: //rep, :: para name
            switch(id_token)
            {
                case 15: estado = 47;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 47: //rep, tipo de reporte, para name
            switch(id_token)
            {
                case 23: estado = 43; strcpy(tReport,token); //mbr
                break;
                case 24: estado = 43; strcpy(tReport,token); //disk
                break;
                case 50: estado = 43; strcpy(tReport,token); //inode
                break;
                case 51: estado = 43; strcpy(tReport,token); //journal
                break;
                case 52: estado = 43; strcpy(tReport,token); //block
                break;
                case 53: estado = 43; strcpy(tReport,token); //bm_inode
                break;
                case 54: estado = 43; strcpy(tReport,token); //bm_block
                break;
                case 55: estado = 43; strcpy(tReport,token); //tree
                break;
                case 56: estado = 43; strcpy(tReport,token); //sb
                break;
                case 57: estado = 43; strcpy(tReport,token); //file
                break;
                case 58: estado = 43; strcpy(tReport,token); //lsi
                break;
                case 59: estado = 43; strcpy(tReport,token); //lsl
                break;
                default:
                printf("Se esperaba el nombre del reporte a mostrar.\n\n");
                return;
            }
        break;
        case 48: //rep, :: para id
            switch(id_token)
            {
                case 15: estado = 49;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 49: //rep, path para el id
            switch(id_token)
            {
                case 18: estado = 43; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena que contenga el id de la partición.\n\n");
                return;
            }
        break;
        case 50: //Comandos de mkfs
            switch(id_token)
            {
                case 14: estado = 51;//-id
                break;
                case 10: estado = 53; //+type
                break;
                case 13: estado = 57;//+add
                break;
                case 7: estado = 55;//+unit
                break;
                case 35: estado = 59;//+Fs
                break;
                default:
                    if(strcmp(cadId,"\0") != 0)
                    { estado = 0; c_mkfs = 1; }
                    else
                    { printf("Faltan parametros para el comando mkfs.\n\n"); }
                return;
            }
        break;
        case 51: //:: para -id
            switch(id_token)
            {
                case 15: estado = 52;
                break;
                default:
                    printf("Se esparaba ::\n\n");
                return;
            }
        break;
        case 52: //path para id
            switch(id_token)
            {
                case 18: estado = 50; strcpy(cadId,token);
                break;
                default:
                    printf("Se esperaba una cadena con el id a formatear.\n\n");
                return;
            }
        break;
        case 53: //:: para +type
            switch(id_token)
            {
                case 15: estado = 54;
                break;
                default:
                    printf("Se esparaba ::\n\n");
                return;
            }
        break;
        case 54: //Fast o full para +type
            switch(id_token)
            {
                case 32: estado = 50; strcpy(tFormateo,"Fast");
                break;
                case 33: estado = 50; strcpy(tFormateo,"Full");
                break;
                default:
                    printf("Se esperaba Fast o Full.\n\n");
                return;
            }
        break;
        case 55: //:: para unit
            switch(id_token)
            {
                case 15: estado = 56;
                break;
                default:
                    printf("Se esparaba ::\n\n");
                return;
            }
        break;
        case 56: //Typs de datos para unit b k m
            switch(id_token)
            {
                case 21: estado = 50; unidad = 'B'; //B
                break;
                case 16: estado = 50; unidad = 'K'; //K
                break;
                case 17: estado = 50; unidad = 'M'; //M
                break;
                default:
                    printf("Se esperaba el tipo de unidades B, k o M.\n\n");
                break;
            }
        break;
        case 57: //:: para add
            switch(id_token)
            {
                case 15: estado = 58;
                break;
                default:
                    printf("Se esparaba ::\n\n");
                return;
            }
        break;
        case 58: //numero para add
            switch(id_token)
            {
                case 19: estado = 50; tamanio = entero;
                break;
                default:
                    printf("Se esperaba un número que indique las unidades.");
                return;
            }
        break;
        case 59: //:: para FS
            switch(id_token)
            {
                case 15: estado = 60;
                break;
                default:
                    printf("Se esparaba ::\n\n");
                return;
            }
        break;
        case 60: //Tipo de sistema de archivos
            switch(id_token)
            {
                case 18: estado = 50; strcpy(fichero,token);
                break;
                default:
                    printf("Se esperaba una cadena con el tipo de sistema de archivos.\n\n");
                return;
            }
        break;
        case 61: //Comandos para login
            switch(id_token)
            {
                case 37: estado = 62; //usr
                break;
                case 38: estado = 64; //pwd
                break;
                default:
                if(strcmp(usuario,"\0") != 0 &&  strcmp(pass,"\0") !=0)
                { estado = 0; c_login = 1;}
                else{ printf("Faltan parametros para el comando login.\n\n"); }
                return;
            }
        break;
        case 62: //:: para usr
            switch(id_token)
            {
                case 15: estado = 63;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 63: //cadena para usr
            switch(id_token)
            {
                case 18: estado = 61; strcpy(usuario,token);
                break;
                default: printf("Se esperaba una cadena con el nombre del usuario.\n\n");
                return;
            }
        break;
        case 64: //:: para pwd
            switch(id_token)
            {
                case 15: estado = 65;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 65: //path para pwd
            switch(id_token)
            {
                case 18: estado = 61; strcpy(pass,token);
                break;
                default: printf("Se esperaba una cadena con el password del usuario.\n\n");
                return;
            }
        break;
        case 66: //Comandos para tune2fs
            switch(id_token)
            {
                case 14: estado = 67; //-id
                break;
                default:
                if(strcmp(cadId,"\0")!=0)
                { estado = 0; c_tunefs = 1;}
                else { printf("Se esperaba el parametro -id.\n\n"); }
                return;
            }
        break;
        case 67: //:: para id
            switch(id_token)
            {
                case 15: estado = 68;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 68: //path para id
            switch(id_token)
            {
                case 18: estado = 66; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la partición.\n\n");
                return;
            }
        break;
        case 69: //Comandos para loss
            switch(id_token)
            {
                case 14: estado = 70; //-id
                break;
                default:
                if(strcmp(cadId,"\0")!=0)
                { estado = 0; c_loss = 1;}
                else { printf("Se esperaba el parametro -id.\n\n"); }
                return;
            }
        break;
        case 70: //:: para loss
            switch(id_token)
            {
                case 15: estado = 71;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 71: //path para loss
            switch(id_token)
            {
                case 18: estado = 69; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la partición.\n\n");
                return;
            }
        break;
        case 72: //Comandos para recovery
            switch(id_token)
            {
                case 14: estado = 73; //-id
                break;
                default:
                if(strcmp(cadId,"\0")!=0)
                { estado = 0; c_recovery= 1;}
                else { printf("Se esperaba el parametro -id.\n\n"); }
                return;
            }
        break;
        case 73: //:: para recovery
            switch(id_token)
            {
                case 15: estado = 74;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 74: //path para recovery
            switch(id_token)
            {
                case 18: estado = 72; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la partición.\n\n");
                return;
            }
        break;
        case 75: //comandos para mkgrp
            switch(id_token)
            {
                case 14: estado = 76;//-id
                break;
                case 9: estado = 78;//-name
                break;
                default:
                if(strcmp(cadId,"\0")!=0 && strcmp(nombre,"\0")!=0)
                { estado = 0; c_mkgrp = 1;}
                else
                printf("Faltan parametros para el comando mkgrp.\n\n");
                return;
            }
        break;
        case 76: //:: para id
            switch(id_token)
            {
                case 15: estado = 77;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 77: //path para id
            switch(id_token)
            {
                case 18: estado = 75; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la partición.\n\n");
                return;
            }
        break;
         case 78: //:: para name
            switch(id_token)
            {
                case 15: estado = 79;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 79: //path para name
            switch(id_token)
            {
                case 18: estado = 75; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del grupo a crear.\n\n");
                return;
            }
        break;
        case 80: //comando rmgrp
            switch(id_token)
            {
                case 14: estado = 81;//-id
                break;
                case 9: estado = 83;//-name
                break;
                default:
                if(strcmp(cadId,"\0") != 0 && strcmp(nombre,"\0") != 0)
                { estado = 0; c_rmgrp = 1; }
                else
                    printf("Faltan parametros para el comando rmgrp\n\n");
                return;
            }
        break;
        case 81: //:: para -id
            switch(id_token)
            {
                case 15: estado = 82;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 82: //path para -id
            switch(id_token)
            {
                case 18: estado = 80; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion del disco.\n\n");
                return;
            }
        break;
        case 83: //:: para -name
            switch(id_token)
            {
                case 15: estado = 84;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 84: //path para -name
            switch(id_token)
            {
                case 18: estado = 80; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del grupo a eliminar.\n\n");
                return;
            }
        break;
        case 85: //comandos rmusr
            switch(id_token)
            {
                case 14: estado = 86;//-id
                break;
                case 37: estado = 88;//-usr
                break;
                default:
                if(strcmp(cadId,"\0") != 0 && strcmp(nombre,"\0") != 0)
                { estado = 0; c_rmusr = 1; }
                else
                    printf("Faltan parametros para el comando rmusr\n\n");
                return;
            }
        break;
        case 86: //:: para -id
            switch(id_token)
            {
                case 15: estado = 87;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 87: //path para -id
            switch(id_token)
            {
                case 18: estado = 85; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion del disco.\n\n");
                return;
            }
        break;
        case 88: //:: para -usr
            switch(id_token)
            {
                case 15: estado = 89;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 89: //path para -usr
            switch(id_token)
            {
                case 18: estado = 85; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del usuario a eliminar.\n\n");
                return;
            }
        break;
        case 90: //comandos para mkusr
            switch(id_token)
            {
                case 14: estado = 91;//-id
                break;
                case 37: estado = 93;//-usr
                break;
                case 38: estado = 95;//-pwd
                break;
                case 47: estado = 97;//-grp
                break;
                default:
                    if(strcmp(cadId,"\0") != 0 && strcmp(usuario,"\0") != 0 && strcmp(pass,"\0") != 0 && strcmp(nombre,"\0") != 0)
                    { estado = 0; c_mkusr = 1; }
                    else
                    printf("Faltan parametros para el comando mkusr\n\n");
                return;
            }
        break;
        case 91: //:: para id
            switch(id_token)
            {
                case 15: estado = 92;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 92: //path para -id
            switch(id_token)
            {
                case 18: estado = 90; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion del disco.\n\n");
                return;
            }
        break;
        case 93: //:: para -usr
            switch(id_token)
            {
                case 15: estado = 94;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 94: //path para -usr
            switch(id_token)
            {
                case 18: estado = 90; strcpy(usuario,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del usuario a crear.\n\n");
                return;
            }
        break;
        case 95: //:: para -pwd
            switch(id_token)
            {
                case 15: estado = 96;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 96: //path para -pwd
            switch(id_token)
            {
                case 18: estado = 90; strcpy(pass,token);
                break;
                default:
                printf("Se esperaba una cadena con el pass del usuario a crear.\n\n");
                return;
            }
        break;
         case 97: //:: para -grp
            switch(id_token)
            {
                case 15: estado = 98;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 98: //path para -grp
            switch(id_token)
            {
                case 18: estado = 90; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del grupo.\n\n");
                return;
            }
        break;
        case 99: //comandos mkdir
            switch(id_token)
            {
                case 14: estado = 100;//-id
                break;
                case 8: estado = 102;//-path
                break;
                case 49: estado = 99; padre = '1';//+p
                break;
                default:
                    if(strcmp(cadId,"\0")!=0 && strcmp(fichero,"\0")!=0 )
                    { estado = 0; c_mkdir = 1; }
                    else
                    printf("Faltan parametros para el comando mkdir\n\n");
                return;
            }
        break;
        case 100: //:: para id
            switch(id_token)
            {
                case 15: estado = 101;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 101: //path para -id
            switch(id_token)
            {
                case 18: estado = 99; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion del disco.\n\n");
                return;
            }
        break;
        case 102: //:: para -path
            switch(id_token)
            {
                case 15: estado = 103;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 103: //path para -path
            switch(id_token)
            {
                case 18: estado = 99; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el path a crear.\n\n");
                return;
            }
        break;
        case 104: //mkfile
            switch(id_token)
            {
                case 14: estado = 105;//-id
                break;
                case 8:  estado = 107;//-path
                break;
                case 49: estado = 104; padre = '1';//+p
                break;
                case 61: estado = 109;//+size
                break;
                default:
                if(strcmp(cadId,"\0")!= 0 && strcmp(fichero,"\0") != 0)
                { estado = 1; c_mkfile = 1;}
                else
                { printf("Faltan parametros del comando mkfile.\n\n"); }
                return;
            }
        break;
        case 105: //:: para id
            switch(id_token)
            {
                case 15: estado = 106;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 106: //cadena para id
            switch(id_token)
            {
                case 18: estado = 104; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la partición.\n\n");
                return;
            }
        break;
        case 107: //:: para path
            switch(id_token)
            {
                case 15: estado = 108;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 108: //cadena para path
            switch(id_token)
            {
                case 18: estado = 104; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el archivo a crear.\n\n");
                return;
            }
        break;
        case 109: //:: para size
            switch(id_token)
            {
                case 15: estado = 110;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 110: //numero para size
            switch(id_token)
            {
                case 19: estado = 104; tamanio = entero;
                break;
                default:
                    printf("Se esperaba un número que indique las unidades.");
                return;
            }
        break;
        case 111: //Comandos para chgrp
            switch(id_token)
            {
                case 37: estado = 112;//usr
                break;
                case 47: estado = 114;//grp
                break;
                default:
                if(strcmp(usuario,"\0")!= 0 && strcmp(nombre,"\0")!=0)
                { estado = 0; c_chgrp = 1;}
                else
                { printf("Faltan parametros para el comando chgrp.\n\n"); }
                return;
            }
        break;
        case 112: //:: para usr
            switch(id_token)
            {
                case 15: estado = 113;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 113: //cadena para usr
            switch(id_token)
            {
                case 18: estado = 111; strcpy(usuario,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del usuario.\n\n");
                return;
            }
        break;
        case 114: //:: para grp
            switch(id_token)
            {
                case 15: estado = 115;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 115: //Cadena para grp
             switch(id_token)
            {
                case 18: estado = 111; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nombre del grupo.\n\n");
                return;
            }
        break;
        case 116: //Comandos para ren
            switch(id_token)
            {
                case 14: estado = 117;//id
                break;
                case 8: estado = 119;//path
                break;
                case 9: estado = 121;//name
                break;
                default:
                if(strcmp(cadId,"\0")!=0 && strcmp(fichero,"\0")!=0 && strcmp(nombre,"\0")!=0)
                { estado = 0; c_ren = 1;}
                else
                { printf("Faltan parametros para el comando ren.\n\n"); }
                return;
            }
        break;
        case 117: //:: para id
             switch(id_token)
            {
                case 15: estado = 118;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 118: //cadena para Id.
            switch(id_token)
            {
                case 18: estado = 116; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id del grupo.\n\n");
                return;
            }
        break;
         case 119: //:: para path
             switch(id_token)
            {
                case 15: estado = 120;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 120: //cadena para path.
            switch(id_token)
            {
                case 18: estado = 116; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el path del archivo o carpeta.\n\n");
                return;
            }
        break;
        case 121: //:: para name
             switch(id_token)
            {
                case 15: estado = 122;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 122: //cadena para name.
            switch(id_token)
            {
                case 18: estado = 116; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nuevo nombre del archivo o carpeta.\n\n");
                return;
            }
        break;
        case 123: //Comandos para cat
            switch(id_token)
            {
                case 14: estado = 124;//id
                break;
                case 65: estado = 126;//file
                break;
                default:
                estado = 0;
                return;
            }
        break;
        case 124: //:: para id
            switch(id_token)
            {
                case 15: estado = 125;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 125: //cadena para id
            switch(id_token)
            {
                case 18: estado = 123; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion.\n\n");
                return;
            }
        break;
        case 126: //numero para file
            switch(id_token)
            {
                case 19: estado = 127;
                break;
                default:
                printf("Se esperaba el numero de comando.\n\n");
                return;
            }
        break;
        case 127: //:: para file
            switch(id_token)
            {
                case 15: estado = 128;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 128: //cadena par file
            switch(id_token)
            {
                case 18: estado = 123; memset(fichero,0,500); strcpy(fichero,token); comando_cat();
                break;
                default:
                printf("Se esperaba una cadena con el nombre del archivo.\n\n");
                return;
            }
        break;
        case 129: //parametros para mv
            switch(id_token)
            {
                case 14: estado = 130;//_id
                break;
                case 8: estado = 132;//path
                break;
                case 67: estado = 134;//dest
                break;
                default:
                    if(strcmp(cadId,"\0")!=0 && strcmp(fichero,"\0") != 0 && strcmp(nombre,"\0") !=0)
                    {estado = 0; c_mv = 1;}
                    else
                    { printf("Faltan parametros para el comando mv.\n\n"); }
                return;
            }
        break;
        case 130: //:: para id
            switch(id_token)
            {
                case 15: estado = 131;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 131: //cadena para id
            switch(id_token)
            {
                case 18: estado = 129; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion.\n\n");
                return;
            }
        break;
        case 132: //:: para path
            switch(id_token)
            {
                case 15: estado = 133;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 133: //cadena para path
            switch(id_token)
            {
                case 18: estado = 129; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el fichero a mover.\n\n");
                return;
            }
        break;
        case 134: //:: para dest
            switch(id_token)
            {
                case 15: estado = 135;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 135: //cadena para dest
            switch(id_token)
            {
                case 18: estado = 129; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el nuevo destino.\n\n");
                return;
            }
        break;
        case 136: //:: para ruta
            switch(id_token)
            {
                case 15: estado = 137;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 137: //cadena para ruta
            switch(id_token)
            {
                case 18: estado = 43; strcpy(nombre,token);
                break;
                default:
                printf("Se esperaba una cadena con el archivo a leer.\n\n");
                return;
            }
        break;
        case 138:
            switch(id_token)
            {
                case 70: estado = 139;//ugo
                break;
                case 14: estado = 141;//id
                break;
                case 8: estado = 143;//path
                break;
                case 71: estado = 138; recursivo = '1';//+r
                break;
                default:
                if(strcmp(cadId,"\0") != 0 && strcmp(fichero,"\0") != 0 && tamanio != -1)
                { estado = 0; c_chmod = 1;}
                else
                { printf("Faltan parametros para el comando chmod.\n\n"); }
                return;
            }
        break;
        case 139: //:: para ugo
            switch(id_token)
            {
                case 15: estado = 140;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 140: //numero para ugo
            switch(id_token)
            {
                case 19: estado = 138; tamanio = entero;
                break;
                default:
                printf("Se esperaba un numero con el nuevo permiso.\n\n");
                return;
            }
        break;
        case 141: //:: para id
            switch(id_token)
            {
                case 15: estado = 142;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 142: //cadena para id
            switch(id_token)
            {
                case 18: estado = 138; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id del disco.\n\n");
                return;
            }
        break;
        case 143: //:: para path
            switch(id_token)
            {
                case 15: estado = 144;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 144: //cadena para path
            switch(id_token)
            {
                case 18: estado = 138; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el fichero a cambiar Permiso.\n\n");
                return;
            }
        break;
        case 145: //Comandos para chown
            switch(id_token)
            {
                case 14: estado = 146;//id
                break;
                case 8: estado = 148;//path
                break;
                case 37: estado = 150;//usr
                break;
                case 71: estado = 145; recursivo = '1';//+r
                break;
                default:
                if(strcmp(cadId,"\0") != 0 && strcmp(fichero,"\0") != 0 && strcmp(usuario,"\0") != 0)
                { estado = 0; c_chown = 1; }
                else
                { printf("Faltan comandos para el parametro chown.\n\n"); }
                return;
            }
        break;
        case 146: //:: para id
            switch(id_token)
            {
                case 15: estado = 147;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 147: //cadena para id
            switch(id_token)
            {
                case 18: estado = 145; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena con el id de la particion.\n\n");
                return;
            }
        break;
        case 148: //:: para path
            switch(id_token)
            {
                case 15: estado = 149;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 149: //cadena para path
            switch(id_token)
            {
                case 18: estado = 145; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena con el fichero a cambiar.\n\n");
                return;
            }
        break;
        case 150: //:: para usr
            switch(id_token)
            {
                case 15: estado = 151;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 151: //cadena para usr
            switch(id_token)
            {
                case 18: estado = 145; strcpy(usuario,token);
                break;
                default:
                printf("Se esperaba una cadena con el nuevo usuario.\n\n");
                return;
            }
        break;
        case 152: //comandos para edit
            switch(id_token)
            {
                case 14: estado = 153;//-id
                break;
                case 8: estado = 155;//-path
                break;
                case 61: estado = 157;//+size
                break;
                default:
                if(strcmp(cadId,"\0") != 0 && strcmp(fichero,"\0") != 0 )
                { estado = 0; c_edit = 1; }
                else
                { printf("Faltan parametros para el comando edit.\n\n"); }
                return;
            }
        break;
        case 153: //:: para id
            switch(id_token)
            {
                case 15: estado = 154;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 154: //cadena para id
            switch(id_token)
            {
                case 18: estado = 152; strcpy(cadId,token);
                break;
                default:
                printf("Se esperaba una cadena.\n\n");
                return;
            }
        break;
        case 155: //:: para path
            switch(id_token)
            {
                case 15: estado = 156;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 156: //cadena para path
            switch(id_token)
            {
                case 18: estado = 152; strcpy(fichero,token);
                break;
                default:
                printf("Se esperaba una cadena.\n\n");
                return;
            }
        break;
        case 157: //:: para size
            switch(id_token)
            {
                case 15: estado = 158;
                break;
                default:
                printf("Se esperaba ::\n\n");
                return;
            }
        break;
        case 158: //cadena para path
            switch(id_token)
            {
                case 19: estado = 152; tamanio = entero;
                break;
                default:
                printf("Se esperaba un numero.\n\n");
                return;
            }
        break;
    }
}








