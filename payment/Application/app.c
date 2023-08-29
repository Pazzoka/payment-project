
#include "..\Application\app.h"
void appstart(void)
{
	ST_transaction_t trans;
	EN_terminalError_t Terminal_Error;
	EN_cardError_t Card_Error;
	int MA=0;
	int option=0;
	printf("Hi there\n");
	while (1) {
		do {
			printf("1-Enter new transaction\n");
			printf("2-list all transactions\n");
			gets(&option);
			
		} while (option != '1' && option != '2');
		if (option == '1') {
			printf("\nPlease Enter Card Name : ");
			gets(trans.cardHolderData.cardHolderName);
			Card_Error = getCardHolderName(&trans.cardHolderData);
			if (Card_Error == CARD_OK) {
				printf("Please enter the Primary Account Number : ");
				gets(trans.cardHolderData.primaryAccountNumber);
				Card_Error = getCardPAN(&trans.cardHolderData);
				if (Card_Error == CARD_OK) {
					printf("please enter the the expiry date in the form MM/YY: ");
					gets(trans.cardHolderData.cardExpirationDate);
					Card_Error = getCardExpiryDate(&trans.cardHolderData);
					if (Card_Error == CARD_OK) {
						time_t tt = time(0);
						struct tm* dt = localtime(&tt);
						char mon[3];
						char day[3];
						char year[5];
						_itoa(dt->tm_mday, day, 10);
						_itoa(dt->tm_mon + 1, mon, 10);
						_itoa(dt->tm_year + 1900, year, 10);

						if (dt->tm_mday < 10) {
							strcpy(trans.terminalData.transactionDate, "0");
							strcat(trans.terminalData.transactionDate, day);
						}
						else {
							strcpy(trans.terminalData.transactionDate, day);
						}
						strcat(trans.terminalData.transactionDate, "/");
						if (dt->tm_mon + 1 < 10) {
							strcat(trans.terminalData.transactionDate, "0");
							strcat(trans.terminalData.transactionDate, mon);
						}
						else {
							strcat(trans.terminalData.transactionDate, mon);
						}
						strcat(trans.terminalData.transactionDate, "/");
						strcat(trans.terminalData.transactionDate, year);
						Terminal_Error = getTransactionDate(&trans.terminalData);
						if (Terminal_Error == TERMINAL_OK) {
							Terminal_Error = isCardExpired(&trans.cardHolderData, &trans.terminalData);
							if (Terminal_Error == TERMINAL_OK) {
								printf("please enter the transaction amount:  ");
								scanf("%f",&trans.terminalData.transAmount);
								Terminal_Error = getTransactionAmount(&trans.terminalData);
								if (Terminal_Error == TERMINAL_OK) {
									printf("please enter the max. amount:");
									scanf("%f", &trans.terminalData.maxTransAmount);
									Terminal_Error = setMaxAmount(&trans.terminalData, MA);
									if (Terminal_Error == TERMINAL_OK) {
										Terminal_Error = isBelowMaxAmount(&trans.terminalData);
										if (Terminal_Error == TERMINAL_OK) {
											trans.transState = recieveTransactionData(&trans);
										}
										else {
											printf("EXCEED_MAX_AMOUNT\n");
										}
									}
									else {
										printf("INVALID_MAX_AMOUNT\n");
									}
								}
								else {
									printf("INVALID_AMOUNT\n");
								}
							}
							else {
								printf("EXPIRED_CARD \n");
							}
						}
						else {
							printf("Wrong Date \n");
						}
					}
					else {
						printf("Wrong Exp Date\n");
					}
				}
				else {
					printf("Wrong PAN\n");
				}
			}
			else {
				printf("Wrong Name\n");
			}
		}

		
		if (option == '2') {
			listSavedTransactions();
		}
	}
}

int main() {
	
	
		
		printf("\n\n\n\n");
		printf("                                   welcome to pazzoka's payment project                                                  \n\n\n");

	
			time_t tt = time(0);
			struct tm* dt = localtime(&tt);
			printf("                           time:  %.2d:%.2d:%.2d                date: %.2d/%.2d/%.4d\n", dt->tm_hour, dt->tm_min, dt->tm_sec, dt->tm_mday, dt->tm_mon + 1, dt->tm_year + 1900);
			

	
		printf("\n\n\n\n\n");
		
	     appstart();
	// getCardHolderNametest();
	// getCardExpiryDatetest();
	// getCardPANtest();
	// getTransactionDateTest();
	// isCardExpriedTest();
	// getTransactionAmountTest();
	// setMaxAmountTest();
	// isBelowMaxAmountTest();
	// isValidAccountTest();
	// isBlockedAccountTest();
	// isAmountAvailableTest();
	// saveTransactionTest();
	// recieveTransactionDataTest();*/
		
}


/*
right name:        amr maged hanafy moha            
running pan:    013245678912345604         5000
running pan:    013245678912345603         4000
running pan:    013245678912345602         3000

blocked pan:        013245678912345605
 












*/
 




