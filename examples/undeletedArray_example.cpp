#include "undeletedArray_example.hpp"
#include "cbmemory.hpp"

#include <iostream>

class UndeletedArrayExample
{
public:
  virtual ~UndeletedArrayExample() {}
};

void undeletedArrayExample()
{
  //Examples of defining type
  //using UndeletedArrayExampleArray = declype(tracked_new_array(UndeletedArrayExample)(5);
  //using UndeletedArrayExampleArray = tracked_new_array_type(UndeletedArrayExample);
  using UndeletedArrayExampleArray = CBMemory::ArrayType<UndeletedArrayExample>;

  UndeletedArrayExampleArray* array = tracked_new_array<UndeletedArrayExample[5]>();
  
  if (::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    for (auto object : ::CBMemory::monitor)
    {
      std::cout << "Undeleted " << object << std::endl;
    }
  }

  delete [] array;
}