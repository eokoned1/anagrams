/*
 * File: proj1.cpp
 * Author: Mofe Okonedo
 * E-mail: eyimofeokonedo@gmail.com
 * This file contains the source code for Project 1.
 * A game where the computer generates a word more than 8 letters from a text file and builds a array of
 * all the words that can be made an anagram or partial from a chosen word. Player guesses a word and the
 * program will check if the guess is a word from the array, if the guess can be made from the chosen word
 * and lastly if the guess hasn't already been guessed. If all of these run true, then the amount of anagrams
 * is incremented, if these all fail, then it notifies the user why and then asks for another guess. Game
 * terminates when all the full and partial anagrams are guessed for the word.
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;
const int WORDLENGTH = 8; // minimum length of chosen word
const string MYFILE = "proj1_data.txt"; // where text file is located
const int FILESIZE = 9578; // total size of the text file
const int ASCII = 256; // ASCII table size

/* Function Name: loadFile
 * Pre-Condition: pass in the array
 * Post-Condition: Returns the string of the random generated word
 */

bool loadFile(string stringData[FILESIZE]);

/* Function Name: pickStartingWord
 * Pre-Condition: Array of text file data is passed in
 * Post-Condition: Returns the string of the random generated word
 */

string pickStartingWord(string stringData[FILESIZE]);

/* Function Name: isAnagram
 * Pre-Condition: The chosen word and the user inputted word.
 * Post-Condition: Returns a boolean if the word is or is not an anagram of the randomly generated word
 */

bool isAnagram(string wordOne, string wordTwo);

/* Function Name: getInput
 * Pre-Condition: User Input is at least 3 characters
 * Post-Condition: Returns the user input
 */

string getInput();

/* Function Name: totalAnagrams
 * Pre-Condition: Pass in the array of words in text file and generated starting word
 * Post-Condition: Returns the count of the amount of total anagrams that can be made from the generated word
 */

int totalAnagrams(string stringData[FILESIZE], string startingWord);

/* Function Name: checkGuess
 * Pre-Condition: Pass in the user-input, array of guessed words and the size of the array
 * Post-Condition: Returns true if the user input was already guessed and false if it wasn't
 */

bool checkGuess(string userInput, string guessedWords[FILESIZE], int arraySize);

/* Function Name: checkValid
 * Pre-Condition: User Input and array of full words passed in
 * Post-Condition: Returns a boolean if the word is found in the full list of words therefore making
 * it a valid word or not
 */

bool checkValid(string userInput, string stringData[FILESIZE]);


int main() {
    cout << "Welcome to UMBC Anagrammer!" << endl;

    string stringData[FILESIZE]; // initialize our array with a size of all the words in the text file

    if (!loadFile(stringData)) { // if loadfile doesn't execute return 1 which indicates that it did not run properly
	    return 1;
    }

    string startingWord = pickStartingWord(stringData); // call pickStarting word to choose the word we are finding
    // anagrams for

    int numAnagrams = totalAnagrams(stringData, startingWord); // initialize variable to store the number of anagrams
    // that can be made from our starting word

    string wordsGuessed[numAnagrams]; // initialize an array for the valid guessed words with a size of the number of
    // correct anagrams available

    cout << "There are " << numAnagrams << " anagrams available in this puzzle." << endl;

    int currIndex = 0; // initializes count of valid guessed words

    cout << "Starting word is: "<< startingWord << endl;

    do {
        string word = getInput(); // Initialize word equal to our function getInput which gets the user-input
        if (checkValid(word, stringData)){ //run it through a number of if-statements. If it is a valid word
                                                    // (checkValid) runs true
            if (isAnagram(startingWord, word)){ // if the word is an anagram of the guessed word pass
                if(!checkGuess(word, wordsGuessed, numAnagrams)) { // checks if the word
                    // wasn't already guessed
                    wordsGuessed[currIndex] = word; // load user input word into array of valid guessed anagram words
                    currIndex++; // increment current index by 1
                    cout << word << " is an anagram of " << startingWord << endl;
                    cout << "You have guessed " << currIndex << " of " << numAnagrams << " anagrams available" << endl;

                }
                else{
                    cout << "Already guessed" << endl; // tell user their guess was made already
                    cout << "You have already guessed " << currIndex << " out of " << numAnagrams << " Anagrams" << endl;
                }
            }
            else{
                cout << word << " is not an anagram of " << startingWord << endl;
            }
        }
        else{
            cout << word << " is not a valid word"<< endl;
            cout << "You have  guessed " << currIndex << " of " << numAnagrams << " words available" << endl;


        }

    } while(currIndex < numAnagrams); // do-while loop that runs while the amount of guesses is less than the amount of
                                      // anagrams

    return 0;
}


bool checkGuess(string userInput, string guessedWords[], int arraySize){
    for(int i = 0; i < arraySize; i++){
        if(guessedWords[i] == userInput) // if the index of the guessed words array is equal to users input they already
            // guessed the word
            return true; // returning true means the word was guessed previously
    }
    return false; // word was not guessed already

}


int totalAnagrams(string stringData[FILESIZE], string startingWord){
    int totalAnagram = 0; // counter variable
    for(int i = 0; i < FILESIZE; i++){
        if (isAnagram(startingWord, stringData[i])){ // if isAnagram runs true increment number of
            // total anagrams by 1
            totalAnagram++;
        }



    }
    return totalAnagram;
}


string getInput(){
    string userInput;
    do {
        cout << "What word would you like to try? " << endl;
        cin >> userInput;
        if (userInput.length() < 3){
            cout << "Minimum of 3 characters" << endl;
        }

    }
    while (userInput.length() < 3);

    // Loops through the list of characters 'string' and assigns the index at
    // the string equal to the character but lowercase with the 'tolower' func
    for (int i = 0; i < int(userInput.length()); i++){
        userInput[i] = tolower(userInput[i]);
}

    cout << userInput << endl;
    return userInput;
}


bool checkValid(string userInput, string stringData[FILESIZE]){

    bool found = false; // boolean flag starts at false

    for(int i = 0; i < FILESIZE; i++){
        if (stringData[i] == userInput){ // the user input is found in array of text file strings then it is a valid
            // word and we return true
            found = true;
            return found;
        }
    }
    return found; // if it is not found in the array it is an invalid word and we return false which was initialized
}


bool isAnagram(string wordOne, string wordTwo) {
    /* create an array of integers and initialize all the elements to 0, then we loop through
     * the string and increment the array by 1 at the characters ASCII value
     */
    int asciiTable[ASCII] = {0};
    for (int i = 0; i < int(wordOne.length()); i++ ){
      int index = wordOne[i];
        asciiTable[index]++;

    }
    // loop through the string and then decrement the array by 1 at the characters ASCII value
    for (int j = 0; j < int(wordTwo.length()); j++ ) {
      int pos = wordTwo[j];
        asciiTable[pos]--;
    }
    /* Now if the second word is an anagram of the first the element values will either be 0 or
     * positive and if it is not an anagram then it will be negative. Now we loop through the array
     * and if there is a negative number in the array then we return False, and it is not an anagram
     * if there are no negative numbers, then we return true, and it is an Anagram.
     */
    for (int k = 0; k < ASCII; k++ ) {
        if(asciiTable[k] < 0){
            return false;
        }
    }
    return true;
}


string pickStartingWord(string stringData[FILESIZE]) {

    string word = ""; //initialize variable with empty string
    int randomNum;
    srand(time(NULL)); // seed the time with srand() and time() functions
    do { // use a do-while loop that utilizes the rand() function of a word in the list that is 8 or more letters
        randomNum = (rand()% (FILESIZE));
        word = stringData[randomNum];

    }
    while(word.length() < 8);
    return word; // we return that word.
}


bool loadFile(string stringData[FILESIZE]) {
    int counter = 0;
    fstream myFile(MYFILE); // We use the fsteam() function and load our text file "MYFILE" and initialize a string
    string currentLine;
    if (myFile.is_open()) { //then check if the file is open
        while (getline(myFile, currentLine)) { //we use getline() to read the line into the array
            stringData[counter] = currentLine;
            counter++; // increment the counter to go all the way down the text file.
        }
        myFile.close(); // close the file
        return true;
    } else{ // else the file does not exit
        cout << "This file does not exist" << endl; // print out an error message
        myFile.close();
        return false;
    }

}


