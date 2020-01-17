#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::reverse;

vector<vector<bool>> P;
vector<vector<string>> S;
vector<int> posit;

int main() 
{
	string input;
	int amount;
	while (getline(cin,input)) {
		for (unsigned int i = 0; i < input.size(); i++) {	
			vector<string> line;
			vector<bool> boo;
			amount = input.size()-i;
			for (int j = 1; j < amount+1;j++) {
				line.push_back(input.substr(i,j));
				boo.push_back(false);
			}
			S.push_back(line); 
			P.push_back(boo);
		}
		// All single letters are palindromes
		// Check for all double letters
		for (unsigned int i = 0;i <input.size();i++){
			for (int j= 0; j<2;j++){
				if (j == 0){
					P[i][j] = true;
				}
				else {
					P[i][j] = (input[i] == input [i+j]);
				}
			}
		}
		// Check all palindromes of same length to allow the P[][] check to correctly identify previously found palindromes
		for (unsigned int length = 2; length < input.size();length++) {
			for (unsigned int position = 0; position < input.size()-length;position++) {
					P[position][length] = (input[position] == input[position+length] && P[position+1][length-2]);
			}
		}

 		for (unsigned int i = 0; i<P.size();i++) {
			for (unsigned int j = P[i].size(); j>0 ;j--){
				if (P[i][j-1] == true) {
					posit.push_back(j);
					i+=j-1;
					break;
				}
			} 
		}
		if ((unsigned int) posit[0] == input.size()) {
			cout << "0 " << input << endl;
		} else {
			int start = 0;
			cout << posit.size()-1 << " ";
			while (posit.size()!=0) {
				int cut = posit[0];
				for (int i = 0 ;i<cut; ++i) {
					cout << input[start++];
				}
				if (posit.size() == 1) {
					cout << endl;
					posit.erase(posit.begin());
				} else {
					cout << "|";
					posit.erase(posit.begin());
				}
			}
		}

		P.resize(0);
		S.resize(0);
		posit.resize(0);
	}
}