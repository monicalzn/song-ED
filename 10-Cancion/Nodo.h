#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

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


   private:
        Nodo *inicio;

};



#endif // NODO_H_INCLUDED
