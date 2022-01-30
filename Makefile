CXX = g++
CXXFLAGS = -g -O2
TARGET = a

SRC = src/
OBJSRC = obj/
LIBSRC = src/lib
INCLSRC = src/include
BIN = bin/

SRCS = $(wildcard $(SRC)*.cpp)
OBJS = $(SRCS:$(SRC)%.cpp=$(OBJSRC)%.o)
DEPS = $(OBJS:$(OBJSRC)%.o=$(BIN)%.d)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -L $(LIBSRC) -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

$(OBJSRC)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLSRC) -c $< -o $@

clean: 
	del /f obj\\*.o
	del /f a.exe