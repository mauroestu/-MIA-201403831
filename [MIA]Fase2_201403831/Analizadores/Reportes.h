void reporte_inode()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    LISTA_INODOS *aInodo = sistema_ext.inodos;

    if(sistema_ext.s_bloque.formateado == 1)
    {

        FILE *reporte = fopen("inode.dot","a");
        fprintf(reporte,"digraph G {}");
        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"dot -Tpng -o %s inode.dot",fichero);
        system(sistema);
        memset(sistema,0,600);
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
        return;
    }

    char hola[1000], hola2[1000];
    strcpy(hola,"digraph G {\nnode [shape=circle]; \nnode [style=filled];");
    strcat(hola,"\nnode [fillcolor=\"#EEEEEE\"]; \nnode [color=\"#EEEEEE\"];");
    strcat(hola,"\nedge [color=\"#31CEF0\"]; \n");
    FILE *reporte;
    remove("inode.dot");
    reporte = fopen("inode.dot","a");
    fprintf(reporte,hola);
    memset(hola,0,1000);
    while(aInodo!=NULL)
    {
        sprintf(hola,"\"Inodo: %d \n i_uid: %d \n i_gid: %d \n i_perm: %d \n i_size: %d \n i_type: %d \n i_path: %s \n i_atime: %s \n i_ctime: %s \n i_mtime: %s\n",
        aInodo->i_nodo.i_nlink,aInodo->i_nodo.i_uid,aInodo->i_nodo.i_gid,aInodo->i_nodo.i_perm, aInodo->i_nodo.i_size,
        aInodo->i_nodo.i_type, aInodo->i_nodo.i_pathlink, aInodo->i_nodo.i_atime, aInodo->i_nodo.i_ctime, aInodo->i_nodo.i_mtime);
        sprintf(hola2,"i_bloc_0: %d \n i_bloc_1: %d \n i_bloc_2: %d \n i_bloc_3: %d \n i_bloc_4: %d \n i_bloc_5: %d \n i_bloc_6: %d \n i_bloc_7: %d \n i_bloc_8: %d \n i_bloc_9: %d \n i_bloc_10: %d \n i_bloc_11: %d \n i_bloc_12: %d \n i_bloc_13: %d \n i_bloc_14: %d\"",
        aInodo->i_nodo.i_block[0],aInodo->i_nodo.i_block[1],aInodo->i_nodo.i_block[2],aInodo->i_nodo.i_block[3],aInodo->i_nodo.i_block[4],
        aInodo->i_nodo.i_block[5],aInodo->i_nodo.i_block[6],aInodo->i_nodo.i_block[7],aInodo->i_nodo.i_block[8],aInodo->i_nodo.i_block[9],
        aInodo->i_nodo.i_block[10],aInodo->i_nodo.i_block[11],aInodo->i_nodo.i_block[12],aInodo->i_nodo.i_block[13],aInodo->i_nodo.i_block[14]);
        strcat(hola,hola2);
        fprintf(reporte,hola);
        memset(hola,0,1000); memset(hola2,0,1000);
        if(aInodo->siguiente!=NULL)
        fprintf(reporte," -> ");

        aInodo = aInodo->siguiente;
    }
    fprintf(reporte,"\n}");
    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s inode.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_block()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    LISTA_BLOQUES *aBloque = sistema_ext.bloques;

    if(sistema_ext.s_bloque.formateado == 1)
    {

        FILE *reporte = fopen("block.dot","a");
        fprintf(reporte,"digraph G {}");
        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"dot -Tpng -o %s block.dot",fichero);
        system(sistema);
        memset(sistema,0,600);
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
        return;
    }

    char hola[1000];
    strcpy(hola,"digraph G {\nnode [shape=circle]; \nnode [style=filled];");
    strcat(hola,"\nnode [fillcolor=\"#EEEEEE\"]; \nnode [color=\"#EEEEEE\"];");
    strcat(hola,"\nedge [color=\"#31CEF0\"]; \n");
    FILE *reporte;
    remove("block.dot");
    reporte = fopen("block.dot","a");
    fprintf(reporte,hola);
    memset(hola,0,1000);

    while(aBloque!=NULL)
    {
        switch(aBloque->i_type)
        {
            case 0:
            sprintf(hola,"\"Bloque Archivo \n b_block: %d \n b_content: %s\"",aBloque->b_archivo.n_bloque,aBloque->b_archivo.b_content);
            break;
            case 1:
            sprintf(hola,"\"Bloque Carpeta \n b_block: %d \n b_name: %s \n content_0: %d \n content_1: %d \n content_2: %d \n content_3: %d\"",
            aBloque->b_carpeta.n_bloque,aBloque->b_carpeta.b_name,
            aBloque->b_carpeta.content[0],aBloque->b_carpeta.content[1],aBloque->b_carpeta.content[2],aBloque->b_carpeta.content[3]);
            break;
            default:
            sprintf(hola,"\"Bloque apuntador \n n_block: %d \n b_pointer_0: %d \n b_pointer_1: %d \n b_pointer_2: %d \n b_pointer_3: %d \n b_pointer_4: %d \n b_pointer_5: %d \n b_pointer_6: %d \n b_pointer_7: %d \n b_pointer_8: %d \n b_pointer_9: %d \n b_pointer_10: %d \n b_pointer_11: %d \n b_pointer_12: %d \n b_pointer_13: %d \n b_pointer_14: %d \n b_pointer_15: %d \"",
            aBloque->b_apuntador.n_bloque,aBloque->b_apuntador.b_pointers[0],aBloque->b_apuntador.b_pointers[1],aBloque->b_apuntador.b_pointers[2]
            ,aBloque->b_apuntador.b_pointers[3],aBloque->b_apuntador.b_pointers[4],aBloque->b_apuntador.b_pointers[5],aBloque->b_apuntador.b_pointers[6]
            ,aBloque->b_apuntador.b_pointers[7],aBloque->b_apuntador.b_pointers[8],aBloque->b_apuntador.b_pointers[9],aBloque->b_apuntador.b_pointers[10]
            ,aBloque->b_apuntador.b_pointers[11],aBloque->b_apuntador.b_pointers[12],aBloque->b_apuntador.b_pointers[13],aBloque->b_apuntador.b_pointers[14]
            ,aBloque->b_apuntador.b_pointers[15]);
            break;
        }

        fprintf(reporte,hola);
        memset(hola,0,1000);
        if(aBloque->siguiente!=NULL)
        fprintf(reporte," -> ");
        aBloque = aBloque->siguiente;
    }

    fprintf(reporte,"\n}");
    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s block.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_sb()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    SUPER_BLOQUE sBloque = sistema_ext.s_bloque;
    char hola[1000];
    strcpy(hola,"digraph G {\nnode[shape=box] a0 [label=< <TABLE BORDER = \"1\" CELLBORDER=\"1\" CELLSPACING = \"1\"> \n");
    FILE *reporte;
    remove("sb.dot");
    reporte = fopen("sb.dot","a");
    fprintf(reporte,hola);
    memset(hola,0,1000);

    ///////////////////////
    fprintf(reporte,"<TR><TD>Nombre</TD><TD>Valor</TD></TR>\n");
    sprintf(hola,"<TR><TD>s_inodes_count</TD><TD>%d</TD></TR>\n",sBloque.s_inodes_count);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_blocks_count</TD><TD>%d</TD></TR>\n",sBloque.s_blocks_count);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_free_blocks_count</TD><TD>%d</TD></TR>\n",sBloque.s_free_blocks_count);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_free_inodes_count</TD><TD>%d</TD></TR>\n",sBloque.s_free_inodes_count);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_mtime</TD><TD>%s</TD></TR>\n",sBloque.s_mtime);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_umtime</TD><TD>%s</TD></TR>\n",sBloque.s_umtime);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_mnt_count</TD><TD>%d</TD></TR>\n",sBloque.s_mnt_count);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_magic</TD><TD>%s</TD></TR>\n",sBloque.s_magic);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_inode_size</TD><TD>%d</TD></TR>\n",sBloque.s_inode_size);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_block_size</TD><TD>%d</TD></TR>\n",sBloque.s_block_size);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_first_ino</TD><TD>%d</TD></TR>\n",sBloque.s_first_ino);
    fprintf(reporte,hola); memset(hola,0,1000);
    sprintf(hola,"<TR><TD>s_first_blo</TD><TD>%d</TD></TR>\n",sBloque.s_first_blo);
    fprintf(reporte,hola); memset(hola,0,1000);
    ///////////////////////


    fprintf(reporte,"</TABLE>>]; } ");
    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s sb.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);

}

void reporte_bm_inode()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    MATRIZ *bitIno = sistema_ext.s_bloque.bit_i;

    if(sistema_ext.s_bloque.formateado == 1)
    {
        char jaja = '0';
        int contador = 0;

        char hola[5];
        FILE *reporte;
        remove(fichero);
        reporte = fopen(fichero,"a");
        memset(hola,0,5);

        while(bitIno!=NULL)
        {
            sprintf(hola,"%c  ",jaja);
            fprintf(reporte,hola);
            memset(hola,0,5);

            if(contador == 19)
            { fprintf(reporte,"\n"); contador = -1; }

            contador++;
            bitIno = bitIno->siguiente;
        }

        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
        return;
    }

    int contador = 0;

    char hola[5];
    FILE *reporte;
    remove(fichero);
    reporte = fopen(fichero,"a");
    memset(hola,0,5);

    while(bitIno!=NULL)
    {
        sprintf(hola,"%c  ",bitIno->c);
        fprintf(reporte,hola);
        memset(hola,0,5);

        if(contador == 19)
        { fprintf(reporte,"\n"); contador = -1; }

        contador++;
        bitIno = bitIno->siguiente;
    }

    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_bm_block()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    MATRIZ *bitBlo = sistema_ext.s_bloque.bit_b;

    if(sistema_ext.s_bloque.formateado == 1)
    {   int contador = 0;
        char jaja = '0';
        char hola[5];
        FILE *reporte;
        remove(fichero);
        reporte = fopen(fichero,"a");
        memset(hola,0,5);

        while(bitBlo!=NULL)
        {
            sprintf(hola,"%c  ",jaja);
            fprintf(reporte,hola);
            memset(hola,0,5);

            if(contador == 19)
            { fprintf(reporte,"\n"); contador = -1; }

            contador++;
            bitBlo = bitBlo->siguiente;
        }

        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
    }
    int contador = 0;

    char hola[5];
    FILE *reporte;
    remove(fichero);
    reporte = fopen(fichero,"a");
    memset(hola,0,5);

    while(bitBlo!=NULL)
    {
        sprintf(hola,"%c  ",bitBlo->c);
        fprintf(reporte,hola);
        memset(hola,0,5);

        if(contador == 19)
        { fprintf(reporte,"\n"); contador = -1; }

        contador++;
        bitBlo = bitBlo->siguiente;
    }

    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_journaling()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    LISTA_JOURNAL *aJournal = sistema_ext.journal;

    if(sistema_ext.s_bloque.s_filesystem_type == 2)
    {
        char hola[2000];
        FILE *reporte;
        remove(fichero);
        reporte = fopen(fichero,"a");
        memset(hola,0,2000);

        while(aJournal!=NULL)
        {
            sprintf(hola,"Tipo de operacion: %d\nTipo : %d\nNombre: %s\nContenido: %s\nPropietario: %s\nFecha: %s \nPermisos: %d",
            aJournal->j_nodo.tipo_operacion,aJournal->j_nodo.tipo_archivo,aJournal->j_nodo.nombre,aJournal->j_nodo.contenido,
            aJournal->j_nodo.propietario,aJournal->j_nodo.fecha,aJournal->j_nodo.permisos);
            fprintf(reporte, hola); memset(hola,0,100);
            fprintf(reporte,"\n\n");
            aJournal=aJournal->siguiente;
        }

        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
    }
    else
    {
        printf("El sistema no es ext3 para mostrar journaling.\n\n");
        FILE *reporte;
        remove(fichero);
        reporte = fopen(fichero,"a");
        fclose(reporte);
    }


}

void reporte_tree()
{
    Directorio();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);
    LISTA_INODOS *aInodo = sistema_ext.inodos;
    LISTA_BLOQUES *aBloque = sistema_ext.bloques;

    if(sistema_ext.s_bloque.formateado == 1)
    {
        FILE *reporte;
        remove("tree.dot");
        reporte = fopen("tree.dot","a");
        fprintf(reporte,"digraph G {}");
        fclose(reporte);
        char sistema[600];
        sprintf(sistema,"dot -Tpng -o %s tree.dot",fichero);
        system(sistema);
        memset(sistema,0,600);
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
        return;
    }

    int i;

    char Total[99999]; char hola[1000]; memset(Total,0,99999); memset(hola,0,1000);
    strcpy(Total,"digraph G{\ngraph [rankdir = \"LR\"];\nnode [fontsize=\"16\" shape = \"ellipse\"];\nedge [];");
    while(aInodo!=NULL)
    {
        sprintf(hola,"\"inodo %d\" [ label = \"<f0> ID: %d | UId: %d | 201403831 | Nombre: %s | Tipo: %d | Size: %d | Permiso: %d",
        aInodo->i_nodo.i_nlink,aInodo->i_nodo.i_nlink,aInodo->i_nodo.i_uid,aInodo->i_nodo.i_pathlink,aInodo->i_nodo.i_type,aInodo->i_nodo.i_size,aInodo->i_nodo.i_perm);
        strcat(Total,hola); memset(hola,0,1000);
        for(i = 0; i < 15; i++)
        {
            if(aInodo->i_nodo.i_block[i]!=-1)
            {
                if(i < 12)
                {
                    sprintf(hola,"| <f%d> AD_%d = %d ",i+1,i,aInodo->i_nodo.i_block[i]);
                    strcat(Total,hola); memset(hola,0,1000);
                }
                else
                {
                    sprintf(hola,"| <f%d> AI_%d = %d ",i+1,i,aInodo->i_nodo.i_block[i]);
                    strcat(Total,hola); memset(hola,0,1000);
                }

            }
        }

        strcat(hola,"\",\nfillcolor = \"cornflowerblue\",style = \"filled\",\nshape=\"record\"\n];\n");
        strcat(Total,hola); memset(hola,0,1000);
        aInodo = aInodo->siguiente;
    }

    FILE *reporte;
    remove("tree.dot");
    reporte = fopen("tree.dot","a");
    fprintf(reporte,Total);
    memset(Total,0,99999);
    strcpy(Total,"");

    while(aBloque!=NULL)
    {
        switch(aBloque->i_type)
        {
            case 0:
                sprintf(hola,"\"bloque %d\" [ label = \"<f0> Carne: 201403831 | Bloque %d | Contenido: %s ",aBloque->b_archivo.n_bloque,aBloque->b_archivo.n_bloque,aBloque->b_archivo.b_content);
                strcat(Total,hola); memset(hola,0,1000);

                strcat(hola,"\",\nfillcolor = \"springgreen3\",style = \"filled\",\nshape=\"record\"\n];\n");
                strcat(Total,hola); memset(hola,0,1000);
            break;
            case 1:
                sprintf(hola,"\"bloque %d\" [ label = \"<f0>Carne: 201403831 | Bloque %d",aBloque->b_carpeta.n_bloque,aBloque->b_carpeta.n_bloque);
                strcat(Total,hola); memset(hola,0,1000);

                for(i = 0; i < 4; i++)
                {
                    if(aBloque->b_carpeta.content[i]!= -1)
                    {
                        sprintf(hola,"| <f%d> Hijo_%d = %d ",i+1,i,aBloque->b_carpeta.content[i]);
                        strcat(Total,hola); memset(hola,0,1000);
                    }
                }

                strcat(hola,"\",\nfillcolor = \"goldenrod1\",style = \"filled\",\nshape=\"record\"\n];\n");
                strcat(Total,hola); memset(hola,0,1000);
            break;
            case 2:
                //strcat(hola,"\",\nfillcolor = \"yellow\",style = \"filled\",\nshape=\"record\"\n];\n");
                //strcat(Total,hola); memset(hola,0,1000);
            break;
        }

        aBloque = aBloque->siguiente;
    }

    fprintf(reporte,Total); memset(Total,0,99999); strcpy(Total,"");

    aInodo = sistema_ext.inodos; aBloque = sistema_ext.bloques;

    while(aInodo!=NULL)
    {
        for(i = 0; i < 15; i++)
        {
            if(aInodo->i_nodo.i_block[i]!=-1)
            {
                sprintf(hola,"\"inodo %d\":f%d -> \"bloque %d\":f0 [\nid=0\n];\n",aInodo->i_nodo.i_nlink,i+1,aInodo->i_nodo.i_block[i]);
                strcat(Total,hola); memset(hola,0,1000);
            }
        }

        aInodo = aInodo->siguiente;
    }

    while(aBloque!=NULL)
    {
        if(aBloque->i_type == 1)
        {
            for(i = 0; i < 4; i++)
            {
                if(aBloque->b_carpeta.content[i] != -1)
                {
                    sprintf(hola,"\"bloque %d\":f%d -> \"inodo %d\":f0 [\nid=0\n];\n",aBloque->b_carpeta.n_bloque,i+1,aBloque->b_carpeta.content[i]);
                    strcat(Total,hola); memset(hola,0,1000);
                }
            }
        }
        aBloque = aBloque->siguiente;
    }

    strcat(Total,"\n}");


    fprintf(reporte,Total);
    fclose(reporte);
    char sistema[600];
    sprintf(sistema,"dot -Tpng -o %s tree.dot",fichero);
    system(sistema);
    memset(sistema,0,600);
    sprintf(sistema,"xdg-open %s",fichero);
	system(sistema);
}

void reporte_file()
{
    Directorio(); ComillasNombre(); ComillasCadId();
    mkdir(pfich);
    chmod(pfich,0777);
    TablaMount auxiliar;
    MBR disco;
    EXT sistema_ext;
    auxiliar = rTabla(cadId);
    disco = returnMBR(auxiliar.path);
    sistema_ext = returnSistema(disco,auxiliar);

    if(strcmp(nombre,"/user.txt")==0)
    {
        char archi[15] = "gru_"; strcat(archi,cadId); strcat(archi,".txt");
        char linea[37];
        FILE* archivo = fopen(archi,"r");
        fscanf(archivo,"%s",&linea);
        /**********Toma tu maghia Prr0 >:'v**************/
        char hola[1000];
        strcpy(hola,"digraph G {\nnode[shape=box] a0 [label=< <TABLE BORDER = \"1\" CELLBORDER=\"1\" CELLSPACING = \"1\"> \n");
        FILE *reporte;
        remove("file.dot");
        reporte = fopen("file.dot","a");
        fprintf(reporte,hola);
        memset(hola,0,1000);
        sprintf(hola,"<TR><TD>Contenido %s</TD></TR>\n",nombre);
        fprintf(reporte,hola); memset(hola,0,1000);
        /************************************************/
        while(!feof(archivo))
        {
            /***************La magia prro :v******************/

            sprintf(hola,"<TR><TD>%s</TD></TR>\n",linea);
            fprintf(reporte,hola); memset(hola,0,1000);

            /*************************************************/
            fscanf(archivo,"%s",&linea);
        }
        fclose(archivo);
        memset(archi,0,15); memset(linea,0,37);
        strcpy(archi,"user_"); strcat(archi,cadId); strcat(archi,".txt");
        archivo = fopen(archi,"r");
        fscanf(archivo,"%s",&linea);
        while(!feof(archivo))
        {
            /***************La magia prro :v******************/

            sprintf(hola,"<TR><TD>%s</TD></TR>\n",linea);
            fprintf(reporte,hola); memset(hola,0,1000);

            /*************************************************/
            fscanf(archivo,"%s",&linea);
        }
        fprintf(reporte,"</TABLE>>]; } ");
        fclose(reporte);
        fclose(archivo);
        char sistema[600];
        sprintf(sistema,"dot -Tpng -o %s file.dot",fichero);
        system(sistema);
        memset(sistema,0,600);
        sprintf(sistema,"xdg-open %s",fichero);
        system(sistema);
    }
    else if(sistema_ext.s_bloque.formateado == 1)
    {
        printf("El fichero %s no existe.\n\n",nombre);
        return;
    }
    else
    {
        int existe = 0;
        LISTA_INODOS *iAux; LISTA_BLOQUES *bAux;
        iAux = sistema_ext.inodos;
        INODO rInodo; BLOQUE_ARCHIVO rArchivo;
        while(iAux!=NULL)
        {
            if(strcmp(iAux->i_nodo.i_pathlink,nombre)==0)
            { existe = 1; rInodo = iAux->i_nodo; break;}
            iAux = iAux->siguiente;
        }
        if(existe == 1)
        {
            /****************Toma tu maghia Prr0 >:'v*****************/
            char hola[1000];
            strcpy(hola,"digraph G {\nnode[shape=box] a0 [label=< <TABLE BORDER = \"1\" CELLBORDER=\"1\" CELLSPACING = \"1\"> \n");
            FILE *reporte;
            remove("file.dot");
            reporte = fopen("file.dot","a");
            fprintf(reporte,hola);
            memset(hola,0,1000);
            sprintf(hola,"<TR><TD>Contenido %s</TD></TR>\n",nombre);
            fprintf(reporte,hola); memset(hola,0,1000);
            /*********************************************************/

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
                            sprintf(hola,"<TR><TD>%s</TD></TR>\n",rArchivo.b_content);
                            fprintf(reporte,hola); memset(hola,0,1000);
                        }
                        bAux = bAux->siguiente;
                    }

                }
                else
                { break; }
            }

            /***************Mas magia tukan mistico :v****************/
            fprintf(reporte,"</TABLE>>]; } ");
            fclose(reporte);
            char sistema[600];
            sprintf(sistema,"dot -Tpng -o %s file.dot",fichero);
            system(sistema);
            memset(sistema,0,600);
            sprintf(sistema,"xdg-open %s",fichero);
            system(sistema);
            /*********************************************************/
        }
        else
        {
            printf("El fichero %s no existe.\n\n",nombre);
        }
    }
}











