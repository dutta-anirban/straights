SOURCES = \
	wasm_lib.cc \
	src/board.cc \
	src/card.cc \
	src/easyComp.cc \
	src/hardComp.cc \
	src/humanPlayer.cc \
	src/medComp.cc \
	src/player.cc \
	src/subject.cc

OPTIONS = \
	-lembind \
	-Isrc \
	-std=c++14 \
	-Wno-unqualified-std-cast-call \
	-sASYNCIFY -sASYNCIFY_IMPORTS=getInput -sASYNCIFY_STACK_SIZE=128000

straights.js straights.wasm: ${SOURCES}
	emcc ${OPTIONS} ${SOURCES} -o straights.js

output.zip: straights.js straights.wasm
	zip -9 output.zip straights.js straights.wasm index.html style.css

.PHONY: clean
clean:
	rm -f straights.js straights.wasm

.PHONY: all
all: straights.js straights.wasm
