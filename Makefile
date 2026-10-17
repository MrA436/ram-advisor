# ==============================================================================
# Makefile: RAM Usage Monitor & Telemetry System (Phase 1: 40% Milestone)
# ==============================================================================

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = ram_monitor

SRCS = main.cpp circular_queue.cpp process_table.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
