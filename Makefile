LIBS=-lncurses -lstdc++fs
EXEC=nymsaluk
CXX=g++-8
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long -O0 -ggdb -g

# finds all .cpp files in src/
src=$(wildcard src/*.cpp)

# generates files from all .cpp
obj=$(src:.cpp=.o)

# compiles code
compile: $(EXEC)

# deletes all .o files and compiles the whole project
recompile: clean compile

# runs app
run:
	./$(EXEC)

$(EXEC): $(obj)
	$(CXX) $^ -o $(EXEC) $(LIBS)

# creates doxygen file
doc:
	 @doxygen ./doxyfile

# deletes all .o files
clean:
	rm -rf src/*.o nymsaluk
