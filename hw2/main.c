#include<stdio.h>
#include<stdlib.h> 
#include<time.h>
#include <string.h>

FILE* lottoFile;
FILE* countFile;
FILE* operatorFile;
FILE* salesRecordFile; 
static int currentCount;
static int id, idArr[1];
static char name[32];
static char date[32];
static char Time[32];

typedef struct lottoRecord {
	int lotto_no;
	int lotto_receipt;
	int emp_id;
	char lotto_date[32];
	char lotto_time[32];
}lotto_record_t; 

typedef struct employeeRecord {
	int emp_id;
	char emp_name[32];
	int emp_salary;
}emp_record_t;

void recordTheEmployee(int salary) {
	emp_record_t recordEmployee;
	recordEmployee.emp_id = id;
	strcpy(recordEmployee.emp_name, name);
	recordEmployee.emp_salary = salary;
	
	operatorFile = fopen("operator_id.txt","ab");
	fwrite(&recordEmployee, sizeof(recordEmployee), 1, operatorFile);
	fclose(operatorFile);
}

void cutTheTime() { 
	time_t now = time(0);
	strftime(date, 100, "%Y%m%d", localtime(&now));
	strftime(Time, 100, "%H:%M:%S", localtime(&now));
}

void setAndOutputRecords() {
	lotto_record_t doRecord;
	doRecord.lotto_no = currentCount;
	doRecord.lotto_receipt = currentCount*55;
	doRecord.emp_id = id;
	strcpy(doRecord.lotto_date, date);
	strcpy(doRecord.lotto_time, Time);

	salesRecordFile = fopen("salesRecordFile.bin","ab");
	fwrite(&doRecord, sizeof(doRecord), 1, salesRecordFile);
	fclose(salesRecordFile);
}



void countTimes() { 
    int read[1];
    int write[1];    
    if((countFile = fopen("countFile.bin", "r")) == NULL) {
        countFile = fopen("countFile.bin", "wb+");
        write[0] = 1;       
        fwrite(write, sizeof(int), 1, countFile);
    }
    else {
        countFile = fopen("countFile.bin", "rb+");
        fseek(countFile, 0, SEEK_SET);
        fread(read, sizeof(int), 1, countFile);
        fclose(countFile);    
        write[0] = read[0] + 1;
        countFile = fopen("countFile.bin", "wb+");
        fwrite(write, sizeof(int), 1, countFile);
    }
    fclose(countFile);
    currentCount = write[0];
}  

void get_6_RandNum() { 
    int r[12];
    int i = 0, j, box;
    while(i<=5){
        box = rand()%69+1;
        for(j = 0; j < i; j++){
            if(box == r[j])break;
        }
        if(j == i){
            r[i] = box;
            i++;
        }
    }
    for (int a = 0; a < 6; ++a) {
        for (int b = 0; b < a; ++b) {
              if (r[b] > r[a]) {
            int temp = r[b];
            r[b] = r[a];
            r[a] = temp;
            }    
           }
    }
    r[6] = rand()%10+1;
    for(j = 0; j <= 6; j++){
        fprintf(lottoFile,"%02d ",r[j]);
    }
}


int main(){
	

    int a,i;
    char lottoFileName[80];
    printf("welcome to the lottery machine(?)\n");
    printf("please input the operator ID:");
    scanf("%d",&id);
	

    if(id == 0){

        int salary;

        printf("please input the ID you want to add:");
        scanf("%d",&id);
        printf("please input the NAME you want to add:");
        scanf("%s",name);
        printf("please input the salary you want to add:");
        scanf("%d",&salary);
        recordTheEmployee(salary);
        printf("end the input");	
    }
	
    else if(id != 0){
		
        printf("how many lottery you wanna buy:");
	scanf("%d", &i);
	printf("\noutput you %d set(s) of lottery to lotto.txt\n", i);
	
	srand(time(NULL));
	countTimes();
	sprintf(lottoFileName, "lotto[%04d].txt", currentCount);
	lottoFile = fopen(lottoFileName,"w+");
	time_t now;
	time(&now);
	char* dt = ctime(&now);
	dt[strlen(dt)-1]=0;
	fprintf(lottoFile,"========= lotto649 =========\n");
	fprintf(lottoFile,"========+ No.%05d +========\n",currentCount);
	fprintf(lottoFile,"= %s =\n", dt);
	for(a = 1; a <= i; a++){
	    fprintf(lottoFile,"= [%d]:", a);
	    get_6_RandNum();
	    fprintf(lottoFile,"=\n");
	}
	for(; a <= 5; a++)fprintf(lottoFile,"= [%d]:== == == == == == == =\n", a);
	fprintf(lottoFile, "========* Op.%05d *========\n", id);
	fprintf(lottoFile,"========= csie@CGU =========\n");
	fclose(lottoFile);
	 
	cutTheTime();
	setAndOutputRecords();
    }
}