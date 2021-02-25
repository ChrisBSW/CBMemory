#pragma once

#include "MemoryMonitoredObject.hpp"
#include "MemoryMonitoredArray.hpp"
#include <string>

namespace CBMemory
{
  template <class T> class TrackedNewObjectAllocator
  {
  public:
    using ObjectType = MemoryMonitoredObject<T>;

    template <class ...Arguments> static ObjectType* allocate(const char* filename, uint32_t lineNumber, Arguments&&... arguments)
    {
      ObjectType* output = new ObjectType(std::forward<Arguments>(arguments)...);
      MemoryMonitor::instance().addObject<T>(filename, lineNumber, output);
      return output;
    }
  };

  template <class T, std::size_t Size> class TrackedNewObjectAllocator<T[Size]>
  {
  public:
    using ObjectType = MemoryMonitoredArray<T>;  
    
    template <class ...Arguments> static ObjectType* allocate(const char* filename, uint32_t lineNumber, Arguments&&... arguments)
    {
      ObjectType* output = new ObjectType[Size];
      MemoryMonitor::instance().addArray<T>(filename, lineNumber, output, Size);
      return output;
    }
  };

  class TrackedNewAllocator
  {
  public:
    TrackedNewAllocator(const char* filename, uint32_t lineNumber):
      _filename(filename),
      _lineNumber(lineNumber)
    {}

    template <class T, class ...Arguments> typename TrackedNewObjectAllocator<T>::ObjectType* allocate(Arguments&&... arguments)
    {
      return TrackedNewObjectAllocator<T>::allocate(_filename, _lineNumber, std::forward<Arguments>(arguments)...);
    }
  private:
    const char* _filename;
    uint32_t _lineNumber;
  };

 template <class T> class UntrackedNewObjectAllocator
  {
  public:
    using Type = T;
    static constexpr std::size_t size = 0;

    template <class ...Arguments> static T* allocate(Arguments&&... arguments)
    {
      return new T(std::forward<Arguments>(arguments)...);
    }
  };

  template <class T, std::size_t Size> class UntrackedNewObjectAllocator<T[Size]>
  {
  public:
    using Type = T;
    static constexpr std::size_t size = Size;
    
    template <class ...Arguments> static T* allocate(Arguments&&... arguments)
    {
      return new T[Size];
    }
  };

  class UntrackedNewAllocator
  {
  public:
    template <class T, class ...Arguments> static T* allocate(Arguments&&... arguments)
    {
      return UntrackedNewObjectAllocator<T>::allocate(std::forward<Arguments>(arguments)...);
    }
  };
}

#if CBMEMORY_TRACK == 1
#define tracked_new ::CBMemory::TrackedNewAllocator(__FILE__, __LINE__).allocate
#else
#define tracked_new ::CBMemory::UntrackedNewAllocator::allocate
#endif