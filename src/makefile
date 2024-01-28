data_test: data.o file.o data_test.o
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls data_test.o data.o file.o -o data_test
	rm *.o

simulation: data.o file.o simulation.o structure.o distance.o 
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls simulation.o data.o file.o distance.o structure.o -o simulation
	rm *.o


chemins_main: chemins_main.o structure.o a_etoile.o data.o file.o distance.o
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls distance.o structure.o a_etoile.o data.o file.o chemins_main.o -o chemins_main
	rm *.o

chemins_main.o: chemins_main.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c chemins_main.c

structure.o: structure.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c structure.c

distance.o: distance.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c distance.c 

a_etoile.o: a_etoile.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c a_etoile.c

data.o: data.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c data.c

data_test.o: data_test.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c data_test.c

test_data.o: test_data.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c test_data.c

file.o: file.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c file.c

simulation.o: simulation.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -c simulation.c

simulation_main.o: simulation_main.c
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -c simulation_main.c

simulation_main: simulation_main.o simulation.o data.o file.o structure.o distance.o a_etoile.o
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer simulation_main.o simulation.o data.o file.o distance.o structure.o a_etoile.o -o simulation_main
	rm *.o