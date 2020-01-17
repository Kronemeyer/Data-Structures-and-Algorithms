#define turtles 4

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  int sum = 0, value = 0;
  while(true) {
    for(int count = 0; count < turtles; count++){
    cin >> value;
    sum += value;
    }
    if(sum == 0)
      break;
    cout << sum << endl;
    sum = 0;
  }
}
