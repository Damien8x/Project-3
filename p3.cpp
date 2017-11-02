


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
	cout << ff.printCorruption(3);
	
	cin.get();

	return 0;
}