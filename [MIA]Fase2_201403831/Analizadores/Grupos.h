
void comando_chgrp()
{
    ComillasUsuario(); ComillasNombre();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0)
    {
        /************Obtenemos el auxiliar*****************/
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
        /****************************************************/
        if(VerificacionUsuario(usuario,auxiliar.id) == 1 && VerificarGrupo(nombre,auxiliar.id) == 1)
        {
            char lineaJournal[37];
            char lineaAux[37]; int nUser = 1; char linea[37]; memset(lineaAux,0,37); memset(lineaAux,0,37);
            char aux[15] = "user_"; strcat(aux,auxiliar.id); strcat(aux,".txt");
            char auxuser[15] = "auxuser_"; strcat(auxuser,auxiliar.id); strcat(auxuser,".txt");
            FILE *infile; FILE *outfile;
            infile = fopen(aux,"r"); outfile = fopen(auxuser,"a+");

            fscanf(infile,"%s",&linea);
            while(!feof(infile))
            {
                sprintf(lineaAux,"%d,U,%s,%s,%s",nUser,temporalGrupo,usuario,temporalPass);
                if(strcmp(lineaAux,linea)== 0)
                {
                    memset(lineaAux,0,37);
                    sprintf(lineaAux,"%d,U,%s,%s,%s",nUser,nombre,usuario,temporalPass);
                    strcpy(lineaJournal,lineaAux); strcat(lineaJournal,"\n");
                    fprintf(outfile,lineaAux);
                    fprintf(outfile,"\n");
                    memset(lineaAux,0,37);
                }
                else
                {
                    fprintf(outfile,linea);
                    fprintf(outfile,"\n");
                }
                nUser++;
                fscanf(infile,"%s",&linea);
            }
            fclose(infile); fclose(outfile);
            memset(auxuser,0,15);
            strcpy(auxuser,"auxuser_");
            strcat(auxuser,auxiliar.id); strcat(auxuser,".txt");
            remove(aux);
            rename(auxuser,aux);
            printf("Usuario: %s se cambio al Grupo: %s\n\n",usuario,nombre);
            memset(temporalGrupo,0,10); memset(temporalPass,0,10);
        }
        else
        { printf("El usuario o grupo no existe.\n\n"); }
    }
    else
    {
        printf("Debe iniciar sessión como usuario root.\n\n");
    }
}

void comando_ren()
{
    ComillasCadId(); ComillasFichero(); ComillasNombre();
    if(strcmp(session.usuario,"\0") != 0 && VerificarUsuario(cadId) == 1)
    {
        TablaMount auxiliar;
        MBR disco;
        EXT sistema_ext;
        auxiliar = rTabla(cadId);
        disco = returnMBR(auxiliar.path);
        sistema_ext = returnSistema(disco,auxiliar);
        INODO IActual;
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char Time[15]; strftime(Time,15,"%d/%m/%y %H:%M:%S",tlocal);
        /***********************************************************/
        int existe = 0;
        LISTA_INODOS *iAux; iAux = sistema_ext.inodos;

        while(iAux!=NULL)
        {
            if(strcmp(iAux->i_nodo.i_pathlink,fichero) == 0)
            { existe = 1; IActual = iAux->i_nodo; break; }
            iAux=iAux->siguiente;
        }
        if(existe == 1)
        {
            existe = 0;
            if(PermisosEscritura(IActual.i_perm) == 1)
            {
                int Diagonal = 0,i;
                for(i = 0; i < strlen(fichero);i++)
                {
                    if(fichero[i]=='/')
                    {Diagonal=i;}
                }
                char NuevoNombre[200]; memset(NuevoNombre,0,200);
               for(i = 0; i <= Diagonal; i++)
               { NuevoNombre[i] = fichero[i]; }
                strcat(NuevoNombre,nombre);
                iAux = NULL; iAux = sistema_ext.inodos;
                while(iAux!=NULL)
                {
                    if(strcmp(iAux->i_nodo.i_pathlink,NuevoNombre) == 0)
                    { existe = 1; break; }
                    iAux=iAux->siguiente;
                }
                if(existe == 0)
                {
                    char AntiguoNombre[100]; memset(AntiguoNombre,0,100);
                    strcpy(AntiguoNombre,IActual.i_pathlink);
                    memset(IActual.i_pathlink,0,100);
                    strcpy(IActual.i_pathlink,NuevoNombre);

                    sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,IActual,AntiguoNombre);
                    /***************************************/
                    JOURNALING rJour = NuevoJournal(2,1,fichero,NuevoNombre,Time,session.usuario,IActual.i_perm);
                    sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
                    asigPrueba(sistema_ext,auxiliar.id);
                    /***************************************/
                    printf("La carpeta %s ha sido cambiada ha %s.\n\n",AntiguoNombre,NuevoNombre);
                }
                else
                { printf("La carpeta ya existe.\n\n"); }
            }
            else
            {
                printf("El fichero %s no tiene permisos de escritura.\n\n",fichero);
            }

        }
        else
        { printf("El fichero %s no existe.\n\n",fichero); }
    }
    else
    {
        printf("Debe iniciar sesion primero.\n\n");
    }
}

void comando_cat()
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
        /************************************************************/
        int existe = 0;
        LISTA_INODOS *iAux; LISTA_BLOQUES *bAux;
        iAux = sistema_ext.inodos;
        INODO rInodo; BLOQUE_ARCHIVO rArchivo;
        while(iAux!=NULL)
        {
            if(strcmp(iAux->i_nodo.i_pathlink,fichero)==0)
            { existe = 1; rInodo = iAux->i_nodo; break;}
            iAux = iAux->siguiente;
        }

        if(existe == 1)
        {
            if(PermisosLectura(rInodo.i_perm)==1)
            {   printf("Contenido de %s:\n\n",fichero);
                int i;
                for(i = 0; i < 15; i++)
                {
                    if(rInodo.i_block[i]!=-1)
                    {
                        bAux = NULL; bAux = sistema_ext.bloques;
                        while(bAux!=NULL)
                        {
                            if(bAux->b_archivo.n_bloque == rInodo.i_block[i])
                            {
                                rArchivo = bAux->b_archivo;
                                printf("%s\n",rArchivo.b_content);
                            }
                            bAux = bAux->siguiente;
                        }

                    }
                    else
                    { break; }
                }
                printf("\n");
            }
            else
            { printf("El archivo %s no tiene permisos de lectura.\n\n"); }
        }
        else
        { printf("El archivo %s no existe.\n\n"); }

    }
    else
    { printf("Primero debe iniciar sesion.\n\n"); }
}

void comando_mv()
{
    ComillasFichero(); ComillasCadId(); ComillasNombre();
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
        LISTA_INODOS *Origen, *Destino, *Padre; INODO iOrigen, iDestino, iPadre;
        LISTA_BLOQUES *bPadre; bPadre = sistema_ext.bloques; BLOQUE_CARPETA iCarpeta;
        int numOrigen, existOrigen = 0, existDest = 0;
        Origen = sistema_ext.inodos; Destino = sistema_ext.inodos; Padre = sistema_ext.inodos;

        while(Origen!=NULL)
        {
            if(strcmp(Origen->i_nodo.i_pathlink,fichero)==0)
            { existOrigen = 1; iOrigen = Origen->i_nodo; break;}
            Origen = Origen->siguiente;
        }
        while(Destino!=NULL)
        {
            if(strcmp(Destino->i_nodo.i_pathlink,nombre)==0)
            { existDest = 1; iDestino = Destino->i_nodo; break;}
            Destino = Destino->siguiente;
        }
        if(existOrigen == 0) {printf("El fichero origen %s no existe\n\n",fichero); return;}
        if(existDest == 0) {printf("El fichero destino %s no existe\n\n",nombre); return;}
        if(PermisosEscritura(iOrigen.i_perm)==0) {printf("El fichero %s no tiene permisos de escritura",iOrigen.i_pathlink); return;}
        if(PermisosEscritura(iDestino.i_perm)==0) {printf("El fichero %s no tiene permisos de escritura",iDestino.i_pathlink); return;}
        numOrigen = iOrigen.i_nlink;

        int i,Diagonal; char CarpetasPadres[200]; memset(CarpetasPadres,0,200);
        /******************************************/
        for(i = 0; i < strlen(fichero); i++)
        {
            if(fichero[i]=='/') {Diagonal = i;}
        }
        for(i = 0; i < Diagonal; i++)
        { CarpetasPadres[i] = fichero[i];}


        while(Padre!=NULL)
        {
            if(strcmp(Padre->i_nodo.i_pathlink,CarpetasPadres)==0)
            {
                iPadre = Padre->i_nodo; break;
            }
            Padre = Padre->siguiente;
        }
        if(PermisosEscritura(iPadre.i_perm)==0) {printf("La carpeta padre donde se encuentra alojado %s no tiene permisos de escritura.\n\n",fichero); return;}

        for(i = 0; i < 15; i++)
        {
            if(iPadre.i_block[i+1]==-1)
            {
                while(bPadre!=NULL)
                {
                    if(bPadre->b_carpeta.n_bloque == iPadre.i_block[i])
                    {
                        int j;
                        for(j=0;j<4;j++)
                        {
                            if(bPadre->b_carpeta.content[i] == numOrigen)
                            {
                                iCarpeta = bPadre->b_carpeta;
                                iCarpeta.content[j] = -1;
                                break;
                            }
                        }
                        break;
                    }
                    bPadre = bPadre->siguiente;
                }
                break;
            }
        }
        /******************************************/
        BLOQUE_APUNTADOR apun; BLOQUE_ARCHIVO archi;
        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,apun,archi,iCarpeta,1,iCarpeta.n_bloque);
        bPadre = NULL; bPadre = sistema_ext.bloques;
        for(i=0; i<15; i++)
        {
            if(iDestino.i_block[i+1] == -1)
            {
                while(bPadre!=NULL)
                {
                    if(bPadre->b_carpeta.n_bloque == iDestino.i_block[i])
                    {
                        iCarpeta = bPadre->b_carpeta;
                        int j;
                        for(j=0;j<4;j++)
                        {
                            if(iCarpeta.content[j]==-1)
                            {
                                iCarpeta.content[j] = numOrigen;
                                break;
                            }
                        }
                        break;
                    }
                    bPadre=bPadre->siguiente;
                }
                break;
            }
        }

        sistema_ext.bloques = ModificarBloque(sistema_ext.bloques,apun,archi,iCarpeta,1,iCarpeta.n_bloque);
        /***************************************/
        JOURNALING rJour = NuevoJournal(2,3,fichero,nombre,Time,session.usuario,iOrigen.i_perm);
        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
        asigPrueba(sistema_ext,auxiliar.id);
        /***************************************/
        printf("Se movio el fichero %s a %s.\n\n",fichero,nombre);
    }
    else
    {
        printf("Primero debe iniciar sesion.\n\n");
    }
}

void comando_chmod()
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
        if(recursivo == '\0')
        {
            LISTA_INODOS *iAux; iAux = sistema_ext.inodos;
            INODO rInodo; int existe = 0;
            while(iAux!=NULL)
            {
                if(strcmp(iAux->i_nodo.i_pathlink,fichero)==0)
                { existe = 1; rInodo = iAux->i_nodo; break;}
                iAux = iAux->siguiente;
            }
            if(rInodo.i_uid != atoi(session.idUsuario) || strcmp(session.grupo,"root")!=0)
            {printf("El usuario no es propietario del fichero, inicie sesión como root.\n\n"); return;}
            /*********Aqui pones validacion si pertenece al grupo*****************/

            if(existe == 0) { printf("El fichero %s no existe.\n\n",fichero); return;}
            rInodo.i_perm = tamanio;
            sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,rInodo.i_pathlink);
            /***************************************/
            JOURNALING rJour = NuevoJournal(2,4,fichero,"",Time,session.usuario,tamanio);
            sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
            asigPrueba(sistema_ext,auxiliar.id);
            /***************************************/
            printf("Se le asignaron los permisos %d al fichero %s.\n\n",tamanio,fichero);
        }
        else
        {
            //Recursivo
        }
    }
    else
    {
        printf("Primero debe iniciar sesión.\n\n");
    }
}

void comando_chown()
{
    ComillasCadId(); ComillasFichero(); ComillasUsuario();
    if(strcmp(session.usuario,"\0") != 0 && strcmp(session.grupo,"root") == 0 && VerificarUsuario(cadId) == 1)
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
        LISTA_INODOS *iAux; iAux = sistema_ext.inodos;
        INODO rInodo; int existe = 0;
        while(iAux!=NULL)
        {
            if(strcmp(iAux->i_nodo.i_pathlink,fichero) == 0)
            { existe = 1; rInodo = iAux->i_nodo; break; }
            iAux = iAux->siguiente;
        }
        if(existe == 0){ printf("El fichero %s no existe.\n\n",fichero); return; } existe = 0;

        existe = VerificacionUsuario2(usuario,cadId);
        if(existe == 0){ printf("El usuario %s no existe o está eliminado.\n\n",usuario); return;}

        rInodo.i_uid = atoi(temporalId);

        sistema_ext.inodos = ModificarInodo(sistema_ext.inodos,rInodo,rInodo.i_pathlink);
        /***************************************/
        JOURNALING rJour = NuevoJournal(2,4,fichero,temporalId,Time,usuario,rInodo.i_perm);
        sistema_ext.journal = InsertJournal(sistema_ext.journal,rJour);
        asigPrueba(sistema_ext,auxiliar.id);
        /***************************************/
        printf("El fichero %s esta asignado a %s, nuevo i_uid: %d.\n\n",fichero,usuario,atoi(temporalId));
        memset(temporalId,0,5);
    }
    else
    {
        printf("Debe iniciar sesión como usuario root.\n\n");
    }
}


