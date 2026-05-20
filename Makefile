CXX = g++
CXXFLAGS = -std=c++20

PROGRAMOS_PAV = programa

$(PROGRAMOS_PAV): *.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAMOS_PAV)
# $^ — nurodo visas priklausomybes