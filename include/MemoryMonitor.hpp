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
    template <class T, class Enabler> friend class MemoryMonitoredObject;
    template <class T, class Enabler> friend class MemoryMonitoredArray;
  public:
    static MemoryMonitor& instance();
  
    enum class Type
    {
      Object,
      Array
    };
    struct Object
    {
      Type type;
      const char* filename;
      uint32_t lineNumber;
      const BaseMemoryMonitoredObject* object;
      std::size_t size;
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
    template <class T> void addObject(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object)
    {
      this->addObject(filename, lineNumber, object);
    }

    template <class T> void addArray(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* array, std::size_t size)
    {
      this->addArray(filename, lineNumber, array, size);
    }

    void addObject(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object);
    void addArray(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* array, std::size_t size);


    void removeObject(const BaseMemoryMonitoredObject* object);
    void removeArray(const BaseMemoryMonitoredObject* array, std::size_t size);
  private:
    Objects _objects;
  };

  extern MemoryMonitor& monitor;
}

std::ostream& operator << (std::ostream& ostream, const ::CBMemory::MemoryMonitor::Object& object);