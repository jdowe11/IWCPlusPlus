CXX = g++ #using g++ compiler
CXXFLAGS = -Wall -std=c++17 -O2
DEBUG = -g

all: build

build: 
	$(CXX) $(CXXFLAGS) src/*.cpp -o iwcpp

debug:
	$(CXX) $(DEBUG) $(CXXFLAGS) src/*.cpp -o test.out
	lldb ./test.out test.iwc
	@rm -rf *.out
	@rm -rf *.dSYM

clean:
	@rm -rf *.out
	@rm -rf iwcpp