#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int score_letter(char letter, char **vocabulary, size_t num_words) {
	int count = 0;
	for(int i=0;i<(int)num_words;i++){
		if(vocabulary[i]!=NULL){
		if(strchr(vocabulary[i],letter)!=NULL)
			count++;
	}
	}
  return count;

}
int score_word(char *word, int *letter_scores) {
	int score =0;
	for(int i=0;i<26;i++){
		char currentletter=97+i;
		if(strchr(word,currentletter)!=NULL)
			score+=letter_scores[i];
	}
  return score;

}
char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}
size_t filter_vocabulary_gray(char letter, char **vocabulary,size_t num_words) {
	size_t words_freed = 0;
	for(int i=0; i<(int)num_words;i++){
		if(vocabulary[i]!=NULL){
		if(strchr(vocabulary[i],letter)!=NULL){
			char *delete_word = vocabulary[i];
			free(delete_word);
			vocabulary[i]=NULL;
			words_freed++;
		}
		}
	}
  return words_freed;
}
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,size_t num_words) {
	size_t words_freed = 0;
	for(int i =0;i<(int)num_words;i++){
		if(vocabulary[i]!=NULL){
		bool shouldfree= false;
		if(strchr(vocabulary[i],letter)==NULL)
			shouldfree=true;
		else {
			char *letterinword;
			int index;
			letterinword = strchr(vocabulary[i],letter);
			index = (int)(letterinword-vocabulary[i]);
			if(index==position)
				shouldfree= true;
		}
		if(shouldfree){
			char *delete_word = vocabulary[i];
                        free(delete_word);
                        vocabulary[i] = NULL;
                        words_freed++;
		}
	}
	}
  return words_freed;

}
size_t filter_vocabulary_green(char letter, int position, char **vocabulary,size_t num_words) {
        size_t words_freed = 0;
        for(int i =0;i<(int)num_words;i++){
		if(vocabulary[i]!=NULL){
		bool shouldfree=false;
                if(strchr(vocabulary[i],letter)==NULL)
                        shouldfree = true;
                else {
                        char *letterinword;
                        int index;
                        letterinword = strchr(vocabulary[i],letter);
                        index = (int)(letterinword-vocabulary[i]);
                        if(index!=position)
                                shouldfree = true;
                }
		if(shouldfree){
			char *delete_word = vocabulary[i];
                        free(delete_word);
			vocabulary[i]=NULL;
                        words_freed++;
		}
        }
	}
  return words_freed;

}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
