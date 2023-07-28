#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct
{
    char nombre[20];
    char apellido[20];
    int edad;
    int dni;
    int id;
    int dinero;
} cliente;

void registro_cliente_cuentas(char nombre_archivo[]);
void registro_nuevo_cliente ( char nombre_archivo[]);
void consulta_clientes(char nombre_archivo[],char nombre[],char apellido[]);
void mostrarcliente(cliente nuevo);
int validacionID(char nombre_archivo[],int id);
void deposito_y_retiros(char nombre_archivo[],int posicion,int dinero);
void depositar(char nombre_archivo[],int posicion,int dinero);
void retirar(char nombre_archivo[],int posicion,int dineroretirar);
void transferencia(char nombre_archivo[],int posicion);
float inversion_plazo_fijo(float monto_prestamo,float tasa_anual,int meses);

int main()
{

    char nombre_archivo[]= {"clientes.dat"};
    char  nombre[10];
    char apellido[10];
    int dni;
    int edad;
    int dinero=0;
    int continuar4=1;
    int opcion_inversion;
    int id_inversor;
    float monto_prestamo;
    float tasa_anual;
    int meses;
    int id;
    srand(time(NULL));


    int option;
    do
    {
        menu();
        scanf ("%d",&option);



        switch(option)
        {

        case 1:
            registro_cliente_cuentas(nombre_archivo);
            break;
        case 2:
            printf("Para realizar DEPOSITO/RETIRO/TRANSFERENCIA ingrese su ID");
            fflush(stdin);
            scanf("%i",&id);

            int posicion=validacionID(nombre_archivo,id);

            if (posicion==-1)
            {

                printf("ID NO REGISTRADO");
            }
            else
            {
                deposito_y_retiros(nombre_archivo,posicion,dinero);
            }

            break;


        case 3:
            printf("***********************************\n");
            puts("BIENBENIDO AL SECTOR DE INVERSIONES\n");
            printf("***********************************\n");
            printf("\n");
            printf("1. CALCULADORA PLAZO FIJO\n");
            printf("2. VOLVER AL INICIO\n");
            fflush(stdin);
            scanf("%i",&opcion_inversion);

            if (opcion_inversion==1)
            {
                printf("Ingrese su id");
                fflush(stdin);
                scanf("%i",&id_inversor);
                posicion=validacionID(nombre_archivo,id_inversor);


                if (posicion==-1)
                {

                    printf("ID NO REGISTRADO");
                }
                else
                {

                    cargar_datos_inversion(&monto_prestamo,&tasa_anual,&meses);
                    float monto_final=inversion_plazo_fijo(monto_prestamo,tasa_anual,meses);
                    printf("Monto final:%f",monto_final);
                }


            }
            break;

        case 4:



                printf("Ingrese el nombre del cliente a consultar\n");
                fflush(stdin);
                scanf("%s",&nombre);
                printf("Ingrese el apellido del cliente a consultar\n");
                fflush(stdin);
                scanf("%s",&apellido);
                consulta_clientes(nombre_archivo,nombre,apellido);


        }


    }
    while ( option != 0 );

    return 0;
}

void menu()
{

    printf("*********************\n");
    printf("BANCO ETIENNE FRANCES\n");
    printf("*********************\n");
    printf("\n");
    printf("\n");
    printf("**************\n");
    printf("MENU PRINCIPAL\n");
    printf("**************\n");
    printf("1. CLIENTES\n");
    printf("2. DEPOSITOS/RETIROS/TRANSFERENCIA\n");
    printf("3. INVERSION\n");
    printf("4. ESTADO DE CUENTA\n");

}





void registro_cliente_cuentas(char nombre_archivo[])
{

    int opciones;
    printf("1 REGISTRO\n");
    printf("2 REGRESAR MENU PRINCIPAL\n");
    scanf("%i",&opciones);

    if(opciones==1)
    {

        registro_nuevo_cliente(nombre_archivo);

    }


}


void registro_nuevo_cliente ( char nombre_archivo[])
{


    FILE *archi;
    archi= fopen(nombre_archivo,"ab");
    cliente nuevo;
    int repeticion;
    int id;
    if (archi!=NULL)
    {
            printf("Nombre del nuevo cliente\n");
            fflush(stdin);
            scanf("%s",&nuevo.nombre);

            printf("Apellido del nuevo cliente\n");
            fflush(stdin);
            scanf("%s",&nuevo.apellido);

            printf("Edad\n");
            fflush(stdin);
            scanf("%i",&nuevo.edad);

            printf("DNI\n");
            fflush(stdin);
            scanf("%i",&nuevo.dni);



            printf("Ingrese su id");
            fflush(stdin);
            scanf("%i",&id);
            repeticion=repeticionID(nombre_archivo,id);
            printf("Repeticion %i \n",repeticion);

            while (repeticion==1){

                printf("id ya existe\n");
                printf("Ingrese otra\n");
                fflush(stdin);
                scanf("%i",&id);
                repeticion=repeticionID(nombre_archivo,id);
            }
            if (repeticion==0){
                nuevo.id=id;
            }

            /*
            do
            {
                id=rand()%6;
              repeticion=repeticionID(nombre_archivo,id);

            }
            while (repeticion==1);

            nuevo.id=id;
            printf("Su ID es: %i \n",id);
*/

            fwrite(&nuevo,sizeof(cliente),1,archi);

        }
        fclose(archi);
    }



void consulta_clientes(char nombre_archivo[],char nombre[],char apellido[])
{

    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    cliente nuevo;
    int i=0;
    int continuar=1;
    if (archi!=NULL)
    {


        while (!feof(archi))
        {
            fread(&nuevo,sizeof(cliente),1,archi);
            if(!feof(archi))
            {

                if(strcmp(nombre,nuevo.nombre)==0)
                {

                    if(strcmp(apellido,nuevo.apellido)==0)
                    {

                        printf("Registro Numero %i\n",i++);
                        mostrarcliente(nuevo);


                    }
                    else
                    {
                        printf("Cliente no existe\n");
                    }
                }
            }
        }

        fclose(archi);
    }
}

void mostrarcliente(cliente nuevo)
{

    printf("Nombre %s \n",nuevo.nombre);
    printf("Apellido %s \n",nuevo.apellido);
    printf("Edad %i \n",nuevo.edad);
    printf("DNI %i \n",nuevo.dni);
    printf("Dinero %i \n",nuevo.dinero);
    printf("ID %i \n",nuevo.id);

}


int validacionID(char nombre_archivo[],int id)
{

    int i=0;
    int posicion=-1;
    cliente identificacion;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");

    if (archi!=NULL)
    {

        while(!feof(archi))
        {

            i++;
            fread(&identificacion,sizeof(cliente),1,archi);

            if (!feof(archi))
            {

                if (identificacion.id==id)
                {
                    posicion=i;
                    mostrarcliente(identificacion);
                    break;
                }

            }
        }
        fclose(archi);
    }
    return posicion;
}


void deposito_y_retiros(char nombre_archivo[],int posicion,int dinero)
{

    int deposito;
    int contdeposito=1;

    printf("1.DEPOSITO\n");
    printf("2.RETIRO\n");
    printf("3.TRANSFERENCIA\n");
    printf("4.VOLVER MENU\n");
    scanf("%i",&deposito);

    if (deposito==1)
    {

        while (contdeposito==1)
        {


            printf("Ingrese el dinero a depositar\n");
            fflush(stdin);
            scanf("%i",&dinero);
            depositar(nombre_archivo,posicion,dinero);
            printf("desea realizar otro deposito?\n");
            fflush(stdin);
            scanf("%i",&contdeposito);

        }
    }

    if (deposito==2)
    {

        while(contdeposito==1)
        {

            printf("Ingrese el dinero a retirar\n");
            fflush(stdin);
            scanf("%i",&dinero);
            retirar(nombre_archivo,posicion,dinero);


            printf("desea realizar otro retiro?\n");
            fflush(stdin);
            scanf("%i",&contdeposito);
        }
    }


    if (deposito==3)
    {

        while(contdeposito==1)
        {

            transferencia(nombre_archivo,posicion);

            printf("desea realizar otra transferencia?\n");
            fflush(stdin);
            scanf("%i",&contdeposito);

        }
    }

    else
    {
        menu();
    }
}


void depositar(char nombre_archivo[],int posicion,int dinero)
{

    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    cliente deposito1;


    if (archi!=NULL)
    {

        fseek(archi,sizeof(cliente)*(posicion-1),SEEK_SET);
        fread(&deposito1,sizeof(cliente),1,archi);

        deposito1.dinero+=dinero;

        fseek(archi,sizeof(cliente)*(posicion-1),SEEK_SET);
        fwrite(&deposito1,sizeof(cliente),1,archi);

        printf("Deposito realizado con exito\n");
        mostrarcliente(deposito1);

        fclose(archi);
    }

}




void retirar(char nombre_archivo[],int posicion,int dineroretirar)
{
    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");

    cliente retiro;

    if (archi!=NULL)
    {

        fseek(archi,sizeof(cliente)*(posicion-1),SEEK_SET);
        fread(&retiro,sizeof(cliente),1,archi);

        if(retiro.dinero>0 && dineroretirar<=retiro.dinero)
        {

            retiro.dinero-=dineroretirar;

            fseek(archi,sizeof(cliente)*(posicion-1),SEEK_SET);
            fwrite(&retiro,sizeof(cliente),1,archi);
            printf("Retiro realizado con exito\n");
        }
        else
        {
            printf("no se puede relizar, no tiene dinero suficiente para realizar el retiro\n");
        }



        mostrarcliente(retiro);


        fclose(archi);
    }

}



void transferencia(char nombre_archivo[],int posicion)
{

    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    cliente transferencia;
    int posicion1=0;

    int dinero_transferencia;
    int id;
    printf("Ingrese la id a la que desea transferir\n");
    fflush(stdin);
    scanf("%i",&id);

    if (archi!=NULL)
    {

        while(!feof(archi))
        {

            posicion1++;
            fread(&transferencia,sizeof(cliente),1,archi);

            if(!feof(archi))
            {

                if (id==transferencia.id)
                {

                    printf("Usted le transferira a:\n");
                    mostrarcliente(transferencia);

                    printf("Ingrese el dinero a transferir\n");
                    fflush(stdin);
                    scanf("%i",&dinero_transferencia);

                    retirar(nombre_archivo,posicion,dinero_transferencia);
                    depositar(nombre_archivo,posicion1,dinero_transferencia);



                }
            }

        }

        fclose(archi);

    }
}




float inversion_plazo_fijo(float monto_prestamo,float tasa_anual,int meses)
{

    float tasa_mensual;
    tasa_mensual=(tasa_anual / 100) / 12; /**Convertir la tasa anual a tasa mensual*/

    float monto_final;
    monto_final=monto_prestamo;

    for (int i=0; i<meses; i++)
    {

        monto_final=monto_final+((float)monto_final*(float)tasa_mensual);
    }


    return monto_final;
}


void cargar_datos_inversion(float *monto_prestamo,float *tasa_anual,int *meses)
{

    printf("Ingrese el MONTO DEL PRESTAMO");
    fflush(stdin);
    scanf("%f",monto_prestamo);


    printf("Ingrese la TASA ANUAL");
    fflush(stdin);
    scanf("%f",tasa_anual);


    printf("Ingrese cantidad de MESES");
    fflush(stdin);
    scanf("%i",meses);



}







int repeticionID(char nombre_archivo[],int id)
{

    int repeticion=0;
    cliente repeticion_ID;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");

    if (archi!=NULL)
    {

        while(!feof(archi))
        {
            fread(&repeticion_ID,sizeof(cliente),1,archi);

            if (!feof(archi))
            {

                if (repeticion_ID.id==id)
                {
                    repeticion=1;

                }

            }
        }
        fclose(archi);
    }
    return repeticion;
}


