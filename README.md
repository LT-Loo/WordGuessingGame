## Introduction
This is a simple word guessing game where players guess the word chosen by guessing a letter each time within a limited guessing rounds.

## Technology Used
Language: C++

## How To Play
1. Execute the program using the command line below:
```
[Output filename] [Word Length] [Max number of allowed guesses]
```
2. Enter a letter each round until correctly guessing the word or running out of guesses. Enjoy the game!

## How The Program Runs
1. Once the game program receives the word length and maximum number of allowed guesses from the command line, it constructs a list of all words whose length matches the input length.
2. It prompts the player to enter a letter.
3. After receiving the letter input, it divides the word list into categories according to the placement of the letter input in the words.
4. The largest category is chosen and words that aren't in that category are removed from the word list.
5. It prints out how many guesses the user has remaining, along with any letters the player has guessed, the current blanked-out version of the word and the number of words remaining, as shown in the example below:
```
Enter a letter: a
__a___, Guesses left = 6, Words left = 8154
```
6. Repeat step 2 - 5 until player has run out of guesses, pick a word from the word list and display it as the word that the program initially "chose". If the player correctly guesses the word, congratulate them and terminate the program.

## Developer
Loo<br>
loo.workspace@gmail.com
