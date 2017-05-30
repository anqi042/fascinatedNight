# which Complier
CC = g++

#headers
INCLUDE =

#OBJECTS  .o file
OBJECTS = main.o

# Complier Options
CFLAGS = -std=c++11 -g -Wall -fPIC




#libs
LIBRARYS = -lboost_system -lboost_thread

#target program name
TARGET = timer4


%.o:%.cpp
	$(CC)   $(CFLAGS)  -c $< $(INCLUDE)  $(LIBRARYS)

$(TARGET):$(OBJECTS)
	$(CC)   $(CFLAGS) -o $@ $^ $(INCLUDE)  $(LIBRARYS)


clean :
	rm -f $(OBJECTS) $(TARGET)

