#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 5

struct Person {
	char* name;
	unsigned int age;
	struct Person** friends;
	int sizeAllocated;
	int sizeFriends;
};

typedef struct Person pers_t;

pers_t* create(char* name, unsigned int age) {
	pers_t* result = (pers_t*) malloc(sizeof(pers_t));
	result->name = strdup(name);
	result->age = age;
	result->friends = (pers_t**) malloc(sizeof(pers_t*) * INITIAL_CAPACITY);
	result->sizeAllocated = INITIAL_CAPACITY;
	return result; 
}

void destroy(pers_t* pers){
	free(pers->name);
	free(pers);
}

void addFriend(pers_t* pers, pers_t* newFriend) {
	//printf("DEBUG size: %d\n", pers->sizeAllocated);
	//printf("DEBUG pointer: %p\n", *(pers->friends + pers->sizeAllocated - 1));
	if (pers->sizeFriends == pers->sizeAllocated) {
		printf("Reallocating...\n");
		int newSize = pers->sizeAllocated * 2;
		pers->friends =  realloc(pers->friends, newSize * sizeof(pers_t*));
		if (pers->friends) {
			pers->sizeAllocated = newSize;
			printf("Reallocation succeed, newSize is %d\n", newSize);
		} else {
			fprintf(stderr, "could not reallocate memory\n");
			exit(1);
    }
	}
	pers_t** friends = pers->friends;
	while (*friends) {
		friends++;
  }		
  *friends = newFriend;
	pers->sizeFriends++; 
}

void displayPerson(pers_t* pers) {
  printf("Name: %s, Age: %d\n", pers->name, pers->age);
}

void displayFriends(pers_t* pers) {
	unsigned int i;
	printf("Friends of %s:\n", pers->name);
	for (i=0; i<pers->sizeFriends; i++) {
		pers_t** friends = pers->friends + i;
		if (*friends) {
			displayPerson(*friends);
		} else {
			break;
		}
	}
}

int main(){
	pers_t* agent = create("Agent Smith", 128);
	printf("Added: ");
	displayPerson(agent);	
	pers_t* sonny = create("Sonny Moore", 256);
	printf("Added: ");
	displayPerson(sonny);
	//addFriend(agent, sonny);
	//displayFriends(agent);
	//displayFriends(sonny);
	//addFriend(agent, agent);
	//displayFriends(agent);
	int nbFriend;
	for (nbFriend = 0; nbFriend < 11; nbFriend++) {
		printf("Adding friend nb: %d\n", nbFriend + 1);
		char newFriend[50];
		sprintf(newFriend, "Oli Pichon %d", nbFriend + 1);
		pers_t* friend = create(newFriend, nbFriend + 30);
		addFriend(agent, friend);		
	}
	displayFriends(agent);
	return 0;
}
