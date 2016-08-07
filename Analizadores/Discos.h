//Informacion para manipular archivos.
int tamanio = -1;
char unidad = '-';
char fichero[500];
char nombre[100] ;
char tipo = '-';
char ajuste[10] ;
char particion[10];
char Extend[3] = "dsk";

//Comandos a utilizar
int c_mkdisk = 0;
int c_rmdisk = 0;
int c_fdisk = 0;
int c_mount = 0;
int c_umount = 0;

typedef struct TablaRegistro
{
    int intParticiones;
    char path[500];

}Datos;

void InicializarValores()
{
 tamanio = -1;
 unidad = '-';
 memset(fichero,0,500);
 memset(nombre,0,100);
 memset(ajuste,0,10);
 memset(particion,0,10);
 tipo = '-';
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

void InicializarComandos()
{
 c_mkdisk = 0;c_rmdisk = 0;c_fdisk = 0;c_mount = 0;c_umount = 0;
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
    {}
    else if(c_mount == 1)
    {

    }
    else if(c_umount == 1)
    {}
    else
    {}


}

void comando_rmdisk()
{

}

void comando_mkdisk()
{
if(tamanio!=-1)
{
    int cBytes = 0;
    char c = '\0';
    char total[600];
    memset(total,0,600);
    if(unidad == 'K')
    {
        cBytes = tamanio;

    }
    else
    {
        cBytes = tamanio;
    }
    ComillasFichero();
    ComillasNombre();
    int exito = 0;

    exito = extension();

    if(exito == 0)
    {printf("Es obligatorio que la extensión sea .dsk"); return;}
    strcat(total,fichero);
    strcat(total,nombre);
    FILE *archivo;
    archivo = fopen(total,"ab+");
    fwrite(&c,1024*1024,1,archivo);

    fclose(archivo);
    printf("Partición con el nombre %s creada en %s.\n\n",nombre,fichero);
}
}
