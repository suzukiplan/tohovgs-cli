SOURCE=src/miniz.c\
	src/BufferQueue.cpp\
	src/sound-ios.cpp\
	src/tohovgs.cpp\
	src/vgs2tone.c\
	src/vgsdec.c\
	src/vgsmml.c

all: tohovgs
	./tohovgs playlist.csv

tohovgs: $(SOURCE)
	clang -Os -o tohovgs $(SOURCE) -lstdc++ -framework Foundation -framework AudioToolbox
