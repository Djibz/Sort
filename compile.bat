g++ -c -L./lib -I./include src/sortAlgo.cpp -o object/sortAlgo.o
g++ -c -L./lib -I./include src/sortGUI.cpp -o object/sortGUI.o
g++ -c -L./lib -I./include src/main.cpp -o object/main.o
g++ -L./lib -I./include object/sortAlgo.o object/sortGUI.o object/main.o -lmingw32 -lSDL2main -lSDL2 -o main