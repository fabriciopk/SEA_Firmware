CXX = g++
CC = gcc
CFLAGS = -I include -I/usr/include -Wall -O2
CXXFLAGS = -Iinclude -I/usr/include -Wall -O2

OUTPUTDIR = bin/
MKDIR = mkdir -p $(OUTPUTDIR)
OBJECTCC = dxl_hal.o dynamixel.o

CSOURCES = dxl_hal.c dynamixel.c
CXXSOURCES = dynamixel_test.cpp


all: dynamixel.o dxl_hal.o dynamixel_test.o dynamixel_test 

dynamixel_test: dynamixel.o dxl_hal.o dynamixel_test.o
	@$(CXX) dynamixel.o dxl_hal.o dynamixel_test.o -o dynamixel_test

dynamixel_test.o: dynamixel_test.cpp
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

dxl_hal.o: dxl_hal.c
	@$(CC) -c $< -o $@ $(CFLAGS)

dynamixel.o: dynamixel.c
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) -rf $(OUTPUTDIR)
	$(RM) ./*.o dynamixel_test