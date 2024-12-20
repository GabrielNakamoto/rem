CXX=g++
CXXFLAGS= -std=c++17

SRC=main.cpp
OBJ=main.o

%.o: %.c
	$(CXX) $(CXXFLAGS)

rem: $(OBJ)
	$(CXX) $(CXXFLAGS) -o rem $(OBJ)

clean:
	$(RM) $(OBJ)
