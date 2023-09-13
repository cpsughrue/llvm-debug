CXX = /home/cpsughrue/repos/llvm-project-fork/build/bin/clang++
CXXFLAGS = -fmodule-build-daemon
OBJS = main.o add.o
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: sources/main.cpp
	$(CXX) $(CXXFLAGS) -c sources/main.cpp -o main.o

add.o: sources/add.cpp
	$(CXX) $(CXXFLAGS) -c sources/add.cpp -o add.o

clean:
	rm -f $(OBJS) $(TARGET)

