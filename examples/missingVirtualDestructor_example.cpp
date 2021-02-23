
#include "cbmemory.hpp"

#include <iostream>

class MissingVirtualDestructorExample
{
public:
  MissingVirtualDestructorExample() {}  
};

void missingVirtualDestructorExample()
{
  try
  {
    MissingVirtualDestructorExample* missingVirtualDestructor = tracked_new(MissingVirtualDestructorExample)();
    delete missingVirtualDestructor;
  }
  catch (const ::CBMemory::MemoryMonitor::Error& error)
  {
    std::cout << error.message() << " @ " << error.filename() << ":" << error.lineNumber() << std::endl;;
  }
}