CC			=	g++

TARGET		=	Annoying
SOURCES	=		rock.cpp \
				paper.cpp \
				scissor.cpp \
				lizard.cpp \
				spock.cpp \
				main.cpp
				
OBJS		=	$(SOURCES:.cpp=.o)

CPPFLAGS	=	-Wall -O2

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $<
	
clean:
	rm -fr $(OBJS) $(TARGET)
