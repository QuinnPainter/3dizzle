appname := 3dstuff.out
CXX := g++
CXXFLAGS := -Wall -g # -g is for debugging symbols
LDFLAGS := -lSDL2
SRCDIR := src
srcfiles := $(shell find $(SRCDIR) -maxdepth 1 -name "*.cpp")
objects := $(patsubst %.cpp, %.o, $(srcfiles))

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) -o $(appname) $(objects) $(LDLIBS) $(LDFLAGS)

clean:
	rm -f $(objects) $(appname)
