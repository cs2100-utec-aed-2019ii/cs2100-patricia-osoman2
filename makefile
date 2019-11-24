run: compile
	@./trie.o

compile:
	@clang++ -o trie.o main.cpp

clean:
	@rm trie.o
