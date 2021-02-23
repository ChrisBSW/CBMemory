#pragma once

#include "MemoryMonitoredObject.hpp"
#include <string>

namespace CBMemory
{
  class TrackedNewAllocator
  {
  public:
    TrackedNewAllocator(const char* className, const char* filename, uint32_t lineNumber):
      _className(className),
      _filename(filename),
      _lineNumber(lineNumber)
    {}

    template <class T, class ...Arguments> T* allocate(Arguments&&... arguments)
    {
      MemoryMonitoredObject<T>* object = new MemoryMonitoredObject<T>(std::forward<Arguments>(arguments)...);
      MemoryMonitor::instance().addObject<T>(_className, _filename, _lineNumber, object);
      return object;
    }
  private:
    const char* _className;
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
  };
}


#ifndef CBMEMORY_TRACK
#define CBMEMORY_TRACK 1
#endif

#if CBMEMORY_TRACK == 1
#define tracked_new(className) ::CBMemory::TrackedNewAllocator(#className, __FILE__, __LINE__).allocate<className>
#else
#define tracked_new(className) ::CBMemory::UntrackedNewAllocator::allocate<className>
#endif