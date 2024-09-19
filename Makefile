FLAGS = -g -c -Wall
COMPILED = compiled
OUT = out

all: src/main.c src/Graph.c src/TST.c src/LinkedList.c src/Page.c
	@mkdir -p $(OUT)
	@mkdir -p $(COMPILED)
	@gcc $(FLAGS) src/main.c -o $(COMPILED)/main.o
	@gcc $(FLAGS) src/Graph.c -o $(COMPILED)/Graph.o
	@gcc $(FLAGS) src/TST.c -o $(COMPILED)/TST.o
	@gcc $(FLAGS) src/LinkedList.c -o $(COMPILED)/LinkedList.o 
	@gcc $(FLAGS) src/Page.c -o $(COMPILED)/Page.o 
	@gcc -o trab3 $(COMPILED)/main.o $(COMPILED)/Graph.o $(COMPILED)/TST.o $(COMPILED)/LinkedList.o $(COMPILED)/Page.o

run:
	./trab3 docs/

run_N10:
	./trab3 in/N10.txt $(OUT)/N10.txt 

run_N100:
	./trab2 in/N100.txt $(OUT)/N100.txt 

run_N1000:
	./trab2 in/N1000.txt $(OUT)/N1000.txt 

run_N10000:
	./trab2 in/N10000.txt $(OUT)/N10000.txt
	
val:
	valgrind --leak-check=full --show-leak-kinds=all -s ./trab3 docs/ > valgrind_output.txt 2>&1

valgrind_N10:
	valgrind --leak-check=full --show-leak-kinds=all ./trab2 in/N10.txt $(OUT)/N10.txt

valgrind_N100:
	valgrind --leak-check=full --show-leak-kinds=all ./trab2 in/N100.txt $(OUT)/N100.txt

valgrind_N1000:
	valgrind --leak-check=full --show-leak-kinds=all ./trab2 in/N1000.txt $(OUT)/N1000.txt

valgrind_N10000:
	valgrind --leak-check=full --show-leak-kinds=all ./trab2 in/N10000.txt $(OUT)/N10000.txt
	
clean:
	@rm -f $(COMPILED)/*.o
	@rm -rf $(COMPILED)
	@rm -rf $(OUT)
	@rm -f trab3