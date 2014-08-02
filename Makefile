OBJECTS = descriptor.o  miner.o  pattern-tree.o subgraph_hasher.o  tokenizer.o treenode.o  utils.o
#FLAGS = -g -std=c++0x -lboost_serialization
FLAGS = -g 

PSE : $(OBJECTS)
	g++ $(FLAGS) -o PSE $(OBJECTS)

miner.o : miner.cpp utils.h tokenizer.h pattern-tree.h
	g++ $(FLAGS) -c miner.cpp
descriptor.o : descriptor.cpp pattern-tree.h
	g++ $(FLAGS) -c descriptor.cpp
pattern-tree.o : pattern-tree.cpp pattern-tree.h
	g++ $(FLAGS) -c pattern-tree.cpp
subgraph_hasher.o : subgraph_hasher.cpp pattern-tree.h
	g++ $(FLAGS) -c subgraph_hasher.cpp
tokenizer.o : tokenizer.cpp tokenizer.h
	g++ $(FLAGS) -c tokenizer.cpp
treenode.o : treenode.cpp pattern-tree.h
	g++ $(FLAGS) -c treenode.cpp
utils.o : utils.cpp utils.h
	g++ $(FLAGS) -c utils.cpp
	
clean :
	rm $(OBJECTS) PSE
