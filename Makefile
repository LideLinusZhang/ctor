CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = board.o boardLayoutFactory.o boardPrinters.o buildingType.o color.o controller.o edge.o fairDice.o fileMode.o game.o geese.o loadedDice.o main.o player.o randomGen.o randomMode.o resourceType.o tile.o vertex.o view.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = constructor
	
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	
-include ${DEPENDS} # reads the .d files and reruns dependencies

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

.PHONY: clean
