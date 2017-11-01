#include "FindFault.h"
#include <iostream>
#include <string>

using namespace std;

int main(){


	FindFault ff;
	ff.encrypt("adsfadsf");
	ff.encrypt("sjdf;alsdjdfasdjfd");

	FindFault ff1;
	ff1.encrypt("ASDAFASDFADFADF");
	ff1.encrypt("JLLKKLGgglghlghl");

	FindFault lmn;

	lmn = ff1;

	cout << lmn.getNumberOfElements();

	cin.get();




	return 0;

}