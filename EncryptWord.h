// Author: Damien Sudol
// Filename: EncryptWord P2
// Date: 10/16/2017
// Version: 1.1
//
// Description: class aims to provide functions in a logical, efficient format, capable of encrypting passed strings greater than 3 characters, using a caesar cryptic shift.
// In addition, class provides necessary functions to fascilitate a guessing game from passed data in relation to the shift value used during encryption.
// Statistics are also provided modularly through accesor methods for UI benefits. Minimal error handling provided through the class. prompts will display indicating improper data
// but error handling on the application side will be necessary to maintain integrity of the program. Access to the encrypt() method and the return value of getPhrase(encrypted vs decrypted)
// will be dependent on the internal state of the object, details  of dependencies are presented defined below for the encrypt() method. 
//
// Assumptions: class will be utilized for its intended purporse of encryption followed by an interactive guessing game which provides statitical feedback. Failure to succesfuly encrypt
// a phrase prior to calling checkShift() method or any accesor methods will yield insignifcant data. The use of the objectReset() method should only be used to clear all existing data
// and return object to its initial state. Error handling will consist of console prompts to enter acceptable data and pre-determined return values stated below.
// Application programmers must handle review all preconditions to avaoid improper data and ensure preconditions are met for object integrety.  All public funtions are necessary for 
// succesful implementation of the classes intended use. Please review all definitions, pre and post conditions listed below.

// #include <iostream>
#ifndef ENCRYPTWORD_H
#define ENCRYPTWORD_H
#include <string>
using namespace std;

class EncryptWord
{
public:
	// definition: class constructor, called to initialize EncryptWord object. Object is necessary to access public methods of EncryptWord class.
	// precondition: constructor accepts no arguments. state of object is not applicable prior to call.
	// postcondition: object initialized with default values.  All object attributes are private and cannot be directly accessed.
	EncryptWord();

	EncryptWord(const EncryptWord &);


	EncryptWord & operator=(const EncryptWord &);

	bool operator==(const EncryptWord &);

	EncryptWord operator+(const EncryptWord &) const;

	bool operator !=(const EncryptWord &);


	// definition: method accepts argument of type string, with a minimum of 4 characters. passed string will be returned as an encrypted string, pending condtions are met. encryption 
	// will shift characters according to the "shift", a randomly generated value between 1 and 9. if "shift" value is equal to "3" all characters of passed string will
	// increment by "3" according to associated ascii value, and returned as the newly associated character; for instance, the character 'a' = 97(ascii value) will shift 3 and returned as 
	// 'd' = 100(ascii). If character in passed string is "shifted" beyond the english alphabet, according to new ascii value, shift will wrap back to beginning of alphabelt; for instance, the character 'y' = 121(ascii value) with  
	// a shift of "3" will be returned as "b"= 98 (ascii value). any characters of passed string outside of english alphabelt, including numbers and special characters, will 
	// shift without wrapping, aside from empty spaces, which will be returned equal to themselves.  If encryption takes place, internal states will change and reuse of the function will be disabled,
	// getPhrase() will return the encrypted phrase until either checkShift() is passed the value equal to the encrypted shift value provided, or objectReset() is called, allowing for re-use of the function and getPhrase() to return a decrypted value . 
	// precondition: method accepts one argument of type string, with a minimum of 4 characters for succesful encryption. Succesful encryption will disable re-use of the function and set the return
	// value of getPhrase() to the newly encrypted phrase. If one of two conditions are met; objectReset() is called or the "shift" value is passed to the checkShift() method, the encrypt() method will be unlocked.
	// postcondition: returns encrypted version of argument according to the associated shift value. A string return of -1 indicates minimal size of argument is not met. A return value of -2 indicates encryption has been disabled.
	string encrypt(string);

	// definition: assumed that method will be used as a tool to determine value of the encryption "shift" used in encrypt(string). method has four possible integer return values
	// which relate to the integer values passed to method and the current EncryptWord "shift" value. -1 will be returned if passed argument is less than "shift" value,
	// 1 will be returned if passed argument is greater than "shift" value, 0 will be returned if passed argument is equal to "shift" value 2 will be returned if argument is invalid or out of bounds.
	// Returned value can be utilized in application to guide user's guesses towards the "shift value". 
	// EncryptWord class utilizes checkShift(int) method to track data to be utilized by applications.Every call to method will change state of object to reflect the
	// passed integer related to "shift" value, including return values of the following EncryptWord methods; getGuessCount() return value will increment by 1 for each call to checkShift(int),
	// getTotalGuess() return value will increase by the value of integer passed to checkShift(int), getAvgGuess() return value update to reflect an avg of all passed values to checkShift(int) post
	// object initization and prior to objectReset() call, getLowGuessCount() return value will increment by one for every return value of -1, getHighGuessCount() return value will increment by one
	// for every checkShift(int) return value of 1. Out of bounds or invalid integer arguments will return a value of 2, indicating an error, and must be handled by the application programmer.
	// precondition: legal arguments, integer value between 1 and 9
	// postcondition: return integer value of -1, 0, 1, or 2 
	int checkShift(int);

	// definition: resets all class attributes to default values. assumed use; prior to call to encrypt(string) and subsequently checkShift(int) method, allowing for user statistics
	// associated with checkShift(int) to not include prior encryptions and "guesses".
	// precondition: object takes no arguments. if object state has not been changed post initialization, method will have no impact on object's state.
	// postcondition: returns integer object to original state of initialization. 
	void objectReset();

	// definition: Associated with checkShift() method, returns total "guesses" by user (calls to checkShift()).
	// precondition: if checkShift() has not been called, a default value of 0 will be returned.
	// postcondition: returns integer value of all calls to checkShift() method. object state not be impacted.
	int getGuessCount() const;

	// definition: Associated with checkShift() method, returns total of "guess" values by user (total of integers passed as checkShift() argument).
	// precondition: if checkShift() has not been called, a default value of 0 will be returned.
	// postcondition: returns integer value of all integer arguments passed to checkShift() method. object state not be impacted.
	int getTotalGuess() const;

	// definition: Associated with checkShift() method, returns average of total "guess" values and total "guesses" (checkShift() calls and total of integers passed as checkShift() arguments)
	// precondition: if checkShift() has not been called, a default value of 0 will be returned.
	// postcondition: returns integer average of getGuessCount() and getTotalGuessCount(). object state not be impacted.
	double getAvgGuess() const;

	// defintion: Associated with cheeckShift() method returns, the number of "guesses" less than cryptic shift value at time of call (total of -1 return values from checkShift() calls)
	// precondition: a call to checkShift() with a return value of -1 required for a return value other than the default 0.
	// postcondition: returns integer value related to the number of -1 return values from previous checkShift() calls. object state not be impacted.
	int getLowGuessCount() const;

	// definition: associated with checkShift() method, returns the number of "guesses" greater than  cryptic shift value at time of call (total of 1 return values from checkShift() calls)
	// precondition: a call to checkShift() with a return value of 1 required for a return value other than the default 0.
	// postcondition: returns integer value related to the number of 1 return values from previous checkShift() calls. object state not be impacted.
	int getHighGuessCount() const;	

	// defintion: dependent on succesful encryption using encrypt() method. if argument has been succesfully encrypted, objectReset() has not been called,
	// checkShift() has not been passed integer equal to shift value, then return value will be encrypted; else, return value will be decrypted
	// precondition: n/a
	// postcondition: encryptedPhrase or phrase returned
	string getPhrase() const;

	// defintion: dependent on succesful encryption using encrypt() method. if argument has been succesfully encrypted, objectReset() has not been called,
	// checkShift() has not been passed integer equal to shift value, then return value will be encrypted; else, return value will be decrypted
	// precondition: n/a
	// postcondition: encryptedPhrase or phrase returned
	string getEncryptPhrase() const;

private:

	void setShift(int);

	void encryptionOff(bool);

	void setPhrase(string, string);

	void statistics(int, int);
	
	void setGuessCount();

	void setTotalGuess(int);

	void setAvgGuess(int, int);

	void setHighGuessCount();

	void setLowGuessCount();

	void setOn(bool);
	
	bool getOn() const;

	int shift;

	bool on;

	int guessCount;

	int avgGuess;

	int totalGuess;

	int highGuessCount;

	int lowGuessCount;

	string phrase;

	string encryptPhrase;	
};

#endif
