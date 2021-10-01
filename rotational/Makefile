# Change paths according to your Binary folder

LIBS = "../libraries/lib"  # Libraries Path
ICLD = "../libraries/include"  # Include Path
FRM = "../libraries/Frameworks"  # Frameworks Path

LIB_FLAGS = -lsfml-audio -lsfml-network -lsfml-window -lsfml-graphics -lsfml-system

main:
	g++ -std=c++11 -I${ICLD} -L${LIBS} -F${FRM} ${LIB_FLAGS} $@.cpp -o $@.o
