# ==== переменные make =====
#COMPILER = C:\msys64\mingw64\bin\g++.exe
COMPILER =  C:\mingw64\bin\g++.exe
#COMPILER = g++
LIBS =  -lSDL2main -lSDL2 -lSDL2_image

#for windows/mingw
MINGWLIB = -lmingw32

#for linux/wsl
# sudo apt install libsdl2-dev
LINUX_SDL2 = `sdl2-config --libs`

INCLUDEFOLDERS = -I source/include
LINKFOLDERS  = -L source/src  -L source/lib
DEBUGFLAGS = -O0 -g

SRC=source/src/

OBJECTFILES = main.o game.o input.o graphics.o sprite.o animatedSprite.o player.o level.o tile.o tinyxml2.o

BIN = doukutsu

# ==== инструкции make ====== 
# что скомпилировать: что требуется
#		инструкция

# ========== make ==========  
# примеры использования
# make graphics.o
# make all
# make clean
# make 			- вызывает верхнюю команду

all : $(BIN)

$(BIN): $(OBJECTFILES)
	$(COMPILER) -E $(DEBUGFLAGS) $(OBJECTFILES) -o $(BIN) $(INCLUDEFOLDERS) $(LINKFOLDERS) $(MINGWLIB) $(LIBS) 
 
main.o: 
	$(COMPILER) $(DEBUGFLAGS)  -c $(SRC)main.cpp $(INCLUDEFOLDERS) -o main.o  

game.o: 
	$(COMPILER) -c $(SRC)game.cpp $(INCLUDEFOLDERS) -o game.o $(DEBUGFLAGS)

graphics.o:
	$(COMPILER) -c $(SRC)graphics.cpp $(INCLUDEFOLDERS) -o graphics.o $(DEBUGFLAGS)

input.o:
	$(COMPILER) -c $(SRC)input.cpp $(INCLUDEFOLDERS) -o input.o $(DEBUGFLAGS)

sprite.o:
	$(COMPILER) -c $(SRC)sprite.cpp $(INCLUDEFOLDERS)  -o sprite.o $(DEBUGFLAGS)

animatedSprite.o: 
	$(COMPILER) -c $(SRC)animatedSprite.cpp $(INCLUDEFOLDERS)  -o animatedSprite.o $(DEBUGFLAGS)

player.o:
	$(COMPILER) -c $(SRC)player.cpp  $(INCLUDEFOLDERS)  -o player.o $(DEBUGFLAGS)

level.o:
	$(COMPILER) -c $(SRC)level.cpp  $(INCLUDEFOLDERS)  -o level.o $(DEBUGFLAGS)

tile.o:
	$(COMPILER) -c $(SRC)tile.cpp  $(INCLUDEFOLDERS)  -o tile.o $(DEBUGFLAGS)

tinyxml2.o:
	$(COMPILER) -c $(SRC)tinyxml2.cpp  $(INCLUDEFOLDERS)  -o tinyxml2.o $(DEBUGFLAGS)


# работает только в линуксовой консоли / mingw
clean:
	rm *.o *.exe