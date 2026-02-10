#include <stddef.h>

size_t maxSeq(int *array, size_t n)
{
  // if n = 0, return 0; if n = 1,  return 1
  if (n == 0 || n == 1)
  {
    return n;
  }
  // define maxLength and tmpLength=1
  size_t maxLength = 0;
  size_t tmpLength = 1;
  // for 1<=i<n
  for (size_t i = 1; i < n; i++)
  {
    // compare (i-1)th and ith, if <
    if (array[i - 1] < array[i])
    {
      // tmpLength+1
      tmpLength++;
    }
    else
    {
      // if not, compare maxLength and tmpLength
      if (maxLength < tmpLength)
      {
        // if <, maxLength = tmpLength
	maxLength = tmpLength;
      }
      //reset tmpLength
      tmpLength = 1;
      
    }
  }
  if (maxLength < tmpLength)
  {
    maxLength = tmpLength;
  }
  // return maxLength
  return maxLength;
}
