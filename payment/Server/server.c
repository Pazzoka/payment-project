#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "..\Server\server.h"
ST_accountsDB_t accountsDB[255] = {
										{1000.0, RUNNING, "013245678912345600"},
										{2000.0, RUNNING, "013245678912345601"},
										{3000.0, RUNNING, "013245678912345602"},
										{4000.0, RUNNING, "013245678912345603"},
										{5000.0, RUNNING, "013245678912345604"},
										{6000.0, BLOCKED, "013245678912345605"},
										{7000.0, BLOCKED, "013245678912345606"},
										{8000.0, BLOCKED, "013245678912345607"},
										{9000.0, BLOCKED, "013245678912345608"},
										{10000.0,BLOCKED, "013245678912345609"}
};
int j;  int v[255] = { 0 }; int f; int error;
static uint32_t TransIndex = 0 ;
ST_transaction_t transactionsDB[255] = { 0 };
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0){
			//printf(" SERVER_OK\n");
			accountRefrence->state = accountsDB[i].state;
			accountRefrence->balance = accountsDB[i].balance;
			j = i;
			error = SERVER_OK;
			return  SERVER_OK;
         }	
	}
	//printf("ACCOUNT_NOT_FOUND\n");
	error = ACCOUNT_NOT_FOUND;
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountsDB[j].state == BLOCKED)
	{
		//printf(" BLOCKED_ACCOUNT\n");
		error = BLOCKED_ACCOUNT;
		return BLOCKED_ACCOUNT;
	}
	else if (accountsDB[j].state == RUNNING)
	{
		//printf(" RUNNING_ACCOUNT\n");
		error = SERVER_OK;
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (accountsDB[j].balance < termData->transAmount) {
		//printf(" LOW_BALANCE\n");
		//printf(" Low balance: %f\n", accountsDB[j].balance);
		error = LOW_BALANCE;
		return LOW_BALANCE;
	}
	else {
		//printf(" ENOUGH_BALANCE\n");
		//printf(" ENOUGH_BALANCE: %f\n", termData->transAmount);
		error = SERVER_OK;
		return SERVER_OK;
		
	}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	//puts(transData->cardHolderData.cardHolderName);


	if (TransIndex < 255) {

		transData->transactionSequenceNumber = TransIndex;
		transactionsDB[TransIndex].cardHolderData = transData->cardHolderData;
		transactionsDB[TransIndex].terminalData = transData->terminalData  ;
		transactionsDB[TransIndex].transState = v[TransIndex];
		transactionsDB[TransIndex].transactionSequenceNumber = transData->transactionSequenceNumber;
		TransIndex++;
		//printf("ayyyyyyyyyy :  %d ", transData->cardHolderData.cardExpirationDate);
		error = SERVER_OK;

	 return SERVER_OK;
	}
	else {
		error = SAVING_FAILED;
		return SAVING_FAILED;
	}
	/*transactionsDB[TransIndex] = *transData;
	puts(transactionsDB[TransIndex].cardHolderData.cardHolderName);
	TransIndex++;
	return SERVER_OK;*/
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	
	//transData->transState = APPROVED;
	if (isValidAccount(&transData->cardHolderData, &accountsDB) == ACCOUNT_NOT_FOUND) {
		//printf("fraud\n");
		if (f < 10) {
			v[f] = FRAUD_CARD;
			f++;
		}
		error = FRAUD_CARD;
		return  FRAUD_CARD;
	}
	if (saveTransaction(transData) == SAVING_FAILED) {
		//printf("INTERNAL_SERVER_ERROR\n");
		if (f < 10) {
			v[f] = INTERNAL_SERVER_ERROR;
			f++;
		}
		error = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	if (isAmountAvailable(&transData->terminalData, &accountsDB) == LOW_BALANCE) {
		//printf("DECLINED_INSUFFECIENT_FUND\n");
		if (f < 10) {
			v[f] = DECLINED_INSUFFECIENT_FUND;
			f++;
		}
		error = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (isBlockedAccount(&accountsDB) == BLOCKED_ACCOUNT) {
		//printf("DECLINED_STOLEN_CARD\n");
		if (f < 10) {
			v[f] = DECLINED_STOLEN_CARD;
			f++;
		}
		error = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else {
		//printf("APPROVED\n");
		if (f < 10) {
			v[f] = APPROVED;
			f++;
		}
		printf("the old balance is: %f\n", accountsDB[j].balance);
		accountsDB[j].balance = accountsDB[j].balance - transData->terminalData.transAmount;
		printf("the new balance is: %f\n", accountsDB[j].balance);
		error = APPROVED;
		return APPROVED;
	}
}
void listSavedTransactions(void) {

	//printf("%d\n", transactionsDB[TransIndex - 1].transState);

	for (uint8_t k = 0; k <= TransIndex; k++) {
		printf("\n###########################\n");
		printf("Transaction Sequence Number: %d\n", transactionsDB[k -1].transactionSequenceNumber);
		printf("Transaction Date: %s\n", transactionsDB[k -1].terminalData.transactionDate);
		printf("Transaction Amount: %f\n", transactionsDB[k-1].terminalData.transAmount);
		
	    if (v[k-1] == APPROVED) {
			printf("TransactionState:APPROVED\n");
		}
		if (v[k-1] == DECLINED_INSUFFECIENT_FUND) {
			printf("TransactionState:DECLINED_INSUFFECIENT_FUND\n");
		}
		if (v[k-1] == DECLINED_STOLEN_CARD) {
			printf("TransactionState:DECLINED_STOLEN_CARD\n");

		}
		if (v[k-1] == FRAUD_CARD) {
			printf("TransactionState:FRAUD_CARD\n");
		}
		if (v[k-1] == INTERNAL_SERVER_ERROR) {
			printf("TransactionState:INTERNAL_SERVER_ERROR\n");
		}

		printf("Terminal Max Amount: %f\n", transactionsDB[k -1].terminalData.maxTransAmount);
		printf("Card holder Name: %s\n", transactionsDB[k -1].cardHolderData.cardHolderName);
		printf("PAN:%s \n", transactionsDB[k-1].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transactionsDB[k-1].cardHolderData.cardExpirationDate);
		printf("#########################\n\n");
		
	}
}
void isValidAccountTest(void)    {
	ST_cardData_t cardData;
	char testError[15];

	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: isValidAccount\n\n\n");

	/*test case 1:account found*/
	printf("test case 1:account found\n");
	printf("input data:013245678912345604\n");
	printf("expected result: SERVER_OK\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345604");
	isValidAccount(&cardData, &accountsDB);
	
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == ACCOUNT_NOT_FOUND) {
		strcpy(testError, "ACCOUNT_NOT_FOUND");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 2:account not found*/
	printf("test case 2:account not found\n");
	printf("input data:0132456789123456045\n");
	printf("expected result: ACCOUNT_NOT_FOUND\n");
	strcpy(cardData.primaryAccountNumber, "0132456789123456045");
	isValidAccount(&cardData, &accountsDB);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == ACCOUNT_NOT_FOUND) {
		strcpy(testError, "ACCOUNT_NOT_FOUND");
	}
	printf("Actual result: %s\n", testError);
	printf("\n###########################\n\n");
}
void isBlockedAccountTest(void) {
	ST_cardData_t cardData;
	char testError[15];

	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: isBlockedAccount\n\n\n");

	/*test case 1:account Running*/
	printf("test case 1:account Running\n");
	printf("input data:013245678912345604\n");
	printf("expected result: SERVER_OK\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345604");
	isValidAccount(&cardData, &accountsDB);
	isBlockedAccount(&accountsDB);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == BLOCKED_ACCOUNT) {
		strcpy(testError, "BLOCKED_ACCOUNT");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 2:account Blocked*/
	printf("test case 2:account Blocked\n");
	printf("input data:013245678912345606\n");
	printf("expected result: BLOCKED_ACCOUNT\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345606");
	isValidAccount(&cardData, &accountsDB);
	isBlockedAccount(&accountsDB);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == BLOCKED_ACCOUNT) {
		strcpy(testError, "BLOCKED_ACCOUNT");
	}
	printf("Actual result: %s", testError);
	printf("\n###########################\n\n");
}
void isAmountAvailableTest(void) {
	ST_cardData_t cardData;
	ST_terminalData_t termdata;
	char testError[15];

	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: isAmountAvailable\n\n\n");

	/*test case 1:amount available*/
	printf("test case 1:ammount available\n");
	printf("input data PAN:013245678912345604\n");
	printf("input data trans amount:3000\n");
	printf("expected result: SERVER_OK\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345604");
	termdata.transAmount = 3000;
	isValidAccount(&cardData, &accountsDB);
	isAmountAvailable(&termdata, &accountsDB);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == LOW_BALANCE) { 
		strcpy(testError, "LOW_BALANCE");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 2:low BALANCE*/
	printf("test case 1:low balance\n");
	printf("input data PAN:013245678912345604\n");
	printf("input data trans amount:6000\n");
	printf("expected result: LOW_BALANCE\n");
	strcpy(cardData.primaryAccountNumber, "013245678912345604");
	termdata.transAmount = 6000;
	isValidAccount(&cardData, &accountsDB);
	isAmountAvailable(&termdata, &accountsDB);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == LOW_BALANCE) {
		strcpy(testError, "LOW_BALANCE");
	}
	printf("Actual result: %s", testError);
	printf("\n###########################\n\n");






}
void recieveTransactionDataTest(void) {
	
 	ST_transaction_t trans;
	char testError[15];


	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: recieveTransactionData\n\n\n");

	/*test case 1:account not found*/
	printf("test case 1:account not found\n");
	printf("input data PAN:0132456789123456045\n");
	printf("input data trans amount:3000\n");
	printf("input data TransIndex:1\n");
	printf("expected result: FRAUD_CARD\n");
	strcpy(trans.cardHolderData.primaryAccountNumber, "01324567891234560455");
	trans.terminalData.transAmount = 3000;
	TransIndex = 1;
	recieveTransactionData(&trans);
	if (error == APPROVED) {
		strcpy(testError, "APPROVED");
	}
	if (error == FRAUD_CARD) {
		strcpy(testError, "FRAUD_CARD");
	}
	if (error == DECLINED_INSUFFECIENT_FUND) {
		strcpy(testError, "DECLINED_INSUFFECIENT_FUND");
	}
	if (error == INTERNAL_SERVER_ERROR) {
		strcpy(testError, "INTERNAL_SERVER_ERROR");
	}
	if (error == DECLINED_STOLEN_CARD) {
		strcpy(testError, "DECLINED_STOLEN_CARD");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 2:low balance*/
	printf("test case 2:low balance\n");
	printf("input data PAN:013245678912345604\n");
	printf("input data trans amount:7000\n");
	printf("input data TransIndex:1\n");
	printf("expected result: DECLINED_INSUFFECIENT_FUND\n");
	strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345604");
	trans.terminalData.transAmount = 7000;
	TransIndex = 1;
	recieveTransactionData(&trans);
	if (error == APPROVED) {
		strcpy(testError, "APPROVED");
	}
	if (error == FRAUD_CARD) {
		strcpy(testError, "FRAUD_CARD");
	}
	if (error == DECLINED_INSUFFECIENT_FUND) {
		strcpy(testError, "DECLINED_INSUFFECIENT_FUND");
	}
	if (error == INTERNAL_SERVER_ERROR) {
		strcpy(testError, "INTERNAL_SERVER_ERROR");
	}
	if (error == DECLINED_STOLEN_CARD) {
		strcpy(testError, "DECLINED_STOLEN_CARD");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 3:saving faild*/
	printf("test case 3:saving faild\n");
	printf("input data PAN:013245678912345604\n");
	printf("input data trans amount:3000\n");
	printf("input data TransIndex:300\n");
	printf("expected result: INTERNAL_SERVER_ERROR\n");
	strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345604");
	trans.terminalData.transAmount = 3000;
	TransIndex = 300;
	recieveTransactionData(&trans);
	if (error == APPROVED) {
		strcpy(testError, "APPROVED");
	}
	if (error == FRAUD_CARD) {
		strcpy(testError, "FRAUD_CARD");
	}
	if (error == DECLINED_INSUFFECIENT_FUND) {
		strcpy(testError, "DECLINED_INSUFFECIENT_FUND");
	}
	if (error == INTERNAL_SERVER_ERROR) {
		strcpy(testError, "INTERNAL_SERVER_ERROR");
	}
	if (error == DECLINED_STOLEN_CARD) {
		strcpy(testError, "DECLINED_STOLEN_CARD");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 4:blocked*/
	printf("test case 4:blocked\n");
	printf("input data PAN:013245678912345606\n");
	printf("input data trans amount:3000\n");
	printf("input data TransIndex:1\n");
	printf("expected result: DECLINED_STOLEN_CARD\n");
	strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345606");
	trans.terminalData.transAmount = 3000;
	TransIndex = 1;
	recieveTransactionData(&trans);
	if (error == APPROVED) {
		strcpy(testError, "APPROVED");
	}
	if (error == FRAUD_CARD) {
		strcpy(testError, "FRAUD_CARD");
	}
	if (error == DECLINED_INSUFFECIENT_FUND) {
		strcpy(testError, "DECLINED_INSUFFECIENT_FUND");
	}
	if (error == INTERNAL_SERVER_ERROR) {
		strcpy(testError, "INTERNAL_SERVER_ERROR");
	}
	if (error == DECLINED_STOLEN_CARD) {
		strcpy(testError, "DECLINED_STOLEN_CARD");
	}
	printf("Actual result: %s\n\n", testError);



	/*test case 5:server ok*/
	printf("test case 5:server ok\n");
	printf("input data PAN:013245678912345604\n");
	printf("input data trans amount:3000\n");
	printf("input data TransIndex:1\n");
	printf("expected result: APPROVED\n");
	strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345604");
	trans.terminalData.transAmount = 3000;
	TransIndex = 1;
	recieveTransactionData(&trans);
	if (error == APPROVED) {
		strcpy(testError, "APPROVED");
	}
	if (error == FRAUD_CARD) {
		strcpy(testError, "FRAUD_CARD");
	}
	if (error == DECLINED_INSUFFECIENT_FUND) {
		strcpy(testError, "DECLINED_INSUFFECIENT_FUND");
	}
	if (error == INTERNAL_SERVER_ERROR) {
		strcpy(testError, "INTERNAL_SERVER_ERROR");
	}
	if (error == DECLINED_STOLEN_CARD) {
		strcpy(testError, "DECLINED_STOLEN_CARD");
	}
	printf("Actual result: %s", testError);
	printf("\n###########################\n\n");
}
void saveTransactionTest(void) {
	ST_transaction_t trans;
	char testError[15];


	printf("\n###########################\n");
	printf("Tester name: Amr Maged Hanafy \n");
	printf("test Function: saveTransaction\n\n\n");

	/*test case 1:amount available*/
	printf("test case 1:trans index <255\n");
	printf("input data:1\n");
	printf("expected result: SERVER_OK\n");
	//strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345604");
	TransIndex = 1;
	saveTransaction(&trans);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == SAVING_FAILED) {
		strcpy(testError, "SAVING_FAILED");
	}
	printf("Actual result: %s\n\n", testError);


	/*test case 1:amount available*/
	printf("test case 2:trans index >255\n");
	printf("input data:300\n");
	printf("expected result: SAVING_FAILED\n");
	//strcpy(trans.cardHolderData.primaryAccountNumber, "013245678912345604");
	TransIndex = 300;
	saveTransaction(&trans);
	if (error == SERVER_OK) {
		strcpy(testError, "SERVER_OK");
	}
	if (error == SAVING_FAILED) {
		strcpy(testError, "SAVING_FAILED");
	}
	printf("Actual result: %s", testError);
	printf("\n###########################\n\n");
}





















