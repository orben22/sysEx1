#include <malloc.h>
#include <stdlib.h>
#include "AdptArray.h"
//indexused my solution for Q4 in the exam moed_a and improved it

/**
 * ADT struct
 * can have any kind of element
 */
typedef struct AdptArray_ {
    int Size;
    PElement *pElemArray;
    DEL_FUNC delete;
    COPY_FUNC copy;
    PRINT_FUNC print;
} AdptArray_, *PAdptArray;

/**
 * Creates a new adptArray
 * @param copyFunc to copy a Pelement
 * @param delFunc to delete a Pelement
 * @param printFunc to print a Pelement
 * @return pointer to the ADT that was created
 */
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray arr = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (arr == NULL) {
        return NULL;
    }
    arr->Size = 0;
    arr->pElemArray = (PElement *) malloc(sizeof(PElement));
    if (arr->pElemArray == NULL) {
        return NULL;
    }
    if (delFunc == NULL || copyFunc == NULL || printFunc == NULL) {
        return NULL;
    }
    arr->delete = delFunc;
    arr->copy = copyFunc;
    arr->print = printFunc;
    return arr;
}

/**
 * a safe delete function that removes all Pelements in the adptArray
 * using the delete function given at the start
 * and release the memory of the array and the struct itself
 * @param arr pointer to the ADT
 */
void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) return;
    if (arr->pElemArray == NULL) return;
    for (int index = 0; index < arr->Size; index++) {
        if (arr->pElemArray[index] != NULL) {
            arr->delete(arr->pElemArray[index]);
        }
    }
    free(arr->pElemArray);
    free(arr);
}

/**
 * insert a new element at the given index
 * if the index is bigger than the size of the array
 * increase the size and then insert the element
 * @param arr pointer to the ADT
 * @param index
 * @param PElem to insert into the ADT
 * @return result FAIL or SUCCESS
 */
Result SetAdptArrayAt(PAdptArray arr, int index, PElement PElem) {
    if (arr == NULL) return FAIL;
    if (PElem == NULL) return FAIL;
    if (index >= arr->Size) {
        PElement *tempArr = (PElement *) malloc(sizeof(PElement) * (index + 1));
        for (int j = 0; j < index + 1; j++) {
            if (j < arr->Size) tempArr[j] = arr->pElemArray[j];
            else tempArr[j] = NULL;
        }
        arr->Size = index + 1;
        free(arr->pElemArray);
        arr->pElemArray = tempArr;
    }
    if (arr->pElemArray[index] != NULL) arr->delete(arr->pElemArray[index]);
    PElement temp = arr->copy(PElem);
    arr->pElemArray[index] = temp;
    return SUCCESS;
}

/**
 * get an element in index from the adptArray
 * @param arr pointer to the ADT
 * @param index
 * @return Pelement at that index arr[index] if not nulls
 */
PElement GetAdptArrayAt(PAdptArray arr, int index) {
    if (arr == NULL) return NULL;
    if (arr->pElemArray == NULL) return NULL;
    if (arr->pElemArray[index] == NULL) return NULL;
    return arr->copy(arr->pElemArray[index]);
}

/**
 * get the adpt array size -1 if its not allocated
 * @param arr pointer to the ADT
 * @return size or -1
 */
int GetAdptArraySize(PAdptArray arr) {
    if (arr != NULL || arr->pElemArray != NULL) return arr->Size;
    return -1;
}

/**
 * Print the adptArray elements using the print function that was given at the start
 * check for NULL
 * @param arr
 */
void PrintDB(PAdptArray arr) {
    if (arr == NULL) return;
    if (arr->pElemArray == NULL) return;
    for (int index = 0; index < arr->Size; index++) {
        if (arr->pElemArray[index] != NULL) arr->print(arr->pElemArray[index]);
    }
}
