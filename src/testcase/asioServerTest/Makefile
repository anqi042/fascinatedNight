# which Complier
CC = g++

#headers
INCLUDE = 

#OBJECTS  .o file
OBJECTS = main.o

# Complier Options
CFLAGS = -std=c++11 -g -Wall -fPIC




#libs
LIBRARYS = -lpthread -Wl,-rpath=/usr/local/lib/  -lboost_log  -lboost_thread -lboost_system -lboost_log_setup

#target program name
TARGET = server


%.o:%.cpp
	$(CC)   $(CFLAGS)  -c $< $(INCLUDE)  $(LIBRARYS)

$(TARGET):$(OBJECTS)
	$(CC)   $(CFLAGS) -o $@ $^ $(INCLUDE)  $(LIBRARYS)


clean :
	rm -f $(OBJECTS) $(TARGET)

