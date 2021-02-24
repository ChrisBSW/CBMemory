#pragma once

#include "BaseMemoryMonitoredObject.hpp"
#include "MemoryMonitor.hpp"

#include <string>
#include <iostream>

namespace CBMemory
{
  template <class T> class MemoryMonitoredObject: public BaseMemoryMonitoredObject, public T
  {
  public:
    template <class ...Arguments> MemoryMonitoredObject(Arguments&&... arguments):
      T(std::forward<Arguments>(arguments)...)
    {}

    ~MemoryMonitoredObject() override
    {
      MemoryMonitor::instance().removeObject(static_cast<BaseMemoryMonitoredObject*>(this));
    }
  };
}