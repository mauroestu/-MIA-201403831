INODO NuevoInodo(int Link, int UserId, int GruId, int Size, int Permiso, int Type, char path[],
char atime[], char ctime[], char mtime[])
{
    INODO rInodo;

    rInodo.i_nlink = Link;
    strcpy(rInodo.i_pathlink,path);
    rInodo.i_uid = UserId;
    rInodo.i_gid = GruId;
    rInodo.i_size = Size;
    strcpy(rInodo.i_atime, atime);
    strcpy(rInodo.i_ctime, ctime);
    strcpy(rInodo.i_mtime, mtime);
    rInodo.i_perm = Permiso;
    rInodo.i_type = Type;
    int i;
    for(i = 0; i <15; i++)
    {
        rInodo.i_block[i] = -1;
    }

    return rInodo;
}

BLOQUE_CARPETA NuevoBloqueCarpeta(int bloque, char nombre[])
{
    BLOQUE_CARPETA rCarpeta;

    rCarpeta.n_bloque = bloque;
    strcpy(rCarpeta.b_name, nombre);
    rCarpeta.content[0] = -1;
    rCarpeta.content[1] = -1;
    rCarpeta.content[2] = -1;
    rCarpeta.content[3] = -1;

    return rCarpeta;
}

EXT ObtencionExt(char id[])
{
    EXT sistema;
    char total[20] = "lista_"; strcat(total,id); strcat(total,".bin");
    FILE *archivo = fopen(total,"r+b");
    fseek(archivo,0,SEEK_SET);
    fread(&sistema,sizeof(archivo),1,archivo);
    fclose(archivo);

    return sistema;
}

void EscribirStruct(EXT sistema, char id[])
{
    char total[20] = "lista_"; strcat(total,id); strcat(total,".bin");
    FILE *archivo;
    archivo = fopen(total,"ab+");
    fseek(archivo,0,SEEK_SET);
    fwrite(&total,sizeof(sistema),1,archivo);
    fclose(archivo);
}


JOURNALING NuevoJournal(int tipo_operacion, int tipo_archivo, char nombre[], char contenido[], char fecha[],
char propietario[], int permisos)
{
    JOURNALING rJournal;

    rJournal.tipo_operacion = tipo_operacion;
    rJournal.tipo_archivo = tipo_archivo;
    strcpy(rJournal.nombre,nombre);
    strcpy(rJournal.contenido,contenido);
    strcpy(rJournal.fecha,fecha);
    strcpy(rJournal.propietario,propietario);
    rJournal.permisos = permisos;

    return rJournal;
}

BLOQUE_ARCHIVO NuevoBloqueArchivo(int bloque, char contenido[])
{
    BLOQUE_ARCHIVO rArchivo;
    rArchivo.n_bloque = bloque;
    int i, contador = 0;
    strcpy(rArchivo.b_content,contenido);

    return rArchivo;
}

BLOQUE_APUNTADOR NuevoBloqueApuntador(int bloque)
{
    BLOQUE_APUNTADOR rApuntador;

    rApuntador.n_bloque = bloque;
    int i;
    for(i = 0; i < 16; i++)
    {
        rApuntador.b_pointers[i] = -1;
    }

    return rApuntador;
}

EXT InsertarRaiz(SUPER_BLOQUE spBloque, char DatosUsuario[])
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
    EXT sAuxiliar;
    int pos_ino = RetornarPosicion(spBloque.bit_i);
    int pos_blo = RetornarPosicion(spBloque.bit_b);
    ModificarBitMap(spBloque.bit_i,pos_ino);
    spBloque.s_first_ino = RetornarPosicion(spBloque.bit_i);
    ModificarBitMap(spBloque.bit_b,pos_blo);
    spBloque.s_first_blo = RetornarPosicion(spBloque.bit_b);

    LISTA_INODOS *cInodo = NULL; LISTA_BLOQUES *cBloque = NULL; LISTA_JOURNAL *cJournal = NULL;
    INODO nInodo; BLOQUE_CARPETA nCarpeta; BLOQUE_APUNTADOR nApuntador; BLOQUE_ARCHIVO nArchivo;
    JOURNALING nJournal;

    nInodo = NuevoInodo(pos_ino,1,1,-1,777,1,"/",Time,Time,Time);
    nInodo.i_block[0] = pos_blo;
    nCarpeta = NuevoBloqueCarpeta(pos_blo,"/");
    nJournal = NuevoJournal(1,1,"/","\0",Time,"root",777); //1=crear 2=editar 3=eliminar
    ////////////////////////////////////////////////////////
    pos_ino = RetornarPosicion(spBloque.bit_i);
    pos_blo = RetornarPosicion(spBloque.bit_b);
    ModificarBitMap(spBloque.bit_i,pos_ino);
    spBloque.s_first_ino = RetornarPosicion(spBloque.bit_i);
    ModificarBitMap(spBloque.bit_b,pos_blo);
    spBloque.s_first_blo = RetornarPosicion(spBloque.bit_b);
    spBloque.s_free_blocks_count--; spBloque.s_free_blocks_count--;
    spBloque.s_free_inodes_count--; spBloque.s_free_inodes_count--;
    /////////////////////////////////////////////////////////
    nCarpeta.content[0] = pos_ino;
    cInodo = InsertInodo(cInodo,nInodo);
    cBloque = InsertBloque(cBloque,1,nCarpeta,nApuntador,nArchivo);
    cJournal = InsertJournal(cJournal,nJournal);


    nInodo = NuevoInodo(pos_ino,1,1,52,777,0,"/user.txt",Time,Time,Time);
    nInodo.i_block[0] = pos_blo;
    nArchivo = NuevoBloqueArchivo(pos_blo,DatosUsuario);
    nJournal = NuevoJournal(1,0,"/usert.txt",DatosUsuario,Time,"root",777);

    cInodo = InsertInodo(cInodo,nInodo);
    cBloque = InsertBloque(cBloque,0,nCarpeta,nApuntador,nArchivo);
    cJournal = InsertJournal(cJournal,nJournal);

    sAuxiliar.s_bloque = spBloque; //Inserción del superbloque;
    sAuxiliar.inodos = cInodo; //Inserción inodos
    sAuxiliar.bloques = cBloque; //Inserción bloques
    sAuxiliar.journal = cJournal; //Inserción journal
    return sAuxiliar;
}

void formateo(int posicion, int tamaPart, int tSistema, MBR disco, TablaMount auxiliar, char pIdM[])
{
    int totalInodos = 0;
    totalInodos = (tamaPart - sizeof(SUPER_BLOQUE)) / ((sizeof(LISTA_INODOS) + 4) + (3*sizeof(LISTA_BLOQUES)));
    int totalBloques = 3*totalInodos;

    MATRIZ *Mbloques = NULL;
    MATRIZ *Minodos = NULL;
    int i;
    for(i = 1; i <= totalInodos; i++) Minodos = InsertCarac(Minodos,'0');
    for(i = 1; i <= totalBloques; i++) Mbloques = InsertCarac(Mbloques,'0');

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    EXT sistema_ext23;
    SUPER_BLOQUE spBloque;
    spBloque.formateado = 0;
    spBloque.s_filesystem_type = tSistema;
    spBloque.s_inodes_count = totalInodos;
    spBloque.s_blocks_count = totalBloques;
    spBloque.s_free_blocks_count = totalBloques;
    spBloque.s_free_inodes_count = totalInodos;
    strcpy(spBloque.s_magic,"0xEF53");
    spBloque.s_inode_size = 128;
    spBloque.s_block_size = 64;
    spBloque.s_first_ino = 1;
    spBloque.s_first_blo = 1;
    spBloque.s_mnt_count = 1;
    strftime(spBloque.s_mtime,15,"%d/%m/%y %H:%M:%S",tlocal);
    strftime(spBloque.s_mtime,15,"%d/%m/%y %H:%M:%S",tlocal);
    spBloque.bit_b = Mbloques;
    spBloque.bit_i = Minodos;

    /////////////////////////////////////////////////////
    char DatosUsuario[64] = "1,G,root      \n";
    strcat(DatosUsuario,"1,U,root      ,root      ,201403831 \n");
    char grupo[15] = "gru_"; strcat(grupo,pIdM); strcat(grupo,".txt");
    char usuario[15] = "user_"; strcat(usuario,pIdM); strcat(usuario,".txt");
    FILE *Archivo = fopen(grupo,"a+");
    fprintf(Archivo,"1,G,root\n"); fclose(Archivo);
    Archivo = fopen(usuario,"a+");
    fprintf(Archivo,"1,U,root,root,201403831\n"); fclose(Archivo);
    //////////////////////////////////////////////////////

    sistema_ext23 = InsertarRaiz(spBloque,DatosUsuario);
    //EscribirStruct(sistema_ext23,pIdM);
    //sprueba = sistema_ext23;
    asigPrueba(sistema_ext23,auxiliar.id);
    Archivo = fopen(auxiliar.path,"r+b");
    fseek(Archivo,posicion,SEEK_SET);
    fwrite(&sistema_ext23, sizeof(sistema_ext23),1,Archivo);
    fclose(Archivo);
    printf("El disco %s ha sido formateado \n\n",auxiliar.path);
}

void comando_mkfs()
{
    ComillasCadId();
    ComillasFichero();
    if(strcmp(fichero,"2fs") == 0 || strcmp(fichero,"3fs") == 0 || strcmp(fichero,"\0") == 0)
    {
        int tSistema = 0;
        if(strcmp(fichero,"3fs") == 0) tSistema = 2;
        else tSistema = 1;

        if(strcmp(tFormateo,"Fast") == 0 || strcmp(tFormateo,"Full") == 0 || strcmp(tFormateo,"\0") == 0)
        {
            if(tamanio == -1)
            {
                char Directorio[500];
                TablaMount auxiliar;
                FILE *Registro;
                Registro = fopen("Tabla_Particiones.bin","rb");
                if(Registro == NULL) return;

                fread(&auxiliar, sizeof(TablaMount),1,Registro);
                while(!feof(Registro))
                {
                    if(strcmp(auxiliar.id,cadId) == 0 && auxiliar.activo == 1) { break; }
                    fread(&auxiliar, sizeof(TablaMount),1,Registro);
                }
                fclose(Registro);

                MBR disco = returnMBR(auxiliar.path);

                int posicion = 0, tamaPart = 0;

                if(strcmp(disco.mbr_partition_1.part_name,auxiliar.nombre) == 0)
                {
                    posicion = disco.mbr_partition_1.part_start; tamaPart = disco.mbr_partition_1.part_size;
               }
                else if(strcmp(disco.mbr_partition_2.part_name,auxiliar.nombre) == 0)
                {
                    posicion = disco.mbr_partition_2.part_start; tamaPart = disco.mbr_partition_2.part_size;
                }
                else if(strcmp(disco.mbr_partition_3.part_name,auxiliar.nombre) == 0)
                {
                    posicion = disco.mbr_partition_3.part_start; tamaPart = disco.mbr_partition_3.part_size;
                }
                else if(strcmp(disco.mbr_partition_4.part_name,auxiliar.nombre) == 0)
                {
                    posicion = disco.mbr_partition_4.part_start; tamaPart = disco.mbr_partition_4.part_size;
                }
                else
                { printf("Partición no formateada.\n\n"); return; }

                formateo(posicion,tamaPart,tSistema,disco,auxiliar,cadId);
            }
            else
            {
                //Parar agregar mamadas
            }
        }
    }
    else
    {
        printf("Sistema de archivos a aplicar inválido.\n\n");
        return;
    }
}

int VerificarUsuario(char id[])
{
    int exito = 0, conta = 0, palabra = 0, i; char tUser[20]; char linea[50];
    char usuario[20] = "user_"; strcat(usuario,id); strcat(usuario,".txt");
    FILE *Registro = fopen(usuario,"r");
    if(Registro == NULL) return 0;
    fscanf(Registro,"%s",&linea);
    while(!feof(Registro))
    {
        for(i = 0; i <= strlen(linea); i++)
        {
            if(linea[i] == ',') { conta = 0; i++; palabra++;}

            switch(palabra)
            {
                case 3:
                    tUser[conta] = linea[i];
                    conta++;
                    if(linea[i+1]==','){tUser[conta]='\0';}
                break;
            }
        }
        palabra = 0;
        if(strcmp(session.usuario,tUser) == 0)
        {exito = 1; break; }
        else fscanf(Registro,"%s",&linea);
    }
    fclose(Registro);

    return exito;
}

void ObtenerGrupo(char Idm[])
{
    char gru[20] = "gru_"; strcat(gru,Idm); strcat(gru,".txt"); char linea[15];
    int conta = 0, palabra = 0,i; char temp_grupo[10]; char tGruID[5];
    FILE *Registro = fopen(gru,"r");
    fscanf(Registro,"%s",&linea);
    while(!feof(Registro))
    {
        for(i = 0; i < strlen(linea);i++)
        {
            if(linea[i] == ',') {conta = 0; palabra++; i++;}
            else if(linea[i]=='\n' || linea[i]=='\0') {break;}
            switch(palabra)
            {
                case 0: tGruID[conta] = linea[i]; conta++;
                break;
                case 2: temp_grupo[conta] = linea[i];
                conta++;
                break;
            }
        }

        if(strcmp(session.grupo,temp_grupo) == 0)
        {
            strcpy(session.idGrupo,tGruID);
            break;
        }
    }
    fclose(Registro);
}

int Verificacion(char linea[], char Idm[])
{
    int exito = 0, conta = 0, palabra = 0, i; char tUser[20]; char tPass[20]; char tGrupo[20]; char tUserID[5];

    for(i = 0; i <= strlen(linea); i++)
    {
        if(linea[i] == ',') { conta = 0; i++; palabra++;}

        switch(palabra)
        {
            case 0:
                tUserID[conta] = linea[i];
                conta++;
            break;
            case 2:
                tGrupo[conta] = linea[i];
                conta++;
                if(linea[i+1]==','){tGrupo[conta]='\0';}
            break;
            case 3:
                tUser[conta] = linea[i];
                conta++;
            break;
            case 4:
                tPass[conta] = linea[i];
                conta++;
            break;
        }
    }

    if(strcmp(tUser,usuario) == 0 && strcmp(tPass,pass) == 0)
    {
        strcpy(session.usuario,usuario); strcpy(session.contra,pass); strcpy(session.grupo,tGrupo);
        strcpy(session.idUsuario,tUserID);
        ObtenerGrupo(Idm);
        exito = 1;
    }
    return exito;
}

void comando_login()
{
    ComillasUsuario(); ComillasPass();
    if(strcmp(session.usuario,"\0") == 0,strcmp(session.contra,"\0") == 0,strcmp(session.grupo,"\0") == 0)
    {
        TablaMount auxiliar;
        FILE *Registro = fopen("Tabla_Particiones.bin","rb");
        if(Registro == NULL) return;

        fread(&auxiliar, sizeof(TablaMount),1,Registro);
        while(!feof(Registro))
        {
            if(auxiliar.activo == 1) { break; }
            fread(&auxiliar, sizeof(TablaMount),1,Registro);
        }
        fclose(Registro);
        char usuario[15] = "user_"; strcat(usuario,auxiliar.id); strcat(usuario,".txt");
        char linea[50];
        Registro = fopen(usuario,"r");
        fscanf(Registro,"%s",&linea);
        int exito = 0;
        while(!feof(Registro))
        {
            exito = Verificacion(linea,auxiliar.id);
            if(exito == 1) break;
            else fscanf(Registro,"%s",&linea);
        }
        fclose(Registro);

        if(exito == 0) {printf("Credenciales incorrectas.\n\n");}
        else printf("Usuario: %s del Grupo: %s ha iniciado sesión.\n\n",session.usuario,session.grupo);
    }
    else
    {
        printf("Ya tiene iniciada una sesión en el sistema.\n\n");
    }
}

void comando_logout()
{
    if(strcmp(session.usuario,"\0") != 0)
    {
        printf("El usuario %s ha cerrado sesion\n\n",session.usuario);
        memset(session.usuario,0,20); memset(session.contra,0,20); memset(session.grupo,0,20);
    }
    else
    {
        printf("Primero debe iniciar sesion con algun usuario.\n\n");
    }
}


TablaMount rTabla(char pID[])
{
    TablaMount rMount;

    FILE* Registro = fopen("Tabla_Particiones.bin","rb");
    if(Registro == NULL) return;

    fread(&rMount, sizeof(TablaMount),1,Registro);
    while(!feof(Registro))
    {
        if(strcmp(rMount.id,pID) == 0 && rMount.activo == 1) { break; }
        fread(&rMount, sizeof(TablaMount),1,Registro);
    }
    fclose(Registro);

    return rMount;
}

void EscribirSistemaArchivos(MBR disco, TablaMount auxiliar, EXT sistema_ext)
{
    int posicion = 0;
    if(strcmp(disco.mbr_partition_1.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_1.part_start;
    else if(strcmp(disco.mbr_partition_2.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_2.part_start;
    else if(strcmp(disco.mbr_partition_3.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_3.part_start;
    else if(strcmp(disco.mbr_partition_4.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_4.part_start;

    FILE *Registro = fopen(auxiliar.path,"r+b");
    fseek(Registro,posicion,SEEK_SET);
    fwrite(&sistema_ext, sizeof(returnPrueba(auxiliar.id)),1,Registro);
    fclose(Registro);
}

EXT returnSistema(MBR disco, TablaMount auxiliar)
{
    EXT sistema_ext = returnPrueba(auxiliar.id);
    /*int posicion = 0;
    if(strcmp(disco.mbr_partition_1.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_1.part_start;
    else if(strcmp(disco.mbr_partition_2.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_2.part_start;
    else if(strcmp(disco.mbr_partition_3.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_3.part_start;
    else if(strcmp(disco.mbr_partition_4.part_name,auxiliar.nombre) == 0) posicion = disco.mbr_partition_4.part_start;

    FILE *Registro = fopen(auxiliar.path,"r+b");
    fseek(Registro,posicion,SEEK_SET);
    fread(&sistema_ext, sizeof(returnPrueba(auxiliar.id)),1,Registro);
    fclose(Registro);*/

    return sistema_ext;
}

void comando_tunefs()
{
    ComillasCadId();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        if(sistema_ext.s_bloque.s_filesystem_type == 1)
        {
            sistema_ext.s_bloque.s_filesystem_type = 2;
            asigPrueba(sistema_ext,cadId);
            EscribirSistemaArchivos(disco,auxiliar,sistema_ext);
            printf("El sistema de archivos ha sido formateado a ext3.\n\n");
        }
        else
        {
            printf("El sistema de archivos ya está en formato ext3.\n\n");
        }
    }
    else
    {
        printf("Debe iniciar sesion como usuario root.\n\n");
    }
}

void comando_loss()
{
    ComillasCadId();
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    if(sistema_ext.s_bloque.s_filesystem_type == 2)
    {
    sistema_ext.s_bloque.formateado = 1;
    asigPrueba(sistema_ext,auxiliar.id);
    Espera(); Espera(); Espera();
    Espera(); Espera(); Espera();
    printf("Sistema formateado totalmente.\n\n");
    }
    else
    { printf("El sistema no es ext3, al formatearlo no se recuperará.\n\n"); }
}

void comando_recovery()
{
    ComillasCadId();
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    if(sistema_ext.s_bloque.s_filesystem_type == 2)
    {
        sistema_ext.s_bloque.formateado = 0;
        asigPrueba(sistema_ext,auxiliar.id);
        Espera(); Espera(); Espera();
        Espera(); Espera(); Espera();
        printf("Sistema recuperado totalmente.\n\n");
    }
    else
    {
        printf("El sistemaa no es ext3 para aplicar el journaling.\n\n");
    }

}

int CantidadGrupos(char id[])
{
    int cantidad = 1; char linea[50];
    char usuario[20] = "gru_"; strcat(usuario,id); strcat(usuario,".txt");
    FILE *Registro = fopen(usuario,"r");
    fscanf(Registro,"%s",&linea);
    while(!feof(Registro))
    {
        cantidad++;
        fscanf(Registro,"%s",&linea);
    }

    return cantidad;
}

int CantidadUsuarios(char id[])
{
    int cantidad = 1; char linea[50];
    char usuario[20] = "user_"; strcat(usuario,id); strcat(usuario,".txt");
    FILE *Registro = fopen(usuario,"r");
    fscanf(Registro,"%s",&linea);
    while(!feof(Registro))
    {
        cantidad++;
        fscanf(Registro,"%s",&linea);
    }

    return cantidad;
}

int ObtenerTamanioCadena(char cad[])
{
    int tamanio = 0,i;
    for(i = 0; i < strlen(cad);i++)
    {
        if(cad[i]=='\0') break;
        tamanio++;
    }

    return tamanio;
}


char* sub_str(char* cadena, int comienzo, int longitud)
{
    if(longitud == 0) longitud = strlen(cadena) - comienzo -1;

    char *nuevo =(char *)malloc(sizeof(char) * longitud);

    strncpy(nuevo,cadena + comienzo, longitud);
    return nuevo;
}

char temporalGrupo[10];
char temporalPass[10];
char temporalId[5];

int VerificacionUsuario2(char grupo[], char cdId[])
{
    int existe = 0,i, palabra = 0, conta = 0;
    char temp_grupo[37]; char activo; char linea[37];
    memset(temp_grupo,0,37);
    char gru[20] = "user_"; strcat(gru,cdId); strcat(gru,".txt");
    FILE *Registro = fopen(gru,"r");
    fscanf(Registro,"%s",&linea);

    while(!feof(Registro))
    {
        for(i = 0; i < strlen(linea);i++)
        {
            if(linea[i] == ',') {conta = 0; palabra++; i++;}
            switch(palabra)
            {
                case 0: temporalId[conta] = linea[i];
                conta++;
                break;
                case 2: temporalGrupo[conta] = linea[i];
                conta++;
                break;
                case 3: temp_grupo[conta] = linea[i];
                conta++;
                break;
                case 4:
                temporalPass[conta] = linea[i];
                conta++;
                break;
            }
        }
        if(strcmp(temp_grupo,grupo) == 0 && strcmp(temporalId,"0") !=0)
        { existe = 1; break;}
        else
        {
        memset(temp_grupo,0,37); conta = 0; palabra = 0; memset(temp_grupo,0,10); memset(temporalPass,0,10);
        fscanf(Registro,"%s",&linea);
        }
    }
    fclose(Registro);

    return existe;
}

int VerificacionUsuario(char grupo[], char cdId[])
{
    int existe = 0,i, palabra = 0, conta = 0;
    char temp_grupo[37]; char activo; char linea[37];
    memset(temp_grupo,0,37);
    char gru[20] = "user_"; strcat(gru,cdId); strcat(gru,".txt");
    FILE *Registro = fopen(gru,"r");
    fscanf(Registro,"%s",&linea);

    while(!feof(Registro))
    {
        for(i = 0; i < strlen(linea);i++)
        {
            if(linea[i] == ',') {conta = 0; palabra++; i++;}
            switch(palabra)
            {
                case 0: activo = linea[i];
                break;
                case 2: temporalGrupo[conta] = linea[i];
                conta++;
                break;
                case 3: temp_grupo[conta] = linea[i];
                conta++;
                break;
                case 4:
                temporalPass[conta] = linea[i];
                conta++;
                break;
            }
        }
        if(strcmp(temp_grupo,grupo) == 0 && activo != '0')
        { existe = 1; break;}
        else
        {
        memset(temp_grupo,0,37); conta = 0; palabra = 0; memset(temp_grupo,0,10); memset(temporalPass,0,10);
        fscanf(Registro,"%s",&linea);
        }
    }
    fclose(Registro);

    return existe;
}

int VerificarGrupo(char grupo[], char cdId[])
{
    int existe = 0,i, palabra = 0, conta = 0;
    char temp_grupo[15]; char activo; char linea[15];
    memset(temp_grupo,0,15);
    char gru[20] = "gru_"; strcat(gru,cdId); strcat(gru,".txt");
    FILE *Registro = fopen(gru,"r");
    fscanf(Registro,"%s",&linea);
    while(!feof(Registro))
    {
        for(i = 0; i < strlen(linea);i++)
        {
            if(linea[i] == ',') {conta = 0; palabra++; i++;}
            else if(linea[i]=='\n' || linea[i]=='\0') {break;}
            switch(palabra)
            {
                case 0: activo = linea[i];
                break;
                case 2: temp_grupo[conta] = linea[i];
                conta++;
                break;
            }
        }

        if(strcmp(temp_grupo,grupo) == 0 && activo != '0')
        { existe = 1;}
        else
        {
        memset(temp_grupo,0,15); conta = 0; palabra = 0;
        fscanf(Registro,"%s",&linea);
        }
    }
    fclose(Registro);

    return existe;
}

EXT InsertArchivoUsers(EXT sistema_ext, char pathlink[], char linea_bloque[], int tamaCadena)
{
    EXT rSistema;
    INODO rInodo;
    BLOQUE_ARCHIVO aBloque;
    LISTA_INODOS *auxiliar;
    LISTA_BLOQUES *auxbloque;
    rSistema = sistema_ext;
    auxiliar = rSistema.inodos;
    auxbloque = rSistema.bloques;
    while(auxiliar!=NULL)
    {
        if(strcmp(auxiliar->i_nodo.i_pathlink,pathlink)==0)
        {
            rInodo = auxiliar->i_nodo;
            break;
        }
        auxiliar = auxiliar->siguiente;
    }
    rInodo.i_size = rInodo.i_size + tamaCadena;
    int i;
    for(i = 0; i < 15; i++) {
        if(rInodo.i_block[i] == -1) break;
    } i--;

    if(i < 12)
    {
        while(auxbloque!=NULL)
        {
            if(auxbloque->i_type == 0)
            {
                if(rInodo.i_block[i] == auxbloque->b_archivo.n_bloque)
                {
                    aBloque = auxbloque->b_archivo;
                    break;
                }
            }
            auxbloque = auxbloque->siguiente;
        }
        int TamanioCadena = ObtenerTamanioCadena(auxbloque->b_archivo.b_content);
        int posActual = 0;
        int Cantidad = 64 - TamanioCadena;
        if(Cantidad >=tamaCadena) strcat(auxbloque->b_archivo.b_content,linea_bloque);
        else
        {
            strcat(auxbloque->b_archivo.b_content,sub_str(linea_bloque,posActual,Cantidad));
            posActual = Cantidad - tamaCadena;
            posActual = tamaCadena - (posActual*(-1));
            i++;
            if(i < 12)
            {
                int pos_blo = RetornarPosicion(rSistema.s_bloque.bit_b);
                ModificarBitMap(rSistema.s_bloque.bit_b,pos_blo);
                rSistema.s_bloque.s_first_blo = RetornarPosicion(rSistema.s_bloque.bit_b);
                rSistema.s_bloque.s_free_blocks_count--;
                rInodo.i_block[i] = pos_blo;
                rSistema.inodos = ModificarInodo(rSistema.inodos,rInodo,"/user.txt");
                auxbloque = NULL; auxbloque = rSistema.bloques;
                BLOQUE_CARPETA bCarpeta; BLOQUE_APUNTADOR bApun; BLOQUE_ARCHIVO bArchi;

                bArchi = NuevoBloqueArchivo(pos_blo,sub_str(linea_bloque,posActual,strlen(linea_bloque)));

                auxbloque = InsertBloque(auxbloque,0,bCarpeta,bApun,bArchi);

                rSistema.bloques = auxbloque;
            }
            else
            {
                //Bloque apuntador
            }
        }
    }
    else
    {
        //Bloque apuntador
    }

    return rSistema;
}

void comando_mkgrp()
{
    ComillasCadId(); ComillasNombre();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar; int Cantidad = 0;
        MBR disco;
        EXT sistema_ext, aux_sistema; INODO i_nodo;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        aux_sistema = sistema_ext;
        Cantidad = CantidadGrupos(cadId);
        int existe = VerificarGrupo(nombre, cadId);
        if(CantLetras(nombre) == 1 && existe == 0)
        {
            int i;
            char usuario[20] = "gru_"; char linea_archivo[15]; char linea_bloque[15]; strcat(usuario,cadId); strcat(usuario,".txt");
            FILE *Archivo = fopen(usuario,"a+");
            sprintf(linea_archivo,"%d,G,%s",Cantidad,nombre);
            strcpy(linea_bloque,linea_archivo);
            strcat(linea_archivo,"\n");
            fprintf(Archivo,linea_archivo);
            fclose(Archivo);
            Cantidad = 10 - strlen(nombre);
            for(i = 0; i<Cantidad; i++) strcat(linea_bloque," ");
            strcat(linea_bloque,"\n");
            ///////////////////////////////////////////////

            sistema_ext = InsertArchivoUsers(aux_sistema,"/user.txt",linea_bloque,15);
            /***************************************/
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char timeJour[15];
            strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
            JOURNALING rJour = NuevoJournal(1,0,"/user.txt",linea_bloque,timeJour,"root",777);
            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
            asigPrueba(sistema_ext,cadId);
            /***************************************/

           /* LISTA_BLOQUES *BloqueAuxiliar;
            BloqueAuxiliar = sistema_ext.bloques;

            while(BloqueAuxiliar!=NULL)
            {
                printf("%d\n",BloqueAuxiliar->i_type);
                BloqueAuxiliar=BloqueAuxiliar->siguiente;
            }*/



            ///////////////////////////////////////////////
            printf("Grupo \"%s\" creado con exito.\n\n",nombre);
        }
        else if(existe == 1)
        {
            printf("El nombre del grupo a crear ya existe.\n\n");
        }
        else
        {
            printf("El nombre del grupo a crear debe ser menor o igual a 10 letras.\n\n");
        }
    }
    else
    {
        printf("Debe iniciar sesion como usuario root.\n\n");
    }

}

void comando_rmgrp()
{
    ComillasCadId(); ComillasNombre();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        int existe = VerificarGrupo(nombre,cadId);
        if(existe == 1)
        {
            char lineaJournal[15];
            char lineaAux[15]; int nGrupo = 1; char linea[15]; memset(lineaAux,0,15); memset(lineaAux,0,15);
            char gru[15] = "gru_"; strcat(gru,cadId); strcat(gru,".txt");
            char auxgru[15] = "auxgru_"; strcat(auxgru,cadId); strcat(auxgru,".txt");
            FILE *infile; FILE *outfile;
            infile = fopen(gru,"r"); outfile = fopen(auxgru,"a+");

            fscanf(infile,"%s",&linea);
            while(!feof(infile))
            {
                sprintf(lineaAux,"%d,G,",nGrupo); strcat(lineaAux,nombre);
                if(strcmp(lineaAux,linea) == 0)
                {
                    memset(lineaAux,0,15);
                    strcpy(lineaAux,"0,G,"); strcat(lineaAux,nombre);
                    strcpy(lineaJournal,lineaAux); strcat(lineaJournal,"\n");
                    fprintf(outfile,lineaAux);
                    fprintf(outfile,"\n");
                }
                else
                {
                    fprintf(outfile,linea);
                    fprintf(outfile,"\n");
                }
                nGrupo++;
                fscanf(infile,"%s",&linea);
            }

            fclose(infile); fclose(outfile);
            remove(gru);
            rename(auxgru,gru);
            /***************************************/
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char timeJour[15];
            strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
            JOURNALING rJour = NuevoJournal(3,0,"/user.txt",lineaJournal,timeJour,"root",777);
            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
            asigPrueba(sistema_ext,cadId);
            /***************************************/
            printf("Grupo %s eliminado con exito.\n\n",nombre);

        }
        else
        {
            printf("El nombre del grupo no Existe.\n\n");
        }
    }
    else
    {
        printf("Debe iniciar sesion como usuario root.\n\n");
    }
}

void comando_mkusr()
{
    ComillasCadId(); ComillasNombre(); ComillasPass(); ComillasUsuario();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar; int Cantidad = 0;
        MBR disco;
        EXT sistema_ext, aux_sistema; INODO i_nodo;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        aux_sistema = sistema_ext;
        Cantidad = CantidadUsuarios(cadId);
        int ExisteGrupo = VerificarGrupo(nombre,cadId), ExisteUsuario = VerificacionUsuario(usuario,cadId);
        if(ExisteGrupo == 1 && ExisteUsuario == 0)
        {
            if(CantLetras(usuario) == 1 && CantLetras(pass) == 1)
            {
                int i;
                char user[20] = "user_"; char linea_archivo[37]; char linea_bloque[37]; strcat(user,cadId); strcat(user,".txt");
                FILE *Archivo = fopen(user,"a+");
                sprintf(linea_archivo,"%d,U,%s,%s,%s",Cantidad,nombre,usuario,pass);
                strcat(linea_archivo,"\n");
                fprintf(Archivo,linea_archivo);
                fclose(Archivo);
                sprintf(linea_bloque,"%d,U,%s",Cantidad,nombre);
                Cantidad = 10 - strlen(nombre);
                for(i = 0; i<Cantidad; i++) { strcat(linea_bloque," "); } strcat(linea_bloque,",");
                strcat(linea_bloque,usuario);
                Cantidad = 10 - strlen(usuario);
                for(i = 0; i<Cantidad; i++) { strcat(linea_bloque," "); } strcat(linea_bloque,",");
                strcat(linea_bloque,pass);
                Cantidad = 10 - strlen(pass);
                for(i = 0; i<Cantidad; i++) { strcat(linea_bloque," "); } strcat(linea_bloque,"\n");
            ///////////////////////////////////////////////
            sistema_ext = InsertArchivoUsers(aux_sistema,"/user.txt",linea_bloque,37);
            /***************************************/
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char timeJour[15];
            strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
            JOURNALING rJour = NuevoJournal(1,0,"/user.txt",linea_bloque,timeJour,"root",777);
            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
            asigPrueba(sistema_ext,cadId);
            /***************************************/
             printf("Usuario \"%s\" creado con exito.\n\n",usuario);
            }
            else
            {
                printf("El usuario y la contrasenia solo llevan 10 letras maximo.\n\n");
            }
        }
        else if(ExisteGrupo == 0)
        { printf("El grupo no existe.\n\n"); }
        else
        { printf("El usuario ya existe.\n\n"); }
    }
    else
    {
        printf("Debe iniciar sesion como usuario root.\n\n");
    }
}


void comando_rmusr()
{
    ComillasCadId(); ComillasNombre(); memset(temporalGrupo,0,10); memset(temporalPass,0,10);
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        int existe = VerificacionUsuario(nombre,cadId);
        if(existe == 1)
        {
            char lineaJournal[37];
            char lineaAux[37]; int nGrupo = 1; char linea[37]; memset(lineaAux,0,37); memset(lineaAux,0,37);
            char gru[15] = "user_"; strcat(gru,cadId); strcat(gru,".txt");
            char auxgru[15] = "auxuser_"; strcat(auxgru,cadId); strcat(auxgru,".txt");
            FILE *infile; FILE *outfile;
            infile = fopen(gru,"r"); outfile = fopen(auxgru,"a+");

            fscanf(infile,"%s",&linea);
            while(!feof(infile))
            {
                sprintf(lineaAux,"%d,U,%s,%s,%s",nGrupo,temporalGrupo,nombre,temporalPass);
                if(strcmp(lineaAux,linea) == 0)
                {
                    memset(lineaAux,0,37);
                    sprintf(lineaAux,"0,U,%s,%s,%s",temporalGrupo,nombre,temporalPass);
                    strcpy(lineaJournal,lineaAux); strcat(lineaJournal,"\n");
                    fprintf(outfile,lineaAux);
                    fprintf(outfile,"\n");
                }
                else
                {
                    fprintf(outfile,linea);
                    fprintf(outfile,"\n");
                }
                nGrupo++;
                fscanf(infile,"%s",&linea);
            }

            fclose(infile); fclose(outfile);
            remove(gru);
            rename(auxgru,gru);
            /***************************************/
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char timeJour[15];
            strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
            JOURNALING rJour = NuevoJournal(3,0,"/user.txt",lineaJournal,timeJour,"root",777);
            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
            asigPrueba(sistema_ext,cadId);
            /***************************************/
            printf("Usuario %s eliminado con exito.\n\n",nombre);
            memset(temporalGrupo,0,10); memset(temporalPass,0,10);
        }
        else
        {
            printf("El nombre del usuario no Existe.\n\n");
        }
    }
    else
    {
        printf("Debe iniciar sesion como usuario root.\n\n");
    }
}



















