
#include "..\Card\card.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int error;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	if ((strlen(cardData->cardHolderName) > 24) || (strlen(cardData->cardHolderName) < 20)  || (cardData->cardHolderName == NULL))
	{
		error = WRONG_NAME;
		return WRONG_NAME;
	}
	else
	{
		error = CARD_OK;
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	if (cardData->cardExpirationDate[0] > '1' || cardData->cardExpirationDate[2] != '/'
		|| strlen(cardData->cardExpirationDate) != 5 || (cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1] > '2')
		|| (cardData->cardExpirationDate[0] == '0' && cardData->cardExpirationDate[1] > '9')||cardData->cardExpirationDate==NULL) {
		error = WRONG_EXP_DATE;
		return WRONG_EXP_DATE;
		
	}
	else {
		error = CARD_OK;
		return CARD_OK;
	}	
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || cardData->primaryAccountNumber == NULL) {
		error = WRONG_PAN;
		return WRONG_PAN;
	}
	else{
		error = CARD_OK;
		return CARD_OK;
	}
}


void getCardHolderNametest(void) {
	ST_cardData_t cardData;
	char testError[15];
	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: getCardHolderName \n");


	printf("test case 1: input <20 char \n");
	printf("input data: amr maged\n");
	printf("expected result: WRONG_NAME\n");
	strcpy(cardData.cardHolderName, "amr maged");
	getCardHolderName(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_NAME){
		strcpy(testError, "WRONG_NAME");
	}
	printf("Actual result: %s\n\n",testError);


	printf("test case 2: input >24 char\n");
	printf("input data: amr maged hanafy mohamed mohamed\n");
	printf("expected result: WRONG_NAME\n");
	strcpy(cardData.cardHolderName, "amr maged hanafy mohamed mohamed");
	getCardHolderName(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_NAME) {
		strcpy(testError, "WRONG_NAME");
	}
	printf("Actual result: %s\n\n", testError);

	printf("test case 3: input = NULL\n");
	printf("input data:\0");
	strcpy(cardData.cardHolderName,"\0\n");
	printf("%s\n", cardData.cardHolderName);
	if ((getCardHolderName(&cardData)) == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	else {
		strcpy(testError, "WRONG_NAME");
	}
	printf("expected result: WRONG_NAME\n");
	printf("Actual result: %s\n\n", testError);

	
	printf("test case 3: 20<input <24\n");
	printf("input data:amr maged hanafy mohamed \n");
	printf("expected result: CARD_OK\n");
	strcpy(cardData.cardHolderName, "amr maged hanafy moha\n");
	getCardHolderName(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_NAME) {
		strcpy(testError, "WRONG_NAME");
	}
	printf("Actual result: %s\n", testError);
	printf("###########################\n\n\n");
}
void getCardExpiryDatetest(void) {
	ST_cardData_t cardData;
	char testError[15];
	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: getCardExpiryDate \n\n\n");

	/*test case 1:month unit more than 2*/
	printf("test case 1:month unit more than 2\n");
	printf("input data:13/25\n");
	printf("expected result: WRONG_EXP_DATE\n");
	strcpy(cardData.cardExpirationDate,"13/25");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE){
		strcpy(testError, "WRONG_EXP_DATE");
	}
	
	printf("Actual result: %s\n\n", testError);

	/*test case 2:month tenth more than 1*/
	printf("test case 2:month tenth more than 1\n");
	printf("input data:21/21\n");
	printf("expected result: WRONG_EXP_DATE\n");
	strcpy(cardData.cardExpirationDate, "21/21");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "WRONG_EXP_DATE");
	}

	printf("Actual result: %s\n\n", testError);


	/*test case 3:there is no '/' */
	printf("test case 3:there is no '/' \n");
	printf("input data:11.11\n");
	printf("expected result: WRONG_EXP_DATE\n");
	strcpy(cardData.cardExpirationDate, "11.11");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "WRONG_EXP_DATE");
	}

	printf("Actual result: %s\n\n", testError);


	/*test case 4: strlen not equal 5  */

	printf("test case 4: strlen not equal 5  \n");
	printf("input data:110/21\n");
	printf("expected result: WRONG_EXP_DATE\n");
	strcpy(cardData.cardExpirationDate, "110/21");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "WRONG_EXP_DATE");
	}

	printf("Actual result: %s\n\n", testError);

	printf("test case 5:equal NULL\n");
	printf("input data:\n");
	printf("expected result: WRONG_EXP_DATE\n");
	strcpy(cardData.cardExpirationDate, "\n");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "WRONG_EXP_DATE");
	}
	printf("Actual result: %s\n\n", testError);

       //test case 6: right date 
	printf("test case 6: right date  \n");
	printf("input data:11/11\n");
	printf("expected result: CARD_OK\n");
	strcpy(cardData.cardExpirationDate, "11/11");
	getCardExpiryDate(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_EXP_DATE) {
		strcpy(testError, "WRONG_EXP_DATE");
	}
	printf("Actual result: %s\n", testError);
	printf("###########################\n\n\n");
}
void getCardPANtest(void) {
	ST_cardData_t cardData;
	char testError[15];
	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: getCardPAN \n\n\n");


	/*test case 1:strlen <16*/
	printf("test case 1:strlen <16\n");
	printf("input data:123456789\n");
	printf("expected result: WRONG_PAN\n");
	strcpy(cardData.primaryAccountNumber, "123456789");
	getCardPAN(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_PAN) {
		strcpy(testError, "WRONG_PAN");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 2:strlen >19*/
	printf("test case 2:strlen >19\n");
	printf("input data:01234567891234567891\n");
	printf("expected result: WRONG_PAN\n");
	strcpy(cardData.primaryAccountNumber, "01234567891234567891");
	getCardPAN(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_PAN) {
		strcpy(testError, "WRONG_PAN");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 3:strlen >19*/
	printf("test case 3: equal to NULL\n");
	printf("input data:\n");
	printf("expected result: WRONG_PAN\n");
	strcpy(cardData.primaryAccountNumber, "\0");
	getCardPAN(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_PAN) {
		strcpy(testError, "WRONG_PAN");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 4:16<strlen<19*/
	printf("test case 3:16<strlen<19\n");
	printf("input data:013245678912345603\n");
	printf("expected result: CARD_OK\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345603");
	getCardPAN(&cardData);
	if (error == CARD_OK) {
		strcpy(testError, "CARD_OK");
	}
	if (error == WRONG_PAN) {
		strcpy(testError, "WRONG_PAN");
	}
	printf("Actual result: %s\n", testError);
	printf("###########################\n\n\n");
}

