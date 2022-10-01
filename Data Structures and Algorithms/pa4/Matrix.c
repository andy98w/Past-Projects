/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#4 
* Matrix.c
* Main File for Matrix ADT
*********************************************************************************/
#include "Matrix.h"
typedef struct EntryObj* Entry;
typedef struct EntryObj{
        int column;
        double val;
}EntryObj;
typedef struct MatrixObj{
        List *lists;
        int NNZ;
        int size;
}MatrixObj;
Matrix newMatrix(int n){
	Matrix m = (Matrix)malloc(sizeof(MatrixObj));
	m->lists=(List*)malloc((n+1)*sizeof(List*));
	m->size=n;
	m->NNZ=0;
	for(int i=1;i<=n;i++){
		m->lists[i]=newList();
	}
	return m;
}
Entry newEntry(int j, double x){
	Entry e = (Entry)malloc(sizeof(EntryObj));
	e->column = j;
	e->val = x;
	return e;
}
void freeEntry(Entry *pE){
	free(*pE);
	*pE=NULL;
}
void freeMatrix(Matrix* pM){
	for(int i = 1; i<=size(*pM);i++){
		moveFront((*pM)->lists[i]);
		for(int j=1;j<=length((*pM)->lists[i]);j++){
			Entry e = get((*pM)->lists[i]);
			moveNext((*pM)->lists[i]);
			freeEntry(&e);
		}
		freeList(&(*pM)->lists[i]);
	}
	free((*pM)->lists);
	free(*pM);
}
int size(Matrix M){
	return M->size;
}
int NNZ(Matrix M){
	return M->NNZ;
}
int equals(Matrix A, Matrix B){
	int out = 1;
	Matrix D = copy(B);
	if(A->NNZ!=D->NNZ){
		freeMatrix(&D);
		return 0;
	}
	if(A->size!=D->size){
		freeMatrix(&D);
		return 0;
	}
	for(int i =1;i<=A->size;i++){
		if(length(A->lists[i])!=0&&length(D->lists[i])!=0){
			moveFront(A->lists[i]);
			moveFront(D->lists[i]);
			if(length(A->lists[i])!=length(D->lists[i])){
				freeMatrix(&D);
				return 0;
			}
			Entry x, y;
			for(int j = 1;j<=length(A->lists[i]);j++){
				x = get(A->lists[i]);
				y = get(D->lists[i]);
				if(x->val!=y->val||x->column!=y->column){
					freeMatrix(&D);
					return 0;
				}
				moveNext(A->lists[i]);
				moveNext(D->lists[i]);
			}
		}
		else if(length(A->lists[i])!=0&&length(D->lists[i])==0){
			freeMatrix(&D);
			return 0;
		}
		else if(length(A->lists[i])==0&&length(D->lists[i])!=0){
			freeMatrix(&D);
			return 0;
		}
	}
	freeMatrix(&D);
	return out;
}
void makeZero(Matrix M){
	for(int i = 1;i<=size(M);i++){
		if(length(M->lists[i])!=0){
	        	moveFront(M->lists[i]);
               		for(int j=1;j<=length(M->lists[i]);j++){
                       		Entry e = get(M->lists[i]);
                        	moveNext(M->lists[i]);
                        	freeEntry(&e);
                	}
		}
		freeList(&(M->lists[i]));
	}	
	for(int i=1;i<=M->size;i++){
                M->lists[i]=newList();
        }
	M->NNZ=0;
}
void changeEntry(Matrix M, int i, int j, double x){
	bool boo = false;
	bool boo2 = false;
	if(length(M->lists[i])==0){
		if(x==0){
			return;
		}
		Entry y = newEntry(j,x);
		append(M->lists[i],y);
		M->NNZ++;
		return;
	}
	moveFront(M->lists[i]);
	Entry z = get(M->lists[i]);
	while(z->column<j){
		moveNext(M->lists[i]);
		z = get(M->lists[i]);
		if(index(M->lists[i])==-1){
			boo =  true;
			break;
		}
		if(z->column==j){
			boo2= true;
			break;
		}
	}
	if(boo){
		if(x==0){
			return;
		}
		Entry y = newEntry(j,x);
		append(M->lists[i],y);
		M->NNZ++;
		return;
	}
	else if(boo2){
		if(x==0){
			Entry x = get(M->lists[i]);
			freeEntry(&x);
			delete(M->lists[i]);
			M->NNZ=M->NNZ-1;
			return;
		}else{
			Entry y = newEntry(j,x);
			insertBefore(M->lists[i],y);
			Entry z = get(M->lists[i]);
			freeEntry(&z);
			delete(M->lists[i]);
			return;
		}
	}
	else{
		if(x==0){
			moveFront(M->lists[i]);
			Entry x = get(M->lists[i]);
			if(x->column==j){
				freeEntry(&x);
				delete(M->lists[i]);
				M->NNZ=M->NNZ-1;
				return;
			}
			else{
				return;
			}
		}
		Entry y = newEntry(j,x);
                insertBefore(M->lists[i],y);
                M->NNZ++;
		if(j==z->column){
			freeEntry(&z);
			delete(M->lists[i]);
			M->NNZ--;
		}
	}
}
Matrix copy(Matrix A){
	Matrix B = newMatrix(A->size);
	for(int i =1;i<=size(A);i++){
		if(length(A->lists[i])!=0){
			moveFront(A->lists[i]);
			Entry a = get(A->lists[i]);
			while(a!=NULL){
				changeEntry(B,i,a->column,a->val);
				moveNext(A->lists[i]);
				a = get(A->lists[i]);
			}
		}
	}
	return B;
}
Matrix transpose(Matrix A){
	Matrix B = newMatrix(A->size);
	for(int i =1;i<=size(A);i++){
		if(length(A->lists[i])!=0){
                moveFront(A->lists[i]);
                for(int j=1;j<=length(A->lists[i]);j++){
			Entry a = get(A->lists[i]);
                        changeEntry(B,a->column,i,a->val);
                        moveNext(A->lists[i]);
                }
		}
	}
        return B;
}
Matrix scalarMult(double x, Matrix A){
	Matrix B = newMatrix(A->size);
	for(int i =1;i<=size(A);i++){
		if(length(A->lists[i])!=0){
                	moveFront(A->lists[i]);
                	for(int j=1;j<=length(A->lists[i]);j++){
				Entry a = get(A->lists[i]);
				Entry b = newEntry(a->column,(x)*a->val);
				if(b->val==0){
					freeEntry(&b);
					continue;
				}
				else{
                        		append(B->lists[i],b);
					B->NNZ++;
                        		moveNext(A->lists[i]);
				}
                	}
		}
	}
        return B;
}
Matrix sum(Matrix A, Matrix B){
        Matrix D = copy(B);
        Matrix C = newMatrix(A->size);
        for(int i =1;i<=size(A);i++){
                if(length(A->lists[i])!=0&&length(D->lists[i])!=0){
			moveFront(A->lists[i]);
                	moveFront(D->lists[i]);
                        Entry a,b;
                        a = get(A->lists[i]);
                        b = get(D->lists[i]);
                        while(a!=NULL||b!=NULL){
                                int acol,bcol;
                                if(a==NULL)
                                        acol=size(B)+1;
                                else if(b==NULL)
                                        bcol=size(A)+1;
                                else{
                                        acol=a->column;
                                        bcol=b->column;
                                }
                                if(acol<bcol){
                                        changeEntry(C,i,a->column,a->val);
                                        moveNext(A->lists[i]);
                                }
                                else if(acol>bcol){
                                        changeEntry(C,i,b->column,b->val);
                                        moveNext(D->lists[i]);
                                }
                                else if(acol==bcol){
					Entry z = newEntry(a->column,a->val+b->val);
					if(z->val==0){
						freeEntry(&z);
					}
					else{
                                        	append(C->lists[i],z);
						C->NNZ++;
					}
					moveNext(A->lists[i]);
                                        moveNext(D->lists[i]);
                                }
                                a = get(A->lists[i]);
                                b = get(D->lists[i]);
                        }
                }
                else if(length(A->lists[i])==0&&length(D->lists[i])!=0){
			moveFront(D->lists[i]);
                        for(int j=1;j<=length(D->lists[i]);j++){
                                Entry b = get(D->lists[i]);
                                changeEntry(C,i,b->column,b->val);
				moveNext(D->lists[i]);
                        }
                }
                else if(length(A->lists[i])!=0&&length(D->lists[i])==0){
			moveFront(A->lists[i]);
                        for(int j=1;j<=length(A->lists[i]);j++){
                                Entry a = get(A->lists[i]);
                                changeEntry(C,i,a->column,a->val);
				moveNext(A->lists[i]);
                        }
                }
        }
        freeMatrix(&D);
        return C;
}
Matrix diff(Matrix A, Matrix B){
	Matrix D = copy(B);
	Matrix C = newMatrix(A->size);
        for(int i =1;i<=size(A);i++){
                moveFront(A->lists[i]);
                moveFront(D->lists[i]);
                if(length(A->lists[i])!=0&&length(D->lists[i])!=0){
                        Entry a,b;
			a = get(A->lists[i]);
			b = get(D->lists[i]);
			while(a!=NULL||b!=NULL){
                                int acol,bcol;
                                if(a==NULL)
                                        acol=size(B)+1;
                                else if(b==NULL)
                                        bcol=size(A)+1;
                                else{
                                        acol=a->column;
                                        bcol=b->column;
                                }
                                if(acol<bcol){
                                        changeEntry(C,i,a->column,a->val);
                                        moveNext(A->lists[i]);
                                }
                                else if(acol>bcol){
                                        changeEntry(C,i,b->column,-(b->val));
                                        moveNext(D->lists[i]);
                                }
                                else if(acol==bcol){
                                        changeEntry(C,i,a->column,(a->val)-(b->val));
                                        moveNext(A->lists[i]);
                                        moveNext(D->lists[i]);
                                }
			        a = get(A->lists[i]);
                                b = get(D->lists[i]);
                        }
                }
                else if(length(A->lists[i])==0&&length(D->lists[i])!=0){
			moveFront(D->lists[i]);
                        for(int j=1;j<=length(D->lists[i]);j++){
                                Entry b = get(D->lists[i]);
                                changeEntry(C,i,b->column,-(b->val));
				moveNext(D->lists[i]);
                        }
                }
                else if(length(A->lists[i])!=0&&length(D->lists[i])==0){
			moveFront(A->lists[i]);
                        for(int j=1;j<=length(A->lists[i]);j++){
                                Entry a = get(A->lists[i]);
                                changeEntry(C,i,a->column,a->val);
				moveNext(A->lists[i]);
                        }
                }
        }
	freeMatrix(&D);
        return C;
}
double vectorDot(List P, List Q){
	moveFront(P);
	moveFront(Q);
	double d = 0.0;
	if(length(P)==0||length(Q)==0){
		return 0;
	}
	else if(length(Q)!=0&&length(P)!=0){
		Entry a, b;
		a = get(P);
		b = get(Q);
		while(a!=NULL&&b!=NULL){
			int acol,bcol;
                        if(a==NULL)
                                acol=length(Q)+1;
                        else if(b==NULL)
                                bcol=length(P)+1;
                        else{
                                acol=a->column;
                                bcol=b->column;
                        }
                        if(acol<bcol){
                                moveNext(P);
                        }
                        else if(acol>bcol){
                                moveNext(Q);
                        }
                        else if(acol==bcol){
				d+=(b->val)*(a->val);
                                moveNext(P);
                                moveNext(Q);
                        }
		        a = get(P);
                        b = get(Q);
		}
	}
	return d;
}
Matrix product(Matrix A, Matrix B){
        Matrix C = newMatrix(A->size);
	Matrix D = transpose(B);
        for(int i =1;i<=size(A);i++){
                for(int j=1;j<=size(A);j++){
                        changeEntry(C,i,j,vectorDot(A->lists[i],D->lists[j]));
                }
        }
	freeMatrix(&D);
        return C;
}
void printMatrix(FILE* out, Matrix M){
	if(M->NNZ==0){
		return;
	}
	for(int i =1;i<=M->size;i++){
		if(length(M->lists[i])!=0){
			fprintf(out,"%d: ",i);
			moveFront(M->lists[i]);
			Entry x = get(M->lists[i]);
			while(x!=NULL){
				fprintf(out," (%d, %0.1f)",x->column,x->val);
				moveNext(M->lists[i]);
				x = get(M->lists[i]);
			}
			fprintf(out,"\n");
		}
	}
}
