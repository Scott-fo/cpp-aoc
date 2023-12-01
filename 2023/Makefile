CXXFLAGS=-Wall -Wextra -std=c++23 -pedantic

# Pattern rule for compiling any .cc file
%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
