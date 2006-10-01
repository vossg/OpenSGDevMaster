# trivial makefile for OpenSG example

SRCS := Nodes.cpp TestWindow.cpp Test.cpp Image.cpp python_wrapper.cpp

OBJS := $(SRCS:.cpp=.o)

OPT :=  --dbg
#OPT :=  --opt
# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
#OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


OSGROOT := ../../build.linux/instlinks

CC := g++

CCFLAGS = -g -I. -I/usr/include/python2.4 \
          -DBOOST_PYTHON_DYNAMIC_LIB -fPIC \
        $(shell $(OSGROOT)/bin/osg2-config --cflags $(OPT) FileIO Base System GLUT Drawable Util)

LDFLAGS = $(shell $(OSGROOT)/bin/osg2-config --libs $(OPT) FileIO Base System GLUT Drawable Util) \
         -g -fPIC  -L. -lboost_python

default: osgbench.so

clean:
	rm -f *.o osgbench.so

osgbench.so: $(OBJS) $(SRCS)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) $< $(OBJS) $(LDFLAGS) -o $@ 


%.so:
	$(CC) -shared $(OBJS) $(LDFLAGS) -o $@ 


Nodes.o: Nodes.h Nodes.cpp
TestWindow.o: TestWindow.h TestWindow.cpp
Test.o: Test.h Test.cpp
python_wrapper.o: python_wrapper.cpp Nodes.h TestWindow.h Test.h Image.h
