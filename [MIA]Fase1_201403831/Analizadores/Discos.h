//Informacion para manipular archivos.
int tamanio = -1;
char unidad = '-';
char fichero[500];
char nombre[100] ;
char pfich[500];
char tipo = '-';
char tEliminacion[10];
char tReport[10];
char ajustefit[10] ;
char particion[10];
char Extend[3] = "dsk";
char ext_sh[2] = "sh";
char cadId[30];
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
    char fecha[128];
    int activo;
    int tama;
}Datos;

typedef struct estructura_primaria
{
    char part_status;
    char part_type;
    char part_fit[10];
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
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    part_primaria mbr_partition_1;
    part_primaria mbr_partition_2;
    part_primaria mbr_partition_3;
    part_primaria mbr_partition_4;
    part_extended mbr_partition;
}MBR;

typedef struct mount
{
    char path[100];
    char nombre[100];
    char id[10];
    int activo;
}TablaMount;

void InicializarValores()
{
 tamanio = -1;
 unidad = '-';
 memset(fichero,0,500);
 memset(nombre,0,100);
 memset(ajustefit,0,10);
 memset(particion,0,10);
 memset(tReport,0,10);
 memset(cadId,0,30);
 memset(tEliminacion,0,10);
 memset(pfich,0,500);
 tipo = '-';
 crear=0;eliminar=0;agregar=0;
}

void InicializarComandos()
{
 c_mkdisk = 0;c_rmdisk = 0;c_fdisk = 0;c_mount = 0;c_umount = 0; c_mbr = 0; c_disk = 0; c_exec = 0;
}

MBR returnMBR(char disco[])
{
    MBR mbrDisco;

    FILE *archivo = fopen(disco,"r+b");
    if(archivo == NULL)
    { printf("No existe el disco duro.\n\n"); return;}
    fread(&mbrDisco,sizeof(MBR),1,archivo);
    fclose(archivo);

    return mbrDisco;
}

void ComillasCadId()
{
    char temp[30];
    strcpy(temp,cadId);
    memset(cadId,0,30);
    int i, conta = 0;
    for(i = 0; i < strlen(temp); i++)
    {
        if(temp[i] != '\"')
        {
            cadId[conta] = temp[i];
            conta++;
        }
    }
}

void Directorio()
{
    int i,j=0;
    char aux1[100];
    for(i = 0; i < strlen(fichero); i++)
    {
        if(fichero[i] != '.')
        {
            pfich[i] = fichero[i];
        }
        else
        {break;}
    }

    for(i = 0; i < strlen(fichero); i++)
    {
        if(fichero[i] != '/')
        {
            aux1[j] = fichero[i];
            j++;
        }
        else
        {
            memset(aux1,0,100);
            j=0;
        }
    }
    memset(fichero,0,500);
    strcpy(fichero,pfich);
    strcat(fichero,"/");
    strcat(fichero,aux1);
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
        comando_mount();
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

void reemplazoMBR(char directorio[], MBR disco)
{
    FILE *Registro;
    Registro = fopen(directorio,"r+b");
    fseek(Registro, 0 , SEEK_SET);
    fwrite(&disco, sizeof(MBR),1,Registro);
    fclose(Registro);
    MBR aux;
    aux = returnMBR(directorio);
    //printf("%c - %d\n",aux.mbr_partition_1.part_status,aux.mbr_partition_1.part_size);
    //printf("%c - %d\n",aux.mbr_partition_2.part_status,aux.mbr_partition_2.part_size);
    //printf("%c - %d\n",aux.mbr_partition_3.part_status,aux.mbr_partition_3.part_size);
    //printf("%c - %d\n",aux.mbr_partition_4.part_status,aux.mbr_partition_4.part_size);
}

void comando_rmdisk()
{

    ComillasFichero();
    char sino;
    fflush(stdin);
    printf("¿Desea eliminar el disco duro? s/n ");
    getchar();
    scanf("%c",&sino);

    if(sino == 's' || sino == 'S')
    {
    if(remove(fichero) == 0)
    {
        printf("El disco duro ha sido eliminado correctamente.\n\n",fichero);
        FILE *Registro;
        Registro = fopen("Tabla_Registro.bin","r+b");
        int posicion = 0;
        Datos auxiliar, reg;
        fread(&auxiliar,sizeof(Datos),1,Registro);
        while(!feof(Registro))
        {
            posicion++;
            if(strcmp(auxiliar.total,fichero) == 0)
            { break; }
            else
            { fread(&auxiliar,sizeof(Datos),1,Registro); }
        }
        posicion--;
        fseek(Registro, posicion * sizeof(Datos), SEEK_SET);
        reg = auxiliar;
        reg.activo = 0;

        fwrite(&reg, sizeof(Datos), 1, Registro);

        fclose(Registro);
        Datos aux;
        Registro = fopen("Tabla_Registro.bin","rb");
        fread(&aux,sizeof(Datos),1,Registro);

        while(!feof(Registro))
        {
            fread(&aux,sizeof(Datos),1,Registro);
        }

        fclose(Registro);
    }
    else
    {
        printf("Error: No se pudo eliminar el disco duro.\n\n");
    }
    }
    else
    {
      return;
    }
}

void mostrarParticiones()
{
    FILE *Registro;
    TablaMount auxiliar;
    Registro = fopen("Tabla_Particiones.bin","rb");
    if(Registro == NULL)
    { printf("No hay particiones montadas.\n\n"); return; }

    fread(&auxiliar, sizeof(TablaMount),1,Registro);
    while(!feof(Registro))
    {
        if(auxiliar.activo == 1)
        {
            printf("%d %s | %s | %s | montada.\n",auxiliar.activo,auxiliar.id,auxiliar.nombre,auxiliar.path);
        }
        fread(&auxiliar, sizeof(TablaMount),1,Registro);
    }
    printf("\n");
    fclose(Registro);
}

int CantParticiones()
{
    int cantidad = 0;
    FILE *Registro;
    TablaMount auxiliar;
    Registro = fopen("Tabla_Particiones.bin","rb");
    if(Registro == NULL)
    { return 1;}

    fread(&auxiliar, sizeof(TablaMount),1,Registro);
    while(!feof(Registro))
    {
        cantidad++;
        fread(&auxiliar, sizeof(TablaMount),1,Registro);
    }
    cantidad++;
    fclose(Registro);
    return cantidad;
}

int CantRegistros()
{
    int cantidad = 0;
    FILE *Registro;
    Datos auxiliar;
    Registro = fopen("Tabla_Registro.bin","rb");
    if(Registro == NULL)
    { return 1; }

    fread(&auxiliar, sizeof(Datos),1,Registro);
    while( !feof( Registro ) )
    {

        cantidad++;
        fread(&auxiliar, sizeof(Datos),1,Registro);
    }

    cantidad++;
    fclose(Registro);
    return cantidad;
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
        cBytes = tamanio * 1024;
    }
    else
    {
        cBytes = tamanio *1024 *1024;
    }
    ComillasFichero();
    ComillasNombre();
    int exito = 0;
    mkdir(fichero);
    chmod(fichero,0777);
    exito = extension();

    if(exito == 0)
    {printf("Es obligatorio que la extensión sea .dsk\n\n"); return;}
    strcat(total,fichero);
    strcat(total,nombre);


    Datos registro;
    strcpy(registro.nombre,nombre);
    strcpy(registro.path,fichero);
    strcpy(registro.total,total);
    registro.activo = 1;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(registro.fecha,128,"%d/%m/%y %H:%M:%S",tlocal);
    registro.tama = cBytes;

    //Inserción del mbr
    MBR tabla_mbr;
    part_primaria datos_primaria;
    part_extended datos_extend;
    datos_primaria.part_status = 'i';
    datos_extend.part_status = 'i';
    tabla_mbr.mbr_tamanio = cBytes;
    int numero;
    numero = CantRegistros();
    strftime(tabla_mbr.mbr_fecha_creacion,128,"%d/%m/%y %H:%M:%S",tlocal);
    tabla_mbr.mbr_disk_signature = numero;
    tabla_mbr.mbr_partition_1 = datos_primaria;
    tabla_mbr.mbr_partition_2 = datos_primaria;
    tabla_mbr.mbr_partition_3 = datos_primaria;
    tabla_mbr.mbr_partition_4 = datos_primaria;
    tabla_mbr.mbr_partition = datos_extend;
    int i;
    FILE *archivo;
    archivo = fopen(total,"rb+");
    if(archivo != NULL)
    {
        printf("El disco duro ya existe en el path escrito.\n\n");
        return;
    }
    archivo = fopen(total,"ab+");

    fwrite(&tabla_mbr,sizeof(MBR),1,archivo);



    for(i=0; i < cBytes; i++)
    {
        fwrite(&c,sizeof(char),1,archivo);
    }


    EscribirTabla(registro);
    fclose(archivo);
    printf("Partición con el nombre %s %d creada en %s.\n\n",nombre,numero,fichero);
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
{
    if(tamanio != -1 && strcmp(fichero,"\0") != 0 && strcmp(nombre,"\0") != 0)
    {
        ComillasFichero();
        ComillasNombre();
        char total[600];
        memset(total,0,600);
        int cBytes = tamanio;

        switch(unidad)
        {
            case 'B': cBytes = tamanio * 1;
            break;
            case 'M': cBytes = tamanio * 1024 * 1024;
            break;
            default: cBytes = tamanio * 1024;
            break;
        }

    if(tipo == 'E')
    {}
    else if(tipo == 'L')
    {}
    else
    {
            FILE *Validar = fopen(fichero,"rb");
            if(Validar == NULL)
            {printf("El path indicado no es correcto.\n\n"); return;}
            fclose(Validar);

            int nombreExistente = 0, part1 = 0, part2 = 0, part3 = 0, part4 = 0;
            MBR disco;
            disco = returnMBR(fichero);
            int totalParticiones = 0;
            if(disco.mbr_partition_1.part_status == 'a')
            {
                totalParticiones += disco.mbr_partition_1.part_size; part1 = 1;
                if(strcmp(disco.mbr_partition_1.part_name,nombre) == 0) { nombreExistente = 1; }
            }
            if(disco.mbr_partition_2.part_status == 'a')
            {
                totalParticiones += disco.mbr_partition_2.part_size; part2 = 1;
                if(strcmp(disco.mbr_partition_2.part_name,nombre) == 0) { nombreExistente = 1; }
            }
            if(disco.mbr_partition_3.part_status == 'a')
            {
                totalParticiones += disco.mbr_partition_3.part_size; part3 = 1;
                if(strcmp(disco.mbr_partition_3.part_name,nombre) == 0) { nombreExistente = 1; }
            }
            if(disco.mbr_partition_4.part_status == 'a')
            {
                totalParticiones += disco.mbr_partition_4.part_size; part4 = 1;
                if(strcmp(disco.mbr_partition_4.part_name,nombre) == 0) { nombreExistente = 1; }
            }

            totalParticiones = disco.mbr_tamanio - totalParticiones;
            //totalParticiones = totalParticiones - cBytes;

            if(totalParticiones > cBytes)
            {

                part_primaria particioP;
                particioP.part_status = 'a';
                particioP.part_type = 'P';
                particioP.part_size = cBytes;

                if(strcmp(ajustefit,"WF") == 0)
                {}
                else if(strcmp(ajustefit,"BF") == 0)
                {}
                else
                {
                    particioP.part_start = 0;
                    strcpy(particioP.part_fit,"FF");
                }




                if(nombreExistente != 1)
                {

                    strcpy(particioP.part_name,nombre);
                    if(part1 == 0)
                    {
                        disco.mbr_partition_1 = particioP;
                    }
                    else if(part2 == 0)
                    {
                        disco.mbr_partition_2 = particioP;
                    }
                    else if(part3 == 0)
                    {
                        disco.mbr_partition_3 = particioP;
                    }
                    else if(part4 == 0)
                    {
                        disco.mbr_partition_4 = particioP;
                    }
                    else
                    {
                        printf("Ya no se pueden crear más particiones primarias.\n\n");
                        return;
                    }
                    reemplazoMBR(fichero,disco);
                    printf("Particion creada exitosamente.\n\n");
                }
                else
                {
                    printf("El nombre de la partición ya existe en este disco duro.\n\n");
                }
            }
            else
            {
                printf("El tamanio de la partición a crear sobrepasa el espacio del disco duro.\n\n");
            }

    }

    }
    else
    {
        printf("Faltan parámetros para crear una partición.\n\n");
    }
}

void fdisk_eliminar()
{
    ComillasFichero();
    ComillasNombre();
    if(strcmp(tEliminacion,"\0") != 0 && strcmp(fichero,"\0") != 0 && strcmp(nombre,"\0") != 0)
    {
        MBR disco = returnMBR(fichero);

        if(strcmp(tEliminacion,"Full"))
        {
            if(strcasecmp(disco.mbr_partition_1.part_name,nombre) == 0)
            {
                disco.mbr_partition_1.part_status = 'i'; memset(disco.mbr_partition_1.part_fit,0,10);
                disco.mbr_partition_1.part_size = 0; disco.mbr_partition_1.part_start = 0;
                disco.mbr_partition_1.part_type = '\0'; memset(disco.mbr_partition_1.part_name,0,16);
            }
            else if(strcasecmp(disco.mbr_partition_2.part_name,nombre) == 0)
            {
                disco.mbr_partition_2.part_status = 'i'; memset(disco.mbr_partition_2.part_fit,0,10);
                disco.mbr_partition_2.part_size = 0; disco.mbr_partition_2.part_start = 0;
                disco.mbr_partition_2.part_type = '\0'; memset(disco.mbr_partition_2.part_name,0,16);
            }
            else if(strcasecmp(disco.mbr_partition_3.part_name,nombre) == 0)
            {
                disco.mbr_partition_3.part_status = 'i'; memset(disco.mbr_partition_3.part_fit,0,10);
                disco.mbr_partition_3.part_size = 0; disco.mbr_partition_3.part_start = 0;
                disco.mbr_partition_3.part_type = '\0'; memset(disco.mbr_partition_3.part_name,0,16);
            }
            else if(strcasecmp(disco.mbr_partition_4.part_name,nombre) == 0)
            {
                disco.mbr_partition_4.part_status = 'i'; memset(disco.mbr_partition_4.part_fit,0,10);
                disco.mbr_partition_4.part_size = 0; disco.mbr_partition_4.part_start = 0;
                disco.mbr_partition_4.part_type = '\0'; memset(disco.mbr_partition_4.part_name,0,16);
            }
            else
            {
                printf("El nombre de la partición a eliminar no existe.")
            }
            reemplazoMBR(fichero,disco);
            printf("Se elimino la partición %s en modo Full.",nombre);
        }
        else
        {
            if(strcasecmp(disco.mbr_partition_1.part_name,nombre) == 0)
            { disco.mbr_partition_1.part_status = 'i'; }
            else if(strcasecmp(disco.mbr_partition_2.part_name,nombre) == 0)
            { disco.mbr_partition_2.part_status = 'i'; }
            else if(strcasecmp(disco.mbr_partition_3.part_name,nombre) == 0)
            { disco.mbr_partition_3.part_status = 'i';  }
            else if(strcasecmp(disco.mbr_partition_4.part_name,nombre) == 0)
            { disco.mbr_partition_4.part_status = 'i';  }
            else
            {
                printf("El nombre de la partición a eliminar no existe.")
            }
            reemplazoMBR(fichero,disco);
            printf("Se elimino la partición %s en modo Fast.",nombre);
        }
    }
    else
    {
        printf("Faltan parámetros para eliminar una partición.\n\n");
    }
}

void fdisk_agregar()
{}

void comando_mount()
{
    ComillasFichero();
    ComillasNombre();
    MBR auxiliar;
    TablaMount regMont;
    FILE *Disco;
    Disco = fopen(fichero,"rb");
    int ExisteParticion = 0;
    if(Disco == NULL)
    { printf("El path es incorrecto.\n\n"); return; }
    fclose(Disco);
    auxiliar = returnMBR(fichero);
    Disco = fopen("Tabla_Particiones.bin","ab+");

    if(strcmp(auxiliar.mbr_partition_1.part_name,nombre) == 0 && auxiliar.mbr_partition_1.part_status == 'a'){ ExisteParticion = 1; }
    else if(strcmp(auxiliar.mbr_partition_2.part_name,nombre) == 0 && auxiliar.mbr_partition_2.part_status == 'a'){ ExisteParticion = 1; }
    else if(strcmp(auxiliar.mbr_partition_3.part_name,nombre) == 0 && auxiliar.mbr_partition_3.part_status == 'a'){ ExisteParticion = 1; }
    else if(strcmp(auxiliar.mbr_partition_4.part_name,nombre) == 0 && auxiliar.mbr_partition_4.part_status == 'a'){ ExisteParticion = 1; }

    if(ExisteParticion == 0)
    { printf("El nombre de la partición a montar no existe.\n\n"); return; }
    else
    {
        char id[10];
        int cantidad = CantParticiones(), letra = auxiliar.mbr_disk_signature;
        char cLetra = (letra + 96);
        sprintf(id,"vd%c%d",cLetra,cantidad);
        regMont.activo = 1;
        strcpy(regMont.path,fichero);
        strcpy(regMont.nombre,nombre);
        strcpy(regMont.id,id);
        fwrite(&regMont,sizeof(TablaMount),1,Disco);
        printf("La partición %s con id %s ha sido montada en el sistema.\n\n",nombre,id);
    }

    fclose(Disco);
}

void comando_umount()
{
    int pos = 0;
    if(strcmp(cadId,"\0") != 0)
    {
        ComillasCadId();
        FILE *Registro;
        int exito = 0;
        TablaMount auxiliar;
        Registro = fopen("Tabla_Particiones.bin","rb");
        if(Registro == NULL)
        { printf("No hay particiones montadas.\n\n"); return;}

        fread(&auxiliar, sizeof(TablaMount),1,Registro);
        while(!feof(Registro))
        {
            pos++;
            if(strcmp(auxiliar.id,cadId) == 0)
            {
                exito = 1;
                break;
            }
        fread(&auxiliar, sizeof(TablaMount),1,Registro); exito = 0;
        }
    fclose(Registro);

        if(exito == 1)
        {
            if(auxiliar.activo == 1)
            {
                FILE *modificacion;
                auxiliar.activo = 0;
                modificacion = fopen("Tabla_Particiones.bin","r+b");
                fseek(modificacion,0,SEEK_SET);
                pos--;
                fseek(modificacion,pos*sizeof(TablaMount),SEEK_SET);
                fwrite(&auxiliar,sizeof(TablaMount),1,modificacion);
                fclose(modificacion);

                printf("Particion desmontada exitosamente.\n\n");
            }
            else
            {
                printf("Esta partición ya se encuentra desmontada.\n\n");
            }
        }
        else
        {
            printf("No existe el id de la partición indicada.\n\n");
        }
    }
    else
    {
        printf("Por lo menos debe indicar un parámetro.\n\n");
    }
}

void reportes()
{
ComillasFichero();
ComillasCadId();

    if(strcmp(tReport,"mbr") == 0)
    {
        reporte_mbr();
    }
    else if(strcmp(tReport,"disk") == 0)
    {
        reporte_disk();
    }
    else
    {
        printf("Tipo de reporte no identificado.\n\n");
    }
}

void reporte_mbr()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    FILE *Registro;
    TablaMount auxiliar;
    Registro = fopen("Tabla_Particiones.bin","rb");
    if(Registro == NULL)
    { return;}

    fread(&auxiliar, sizeof(TablaMount),1,Registro);
    while(!feof(Registro))
    {
        if(strcmp(auxiliar.id,cadId) == 0)
        {
            break;
        }
        fread(&auxiliar, sizeof(TablaMount),1,Registro);
    }
    fclose(Registro);

    MBR disco = returnMBR(auxiliar.path);

/////////////////////////////////////////////////////////////////////////7
    char hola[9999];
    FILE *repMBR;
    remove("mbr.dot");
    repMBR = fopen("mbr.dot","a");
    strcpy(hola,"digraph G { node[shape=box] a0 [label=< <TABLE BORDER = \"1\" CELLBORDER=\"1\" CELLSPACING = \"1\"> \n");
    fprintf(repMBR,hola);
    memset(hola,0,9999);

    strcpy(hola,"<TR><TD>Nombre</TD><TD>Valor</TD></TR>\n");
    fprintf(repMBR,hola);
    memset(hola,0,9999);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
        sprintf(hola,"<TR><TD>mbr_tamanio</TD><TD>%d</TD></TR>\n <TR><TD>mbr_fecha_creacion</TD><TD>%s</TD></TR>\n ",disco.mbr_tamanio,disco.mbr_fecha_creacion);
        fprintf(repMBR,hola);
        memset(hola,0,9999);

        sprintf(hola,"<TR><TD>mbr_signature</TD><TD>%d</TD></TR>\n",disco.mbr_disk_signature);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(disco.mbr_partition_1.part_status == 'a')
    {
        sprintf(hola,"<TR><TD>part_status_1</TD><TD>%c</TD></TR>\n <TR><TD>part_type_1</TD><TD>%c</TD></TR>\n",disco.mbr_partition_1.part_status, disco.mbr_partition_1.part_type);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_fit_1</TD><TD>%s</TD></TR>\n <TR><TD>part_start_1</TD><TD>%d</TD></TR>\n",disco.mbr_partition_1.part_fit, disco.mbr_partition_1.part_start);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_size_1</TD><TD>%d</TD></TR>\n <TR><TD>part_name_1</TD><TD>%s</TD></TR>\n",disco.mbr_partition_1.part_size, disco.mbr_partition_1.part_name);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
    }


    if(disco.mbr_partition_2.part_status == 'a')
    {
        sprintf(hola,"<TR><TD>part_status_2</TD><TD>%c</TD></TR>\n <TR><TD>part_type_2</TD><TD>%c</TD></TR>\n",disco.mbr_partition_2.part_status, disco.mbr_partition_2.part_type);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_fit_2</TD><TD>%s</TD></TR>\n <TR><TD>part_start_2</TD><TD>%d</TD></TR>\n",disco.mbr_partition_2.part_fit, disco.mbr_partition_2.part_start);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_size_2</TD><TD>%d</TD></TR>\n <TR><TD>part_name_2</TD><TD>%s</TD></TR>\n",disco.mbr_partition_2.part_size, disco.mbr_partition_2.part_name);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
    }

    if(disco.mbr_partition_3.part_status == 'a')
    {
         sprintf(hola,"<TR><TD>part_status_3</TD><TD>%c</TD></TR>\n <TR><TD>part_type_3</TD><TD>%c</TD></TR>\n",disco.mbr_partition_3.part_status, disco.mbr_partition_3.part_type);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_fit_3</TD><TD>%s</TD></TR>\n <TR><TD>part_start_3</TD><TD>%d</TD></TR>\n",disco.mbr_partition_3.part_fit, disco.mbr_partition_3.part_start);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_size_3</TD><TD>%d</TD></TR>\n <TR><TD>part_name_3</TD><TD>%s</TD></TR>\n",disco.mbr_partition_3.part_size, disco.mbr_partition_3.part_name);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
    }

    if(disco.mbr_partition_4.part_status == 'a')
    {
       sprintf(hola,"<TR><TD>part_status_4</TD><TD>%c</TD></TR>\n <TR><TD>part_type_4</TD><TD>%c</TD></TR>\n",disco.mbr_partition_4.part_status, disco.mbr_partition_4.part_type);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_fit_4</TD><TD>%s</TD></TR>\n <TR><TD>part_start_4</TD><TD>%d</TD></TR>\n",disco.mbr_partition_4.part_fit, disco.mbr_partition_4.part_start);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
        sprintf(hola,"<TR><TD>part_size_4</TD><TD>%d</TD></TR>\n <TR><TD>part_name_4</TD><TD>%s</TD></TR>\n",disco.mbr_partition_4.part_size, disco.mbr_partition_4.part_name);
        fprintf(repMBR,hola);
        memset(hola,0,9999);
    }


    strcpy(hola," </TABLE>>]; } ");
    fprintf(repMBR,hola);
    memset(hola,0,9999);


    fclose(repMBR);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s mbr.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_disk()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    FILE *Registro;
    TablaMount auxiliar;
    Registro = fopen("Tabla_Particiones.bin","rb");
    if(Registro == NULL)
    { return;}

    fread(&auxiliar, sizeof(TablaMount),1,Registro);
    while(!feof(Registro))
    {
        if(strcmp(auxiliar.id,cadId) == 0)
        {
            break;
        }
        fread(&auxiliar, sizeof(TablaMount),1,Registro);
    }
    fclose(Registro);

    MBR disco = returnMBR(auxiliar.path);
    //////////////////////////////////////////////////////////////////////
    char hola[9999];
    FILE *repMBR;
    remove("disk.dot");
    repMBR = fopen("disk.dot","a");
    strcpy(hola,"digraph G { node[shape=box] a0 [label=< <TABLE BORDER = \"1\" CELLBORDER=\"1\" CELLSPACING = \"1\"> \n <TR>");
    fprintf(repMBR,hola);
    memset(hola,0,9999);
    /////////////////////////////////////////////////////////////////////

    strcpy(hola,"<TD>   MBR   </TD>"); fprintf(repMBR,hola); memset(hola,0,9999); int particiones = 1;
    if(disco.mbr_partition_1.part_status == 'a')
    {
        memset(hola,0,9999); strcpy(hola,"<TD>     Primaria     </TD>"); fprintf(repMBR,hola); memset(hola,0,9999);
    }
    else
    {
        strcpy(hola,"<TD>     Libre      </TD>");
        int seguir = 0;
        if(disco.mbr_partition_2.part_status == 'i')
        {
            memset(hola,0,9999); seguir = 1;
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
        }
        else
        { memset(hola,0,9999); strcpy(hola,"<TD>     Libre      </TD>"); fprintf(repMBR,hola); seguir = 0;}

        if(disco.mbr_partition_3.part_status == 'i' && seguir == 1)
        {
            memset(hola,0,9999);
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
        }else if(seguir == 1)
        { fprintf(repMBR,hola); seguir = 0;}
        if(disco.mbr_partition_4.part_status == 'i' && seguir == 1)
        {
            memset(hola,0,9999);
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
            printf(repMBR,hola);
        }else if(seguir == 1)
        {  fprintf(repMBR,hola); seguir = 0;}
    }

    if(disco.mbr_partition_2.part_status == 'a')
    {
        memset(hola,0,9999); strcpy(hola,"<TD>     Primaria     </TD>"); fprintf(repMBR,hola);
    }
    else
    {
        strcpy(hola,"<TD>     Libre      </TD>");
        int seguir = 0;
        if(disco.mbr_partition_3.part_status == 'i')
        {
            memset(hola,0,9999); seguir = 1;
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
        }
        else
        { memset(hola,0,9999); strcpy(hola,"<TD>     Libre      </TD>"); fprintf(repMBR,hola); seguir = 0;}

        if(disco.mbr_partition_4.part_status == 'i' && seguir == 1)
        {
            memset(hola,0,9999);
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
            printf(repMBR,hola);
        }else if(seguir == 1)
        { fprintf(repMBR,hola); seguir = 0;}

    }

    if(disco.mbr_partition_3.part_status == 'a')
    {
        memset(hola,0,9999); strcpy(hola,"<TD>     Primaria     </TD>"); fprintf(repMBR,hola); memset(hola,0,9999);
    }
    else
    {
        strcpy(hola,"<TD>     Libre      </TD>");
        int seguir = 0;
        if(disco.mbr_partition_4.part_status == 'i')
        {
            memset(hola,0,9999); seguir = 1;
            particiones++;
            sprintf(hola,"<TD rowspan=\"%d\">       Libre       </TD>",particiones);
            printf(repMBR,hola);
        }
        else
        { memset(hola,0,9999); strcpy(hola,"<TD>     Libre      </TD>"); fprintf(repMBR,hola); seguir = 0;}
    }

    if(disco.mbr_partition_4.part_status == 'a')
    {
        memset(hola,0,9999); strcpy(hola,"<TD>     Primaria     </TD>"); fprintf(repMBR,hola); memset(hola,0,9999);
    }
    else
    {memset(hola,0,9999); strcpy(hola,"<TD>     Libre      </TD>"); fprintf(repMBR,hola); memset(hola,0,9999);}

    //////////////////////////////////////////////////////////////////////
    strcpy(hola," </TR> </TABLE>>]; } ");
    fprintf(repMBR,hola);
    memset(hola,0,9999);

    //////////////////////////////////////////////////////////////////////
    fclose(repMBR);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s disk.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

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

