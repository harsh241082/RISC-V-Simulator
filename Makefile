all: final cleano

final: src/data.o src/encorder.o src/instruction.o src/main.o src/parser.o src/utils.o src/cpu.o src/memory.o src/executor.o
	g++ src/*.o -o riscv_sim

data.o: data.cpp
	g++ -c src/data.o

encorder.o: encorder.cpp
	g++ -c src/encorder.o

instruction.o: instruction.cpp
	g++ -c src/instruction.o

main.o: main.cpp
	g++ -c src/main.o

parser.o: parser.cpp
	g++ -c src/parser.o

utils.o: utils.cpp
	g++ -c src/utils.o

cpu.o: cpu.cpp
	g++ -c src/cpu.o

memory.o: memory.cpp
	g++ -c src/memory.o

executor.o: executor.cpp	
	g++ -c src/executor.o

linerunner.o: linerunner.cpp
	g++ -c src/linerunner.o
	
cleano: 
	rm src/*.o

clean: cleano
	rm riscv_sim.exe