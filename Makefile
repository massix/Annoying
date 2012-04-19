CC			=	clang++

TARGET		=	Annoying
SOURCES	=		rock.cpp \
				paper.cpp \
				scissor.cpp \
				lizard.cpp \
				spock.cpp \
				main.cpp
				
OBJS		=	$(SOURCES:.cpp=.o)

CPPFLAGS	=	-I. -I/usr/include/c++/v1 -Wall -O2 -arch x86_64 -std=c++0x -stdlib=libc++
LDFLAGS		=	-stdlib=libc++

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
	
clean:
	rm -fr $(OBJS) $(TARGET)
