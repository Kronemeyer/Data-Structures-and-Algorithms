/*  Benjamin Kronemeyer 10/24/19 
    I did use a few web sources to help with this project. The solution function was influenced by
    geeksforgeeks.org/c-code-article-backtracking-set-8-solving-cryptarithmetic-puzzles/
*/
#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct cell {
    char letter;
    int number;
};

bool tryThigns(int count, cell* arr, int n, string s1, string s2, string s3);
void solveThis(string s1, string s2, string s3);

vector<size_t> used(10);
bool solved = false;

int main() {
    string first, second, added;
    size_t plus, equals;
    // TODO(ben): add while loop to have program read from file till end of file
    while (getline(std::cin,added)) {
        plus = added.find('+'); // find position of plus
        if (plus!= string::npos) {
            first = added.substr(0,plus);
            added.erase(0,plus+1);
        }
        equals = added.find('='); // find position of equals
        if (equals!=string::npos) {
            second = added.substr(0,equals);
            added.erase(0,equals+1);
        }
        solveThis(first,second,added);
        if (solved == false) {
            cout << "No solution" << endl;
        }
				solved = false;
        cout << endl;
    }
}
void sum(cell* arr, const int count, string first, string second, string added) {
    size_t i;
    int j;
    string val = "";
    int firstnum, secondnum, addednum;
    for (i=0;i<first.length();i++) {
        char tmp = first[i];
        for (j=0;j<count;j++) 
            if (arr[j].letter == tmp)
                break;
        val += to_string(arr[j].number); 
    }
    firstnum = stoi(val);
    val = "";
    for (i=0;i<second.length();i++) {
        char tmp = second[i];
        for (j=0;j<count;j++) 
            if (arr[j].letter == tmp)
               break;
        val += to_string(arr[j].number);
    }    
    secondnum = stoi(val);
    val = "";
    for (i=0;i<added.length();i++) {
        char tmp = added[i];
        for (j=0;j<count;j++)
            if (arr[j].letter == tmp)
                break;
        val += to_string(arr[j].number);
    }
    addednum = stoi(val);
    if (val.at(0) == '0') {
        addednum = 0;
    }
    val = "";
    if (addednum == (firstnum+secondnum)){
        solved = true;
        cout << firstnum << "+" << secondnum << "=" << addednum << endl;
    }
}
/*
 * Try all the different possible permutations for each cell in the array
 */
void tryThings(const int count, cell* arr, int n, string s1, string s2, string s3){
    size_t i;
    if (n == count-1) {
        for (i=0;i<10;i++){
            if (used[i] == 0) {
                arr[n].number = i;
                sum(arr,count,s1,s2,s3);
            }
        }
    }
    for (int i=0;i<10;i++){
        if(used[i] == 0) {
            arr[n].number = i;
            used[i] = 1;
            tryThings(count,arr,n+1,s1,s2,s3);
            used[i]=0;
        }
    }
}
void solveThis(string first, string second, string added){
    size_t i;
    list<char> unique;  
    for (i=0;i<first.length();i++){
        unique.push_front(first[i]);
    }
    for (i=0;i<second.length();i++){
        unique.push_front(second[i]);
    }
    for (i=0;i<added.length();i++){
        unique.push_front(added[i]);
    }
    unique.sort();
    unique.unique();
    const int size = unique.size();
    cell arr[size];
    i=0;
    while (!unique.empty()){
        arr[i].letter = unique.front();
        unique.pop_front();
        i++;
    }
    tryThings(size,arr,0,first,second,added);
}
