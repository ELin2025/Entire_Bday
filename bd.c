#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <climits>


int compare(time_t, time_t, time_t);
char* readLine(FILE* f);
main(){
	time_t currentTime = time(NULL);
	char ch;
	int count=0;
	int counter =0;	
	FILE *fp = fopen("Data.txt", "r");
	if(fp == NULL){
		printf("Cannot find file");
		return 0;
	}
	while((ch = fgetc(fp)) != EOF){
		while(ch != '\n'){
			ch = (char)fgetc(fp);
		}
		counter++;
		if(counter==8){
			count++;
			counter =0;
		}
	}
	fclose(fp);
	int isName = 1;
	char* names[count];
	struct tm prepare[count];
	time_t bday[count];
	int byear[count];
	FILE* f = fopen("Data.txt", "r");
	int counte = 0;
	while((ch = fgetc(f)) != EOF){
		char* h = (char*)malloc(1000);
		h[0] = '\0';
		char* cha = (char*)malloc(sizeof(&ch));
		while(ch != '\n'){
			cha = &ch;
			*(cha+1) = *("");
			strcat(h, cha);
			ch = fgetc(f);
		}
		ch = fgetc(f);
		if(isName==1){	
			names[counte] = h;
			while(ch != '\n'){
				ch = fgetc(f);
			}
			isName = 0;
		}
		else{
			char* day = (char*)malloc(sizeof(h));
			day = h + 8;
			char* year= (char*)malloc(sizeof(h));
			for(int i = 0; i< 4; i++){
				*(year+i) =*(h);
				h++;
			}
			h++;
			char*month =(char*)malloc(sizeof(h));
			for(int i = 0; i< 2; i++){
				*(month+i) = *(h);
				h++;
			}
			sscanf(day, "%d", &prepare[counte].tm_mday);
			sscanf(month, "%d", &prepare[counte].tm_mon);
			sscanf(year, "%d", &byear[counte]);
			struct tm* now = localtime(&currentTime);
			prepare[counte].tm_year =  now->tm_year;
			prepare[counte].tm_mon = prepare[counte].tm_mon - 1;
			prepare[counte].tm_sec = 59;
			prepare[counte].tm_min = 59;
			prepare[counte].tm_hour = 23+1;
			for(int i =0; i< 5;i++){
				while(ch != '\n'){
					ch = fgetc(f);
				}
				if(i==4){
					break;
				}
				ch = fgetc(f);
			}	
			isName = 1;
			counte++;
		}
		free(h);
		free(cha);
		
	}
	fclose(f);
	int b = 0;
	for(int i = 0; i< count;i++){
		bday[i] = mktime(&prepare[i]);
		if(difftime(bday[i], currentTime) >= 0){
			b++;
		}
	}
	int age[b];
	time_t valid[b];
	char* validName[b];
	time_t final[b];
	char* finalName[b];
	int finalAge[b];
	int a = 0;
	for(int i = 0; i<count; i++){
		if(difftime(bday[i], currentTime)>=0){
			valid[a] = bday[i];
			validName[a] = names[i];
			age[a] =prepare->tm_year-  (byear[i]- 1900) ;
			a++;
		}
	}
	char* string;
	time_t recent;
	recent = valid[0];
	for(int i  = 0; i< b; i++){
		if(difftime(valid[i], currentTime) >= 0){
			if(compare(valid[i], recent, currentTime) <=0){
				recent= valid[i];
			}
		}
	}
	int an = 0;
	struct tm *cur = localtime(&currentTime);
	cur->tm_hour =23;
	cur->tm_min = 59;
	cur->tm_sec = 59;
	time_t current = mktime(cur);
	int d = difftime(recent, current)/3600/24;
	for(int i = 0; i< b; i++){
		if(compare(valid[i], recent, currentTime) == 0 ){
			final[an] = valid[i];
			finalName[an] = validName[i];	
			finalAge[an] = age[i];
			an++;
		}
	}
	finalName[an] = (char*)"done";
	FILE *file;
		file = fopen("read.txt", "w");
		if(file== NULL){
			return 0 ;
		}
		currentTime = time(NULL);
		struct tm *hi = localtime(&currentTime);
		if(hi->tm_hour > 12){
			hi->tm_hour = hi->tm_hour-12;
		}
		currentTime = mktime(hi);
		char* edit = (char*)malloc(sizeof(ctime(&currentTime)));
		char* temp = (char*)malloc(sizeof(edit));
		temp = ctime(&currentTime);
		edit[0] = '\0';
		for(int i = 0; i<10;i++){
			*(edit + i) = *(temp);
			temp++;
		}
		*(edit+10) = *("");
		string = ctime(&currentTime) + 20;
		strcat(edit, " ");
		strcat(edit, string);
		fprintf(file, "Today's date is %s", edit);
		for(int i = 0; i< b; i++){
			if(finalName[i] == "done"){
				break;
			}
			if(d == 0){
				fprintf(file, "%s is %d years old today. HAPPY BIRTHDAY!!!!", finalName[i], finalAge[i]);
			}
			else if(d<= 3){
				fprintf(file, "%s is going to be %d years old in %d days", finalName[i], finalAge[i], d);
			}
	}
	fclose(file);
	return 0;
}
int compare(time_t y, time_t n, time_t current){
	if(difftime(y, current)>difftime(n, current)){
		return 1;
	}
	else if(difftime(y, current)==difftime(n,current)){
		return 0;
	}
	else{
		return -1;
	}
}	
