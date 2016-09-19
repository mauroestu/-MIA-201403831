
typedef struct TablaRegistro
{
    char nombre[100];
    char path[500];
    char total[500];
    char fecha[128];
    int activo;
    int tama;
}Datos;

void Espera()
{
int i;
for(i = 0; i<999999; i++){}
for(i = 0; i<999999; i++){}
for(i = 0; i<999999; i++){}
for(i = 0; i<999999; i++){}
}
typedef struct estructura_primaria
{
    char part_status;
    char part_type;
    char part_fit[10];
    int part_start;
    int part_size;
    char part_name[16];
}part_primaria;

typedef struct estructura_logico
{
    char part_status;
    char part_fit[10];
    int part_start;
    int part_size;
    char part_name[16];
}part_logic;


typedef struct estructura_extend
{
    char part_status;
    char part_fit[10];
    int part_start;
    int part_size;
    char part_name[16];
    part_logic part_logic_1;
    part_logic part_logic_2;
    part_logic part_logic_3;
    part_logic part_logic_4;
    part_logic part_logic_5;
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

///////////////////////////////

typedef struct nodo_caracter
{
    char c;
    struct nodo_caracter *siguiente;
}MATRIZ;

typedef struct nodo_super_bloque
{
    int formateado;
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    char s_mtime[15];
    char s_umtime[15];
    int s_mnt_count;
    char s_magic[10];
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    MATRIZ *bit_b;
    MATRIZ *bit_i;
}SUPER_BLOQUE;


//typedef struct nodo_contenido
//{
  //  int n_inodo;
   // char b_name[12];
//}CONTENIDO;

typedef struct nodo_carpeta
{
    int n_bloque;
    char b_name[12];
    int content[4];
}BLOQUE_CARPETA;

typedef struct nodo_archivo
{
    int n_bloque;
    char b_content[64];
}BLOQUE_ARCHIVO;

typedef struct nodo_apuntador
{
    int n_bloque;
    int b_pointers[16];
}BLOQUE_APUNTADOR;

typedef struct nodo_inodo
{
    int i_nlink;
    char i_pathlink[100];
    int i_uid;
    int i_gid;
    int i_size;
    char i_atime[15];
    char i_ctime[15];
    char i_mtime[15];
    int i_block[15];
    int i_type;
    int i_perm;
}INODO;

typedef struct NODO
{
    int i_type;
    BLOQUE_CARPETA b_carpeta;
    BLOQUE_ARCHIVO b_archivo;
    BLOQUE_APUNTADOR b_apuntador;
    struct NODO *siguiente;
}LISTA_BLOQUES;

typedef struct nodo_journal
{
    int tipo_operacion;
    int tipo_archivo;
    char nombre[20];
    char contenido[500];
    char fecha[15];
    char propietario[20];
    int permisos;
}JOURNALING;

typedef struct NODO_J
{
    JOURNALING j_nodo;
    struct NODO_J *siguiente;
}LISTA_JOURNAL;

typedef struct log
{
    char usuario[20];
    char contra[20];
    char grupo[20];
    char idUsuario[5];
    char idGrupo[5];
}SESION;

SESION session;

typedef struct NODO_I
{
    INODO i_nodo;
    struct NODO_I *siguiente;
}LISTA_INODOS;

typedef struct nodo_ext
{
    SUPER_BLOQUE s_bloque;
    LISTA_JOURNAL *journal;
    LISTA_BLOQUES *bloques;
    LISTA_INODOS *inodos;
}EXT;

MATRIZ *InsertCarac(MATRIZ *cabeza, char c)
{
    MATRIZ *nuevo, *ultimo;
    nuevo = (MATRIZ *)malloc(sizeof(MATRIZ));
    nuevo->c = c;
    nuevo->siguiente = NULL;

    if(cabeza == NULL)
    { cabeza = nuevo; }
    else
    {
        ultimo = cabeza;
        while(ultimo->siguiente!=NULL) ultimo = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }

    return cabeza;
}


LISTA_JOURNAL *InsertJournal(LISTA_JOURNAL *cabeza, JOURNALING nodo)
{
    LISTA_JOURNAL *nuevo, *ultimo;
    nuevo = (LISTA_JOURNAL *)malloc(sizeof(LISTA_JOURNAL));
    nuevo->j_nodo = nodo;
    nuevo->siguiente = NULL;

    if(cabeza == NULL)
    { cabeza = nuevo; }
    else
    {
        ultimo = cabeza;
        while(ultimo->siguiente!=NULL) ultimo = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }
    return cabeza;
}

MATRIZ *EliminarBitmap(MATRIZ *cabeza, int posicion)
{
    MATRIZ *auxiliar;
    auxiliar = cabeza;
    int i = 1;

    while(auxiliar!=NULL)
    {
        if(i==posicion)break;
        auxiliar = auxiliar->siguiente;
        i++;
    }
    auxiliar->c = '0';

    return cabeza;
}

LISTA_BLOQUES *ModificarBloque(LISTA_BLOQUES *cabeza, BLOQUE_APUNTADOR apunNodo,
BLOQUE_ARCHIVO archiNodo, BLOQUE_CARPETA carpeNodo, int tipo, int nBloque)
{
    LISTA_BLOQUES *auxiliar;
    auxiliar = cabeza;
    switch(tipo)
    {
        case 0:
            while(auxiliar!=NULL)
            {
                if(auxiliar->b_archivo.n_bloque == nBloque)break;
                auxiliar = auxiliar->siguiente;
            }
            auxiliar->b_archivo = archiNodo;
        break;
        case 1:
            while(auxiliar!=NULL)
            {
                if(auxiliar->b_carpeta.n_bloque == nBloque)break;
                auxiliar = auxiliar->siguiente;
            }
            auxiliar->b_carpeta=carpeNodo;
        break;
        case 2:
            while(auxiliar!=NULL)
            {
                if(auxiliar->b_apuntador.n_bloque == nBloque)break;
                auxiliar = auxiliar->siguiente;
            }
            auxiliar->b_apuntador = apunNodo;
        break;
    }

    return cabeza;
}

LISTA_INODOS *ModificarInodo(LISTA_INODOS *cabeza, INODO nodo, char nombre[])
{
    LISTA_INODOS *auxiliar;
    auxiliar = cabeza;

    while(auxiliar!=NULL)
    {
        if(strcmp(auxiliar->i_nodo.i_pathlink,nombre)==0)break;
        auxiliar = auxiliar->siguiente;
    }
    auxiliar->i_nodo = nodo;
    return cabeza;
}

LISTA_INODOS *EliminarInodo(LISTA_INODOS *cabeza, int n_inodo)
{
    LISTA_INODOS *auxiliar = cabeza;

    while(auxiliar!=NULL)
    {
        if(auxiliar->i_nodo.i_nlink == n_inodo)
        { free(auxiliar); break; }
        auxiliar = auxiliar->siguiente;
    }

    return cabeza;
}

LISTA_BLOQUES *EliminarBloque(LISTA_BLOQUES *cabeza, int n_bloque, int tipo)
{
    LISTA_BLOQUES *auxiliar = cabeza;
    switch(tipo)
    {
        case 0:
        while(auxiliar!=NULL)
        {
            if(auxiliar->b_archivo.n_bloque == n_bloque)
            { free(auxiliar); break; }
            auxiliar = auxiliar->siguiente;
        }
        break;
        case 1:
        while(auxiliar!=NULL)
        {
            if(auxiliar->b_carpeta.n_bloque == n_bloque)
            { free(auxiliar); break; }
            auxiliar = auxiliar->siguiente;
        }
        break;
        default:
        while(auxiliar!=NULL)
        {
            if(auxiliar->b_apuntador.n_bloque == n_bloque)
            { free(auxiliar); break; }
            auxiliar = auxiliar->siguiente;
        }
        break;
    }

    return cabeza;
}

LISTA_INODOS *InsertInodo(LISTA_INODOS *cabeza, INODO nodo)
{
    LISTA_INODOS *nuevo, *ultimo;
    nuevo = (LISTA_INODOS *)malloc(sizeof(LISTA_INODOS));
    nuevo->i_nodo = nodo;
    nuevo->siguiente = NULL;

    if(cabeza == NULL)
    {
        cabeza = nuevo;
    }
    else
    {
        ultimo = cabeza;
        while(ultimo->siguiente!=NULL) ultimo = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }

    return cabeza;
}

LISTA_BLOQUES *InsertBloque(LISTA_BLOQUES *cabeza, int tipo,
BLOQUE_CARPETA carpeta, BLOQUE_APUNTADOR apuntador, BLOQUE_ARCHIVO archivo)
{
    LISTA_BLOQUES *nuevo, *ultimo;
    nuevo = (LISTA_BLOQUES *)malloc(sizeof(LISTA_BLOQUES));
    nuevo->i_type = tipo;
    nuevo->siguiente = NULL;
    switch(tipo)
    {
        case 0: nuevo->b_archivo = archivo;
        break;
        case 1: nuevo->b_carpeta = carpeta;
        break;
        case 2: nuevo->b_apuntador = apuntador;
        break;
    }

    if(cabeza==NULL)
    {

        cabeza = nuevo;
    }
    else
    {
        ultimo = cabeza;
        while(ultimo->siguiente!=NULL) ultimo = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }

    return cabeza;
}

int RetornarPosicion(MATRIZ *cabeza)
{
    int i = 1;
    while(cabeza!=NULL)
    {
        if(cabeza->c == '0') { break; }
        cabeza = cabeza->siguiente;
        i++;
    }
    return i;
}

void ModificarBitMap(MATRIZ *cabeza, int posicion)
{
    int i = 1;
    while(cabeza!=NULL)
    {
        if(i == posicion)
        {
            cabeza->c = '1';
            break;
        }
        cabeza = cabeza->siguiente;
        i++;
    }
}


EXT sis_vda1; EXT sis_vda2; EXT sis_vda3; EXT sis_vda4; EXT sis_vda5; EXT sis_vda6; EXT sis_vda7; EXT sis_vda8; //1=crear 2=editar 3=eliminar
EXT sis_vdb1; EXT sis_vdb2; EXT sis_vdb3; EXT sis_vdb4; EXT sis_vdb5; EXT sis_vdb6; EXT sis_vdb7; EXT sis_vdb8;
EXT sis_vdc1; EXT sis_vdc2; EXT sis_vdc3; EXT sis_vdc4; EXT sis_vdc5; EXT sis_vdc6; EXT sis_vdc7; EXT sis_vdc8;
EXT sis_vdd1; EXT sis_vdd2; EXT sis_vdd3; EXT sis_vdd4; EXT sis_vdd5; EXT sis_vdd6; EXT sis_vdd7; EXT sis_vdd8;
EXT sis_vde1; EXT sis_vde2; EXT sis_vde3; EXT sis_vde4; EXT sis_vde5; EXT sis_vde6; EXT sis_vde7; EXT sis_vde8;
EXT sis_vdf1; EXT sis_vdf2; EXT sis_vdf3; EXT sis_vdf4; EXT sis_vdf5; EXT sis_vdf6; EXT sis_vdf7; EXT sis_vdf8;
EXT sis_vdg1; EXT sis_vdg2; EXT sis_vdg3; EXT sis_vdg4; EXT sis_vdg5; EXT sis_vdg6; EXT sis_vdg7; EXT sis_vdg8;
EXT sis_vdh1; EXT sis_vdh2; EXT sis_vdh3; EXT sis_vdh4; EXT sis_vdh5; EXT sis_vdh6; EXT sis_vdh7; EXT sis_vdh8;


void asigPrueba(EXT sistema, char id[])
{   /*************Vda************/
    if(strcmp(id,"vda1")==0)
    { sis_vda1 = sistema; return; }
    if(strcmp(id,"vda2")==0)
    { sis_vda2 = sistema; return; }
    if(strcmp(id,"vda3")==0)
    { sis_vda3 = sistema; return; }
    if(strcmp(id,"vda4")==0)
    { sis_vda4 = sistema; return; }
    if(strcmp(id,"vda5")==0)
    { sis_vda5 = sistema; return; }
    if(strcmp(id,"vda6")==0)
    { sis_vda6 = sistema; return; }
    if(strcmp(id,"vda7")==0)
    { sis_vda7 = sistema; return; }
    if(strcmp(id,"vda8")==0)
    { sis_vda8 = sistema; return; }
    /*************Vdb************/
    if(strcmp(id,"vdb1")==0)
    { sis_vdb1 = sistema; return; }
    if(strcmp(id,"vdb2")==0)
    { sis_vdb2 = sistema; return; }
    if(strcmp(id,"vdb3")==0)
    { sis_vdb3 = sistema; return; }
    if(strcmp(id,"vdb4")==0)
    { sis_vdb4 = sistema; return; }
    if(strcmp(id,"vdb5")==0)
    { sis_vdb5 = sistema; return; }
    if(strcmp(id,"vdb6")==0)
    { sis_vdb6 = sistema; return; }
    if(strcmp(id,"vdb7")==0)
    { sis_vdb7 = sistema; return; }
    if(strcmp(id,"vdb8")==0)
    { sis_vdb8 = sistema; return; }
    /*************Vdc************/
    if(strcmp(id,"vdc1")==0)
    { sis_vdc1 = sistema; return; }
    if(strcmp(id,"vdc2")==0)
    { sis_vdc2 = sistema; return; }
    if(strcmp(id,"vdc3")==0)
    { sis_vdc3 = sistema; return; }
    if(strcmp(id,"vdc4")==0)
    { sis_vdc4 = sistema; return; }
    if(strcmp(id,"vdc5")==0)
    { sis_vdc5 = sistema; return; }
    if(strcmp(id,"vdc6")==0)
    { sis_vdc6 = sistema; return; }
    if(strcmp(id,"vdc7")==0)
    { sis_vdc7 = sistema; return; }
    if(strcmp(id,"vdc8")==0)
    { sis_vdc8 = sistema; return; }
    /*************Vdd************/
    if(strcmp(id,"vdd1")==0)
    { sis_vdd1 = sistema; return; }
    if(strcmp(id,"vdd2")==0)
    { sis_vdd2 = sistema; return; }
    if(strcmp(id,"vdd3")==0)
    { sis_vdd3 = sistema; return; }
    if(strcmp(id,"vdd4")==0)
    { sis_vdd4 = sistema; return; }
    if(strcmp(id,"vdd5")==0)
    { sis_vdd5 = sistema; return; }
    if(strcmp(id,"vdd6")==0)
    { sis_vdd6 = sistema; return; }
    if(strcmp(id,"vdd7")==0)
    { sis_vdd7 = sistema; return; }
    if(strcmp(id,"vdd8")==0)
    { sis_vdd8 = sistema; return; }
    /*************Vde************/
    if(strcmp(id,"vde1")==0)
    { sis_vde1 = sistema; return; }
    if(strcmp(id,"vde2")==0)
    { sis_vde2 = sistema; return; }
    if(strcmp(id,"vde3")==0)
    { sis_vde3 = sistema; return; }
    if(strcmp(id,"vde4")==0)
    { sis_vde4 = sistema; return; }
    if(strcmp(id,"vde5")==0)
    { sis_vde5 = sistema; return; }
    if(strcmp(id,"vde6")==0)
    { sis_vde6 = sistema; return; }
    if(strcmp(id,"vde7")==0)
    { sis_vde7 = sistema; return; }
    if(strcmp(id,"vde8")==0)
    { sis_vde8 = sistema; return; }
    /*************Vdf************/
    if(strcmp(id,"vdf1")==0)
    { sis_vdf1 = sistema; return; }
    if(strcmp(id,"vdf2")==0)
    { sis_vdf2 = sistema; return; }
    if(strcmp(id,"vdf3")==0)
    { sis_vdf3 = sistema; return; }
    if(strcmp(id,"vdf4")==0)
    { sis_vdf4 = sistema; return; }
    if(strcmp(id,"vdf5")==0)
    { sis_vdf5 = sistema; return; }
    if(strcmp(id,"vdf6")==0)
    { sis_vdf6 = sistema; return; }
    if(strcmp(id,"vdf7")==0)
    { sis_vdf7 = sistema; return; }
    if(strcmp(id,"vdf8")==0)
    { sis_vdf8 = sistema; return; }
    /*************Vdg************/
    if(strcmp(id,"vdg1")==0)
    { sis_vdg1 = sistema; return; }
    if(strcmp(id,"vdg2")==0)
    { sis_vdg2 = sistema; return; }
    if(strcmp(id,"vdg3")==0)
    { sis_vdg3 = sistema; return; }
    if(strcmp(id,"vdg4")==0)
    { sis_vdg4 = sistema; return; }
    if(strcmp(id,"vdg5")==0)
    { sis_vdg5 = sistema; return; }
    if(strcmp(id,"vdg6")==0)
    { sis_vdg6 = sistema; return; }
    if(strcmp(id,"vdg7")==0)
    { sis_vdg7 = sistema; return; }
    if(strcmp(id,"vdg8")==0)
    { sis_vdg8 = sistema; return; }
    /*************Vdh************/
    if(strcmp(id,"vdh1")==0)
    { sis_vdh1 = sistema; return; }
    if(strcmp(id,"vdh2")==0)
    { sis_vdh2 = sistema; return; }
    if(strcmp(id,"vdh3")==0)
    { sis_vdh3 = sistema; return; }
    if(strcmp(id,"vdh4")==0)
    { sis_vdh4 = sistema; return; }
    if(strcmp(id,"vdh5")==0)
    { sis_vdh5 = sistema; return; }
    if(strcmp(id,"vdh6")==0)
    { sis_vdh6 = sistema; return; }
    if(strcmp(id,"vdh7")==0)
    { sis_vdh7 = sistema; return; }
    if(strcmp(id,"vdh8")==0)
    { sis_vdh8 = sistema; return; }
}

EXT returnPrueba(char id[])
{
EXT rPruebita;
    /*************Vda************/
    if(strcmp(id,"vda1")==0)
    { rPruebita = sis_vda1; return rPruebita; }
    if(strcmp(id,"vda2")==0)
    { rPruebita = sis_vda2; return rPruebita; }
    if(strcmp(id,"vda3")==0)
    { rPruebita = sis_vda3; return rPruebita; }
    if(strcmp(id,"vda4")==0)
    { rPruebita = sis_vda4; return rPruebita; }
    if(strcmp(id,"vda5")==0)
    { rPruebita = sis_vda5; return rPruebita; }
    if(strcmp(id,"vda6")==0)
    { rPruebita = sis_vda6; return rPruebita; }
    if(strcmp(id,"vda7")==0)
    { rPruebita = sis_vda7; return rPruebita; }
    if(strcmp(id,"vda8")==0)
    { rPruebita = sis_vda8; return rPruebita; }
    /*************Vdb************/
    if(strcmp(id,"vdb1")==0)
    { rPruebita = sis_vdb1; return rPruebita; }
    if(strcmp(id,"vdb2")==0)
    { rPruebita = sis_vdb2; return rPruebita; }
    if(strcmp(id,"vdb3")==0)
    { rPruebita = sis_vdb3; return rPruebita; }
    if(strcmp(id,"vdb4")==0)
    { rPruebita = sis_vdb4; return rPruebita; }
    if(strcmp(id,"vdb5")==0)
    { rPruebita = sis_vdb5; return rPruebita; }
    if(strcmp(id,"vdb6")==0)
    { rPruebita = sis_vdb6; return rPruebita; }
    if(strcmp(id,"vdb7")==0)
    { rPruebita = sis_vdb7; return rPruebita; }
    if(strcmp(id,"vdb8")==0)
    { rPruebita = sis_vdb8; return rPruebita; }
    /*************Vdc************/
    if(strcmp(id,"vdc1")==0)
    { rPruebita = sis_vdc1; return rPruebita; }
    if(strcmp(id,"vdc2")==0)
    { rPruebita = sis_vdc2; return rPruebita; }
    if(strcmp(id,"vdc3")==0)
    { rPruebita = sis_vdc3; return rPruebita; }
    if(strcmp(id,"vdc4")==0)
    { rPruebita = sis_vdc4; return rPruebita; }
    if(strcmp(id,"vdc5")==0)
    { rPruebita = sis_vdc5; return rPruebita; }
    if(strcmp(id,"vdc6")==0)
    { rPruebita = sis_vdc6; return rPruebita; }
    if(strcmp(id,"vdc7")==0)
    { rPruebita = sis_vdc7; return rPruebita; }
    if(strcmp(id,"vdc8")==0)
    { rPruebita = sis_vdc8; return rPruebita; }
    { rPruebita = sis_vdb8; return rPruebita; }
    /*************Vde************/
    if(strcmp(id,"vde1")==0)
    { rPruebita = sis_vde1; return rPruebita; }
    if(strcmp(id,"vde2")==0)
    { rPruebita = sis_vde2; return rPruebita; }
    if(strcmp(id,"vde3")==0)
    { rPruebita = sis_vde3; return rPruebita; }
    if(strcmp(id,"vde4")==0)
    { rPruebita = sis_vde4; return rPruebita; }
    if(strcmp(id,"vde5")==0)
    { rPruebita = sis_vde5; return rPruebita; }
    if(strcmp(id,"vde6")==0)
    { rPruebita = sis_vde6; return rPruebita; }
    if(strcmp(id,"vde7")==0)
    { rPruebita = sis_vde7; return rPruebita; }
    if(strcmp(id,"vde8")==0)
    { rPruebita = sis_vde8; return rPruebita; }
    /*************Vdf************/
    if(strcmp(id,"vdf1")==0)
    { rPruebita = sis_vdf1; return rPruebita; }
    if(strcmp(id,"vdf2")==0)
    { rPruebita = sis_vdf2; return rPruebita; }
    if(strcmp(id,"vdf3")==0)
    { rPruebita = sis_vdf3; return rPruebita; }
    if(strcmp(id,"vdf4")==0)
    { rPruebita = sis_vdf4; return rPruebita; }
    if(strcmp(id,"vdf5")==0)
    { rPruebita = sis_vdf5; return rPruebita; }
    if(strcmp(id,"vdf6")==0)
    { rPruebita = sis_vdf6; return rPruebita; }
    if(strcmp(id,"vdf7")==0)
    { rPruebita = sis_vdf7; return rPruebita; }
    if(strcmp(id,"vdf8")==0)
    { rPruebita = sis_vdf8; return rPruebita; }
    /*************Vdg************/
    if(strcmp(id,"vdg1")==0)
    { rPruebita = sis_vdg1; return rPruebita; }
    if(strcmp(id,"vdg2")==0)
    { rPruebita = sis_vdg2; return rPruebita; }
    if(strcmp(id,"vdg3")==0)
    { rPruebita = sis_vdg3; return rPruebita; }
    if(strcmp(id,"vdg4")==0)
    { rPruebita = sis_vdg4; return rPruebita; }
    if(strcmp(id,"vdg5")==0)
    { rPruebita = sis_vdg5; return rPruebita; }
    if(strcmp(id,"vdg6")==0)
    { rPruebita = sis_vdg6; return rPruebita; }
    if(strcmp(id,"vdg7")==0)
    { rPruebita = sis_vdg7; return rPruebita; }
    if(strcmp(id,"vdg8")==0)
    { rPruebita = sis_vdg8; return rPruebita; }
    /*************Vdh************/
    if(strcmp(id,"vdh1")==0)
    { rPruebita = sis_vdh1; return rPruebita; }
    if(strcmp(id,"vdh2")==0)
    { rPruebita = sis_vdh2; return rPruebita; }
    if(strcmp(id,"vdh3")==0)
    { rPruebita = sis_vdh3; return rPruebita; }
    if(strcmp(id,"vdh4")==0)
    { rPruebita = sis_vdh4; return rPruebita; }
    if(strcmp(id,"vdh5")==0)
    { rPruebita = sis_vdh5; return rPruebita; }
    if(strcmp(id,"vdh6")==0)
    { rPruebita = sis_vdh6; return rPruebita; }
    if(strcmp(id,"vdh7")==0)
    { rPruebita = sis_vdh7; return rPruebita; }
    if(strcmp(id,"vdh8")==0)
    { rPruebita = sis_vdh8; return rPruebita; }
}














