#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int infotype;
typedef struct TElmtList *address;
typedef struct TElmtList{
    infotype info;
    address next;
} ElmtList;

typedef struct List {
    address first;
};

bool IsEmpty(List L){
    return ((L).first == NULL);
}

void CreateEmpty(List *L){
    (*L).first = NULL;
}

void Deallocation(address hapus){
    free(hapus);
}

address Allocation(infotype x){
    address NewElmt;
    NewElmt = (ElmtList*) malloc (sizeof(ElmtList)); //biasanya keluar pas Ujian

    NewElmt->info = x;
    NewElmt->next = NULL;

    return NewElmt;
}

void InsertFirst(List *L, infotype x){
    address NewElmt;
    NewElmt = Allocation(x);

    if(NewElmt != NULL){
        NewElmt->next = (*L).first;
    }
    
    (*L).first = NewElmt;
}

void InsertAfter(address *PredElmt, infotype x){
    address NewElmt;
    NewElmt = Allocation(x);

    if(NewElmt != NULL){
        NewElmt->next = (*PredElmt)->next;
        (*PredElmt)->next = NewElmt;
    }
}

void InsertLast(List *L, infotype x){
    if(IsEmpty(*L)){
        InsertFirst(&(*L), x);
    } else {
        address temp;
        temp = (*L).first;
        while (temp->next != NULL){
            temp = temp->next;
        }
        InsertAfter(&temp, x);
    }
}

void DeleteFirst(List *L, infotype *hapus){
    if(!IsEmpty(*L)){
        address temp;
        temp = (*L).first;
        *hapus = temp->info;
        (*L).first = (*L).first->next;
        temp->next = NULL;
        Deallocation(temp);
    }
}

void DeleteAfter(address pred, infotype *hapus){
    if(pred->next != NULL){
        address temp;
        temp = pred->next;
        *hapus = temp->info;
        pred->next = temp->next;
        temp->next = NULL;
        Deallocation(temp);
    }
}

void DeleteLast(List *L, infotype *hapus){
    if(!IsEmpty(*L)){
        address temp, predTemp;
        predTemp = NULL;
        temp = (*L).first;
        while (temp->next != NULL){
            predTemp = temp;
            temp = temp->next;
        }

        if(temp == (*L).first){
            DeleteFirst(&(*L), &(*hapus));
        } else {
            DeleteAfter(predTemp, &(*hapus));
        }
    }
}

void insert_number(List *L, infotype angka){
	
}

int main(){
    address temp;
    List data;
    infotype tempHapus;

    CreateEmpty(&data);
    InsertLast(&data, 5);
    InsertLast(&data, 3);
    InsertLast(&data, 4);
    InsertLast(&data, 10);
    InsertLast(&data, 8);

    temp = data.first;
    while (temp != NULL){
        cout << temp->info << endl;

        temp = temp->next;
    }
}
