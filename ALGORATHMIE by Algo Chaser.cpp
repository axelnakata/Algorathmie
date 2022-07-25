#include <stdio.h>
#include <string.h>


//declaring structure (2 structure)
struct Order{ // struct for order in the first place
		char soup[50];
		int soupprice;
		char noodle[20];
		char topping[8][20];
		int toppingprice[8];
	};

struct Bill{
		double subtotal;
		float totaltax;
		float totalservice;
		float totalgrandtotal;
};

//declaring array of structure (1 array of structure)
struct SoupBase{ // struct for format of soup base
		char soupBaseMenu[120];
		int soupPriceMenu;
	};

int counter=0; // global counter for topping choice
struct Order order;

// binary search function
bool binarySearch(int arr[], int N, int query, int leftIndex, int rightIndex);

//mergesort function
void conquer(int leftmostIndex, int middleIndex, int rightmostIndex);
void divide(int leftmostIndex, int rightmostIndex);


// declaring function (9 functions)
void printOrder( struct Order order); //function to struct order
void printMenu( int a, char b[], char c[] ); //function to print list of topping
void printSoup( struct SoupBase soupbase[]); //function to print list of soupbase
void printNoodle(int b, char arr[]); //function to print list of noodle
void invalid(); // function to print invalid input
float tax(int a, float b); // function to calculate tax
float service(int a, float b); // function to calculate service
float grandtotal(double a, float b, float c, float d); // function to calculate grand total (sub total + tax + service)
float changes(int a, double b, double c); // function to calculate changes


// declaring recursion function (1 function)
void printOrderTopping(int i, struct Order order); // recursion function to print topping into the bill



int main(){
	
	int totalBuy = 0, soupSelection;
	char name[10];
	
	printf("Welcome to Algorathmie!\n\n");
	printf("Please enter your name:\n");
	scanf("%s", &name);
	printf("\n\n");
	

	// Soup base selection
	printf("Today's promo: BUY SMOKE BEEF AS YOUR TOPPING GET FREE NORI!\n\n");
	printf("First of all, choose your soup base (input the number of the list):\n");
	
	struct SoupBase soupbase[3] = {
		{"Original", 20},
		{"Spicy Miso", 25},
		{"Curry", 30}
	};
	
	printSoup(soupbase);
	printf("\n\n");
	
	
	for (int i=0; i < 2; i++){ //loop for soupbase selection input
		scanf("%d", &soupSelection);
		getchar();
		
		switch(soupSelection){
			case 1: {
				totalBuy += 20000;
				strcpy(order.soup, "Original");
				order.soupprice = 20000;
				i++;
				break;
			}
			case 2: {
				totalBuy += 25000;
				strcpy(order.soup, "Spicy Miso");
				order.soupprice = 25000;
				i++;
				break;
			}
			case 3: {
				totalBuy += 30000;
				strcpy(order.soup, "Curry");
				order.soupprice = 30000;
				i++;
				break;
			}
			default: {
				// go back to soupbase scan for a retry due to invalid input
				i = 0;
				invalid();
			}
		}
	}
	
	printf("\n");
	printf("You choose %s soup base, great choice!\n\n", soupbase[soupSelection-1].soupBaseMenu);
	printf("Now, lets select your noodle type!\n");
	
	
	// noodle selection
	char noodleMenu [2][120] = {"Thick", "Thin"}; 

	int j=0;
	while(j<2){
		printNoodle(j+1 , noodleMenu[j]);
		j++;
	}
	printf("\n\n");
	
		
	int noodleSelection;
	for (int i=0; i < 2; i++){ //loop for noodle selection input
		scanf("%d", &noodleSelection);
		getchar();
	
		if (noodleSelection==1){
			strcpy(order.noodle, "Thick");
			break;
		}
		else if (noodleSelection == 2){
			strcpy(order.noodle, "Thin");
			break;
		}
		else {
			// go back to noodle scan for a retry due to invalid input 
			i=0;
			invalid();
		}
	}
	
	printf("\n");
	printf("You choose %s noodles, let's move on!\n", noodleMenu[noodleSelection-1]);
	
	
	// topping selection	
	printf("\nTime to make it delicious, choose a topping!\n");

	int toppingSelection;
	char toppingMenu [7][120] = {"Chicken Charsiu", "Chicken Katsu", "Smoked Beef\t", "Soft-Boiled Egg", "Tempura\t", "Fried Wonton", "Nori\t"};
	char toppingPriceMenu [7][120] = {"15k", "15k", "20k", "5k", "7k", "10k", "3k"};
	
	for(int m=0; m<2; m++){
			int k = 0;
		do{printMenu( k+1, toppingMenu[k],  toppingPriceMenu[k]);
		k++;
		}
		while(k<7);
		printf("\n\n");
		
		for (int i=0; i < 2; i++){ // loop for topping selection input
			scanf("%d", &toppingSelection);
			getchar();
	
			switch(toppingSelection){
				case 1: {
					totalBuy += 15000;
					order.toppingprice[counter] = 15000;
					i++;
					break;
				}
				case 2: {
					totalBuy += 15000;
					order.toppingprice[counter] = 15000;
					i++;
					break;
				}
				case 3: {
					totalBuy += 20000;
					order.toppingprice[counter] = 20000;
					i++;
					break;
				}
				case 4:{
					totalBuy += 5000;
					order.toppingprice[counter] = 5000;
					i++;
					break;
				}
				case 5:{
					totalBuy += 7000;
					order.toppingprice[counter] = 7000;
					i++;
					break;
				}
				case 6:{
					totalBuy += 10000;
					order.toppingprice[counter] = 10000;
					i++;
					break;
				}
				case 7:{
					totalBuy += 3000;
					order.toppingprice[counter] = 3000;
					i++;
					break;
				}
				default: {
					// go back to topping scan for a retry due to invalid input
					i=0;
					invalid();
				}
			}
		}	
	
		printf("\n");
		printf("You choose %s\n", toppingMenu[toppingSelection-1]);
		
		// question: add topping or no
		printf("\nDo you want to add another topping? (Y/N)\n");
		
		char optiontoppingaddition[2], optionanotherorder;
		scanf("%s", &optiontoppingaddition);
		getchar();
	
		strcpy(order.topping[counter], ("%s", toppingMenu[toppingSelection-1]));
	
		if (strcmpi(optiontoppingaddition, "Y") == 0){
			puts("");
			counter++;
			m=0;
			// go back to topping list print and prepare for another input
		}
		else{
			break;
		}
	}
	
	//sort order before print bill
	if (counter>0){
		divide(0, counter);
	}
	
	bool result = binarySearch(order.toppingprice, counter+1, 20000, 0, counter);
	
	printf("\nTime to review your order!\n\n\n");
		
	// Print receipt
	FILE* in = fopen("date.txt", "r");
	char month[15];
	int date, year;
	
	printf("                       ALGORATHMIE\n ");
  	printf("             +============================+ \n\n");
  	while (fscanf(in, "%d %[^ ] %d", &date, month, &year)!= EOF){ //reading txt file to print date
		printf("Date: %d %s %d\n", date, month, year); 
	}
	printf("Invoice To: %s\n", strupr(name));
	printf("-----------------------------------------------------------\n");
	printf("Items\t\t\t\t Qty\t\t Total\n");
	
	printOrder(order);
	(result== true) ? printf("Topping %d : Nori\t\t  1\t\t\n", counter+2) : puts("");
	
	printf("-----------------------------------------------------------\n");
	
	float taxbill;
	float servicebill;
	float grandtotalbill;

struct Bill bill;
	bill.subtotal= totalBuy * 1.00;
	bill.totaltax =tax(totalBuy, taxbill);
	bill.totalservice= service(totalBuy, servicebill);
	bill.totalgrandtotal= grandtotal(bill.subtotal, bill.totaltax, bill.totalservice, grandtotalbill);
	
	printf("Sub Total\t\t\t\t\t %.2lf\n", bill.subtotal); // total order price
	printf("Tax\t\t\t\t\t\t  %.2f\n", bill.totaltax); // total tax (11%)
	printf("Service\t\t\t\t\t\t  %.2f\n", bill.totalservice); // total service (5%)
	printf("Grand Total\t\t\t\t\t %.2f\n", bill.totalgrandtotal); // grand total (order + tax + service)
	
	// Choosing payment
	printf("\n\n");
	printf("How do you prefer to Pay?\n\n");
    printf("We accept CASH or DEBIT CARD.\n");
    printf("1) CASH\n");
    printf("2) CARD\n\n");
    printf("Type 1 for Cash and 2 for Card\n");
    
	int payment;
    scanf ("%d", &payment);
    (payment == 1) ? printf("\nPlease enter the amount of your cash:\n") : printf ("\nPlease wait for your receipt.\n");
    
    unsigned int cash;
    int totalchanges;
    
    if (payment == 1){
		for (int i = 0; i < 2; i++){
		scanf ("%u", &cash);
		if(cash < bill.totalgrandtotal){
			puts("");
			invalid();
			puts("\nPlease enter the amount of your cash:");
		}
		else{
			break;
		}
	}
}
	int changestotal = changes(cash, bill.totalgrandtotal, totalchanges);
	if (payment == 1){
		printf("\nYour change will be Rp%d.00\n", changestotal);
	}
	
	printf("\nHere is your receipt, Thank you for coming to Algorathmie!\n");
		
	//RECEIPT
	
	FILE* out = fopen("receipt.txt", "w"); // output text file for receipt
	fprintf(out, "                       ALGORATHMIE\n ");
  	fprintf(out,"             +============================+ \n\n");
	fprintf(out,"Date: %d %s %d\n", date, month, year);
	fprintf(out,"Invoice To: %s\n", strupr(name));
	fprintf(out,"-----------------------------------------------------------\n");
	fprintf(out,"Items\t\t\t\t Qty\t\t Total\n");
	
	fprintf(out,"Soup\t  : %s\t\t  1\t\t %d\n", order.soup, order.soupprice);
	fprintf(out,"Noodle\t  : %s\t\t  1\t\t \n", order.noodle);
	
	for(int i = 0; i < counter+1; i++){
		fprintf(out, "Topping %d : %s\t  1\t\t %d\n", i+1, order.topping[i], order.toppingprice[i]);
	}
	if (result== true) {
		fprintf(out, "Topping %d : Nori\t\t  1\t\t\n", counter+2);
	}
	
	fprintf(out,"-----------------------------------------------------------\n");
	
	fprintf(out,"Sub Total\t\t\t\t\t %.2lf\n", bill.subtotal); // total order price
	fprintf(out,"Tax\t\t\t\t\t\t  %.2f\n", bill.totaltax); // total tax (11%)
	fprintf(out,"Service\t\t\t\t\t\t  %.2f\n", bill.totalservice); // total service (5%)
	fprintf(out,"Grand Total\t\t\t\t\t %.2f\n", bill.totalgrandtotal); // grand total (order + tax + service)
	if (payment == 1){
		fprintf(out, "\nPaid by: Cash.\n");
		fprintf(out, "Total payment\t\t\t\t\t %u.00\n", cash);
		fprintf(out, "Change\t\t\t\t\t\t %d.00\n", changestotal);
	}
	else{
		fprintf(out, "\nPaid by: Card.\n");
	}
	fprintf(out, "\n\n");
	fprintf(out, "           Thank you For coming to ALGORATHMIE\n ");
  	fprintf(out,"     +============================================+ \n\n");;

	
	fclose(in);
	fclose(out);
	
	return 0;	
}

//mergesort function
void conquer(int leftmostIndex, int middleIndex, int rightmostIndex) {
    // Merge and sort sub-array until we reach the full array
    int temporary[rightmostIndex-leftmostIndex+1];
    char temporary2[rightmostIndex-leftmostIndex+1][20];
    int firstyArrayIndex = leftmostIndex, secondArrayIndex = middleIndex+1;
    int temporaryArrayIndex = 0;


    // while there is still leftover elements
    while(firstyArrayIndex <= middleIndex && secondArrayIndex <= rightmostIndex) {
        if(order.toppingprice[firstyArrayIndex] < order.toppingprice[secondArrayIndex]) {
            temporary[temporaryArrayIndex++] = order.toppingprice[firstyArrayIndex++];
        } else {
            temporary[temporaryArrayIndex++] = order.toppingprice[secondArrayIndex++];
        }
    }

    // In case of uneven array in p1 and p2
    // Note that the leftover elements will always be in first array due to the divide process
    while(firstyArrayIndex <= middleIndex) {
        temporary[temporaryArrayIndex++] = order.toppingprice[firstyArrayIndex++];
    }

    // Copy the temporary array to the new sorted array
    for(int i = 0; i < temporaryArrayIndex; i++) {
        order.toppingprice[i+leftmostIndex] = temporary[i];
    }
}

void divide(int leftmostIndex, int rightmostIndex) {
    // Split array in two until we reach a pair of values
    if(leftmostIndex != rightmostIndex) { // we'll reach pair of values when left == right
        int middleIndex = leftmostIndex + (rightmostIndex-leftmostIndex) / 2; // (left + right) / 2;
        divide(leftmostIndex, middleIndex);
        divide(middleIndex+1, rightmostIndex);
        conquer(leftmostIndex, middleIndex, rightmostIndex);
    }
}

bool binarySearch(int arr[], int N, int query, int leftIndex, int rightIndex) {
    while(leftIndex <= rightIndex) {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if(arr[middleIndex] == query) {
            return true;
        } else if(arr[middleIndex] < query) {
            leftIndex = middleIndex + 1;
        } else {
            rightIndex = middleIndex - 1;
         }
    }

    return false;
}

// Initializing all functions

void printOrder(struct Order order){
	
	printf("Soup\t  : %s\t\t  1\t\t %d\n", order.soup, order.soupprice);
	printf("Noodle\t  : %s\t\t  1\t\t \n", order.noodle);
	printOrderTopping(0, order);
}

void printOrderTopping(int i, struct Order order){
	if(i==counter+1){
		return;
	}
	printf("Topping %d : %s\t  1\t\t %d\n", i+1, order.topping[i], order.toppingprice[i]);
	printOrderTopping(i+1, order);
}

void printMenu( int a, char b[], char c[] ){
	printf("%d) %s @%s\n", a , b, c);
	
}

void printSoup(struct SoupBase soupbase[]){
	for (int i = 0; i < 3; i++){
		printf("%d) %s @%dk\n", i+1 , soupbase[i].soupBaseMenu, soupbase[i].soupPriceMenu);
	}
}

void invalid()
	{printf("Invalid input, please retry.\n");
}

void printNoodle(int b, char arr[]){
	printf("%d) %s\n", b , arr);
}

float tax(int a, float b){
	b = a * 0.11;
	return b;
}

float service(int a, float b){
	b = a * 0.05;
	return b;
}

float grandtotal(double a, float b, float c, float d){
	d = a + b + c;
	return d;
}

float changes(int a, double b, double c){
	c = a - b;
	return c;
}
