OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/part1texturering
BIN2=bin/part2texturedisc
BIN3=bin/part3z2Dshape
BIN4=bin/part4chessboard
SRCS1=part1texturering.cpp utility/readin.cpp utility/shader.cpp utility/stb_image.cpp
SRCS2=part2texturedisc.cpp utility/readin.cpp utility/shader.cpp utility/stb_image.cpp
SRCS3=part3z2Dshape.cpp utility/readin.cpp utility/shader.cpp utility/stb_image.cpp
SRCS4=part4chessboard.cpp utility/readin.cpp utility/shader.cpp utility/stb_image.cpp
INCLUDES=utility/readin.hpp utility/shader.hpp utility/stb_image.h

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)	
$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)	
$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 
