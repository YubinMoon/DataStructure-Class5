CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11

TARGET_TEST = queuetest.exe
TEST_OBJS = queuetest.o CircularQueue.o

all: $(TARGET_TEST)

$(TARGET_TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(TEST_OBJS)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

queuetest.o: queuetest.cpp Queue/CircularQueue.h
	$(CXX) $(CXXFLAGS) -c queuetest.cpp

CircularQueue.o: Queue/CircularQueue.cpp Queue/CircularQueue.h
	$(CXX) $(CXXFLAGS) -c Queue/CircularQueue.cpp

clean:
	rm -f *.o $(TARGET_TEST)
