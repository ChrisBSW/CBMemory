#pragma once

#include <string>

namespace CBMemory
{
  class BaseMemoryMonitoredObject
  {
  public:
    virtual ~BaseMemoryMonitoredObject() = 0;
  };
}