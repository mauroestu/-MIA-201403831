//Informacion para manipular archivos.
int tamanio = -1;
char unidad = '-';
char fichero[500];
char nombre[100] ;
char tipo = '-';
char ajuste[10] ;
char particion[10];
char Extend[3] = "dsk";
char ext_sh[2] = "sh";
int crear = 0; int eliminar = 0; int agregar = 0;
//Comandos a utilizar
int c_mkdisk = 0;
int c_rmdisk = 0;
int c_fdisk = 0;
int c_mount = 0;
int c_umount = 0;
int c_mbr = 0;
int c_disk = 0;
int c_exec = 0;

typedef struct TablaRegistro
{
    char nombre[100];
    char path[500];
    char total[500];
    int tama;
}Datos;

typedef struct estructura_primaria
{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}part_primaria;

typedef struct estructura_extend
{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}part_extended;

typedef struct Disco_MBR
{
    int mbr_tamanio;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    part_primaria mbr_partition_1;
    part_primaria mbr_partition_2;
    part_primaria mbr_partition_3;
    part_extended mbr_partition_4;
}MBR;

typedef struct mount
{
    char path[100];
    char nombre[100];
    char id[500];
}TablaMount;

void InicializarValores()
{
 tamanio = -1;
 unidad = '-';
 memset(fichero,0,500);
 memset(nombre,0,100);
 memset(ajuste,0,10);
 memset(particion,0,10);
 tipo = '-';
 crear=0;eliminar=0;agregar=0;
}

void ComillasFichero()
{
    char temp[500];
    strcpy(temp,fichero);
    memset(fichero,0,500);
    int i,conta = 0;
    for(i=0; i < strlen(temp);i++)
    {
        if(temp[i] != '\"')
        {
            fichero[conta] = temp[i];
            conta++;
        }
    }
}

void ComillasNombre()
{
    char temp[100];
    strcpy(temp,nombre);
    memset(nombre,0,100);
    int i,conta = 0;
    for(i=0; i < strlen(temp);i++)
    {
        if(temp[i] != '\"')
        {
            nombre[conta] = temp[i];
            conta++;
        }
    }
}

int extension()
{
    int ModoExtension = 0, conta =0 , i, logrado = -1;

    for(i = 0; i < strlen(nombre); i++)
    {
        if(ModoExtension == 1)
        {
            if(nombre[i] == Extend[conta])
            {
                logrado = 1;
                conta++;
            }
            else
            {
                ModoExtension = 0;
            }
        }
        else
        {
            logrado = 0;
        }

        if(nombre[i] == '.')
        {
            ModoExtension = 1;
        }
    }

    return ModoExtension;
}

int extension_sh()
{
    int ModoExtension = 0, conta =0 , i, logrado = -1;

    for(i = 0; i < strlen(fichero); i++)
    {
        if(ModoExtension == 1)
        {
            if(fichero[i] == ext_sh[conta])
            {
                logrado = 1;
                conta++;
            }
            else
            {
                ModoExtension = 0;
            }
        }
        else
        {
            logrado = 0;
        }

        if(fichero[i] == '.')
        {
            ModoExtension = 1;
        }
    }

    return ModoExtension;
}

void fdisk_crear();
void fdisk_eliminar();
void fdisk_agregar();

void EscribirTabla(Datos Tabla)
{
    FILE *Registro;
    Registro = fopen("Tabla_Registro.bin","ab+");
    fwrite(&Tabla,sizeof(Datos),1,Registro);
    fclose(Registro);
}

void InicializarComandos()
{
 c_mkdisk = 0;c_rmdisk = 0;c_fdisk = 0;c_mount = 0;c_umount = 0; c_mbr = 0; c_disk = 0; c_exec = 0;
}

void SelectorComandos()
{
    if(c_mkdisk == 1)
    {
        comando_mkdisk();
    }
    else if(c_rmdisk == 1)
    {
        comando_rmdisk();
    }
    else if(c_fdisk == 1)
    {
        comando_fdisk();
    }
    else if(c_mount == 1)
    {
        comando_mount();
    }
    else if(c_umount == 1)
    {

    }
    else if(c_mbr == 1)
    {

    }
    else if(c_disk == 1)
    {

    }
    else if(c_exec == 1)
    {
        script_exec();
    }
}

void comando_rmdisk()
{
    ComillasFichero();
    if(remove(fichero) == 0)
    {
        printf("El disco duro ha sido eliminado correctamente.\n\n",fichero);
    }
    else
    {
        printf("Error: No se pudo eliminar el disco duro.\n\n");
    }
}

void comando_mkdisk()
{
if(tamanio!=-1)
{
    int cBytes = 0;
    char c = '\0';
    char total[600];
    char directorio[600];
    memset(total,0,600);
    if(unidad == 'K')
    {
        cBytes = tamanio * 1000;
    }
    else
    {
        cBytes = tamanio *1000 *1000;
    }
    ComillasFichero();
    ComillasNombre();
    int exito = 0;

    exito = extension();

    if(exito == 0)
    {printf("Es obligatorio que la extensión sea .dsk\n\n"); return;}
    strcat(total,fichero);
    strcat(total,nombre);
    int j;
    for(j= 0; j<strlen(total); j++)
    {
        if(total[j] != '.')
        {
            directorio[j] = total[j];
        }
        else
        {break;}
    }

    mkdir(directorio);
    chmod(directorio,0777);
    strcat(directorio,"/");
    strcat(directorio,nombre);
    FILE *archivo;
    archivo = fopen(directorio,"ab+");
    int i;
    for(i=0; i < cBytes; i++)
    {
        fwrite(&c,sizeof(char),1,archivo);
    }

    Datos registro;
    strcpy(registro.nombre,nombre);
    strcpy(registro.path,fichero);
    strcpy(registro.total,total);
    registro.tama = cBytes;
    EscribirTabla(registro);
    fclose(archivo);
    printf("Partición con el nombre %s creada en %s.\n\n",nombre,fichero);
}
}

void comando_fdisk()
{
    if(crear == 1)
    {
        fdisk_crear();
    }
    else if(eliminar == 1)
    {
        fdisk_eliminar();
    }
    else if(agregar == 1)
    {
        fdisk_agregar();
    }
}

void fdisk_crear()
{}

void fdisk_eliminar()
{}

void fdisk_agregar()
{}

void comando_mount()
{
    ComillasFichero();
    ComillasNombre();

    FILE *archivo;
    archivo = fopen("Tabla_Particiones.bin","ab+");
    TablaMount registro;

    strcpy(registro.id,"vd");
    strcpy(registro.nombre,nombre);
    strcpy(registro.path,fichero);

    fwrite(&registro,sizeof(TablaMount),1,archivo);

    fclose(archivo);
}

void comando_umount()
{}

void reporte_mbr()
{}

void reporte_disk()
{}

void script_exec()
{
    ComillasFichero();
    int exito = extension_sh();
    char linea[500];
    char comando[500];
    if(exito == 1)
    {
        FILE *archivo;
        archivo = fopen(fichero,"r");
        if(archivo == NULL)
        {
            printf("El archivo no exite.\n\n");
            return;
        }

        while(fgets(linea,500,archivo) != NULL)
        {
            int i;
            for(i = 0; i < strlen(linea); i++)
            {
                if(linea[i] != '\n') { comando[i] = linea[i]; }
                else { break; }
            }
            RevisarComando(comando);
            memset(linea,0,500);
            memset(comando,0,500);
        }

        fclose(archivo);
    }
    else
    {
        printf("El script a subir debe tener la extension .sh\n\n");
        return;
    }
}

