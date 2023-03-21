#include <malloc.h>
#include <stdlib.h>
#include "AdptArray.h"
//i used my solution for Q4 in the exam moed_a and improved it
typedef struct AdptArray_ {
    int Size;
    PElement *pElemArray;
    DEL_FUNC delete;
    COPY_FUNC copy;
    PRINT_FUNC print;
} AdptArray_, *PAdptArray;

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

void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) return;
    if (arr->pElemArray==NULL) return;
    for (int i = 0; i < arr->Size; i++) {
        if(arr->pElemArray[i]!=NULL) {
            arr->delete(arr->pElemArray[i]);
        }
    }
    free(arr->pElemArray);
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int i, PElement PElem) {
    if (arr == NULL) return FAIL;
    if (PElem == NULL) return FAIL;
    if (i >= arr->Size) {
        PElement *tempArr = (PElement *) malloc(sizeof(PElement) * (i + 1));
        for (int j = 0; j < i + 1; j++) {
            if (j < arr->Size) tempArr[j] = arr->pElemArray[j];
            else tempArr[j] = NULL;
        }
        arr->Size = i + 1;
        free(arr->pElemArray);
        arr->pElemArray = tempArr;
    }
    if (arr->pElemArray[i] != NULL) arr->delete(arr->pElemArray[i]);
    PElement temp = arr->copy(PElem);
    arr->pElemArray[i] = temp;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int i) {
    if (arr == NULL) return NULL;
    if (arr->pElemArray == NULL) return NULL;
    if (arr->pElemArray[i] == NULL) return NULL;
    return arr->copy(arr->pElemArray[i]);
}

int GetAdptArraySize(PAdptArray arr) {
    if (arr != NULL || arr->pElemArray != NULL) return arr->Size;
    return -1;
}

void PrintDB(PAdptArray arr) {
    if (arr == NULL) return;
    if (arr->pElemArray == NULL) return;
    for (int i = 0; i < arr->Size; i++){
        if(arr->pElemArray[i]!=NULL) arr->print(arr->pElemArray[i]);
    }
}
