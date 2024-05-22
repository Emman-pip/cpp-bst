#include <iostream>
#include <random>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &arr) {
  int i, prev;
  bool flag = false;
  while (!flag) {
    prev = 0;
    flag = true;
    for (i = 1; i < arr.size(); i++) {
      if (prev >= 0 && arr[prev] > arr[i]) {
        swap(arr[prev], arr[i]);
        flag = false;
      }
      prev++;
    }
    if (flag) {
      return;
    }
  }
}
void addto(int &i) { i++; }
int main() {
  vector<int> arr;
  for (int i = 0; i < 100; i++) {
    arr.push_back(rand() % 100);
  }
  bubbleSort(arr);
  for (int i = 0; i < arr.size(); i++) {
    cout << arr[i] << " ";
  }
}
