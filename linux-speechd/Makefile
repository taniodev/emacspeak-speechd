CXX=g++
CXXFLAGS=-g -Wall -ansi -pedantic
SRC=tclspeechd.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=$(SRC:.cpp=.so)
LIBS=-l:libspeechd.so

all: $(TARGET)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -fPIC -c $(SRC)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -shared -o $@ $< $(LIBS)


clean:
	@rm -f *.o *.so

