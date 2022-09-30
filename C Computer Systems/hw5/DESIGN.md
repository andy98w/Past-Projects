Andrew Wu
Alex Rudnick
CSE 13s

In this lab, we will be programming Wordle which takes a user input of 5 letters. Users will have to guess the correct 5 letter word. It will return green if the user’s word has a matching letter in the correct slot of the answer word in the position of the correct letter, gray if the user’s word does not have that letter in the answer word, and yellow if the user’s word has the same letter as the answer word but not in the correct slot. We will be opening a vocabulary file and picking the answer word from there, and freeing and allocating memory along the way. We have 4 functions to program in our hw5.c file, which is the only executable in this lab.   

Score guess takes the answer word, the user input’s guess, and returns a bool. The result is how close the user was to the answer, which is also stored in a 5 character string. Depending on the user’s input, the result will have a different letter in each of its character slots out of 3. ‘X’ means the user’s letter is not in the answer word, ‘Y’ means the user’s letter is in the answer word but not in the correct spot, and ‘G’ if the user’s letter is in the correct spot of the secret word. It will run a for loop that checks all 5 of the user’s letters. 

PSEUDOCODE:
bool score_guess(char *secret, char *guess, char *result) {
Result = 0
Char letter, secretletter
Char tmp allocate memory of 6
Tmp = 0
For loop 5 times
		Set secret letter to i’th character of secret, set letter to i’th letter of guess
		If letter = secretletter
			Concatenate tmp with g
		Else
			If secret contains letter
				Concatenate tmp with y
			Else
				Concatenate tmp with x
		Set result to tmp
		Free tmp
		If result = ggggg
			Return true
  	return false;
}

Valid guess takes a pointer to a string guess, the vocabulary list, and the number of words in that list. This is simple, as all we need to do is check the vocabulary list for the guess word.

PSEUDOCODE:
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  If guess length is not 5
	Return false
	For int i =0, i< num words, i++
		If vocabulary[i] = guess
			Return true
Return false
}

In load_vocabulary we will open the text file stored in the hw5 directory and store all the values into an array of chars, (char**). Each element points to a char*, which will be dynamically allocated. I was thinking of using a for loop to realloc for each time it runs through the loop. To read the file, use strdup. We will fclose after this for loop and return the result. 
PSEUDOCODE:
char **load_vocabulary(char *filename, size_t *num_words) {
	Char buf
	Char **out
	Out = malloc
	Open file vocabulary.txt
	While buf != null
		Out reallocate memory
		Out[i] = allocate memory
		Set out[i] to buf
		Increment i
	Close file
	Set num words to i
  return out;
}
For free, we will run a for loop that frees memory associated with the vocabulary array of pointers to char*’s. It returns void 

PSEUDOCODE:
void free_vocabulary(char **vocabulary, size_t num_words) {
	Pointer ** to vocabulary
	While vocabulary not null	
		Pointer to vocabulary[0]
		Free pointer
	Free vocabulary
}





