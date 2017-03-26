#include <iostream>
#include <type_traits>
#ifndef HEAP_HPP_
#define HEAP_HPP_
using namespace std;
template<
    typename T>
class Heap
{
private:
  T* _heap;
  int _last_element = 0;
  int _size;
  bool (*_compare)(T,T);
  int getparent(int);
  int getleftchild(int);
  int getrightchild(int);
  void swap(T&,T&);
public:
  Heap(int,bool (*)(T,T));
  void insert(T);
  void displayheap();
  void heapify(int);
  T exactop();
};
#include "Heap.cpp"
#endif
