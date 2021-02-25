#pragma once

#include "BaseMemoryMonitoredObject.hpp"
#include "MemoryMonitor.hpp"

#include <string>
#include <iostream>

namespace CBMemory
{
  template <class T, class Enabler = void> class MemoryMonitoredObject: public BaseMemoryMonitoredObject, public T
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

  template <class T> class MemoryMonitoredObject<T, typename std::enable_if<IsInheritable<T>::value>::type>: public BaseMemoryMonitoredObject
  {
  public:
    MemoryMonitoredObject() = default;
    MemoryMonitoredObject(const T& object):
      _object(object)
    {}

    ~MemoryMonitoredObject() override
    {
      MemoryMonitor::instance().removeObject(static_cast<BaseMemoryMonitoredObject*>(this));
    }

    MemoryMonitoredObject<T>& operator = (const T& object )
    {
      _object = object;
      return *this;
    }

    operator const T&() const
    {
      return _object;
    }
  private:
    T _object;
  };

#if CBMEMORY_TRACK == 1
  template <class T> using ObjectType = MemoryMonitoredObject<T>;
#else
  template <class T> using ObjectType = T;
#endif
}