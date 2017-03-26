#include <iostream>
#include <queue>
#include "Heap.hpp"
//#include "Heap.cpp"
using namespace std;
template <typename T>
bool max_cmp(T a,T b)
{
  return a > b;
}
template <typename T>
bool min_cmp(T a,T b)
{
  return a < b;
}
int main()
{
  int n;
  cin >> n;
  Heap<int> min_heap(n,min_cmp);
  Heap<int> max_heap(n,max_cmp);
  priority_queue<int> pq;
  for(int i = 0; i < n; ++i)
  {
    int k;
    cin >> k;
    min_heap.insert(k);
    max_heap.insert(k);
    pq.push(k);
  }
  for(int i = 0; i < n; ++i)
  {
    cout << min_heap.exactop() << " " << max_heap.exactop() << " " << pq.top() << endl;
    pq.pop();
  }
  //h.displayheap();
}
