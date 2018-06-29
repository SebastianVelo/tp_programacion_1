#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void){
    ArrayList* this;
    ArrayList* resultado = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL) {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            resultado = this;
        }
        else{
            free(this);
        }
    }

    return resultado;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement){
    int resultado = -1;

	if(this != NULL && pElement != NULL){
		if(this->size < this->reservedSize || (this->size >= this->reservedSize && !resizeUp(this)) ){
			this->pElements[this->size]=pElement;
			this->size++;
			resultado = 0;
		}
	}
    return resultado;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this){
    int resultado = -1;
	if(this != NULL){
		free(this);
		resultado = 0;
	}
    return resultado;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this){
    int resultado = -1;
	if(this != NULL){
		resultado = this->size;
	}
    return resultado;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index){
    void* resultado = NULL;
	if(this != NULL && index <= this->size){
		resultado = this->pElements[index];
	}
    return resultado;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement){
    int resultado = -1;
	if(this != NULL && pElement != NULL){
		resultado = 1;
		if(al_indexOf(this, pElement) == -1){
			resultado = 0;
		}
	}
    return resultado;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index, void* pElement){
    int resultado = -1;
	if(this != NULL && pElement != NULL && al_len(this) >= index){
		this->pElements[index]=pElement;
		resultado = 0;
	}
    return resultado;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this, int index){
    int resultado = -1;
	if(this != NULL && this->size >= index){
		void* aux = al_get(this, index);
		if(aux != NULL){
			contract(this, index);
			this->size--;
			resultado = 0;
		}
	}
    return resultado;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this){
    int resultado = -1;
	if(this != NULL){
        this->pElements = realloc(this->pElements, sizeof(void *)*AL_INITIAL_VALUE);
		this->size = 0;
        this->reservedSize=AL_INITIAL_VALUE;
		resultado = 0;
	}
    return resultado;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this){
    ArrayList* resultado = NULL;
	if(this != NULL){
		resultado = al_newArrayList();
		int i;
		for(i = 0; i < al_len(this); i++){
			void* aux = this->pElements[i];
			if(aux != NULL){
				al_add(resultado, aux);
			}
		}
		resultado->size = this->size;
	}
    return resultado;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int resultado = -1;
	if(this != NULL && pElement != NULL && this->size >= index && index > 0){
		if(!expand(this, index)){
		   resultado = 0;
		   al_set(this, index, pElement);
		}
	}
    return resultado;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement){
    int resultado = -1;
	if(this != NULL && pElement != NULL){
		int i;
		for(i = 0; i < al_len(this); i++){
			if(this->pElements[i] == pElement){
				resultado = i;
				break;
			}
		}
	}
    return resultado;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this){
    int resultado = this == NULL ? -1 : (this->size == 0);
    return resultado;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index){
    void* resultado = NULL;
	if(this != NULL && this->size >= index && index > 0){
		resultado = al_get(this, index);
		if(resultado != NULL)
			al_remove(this, index);
	}
    return resultado;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to){
    ArrayList* resultado = NULL;
	if(this != NULL && from > 0 && to < this->size){
		resultado = al_newArrayList();
		int i;
		for(i = from; i < to; i++){
			void* aux = this->pElements[i];
			if(aux != NULL){
				al_add(resultado, aux);
			}
		}
		resultado->size = from-to;
	}
    return resultado ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2){
    int resultado = -1;
	if(this != NULL && this2 != NULL){
		resultado = 1;
		int i;
		for(i = 0; i < this2->size; i++){
			if(al_contains(this, this2->pElements[i]) != 1){
				resultado = 0;
				break;
			}
		}
	}
    return resultado;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order){
    int resultado = -1;
	int flagSwap = 0;
    if(this != NULL && pFunc != NULL && this-> size > 0 && (order == 1 || order == 0)){
        resultado = 0;
		int i,j;
		void *temp;

		for(i = 1; i < al_len(this); i++){
			temp = al_get(this, i);
			j=i-1;
			int descendente = pFunc(temp, al_get(this, j)) == 1 && order == 0;
			while(j>=0 && descendente){
				al_set(this, j+1, al_get(this, j));
				j--;
			}
			al_set(this, j+1, temp); // inserción
		 }

	}
    return resultado;
}
/** \brief
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
void al_map(ArrayList* this, void (*pFunc)(void*)){
    if(this != NULL && pFunc != NULL){
		int i;
		for(i = 0; i < al_len(this); i++)
			pFunc(al_get(this, i));
	}
}
/** \brief
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
ArrayList* al_filter(ArrayList* this2, int (*pFunc)(void*)){
    ArrayList* this = al_newArrayList();
    if(this2 != NULL && pFunc != NULL){
		int i;
		for(i = 0; i < al_len(this2); i++)
            if(pFunc(al_get(this2, i)))
                al_add(this, al_get(this2, i));
	}
	return this;
}
/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
ArrayList *al_difference(ArrayList* listA, ArrayList* listB){
    ArrayList *listC = al_newArrayList();
    if(listA != NULL && listB != NULL){
        int i;
        for(i = 0; i < al_len(listB); i++){
			void* elementListB = al_get(listB, i);
			if(!al_contains(listA, elementListB))
				al_add(listC, elementListB);
        }
	}
    return listC;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int resultado = -1;
	if(this != NULL){
		void* auxiliar = realloc(this->pElements, sizeof(void*) * (this->reservedSize + AL_INCREMENT));
		if(auxiliar != NULL){
			this->pElements = auxiliar;
			this->reservedSize += AL_INCREMENT;
			resultado = 0;
		}
	}
    return resultado;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index){
    int resultado = -1;
	if(this != NULL &&  al_len(this) > index){
		resultado = 0;
		int i;
		for(i =  al_len(this); i >= index; i--){
		   if(al_get(this,i) != NULL)
                al_set(this, i+1, al_get(this,i));
		}
	}
    return resultado;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index){
    int resultado = -1;
	if(this != NULL &&  al_len(this) > index){
		int i;
		for(i = index; i >  al_len(this); i++){
			al_set(this, i, al_get(this, i+1));
		}
	}
    return resultado;
}
