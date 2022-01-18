CXX = g++
TARGET = a

OBJSRC = src/
LIBSRC = src/lib
INCLSRC = src/include

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=src/%.o)
DEPS = $(wildcard $(INCLSRC)*.h)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ -L $(LIBSRC) -l sfml-graphics -l sfml-window -l sfml-system

$(OBJSRC)%.o: %.cpp $(DEPS)
	$(CXX) -I $(INCLSRC) -c -g $< -o $@

clean: 
	del /f $(OBJSRC)*.o
