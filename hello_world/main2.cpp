#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int length;
	string in;
	cout << "say something convincing: " << endl;
	getline(cin, in);
	length = in.size();
	for (int i=0; i < (length + 4); i++) {
		cout << "*";
	}
	cout << endl << "* "<< in << " *" << endl;

	for (int i = 0; i < (length + 4); i++) {
		cout << "*";
	}
	cout << endl;
	return 0;
}