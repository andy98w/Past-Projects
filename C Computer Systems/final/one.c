#include "final.h"

#include <stdio.h>

size_t word_count(char *text) {
  size_t count = 0;
  for(int i=0;text[i]!='\0';i++){
	  if(text[i]>='A'&&text[i]<='z'){
		  if(text[i-1]<'A'||text[i-1]>'z')
			  count++;
	  }
  }
  return count;
}
