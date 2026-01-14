
build:
	rm -f word_ladder
	gcc -Wall main.c -o word_ladder


run:
	./word_ladder

valgrind:
	rm -f word_ladder
	gcc -g -Wall main.c -o word_ladder
	valgrind --leak-check=full --track-origins=yes ./word_ladder

run_sample_dict:
	./word_ladder < sampleDict.txt

run_simple3:
	./word_ladder < simple3.txt

run_simple4:
	./word_ladder < simple4.txt

run_simple5:
	./word_ladder < simple5.txt

clean:
	rm -f word_ladder

rebuild:
	make clean
	make build

build_debug:
	rm -f word_ladder
	gcc -g -Wall main.c -o word_ladder

valgrind_sample:
	valgrind --leak-check=full --track-origins=yes ./word_ladder < sampleDict.txt

run_fast:
	./word_ladder -f

run_quiet:
	./word_ladder -q



