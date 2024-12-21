CXX = g++ #using g++ compiler
CXXFLAGS = -Wall -std=c++17 -O2
DEBUG = -g

all: build

run-tests: build-tests
	./tests/build/tests
	@rm testOutput.txt

build-tests: build
	cmake -S ./tests -B ./tests/build
	cmake --build tests/build

build: 
	$(CXX) $(CXXFLAGS) src/*.cpp -o iwcpp

debug: clean
	$(CXX) $(DEBUG) $(CXXFLAGS) src/*.cpp -o test.out
	lldb ./test.out test.iwc
	@rm -rf *.out
	@rm -rf test.out.dSYM

clean:
	@rm -rf *.out
	@rm -rf iwcpp
