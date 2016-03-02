#ifndef SOP_L_H
#define SOP_L_H

#include "headers.h"

typedef struct doctor{
	char id[30];

	char firstName[30];
	char secondName[30];
	char password[30];

	struct tm visitsTab[20];
	int patientsTab[20];
	int visitsCounter;

	struct tm holiday[2];
}Doctor;


extern int doctorsCounter;
extern Doctor doctors[10];


void createDoctor(char * newid, char * fName, char * sName, char * password);
void addHoliday();
void listVisits();

#endif //SOP_L_H
