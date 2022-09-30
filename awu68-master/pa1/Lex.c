#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#define SIZE 500
int main(int argc, char **argv){
	if(argc!=3){
		fprintf(stderr, "usage: ./Lex <inputfile> <outputfile>");
		exit(1);
	}
	FILE *infile=fopen(argv[1],"r");
	int n =0;
	char buf[SIZE];
	while(fgets(buf,SIZE,infile)!=NULL){
		n++;
	}
	fclose(infile);
	char**stringarray=malloc(n*sizeof(char*));
	FILE *infile2=fopen(argv[1],"r");
	int count = 0;
	char str[SIZE];
	while(fgets(str,SIZE,infile2)!=NULL){
		stringarray[count]=malloc(SIZE*sizeof(char*));
		strcpy(stringarray[count],str);
		count++;
	}
	fclose(infile2);
	List list = newList();
	append(list,0);
	moveFront(list);
	bool hi = true;
	for(int i=1;i<n;i++){
		hi = true;
		if(strcmp(stringarray[i],stringarray[get(list)])<0){
			while(strcmp(stringarray[i],stringarray[get(list)])<0){
				movePrev(list);
				if(index(list)==-1){
                                        prepend(list,i);
                                        moveFront(list);
                                        hi = false;
                                }
			}
			if(hi)
				insertAfter(list,i);
		}
		else if(strcmp(stringarray[i],stringarray[get(list)])>0){
			while(strcmp(stringarray[i],stringarray[get(list)])>0){
                                moveNext(list);
				if(index(list)==-1){
					append(list,i);
                                       moveBack(list);
                                       hi = false;
                                }
                        }
			if(hi)
                        	insertBefore(list,i);
		}
		else if(strcmp(stringarray[i],stringarray[get(list)])==0){
			insertBefore(list,i);
		}
	}
	moveFront(list);
	FILE *output = fopen(argv[2],"w");
	while(index(list)!=-1){
		int a = get(list);
		fputs(stringarray[a],output);
		moveNext(list);
	}
	fclose(output);
	for(int i=0;i<n;i++){
		char *strptr = stringarray[i];
		free(strptr);
	}
	char **strptr2 = stringarray;
	free(strptr2);
	freeList(&list);
}
