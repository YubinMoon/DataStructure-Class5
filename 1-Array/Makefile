CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11
PYTHON = ../.venv/Scripts/python.exe

TARGET_RUN = run.exe
TARGET_TEST = test.exe

OBJS = DenseMatrix.o SparseMatrix.o
RUN_OBJS = main.o $(OBJS)
TEST_OBJS = test.o $(OBJS)

all: $(TARGET_RUN)

$(TARGET_RUN): $(RUN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_RUN) $(RUN_OBJS)

$(TARGET_TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(TEST_OBJS)

test: $(TARGET_TEST)
	$(PYTHON) generate_data.py 20 20 10
	./$(TARGET_TEST)

main.o: main.cpp DenseMatrix.h SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp DenseMatrix.h SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c test.cpp

DenseMatrix.o: DenseMatrix.cpp DenseMatrix.h
	$(CXX) $(CXXFLAGS) -c DenseMatrix.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c SparseMatrix.cpp

clean:
	rm -f *.o $(TARGET_RUN) $(TARGET_TEST)

clear: clean
	rm -rf test_data/*.txt
	rmdir test_data
