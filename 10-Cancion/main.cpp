//estructura de datos
//ing armandina leal
//jonathan ahrens
//a00800663
//monica lozano
//a01138967
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

class Nodo
{
    public:
        double frecuencia;
        int duracion;
        Nodo *sig;
        Nodo() { sig = NULL;}
        Nodo(double f, int d) { frecuencia = f; duracion = d; sig = NULL; }
        Nodo(double f, int d, Nodo* s) { frecuencia = f; duracion = d, sig = s; }
};

class Cancion
{
    public:
//        Inicializa la cancion a una lista vacia
        Cancion() { inicio = NULL;}
//        Copy constructor
        Cancion(const Cancion& C)
//        Inicializa la cancion como una copia de la cancion C pasado como parametro.
        {
            inicio = NULL;
            if (C.inicio != NULL)
            {
                Nodo *p = C.inicio->sig;
                Nodo *aux = new Nodo(p->frecuencia, p->duracion);
                Nodo *r = aux;
                while( p != C.inicio)
                {
                    p = p->sig;
                    r->sig = new Nodo(p->frecuencia, p->duracion);
                    r = r->sig;
                }
                r->sig = aux;
                inicio = r;
            }
        }
//        Destructor
        ~Cancion()
//        Libera la memoria dinamica solicitada.
        {
            while (!cancionVacia()) borraNota();
        }
//        Sobrecarga del operador =
        Cancion& operator = (const Cancion& C )
//        Coloca en la cancion una copia de la cancion C.
        {
            if (this != &C )
            {
                while (!cancionVacia()) borraNota(); //destructor
                if (C.inicio != NULL) //copyconstructor
                {
                    Nodo *p = C.inicio->sig;
                    Nodo *aux = new Nodo(p->frecuencia, p->duracion);
                    Nodo *r = aux;
                    while( p != C.inicio)
                    {
                        p = p->sig;
                        r->sig = new Nodo(p->frecuencia, p->duracion);
                        r = r->sig;
                    }
                    r->sig = aux;
                    inicio = r;
                }
            }
            return *this;
        }
//        Agregar una nota a la cancion
        void agregaNota (double f, int d)
//        Agrega una nota en un nodo que se debe colocar despues del nodo apuntado por inicio. Despues de eso inicio debe apuntar al nuevo nodo.
        {
            Nodo *nuevo = new Nodo(f, d);
            if (inicio == NULL) //si la pila esta vacia
            {   //creo una pila con un nodo
                inicio = nuevo;
            }
            else
            {
                nuevo->sig = inicio->sig;
            }
            inicio->sig = nuevo;
            inicio = nuevo;
        }
        void agregaFlota (double f, int d)
//        Agrega una nota en un nodo que se debe colocar despues del nodo apuntado por inicio. Despues de eso inicio debe apuntar al nuevo nodo.
        {
            Nodo *nuevo = new Nodo(f, d);
            if (inicio == NULL) //si la pila esta vacia
            {   //creo una pila con un nodo
                inicio = nuevo;
            }
            else
            {
                nuevo->sig = inicio->sig;
            }
            inicio->sig = nuevo;
        }
//        Borra una nota a la cancion
        void borraNota ()
//        Borra el nodo que se encuentra despues del nodo apuntado por inicio.
        {   //precondicion: pila no vacia
            Nodo *p = inicio -> sig;
            if( inicio == inicio -> sig )
                inicio = NULL;
            else
            {
                inicio->sig = p->sig;
            }
            delete p;
        }
//        Observa la frecuencia de la nota
        double observaFrecuencia() { return inicio->sig->frecuencia; }
//        Regresa el valor de la frecuencia del nodo que se encuentra despues del nodo apuntado por inicio.
//        Observa la duracion de la nota
        int observaDuracion() { return inicio->sig->duracion; }
//        Regresa el valor de la duracion del nodo que se encuentra despues del nodo apuntado por inicio.
//        Cancion vacia
        bool cancionVacia() { return inicio == NULL; }
//        Regresa el valor true si la cancion no contiene notas; falso en caso contrario.
//        Nota: Puedes agregar a la clase otros metodos que te apoyen para reproducir la cancion pero NO DEBES modificar ninguno de los metodos anteriores.


   // private:
        Nodo *inicio;

};

int main()
{
    Cancion cancion1, cancion2;
    double frequency;
    int time, k=0, j=0;
    char res;
    string archivo;
    bool pausa = true, salida = true, tmezcla = true, mezcla = true, pausa2 = true;

    cout << "Nombre del archivo de la cancion 1" << endl;
    cin >> archivo;

    ifstream archcan;
    archcan.open(archivo.c_str());
    while (archcan >> frequency >> time)
    {
        cancion1.agregaNota(frequency, time);
    }
    archcan.close();

    cout << "Nombre del archivo de la cancion 2" << endl;
    cin >> archivo;
    ifstream archcon;
    archcon.open(archivo.c_str());
    while (archcon >> frequency >> time)
    {
        cancion2.agregaNota(frequency, time);
    }
    archcon.close();

    Nodo *d = cancion1.inicio, *d2 = cancion2.inicio;

    cout << "Presiona: \n r.- Reproducir. \n" << endl;
    cout << "Efectos: \n  1.- Pulso.\n  2.- Inicia Mezcla.\n  3.- TerminaMezcla." << endl;
    cout << "  4.- Sorpresa.\n  5.- Pausa.\n  6.- Continua.\ns.- fin." << endl;
    cin >> res;

    if (tolower(res) == 'r'){
        do{
            do
            {
                if(pausa)
                {
                    cout << ".";
                    Beep(d->frecuencia, d->duracion);
                    d = d->sig;
                }
                if(kbhit())
                {
                    switch(getch())
                    {
                        case '1': //agrega Nota
                            cout << "\2.";
                            Beep(1864.66, 273);
                            break;
                        case '2': //Mezcla
                            mezcla = true;
                            tmezcla = true;
                            do{
                                if (pausa2)
                                {
                                    if(mezcla){
                                        cout << "*";
                                        Beep(d2->frecuencia, d2->duracion);
                                        d2 = d2->sig;
                                        k++;
                                    }
                                    else{
                                        cout << ".";
                                        Beep(d->frecuencia, d->duracion);
                                        d = d->sig;
                                        j++;
                                    }
                                }
                                if(kbhit())
                                {
                                    switch(getch())
                                    {
                                        case '1': //agrega Nota
                                            cancion1.agregaFlota(1864.66, 273);
                                            break;
                                        case '3': // termina mezcla
                                            tmezcla = false;
                                            break;
                                        case '5': //pausas
                                            pausa2 = false;
                                            break;
                                        case '6': //play
                                            pausa2 = true;
                                            break;
                                    }
                                }
                                if(k == 3){mezcla = false; k = 0;}
                                if(j == 3){mezcla = true; j = 0;}
                            }while(tmezcla);
                            break;
                        case '4': // Sorpresa
                            cout << "!";
                            Beep(	587.33	,	545	);cout << "!";
                            Beep(	587.33	,	545	);cout << "!";
                            Beep(	622.254	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	369.994	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	783.991	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	783.991	,	545	);cout << "!";
                            Beep(	739.989	,	545	);cout << "!";
                            Beep(	698.456	,	545	);cout << "!";
                            Beep(	659.255	,	545	);cout << "!";
                            Beep(	622.254	,	545	);cout << "!";
                            Beep(	659.255	,	545	);cout << "!";
                            Beep(	415.305	,	545	);cout << "!";
                            Beep(	554.365	,	545	);cout << "!";
                            Beep(	523.251	,	545	);cout << "!";
                            Beep(	493.883	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	440	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	369.994	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	369.994	,	545	);cout << "!";
                            Beep(	493.883	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	415.305	,	545	);cout << "!";
                            Beep(	587.33	,	545	);cout << "!";
                            Beep(	783.991	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	783.991	,	545	);cout << "!";
                            Beep(	739.989	,	545	);cout << "!";
                            Beep(	698.456	,	545	);cout << "!";
                            Beep(	659.255	,	545	);cout << "!";
                            Beep(	622.254	,	545	);cout << "!";
                            Beep(	659.255	,	545	);cout << "!";
                            Beep(	415.305	,	545	);cout << "!";
                            Beep(	554.365	,	545	);cout << "!";
                            Beep(	523.251	,	545	);cout << "!";
                            Beep(	493.883	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	440	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	369.994	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	391.995	,	545	);cout << "!";
                            Beep(	311.127	,	545	);cout << "!";
                            Beep(	466.164	,	545	);cout << "!";
                            Beep(	391.995	,	545	);

                            break;
                        case '5': //pausas
                            pausa = false;
                            break;
                        case '6': //play
                            pausa = true;
                            break;
                        case 's': // salida
                            salida=false;
                            break;
                    }
                }
            }while(pausa && salida);
        }while(salida);
    };


    return 0;
}
