Andrew Wu
Alex Rudnick
CSE13s

Homework 6 Design:

In homework 6, we will be using the Wordle vocabulary list we did in homework 5 and adding a checker for letter score and word scores. It will also remove words from the vocabulary list that do not have the guessed letter and words that do not have letters in the exact position the guess’s letter has. 

Functions:

Each function will have a checker for if the vocabulary[i] slot is NULL in their for loops that iterate through the vocabulary list. 

Score letter will loop over the vocabulary array and return the int number of words left in the vocabulary list that contains a particular letter. We will use a for loop that iterates num_words times and increment output int. 

int score_letter(char letter, char **vocabulary, size_t num_words) {
	Count = 0
	For i = 0, i<num_words(int) i++
		If vocabulary[i] not null:
		If vocabulary list [i] contains char letter
			Count ++
  return count;
}

Score_word will take a pointer to a word and contains an array of the 26 letters. It will return the int score for the word, which is the sum of the scores of all the letters in that word. We should again run a for loop, this time only running 26 times for the number of letters in the letter array and check to see if the word contains that letter. If it does, add to the output the score of each letter.  

int score_word(char *word, int *letter_scores) {
	Score = 0;
	For i = 0, i<26 i++
		Char Currentletter = 97+i;
		If word contains currentletter
			Score += letter_scores[i];
  return score;
}

Filter vocabulary gray will get rid of all the words in the vocabulary array with the specified letter in the function. We will use a for loop that goes through all of the vocabulary with size t num_words. If a word is detected with the ‘gray’ letter in it, we will free memory allocated to that word and set the pointer to NULL. We will then increment the output by 1, as the function returns the number of words freed. 

size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words) {
	Size_t words freed = 0
	For size_t i = 0, i<num_words,i++
If vocabulary[i] not null:
		If vocabulary[i] contains letter
			Char Delete_vocab = vocabulary[i]
			Vocabulary[i] = NULL
			free(delete_vocab)
			Words freed++
  return words freed;

}

Filter vocabulary yellow will get rid of all the words in the vocabulary array WITHOUT the specified letter and also the words that contain the letter at the specified position. We will use a for loop that goes through the vocabulary list of size_t num words and check to see if the word has the letter in it. If it does, we will check to see if the position that the letter is in matches the int position we get in our function header by using a for loop, iterating through the string. If it does, we free it and if it doesn’t, we keep it in. 

size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words) {
	Size_t words freed = 0
	For size_t i = 0, i<num_words,i++
		If vocabulary[i] not null:
		If vocabulary[i] does not contain letter
			Free vocab
		Else 
			Word = vocabulary[i]
			for(int i = 0; i<5; i++){
                			vocabletter = (word)[i];
				If vocabletter = letter
					If i = position
						Free vocab	
  return words freed;

}

Filter vocabulary green will get rid of all the words in the vocabulary array WITHOUT the specified letter at the specified position. We will use a for loop that goes through the vocabulary list of size_t num words and check to see if the word has the letter in it. If it does, we will check to see if the position that the letter is in matches the int position we get in our function header by using a for loop, iterating through the string. If it does not, we free it.

size_t filter_vocabulary_green(char letter, int position, char **vocabulary,size_t num_words) {
Size_t words freed = 0
	For size_t i = 0, i<num_words,i++
		If vocabulary[i] not null:
		If vocabulary[i] does not contain letter
			Free vocab
		else 
			Word = vocabulary[i]
			for(int i = 0; i<5; i++){
                			vocabletter = (word)[i];
				If vocabletter = letter
					If i != position
						Free vocab	
  return words freed;

}



