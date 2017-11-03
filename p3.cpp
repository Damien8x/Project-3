


#include "FindFault.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	FindFault ff;

	ff.encrypt("ADSFSDF");
	ff.encrypt("aslfjasjf");

	FindFault ff2;
	ff2.encrypt("skldjfas;lfdj");
	ff2.encrypt("afdasdfaf");

	ff.addEncryptWordObjects(1, 2);
	cout << ff.printCorruption(3) << endl;

	ff = ff2;
	cout << ff.printCorruption(1) << endl;

	FindFault testCopy(ff);
	cout << testCopy.printCorruption(1) << endl;
	
	cout << (testCopy == ff) << endl;
	FindFault testAddition;
	testAddition = ff + testCopy;

	ff = testCopy = ff2;
	cout << (ff == testCopy) << endl;
	cout << (testCopy == ff2) << endl;

	testCopy = ff + ff2 + testCopy;
	cout << testCopy.getNumberOfElements() << endl;
	cout << testAddition.getNumberOfElements() << endl;
	cin.get();

	return 0;
}