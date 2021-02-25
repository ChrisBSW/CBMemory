#include "MemoryMonitorError.hpp"

namespace CBMemory
{
  MemoryMonitorError::MemoryMonitorError(const std::string& message, const char* filename, uint32_t lineNumber):
    _message(message),
    _filename(filename),
    _lineNumber(lineNumber)
  {}

  const std::string& MemoryMonitorError::message() const
  {
    return _message;
  }

  const char* MemoryMonitorError::filename() const
  {
    return _filename;
  }

  uint32_t MemoryMonitorError::lineNumber() const
  {
    return _lineNumber;
  }
}