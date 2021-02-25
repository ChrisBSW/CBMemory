#include "undeleted_example.hpp"

#include "cbmemory.hpp"
#include <iostream>

class UndeletedExample
{
public:
  UndeletedExample() {}  
  virtual ~UndeletedExample() {}
};

void undeletedExample()
{
  using UndeletedExampleObject = CBMemory::ObjectType<UndeletedExample>;
  UndeletedExampleObject* undeleted = tracked_new<UndeletedExample>();
  // oops! forgot to delete

  if (::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    for (auto object : ::CBMemory::monitor)
    {
      std::cout << "Undeleted " << object << std::endl;
    }
  }

  delete undeleted;
}