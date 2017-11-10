// Author: Damien Sudol
// Filename: EncryptWord P2
// Date: 10/16/2017
// Version: 1.3


// Description: Driver designed to test overloading of operators for both EncryptWord and FindFault
// types, ensuring that the intended functionality is consistant, while logical. 
//
// Overloaded operators tested for FindFault class(in depth provided in .h):
//	+ 	additon operator concatenates FindFault arrays
//  	= 	assigns values of right object to left
// 	==	compares equality of all attributes for left and right objects, including encapsulated EncryptWord decrypted phrases
//		returns true if equal
//	+= 	adds left and right arguments, then assigns value to left object
//	!=	compares equality of all atrributes for left andd right object, including encapuslated EncryptWord decrypted phrases
//		returns true if not equal 
//
// OverLoadded operators tested for EncryptWord class(in depth provied in .h):
// 	+	returns EncryptWord object with encryped phrase equal to concatenation of left and right objects decrypted phrases
// 	=	assigns all attributes of right object to left object
//	== 	compares decrypted phrases of left and right objects for equality
//		returns true if equal
//	!=	compares decrypted phrases of left andd right objects for equality
//		returns true if not equal
//	+=	concatenates left andd right decrypted phrases, re-encrypts phrase, assigns it to left object, sets all other attributes to default
//
//
// Additionally, copy constructors for both EncryptWord and FindFault are added to their respected classes. Two additional public functions are added
// to the FindFault class allowing for manipulation of EncryptWord objects, adding of EncryptWord dobjects (with returned object addded to container)
// as well as adding and assigning values to an existing object, through the overloading of the += operator.
//
// Assumptions: All overloaded operators will be used for their intended purposes. FindFault.getNumberOfElements() should be referenced whenever
// accessing EncryptWord containers, ensuring arguments are within bounds. Applications should only be build around the listed operators above.
// Amy operators not listed have not been overloaded and will result in errors. All overloaded operators have been chosen for a specific
// purpose, to the benefit of the user. 

#include "FindFault.h"
#include <iostream>
#include <string>
const string STAR =  "***************************************************************************************";
using namespace std;
void welcomeMessage();
void printAddEncryptWordObjects(FindFault&, int, int);
void checkAssignment(FindFault&, FindFault&);
void checkAdditionAssignmentOverload(FindFault&, FindFault&);
FindFault checkAddition(FindFault&, FindFault&);
void checkEWadditionAssignmentOverload(FindFault& obj, int , int);
int main(){ 
	//welcome message
	welcomeMessage();
	
	//create first FindFault object
	FindFault ff;
	
	// encryt two strings, adding two elements to ff's collection
	ff.encrypt("C++ rocks!");
	ff.encrypt("enrypt MEEEEEE");

	// create second  FindFault object
	FindFault ff2;

	// encrypt two strings, adding two elements to ff2's collection
	ff2.encrypt("corruption may occur");
	ff2.encrypt("one of these is corrupted");
	ff2.encrypt(" corruption may occur");
	
	// add elements at position 1 and 2 for objects ff and add returned EncryptWord object to container	
	printAddEncryptWordObjects(ff, 1, 2);
	
	// assign ff to ff2
	checkAssignment(ff2, ff);

	// add another element to ff2
	ff2.encrypt("YYYYYYYYYYYOOOOOOOOOO");

	// add ff to ff2 and assign value to ff3
	FindFault ff3 = checkAddition(ff, ff2);
	
	// add another element to ff3
	ff3.encrypt("Adding another to ff3");
	
	// add elements at 1 and 3 for object ff3 and addd returned EncryptWord dobject to container
	printAddEncryptWordObjects(ff3, 1, 3);

	// assign ff3 to ff
	checkAssignment(ff, ff3);
	
	// add ff3 to ff2 and assign value to ff2
	checkAdditionAssignmentOverload(ff2, ff3);
	
	// add eleement 1 and 2 for object ff and assign value to element 1
	checkEWadditionAssignmentOverload(ff, 1, 2);

	// create new FindFault object and populate container
	FindFault ff4;
	ff4.encrypt("another encryption");
	ff4.encrypt("let's keep testing!");
	ff4.encrypt("let's assign 4 to another object");
	ff4.encrypt("one more");

	//add ff4 to ff2 and assign value to ff4
	checkAdditionAssignmentOverload(ff4, ff2);
	
	// assing object ff to ff4
	checkAssignment(ff4, ff);
	
	// add object ff to ff3 and assign to ff5
	FindFault ff5 = checkAddition(ff, ff3);

	// add objects ff2 andd ff1
	checkAdditionAssignmentOverload(ff5, ff);

	// add element 1 to itself for object ff2
	checkEWadditionAssignmentOverload(ff2, 1, 1);
	
	// add elements at position 1 and 3 for object ff5 and add returned EncryptWord object to container
	printAddEncryptWordObjects(ff5, 1, 3);

	return 0;

}

//definition: demonstrates the ability to add and assign EncryptWord objects using 
// overloaded += object, through the public function addAssignEncryptWordObjects()
// provided in the FindFault class
// precondition: Object must be "ON", integer arguments must be greater than 0 and less
// than or equal to obj.getNumberOfElements().
// modify: element for corresponding right value will not be impacted. element at left
// position will have the right arguments phrase appended to the left arguments phrase
// expected output:  original phrases for EncryptWord objects at positions left and right
// followed by the new phrase after left += right
void checkEWadditionAssignmentOverload(FindFault& obj, int left, int right){
	cout << "print left EncryptWord object's decrypted phrase:" <<endl;
	cout << obj.decrypt(left) << endl << endl;
	cout << "print right EncryptWord object's decrypted phrase" << endl;
	cout << obj.decrypt(right) << endl << endl;
	cout << "~add left and right EncryptWord objects and assign value to left object~" << endl << endl;
	obj.addAssignEncryptWordObjects(left, right);	
	cout << "print left EncryptWord object's decrypted phrase, post assignment" <<endl;
	cout << obj.decrypt(left) << endl;
	cout << STAR << endl;
}

// definition: designed to test overloadding of binary operator +=. Displays number of Elements
// and FindFault.decrypt() for all contained EncryptWord objects for left andd right arguments.
// left and right arguments are then added andd assigned to left object using overloaded += operator.
// number of elements and FindFault.decrypt() for all contained EncryptWord objects are then printed
// for left argument, post assignment.
// precondition: minimumm of one FindFault object which is "ON" to bue used as argument(s).
// modify: right argument not impacted. left object will add copies of all right objects container
// EncryptWord contents.
void checkAdditionAssignmentOverload(FindFault& objLeft,  FindFault& objRight){
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
	cout << "\n~Add FindFault objLeft and objRight and assign values to objLeft~" << endl << endl;

	objLeft+=objRight;

	cout << "print number of elements for objLeft." << endl << "expected output to be sum of objLeft and objRight prior to assignment" << endl <<  endl;
	cout << objLeft.getNumberOfElements() << endl << endl;
	cout << "print collection of EncryptWord decrypted phrases for objLeft." << endl << "expect concatenated output of objLeft and objRight collections prior to assignment:" << endl <<  endl;
	for(int k = 1; k <= objLeft.getNumberOfElements(); k++){
	cout << objLeft.decrypt(k) << endl;
	}
	cout << STAR << endl;
}

// definition: designed to test overloading of FindFault + operator. Displays number of Elements, contents of container (contained EncryptWord's 
// decrypted phrases) for both left and right arguments. new object is created and assigned the value produced by the additon of left andd right
// FindFault objects. Contents of new FindFault object are the concatenation of left and right containers, containing EncryptWord objects
// with the same decrypted outputs as the related arguments, but all other attributes may or may not be identical (new shift value etc).
// precondition: minimum of one FindFault object which is "ON" to be used as argument(s). 
// modify: arguments not impacted. Creates and returns new EncryptWord object, a concatenation of arguments containers.
// expected output: prints number of elements for left object, followed by all decrypted phrases contained in left object's container.
// prints number of elements for right object, followed by all decrypted phrases contained in right object's container
// prints number of elements for new FindFault object assigned the sum of left and right object, followed by all phrases contained in 
// new object's container. number of elements should equal sum of left and right arguments number of elements, contents should be 
// a concatenation of left and right argument's contents.
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
	cout << "\n~Add FindFault objLeft and objRight and assign values to" << endl << " new FindFault object, addObject~" << endl << endl;
	FindFault addObject;
	addObject = objLeft + objRight;
	cout << "print number of elements for new object, addObject." << endl << "expect output to be sum of objRight and objLeft elements:" << endl <<  endl;
	cout << addObject.getNumberOfElements() << endl << endl;
	cout << "print collection of EncryptWord decrypted phrases for addObject." << endl << "expect concatenated output of objLeft and objRight collections:" << endl <<  endl;
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
	"\n*\t\t\t\t\t\t\t\t\t\t\t*\n*WELCOME TO FIND FAULT TEST DRIVER!!\t\t\t\t\t\t\t*\n""*CPSC 5011 "<<
	"PROJECT 3\t\t\t\t\t\t\t\t\t*\n*AUTHOR: DAMIEN SUDOL\t\t\t\t\t\t\t\t\t*\n*Version: 1.3\t\t\t\t\t\t\t\t\t\t*"<<
	"\n*\t\t\t\t\t\t\t\t\t\t\t*\n*\t\t\t\t\t\t\t\t\t\t\t*\n*Driver designed to test overloading of operators for both EncryptWord\t\t\t*"<<
"\n*and FindFault types, ensuring that the intended functionality is consistant,\t\t*\n*while logical.\t\t\t\t\t\t\t\t\t\t*\n" << STAR << endl;
}
