#pragma once

#include <string>

namespace CBMemory
{
  template <class T> class IsInheritable
  {
  public:
    static constexpr bool value = !std::is_class<T>::value;
  };
  
  class BaseMemoryMonitoredObject
  {
  public:
    virtual ~BaseMemoryMonitoredObject() = 0;
  };
}