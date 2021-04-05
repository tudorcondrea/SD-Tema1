build:
	gcc -Wall -Wextra -std=c99 -g planetsFunctionality.c planetsFunctionality.h planets.c CircularDoublyLinkedList.c CircularDoublyLinkedList.h -o main
clean:
	rm main
