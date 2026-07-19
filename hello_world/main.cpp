
#include <iostream> 
#include <vector>
using namespace std;

int main() {
	vector <string> words = { "first", "second", "third" };
	cout << "Hello World" << endl;
	for (int i = 0; i < words.size(); i++) {
		cout << words[i] + " ";
	}
	cout << endl;

	return 0; 
}
