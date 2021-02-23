#define CBMEMORY_TRACK 0

#include "cbmemory.hpp"

#include <iostream>

class UntrackedExample
{
public:
  UntrackedExample() {}  
  virtual ~UntrackedExample() {}
};

void untrackedExample()
{
  UntrackedExample* untracked = tracked_new(UntrackedExample)();
  // oops! forgot to delete

  if (!::CBMemory::monitor.instance().hasUndeletedObjects())
  {
    std::cout << "Object was not tracked!" << std::endl;
  }

  delete untracked;
}