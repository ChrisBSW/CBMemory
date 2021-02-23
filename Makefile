cbmemory:
	g++ -std=c++11 -o cbmemory src/main.cpp src/MemoryMonitor.cpp src/BaseMemoryMonitoredObject.cpp src/MemoryMonitorError.cpp -Iinclude

.PHONY: cbmemory