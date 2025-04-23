

assignment: assignment.o Group.o Person.o
	g++ -std=c++17 -Wall -Iinclude assignment.o Group.o Person.o -o assignment

assignment.o: assignment.cpp
	g++ -std=c++17 -Wall -Iinclude -c assignment.cpp

Group.o: Group.cpp Group.h
	g++ -std=c++17 -Wall -Iinclude -c Group.cpp

Person.o: Person.cpp Person.h
	g++ -std=c++17 -Wall -Iinclude -c Person.cpp

clean:
	rm -f *.o assignment

