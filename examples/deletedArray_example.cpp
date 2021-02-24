#include "deleted_example.hpp"

#include "cbmemory.hpp"
#include <iostream>

class DeletedArrayExample
{
public:
  virtual ~DeletedArrayExample() {}
};

void deletedArrayExample()
{
  using DeletedArrayExampleArray = CBMemory::ArrayType<DeletedArrayExample>;

  DeletedArrayExampleArray* array = tracked_new_array<DeletedArrayExample[5]>();
  std::cout << static_cast<CBMemory::BaseMemoryMonitoredObject*>(array) << std::endl;
  
  delete [] array;

  if (!::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    std::cout << "All memory managed objects deleted" << std::endl;
  }
  else
  {
    for (auto object : ::CBMemory::monitor)
    {
      std::cout << "Undeleted " << object << std::endl;
    }
  }
}