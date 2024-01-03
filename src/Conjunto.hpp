
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr){
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruirAux(_raiz);
}

template <class T>
void Conjunto<T>::destruirAux(Conjunto::Nodo *n) const {
    if(n != nullptr){
        destruirAux(n->izq);
        destruirAux(n->der);
        delete n;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    if (actual == nullptr){
        return false;
    }
    else {
        while (actual != nullptr && actual->valor != clave) {
            if (clave < actual->valor) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
        return actual != nullptr;
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    Nodo* actual = _raiz;
    if (actual == nullptr){
        _raiz = new Nodo(clave);
    }
    else {
        while (actual->valor != clave){
            if (clave < actual->valor && actual->izq == nullptr){
                actual->izq = new Nodo(clave);
                (actual->izq)->pad = actual;
                actual = actual->izq;
            }
            else if (clave < actual->valor && actual->izq != nullptr){
                actual = actual->izq;
            }
            else if (clave > actual->valor && actual->der == nullptr){
                actual->der = new Nodo(clave);
                (actual->der)->pad = actual;
                actual = actual->der;
            }
            else{
                actual = actual->der;
            }
        }
    }

}

template <class T>
void Conjunto<T>::remover(const T& clave) {

    Nodo *actual = _raiz;
    Nodo *padre = _raiz;
    if (actual->der == nullptr && actual->izq == nullptr){ //si se quiere borrar la raiz y la raiz es el unico elemento
        _raiz = nullptr;
    }
    else if (_raiz->valor == clave) { //si se quiere borrar la raiz
        if (predecesorInmediato(_raiz) == nullptr){ //solo tiene hijo derecho
            (_raiz->der)->pad = nullptr;
            _raiz = _raiz->der;
        }
        else if (predecesorInmediato(_raiz)->izq == nullptr) {//si tiene hijo izquierdo y derecho, y el pi no tiene hijo izquierdo
            Nodo* pi = predecesorInmediato(actual);
            pi->der = actual->der;
            if (pi == actual->izq){ //si el predecesor inmediato es directamete el nodo que esta a la izquierda (agrega esto al resto)
                pi->izq = nullptr;
                (pi->pad)->izq = nullptr;
            }
            else {
                pi->izq = actual->izq;
                actual->izq->pad =pi;
                (pi->pad)->der = nullptr;
            }
            pi->pad = nullptr;
            if (pi->der != nullptr){
                pi->der->pad = pi;
            }
            if (pi->izq != nullptr){
                pi->izq->pad = pi;
            }
            _raiz = pi;
        } else {
            Nodo *pi = predecesorInmediato(actual); //REVISAR
            if (pi == actual->izq) {
                pi->der = actual->der;
                pi->pad = nullptr;
                _raiz = pi;
            } else {
                (pi->pad)->der = nullptr;
                pi->der = actual->der;
                padre = pi;
                while (padre->izq != nullptr) {
                    padre = padre->izq;
                }

                padre->izq = actual->izq;
                actual->izq->pad = padre;
                pi->pad = nullptr;
                _raiz = pi;

            }
            if (pi->der != nullptr){
                pi->der->pad = pi;
            }
            if (pi->izq != nullptr){
                pi->izq->pad = pi;
            }
        }
    }


    else{
        while (actual != nullptr && actual->valor != clave) { //esto busca al elemento que se quiere borrar
            if (clave < actual->valor) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
        if (actual->der == nullptr && actual->izq == nullptr) {//caso se quiere borrar hoja
            if (actual == actual->pad->der) {//actualiza el valor actual y deja igual el del padre
                (actual->pad)->der = nullptr;
            } else {
                (actual->pad)->izq = nullptr;
            }
        } else if (actual->der == nullptr && actual->izq != nullptr) {//caso se quiere borrar nodo con un solo hijo
            if (actual == actual->pad->der) {//actualiza el valor actual y deja igual el del padre
                (actual->izq)->pad = actual->pad;
                (actual->pad)->der = actual->izq;
            } else {
                actual->izq->pad = actual->pad;
                (actual->pad)->izq = actual->izq;
            }
        } else if (actual->izq == nullptr && actual->der != nullptr) {//caso se quiere borrar nodo con un solo hijo
            if (actual == actual->pad->der) {//actualiza el valor actual y deja igual el del padre
                actual->der->pad = actual->pad;
                (actual->pad)->der = actual->der;
            } else {
                actual->der->pad = actual->pad;
                (actual->pad)->izq = actual->der;
            }
        } else {//caso se quiere borrar nodo con dos hijos
            Nodo* pi = predecesorInmediato(actual);
            if (actual->pad->der == actual) {
                if (pi->izq == nullptr) {
                    if (pi == actual->izq){ //si el predecesor inmediato es directamete el nodo que esta a la izquierda
                        (pi->pad)->izq = nullptr;
                        pi->pad = actual->pad;
                    }
                    else {
                        (pi->pad)->der = nullptr;
                        pi->izq = actual->izq;
                        actual->izq->pad = pi;
                        pi->pad = actual->pad;
                    }
                    pi->der = actual->der;
                    actual->pad->der = pi;
                    actual->der->pad = pi;
                }
                else{
                    if (pi == actual->izq){ //si el predecesor inmediato es directamete el nodo que esta a la izquierda
                        pi->pad = actual->pad;
                        actual->pad->der = pi;
                        pi->der = actual->der;
                        actual->der->pad = pi;
                    }
                    else{
                        (pi->pad)->der = nullptr;
                        padre = pi;
                        while (padre->izq != nullptr){
                            padre = padre->izq;
                        }
                        padre->izq = actual->izq;
                        actual->izq->pad = padre;
                        actual->pad->der = pi;
                        pi->der = actual->der;
                        actual->der->pad = pi;
                        pi->pad = actual->pad;
                    }


                }
                }
            else {
                if (pi->izq == nullptr) {
                    if (pi == actual->izq){
                        (pi->pad)->izq = nullptr;
                        actual->pad->izq = pi;
                        pi->der = actual->der;
                        pi->pad = actual->pad;
                        actual->der->pad = pi;
                    }
                    else {
                        (pi->pad)->der = nullptr;
                        pi->izq = actual->izq;
                        pi->der = actual->der;
                        actual->der->pad = pi;
                        pi->pad = actual->pad;
                        actual->pad->izq = pi;
                        actual->izq->pad = pi;
                    }
                }
                else {
                    if (pi == actual->izq){ //si el predecesor inmediato es directamete el nodo que esta a la izquierda
                        actual->pad->izq = pi;
                        pi->der = actual->der;
                        actual->der->pad = pi;
                        pi->pad = actual->pad;
                    }
                    else{
                        (pi->pad)->der = nullptr;
                        padre = pi;
                        while (padre->izq != nullptr){
                            padre = padre->izq;
                        }
                        padre->izq = actual->izq;
                        actual->izq->pad = padre;
                        pi->der = actual->der;
                        actual->pad->izq = pi;
                        pi->pad = actual->pad;
                        actual->der->pad = pi;

                    }

                }
                }
            }
        }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {

    Nodo* actual = _raiz;
    while (actual != nullptr && actual->valor != clave) {
        if (clave < actual->valor) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    if (actual->der == nullptr){
        return (actual->pad)->valor;
    }
    else {
        actual = actual->der;
        while (actual->izq != nullptr) {
            actual = actual->izq;
        }
    }
    return actual->valor;

}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    if (actual->izq == nullptr){
        return _raiz->valor;
    }
    else{
        while (actual->izq != nullptr){
            actual = actual->izq;
        }
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    if (actual->der == nullptr){
        return _raiz->valor;
    }
    else{
        while (actual->der != nullptr){
            actual = actual->der;
        }
    }
    return actual->valor;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::predecesorInmediato(Nodo *elem) {
    Nodo* actual = elem;
    actual = actual->izq;
    if (actual == nullptr){
        return nullptr;
    }
    else {
        while (actual->der != nullptr) {
            actual = actual->der;
        }
        return actual;
    }
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    Nodo* actual = _raiz;
    if (_raiz == nullptr){
        return 0;
    }
    else {
        return 1 + cardinalAux(actual->izq) + cardinalAux(actual->der);
    }
}

template <class T>
unsigned int Conjunto<T>::cardinalAux(Nodo* a) const {
    Nodo* actual = a;
    if (a == nullptr){
        return 0;
    }
    else {
        return 1 + cardinalAux(actual->izq) + cardinalAux(actual->der);
    }
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

