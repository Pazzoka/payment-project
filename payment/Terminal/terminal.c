#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "..\Terminal\terminal.h"
int error;
int MA;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	if (strlen(termData->transactionDate) != 10 ||
		/*for month*/termData->transactionDate[3] > '1' || termData->transactionDate[2] != '/'
		|| (termData->transactionDate[3] == '1' && termData->transactionDate[4] > '2')
		|| (termData->transactionDate[3] == '0' && termData->transactionDate[4] > '9') ||
		/*for day*/termData->transactionDate[0] > '3' || termData->transactionDate[5] != '/'
		|| (termData->transactionDate[0] == '3' && termData->transactionDate[1] > '1')
		|| (termData->transactionDate[0] == '2' && termData->transactionDate[1] > '9')
		|| (termData->transactionDate[0] == '1' && termData->transactionDate[1] > '9')
		|| (termData->transactionDate[0] == '0' && termData->transactionDate[1] > '9')||(termData->transactionDate == NULL)) {
		error = WRONG_DATE;
		return WRONG_DATE;
	}
	else {
		error = TERMINAL_OK;
		return TERMINAL_OK;
	}	
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {

	int monE; int yearE; int yearT; int monT; int dayT;
	char ED[6];
	strcpy(ED, cardData->cardExpirationDate);
	char* token = strtok(ED,"/");
	char* token2 = strtok(NULL, "/");
	monE = atoi(token);
	yearE = atoi(token2);
	char TD[6];
	strcpy(TD, termData->transactionDate);
	char* token3 = strtok(TD, "/");
	char* token4 = strtok(NULL, "/");
	char* token5 = strtok(NULL, "/");
	monT = atoi(token4);
	yearT = atoi(token5) % 100;
	
	if (yearE < yearT ||
		yearE >= yearT && monE < monT) {
		//printf("%s", cardData->cardExpirationDate);
		error = EXPIRED_CARD;
		return EXPIRED_CARD;
	}
	else {
		error = TERMINAL_OK;
		return  TERMINAL_OK;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
	if (termData->transAmount <= 0) {
	
		error = INVALID_AMOUNT;
		return INVALID_AMOUNT;
	}
	else {
		error = TERMINAL_OK;
		return TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	if (termData->maxTransAmount <= 0) {
		error = INVALID_MAX_AMOUNT;
		return INVALID_MAX_AMOUNT;
	}
	else {
		error = TERMINAL_OK;
		return TERMINAL_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->maxTransAmount < termData->transAmount) {
		error = EXCEED_MAX_AMOUNT;
		return EXCEED_MAX_AMOUNT;
	}
	else {
		error = TERMINAL_OK;
		return TERMINAL_OK;
	}
}


void getTransactionDateTest(void){
	ST_terminalData_t termdata;
    char testError[15];
	printf("\n###########################\n");
printf("Tester name: Amr Maged Hanafy \n");
printf("test Function: getTransactionDate \n\n\n");

/*test case 1:month unit more than 2*/
printf("test case 1:month unit more than 2\n");
printf("input data:20/13/2022\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate,"20/13/2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);



/*test case 2:month tenth more than 1*/
printf("test case 2:month tenth more than 2\n");
printf("input data:20/21/2022\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate, "20/23/2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);






/*test case 3:there is no '/' */
printf("test case 3:there is no '/' \n");
printf("input data:20.11.2022\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate, "20.23.2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);



/*test case 4:strlen not equal 10 */
printf("test case 4:strlen not equal 5\n");
printf("input data:20/110/2022\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate, "21/113/2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);


/*test case 5:day month more than 3*/
printf("test case 5:day month more than 3\n");
printf("input data:41/11/2022\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate, "41/11/2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);



/*test case 6:day month more than 3*/
printf("test case 6:equal to NULL\n");
printf("input data:\n");
printf("expected result: WRONG_DATE\n");
strcpy(termdata.transactionDate, "\n");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n\n", testError);




    /*test case 7:right date  */
printf("test case 7:right date  \n");
printf("input data:11/11/2022\n");
printf("expected result: TERMINAL_OK\n");
strcpy(termdata.transactionDate, "11/11/2022");

getTransactionDate(&termdata);
if (error == TERMINAL_OK) {
	strcpy(testError, "TERMINAL_OK");
}
if (error == WRONG_DATE) {
	strcpy(testError, "WRONG_DATE");
}
//printf("%d\n", error);
printf("Actual result: %s\n", testError);


printf("###########################\n\n\n");






}
void isCardExpriedTest(void) {
	ST_terminalData_t termdata;
	ST_cardData_t cardData;
	char testError[15];

	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: isCardExpired\n\n\n");

	/*test case 1:expired because of the year of expired is more*/
	printf("test case 1:the year of transation is more\n");
	printf("input data E.D:01/21\n");
	strcpy(termdata.transactionDate, "02/01/2023");
	printf("input data T.D:%s\n",termdata.transactionDate);
	printf("expected result: EXPIRED_CARD\n");
	strcpy(cardData.cardExpirationDate, "01/21");
	
	//puts(termdata.transactionDate);
	getCardExpiryDate(&cardData);
	isCardExpired(&cardData,&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "EXPIRED_CARD");
	}

	printf("Actual result: %s\n\n", testError);


	/*test case 2:the month of expired is more with the same year*/
	printf("test case 2:the month of expired is more with the same year\n");
	printf("input data E.D:01/23\n");
	strcpy(termdata.transactionDate, "02/02/2023");
	printf("input data T.D:%s\n",termdata.transactionDate);
	printf("expected result: EXPIRED_CARD\n");
	strcpy(cardData.cardExpirationDate, "01/23");
	
	//puts(termdata.transactionDate);
	getCardExpiryDate(&cardData);
	isCardExpired(&cardData,&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "EXPIRED_CARD");
	}

	printf("Actual result: %s\n\n", testError);


	/*test case 3:the year of expired is more*/
	printf("test case 3:the year of expired is more\n");
	printf("input data E.D:01/24\n");
	strcpy(termdata.transactionDate, "02/01/2023");
	printf("input data T.D:%s\n", termdata.transactionDate);
	printf("expected result: TERMINAL_OK\n");
	strcpy(cardData.cardExpirationDate, "01/24");

	//puts(termdata.transactionDate);
	//getCardExpiryDate(&cardData);
	isCardExpired(&cardData, &termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "EXPIRED_CARD");
	}

	printf("Actual result: %s\n\n", testError);



	/*test case 4:the year of transaction is equal to expired*/
	printf("test case 4:the year of transaction is equal to expired\n");
	printf("input data E.D:01/23\n");
	strcpy(termdata.transactionDate, "02/01/2023");
	printf("input data T.D:%s\n", termdata.transactionDate);
	printf("expected result: TERMINAL_OK\n");
	strcpy(cardData.cardExpirationDate, "01/23");

	//puts(termdata.transactionDate);
	getCardExpiryDate(&cardData);
	isCardExpired(&cardData, &termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "EXPIRED_CARD");
	}

	printf("Actual result: %s\n", testError);

	printf("###########################\n\n\n");
}
void getTransactionAmountTest(void) {

	ST_terminalData_t termdata;
	char testError[15];



	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: getTransactionAmount\n\n\n");

	/*test case 1:amount equal 0*/
	printf("test case 1:amount equal 0\n");
	printf("input data:0\n");
	printf("expected result: INVALID_AMOUNT\n");
	termdata.transAmount = 0;
	getTransactionAmount(&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == INVALID_AMOUNT) {
		strcpy(testError, "INVALID_AMOUNT");
	}

	printf("Actual result: %s\n\n", testError);


	/*test case 2:amount accepted */
	printf("test case 2:amount accepted \n");
	printf("input data:2000\n");
	printf("expected result: TERMINAL_OK\n");
	termdata.transAmount = 2000;
	getTransactionAmount(&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == INVALID_AMOUNT) {
		strcpy(testError, "INVALID_AMOUNT");
	}

	printf("Actual result: %s\n", testError);

	printf("###########################\n");

}
void setMaxAmountTest(void) {

	ST_terminalData_t termdata;
	char testError[15];

	

	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: setMaxAmount\n\n\n");

	/*test case 1:amount equal 0*/
	printf("test case 1:amount equal 0\n");
	printf("input data:0\n");
	printf("expected result: INVALID_MAX_AMOUNT\n");
	termdata.maxTransAmount =0.0;
	setMaxAmount(&termdata,MA);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == INVALID_MAX_AMOUNT) {
		strcpy(testError, "INVALID_MAX_AMOUNT");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 2:amount accepted */
	printf("test case 2:amount accepted \n");
	printf("input data:2000\n");
	printf("expected result: TERMINAL_OK\n");
	termdata.maxTransAmount = 2000;
	setMaxAmount(&termdata, MA);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == INVALID_MAX_AMOUNT) {
		strcpy(testError, "INVALID_MAX_AMOUNT");
	}

	printf("Actual result: %s\n", testError);

	printf("###########################\n");

}
void isBelowMaxAmountTest(void) {
	ST_terminalData_t termdata;
	char testError[15];



	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: isBelowMaxAmount\n\n\n");

	/*test case 1:not below*/
	printf("test case 1:not below\n");
	printf("input data max ammount :2000\n");
	printf("input data trans ammount :5000\n");
	printf("expected result: EXCEED_MAX_AMOUNT\n");
	termdata.maxTransAmount = 2000;
	termdata.transAmount = 5000;
	//setMaxAmount(&termdata, MA);
	//getTransactionAmount(&termdata);
	isBelowMaxAmount(&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == EXCEED_MAX_AMOUNT) {
		strcpy(testError, "EXCEED_MAX_AMOUNT");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 1:below*/
	printf("test case 1:below\n");
	printf("input data max ammount :2000\n");
	printf("input data trans ammount :1000\n");
	printf("expected result: TERMINAL_OK\n");
	termdata.maxTransAmount = 2000;
	termdata.transAmount = 1000;
	setMaxAmount(&termdata, MA);
	getTransactionAmount(&termdata);
	isBelowMaxAmount(&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == EXCEED_MAX_AMOUNT) {
		strcpy(testError, "EXCEED_MAX_AMOUNT");
	}
	printf("Actual result: %s\n\n", testError);




	/*test case 3:equal*/
	printf("test case 1:equal \n");
	printf("input data max ammount :2000\n");
	printf("input data trans ammount :2000\n");
	printf("expected result: TERMINAL_OK\n");
	termdata.maxTransAmount = 2000;
	termdata.transAmount = 2000;
	//setMaxAmount(&termdata, MA);
	//getTransactionAmount(&termdata);
	isBelowMaxAmount(&termdata);
	if (error == TERMINAL_OK) {
		strcpy(testError, "TERMINAL_OK");
	}
	if (error == EXCEED_MAX_AMOUNT) {
		strcpy(testError, "EXCEED_MAX_AMOUNT");
	}
	printf("Actual result: %s\n", testError);

	printf("###########################\n");

}



























	
	
	

