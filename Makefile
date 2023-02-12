CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = board.o card.o easyComp.o medComp.o hardComp.o humanPlayer.o player.o subject.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
