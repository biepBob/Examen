#Marjan Demuynck #Tycho Cools #Robbe Ceulemans #Yannick van den Steen

# Shell
SHELL = /bin/bash
# Compiler
COMPILER = g++ -g -std=c++11 -Wall -Wno-deprecated -O3 -DNDEBUG

CPPFLAGS = $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)
ROOT1 = $(shell root-config --cflags)
ROOT2 = $(shell root-config --libs)


.PHONY: all clean


all: TestPropagate testPropagateMain.o propagate.o Network.o Layer.o Neuron.o batch.o testimage.o


TestPropagateinterface: testPropagateinterfaceMain.o propagateinterface.o propagate.o propagateRoot.o Network.o Layer.o Neuron.o batch.o testimage.o
	$(COMPILER) $^ ${LDLIBS} ${ROOT2} -lTMVA ${CPPFLAGS} ${ROOT1} ${CPPFLAGS} -o $@

TestPropagate: testPropagateMain.o propagate.o Network.o Layer.o Neuron.o batch.o testimage.o
	$(COMPILER) $^ ${LDLIBS} ${CPPFLAGS} -o $@

TestNetwork: testNetworkMain.o Network.o Layer.o Neuron.o
	$(COMPILER) $^ -o $@

testPropagateinterfaceMain.o: testPropagateinterfaceMain.cpp propagateinterface.h
	$(COMPILER) -c testPropagateinterfaceMain.cpp ${ROOT2} -lTMVA ${ROOT1} -o $@

testPropagateMain.o: testPropagateMain.cpp propagate.h
	$(COMPILER) -c testPropagateMain.cpp -o $@

testNetworkMain.o: testNetworkMain.cpp Network.h
	$(COMPILER) -c testNetworkMain.cpp -o $@

propagateinterface.o: propagateinterface.cpp propagateinterface.h propagate.h propagateRoot.h Network.h batch.h
	$(COMPILER) -c propagateinterface.cpp ${ROOT2} -lTMVA ${ROOT1} -o $@

propagateRoot.o: propagateRoot.cpp propagateRoot.h
	$(COMPILER) -c propagateRoot.cpp ${ROOT2} -lTMVA ${ROOT1}

propagate.o: propagate.cpp propagate.h Network.h batch.h
	$(COMPILER) -c propagate.cpp -o $@

Network.o: Network.cpp Network.h Layer.h
	$(COMPILER) -c Network.cpp -o $@

Layer.o: Layer.cpp Layer.h Neuron.h
	$(COMPILER) -c Layer.cpp -o $@

Neuron.o: Neuron.cpp Neuron.h
	$(COMPILER) -c Neuron.cpp -o $@

batch.o: batch.cpp batch.h testimage.h
	$(COMPILER) -c batch.cpp ${LDLIBS} ${CPPFLAGS} -o $@

testimage.o: testimage.cpp testimage.h
	$(COMPILER) -c testimage.cpp ${LDLIBS} ${CPPFLAGS} -o $@

clean : 
	rm *.o TestPropagate TestPropagateinterface

