#include "MemoryMonitor.hpp"

#include <sstream>

namespace CBMemory
{
  MemoryMonitor& MemoryMonitor::instance()
  {
    static MemoryMonitor monitor;
    return monitor;
  }

  void MemoryMonitor::addObject(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* object)
  {
    _objects.insert({Type::Object, filename, lineNumber, object, 1});
  }

  void MemoryMonitor::addArray(const char* filename, uint32_t lineNumber, const BaseMemoryMonitoredObject* array, std::size_t size)
  {
    _objects.insert({Type::Array, filename, lineNumber, array, size});
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

  void MemoryMonitor::removeArray(const BaseMemoryMonitoredObject* array, std::size_t size)
  {
    (void)size;
    Objects::iterator it = std::find_if(_objects.begin(),_objects.end(), [&array](const Object& searchObject){
      return searchObject.object == array;
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

namespace
{
  std::string makeArrayString(const ::CBMemory::MemoryMonitor::Object& object)
  {
    std::stringstream ss;
    ss << "Array[";
    ss << object.size;
    ss << "]";
    return ss.str();
  }
}
std::ostream& operator << (std::ostream& stream, const ::CBMemory::MemoryMonitor::Object& object)
{
  std::string objectText = object.type == ::CBMemory::MemoryMonitor::Type::Object ? "Object" : makeArrayString(object);
  stream << objectText << "(" << object.object << ") allocated @ " << object.filename << ":" << object.lineNumber;
  return stream;
}