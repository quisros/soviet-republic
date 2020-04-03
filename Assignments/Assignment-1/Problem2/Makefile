OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/part1gradienttriangle
BIN2=bin/part2chessboard
SRCS1=part1gradienttriangle.cpp utility/readin.cpp utility/shader.cpp 
SRCS2=part2chessboard.cpp utility/readin.cpp utility/shader.cpp 
INCLUDES=utility/readin.hpp utility/shader.hpp

all: $(BIN1) $(BIN2)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 
