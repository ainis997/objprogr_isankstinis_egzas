CXX = g++
CXXFLAGS = -std=c++20

SRC_DIR = src
TEKSTU_DIR = tekstai
ISVESTIES_DIR = isvestis

PROGRAMOS_PAV = programa

$(PROGRAMOS_PAV): $(SRC_DIR)/*.cpp
	@if not exist $(TEKSTU_DIR) mkdir $(TEKSTU_DIR)
	@if not exist $(ISVESTIES_DIR) mkdir $(ISVESTIES_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAMOS_PAV)
# $^ — nurodo visas priklausomybes

$(SRC_DIR)/*.cpp: $(SRC_DIR)/*.h