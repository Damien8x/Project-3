// Author: Damien Sudol
// Filename: EncryptWord P2
// Date: 10/16/2017
// Version: 1.1

#include "FindFault.h"
#include <string>

// Definition: class designed to implement all features laid out in FindFault.h, with focus on containment, composition and class maintenance.
// class is responsible for encapsulating several distinct EncryptWord objects using a dynamic, resizeable array. A FindFault object
// will be capable of encryption and decryption by utilizinig the EncryptWord class, through composition. Class will also add a notion of corruption, which
// can be determined by a function call to detectCorruption() for any encapsualted EncryptWord obect. The FindFault.comparePhrase() methodd will detect
// corruption by comparing values of decrypted encryption and orignal phrase, prior to encyption. Upon completion of the program all memory assigned to the 
// heap will be properly managed to assure no memory leaks have been left present.


//FindFault.cpp constants are used to enhance readability and avoid hard coding.
const bool NO_CORRUPTION = true;
const bool CORRUPTION = false;
const int INITIAL_NUMBER_OF_ELEMENTS = 0;

// class attributes
int corruptedEncryption;
int encryptionNotCorrupted;
int numberOfElements;
EncryptWord * ewArray;
string * phraseArray;
int queryAttempts;

FindFault::FindFault()
{
	ewArray = new EncryptWord[INITIAL_NUMBER_OF_ELEMENTS];
	phraseArray = new string[INITIAL_NUMBER_OF_ELEMENTS];
	numberOfElements = 0;
	corruptedEncryption = 0;
	encryptionNotCorrupted = 0;
}
FindFault::FindFault(const FindFault& obj) {
	numberOfElements = obj.numberOfElements;
	corruptedEncryption = obj.corruptedEncryption;
	encryptionNotCorrupted = obj.encryptionNotCorrupted;
	ewArray = new EncryptWord[numberOfElements];
	phraseArray = new string[numberOfElements];
	for (int i = 0; i < numberOfElements; i++) {
		ewArray[i] = obj.ewArray[i];
		phraseArray[i] = obj.phraseArray[i];
	}
}

FindFault & FindFault::operator=(const FindFault & obj) {
	if (this != &obj) {
		delete[] ewArray;
		delete[] phraseArray;
		numberOfElements = obj.numberOfElements;
		corruptedEncryption = obj.corruptedEncryption;
		encryptionNotCorrupted = obj.encryptionNotCorrupted;
		ewArray = new EncryptWord[numberOfElements];
		phraseArray = new string[numberOfElements];
		for (int i = 0; i < numberOfElements; i++) {
			ewArray[i] = obj.ewArray[i];
			phraseArray[i] = obj.phraseArray[i];
		}
	}
	return *this;
}

bool FindFault::operator==(const FindFault & obj)const {
	if (numberOfElements != obj.numberOfElements) {
		return false;
	}
	for (int i = 0; i < numberOfElements; i++) {
		if (ewArray[i].getEncryptPhrase() != obj.ewArray[i].getEncryptPhrase()) {
			return false;
		}
	}
	return (numberOfElements == obj.numberOfElements && corruptedEncryption == obj.corruptedEncryption && encryptionNotCorrupted == obj.encryptionNotCorrupted) ? true : false;
	}

FindFault  FindFault::operator+(const FindFault & obj) const {
	FindFault temp;
	/*
	temp.numberOfElements = numberOfElements + obj.numberOfElements;
	temp.corruptedEncryption = corruptedEncryption + obj.corruptedEncryption;
	temp.encryptionNotCorrupted = encryptionNotCorrupted + obj.encryptionNotCorrupted;
	

	delete[] temp.ewArray;
	delete[] temp.phraseArray;
	temp.ewArray = new EncryptWord[temp.numberOfElements];
	temp.phraseArray = new string[temp.numberOfElements];
	
	for (int i = 0; i <numberOfElements; i++) {
		temp.ewArray[i] = ewArray[i];
		temp.phraseArray[i] = phraseArray[i];
	}
	for (int t = 0; t < obj.numberOfElements; t++) {
		temp.ewArray[(t+numberOfElements)-1] = obj.ewArray[t];
		temp.phraseArray[(t+numberOfElements)-1] = obj.phraseArray[t];
	}
	*/
	for (int i = 0; i < numberOfElements; i++) {
		temp.encrypt(ewArray[i].getPhrase());
	}
	for (int t = 0; t < obj.numberOfElements; t++) {
		temp.encrypt(obj.ewArray[t].getPhrase());
	}
	return  temp;
}


int FindFault::getNumberOfElements() const {
	return numberOfElements;
}

string FindFault::encrypt(string phrase) {
	setNumberOfElements();
	addEW();
	addPhrase(phrase);
	phrase = corruptionPossible(phrase);
	phrase = ewArray[getNumberOfElements() - 1].encrypt(phrase);
	return phrase;
}

bool FindFault::encryptWordObjectsEqual(int elementOne, int elementTwo) const {
	return (ewArray[elementOne-1] == ewArray[elementTwo-1]) ? true : false;
}

void FindFault::addEncryptWordObjects(int elementOne, int elementTwo){
	EncryptWord addEncryptWord = (ewArray[elementOne -1] + ewArray[elementTwo -1]);
	encrypt(addEncryptWord.getPhrase());
}

int FindFault::getQueryAttempts(bool corrupted) const {
	if (corrupted == true) {
		return encryptionNotCorrupted;
	}
	else return corruptedEncryption;
}

string FindFault::decrypt(int elementNumber)  const {
	string decryptedPhrase = ewArray[elementNumber - 1].getPhrase();
	return decryptedPhrase;
}

bool FindFault::detectCorruption(int elementNumber) {
	if (ewArray[elementNumber - 1].getPhrase() == phraseArray[elementNumber - 1]) {
		setQueryAttempts(NO_CORRUPTION);
		return NO_CORRUPTION;
	}
	else {
		setQueryAttempts(CORRUPTION);
		return CORRUPTION;
	}
}

string FindFault::printCorruption(int elementNumber) const {
	int corruptCharNum = 0;
	string corruption = "";
	string originalChar;
	string corruptChar;
	string phrase = phraseArray[elementNumber - 1];
	string ewphrase = ewArray[elementNumber - 1].getPhrase();
	int phraseLength = phrase.length();

	if (phrase == ewphrase) {
		corruption = "NO CORRUPTION \nElement Position:\t" + to_string(elementNumber) + "\nDecrypted String:\t" + ewphrase + "\nOriginal String:\t" + phrase;
		return corruption;
	}
	else {

		for (int i = 0; i <= phraseLength; i++) {
			if (phrase[i] != ewphrase[i]) {
				corruptCharNum = i + 1;
				originalChar = phrase[i];
				corruptChar = ewphrase[i];
			}
		}
		corruption = "CORRUPTION DETECTED \nElement Position:\t" + to_string(elementNumber) + "\nDecrypted String:\t" +
			ewphrase + "\nCorruption Position:\tcharacter " + to_string(corruptCharNum) +
			" \nCorrupted Character:\t" + corruptChar + "\nOriginal Character:\t" + originalChar;
	}
	return corruption;
}

// Definiton: adds 1 to attribute queryAttempts, per call to detectCorruption().
// precondition: none
// postcondition: queryAttempts increased by 1.
void FindFault::setQueryAttempts(bool corruption) {
	if (corruption == true) {
		corruptedEncryption++;
	}
	else encryptionNotCorrupted++;
}

// Definiton: method called per call to FindFault.encrypt() method. Creates new EncryptWord object and new temp array in heap memory with a size
// of ewArray.size() + 1 to store additional element. all elements of ewArray are copied to temp array before ewArray deletes all heap elements. ewArray
// then is pointed to the first element of the dynamic temp array before adding the new EncryptWord object to the last position of the array.
// precondition: call to FindFault.encrypt() with string argument greater than 4 characters.
// postcondition: ewArray elements deleted from heap. ewArray points to new array in heap with size increased by one element. ewArray adds new object to last position in array.
void FindFault::addEW() {
	EncryptWord ew;
	EncryptWord * temp;
	temp = new EncryptWord[getNumberOfElements()];
	for (int i = 0; i < (getNumberOfElements() - 1); i++) {
		temp[i] = ewArray[i];
	}
	delete[] ewArray;
	ewArray = temp;
	ewArray[getNumberOfElements() - 1] = ew;
}
// Definition: method called per call to FindFault.encrypt() method. Creates new temp array in heap memory with a size of phraseArray.size() + 1 to
// store an additional element. all elements of phraseArray are copied to temp array before phraseArray deletes all heap elements. phraseArray
// then is pointed to the first element of the dynamic temp array before adding the additional string to the last position of the array.
// precondition: call to FindFault.encrypt() with string agrument greater than 4 characters.
// postcondition: phraseArray elements deleted from heap. phraseArray points to new array in heap with size increased by one string element. 
// phrase array adds new string to last position in array.
void FindFault::addPhrase(string phrase) {
	string * temp;
	temp = new string[getNumberOfElements()];
	for (int i = 0; i < (getNumberOfElements() - 1); i++) {
		temp[i] = phraseArray[i];
	}
	delete[] phraseArray;
	phraseArray = temp;
	phraseArray[getNumberOfElements() - 1] = phrase;
}
// Definition: method called per call to FindFault.encrypt() method. Tracks the number of EncryptWord elements contained in FindFault class by increasing
// the value of numberOfElements attribute by one for each additonal EncryptWord stored.
// precondition: call to FindFault.encrypt() method with legal argument.
// postcondition: increase of FindFault.numberOfElements attribute by 1.
void FindFault::setNumberOfElements() {
	numberOfElements++;
}

// Defintion: method adds notion of possible corruption to the encryption process. If a string has an even length it will not be corrupted. If a string has
// a uneven length corruption may happen. If phrase.length() has a value not divisible by 4, the character of "phrase" equal to the remainder will be set to the ASCII value of
// the remainder * 30.
// precondition: call to FindFault.encrypt() with legal argument.
// postcondition: value returned will be passed to contained EncryptWord.encrypt(string) method. 
string FindFault::corruptionPossible(string phrase) {
	if (phrase.length() % 2 != 0) {
		int corruption = (phrase.length() % 4);
		phrase[corruption] = corruption * 35;
		return phrase;
	}
	else
		return phrase;
}

// Defintioin: destructor. last called function of program, frees up any remaining allocated heap memory.
FindFault::~FindFault()
{
	delete[] ewArray;
	delete[] phraseArray;
}
