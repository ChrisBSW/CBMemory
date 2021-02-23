#include "MemoryMonitor.hpp"

namespace CBMemory
{
  MemoryMonitor& MemoryMonitor::instance()
  {
    static MemoryMonitor monitor;
    return monitor;
  }

  void MemoryMonitor::addObject(const std::string& className, const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object)
  {
    _objects.insert({className, filename, lineNumber, object});
  }

  void MemoryMonitor::removeObject(const BaseMemoryMonitoredObject* object)
  {
    Objects::iterator it = std::find_if(_objects.begin(),_objects.end(), [&object](const Object& searchObject){
      return searchObject.object == object;
    });
    if (it != _objects.end())
    {
      _objects.erase(it);
    }
  }

  MemoryMonitor::const_iterator MemoryMonitor::begin() const
  {
    return _objects.begin();
  }

  MemoryMonitor::const_iterator MemoryMonitor::end() const
  {
    return _objects.end();
  }

  bool MemoryMonitor::hasUndeletedObjects() const
  {
    return _objects.size() != 0;
  }

  bool MemoryMonitor::ObjectCompare::operator()(const Object& lhs, const Object& rhs) const
  {
    return lhs.object < rhs.object;
  }

  MemoryMonitor& monitor = MemoryMonitor::instance();
}

std::ostream& operator << (std::ostream& stream, const ::CBMemory::MemoryMonitor::Object& object)
{
  stream << object.className << " (" << object.object << ") allocated @ " << object.filename << ":" << object.lineNumber;
  return stream;
}