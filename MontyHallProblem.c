#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_DOORS 3UL

unsigned long generate_random_door(unsigned* doors_arr, unsigned long max_doors) {
	unsigned long lucky_doors = rand() % max_doors;
	doors_arr[lucky_doors] = 1;
	return lucky_doors;
}

unsigned long pick_door(unsigned long max_doors) {
	unsigned long choosen_door = 0;
	do
	{
		printf("Please select a door number between 1 and %lu. \n", max_doors);
		scanf("%ul", &choosen_door);
	} while (choosen_door <= 0 || choosen_door > max_doors);
	return choosen_door-1;
}

unsigned long change_door(unsigned* doors_arr, unsigned long choosen_door, unsigned long max_doors) {
	char prompt = '\0';
	do
	{
		printf("Do you want to change the door you have previously chosen? Y:N \n");
		getchar();
		prompt = getchar();
	} while ((prompt != 'Y') && (prompt != 'N'));

	if (prompt == 'Y') {
		for (unsigned long i = 0; i < max_doors; ++i) {
			if (doors_arr[i] != 7 && i != choosen_door)
				return i;
		}
	}
	return choosen_door;
}

void eliminate_door(unsigned* doors_arr, unsigned long choosen_door, unsigned max_doors) {
	unsigned long unlucky_doors = 0;
	do
	{
		unlucky_doors = rand() % max_doors;
	} while (unlucky_doors == choosen_door || doors_arr[unlucky_doors] == 1 || doors_arr[unlucky_doors] == 7);
	doors_arr[unlucky_doors] = 7;
}

void UserMontyHall(unsigned* doors_arr, unsigned max_doors) {
	unsigned long luckyDoor = generate_random_door(doors_arr, max_doors);
	printf("Lucky Door: %lu \n", luckyDoor + 1);
	unsigned long choosenDoor = pick_door(max_doors);
	printf("Chosen Door: %lu \n", choosenDoor + 1);
	for (unsigned int i = 0; i < (max_doors - 2); ++i) {
		eliminate_door(doors_arr, choosenDoor, max_doors);
	}
	if (doors_arr[choosenDoor] == 1) {
		printf("Congratulations !!! You chose the right door in the first choice. \n");
	}
	else {
		printf("Sorry !!! Unfortunately, you chose the wrong door in your first choice. \n");
	}
	choosenDoor = change_door(doors_arr, choosenDoor, max_doors);
	printf("Chosen Door: %lu \n", choosenDoor + 1);
	if (doors_arr[choosenDoor] == 1) {
		printf("Congratulations !!! You won a car from us. \n");
	}
	else {
		printf("Sorry !!! Unfortunately, you chose the wrong door. \n");
	}
}


void competition(unsigned long* result, unsigned* doors_arr, unsigned max_doors) {
	static unsigned long random = 1;
	random += rand() * random / rand()%rand() + 100 * 17 * rand();
	srand(random);
	unsigned long luckyDoor = generate_random_door(doors_arr, max_doors);
	unsigned long choosenDoor = rand() % max_doors;
	for (unsigned int i = 0; i < (max_doors - 2); ++i) {
		eliminate_door(doors_arr, choosenDoor, max_doors);
	}
	if (doors_arr[choosenDoor] == 1) {
		result[0]++;
	}

	for (unsigned long i = 0; i < max_doors; ++i) {
		if (doors_arr[i] != 7 && i != choosenDoor) {
			choosenDoor = i;
			break;
		}

	}

	if (doors_arr[choosenDoor] == 1) {
		result[1]++;
	}
}	


int main(void) 
{
	unsigned doorsArr[MAX_DOORS] = { 0 };
	//UserMontyHall(doorsArr, MAX_DOORS); // Try your chance

#define MAX_TEST 10000
	unsigned long result[2] = { 0 };
	srand(time(NULL));
	for (unsigned long i = 0; i < MAX_TEST; ++i) {
		competition(result, doorsArr, MAX_DOORS); // Test it automatically.
		for (unsigned long t = 0; t < MAX_DOORS; ++t) {
			doorsArr[t] = 0;
		}
	}
	printf("First guess: %lu \t second guess: %lu\n",result[0],result[1]);
	printf("First guess: %f \t second guess: %f\n", (double)result[0]/(result[0]+ result[1])*100, (double)result[1] / (result[0] + result[1])*100);
	return 0;
}
