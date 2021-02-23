#include "MemoryMonitor.hpp"

namespace CBMemory
{
  MemoryMonitor& MemoryMonitor::instance()
  {
    static MemoryMonitor monitor;
    return monitor;
  }
}