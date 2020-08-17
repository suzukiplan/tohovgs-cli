SOURCE=src/miniz.c\
	src/BufferQueue.cpp\
	src/sound-ios.cpp\
	src/tohovgs.cpp\
	src/vgs2tone.c\
	src/vgsdec.c\
	src/vgsmml.c

all: build
	./tohovgs playlist.csv

build: tohovgs

install: tohovgs
	rm -f /usr/local/bin/tohovgs
	ln -s `pwd`/tohovgs /usr/local/bin/tohovgs

tohovgs: $(SOURCE)
	clang -Os -o tohovgs $(SOURCE) -lstdc++ -framework Foundation -framework AudioToolbox
