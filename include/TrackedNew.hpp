#pragma once

#include "MemoryMonitoredObject.hpp"
#include "MemoryMonitoredArray.hpp"
#include <string>

namespace CBMemory
{
  template <class T> class TrackedNewArrayAllocator
  {
  public:
    using Type = T;
    static constexpr std::size_t size = 0;

    static MemoryMonitoredArray<T>* allocate(const char* filename, uint32_t lineNumber)
    {
      throw MemoryMonitorError("Not an array Type", filename, lineNumber);
    }
  };

  template <class T, std::size_t Size> class TrackedNewArrayAllocator<T[Size]>
  {
  public:
    using Type = T;
    static constexpr std::size_t size = Size;
    
    static MemoryMonitoredArray<T>* allocate(const char* filename, uint32_t lineNumber)
    {
      (void)filename;
      (void)lineNumber;
      return new MemoryMonitoredArray<T>[Size];
    }
  };

  class TrackedNewAllocator
  {
  public:
    TrackedNewAllocator(const char* filename, uint32_t lineNumber):
      _filename(filename),
      _lineNumber(lineNumber)
    {}

    template <class T, class ...Arguments> T* allocate(Arguments&&... arguments)
    {
      MemoryMonitoredObject<T>* object = new MemoryMonitoredObject<T>(std::forward<Arguments>(arguments)...);
      MemoryMonitor::instance().addObject<T>(_filename, _lineNumber, object);
      return object;
    }

    template <class T> MemoryMonitoredArray<typename TrackedNewArrayAllocator<T>::Type>* allocateArray()
    {
      MemoryMonitoredArray<typename TrackedNewArrayAllocator<T>::Type>* object = TrackedNewArrayAllocator<T>::allocate(_filename, _lineNumber);
      
      MemoryMonitor::instance().addArray<T>(_filename, _lineNumber, object, TrackedNewArrayAllocator<T>::size);
      return object;
    }
  private:
    const char* _filename;
    uint32_t _lineNumber;
  };

  class UntrackedNewAllocator
  {
  public:
    template <class T, class ...Arguments> static T* allocate(Arguments&&... arguments)
    {
      return new T (std::forward<Arguments>(arguments)...);
    }
    template <class T> T* allocateArray(std::size_t size)
    {
      return new T[size];
    }
  };
}

#if CBMEMORY_TRACK == 1
#define tracked_new ::CBMemory::TrackedNewAllocator(__FILE__, __LINE__).allocate
#define tracked_new_array ::CBMemory::TrackedNewAllocator(__FILE__, __LINE__).allocateArray
#define tracked_new_array_type ::CBMemory::MemoryMonitoredArray
#else
#define tracked_new ::CBMemory::UntrackedNewAllocator::allocate
#define tracked_new_array ::CBMemory::UntrackedNewAllocator::allocateArray
#define tracked_new_array_type
#endif