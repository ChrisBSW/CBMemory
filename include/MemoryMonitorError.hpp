#pragma once

#include <string>

namespace CBMemory
{
  class MemoryMonitorError 
  {
  public:
    MemoryMonitorError(const std::string& message, const char* filename, uint32_t lineNumber);
    const std::string& message() const;
    const char* filename() const;
    uint32_t lineNumber() const;
  private:
    std::string _message;
    const char* _filename;
    uint32_t _lineNumber;
  };

  class MissingVirtualDestructorError: public MemoryMonitorError
  {
  public:
    MissingVirtualDestructorError(const std::string& className, const char* filename, uint32_t lineNumber);
  };
}