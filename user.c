#include "headers.h"

int pid;

int main(){

	int input;
	time_t tmp;	
	struct tm * visit;



	msqid1 = msgget(999, 0666);
	msqid2 = msgget(998, 0666);
	pid = (int)getpid();
printf("%d\n", pid);

	while(1){

		time(&tmp);
		visit = localtime(&tmp);

		printf("Wybierz:\n");
		printf("1 -- Zaloguj jako pacjent\n");
		printf("2 -- Zaloguj jako lekarz\n");
		printf("3 -- Utworz nowe konto pacjenta\n");
		scanf("%d", &input);

		if(input == 1){
			int patientNumber = loginPatient();

			while(patientNumber != -1){

				printf("Wybierz:\n");
				printf("1 -- Zarezerwuj termin wizyty\n");
				printf("2 -- Odwolaj wizyte\n");
				printf("3 -- Zmien termin wizyty\n");
				printf("4 -- Pokaz wolnych lekarzy w danym terminie\n");
				printf("5 -- Pokaz wolne terminy w dniu\n");
				printf("6 -- Pokaz wolne terminy danego lekarza\n");
				printf("7 -- Wyjdz\n");
				scanf("%d", &input);

				if(input == 7) break;

				switch(input){
					case 1:{
							 //utworz wizyte
							int doctor;

							do{
								printf("Wybierz lekarza: \n");
								printf("0 --- Jan Kowalski\n");
								printf("1 --- Krystian Nowak\n");
								printf("2 --- Przemyslaw Shmidt\n");
								scanf("%d", &doctor);
							}while(doctor < 0 || doctor > 2);


							do{
								printf("Podaj dzien i miesiac: \n");
								scanf("%d %d", &visit->tm_mday, &visit->tm_mon);
							}while(visit->tm_mday <0 || visit->tm_mday >31 || 
									visit->tm_mon < 0 || visit->tm_mon >11);

							do{
								printf("Podaj godzine (co 20 min): \n");
								scanf("%d %d", &visit->tm_hour, &visit->tm_min);
							}while(visit->tm_hour < 0 || visit->tm_hour > 23 || 
									visit->tm_min < 0 || visit->tm_min > 59);


							msg1.time[0] = *visit;
							msg1.number[0] = patientNumber;
							msg1.number[1] = doctor;
							msg1.pid = pid;
							msg1.mtype = 6;
							msgsnd(msqid1, &msg1, sizeof(msg1) - sizeof(long), 0);

							msgrcv(msqid2, &msg2, sizeof(msg2) - sizeof(long), pid, 0);

							if(msg2.error == 1){
								printf("----Termin zarezerwowany----\n");
								
							}
							else{
								printf("####Termin niedostepny####\n");
							}
							
							break;
						 }
					case 2:{
							 //odwolaj
							
							break;
						 }
					case 3:
						 {
							 //zmien termin
							break;
						 }
					case 4:
						 {
							 //lista lekarzy w danym terminie
							break;
						 }
					case 5:
						 {
							 //lista terminow w danym dniu
							int day;
							int month;
							printf("Podaj dzien miesiaca: (1 - 31)\n");
							scanf("%d\n", &day);
							printf("Podaj miesiac: (0 - styczen, 11 - grudzien)\n");
							scanf("%d\n", &month);
							listTermsOnDay(day, month);
							break;
						 }
					case 6:
						 {
							 //lista terminow lekarza
							break;
						 }
					default:
						 {	
							break;
						 }
				}
			}			
		}
		else if(input == 2){

			int doctorNumber = loginDoctor();

			while(doctorNumber != -1){
				printf("Wybierz:\n");
				printf("1 -- Wyswietl wizyty\n");
				printf("2 -- Wez urlop\n");
				printf("3 -- Wyjdz\n");
				scanf("%d", &input);

				if(input == 3) break;

				switch(input){
					case '1':{
							 //wyswietlanie wizyt
							break;
						 }
					case '2':{
							 //urlop
							break;
						 }
					default: {
							break;
						 }
				}
			}
		}
		else if(input == 3){

			msg1.mtype = 2;
			printf("Podaj login:\n");
			scanf("%s", msg1.tab1);
			printf("Podaj imie:\n");
			scanf("%s", msg1.tab2);
			printf("Podaj nazwisko:\n");
			scanf("%s", msg1.tab3);
			printf("Podaj pesel:\n");
			scanf("%s", msg1.tab4);
			printf("Podaj haslo:\n");
			scanf("%s", msg1.tab5);
			msgsnd(msqid1, &msg1, sizeof(msg1) - sizeof(long), 0);
		}
	}
	return 0;
}



int loginPatient(){
	if(fork() == 0){
		char login[30];
		char pas[30];
		bool logged = false;
		int counter = 0;

		while(!logged){

			printf("Podaj login:\n");
			scanf("%s", login);
			printf("Podaj haslo:\n");
			scanf("%s", pas);

			strcpy(msg1.tab1, login);
			strcpy(msg1.tab2, pas);
			msg1.pid = pid;
			msg1.mtype = 1;

			msgsnd(msqid1, &msg1, sizeof(msg1) - sizeof(long), 0);

			msgrcv(msqid2,&msg2,sizeof(msg2) - sizeof(long),pid,0);
			if(msg2.error == -1){
				printf("Blad logowania, sproboj ponownie\n");
				if(++counter == 3) return -1;
			}
			else if(msg2.error == 1){
				logged = true;
			}
		}
		printf("----Zalogowano----\n");
		return msg2.number[0];
	}
	wait(NULL);
}

int loginDoctor(){
	if(fork() == 0){
		char login[30];
		char pas[30];
		bool logged = false;

		while(!logged){

			printf("Podaj login:\n");
			scanf("%s", login);
			printf("Podaj haslo:\n");
			scanf("%s", pas);

			strcpy(msg1.tab1, login);
			strcpy(msg1.tab2, pas);
			msg1.pid = pid;
			msg1.mtype = 9;

			msgsnd(msqid1, &msg1, sizeof(msg1) - sizeof(long), 0);

			msgrcv(msqid2,&msg2,sizeof(msg2) - sizeof(long),pid,0);
			if(msg2.error == -1){
				printf("Blad logowania, sproboj ponownie\n");
			}
			else if(msg2.error == 1){
				logged = true;
			}
		}
		printf("----Zalogowano----\n");
		return msg2.number[0];
	}
	wait(NULL);
}

void listTermsOnDay(int day, int month){

	msg1.mtype = 4;
	msg1.number[0] = day;
	msg1.number[1] = month;

	msgsnd(msqid1, &msg1, sizeof(msg1) - sizeof(long), 0);
}



