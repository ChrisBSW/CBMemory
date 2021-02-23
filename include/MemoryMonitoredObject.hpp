#pragma once

#include <string>

namespace CBMemory
{
  class BaseMemoryMonitoredObject
  {
  public:
    virtual ~BaseMemoryMonitoredObject() = 0;
  };

  template <class T> class MemoryMonitoredObject: public BaseMemoryMonitoredObject, public T
  {
  public:
    template <class ...Arguments> MemoryMonitoredObject(Arguments&&... arguments):
      T(std::forward<Arguments>(arguments)...)
    {}
  };
}