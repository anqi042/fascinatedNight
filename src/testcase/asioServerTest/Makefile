# which Complier
CC = clang++

#headers
INCLUDE = 

#OBJECTS  .o file
OBJECTS = main.o mySocket.o glog.o sockController.o 

# Complier Options
CFLAGS = -std=c++11 -g -DDEBUG -Wall -fPIC




#libs
LIBRARYS = -lpthread -Wl,-rpath=/usr/local/lib/  -lglog  -lboost_thread -lboost_system 

#target program name
TARGET = server


%.o:%.cpp
	$(CC)   $(CFLAGS)  -c $< $(INCLUDE)  $(LIBRARYS)

$(TARGET):$(OBJECTS)
	$(CC)   $(CFLAGS) -o $@ $^ $(INCLUDE)  $(LIBRARYS)


clean :
	rm -f $(OBJECTS) $(TARGET)

