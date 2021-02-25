#include "fundamentalType_example.hpp"

#include "cbmemory.hpp"
#include <iostream>

void fundamentalTypeExample()
{
  using uint32_tObject = CBMemory::ObjectType<uint32_t>;
  uint32_tObject* object = tracked_new<uint32_t>();
  
  *object = 7;

  uint32_t other = *object;
  (void)other;
  delete object;


  using uint32_tArray = CBMemory::ArrayType<uint32_t>;
  uint32_tArray* array = tracked_new_array<uint32_t[5]>();
  
  array[0] = 7;

  delete [] array;

  if (!::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    std::cout << "All memory managed objects deleted" << std::endl;
  }
}