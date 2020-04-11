OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=bin/solution3
SRCS=solution3.cpp utility/readin.cpp utility/shader.cpp utility/stb_image.cpp 
INCLUDES=utility/readin.hpp utility/shader.hpp utility/stb_image.h

all: $(BIN)
$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 
