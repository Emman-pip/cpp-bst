#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
  for (int i = 0; i < 10; i++) {
    cout << rand() % 10 << endl;
  }
  return 0;
}
