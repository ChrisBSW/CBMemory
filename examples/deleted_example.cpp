#include "cbmemory.hpp"

#include <iostream>

class DeletedExample
{
public:
  DeletedExample() {}  
  virtual ~DeletedExample() {}
};

void deletedExample()
{
  DeletedExample* deleted = tracked_new(DeletedExample)();
  
  delete deleted;

  if (!::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    std::cout << "All memory managed objects deleted" << std::endl;
  }
}