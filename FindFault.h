// Author: Damien Sudol
// Filename: EncryptWord P2
// Date: 10/16/2017
// Version: 1.1

#ifndef FINDFAULT_H
#define FINDFAULT_H

#include "EncryptWord.h"
#include <iostream>
#include <string>
using namespace std;
// *DESCRIPTION*
// class aims to provide functions in a logical, efficient format, capable encapsulating multiple, distinct EncryptWord objects.
// The number of EncryptWord objects is dynamic and will increase with every call to the FindFault.encrypt() method.
// It is important to note the element position for any specific object you wish to query against later. The element position will be necessary for 
// calling the correct object with the method provided by this class.
// Error handling on the application side will be necessary to maintain integrity of the program.  
// Legal States ON (getNumberOfElements > 0) is dependent on a minimum of one succesful encryption for a given FindFault object.
// Full class functionality is contingent on the creation and encapsualtion of EncryptWord objects (which occurs when FindFault.encrypt() is called)
// Legal States OFF(getNumberOfElements == 0). Full functionality if class not available.
// FindFault.getNumberOfElements() can be used to determine the state of a FindFault object at any time. 
// 
// *STATE TRANSITIONS*
// OFF-> OFF (constructor -> getNumberOfElements()) *returns default of 0
// OFF-> OFF (constructor-> getQueryAttempts()) *returns default of 0
// OFF-> ON (constructor -> encrypt())
// ON-> ON (encrypt() -> getQueryAttempts())
// ON-> ON (encrypt() -> encrypt())
// ON-> ON (Encrypt() -> getNumberOfElements())
// ON-> ON (encrypt() -> detectCorruption()) 
//
//*INVARIANTS*
// FindFault.encrypt(string) -> argument must be a minimum of 4 characters
// FindFault.detectCorruption(int) -> object must be ON. argument must be greater than 0 and equal or less than FindFault.getNumberOfElements().
// FindFault.decrypt(int) -> object must be ON. argument must be greater than 0 and equal or less than FindFault.getNumberOfElements().
// FindFault.printCorruption(int) -> object must be ON. argument must be greater than 0 and equal or less than FindFault.getNumberOfElements().
//
//*ASSUMPTIONS*
// class will be utilized for its intended purpose, encapsulating EncryptWord objects, providing encryption and decryption,
// the notion of possible corruption, ability to query for corruption, a means to track and display these queries
// All public funtions are necessary for succesful implementation of the classes intended use.
// Please review all definitions, pre and post conditions outlined belowto utilize the full potential of the class.


class FindFault
{
public:
	// Definiton: Class constructor, takes no arguments. Set's object to stable initial state. Necessary for access to public methods.
	// precondition: constructor accepts no arguments. state of object is not applicable prior to call.
	// postcondition: object initialized with default values.  All object attributes are private and cannot be directly accessed.
	FindFault();
	// Definition: returns number of EncryptWord objects contained in FindFault class. Method should be referenced to determine
	// legal argument boundries for FindFault.decrypt() method, FindFault.detectCorruption() method. 
	// precondition: none
	// postcondition: FindFault object not impacted. 
	int getNumberOfElements() const;
	// Definition: takes in string, returns encrypted string via creation of EncryptWord object and call to EncryptWord.encrypt() method. 
	// For all queries for related element, a call to FindFault.getNumberOfElements() prior to any additional calls to FindFault.encrypt() method
	// will return the positon associated with THIS object. 
	// precondition: object may or may not be ON. string argument must be greater than 3 characters.
	// postcondition: FindFault.numberOfElements will increase by 1. New EncryptWord object will be created in heap memory. New string will be 
	// stored in heap memory.
	string encrypt(string);
	// Definition: returns number of calls to FindFault.detectCorruption() method. Argument of value "false" will return an integer representing
	// all queries which have detected corruption. Argument of value "true" will return an integer representing all queries which have not detected corrpution.
	// method tracks queries to ALL encapsualted EncryptWord objects, not individually.
	// precondition: none
	// postcondition: FindFault object not impacted. 
	int getQueryAttempts(bool) const;
	// Definition: detects whether corruption has occured during the encryption process. A return of true indicates no corruption has occured.
	// A return type of false indicates corruption has occured. Legal argument boundries: lower: greater than zero. upper: less than or equal to FindFault.getNumberOfElements()
	// precondition: object ON (getNumberrOfElements() > 0). argument is unsigned integer within legal bounds.
	// postcondition: FindFault.queryAttempts will increase by 1. 
	bool detectCorruption(int);
	// Defintion: returns FindFault contained EncryptWord object's decrypted string, associated with the passed argument. 
	// returned string may or may not have been corrupted during encryption. Legal argument boundries: lower: greater than zero. upper: less than or equal to FindFault.getNumberOfElements()
	// precondition: object ON (getNumberrOfElements() > 0). argument is an unsigned integer within legal bounds.
	// postcondition: FindFault object not impacted.
	string decrypt(int) const;
	// Definition: returns a formatted string for whether corruption of encryption for an encapsualted EncryptWord object has occured.
	// if corruption has occured the impacted character number will be displayed as well as the character in questeion vs original character.
	// important to note that calls to printCorruption will NOT count as queries for corruption detection.
	// precondition: object ON (getNumberOfElements() >0) argument is an unsigned integer within legal bounds.
	// postcondtion: FindFault object not impacted
	string printCorruption(int) const;
	// Definition: Destructor called at end of program to free up all heap allocated memory. Will delete both dynamic arrays from heap and set pointers 
	// to point to NULL.
	~FindFault();

private:
	void setNumberOfElements();
	int numberOfElements;
	void setQueryAttempts(bool);
	EncryptWord * ewArray;
	string * phraseArray;
	string phrase;
	void addEW();
	void addPhrase(string);
	string corruptionPossible(string);
	int corruptedEncryption;
	int encryptionNotCorrupted;
};

#endif