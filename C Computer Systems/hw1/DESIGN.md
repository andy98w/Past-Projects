Andrew Wu
Design doc assignment 1
CSE 13S
Alexander Rudnick

We are given:
A makefile
A template code
A names document

This code will be used to run simulations for the game Pass the Pigs. The game will involve players taking turns rolling a pig, and the winner will depend on the first player to reach 100 points. The player marks the end of their turn when they roll the pig on its side, otherwise their turn will keep going. It is possible for a player to win in 1 turn. There will be user input for the number of players as well as a seed to run the random number generator, which will randomly generate an integer between 0 and 6 inclusive, which will determine the players roll. 

This code should be essentially divided into 3 major parts. First, we must collect the user input. Second, we need to process the user input and match the amount of players entered to the names on the name document and use the seed on the random number generator. Finally, we run the simulation and print the output.

The absolute very first thing we need to do is include <studio.h> and <stdlib.h> to use the random functions, as well as the names file. We should also include the enumerations for the pig sides with the given code in the document.

The first section of the code should be the easiest. The requirements for the number of players is that it should be an integer between 2 and 10. In the event that either a non-integer is entered or that integer is not between 2 and 10 is entered, we will print an error message to stderr and default players to 2. For this we are given the code from the assignment document that essentially gives us the error statement, and the code for scanning input.
##Pseudocode:
Int numberofplayers=0; #declare the integer
Print: “Enter number of players”
scanf(“%s”, numberofplayers) #scans for user input 
If numberofplayers=/=int or >2 or <10:
	Print: errormessage to stderr
	numberofplayers=2 #sets the number of players to 2
The random seed input follows the same idea. If a non-integer is entered, we will default the value to 2021 and print an error message.
Int seed=0; #declares seed as variable
printf(“enter seed”)
scanf(seed) #scans for user input
If seed=/=int:
	Print: errormessage #stderr
	seed=2021 #sets seed to 2021

Now, assuming that the seed and the number of players is correct, we can proceed to the next section of code. We will enumerate the positions of the pig with the code provided in the document. 
Next, use the seed from the input.
Set random (seed) #this will set the random function to the correct seed

I also thought it would be helpful to create a new array of size numberofplayers to keep record of the score. 
Array scores[numberofplayers] #declares an array equal to length of the number of players

Finally, now that we have the array with all participating players as well as the seed, we can start the simulation. I was thinking we could use a for loop, a while loop, and a few conditionals to move to the next turn, with each conditional testing for whether a side has been rolled, or the player has reached 100 points. The side roll conditional would exit the first for loop, thus moving to the next player, while the index of the scores array would check if the player reached over 100 points. I also thought to put a conditional after the for loop to check if “i (the counter)” has reached numberofplayers-1, which would reset “i’ to 0.

Int i
For(i<numberofplayers, i++): #loop that runs through the players
	printf(listofplayers[i]+”Rolls the pig…”
	While true: #infinite loop until a break or exit is called
		thing=array[random(0-6)] #random variable that is enumerated to one of the positions in the pig.
		If thing=SIDE: 
			print(“pig lands on side”)
			Exit #exit for loop, goes back to top for next player
		If thing=RAZORBACK
			scores[i]+=10
			print(“pig lands on back”)
		If thing=TROTTER
			scores[i]+=10
			print(“pig lands upright”)
		If thing=SNOUTER
			scores[i]+=15
			print(“pig lands on snout”)
		If thing=JOWLER
			scores[i]+=5
			print(“pig lands on ear”)
		If scores[i]>=100: #if a player were to reach more than 100 points
			printf(listofplayers[i]+”wins with 100 points!”)
			exit(0) #last thing for the code
	If i=numberofplayers-1: #conditional for when last player is called, the first player gets to go again. I used -1 because it would increment back to 0.
		i=-1
	#goes back to top

