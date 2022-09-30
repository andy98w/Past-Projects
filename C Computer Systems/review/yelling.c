#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
   if(argc>2){
	   fprintf(stderr, "usage: ./yelling <inputfile.txt>\n");
	   return 0;
   }
   if(argc==2){
	   char *out = calloc(1000,sizeof(char));
	   FILE *infile=fopen(argv[1],"r");
	   if(infile==NULL){
		   fprintf(stderr, "Could not open input file\n");
		   return 0;
	   }
	   while(1){
		 char c = fgetc(infile);
		 char s[1];
		 if(c == EOF)
			break;
		 if(c >= 'a' && c<='z'){
			 c = c-32;
			 sprintf(s,"%c",c);
			 strncat(out,s,1);
		 }
		 else
			 sprintf(s,"%c",c);
			 strncat(out,s,1);
	   }
	   fclose(infile);
	   FILE *outfile = fopen(argv[1],"w");
	   fputs(out,outfile);
	   fclose(outfile);
	   return 0;
   }
   else{
	char s[500];
   	printf("Enter a string : ");
   	scanf("%[^\n]s",s);
   	for (int i = 0; s[i]!='\0'; i++) {
      		if(s[i] >= 'a' && s[i] <= 'z') 
         		s[i] = s[i] - 32;
   	}
	printf("yelling: %s",s);
	puts("");
  	return 0;
   }
}
