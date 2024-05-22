#include <iostream>
#include <random>
#include <vector>

using namespace std;

void addto(int &i) { i++; }
int main() {
  int i = 0;
  addto(i);
  addto(i);
  addto(i);
  addto(i);
  addto(i);
  addto(i);
  cout << i << endl;
  return 0;
}
