CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11

TARGET = matrix_test
OBJS = main.o DenseMatrix.o SparseMatrix.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp DenseMatrix.h SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp

DenseMatrix.o: DenseMatrix.cpp DenseMatrix.h
	$(CXX) $(CXXFLAGS) -c DenseMatrix.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c SparseMatrix.cpp

clean:
	rm -f $(OBJS) $(TARGET)
