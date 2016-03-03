#include "headers.h"




void createPatient(char * newid, char * fName, char * sName, char * pesel, char * password){

	strcpy(patients[patientsCounter].id, newid);
	strcpy(patients[patientsCounter].firstName, fName);
	strcpy(patients[patientsCounter].secondName, sName);
	strcpy(patients[patientsCounter].pesel, pesel);
	strcpy(patients[patientsCounter].password, password);
	patients[patientsCounter].registered = false;

	patientsCounter++;
}

void listDoctorsTerm(struct tm * term){

}

void listTermsOnDay(int day, int month){
	
}

void listTermsDoctor(char * doctor){

}

void createVisit(){

	int i;
	int doctor = msg1.number[1];
	int patient = msg1.number[0];
	struct tm tmpdate = msg1.time[0];



	for(i=0; i<20; i++){

		if(tmpdate.tm_mon == doctors[doctor].visitsTab[i].tm_mon && 
				tmpdate.tm_mday == doctors[doctor].visitsTab[i].tm_mday &&
				tmpdate.tm_hour == doctors[doctor].visitsTab[i].tm_hour &&
				tmpdate.tm_min == doctors[doctor].visitsTab[i].tm_min ||
				doctors[doctor].visitsCounter > 19){

			msg2.error = -1;

		}
		else{
			patients[patient].visit = tmpdate;
			patients[patient].doctor = doctor;
			patients[patient].registered = true;
			doctors[doctor].visitsTab[doctors[doctor].visitsCounter] = tmpdate;
			doctors[doctor].patientsTab[doctors[doctor].visitsCounter] = patient;
			doctors[doctor].visitsCounter++;
			msg2.error = 1;
		}	
	}

	msg2.mtype = msg1.pid;
	msgsnd(msqid2, &msg2, sizeof(msg2) - sizeof(long), 0);

	return;
}

void deleteVisit(){

	int patient = msg1.number[0];

	if(patients[patient].registered == true){
		patients[patient].registered = false;
		msg2.time[0] = patients[patient].visit;
		msg2.error = 1;
	}
	else{
		msg2.error = -1;
	}

	msg2.mtype = msg1.pid;
	msgsnd(msqid2, &msg2, sizeof(msg2) - sizeof(long), 0);
}

void modifyTerm(){

}
