

test_a_etoile: ../src/structure.h ../src/structure.o ../src/data.h ../src/data.o ../src/file.h ../src/file.o ../src/distance.h ../src/distance.o ../src/a_etoile.h ../src/a_etoile.o
	gcc -Wall ../src/structure.c ../src/file.c ../src/data.c ../src/distance.c ../src/a_etoile.c test_a_etoile.c -o test_a_etoile -lm


test_structure: ../src/file.h ../src/file.o ../src/structure.h ../src/structure.o ../src/data.h ../src/data.o ../src/distance.h ../src/distance.o ../src/a_etoile.h ../src/a_etoile.o
	gcc -Wall ../src/structure.c ../src/data.c ../src/distance.c ../src/file.c ../src/a_etoile.c test_structure.c -o test_structure -lm

test_distance: ../src/distance.h ../src/distance.o
	gcc -Wall  ../src/distance.c  test_distance.c -o test_distance -lm

test_data: ../src/file.h ../src/file.o ../src/structure.h ../src/structure.o ../src/data.h ../src/data.o ../src/distance.h ../src/distance.o ../src/a_etoile.h ../src/a_etoile.o
	gcc -Wall  ../src/data.c ../src/distance.c ../src/file.c ../src/a_etoile.c  test_data.c -o test_data -lm

test_file: ../src/data.h ../src/data.o ../src/file.h ../src/file.o ../src/a_etoile.h ../src/a_etoile.o ../src/distance.h ../src/distance.o
	gcc -Wall  ../src/file.c ../src/data.c ../src/a_etoile.c ../src/distance.c  test_file.c -o test_file -lm

test_simulation: ../src/data.h ../src/data.o ../src/simulation.h ../src/simulation.o ../src/file.h ../src/file.o ../src/a_etoile.h ../src/a_etoile.o ../src/distance.h ../src/distance.o
	gcc -Wall  ../src/simulation.c ../src/simulation_main.c ../src/file.c ../src/data.c ../src/a_etoile.c ../src/distance.c  test_simulation.c -o test_simulation -lm	

clean:
	rm test_structure test_distance test_data test_a_etoile test_file st_simulation
