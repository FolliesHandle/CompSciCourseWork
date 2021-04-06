proj10: proj10.support.o proj10.driver.o
	gcc proj10.support.o proj10.driver.o -o proj10
proj10.driver.o: proj10.driver.c
	gcc -Wall -c proj10.driver.c
proj10.support.o: proj10.support.s
	gcc -march=native -c proj10.support.s
