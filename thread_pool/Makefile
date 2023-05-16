# CXX = g++ -std=c++11
# TARGET = main
# SRC = $(wildcard *.cpp ./thread_pool/*.cpp)
# OBJ = $(patsubst %.cpp, %.o, $(SRC))

# CXXFLAGS = -c -Wall -lpthread

# $(TARGET):$(OBJ)
# 	$(CXX) -o $@ $^ 

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) $^ -o $@

# .PHONY: clean
# clean:
# 	rm -rf *.o $(TARGET)
main: main.cpp ./thread_pool/TaskQueue.cpp ./thread_pool/ThreadPool.cpp
	g++ -o main main.cpp ./thread_pool/TaskQueue.cpp ./thread_pool/ThreadPool.cpp -pthread
clean:
	rm -rf *.o $(TARGET)