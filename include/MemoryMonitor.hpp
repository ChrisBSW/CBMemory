#pragma once

#include "MemoryMonitoredObject.hpp"
#include "MemoryMonitorError.hpp"
#include <set>

namespace CBMemory
{
  template <class T, class Enabler = void>
  class MemoryMonitorVirtualDestructorChecker
  {
  public:
    static void check() 
    {
      throw MissingVirtualDestructorError(className, filename, lineNumber);
    }
  };

  template <class T> class MemoryMonitorVirtualDestructorChecker<T, typename std::enable_if<std::has_virtual_destructor<T>::value>::type>
  {
  public:
    static void check() {}
  };

  class MemoryMonitor
  {
    friend class TrackedNewAllocator;
    template <class T> friend class MemoryMonitoredObject;
  public:
    static MemoryMonitor& instance();
  
    struct Object
    {
      std::string className;
      const char* filename;
      uint32_t lineNumber;
      const BaseMemoryMonitoredObject* object;
    };

    struct ObjectCompare
    {
      bool operator()(const Object& lhs, const Object& rhs) const;
    };
    using Objects = std::set<Object, ObjectCompare>;

    using Error = MemoryMonitorError;
  private:
    template <class T> void addObject(const std::string& className, const char* filename, uint32_t lineNumber, const MemoryMonitoredObject<T>* object)
    {
      MemoryMonitorVirtualDestructorChecker<T>::check();
      _objects.insert({className, filename, lineNumber, object});
    }
  private:
    Objects _objects;
  };
}