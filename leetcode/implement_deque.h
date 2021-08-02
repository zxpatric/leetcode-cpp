//
// Created by ZhouP on 5/2/2019.
//

#ifndef CPPSANDBOX_LEETCODE_IMPLEMENT_DEQUE_H_
#define CPPSANDBOX_LEETCODE_IMPLEMENT_DEQUE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;


//   end pointer    start pointer
//      |             |
//   ----------------345   vector space
//

struct SimpleDqueue
{
 public:
  // assume size > 1
  SimpleDqueue(size_t size) : m_data(size, 0), m_front (0), m_back(0), m_last(size-1)
  {}

  bool pop_front()
  {
    if (empty())
      return false;
    else
    {
      if (m_front == m_last)
        m_front = 0;
      else
        ++m_front;
      return true;
    }
  }

  bool pop_back()
  {
    if (empty())
      return false;
    else
    {
      if (m_back == 0)
        m_back = m_last;
      else
        --m_back;
      return true;
    }
  }

  bool push_front(int val)
  {
    if (isFull())
      return false;
    else
    {
      if (m_front == 0)
        m_front = m_last;
      else
        --m_front;
      m_data[m_front] = val;
      return true;
    }
  }

  bool push_back(int val)
  {
    if (isFull())
      return false;
    else
    {
      if (m_back == m_last)
        m_back = 0;
      else
        ++m_back;
      m_data[m_back] = val;
      return true;
    }
  }

  int front()
  {
    if (empty())
      return -1; // no data
    else
      return m_data[m_front];
  }

  int back()
  {
    if (empty())
      return -1; // no data
    else
      return m_data[m_back];
  }

  bool empty()
  {
    return m_front == m_back;
  }

  inline bool isFull()
  {
    return m_front - m_back == 1 || (m_front == 0 && m_back == m_last) ;
  }

 private:
  // std::list<int> m_data;
  std::vector<int> m_data;
  int m_front;
  int m_back;
  int m_last;
};


int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  std::cout << "Hello Argo AI!" << std::endl;

  SimpleDqueue my_queue(10);

  return 0;
}


#endif //CPPSANDBOX_LEETCODE_IMPLEMENT_DEQUE_H_
