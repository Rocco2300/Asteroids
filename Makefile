CXX = g++
TARGET = a

SRC = src/
OBJSRC = obj/
LIBSRC = src/lib
INCLSRC = src/include

SRCS = $(wildcard $(SRC)*.cpp)
OBJS = $(SRCS:$(SRC)%.cpp=$(OBJSRC)%.o)
DEPS = $(wildcard $(INCLSRC)*.h)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ -L $(LIBSRC) -l sfml-graphics -l sfml-window -l sfml-system

$(OBJSRC)%.o: $(SRC)%.cpp $(DEPS)
	$(CXX) -I $(INCLSRC) -c -g $< -o $@

clean: 
	del /f obj\\*.o
	del /f a.exe
