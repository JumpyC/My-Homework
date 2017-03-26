#include "Heap.hpp"
//uitility function
template<typename T>
Heap<T>::getparent(int curr_index)
{
  return (curr_index - 1) / 2;
}
template<typename T>
Heap<T>::getleftchild(int curr_index)
{
  int ret_index = curr_index * 2 + 1;
  if(ret_index >= _last_element)
    return curr_index;
  return ret_index;
}
template<typename T>
Heap<T>::getrightchild(int curr_index)
{
  int ret_index = curr_index * 2 + 2;
  if(ret_index >= _last_element)
    return curr_index;
  return ret_index;
}
template<typename T>
void Heap<T>::displayheap()
{
  cout << "Displaying heap : " << endl << endl;
  for(int i = 0; i < _size; ++i)
  {
    cout << _heap[i] << endl;
  }
}
template<typename T>
void Heap<T>::swap(T& A,T& B)
{
//  cout << A << " swap " << B << endl;
  T tmp = A;
  A = B;
  B = tmp;
}
//utility function



template <typename T>
Heap<T>::Heap(int n,bool (*cmp)(T,T))
{
  static_assert(is_arithmetic<T>::value,"must be numeric type");
  _compare = cmp;
  _size = n;
  _heap = new T[n];
}

template<typename T>
void Heap<T>::insert(T key)
{
  _heap[_last_element] = key;
  int curr_index = _last_element++;
  int parent_index = getparent(curr_index);
  while((*_compare)(_heap[curr_index],_heap[parent_index]))
  {
  //  cout << "curr_index = " << _heap[curr_index] << " parent : " << _heap[parent_index] << endl;
    swap(_heap[curr_index],_heap[parent_index]);
    curr_index = parent_index;
    parent_index = getparent(curr_index);
  }
}
template<typename T>
T Heap<T>::exactop()
{
  T ret_val = _heap[0];
  _heap[0] = _heap[--_last_element];
  _heap[_last_element] = ret_val;
  heapify(0);
  return ret_val;
}
template<typename T>
void Heap<T>::heapify(int curr_index)
{
  int left_index = getleftchild(curr_index);
  int right_index = getrightchild(curr_index);
  int move_index = right_index;
  if((*_compare)(_heap[left_index], _heap[right_index]))
  {
    move_index = left_index;
  }
  if((*_compare)(_heap[move_index], _heap[curr_index]))
  {
    swap(_heap[move_index],_heap[curr_index]);
    heapify(move_index);
  }
}
