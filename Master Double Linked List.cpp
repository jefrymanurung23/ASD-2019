#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int infotype;
typedef struct tElmtList *address;

typedef struct tElmtList {
	infotype info;
	address prev;
	address next;
} ElmtList;

typedef struct List {
	address First;
	address Last;
};

#define Info(P) (P)->info
#define Prev(P) (P)->prev
#define Next(P) (P)->next
#define First(L) ((L).First)
#define Last(L) ((L).Last)

bool IsEmpty(List L) {
	return (First(L) == NULL) && (Last(L) == NULL);
}

bool IsOneElement(List L){
	return (First(L) == Last(L));
}

void CreateEmpty(List *L) {
	First(*L) = NULL;
	Last(*L) = NULL;
}

void Deallocation(address hapus) {
	free(hapus);
}

address Allocation(infotype x) {
	address NewElmt;
	NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
	NewElmt->info = x;
	NewElmt->next = NULL;
	NewElmt->prev = NULL;

	return NewElmt;
}

void InsertFirst(List *L, infotype x){
	/* I.S. Sembarang kondisi list, dan diberikan nilai yang akan disimpan */
	/* F.S. Menambahkan elemen ber-nilai x sebagai elemen pertama */
	address NewElmt;
    NewElmt = Allocation(x);

    if(!IsEmpty(*L)){
        Prev(First(*L)) = NewElmt;
    	Next(NewElmt) = First(*L);
    }else{
    	Last(*L) = NewElmt;
	}
	First(*L) = NewElmt;
}

void InsertAfter(List *L, address *PredElmt, infotype x){
	/* I.S. Sembarang kondisi list, PredElmt pastilah elemen list; diberikan
	suatu nilai yang akan di simpan*/
	/* F.S. Insert elemen yang bernilai x sesudah elemen beralamat PredElmt */
	address NewElmt;
    NewElmt = Allocation(x);

    if(!IsEmpty(*L)){
    	Next(NewElmt) = Next(*PredElmt);
    	Prev(NewElmt) = (*PredElmt);
    	Prev(Next(*PredElmt)) = NewElmt;
        Next(*PredElmt) = NewElmt;
    }else{
    	InsertFirst(L, x);
	}
}

void InsertLast(List *L, infotype x){
	/* I.S. Sembarang konisi list, dan diberikan nilai yang akan disimpan */
	/* F.S. Elemen dengan nilai x ditambahkan sebagai elemen terakhir yang baru */
	address NewElmt;
    NewElmt = Allocation(x);
    
    if(!IsEmpty(*L)){
        Prev(NewElmt) = Last(*L);
		Next(Last(*L)) = NewElmt;
    }else{
    	First(*L) = NewElmt;
	}
    Last(*L) = NewElmt;
}

void InsertAfter(List *L, infotype element, infotype x){
	/* I.S. Sembarang kondisi list, PredElmt pastilah elemen list; diberikan
	suatu nilai yang akan di simpan*/
	/* F.S. Insert elemen yang bernilai x sesudah elemen beralamat PredElmt */
	address NewElmt;
    NewElmt = Allocation(x);

	if(IsEmpty(*L)){
		cout<<"could not insert"<<endl;
	}else if(IsOneElement(*L)){
    	if(Info(First(*L)) != element){
            cout<<"could not insert"<<endl;
        }
        InsertLast(L, x);
    }else if(Info(Last(*L)) == element){
    	InsertLast(L, x);
	}else{
		address temp = First(*L);
    	
		while (Info(temp) != element){
        	temp = Next(temp);
        
			if(temp == NULL){
            	cout<<"Could not insert"<<endl;
            	cout<<"element not found"<<endl;
            	break;
        	}
    	}
    	
    	if(temp != NULL){
    		Next(NewElmt) = Next(temp);
	    	Prev(NewElmt) = temp;
	    	Prev(Next(temp)) = NewElmt;
	    	Next(temp) = NewElmt;	
		}	
	}
}

void InsertBefore(List *L, infotype element, infotype x){
	/* I.S. Sembarang kondisi list, PredElmt pastilah elemen list; diberikan
	suatu nilai yang akan di simpan*/
	/* F.S. Insert elemen yang bernilai x sesudah elemen beralamat PredElmt */
	address NewElmt;
    NewElmt = Allocation(x);

	if(IsEmpty(*L)){
		cout<<"could not insert"<<endl;
	}else if(IsOneElement(*L)){
    	if(Info(First(*L)) != element){
            cout<<"could not insert"<<endl;
        }
        InsertFirst(L, x);
    }else if(Info(First(*L)) == element){
    	InsertFirst(L, x);
	}else{
		address temp = First(*L);
    	
		while (Info(temp) != element){
        	temp = Next(temp);
        
			if(temp == NULL){
            	cout<<"Could not insert"<<endl;
            	cout<<"element not found"<<endl;
            	break;
        	}
    	}
    	
    	if(temp != NULL){
    		Next(NewElmt) = temp;
			Prev(NewElmt) = Prev(temp);
			Next(Prev(temp)) = NewElmt;
	    	Prev(temp) = NewElmt;	
		}
	}
}

void DeleteFirst(List *L, infotype *hapus) {
	/* I.S. List tidak kosong, dan terdapat media untuk menyimpan angka yang dihapus */
	/* F.S. *hapus akan menyimpan nilai dari elemen pertama list sebelum penghapusan */
	/* Elemen list berkurang satu (mungkin menjadi kosong) */
	/* First element yg baru adalah suksesor elemen pertama yang lama */
	
	if(IsOneElement(*L)){
        address cur;
        cur = First(*L);
        *hapus = Info(cur);
        First(*L) = NULL;
        Last(*L) = NULL;
		free(cur);
    }else{
    	address cur;
    	cur = First(*L);
        *hapus = Info(cur);
        First(*L) = Next(First(*L));
        Prev(First(*L)) = NULL;
		free(cur);
    }
}

void DeleteLast(List *L, infotype *hapus) {
	/* I.S. List tidak kosong, dan terdapat media untuk menyimpan angka yang dihapus */
	/* F.S. *hapus akan menyimpan nilai dari elemen terakhir list sebelum penghapusan */
	/* Elemen list berkurang satu (mungkin menjadi kosong) */
	/* Last element yg baru adalah predesesor dari elemen terakhir yang lama */
    if(IsOneElement(*L)){
        address cur;
        cur = First(*L);
        *hapus = Info(cur);
        First(*L) = NULL;
        Last(*L) = NULL;
		free(cur);
    }else{
    	address cur;
    	cur = Last(*L);
        *hapus = Info(cur);
        Last(*L) = Prev(Last(*L));
        Next(Last(*L)) = NULL;
		free(cur);
    }
}

void DeleteAfter(List *L, infotype element, infotype *hapus) {
	/* I.S. List tidak kosong. Pred adalah anggota list.
	Next(Pred) != Nil */
	/* F.S. Menghapus Next(Pred): */
	/* *hapus akan menyimpan nilai dari elemen yang akan dihapus */
	
    if(IsOneElement(*L)){
        if(Info(First(*L)) != element){
            cout<<"could not delete"<<endl;
        }
        address temp;
		temp = First(*L);
        First(*L) = NULL;
        Last(*L) = NULL;
        *hapus = Info(temp);
        free(temp);
    }else{
    	address temp;
		temp = First(*L);
	
		while(Info(temp) != element){
        	temp = Next(temp);
        	
			if(temp == NULL){
            	cout<<"element not found"<<endl;
        	}
   	 	}
    	
    	temp = Next(temp);
    	
    	if(temp != NULL){
    		if(Info(temp) == Info(Last(*L))){
    			DeleteLast(L, hapus);
			}else{
    			Prev(Next(temp)) = Prev(temp);
    			Next(Prev(temp)) = Next(temp);
				*hapus = Info(temp);
				free(temp);
			}	
		}	
	}
}

int main(){
	address temp;
    List data;
    infotype tempHapus;

    CreateEmpty(&data);
    InsertLast(&data, 5);
    InsertLast(&data, 3);
    InsertLast(&data, 8);
    InsertAfter(&data, 3, 4);
    

    temp = First(data);
    while (temp != NULL){
        cout << Info(temp) << "-> ";

        temp = Next(temp);
    }
    
    cout << endl;
    DeleteAfter(&data, 4, &tempHapus);
    temp = First(data);
    while (temp != NULL){
        cout << Info(temp) << "-> ";

        temp = Next(temp);
    }
    
    cout << endl;
    cout << "Data yang dihapus = " << tempHapus;
}
