proj05: proj05.support.o proj05.driver.o
	gcc proj05.support.o proj05.driver.o -o proj05

proj05.support.o: proj05.support.c
	gcc -Wall -c proj05.support.c

proj05.driver.o: proj05.driver.c
	gcc -Wall -c proj05.driver.c
