#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFSIZE 2048
 bool score_guess(char *secret, char *guess, char *result) {
	*result='\0';
	char letter;
	char secretletter;
	char *tmp;
	tmp = malloc(6);
	*tmp = '\0';
	for(int i = 0; i<5; i++){
                letter = (guess)[i];
                secretletter = (secret)[i];
		if(letter==secretletter)
			strcat(tmp,"g");
		else{
			if(strchr(secret,letter))
				strcat(tmp,"y");
			else
				strcat(tmp,"x");
		}
	}
	strcpy(result,tmp);
	free(tmp);
	if(strcmp(result, "ggggg")==0)
		return true;
	else
		return false;
}
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
	if(strlen(guess)!=5){
		return false;
	}
  for(int i =0; i<(int)num_words; i++){
	  char *ptr = vocabulary[i];
	  if(strcmp(guess,ptr))
		  return true;
  }
  return false;
}
char **load_vocabulary(char *filename, size_t *num_words) {
	char buf[BUFSIZE];
	char **out;
	out = malloc(1);
	FILE* infile;
	infile=fopen(filename, "r");
	int i = 0;
	while((fgets(buf, BUFSIZE, infile) != NULL)){
		out = realloc(out,(i+1)*10);
		(out)[i] = strndup(buf,5);
		i++;
	}
	fclose(infile);
	*num_words =(size_t)i;
	return out;
}
void free_vocabulary(char **vocabulary, size_t num_words) {
	char **delete_vocab = vocabulary;
	for(int i = 0; i<(int)num_words; i++){
		char *delete_word = vocabulary[i];
		free(delete_word);
	}
	free(delete_vocab);
}
int main(void) {
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;
  srand(time(NULL));
  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);
  // Randomly select one of the words from the file to be today's SECRET WORD.
  int word_index = rand() % num_words;
  char *secret = vocabulary[word_index];
  char guess[80];
  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;
  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }
    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';
    if (!valid_guess(guess, vocabulary, num_words)) {
      printf("not a valid guess\n");
      continue;
    } else {
      num_guesses++;
    }
    success = score_guess(secret, guess, result);
    printf("%s\n", guess);
    printf("%s\n", result);
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);
  return 0;
}
