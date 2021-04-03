build:
	gcc -Wall -Wextra -std=c99 planetsFunctionality.c planetsFunctionality.h planets.c CircularDoublyLinkedList.c CircularDoublyLinkedList.h -o main
clean:
	rm main
