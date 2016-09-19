int PermisosEscritura(int Permiso)
{
    int exito = 0; int dUser = 0; int dGru = 0; int dOtro = 0;
    dUser = Permiso/100;
    dGru = (Permiso/10) - (dUser*10);
    dOtro = Permiso - (dGru *10);

    if(dUser == 7 || dUser == 6 || dUser == 3 || dUser == 2) exito = 1;
    if(dGru == 7 || dGru == 6 || dGru == 3 || dGru == 2) exito = 1;
    if(dOtro == 7 || dOtro == 6 || dOtro == 3 || dOtro == 2) exito = 1;

    return exito;
}

int PermisosLectura(int Permiso)
{
    int exito = 0; int dUser = 0; int dGru = 0; int dOtro = 0;
    dUser = Permiso/100;
    dGru = (Permiso/10) - (dUser*10);
    dOtro = Permiso - (dGru *10);

    if(dUser == 7 || dUser == 6 || dUser == 5 || dUser == 4) exito = 1;
    if(dGru == 7 || dGru == 6 || dGru == 5 || dGru == 4) exito = 1;
    if(dOtro == 7 || dOtro == 6 || dOtro == 5 || dOtro == 4) exito = 1;

    return exito;
}

int PermisosEjecucion(int Permiso)
{
    int exito = 0; int dUser = 0; int dGru = 0; int dOtro = 0;
    dUser = Permiso/100;
    dGru = (Permiso/10) - (dUser*10);
    dOtro = Permiso - (dGru *10);

    if(dUser == 7 || dUser == 5 || dUser == 3 || dUser == 1) exito = 1;
    if(dGru == 7 || dGru == 5 || dGru == 3 || dGru == 1) exito = 1;
    if(dOtro == 7 || dOtro == 5 || dOtro == 3 || dOtro == 1) exito = 1;

    return exito;
}

EXT CrearPadresRecursivo(EXT sistema_ext,char Carpeta[], int posicion, INODO InodoRecursivo)
{
    char auxCarpeta[500]; memset(auxCarpeta,0,500);
    int i;
    for(i= 0; i< posicion; i++) auxCarpeta[i] = Carpeta[i];
    LISTA_INODOS *Iaux;
    posicion++;
    LISTA_BLOQUES  *Baux;
    int existe = 0, numInodo;
    Iaux = sistema_ext.inodos;
    Baux = sistema_ext.bloques;
    INODO rInodo = InodoRecursivo, nInodo;
    BLOQUE_CARPETA rCarpeta, nCarpeta; BLOQUE_APUNTADOR nApun; BLOQUE_ARCHIVO nArchi;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
    while(Iaux!=NULL)
    {
        if(strcmp(Iaux->i_nodo.i_pathlink,auxCarpeta) == 0)
        {
            existe = 1; //numInodo = Iaux->i_nodo.i_nlink;
            rInodo = Iaux->i_nodo;
        }
        Iaux = Iaux->siguiente;
    }

    if(existe == 1)
    {
        if(posicion < strlen(Carpeta))
        {
            for(i = posicion; i < strlen(Carpeta);i++)
            { if(Carpeta[i]=='/') break;
            else
            {posicion++;}}
            return CrearPadresRecursivo(sistema_ext,Carpeta,posicion,rInodo);
        }
        else
        {
            printf("Todo el fichero ya existe.\n\n");
            return sistema_ext;
        }
    }
    else
    {
        if(posicion < strlen(Carpeta))
        {

            for(i = 0; i < 15;i++)
            {
                if(rInodo.i_block[i] == -1) break;
            }
            int j = i;
            i--;
            int numBloque = rInodo.i_block[i];
            while(Baux!=NULL)
            {
                if(numBloque == Baux->b_carpeta.n_bloque)
                {
                    rCarpeta = Baux->b_carpeta;
                    break;
                }
                Baux = Baux->siguiente;
            }

            if(j<12)
            {
                int NuevoBloque = 1;
                for(i = 0; i < 4; i++)
                {
                    if(rCarpeta.content[i] == -1)
                    { NuevoBloque = 0; break;}
                }
                if(NuevoBloque == 0)
                {
                    int pos_ino, pos_blo;
                    SUPER_BLOQUE sBloque;
                    sBloque = sistema_ext.s_bloque;
                    pos_ino = RetornarPosicion(sBloque.bit_i);pos_blo = RetornarPosicion(sBloque.bit_b);
                    ModificarBitMap(sBloque.bit_i,pos_ino);
                    sBloque.s_free_inodes_count--;
                    sBloque.s_first_ino = RetornarPosicion(sBloque.bit_i);

                    ModificarBitMap(sBloque.bit_b,pos_blo);
                    sBloque.s_free_blocks_count--;
                    sBloque.s_first_blo = RetornarPosicion(sBloque.bit_b);
                    rCarpeta.content[i] = pos_ino;
                    nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,auxCarpeta,Time,Time,Time);
                    nInodo.i_block[0] = pos_blo;
                    nCarpeta = NuevoBloqueCarpeta(pos_blo,auxCarpeta);
                    sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                    sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                    sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                    sistema_ext.s_bloque = sBloque;
                    /***************************************/
                    time_t tiempo = time(0);
                    struct tm *tlocal = localtime(&tiempo);
                    char timeJour[15];
                    strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                    JOURNALING rJour = NuevoJournal(1,1,auxCarpeta,"",timeJour,session.usuario,664);
                    sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                    asigPrueba(sistema_ext,cadId);
                    /***************************************/
                    printf("Carpeta %s creada con exito.\n\n",auxCarpeta);
                }
                else
                {
                    //Nuevo bloque de la carpeta padre
                    int pos_ino, pos_blo;
                    pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                    ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                    sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                    rInodo.i_block[j] = pos_blo; nCarpeta = NuevoBloqueCarpeta(pos_blo,rInodo.i_pathlink);
                    sistema_ext.s_bloque.s_free_blocks_count--;
                    sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,rInodo.i_pathlink);
                    sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                    //Nuevo bloque de la carpeta padre
                    rCarpeta = nCarpeta;
                    //////////////
                    pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                    ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                    sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                    sistema_ext.s_bloque.s_free_inodes_count--;
                    ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                    sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                    sistema_ext.s_bloque.s_free_blocks_count--;
                    rCarpeta.content[0] = pos_ino;
                    nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,auxCarpeta,Time,Time,Time);
                    nInodo.i_block[0] = pos_blo;
                    nCarpeta = NuevoBloqueCarpeta(pos_blo,auxCarpeta);
                    sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                    sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                    sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                    /***************************************/
                    time_t tiempo = time(0);
                    struct tm *tlocal = localtime(&tiempo);
                    char timeJour[15];
                    strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                    JOURNALING rJour = NuevoJournal(1,1,auxCarpeta,"",timeJour,session.usuario,664);
                    sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                    asigPrueba(sistema_ext,cadId);
                    /***************************************/
                     printf("Carpeta %s creada con exito. :v\n\n",auxCarpeta);
                }
            }
            else
            {
                //Bloque apuntador
            }

            for(i = posicion; i < strlen(Carpeta);i++)
            { if(Carpeta[i]=='/') break;
            else
            {posicion++;}}
            return CrearPadresRecursivo(sistema_ext,Carpeta,posicion,nInodo);
        }
        else
        {
            return sistema_ext;
        }
    }
}

void comando_mkdir()
{
    ComillasFichero(); ComillasCadId();
    if(strcmp(session.usuario,"\0") != 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
        if(padre == '\0')
        {
            //////////////Obtiene las carpetas padres//////////////
            int i, Diagonal = 0; char CarpetasPadres[500];
            for(i = 0; i < strlen(fichero); i++)
            {
                if(fichero[i] == '/')
                {Diagonal = i; }
            }
            memset(CarpetasPadres,0,500);

            if(Diagonal == 0) Diagonal++;
            for(i = 0; i < Diagonal; i++) { CarpetasPadres[i] = fichero[i]; }
            //////////////////////////////////////////////////////////////////
            LISTA_INODOS *Iaux;
            LISTA_BLOQUES  *Baux;
            int existe = 0, numInodo;
            Iaux = sistema_ext.inodos;
            Baux = sistema_ext.bloques;
            INODO rInodo, nInodo;
            BLOQUE_CARPETA rCarpeta, nCarpeta; BLOQUE_APUNTADOR nApun; BLOQUE_ARCHIVO nArchi;
            while(Iaux!=NULL)
            {
                if(strcmp(Iaux->i_nodo.i_pathlink,CarpetasPadres) == 0)
                {
                    existe = 1; numInodo = Iaux->i_nodo.i_nlink; rInodo = Iaux->i_nodo;
                }
                Iaux = Iaux->siguiente;
            }
            ////////////////////////////////////////////////////////
            if(existe == 1)
            {
                for(i = 0; i < 15;i++)
                {
                    if(rInodo.i_block[i] == -1) break;
                }
                int j = i;
                i--;
                int numBloque = rInodo.i_block[i];
                while(Baux!=NULL)
                {
                    if(numBloque == Baux->b_carpeta.n_bloque)
                    {
                        rCarpeta = Baux->b_carpeta;
                        break;
                    }
                    Baux = Baux->siguiente;
                }

                if(j < 12)
                {
                    int NuevoBloque = 1;
                    for(i = 0; i < 4; i++)
                    {
                        if(rCarpeta.content[i] == -1)
                        { NuevoBloque = 0; break;}
                    }
                    if(NuevoBloque == 0)
                    {
                        int pos_ino, pos_blo;
                        pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                        sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        sistema_ext.s_bloque.s_free_blocks_count--;
                        sistema_ext.s_bloque.s_free_inodes_count--;
                        rCarpeta.content[i] = pos_ino;
                        nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,fichero,Time,Time,Time);
                        nInodo.i_block[0] = pos_blo;
                        nCarpeta = NuevoBloqueCarpeta(pos_blo,fichero);
                        sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                        /***************************************/
                        time_t tiempo = time(0);
                        struct tm *tlocal = localtime(&tiempo);
                        char timeJour[15];
                        strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                        JOURNALING rJour = NuevoJournal(1,1,fichero,"",timeJour,session.usuario,664);
                        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                        asigPrueba(sistema_ext,auxiliar.id);
                        /***************************************/
                        printf("Carpeta %s creada con exito.\n\n",fichero);
                    }
                    else
                    {
                        //Nuevo bloque de la carpeta padre
                        int pos_ino, pos_blo;
                        pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        sistema_ext.s_bloque.s_free_blocks_count--;
                        rInodo.i_block[j] = pos_blo; nCarpeta = NuevoBloqueCarpeta(pos_blo,CarpetasPadres);
                        sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,CarpetasPadres);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        //Nuevo bloque de la carpeta padre
                        rCarpeta = nCarpeta;
                        //////////////
                        pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                        sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        sistema_ext.s_bloque.s_free_blocks_count--;
                        sistema_ext.s_bloque.s_free_inodes_count--;
                        rCarpeta.content[0] = pos_ino;
                        nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,fichero,Time,Time,Time);
                        nInodo.i_block[0] = pos_blo;
                        nCarpeta = NuevoBloqueCarpeta(pos_blo,fichero);
                        sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                        /***************************************/
                        time_t tiempo = time(0);
                        struct tm *tlocal = localtime(&tiempo);
                        char timeJour[15];
                        strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                        JOURNALING rJour = NuevoJournal(1,1,fichero,"",timeJour,session.usuario,664);
                        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                        asigPrueba(sistema_ext,cadId);
                        /***************************************/
                        printf("Carpeta %s creada con exito. :v\n\n",fichero);
                    }
                }
                else
                {
                    //Bloque apuntador
                }

            }
            else
            {
                printf("Las carpetas padres no existen.\n\n");
            }

        }
        else
        {
            //////////////Obtiene las carpetas padres//////////////
            int i, Diagonal = 0; char CarpetasPadres[500];
            for(i = 0; i < strlen(fichero); i++)
            {
                if(fichero[i] == '/')
                {Diagonal = i; }
            }
            memset(CarpetasPadres,0,500);
            if(Diagonal == 0) Diagonal++;
            for(i = 0; i < Diagonal; i++) { CarpetasPadres[i] = fichero[i]; }
            ////////////////////////////////////////////////////////
            INODO rInodo, nInodo;
            BLOQUE_CARPETA rCarpeta, nCarpeta; BLOQUE_APUNTADOR nApun; BLOQUE_ARCHIVO nArchi;
            sistema_ext = CrearPadresRecursivo(sistema_ext,fichero,1,rInodo);
            LISTA_INODOS *Iaux;
            LISTA_BLOQUES  *Baux;
            int numInodo;
            Iaux = sistema_ext.inodos;
            Baux = sistema_ext.bloques;
            while(Iaux!=NULL)
            {
                if(strcmp(Iaux->i_nodo.i_pathlink,CarpetasPadres) == 0)
                {
                    numInodo = Iaux->i_nodo.i_nlink; rInodo = Iaux->i_nodo;
                }
                Iaux = Iaux->siguiente;
            }

            for(i = 0; i < 15;i++)
                {
                    if(rInodo.i_block[i] == -1) break;
                }
                int j = i;
                i--;
                int numBloque = rInodo.i_block[i];
                while(Baux!=NULL)
                {
                    if(numBloque == Baux->b_carpeta.n_bloque)
                    {
                        rCarpeta = Baux->b_carpeta;
                        break;
                    }
                    Baux = Baux->siguiente;
                }

                if(j < 12)
                {
                    int NuevoBloque = 1;
                    for(i = 0; i < 4; i++)
                    {
                        if(rCarpeta.content[i] == -1)
                        { NuevoBloque = 0; break;}
                    }
                    if(NuevoBloque == 0)
                    {
                        int pos_ino, pos_blo;
                        pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                        sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);

                        rCarpeta.content[i] = pos_ino;
                        nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,fichero,Time,Time,Time);
                        nInodo.i_block[0] = pos_blo;
                        nCarpeta = NuevoBloqueCarpeta(pos_blo,fichero);
                        sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);

                        /***************************************/
                        time_t tiempo = time(0);
                        struct tm *tlocal = localtime(&tiempo);
                        char timeJour[15];
                        strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                        JOURNALING rJour = NuevoJournal(1,1,fichero,"",timeJour,session.usuario,664);
                        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                        asigPrueba(sistema_ext,auxiliar.id);
                        /***************************************/
                        printf("Carpeta %s creada con exito.\n\n",fichero);
                    }
                    else
                    {
                        //Nuevo bloque de la carpeta padre
                        int pos_ino, pos_blo;
                        pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        rInodo.i_block[j] = pos_blo; nCarpeta = NuevoBloqueCarpeta(pos_blo,CarpetasPadres);
                        sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,CarpetasPadres);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        //Nuevo bloque de la carpeta padre
                        rCarpeta = nCarpeta;
                        //////////////
                        pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                        ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                        sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                        sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);

                        rCarpeta.content[0] = pos_ino;
                        nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),-1,664,1,fichero,Time,Time,Time);
                        nInodo.i_block[0] = pos_blo;
                        nCarpeta = NuevoBloqueCarpeta(pos_blo,fichero);
                        sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                        /***************************************/
                        time_t tiempo = time(0);
                        struct tm *tlocal = localtime(&tiempo);
                        char timeJour[15];
                        strftime(timeJour,15,"%d/%m/%y %H:%M:%S",tlocal);
                        JOURNALING rJour = NuevoJournal(1,1,fichero,"",timeJour,session.usuario,664);
                        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                        asigPrueba(sistema_ext,cadId);
                        /***************************************/
                        printf("Carpeta %s creada con exito. :v\n\n",fichero);
                    }
                }
                else
                {
                    //Bloque apuntador
                }
        }
    }
    else
    {
        printf("Debe iniciar sesion.\n\n");
    }
}

EXT CrearArchivoRecursivo(EXT sistema_ext,INODO nInodo, BLOQUE_ARCHIVO nArchi, int posicion)
{
    if(tamanio >= 0)
    {
        int pos_blo, i; char cadena[64]; memset(cadena,0,64); char numero = '0';
        pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
        ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
        sistema_ext.s_bloque.s_first_blo= RetornarPosicion(sistema_ext.s_bloque.bit_b);
        sistema_ext.s_bloque.s_free_blocks_count--;
        nInodo.i_block[posicion] = pos_blo;

        for(i = 0; i < 64; i++)
        {
            if(tamanio >= 0)
            {
                if(numero > '9') numero = '0';
                cadena[i] = numero;
                numero++;tamanio--;
            }
            else
            { break; }
        }


        nArchi = NuevoBloqueArchivo(pos_blo,cadena);
        sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,nInodo,nInodo.i_pathlink);
        BLOQUE_APUNTADOR apun; BLOQUE_CARPETA carpe;
        sistema_ext.bloques = InsertBloque(sistema_ext.bloques,0,carpe,apun,nArchi);
        posicion++;
        return CrearArchivoRecursivo(sistema_ext,nInodo,nArchi,posicion);
    }
    else
    {
        return sistema_ext;
    }
}

void comando_mkfile()
{
    ComillasCadId(); ComillasFichero();
    if(strcmp(session.usuario,"\0") != 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
        /***********************************************************/
        if(padre == '\0')
        {
            /*****************Obtiene las carpetas padres*****************/
            int i, Diagonal = 0; char CarpetasPadres[500];
            for(i = 0; i < strlen(fichero); i++)
            {
                if(fichero[i] == '/')
                {Diagonal = i; }
            }
            memset(CarpetasPadres,0,500);

            if(Diagonal == 0) Diagonal++;
            for(i = 0; i < Diagonal; i++) { CarpetasPadres[i] = fichero[i]; }
            /***********************************************************/
            /***************Verifica si existe la carpeta padre***********/
            LISTA_INODOS *Iaux;
            LISTA_BLOQUES  *Baux;
            int existe = 0, numInodo;
            Iaux = sistema_ext.inodos;
            Baux = sistema_ext.bloques;
            INODO rInodo, nInodo;
            BLOQUE_CARPETA rCarpeta, nCarpeta; BLOQUE_APUNTADOR nApun; BLOQUE_ARCHIVO nArchi;
            while(Iaux!=NULL)
            {
                if(strcmp(Iaux->i_nodo.i_pathlink,CarpetasPadres) == 0)
                {
                    existe = 1; numInodo = Iaux->i_nodo.i_nlink; rInodo = Iaux->i_nodo;
                }
                Iaux = Iaux->siguiente;
            }
            /***********************************************************/
            if(existe == 1)
            {
            /*************Obtiene el bloque de carpeta libre************/
                for(i = 0; i < 15;i++)
                {
                    if(rInodo.i_block[i] == -1) break;
                }
                int j = i;
                i--;
                int numBloque = rInodo.i_block[i];
                while(Baux!=NULL)
                {
                    if(numBloque == Baux->b_carpeta.n_bloque)
                    {
                        rCarpeta = Baux->b_carpeta;
                        break;
                    }
                    Baux = Baux->siguiente;
                }
            /***********************************************************/
                if(j < 12)
                {
                    if(tamanio == -1) tamanio = 0;
                    int NuevoBloque = 1;
                    for(i = 0; i < 4; i++)
                    {
                        if(rCarpeta.content[i] == -1)
                        { NuevoBloque = 0; break;}
                    }
                    if(NuevoBloque == 0)
                    {
                        if(PermisosEscritura(rInodo.i_perm) == 1)
                        {
                            int pos_ino, tam = tamanio;
                            pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                            sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            sistema_ext.s_bloque.s_free_inodes_count--;
                            nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),tamanio,664,0,fichero,Time,Time,Time);
                            rCarpeta.content[i] = pos_ino;
                            sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                            sistema_ext = CrearArchivoRecursivo(sistema_ext,nInodo,nArchi,0);

                            sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                            /***************************************/
                            char contenido[500]; memset(contenido,0,500); char numero = '0';
                            for(i = 0; i < tam; i++)
                            {
                                if(numero > '9') numero = '0';
                                contenido[i] = numero;
                                numero++;
                            }
                            JOURNALING rJour = NuevoJournal(1,1,fichero,contenido,Time,session.usuario,664);
                            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                            asigPrueba(sistema_ext,auxiliar.id);
                            /***************************************/
                            printf("Archivo %s de %d bytes creado.\n\n",fichero,tam);
                        }
                        else
                        {
                            printf("La carpeta %s no tiene permisos de escritura.\n\n",CarpetasPadres);
                        }
                    }
                    else
                    {
                        if(PermisosEscritura(rInodo.i_perm) == 1)
                        {
                            /*******Nuevo bloque de la carpeta padre***********/
                            int pos_blo;
                            pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                            ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                            sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                            sistema_ext.s_bloque.s_free_blocks_count--;
                            rInodo.i_block[j] = pos_blo;
                            nCarpeta = NuevoBloqueCarpeta(pos_blo,CarpetasPadres);
                            sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,CarpetasPadres);
                            sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                            rCarpeta = nCarpeta;
                            /**************************************************/
                            int pos_ino, tam = tamanio;
                            pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                            sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            sistema_ext.s_bloque.s_free_inodes_count--;
                            nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),tamanio,664,0,fichero,Time,Time,Time);
                            rCarpeta.content[0] = pos_ino;
                            sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                            sistema_ext = CrearArchivoRecursivo(sistema_ext,nInodo,nArchi,0);

                            sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                            /***************************************/
                            char contenido[500]; memset(contenido,0,500); char numero = '0';
                            for(i = 0; i < tam; i++)
                            {
                                if(numero > '9') numero = '0';
                                contenido[i] = numero;
                                numero++;
                            }
                            JOURNALING rJour = NuevoJournal(1,1,fichero,contenido,Time,session.usuario,664);
                            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                            asigPrueba(sistema_ext,auxiliar.id);
                            /***************************************/
                            printf("Archivo %s de %d bytes creado. :v\n\n",fichero,tam);
                        }
                        else
                        {
                            printf("La carpeta %s no tiene permisos de escritura.\n\n",CarpetasPadres);
                        }

                    }
                }
                else
                {
                    //Bloque apuntador
                }
            }
            else
            {
                printf("Las carpetas padres no existen.\n\n");
            }
        }
        else
        {
            /*****************Obtiene las carpetas padres*****************/
            int i, Diagonal = 0; char CarpetasPadres[500];
            for(i = 0; i < strlen(fichero); i++)
            {
                if(fichero[i] == '/')
                {Diagonal = i; }
            }
            memset(CarpetasPadres,0,500);

            if(Diagonal == 0) Diagonal++;
            for(i = 0; i < Diagonal; i++) { CarpetasPadres[i] = fichero[i]; }
            /***********************************************************/
            /******************Creamos las carpetas padres****************/
            INODO rInodo, nInodo;
            BLOQUE_CARPETA rCarpeta, nCarpeta; BLOQUE_APUNTADOR nApun; BLOQUE_ARCHIVO nArchi;
            sistema_ext = CrearPadresRecursivo(sistema_ext,fichero,1,rInodo);
            /***************Verifica si existe la carpeta padre***********/
            LISTA_INODOS *Iaux;
            LISTA_BLOQUES  *Baux;
            int numInodo;
            Iaux = sistema_ext.inodos;
            Baux = sistema_ext.bloques;

            while(Iaux!=NULL)
            {
                if(strcmp(Iaux->i_nodo.i_pathlink,CarpetasPadres) == 0)
                {
                    numInodo = Iaux->i_nodo.i_nlink; rInodo = Iaux->i_nodo;
                }
                Iaux = Iaux->siguiente;
            }
            /***********************************************************/
            /*************Obtiene el bloque de carpeta libre************/
            for(i = 0; i < 15;i++)
            {
                if(rInodo.i_block[i] == -1) break;
            }
            int j = i;
            i--;
            int numBloque = rInodo.i_block[i];
            while(Baux!=NULL)
            {
                if(numBloque == Baux->b_carpeta.n_bloque)
                {
                    rCarpeta = Baux->b_carpeta;
                    break;
                }
                Baux = Baux->siguiente;
            }
            /***********************************************************/
            /***********************************************************/
                if(j < 12)
                {
                    if(tamanio == -1) tamanio = 0;
                    int NuevoBloque = 1;
                    for(i = 0; i < 4; i++)
                    {
                        if(rCarpeta.content[i] == -1)
                        { NuevoBloque = 0; break;}
                    }
                    if(NuevoBloque == 0)
                    {
                        if(PermisosEscritura(rInodo.i_perm) == 1)
                        {
                            int pos_ino, tam = tamanio;
                            pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                            sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            sistema_ext.s_bloque.s_free_inodes_count--;
                            nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),tamanio,664,0,fichero,Time,Time,Time);
                            rCarpeta.content[i] = pos_ino;
                            sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                            sistema_ext = CrearArchivoRecursivo(sistema_ext,nInodo,nArchi,0);

                            sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                            /***************************************/
                            char contenido[500]; memset(contenido,0,500); char numero = '0';
                            for(i = 0; i < tam; i++)
                            {
                                if(numero > '9') numero = '0';
                                contenido[i] = numero;
                                numero++;
                            }
                            JOURNALING rJour = NuevoJournal(1,1,fichero,contenido,Time,session.usuario,664);
                            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                            asigPrueba(sistema_ext,auxiliar.id);
                            /***************************************/
                            printf("Archivo de %d bytes creado.\n\n",tam);
                        }
                        else
                        {
                            printf("La carpeta %s no tiene permisos de escritura.\n\n",CarpetasPadres);
                        }
                    }
                    else
                    {
                        if(PermisosEscritura(rInodo.i_perm) == 1)
                        {
                            /*******Nuevo bloque de la carpeta padre***********/
                            int pos_blo;
                            pos_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                            ModificarBitMap(sistema_ext.s_bloque.bit_b,pos_blo);
                            sistema_ext.s_bloque.s_first_blo = RetornarPosicion(sistema_ext.s_bloque.bit_b);
                            sistema_ext.s_bloque.s_free_blocks_count--;
                            rInodo.i_block[j] = pos_blo;
                            nCarpeta = NuevoBloqueCarpeta(pos_blo,CarpetasPadres);
                            sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,CarpetasPadres);
                            sistema_ext.bloques = InsertBloque(sistema_ext.bloques,1,nCarpeta,nApun,nArchi);
                            rCarpeta = nCarpeta;
                            /**************************************************/
                            int pos_ino, tam = tamanio;
                            pos_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            ModificarBitMap(sistema_ext.s_bloque.bit_i,pos_ino);
                            sistema_ext.s_bloque.s_first_ino = RetornarPosicion(sistema_ext.s_bloque.bit_i);
                            sistema_ext.s_bloque.s_free_inodes_count--;
                            nInodo = NuevoInodo(pos_ino,atoi(session.idUsuario),atoi(session.idGrupo),tamanio,664,0,fichero,Time,Time,Time);
                            rCarpeta.content[0] = pos_ino;
                            sistema_ext.inodos = InsertInodo(sistema_ext.inodos,nInodo);
                            sistema_ext = CrearArchivoRecursivo(sistema_ext,nInodo,nArchi,0);

                            sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,nApun,nArchi,rCarpeta,1,rCarpeta.n_bloque);
                            /***************************************/
                            char contenido[500]; memset(contenido,0,500); char numero = '0';
                            for(i = 0; i < tam; i++)
                            {
                                if(numero > '9') numero = '0';
                                contenido[i] = numero;
                                numero++;
                            }
                            JOURNALING rJour = NuevoJournal(1,1,fichero,contenido,Time,session.usuario,664);
                            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                            asigPrueba(sistema_ext,auxiliar.id);
                            /***************************************/
                            printf("Archivo de %d bytes creado. :v\n\n",tam);
                        }
                        else
                        {
                            printf("La carpeta %s no tiene permisos de escritura.\n\n",CarpetasPadres);
                        }

                    }
                }
                else
                {
                    //Bloque apuntador
                }
        }
    }
    else
    {
        printf("Primero debe iniciar sesión.\n\n");
    }
}

void comando_edit()
{
    ComillasCadId(); ComillasFichero();
    if(strcmp(session.usuario,"\0") != 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
        /***********************************************************/
        LISTA_INODOS *iAux; iAux = sistema_ext.inodos; int existe = 0;
        INODO rInodo;
        while(iAux!=NULL)
        {
            if(strcmp(iAux->i_nodo.i_pathlink,fichero)==0)
            { existe = 1; rInodo = iAux->i_nodo; break; }
            iAux = iAux->siguiente;
        }
        if(existe==0) {printf("El archivo no existe.\n\n"); return;}
        int i;
        for(i = 0; i <15; i++)
        {
            if(rInodo.i_block[i]!=-1)
            {
                rInodo.i_block[i] = -1;
                sistema_ext.bloques = EliminarBloque(sistema_ext.bloques,rInodo.i_block[i],0);
                sistema_ext.s_bloque.bit_b = EliminarBitmap(sistema_ext.s_bloque.bit_b,rInodo.i_block[i]);
            }
        }
        /*************aqui ya elimine solo tenes que volver a crear esa mierda****************/
    }
    else
    { printf("Debe iniciar sesion primero.\n\n"); }
}









