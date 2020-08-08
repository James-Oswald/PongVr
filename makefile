
INCS=-I"./glew-2.1.0/include" -I./glm
SRCS=-L"C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/lib" -L"./glew-2.1.0/lib/Release/x64" -L"./glew-2.1.0/bin/Release/x64"
LIBS=-lgdi32 -lopengl32 -lglew32
SUBSYS=-mwindows -mconsole

pong: clean
	g++ $(INCS) -o pong.exe main.cpp $(SUBSYS) $(SRCS) $(LIBS)
#g++ -o Pong main.o

#main.o: main.cpp
#	g++ -o main.o -c main.cpp -mwindows $(SRCS) $(LIBS)
	
clean:
#del /f main.o
	del /f Pong.exe


