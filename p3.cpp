


#include "FindFault.h"
#include <iostream>
#include <string>
const string STAR =  "*********************************************************************************";
using namespace std;
void welcomeMessage();
void printAddEncryptWordObjects(FindFault&, int, int);
void checkAssignment(FindFault&, FindFault&);
FindFault checkAddition(FindFault&, FindFault&);

int main(){ 
	//welcome message
	welcomeMessage();
	
	//create first FindFault object
	FindFault ff;
	
	// encryt two strings, adding two elements to ff's collection
	ff.encrypt("ADSFSDF");
	ff.encrypt("aslfjasjf");

	// create second  FindFault object
	FindFault ff2;

	// encrypt two strings, adding two elements to ff2's collection
	ff2.encrypt("skldjfas;lfdj");
	ff2.encrypt("afdasdfaf");
	
	// call to printAddEncryptionObjects for object ff and element positions 1 and 2	
	printAddEncryptWordObjects(ff, 1, 2);
	
	// call to checkAssignment for objects ff and ff2
	checkAssignment(ff, ff2);

	// call to checkAdditon()		
	FindFault ff3 = checkAddition(ff, ff2);

	FindFault testCopy(ff);
	

	return 0;

}

FindFault checkAddition(FindFault& objLeft, FindFault& objRight){
cout << "print number of elements for left object:" << endl;
cout << objLeft.getNumberOfElements() << endl <<endl;
cout << "print collection of EncryptWord decrypted phrases for left argument:" << endl;
for(int i = 1; i <=  objLeft.getNumberOfElements(); i ++){
cout << objLeft.decrypt(i) << endl;
}

cout << "\nprint number of elements for right object:" << endl;
cout << objRight.getNumberOfElements() << endl << endl;
cout << "print collection of EncryptWord decrypted phrases for right argument:" << endl;
for(int j = 1; j <= objRight.getNumberOfElements(); j++){
cout << objRight.decrypt(j) << endl;
}
cout << "\n~Add FindFault objLeft and objRight and assign values to new FindFault object, addObject~" << endl << endl;
FindFault addObject;
addObject = objLeft + objRight;
cout << "print number of elements for new object, addObject. (expect output to be sum of objRight and objLeft elements:" << endl;
cout << addObject.getNumberOfElements() << endl << endl;
cout << "print collection of EncryptWord decrypted phrases for addObject. (expect concatenated output of objLeft and objRight collections:" << endl;
for(int k = 1; k <= addObject.getNumberOfElements(); k++){
cout << addObject.decrypt(k) << endl;
}
cout << STAR << endl;
return addObject;
}


// definition: designed to test overloading of multiple operators; == , != , =. Takes in two arguments which may or may not be the same object
// compare if objects are == ( may return true), compare if objects are != (will return opposite of ==)
// assign right argument to left argument. check if arguments are == (will return true), check if objects are != (will return false) .
// precondition: Both FindFault arguments must be "ON".
// modify: left arguent may be modified to the state of right argument if they are != (as per FindFault.h)
// expected output: 0 or 1 \n opposite of first line \n 1 \n 0
void checkAssignment(FindFault & objLeft, FindFault & objRight){
cout << "is left argument == to right? 1 = yes, 0 = no" << endl;
cout << (objLeft == objRight) << endl << endl;
cout <<"is left argument != to right? 1 = no, 0 = yes (opposite of above)" << endl;
cout << (objLeft != objRight) << endl << endl;
cout << "~assigning objRight to objLeft~" << endl << endl;
objLeft = objRight;
cout << "is left argument == to right? 1 = yes, 0 = no (expect 1)" << endl;
cout << (objLeft == objRight) << endl << endl;
cout << "is left argument != right? 1 = yes, 0 = no (expect 0)" << endl;
cout << (objLeft != objRight) << endl;
cout << STAR << endl;
}


// definition: add EncryptWord elements at positions "left argument"  and "right argument" . appends argument's EncryptWord.phrase.
// appended phrase will become new EncryptWord phrase argument. phrase will be encrypted. object will be added to FindFault collection.
// precondition: Object is "ON".  minimum containment of one EncryptWord argument by FindFault.
// modify: FindFault will add another EncryptWord object to container. numberOfElements attribute will increase by one.
// expected output: Number of elements prior to addEncryptWordObjects. \n left argument element decrypted phrase \n right argument element decrypted phrase
// \n number of elements post call to add EncryptWordObjects (+1 from first line) \n concatenated string of left argument and right argument
void printAddEncryptWordObjects(FindFault & ffobj, int left , int right){
	cout << "Number of Elements:" << endl;
	cout << ffobj.getNumberOfElements() << endl << endl;
	cout << "Decrypt corresponding left element:" << endl;
	cout << ffobj.decrypt(left) << endl << endl;
	cout << "Decrypt corresponding right element:" << endl;
	cout << ffobj.decrypt(right) << endl << endl;
	cout << "~Call to addEncryptWordObjects() with left and right arguments~" << endl << endl;
	ffobj.addEncryptWordObjects(left, right);
	cout << "Number of Elements (expect 1 more element)" << endl;
	cout << ffobj.getNumberOfElements() << endl << endl;
	cout << "print concatenation of left and right element's decrypted phrases" << endl;
	cout << ffobj.decrypt(ffobj.getNumberOfElements()) << endl;
	cout << STAR << endl;
}

//Formatted Welcome Messasge
void welcomeMessage(){
cout << "\n" << STAR <<
	"\n*\t\t\t\t\t\t\t\t\t\t*\n*WELCOME TO FIND FAULT TEST DRIVER!!\t\t\t\t\t\t*\n""*CPSC 5011 "<<
	"PROJECT 3\t\t\t\t\t\t\t\t*\n*AUTHOR: DAMIEN SUDOL\t\t\t\t\t\t\t\t*\n*Version: 1.1\t\t\t\t\t\t\t\t\t*"<<
	"\n*\t\t\t\t\t\t\t\t\t\t*\n" << STAR << endl;
}
