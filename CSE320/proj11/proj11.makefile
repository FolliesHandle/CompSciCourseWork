proj11: proj11.support.o project11.driver.o
	gcc proj11.support.o project11.driver.o -o proj11
proj11.support.o: proj11.support.s
	gcc -march=native -c proj11.support.s