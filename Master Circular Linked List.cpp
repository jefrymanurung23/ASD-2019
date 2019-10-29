#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
infotype info;
address next;
} ElmtList;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last,
maka Next(Last) = First */

typedef struct {
	address First;
} List;

/* Selektor */
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

void createEmpty(List *L){
    First(*L) = NULL;
}

bool isEmpty(List L){
    return (First(L) == NULL);
}

bool IsOneElmt(List L){
    return (Next(First(L)) == First(L));
}

void Deallocation(address hapus){
    free(hapus);
}

address Allocation(infotype x){
    address P;
    P = (ElmtList*) malloc (sizeof(ElmtList));

    Info(P) = x;
    Next(P) = NULL;

    return P;
}

address findLast(List L){
	address P;
	P = First(L);
	
	if(isEmpty(L)){
		return NULL;
	}else{
		while(Next(P) != First(L)){
			P = Next(P);
		}
		return P;
	}
}

address prevNode(List L, address P){
	address temp;
	temp = First(L);
	
	while(Next(temp) != P){
		temp = Next(temp);
	}
	return temp;
}

void insertFirst(List *L, infotype x){
	address P = Allocation(x);
	
	if(isEmpty(*L)){
		First(*L) = P;
		Next(First(*L)) = First(*L);
	}else{
		address last = findLast(*L);
		Next(P) = First(*L);
		First(*L) = P;
		Next(last) = First(*L);
	}
}

void insertAfter(address *PredElmt, infotype x){
	address P = Allocation(x);
	
	Next(P) = Next(*PredElmt);
    Next(*PredElmt) = P;
}

void insertLast(List *L, infotype x){
	address P = Allocation(x);
	
	if(isEmpty(*L)){
		insertFirst(&(*L), x);
	}else{
		address last = findLast(*L);
		Next(last) = P;
		Next(P) = First(*L);
	}
}

void deleteFirst(List *L, infotype *hapus){
	if(!isEmpty(*L)){
		address last = findLast(*L);
		address P = First(*L);
		*hapus = Info(P);
		First(*L) = Next(First(*L));
		Next(last) = First(*L);
		
		Deallocation(P);
	}
}

void deleteAfter(address pred, infotype *hapus){
	address temp;
    temp = Next(pred);
    *hapus = Info(temp);
        
	Next(pred) = Next(temp);
    Next(temp) = NULL;
        
    Deallocation(temp);
}

void deleteLast(List *L, infotype *hapus){
	if(!isEmpty(*L)){
        address last = findLast(*L);
        *hapus = Info(last);
        address prevLast = prevNode(*L, last);
        
        Next(prevLast) = First(*L);
        Next(last) = NULL;
		Deallocation(last);
    }
}

void print(List L){
	if(!isEmpty(L)){
		address P = First(L);
		
		do{
			cout << Info(P) << " ";
			P = Next(P);
		}while(P != First(L));
	}
}

int main(){
	List L;
	createEmpty(&L);
	insertFirst(&L, 3);
	insertFirst(&L, 5);
	insertFirst(&L, 1);
	insertLast(&L, 2);
	
	address temp = First(L);
    while (Next(temp) != First(L)){
        if(Info(temp) == 3){
        	insertAfter(&temp, 6);
        	break;
		}else{
			temp = temp->next;	
		}
    }
    
    int hapus;
//  deleteFirst(&L, &hapus);
//	deleteLast(&L, &hapus);
	
	temp = First(L);
    while (Next(temp) != First(L)){
        if(Info(temp) == 5){
        	deleteAfter(temp, &hapus);
        	break;
		}else{
			temp = temp->next;	
		}
    }
	print(L);
}
