#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int ret = -1;
    if(this != NULL)
    {
        ret = this->size;
    }
    return ret;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    Node* nextNode;
    int i = 0;
    if(this != NULL && nodeIndex >= 0 && !(nodeIndex >= ll_len(this)))
    {
        pNode = this->pFirstNode;
        for(i = 0; i < nodeIndex; i ++)
        {
            if(nodeIndex == 0)
            {
                break;
            }
            nextNode = pNode -> pNextNode;
            pNode = nextNode;
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    ///VERIFICAR SI ESTA BIEN
    int returnAux = -1;
    Node* prev;
    Node* next = NULL;
    Node* nuevoNodo;
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        prev = getNode(this, nodeIndex - 1);
        nuevoNodo = (Node*) malloc(sizeof(Node));
        if(nuevoNodo != NULL)
        {
            if(ll_len(this) == 0)
            {
                next = getNode(this, nodeIndex);
                this->pFirstNode = nuevoNodo;

                nuevoNodo -> pElement = pElement;
                nuevoNodo -> pNextNode = next;
            }
            if(nodeIndex == 0 && ll_len(this) > 0)
            {
                this->pFirstNode = nuevoNodo;

                next = prev -> pNextNode;
                nuevoNodo -> pElement = pElement;
                nuevoNodo -> pNextNode = next;
            }
            if(prev != NULL && ll_len(this) > 0)
            {
                next = prev -> pNextNode;
                prev -> pNextNode = nuevoNodo;
                nuevoNodo -> pElement = pElement;
                nuevoNodo -> pNextNode = next;
            }
            this->size ++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int indice = ll_len(this);
    //Node* actual;
    if(this != NULL)
    {
        //actual = getNode(this, indice);
        if(!addNode(this, indice, pElement))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}
//  ******* OJO CORREGIR *******************
/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;
    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
        auxNode = getNode(this, index);
        if(auxNode != NULL)
        {
            returnAux = auxNode -> pElement;
        }
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* actual;
    //int cantidad;
    if(this != NULL && index >= 0 && !(index >= ll_len(this)))
    {
        actual = getNode(this, index);
        if(actual != NULL)
        {
            actual -> pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* prev = NULL;
    Node* actual = NULL;
    Node* next = NULL;
    //int indice = index;
    if(this != NULL && index >= 0 && !(index >= ll_len(this)))
    {
        prev = getNode(this, index - 1);
        actual = getNode(this, index);
        if(index == 0)
        {
            this->pFirstNode = NULL;
            //free(this->pFirstNode);
            this->size --;
            returnAux = 0;
        }
        if(prev != NULL)
        {
            next = actual -> pNextNode;
            prev->pNextNode = next;
            actual -> pNextNode = NULL;
            //free(actual);
            this->size --;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    Node* node;
    int i;
    if(this != NULL)
    {
        if(ll_len(this) == 1)
        {
            this->pFirstNode = NULL;
            free(this->pFirstNode);
            this->size --;
            returnAux = 0;
        }
        for(i = 0; i < ll_len(this); i++)
        {
            node = getNode(this, i);
            if(node != NULL)
            {
                node->pNextNode = NULL;
                this->size --;
                returnAux = 0;
            }
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(!ll_clear(this))
        {
            free(this);
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    void* pVoid;
    if(this != NULL)
    {
        for(i = 0; i < ll_len(this); i++)
        {
            pVoid = ll_get(this, i);
            if(pElement == pVoid)
            {
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(ll_len(this) > 0)
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
        if(!addNode(this, index, pElement))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* node;
    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
        node = getNode(this, index);
        if(!ll_remove(this, index) && node != NULL)
        {
            returnAux =  node->pElement;
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        if(ll_indexOf(this, pElement) >= 0)
        {
            returnAux = 1;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    void* pVoidAux;
    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for( i = 0; i < ll_len(this); i++)
        {
            pVoidAux = ll_get(this, i);
            if(!ll_contains(this2, pVoidAux))
            {
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;

    if(this != NULL && from >= 0 && to <= ll_len(this))
    {
        cloneArray = ll_newLinkedList();
        for(i = from; i < to; i ++)
        {
            pElement = ll_get(this, i);
            if(pElement != NULL)
            {
                ll_add(cloneArray, pElement);
            }
        }
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();
        for(i = 0; i < ll_len(this); i ++)
        {
            pElement = ll_get(this, i);
            if(pElement != NULL)
            {
                ll_add(cloneArray, pElement);
            }
        }
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int flag;
    int i;
    int auxCmp;
    int lenLinkedList;
    void* auxNode;
    void* auxNode2;
    void* auxNode3;
    if(this != NULL  && pFunc != NULL && order >= 0 && order <= 1)
    {
        returnAux = 0;
        lenLinkedList = ll_len(this);
        do
        {
            flag = 0;
            for(i=0 ; i < lenLinkedList ; i ++)
            {
                auxNode = ll_get(this, i);
                auxNode2 = ll_get(this, i + 1);
                if(auxNode == NULL ||auxNode2 == NULL)
                {
                    continue;
                }
                auxCmp = pFunc(auxNode, auxNode2);
                switch(order)
                {
                case 0:
                    if(auxCmp < 0)
                    {
                        flag = 1;
                        auxNode3 = auxNode;
                        auxNode = auxNode2;
                        auxNode2 = auxNode3;
                        ll_set(this, i, auxNode);
                        ll_set(this, i + 1, auxNode2);
                    }
                    break;
                case 1:
                    if(auxCmp > 0)
                    {
                        flag = 1;
                        auxNode3 = auxNode;
                        auxNode = auxNode2;
                        auxNode2 = auxNode3;
                         ll_set(this, i, auxNode);
                        ll_set(this, i + 1, auxNode2);
                    }
                    break;
                }
            }
            lenLinkedList--;
        }
        while(flag);
    }

    return returnAux;
}
