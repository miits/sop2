#ifndef SOP_P_H
#define SOP_P_H

#include "headers.h"

typedef struct patient{
	char id[30];

	char firstName[30];
	char secondName[30];
	char pesel[30];
	char password[30];

	struct tm visit;
	int doctor;

}Patient;

extern int patientsCounter;
extern Patient patients[100];

void createPatient(char * newid, char * fName, char * sName, char * pesel, char * password);
void listDoctorsTerm(struct tm * term);
void listTermsOnDay(int day, int month);
void listTermsDoctor(char * doctor);
void createVisit();
void deleteVisit();
void modifyTerm();

#endif //SOP_P_H
