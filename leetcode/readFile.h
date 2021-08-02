//
// Created by ZhouP on 5/12/2019.
//

#ifndef CPPSANDBOX_LEETCODE_READFILE_H_
#define CPPSANDBOX_LEETCODE_READFILE_H_

#include <iostream>
#include <cstring>
#include <string>

class Reader
{
 private:
    int m_start;
    int m_end;
    char m_buffer[4096];
    FILE *m_fp;

    int read4K (char* buffer)
    {
      int size = 4096;
      memset(buffer, 0, size);
      fread(buffer, 1, 4096, m_fp);
      return size;
    }

public:
  // [m_start, m_end)
  Reader(std::string fileDescriptor): m_start(0), m_end(0)
  {
    m_fp = fopen(fileDescriptor.c_str(), "r");
    memset(m_buffer, 0, 4096);
  }

  ~Reader()
  {
      if (m_fp)
        fclose(m_fp);
  }

    int readFile(int length, char * buffer)
    {
      int index = 0;
      while (length > 0)
      {
        int available = m_end - m_start;
        if (available >= length)
        {
          memcpy_s(buffer+index, length, m_buffer+m_start, 1);
          index += length;
          m_start += length;
          length = 0;
        }
        else
        {
          memcpy_s(buffer+index, available, m_buffer+m_start, 1);
          index += available;
          m_start = 0;
          m_end = 0;
          length -= available;
        }

        if (available==0)
        {
//          m_end = read4K(m_buffer);
          if (length >= 4096)
          {
            int size = read4K(m_buffer+index);
            if (size == 0)
              break;
            else
            {
              index += size;
              length -= size;
            }
          }
        }
      }
      return index;
    }
};

void test_ReadFile ()
{
  std::string testFile = "abc.txt";
  Reader reader (testFile);
  char buffer[4098];
  reader.readFile(4098, buffer);
}

#endif //CPPSANDBOX_LEETCODE_READFILE_H_
