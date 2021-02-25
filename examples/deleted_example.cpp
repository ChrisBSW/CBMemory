#include "deleted_example.hpp"

#include "cbmemory.hpp"
#include <iostream>

class DeletedExample
{
public:
  DeletedExample() {}  
  virtual ~DeletedExample() {}

  int variable = 9;
  void function() {}
};

void deletedExample()
{
  using DeletedExampleObject = CBMemory::ObjectType<DeletedExample>;
  DeletedExampleObject* deleted = tracked_new<DeletedExample>();
  
  deleted->variable = 7;
  deleted->function();
  delete deleted;

  if (!::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    std::cout << "All memory managed objects deleted" << std::endl;
  }
}