#include <stdio.h>
#include <string.h>

//Main structure.
struct planet {
	char name[30];
	float diameterKm;
	int satellites;
};

int count(int size, struct planet planetsArr[]) {
	//retVal - number of planets, that don`t have satellites.
	int i, retVal = 0;
	for (i = 0; i < size; i++) {
		if (planetsArr[i].satellites == 0) {
			retVal++;
		}
	}
	return retVal;
}

void change(struct planet *pVar, const char *newValue) {
	//Change 'name' field in structure.
	strcpy(pVar->name, newValue);
}

void print(struct planet *pVar) {
	//Print all fields in planet structure.
	printf("Name of a planet: %s\n", (*pVar).name);
	printf("Planet`s diameter: %.2f\n", (*pVar).diameterKm);
	printf("Number of sattelites: %i\n", (*pVar).satellites);
}

int main() {
	int i, index = 1, countVal = 0, indexUser, size = 4;
	struct planet planetsArr [] = { {"Earth", 1000, 1}, {"Pluto", 2000, 2 }, {"HusslePlanet", 3000, 8}, {"Alone", 200, 2} };

	puts("");

	for (i = 0; i < size; i++) {
		struct planet *ptr = &planetsArr[i];
		printf("\tPlanet with index %d:\n", index);
		print(ptr);
		index++;
	}

	puts("");

	countVal = count(size, planetsArr);
	printf("Number of planets without sattelites: %d\n", countVal);

	puts("");

	puts("Please, enter an index.");
	printf("Maximal allowed number: %d\n>>", size-1);
	scanf("%i", &indexUser);
	struct planet *structPtr = &planetsArr[indexUser];
	change(structPtr, "__NewValue");
	printf("\nAfter changing: ");
	print(structPtr);

	puts("\nend of a program");

	getchar();
	return 0;
}