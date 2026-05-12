CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = hw4_p1_infix
OBJS = main.o BinaryTree.o ExpressionParser.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp BinaryTree.h ExpressionParser.h
	$(CXX) $(CXXFLAGS) -c main.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	$(CXX) $(CXXFLAGS) -c BinaryTree.cpp

ExpressionParser.o: ExpressionParser.cpp ExpressionParser.h BinaryTree.h
	$(CXX) $(CXXFLAGS) -c ExpressionParser.cpp

clean:
	rm -f $(TARGET) $(OBJS)