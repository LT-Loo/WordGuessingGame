#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;


class WordGuess {
  private:
    vector<string> words; // Store words that match word length
    vector<char> letterUsed; // Store letters that have been used
    string currentWord;
    int wordLength;
    int numOfGuess;
    bool endGame = false;

    int word_categorized(unordered_multimap<int, string>&, char); //Categorise words and return the key of largest word category

  public:
    WordGuess() {}; // Default constructor
    WordGuess(string, int, int); // User-defined constructor - read file
    ~WordGuess() {}; // Destructor
    
    bool again() {return !endGame;}; // Returns true if guesses remaining and problem not solved
    bool already_used(char); // Returns true if letter already used
    void add_letter(char); // Adds letter to solution and updates data structures
    string current_word() {return currentWord;}; // Returns the current user solution
    int guesses_left() {return numOfGuess;}; // Returns the current number of guesses remaining
    int words_left() {return words.size();}; // Returns the current number of possible solutions
    bool successful(); // Returns true if user guessed the word
    string get_answer() {return words[rand() % words.size()];}; // Returns the word that the computer initially "chose"
};


// User-defined constructor
WordGuess::WordGuess(string filename, int l, int n) {
  string w;
  ifstream infile;
  wordLength = l;
  numOfGuess = n;
  // FOR loop to assign '_' to represent blank spaces
  for (int i = 0; i < wordLength; i++) {
    currentWord += "_"; 
  }
  infile.open(filename);
  if (!infile) {
    cout << "File open failure!" << endl;
  }
  // WHILE loop to read file and insert words that have the said length
  while (!infile.eof()) { 
    infile >> w;
    if (w.length() == wordLength) {words.push_back(w);}
  }
  infile.close();
}


// Private member function
int WordGuess::word_categorized(unordered_multimap<int, string> &groups, char c) {
  int highest = 0; // The size of the greatest word category
  int highestGroup; // The key of the greatest word category
  // FOR loop to categorize words into their respective categories
  for (auto w : words) { 
    int count = 0; 
    vector<int> key_digit; // Used to store key's digit in order to generate key of map
    // FOR loop to store position index(key's digit) of matched letter in the word
    for (int i = 0; i < wordLength; i++) { 
     if (w[i] == c) {
        key_digit.push_back(i+1);
        count++; // Counts how many matched letters
      }
    }
    if (count == 0) { // If no matched letter, key = 0
      groups.emplace(0, w);
      if (groups.count(0) > highest) { // Check if current group is the largest word category
        highest = groups.count(0);
        highestGroup = 0;
      }
    }
    else { // If number of matched letters > 0
      int key = 0;
      // FOR loop to convert key digits into actual key
      for (int i = 0; i < key_digit.size(); i++) {
        key += key_digit[i] * int(pow(10, i));
      }
      groups.emplace(key, w); // Insert words according to keys
      if (groups.count(key) > highest) { // Check if current group is the largest word category
        highest = groups.count(key);
        highestGroup = key;
      }
    }
  }
  return highestGroup; // Return key of largest word category
}


// Public member functions
bool WordGuess::already_used(char c) {
  // FOR loop to check if letter entered by user has been used before
  for (char l : letterUsed) {
    if (c == l) {return true;} 
  }
  letterUsed.push_back(c); // Insert letter into "letterUsed" vector if a new letter is used and return false
  return false;
}

void WordGuess::add_letter(char c) {
  // If letter hasn't been used before
  if (already_used(c)) { 
    unordered_multimap<int, string> groups; // To store words in different word categories
    int key = word_categorized(groups, c); // To store key of greatest word category
    auto it = groups.equal_range(key); // Point to the starting and ending point of the key range
    words.clear();
    // FOR loop to insert new group of words
    for (auto itr = it.first; itr != it.second; itr++) { 
      words.push_back(itr -> second);
    }
    // WHILE loop to update currentWord
    int r;
    while (key > 0) {
      r = key % 10;
      currentWord[r-1] = c;
      key /= 10;
    }
    numOfGuess--;
    if (numOfGuess == 0) {endGame = true;}
    if (successful()) {endGame = true;} // To check if word is successfully guessed
  }
}

bool WordGuess::successful() {
  // FOR loop to check if there's blank space in currentWord
  for (auto c : currentWord) {
    if (c == '_') {return false;} 
  }
  return true; // Guess complete
}


// Main program
int main(int argc, char * argv[])
{char letter;
 if (argc < 3)
   {cout << "Must enter word length and number of guesses on command line" << endl;
    exit(0);
   }
 WordGuess wg("dictionary.txt", atoi(argv[1]), atoi(argv[2]));
 while (wg.again())
   {cout << "Enter a letter: ";
    cin >> letter;
    if (!islower(letter))
      exit(0);
    if (wg.already_used(letter))
      {cout << "You have already tried " << letter << endl;
       continue;
      }
    wg.add_letter(letter);  
    cout << wg.current_word() << ", Guesses left = " << wg.guesses_left() 
         << ", Words left = " << wg.words_left() << endl;  
   }
 if (wg.successful())  
   cout << "Good job!" << endl;   
 else
   cout << "Sorry, the word was " << wg.get_answer() << endl;
 return 0;   
}