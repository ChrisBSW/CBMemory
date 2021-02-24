#pragma once

#include "BaseMemoryMonitoredObject.hpp"
#include "MemoryMonitor.hpp"

#include <string>
#include <iostream>

namespace CBMemory
{
  template <class T> class MemoryMonitoredArray: public BaseMemoryMonitoredObject, public T
  {
  public:
    void operator delete[](void* ptr)
    {
      void* array = ptrToArrayOffset(ptr);
      MemoryMonitor::instance().removeObject(static_cast<BaseMemoryMonitoredObject*>(array));
    }
  private:
    /*converts the delete [] ptr to the beginning of the array,
    arrays are usually stored on the heap as 
    {
      std::size_t size;
      T array[0];
      T array[1];
      ...
      T array[size-1];
    }
    */
    static void* ptrToArrayOffset(void* ptr)
    {
      return reinterpret_cast<void*>(reinterpret_cast<std::size_t>(ptr) + sizeof(ptr));
    }
  };

#if CBMEMORY_TRACK == 1
  template <class T> using ArrayType = MemoryMonitoredArray<T>;
#else
  template <class T> using ArrayType = T;
#endif
}