sources = $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c++11
target = parser


$(target) : $(objects)
	g++ -o $(target) $(objects)

%.o : %.cpp
	g++ -c $(flags) $< -o $@
clean :
	rm $(target) $(objects)