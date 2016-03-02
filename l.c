#include "headers.h"



void createDoctor(char * newid, char * fName, char * sName, char * password){

	strcpy(doctors[doctorsCounter].id, newid);
	strcpy(doctors[doctorsCounter].firstName, fName);
	strcpy(doctors[doctorsCounter].secondName, sName);
	strcpy(doctors[doctorsCounter].password, password);
	doctors[doctorsCounter].visitsCounter = 0;

	doctorsCounter++;
}

void addHoliday(){

	return;
}
void listVisits(){

	return;
}

