// Author: Damien Sudol
// Filename: EncryptWord P2
// Date: 10/16/2017
// Version: 1.1
//
// Description: class aims to provide functions in a logical, efficient format, capable of encrypting passed strings greater than 3 characters, using a caesar cryptic shift.
// In addition, class provides necessary functions to fascilitate a guessing game from passed data in relation to the shift value used during encryption.
// Statistics are also provided modularly through accesor methods for UI benefits. Minimal error handling provided through the class. prompts will display indicating improper data
// but error handling on the application side will be necessary to maintain integrity of the program. Object's encryption may be turned off though a public function, as well as 
// the ability to reset an object to its intitial state. Specifics regarding public methods have been laid out below.
//
// Assumptions: class will be utilized for its intended purporse of encryption followed by an interactive guessing game which provides statitical feedback. Failure to succesfuly encrypt
// a phrase prior to calling checkShift() method or any accesor methods will yield insignifcant data. The use of the objectReset() method should only be used to clear all existing data
// and return object to its initial state. by using the encryptionOff() method you prevent  encryption and ability to randomize a new shift value. Error handling will consist of console prompts
// to enter acceptable data and pre-determined return values stated below. Application programmers must handle improper data to ensure preconditions are met for object integrety.

#include "EncryptWord.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

// class constants
const int ASCII_END_UPPER_ALPHABET_VALUE = 90;
const int ASCII_END_LOWER_ALPHABET_VALUE = 123;
const int ASCII_BLANK_SPACE_VALUE = 32;
const int NUMBER_OF_LETTERS = 26;
const int MINIMUM_PHRASE_LENGTH = 4;
const int SHIFT_UPPER_BOUND = 10;
const int SHIFT_LOWER_BOUND = 0;
const int CORRECT_GUESS = 0;
const int LOW_GUESS = -1;
const int HIGH_GUESS = 1;
const int INVALID_GUESS = 2;
const string INVALID_INPUT_ERROR = "-1";
const string ENCRYPTION_DISABLED = "-2";

// object attributes
int shift;
bool on;
int guessCount;
double avgGuess;
int totalGuess;
int highGuessCount;
int lowGuessCount;
string phrase;
string encryptPhrase;

EncryptWord::EncryptWord()
{
	this->shift = 0;
	this->on = true;
	this->guessCount = 0;
	this->avgGuess = 0;
	this->totalGuess = 0;
	this->highGuessCount = 0;
	this->lowGuessCount = 0;
	this->phrase = "";
	this->encryptPhrase = "";
}

string EncryptWord::encrypt(string phrase)
{
	int phraseLength = phrase.length();

	if (on == false) {
		return ENCRYPTION_DISABLED;
	}

	if (phraseLength > MINIMUM_PHRASE_LENGTH) {

		encryptionOff(false);

		int randomShift = rand() % 9 + 1;

		setShift(randomShift);

		string crypticPhrase;

		int lowerLowShift = ASCII_END_UPPER_ALPHABET_VALUE - randomShift;

		int upperHighShift = ASCII_END_LOWER_ALPHABET_VALUE - randomShift;

		int caesarShift = NUMBER_OF_LETTERS - randomShift;

		int crypticAscii;

		for (int i = 0; i < phraseLength; i++) {

			int ascii = int(phrase[i]);

			if (ascii == ASCII_BLANK_SPACE_VALUE) {
				crypticAscii = ASCII_BLANK_SPACE_VALUE;
			}
			else if (ascii >= lowerLowShift && ascii <= ASCII_END_UPPER_ALPHABET_VALUE) {
				crypticAscii = ascii - caesarShift;
			}
			else if (ascii >= upperHighShift && ascii <= ASCII_END_LOWER_ALPHABET_VALUE) {
				crypticAscii = ascii - caesarShift;
			}
			else {
				crypticAscii = ascii + randomShift;
			}
			char crypticChar = char(crypticAscii);
			crypticPhrase.push_back(crypticChar);
		}
		setPhrase(phrase, crypticPhrase);
		return crypticPhrase;
	}
	else
		return  INVALID_INPUT_ERROR;
}

int EncryptWord::checkShift(int guess)
{

	if (guess == shift)
	{
		statistics(guess, 0);
		encryptionOff(true);
		return CORRECT_GUESS;
	}
	else if (guess > shift  && guess < SHIFT_UPPER_BOUND)
	{
		statistics(guess, 1);
		return HIGH_GUESS;
	}
	else if (guess < shift && guess > SHIFT_LOWER_BOUND)
	{
		statistics(guess, -1);
		return LOW_GUESS;
	}
	else
		return INVALID_GUESS;

}

void EncryptWord::objectReset()
{
	this->guessCount = 0;
	this->avgGuess = 0;
	this->highGuessCount = 0;
	this->lowGuessCount = 0;
	this->shift = 0;
	this->totalGuess = 0;
	setOn(true);
	setPhrase("", "");
}

// definition: Disables use of encrypt(). Toggles getPhrase() from returning encrypted or decrypted phrase.
// precondition: legal arguments, true or false. 
// modify: "on" indirectly
// postcondition: Attribute "on" will be set to value of argument. getPhrase() function returns encryptPhrase if argument is false, returns phrase if argument is true (encrypted vs decrypted)
// true argument will disable encrypt()
void EncryptWord::encryptionOff(bool setting)
{
	if (setting == true)
	{
		setOn(true);
	}
	else if (setting == false)
	{
		setOn(false);
	}
}

// Description: helper method designed to call appropriate functions for game statistics
// precondition: accepts two arguments of type int passed from checkShift(). passed values should reflect
// user "guess" and said guess in relation to the shift value
// modify: no attributes directly
// postcondition: new values will be set to methods setGuessCount(), setTotalGuess(), setAvgGuess() and if 1 is passed
// as integer "relativeToShift" set highGuessCount() will be called. if relativeToShift is passed as -1
// a call to setLowGuessCount() will be called.
void EncryptWord::statistics(int guess, int relativeToShift)
{
	setGuessCount();
	setTotalGuess(guess);
	setAvgGuess(getTotalGuess(), getGuessCount());

	if (relativeToShift == 1)
	{
		setHighGuessCount();
	}
	if (relativeToShift == -1)
	{
		setLowGuessCount();
	}
}


// Description: Mutator member fucntion, sets object's shift value. called from encrypt() method
// precondition: integer value
// moidfy: object's shift value
// postcondition: shift value changed
void EncryptWord::setShift(int shift) {
	this->shift = shift;
}
// Description: mutator member function, sets object's phrase and encryptPhrase. called from encrypt() method
// precondition: must take in two arguments of type string
// modify: phrase and encryptPhrase
// postcondition: change of object attributes phrase and encryptPhrase
void EncryptWord::setPhrase(string phrase, string encryptPhrase) {
	this->phrase = phrase;
	this->encryptPhrase = encryptPhrase;
}

// Description: mutator member function, changes setTotalGuess. called from statistics() method
// precondition: n/a
// modify: guessCount
// postcondition: guessCount attribute increments by 1
void EncryptWord::setGuessCount() {
	this->guessCount++;
}

// Description: mutator member function, sets totalGuess . called from statistics() method
// precondition: int
// modify: totalGuess
// postcondition: totalGuess adds passed integer to itself
void EncryptWord::setTotalGuess(int guess) {
	this->totalGuess += guess;
}

// Description: mutator member function, sets avgGuess. called from  statistics() method
// precondition: integer, integer
// modify: avgGuess
// postcondition: changes avgGuess to reflect avg of totalGuess and guessCount attributes
void EncryptWord::setAvgGuess(int totalGuess, int guessCount) {
	this->avgGuess = totalGuess / guessCount;
}

// Description: mutator member function, sets highGuessCount. called from statistics() method
// precondition: n/a
// modify: highGuessCount
// postcondition: incrememnts highGuessCount by 1
void EncryptWord::setHighGuessCount() {
	this->highGuessCount++;
}

// Description: mutator member function, sets lowGuessCount. called from statistics() method
// precondition: n/a
// modify: lowGuessCount
// postcondition: increments lowGuessCount by 1
void EncryptWord::setLowGuessCount() {
	this->lowGuessCount++;
}

// Description: mutator member function, sets on attribute. 
// precondition: boolean
// moidfy: may impact on attribute
// postcondition: changes state of "on" attribute
void EncryptWord::setOn(bool setting) {
	this->on = setting;
}

// Description: Accesor function to object attribute, on
// precondition: n/a
// modify: n/a
// postcondition: returns boolean value of "on"
bool EncryptWord::getOn() const {
	return on;
}

string EncryptWord::getPhrase() const {

	return phrase;
}
string EncryptWord::getEncryptPhrase() const {
	return encryptPhrase;
}

int EncryptWord::getGuessCount() const {
	return guessCount;
}

int EncryptWord::getTotalGuess() const {
	return totalGuess;
}

double EncryptWord::getAvgGuess() const {
	return avgGuess;
}

int EncryptWord::getLowGuessCount() const {
	return lowGuessCount;
}
int EncryptWord::getHighGuessCount() const {
	return highGuessCount;
}