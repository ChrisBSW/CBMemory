#pragma once

#include <string>

namespace CBMemory
{
  class TrackedNewAllocator
  {
  public:
    TrackedNewAllocator(const char* filename, uint32_t lineNumber):
      _filename(filename),
      _lineNumber(lineNumber)
    {}

    template <class T, class ...Arguments> T* allocate(const std::string& className, Arguments&&... arguments)
    {
      MemoryTrackedObject<T>* object = new MemoryTrackedObject<T>(std::forward<Arguments>(arguments)...);
      MemoryMonitor::instance().addObject<T>(className, _filename, _lineNumber, object);
      return object;
    }

    template <class T, class ...Arguments> T* allocate(Arguments&&... arguments)
    {
      return allocate("Unspecified Class", arguments);
    }
  private:
    const char* _filename;
    uint32_t _lineNumber;
  };

  class UntrackedNewAlocator
  {
  public:
    template <class T, class ...Arguments> T* allocate(const std::string& className, Arguments&&... arguments)
    {
      (void)className;
      return new T (std::forward<Arguments>(arguments)...);
    }
  }
}


#ifndef CBMEMORY_TRACK
#define CBMEMORY_TRACK 1
#endif

#if CBMEMORY_TRACK == 1
#define tracked_new ::CBMemory::TrackedNewAllocator(__FILE__, __LINE__).allocate
#else
#define tracked_new ::CBMemory::UntrackedNewAllocator:allocate
#endif