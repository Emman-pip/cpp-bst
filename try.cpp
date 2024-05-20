#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> arr = {1, 2, 3};
  arr.push_back(4);
  arr.push_back(5);
  arr.pop_back();
  for (int i : arr) {
    cout << i << endl;
  }
  cout << arr[arr.size() - 1];
}
