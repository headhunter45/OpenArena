CPP = g++
INCLUDES = 
LD = g++
INCLUDEPATH = ../include
OBJECTS = bmp.o camera.o ctrls.o level.o main.o mygl.o myglFont.o myglTexture.o physics.o player.o strmanip.o tga.o vector.o
LIBS = -L/usr/X11R6/lib -lGL -lGLU -lXxf86vm
LIBRARIES = 
SO_LIBS = 
SO_LIBRARIES = oa_game.so oa_audio.so oa_net.so oa_video.so oa_input.so
CPPFLAGS = 
LDFLAGS = $(LIBS)

.Phony: all clean install

all: oa

clean: 
	rm -f *.o
	
install:

oa: $(OBJECTS)
	$(LD) $(LDFLAGS) -o oa $(OBJECTS)

oa_game.so:

oa_audio.so:

oa_net.so:

oa_video.so:

oa_input.so:

bmp.o: bmp.cpp $(INCLUDEPATH)/bmp.h
	$(CPP) -c -o bmp.o bmp.cpp
	
camera.o: camera.cpp $(INCLUDEPATH)/camera.h
	$(CPP) -c -o camera.o camera.cpp
	
ctrls.o: ctrls.cpp $(INCLUDEPATH)/ctrls.h
	$(CPP) -c -o ctrls.o ctrls.cpp

level.o: level.cpp $(INCLUDEPATH)/level.h
	$(CPP) -c -o level.o level.cpp
	
mygl.o: mygl.cpp $(INCLUDEPATH)/mygl.h
	$(CPP) -c -o mygl.o mygl.cpp

myglFont.o: myglFont.cpp $(INCLUDEPATH)/myglFont.h
	$(CPP) -c -o myglFont.o myglFont.cpp

myglTexture.o: myglTexture.cpp $(INCLUDEPATH)/myglTexture.h
	$(CPP) -c -o myglTexture.o myglTexture.cpp

physics.o: physics.cpp $(INCLUDEPATH)/physics.h
	$(CPP) -c -o physics.o physics.cpp

player.o: player.cpp $(INCLUDEPATH)/player.h
	$(CPP) -c -o player.o player.cpp

strmanip.o: strmanip.cpp $(INCLUDEPATH)/strmanip.h
	$(CPP) -c -o strmanip.o strmanip.cpp

tga.o: tga.cpp $(INCLUDEPATH)/tga.h
	$(CPP) -c -o tga.o tga.cpp

vector.o: vector.cpp $(INCLUDEPATH)/vector.h
	$(CPP) -c -o vector.o vector.cpp

main.o: linux.cpp $(INCLUDEPATH)/linux.h $(INCLUDEPATH)/main.h
	$(CPP) -c -o main.o linux.cpp
