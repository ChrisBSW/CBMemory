#pragma once

#include "BaseMemoryMonitoredObject.hpp"
#include "MemoryMonitorError.hpp"
#include <set>
#include <algorithm>
#include <ostream>

namespace CBMemory
{
  template <class T, class Enabler = void>
  class MemoryMonitorVirtualDestructorChecker
  {
  public:
    static bool check() 
    {
      return false;
    }
  };

  template <class T> class MemoryMonitorVirtualDestructorChecker<T, typename std::enable_if<std::has_virtual_destructor<T>::value>::type>
  {
  public:
    static bool check() 
    {
      return true;
    }
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
    using const_iterator = Objects::const_iterator;

    const_iterator begin() const;
    const_iterator end() const;
    bool hasUndeletedObjects() const;

    using Error = MemoryMonitorError;
  private:
    template <class T> void addObject(const std::string& className, const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object)
    {
      if (MemoryMonitorVirtualDestructorChecker<T>::check())
      {
        this->addObject(className, filename, lineNumber, object);
      }
      else
      {
        throw MissingVirtualDestructorError(className, filename, lineNumber);
      }
    }

    void addObject(const std::string& className, const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object);

    void removeObject(const BaseMemoryMonitoredObject* object);
  private:
    Objects _objects;
  };

  extern MemoryMonitor& monitor;
}

std::ostream& operator << (std::ostream& ostream, const ::CBMemory::MemoryMonitor::Object& object);