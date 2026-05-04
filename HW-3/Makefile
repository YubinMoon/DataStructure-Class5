CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11

TARGET_TEST = queuetest.exe
TARGET_POSTFIX_TEST = postfixtest.exe
TEST_OBJS = queuetest.o CircularQueue.o
POSTFIX_TEST_OBJS = postfixtest.o InfixToPostfix.o Stack.o

all: $(TARGET_TEST) $(TARGET_POSTFIX_TEST)

$(TARGET_TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(TEST_OBJS)

$(TARGET_POSTFIX_TEST): $(POSTFIX_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_POSTFIX_TEST) $(POSTFIX_TEST_OBJS)

test: $(TARGET_TEST) $(TARGET_POSTFIX_TEST)
	./$(TARGET_TEST)
	./$(TARGET_POSTFIX_TEST)

queuetest.o: queuetest.cpp Queue/CircularQueue.h
	$(CXX) $(CXXFLAGS) -c queuetest.cpp

CircularQueue.o: Queue/CircularQueue.cpp Queue/CircularQueue.h
	$(CXX) $(CXXFLAGS) -c Queue/CircularQueue.cpp

postfixtest.o: postfixtest.cpp InfixToPostfix.h
	$(CXX) $(CXXFLAGS) -c postfixtest.cpp

InfixToPostfix.o: InfixToPostfix.cpp InfixToPostfix.h Stack/Stack.h
	$(CXX) $(CXXFLAGS) -c InfixToPostfix.cpp

Stack.o: Stack/Stack.cpp Stack/Stack.h
	$(CXX) $(CXXFLAGS) -c Stack/Stack.cpp

clean:
	rm -f *.o $(TARGET_TEST) $(TARGET_POSTFIX_TEST)
