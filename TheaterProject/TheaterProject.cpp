// CSC114-4C2
// Group Project
// Justin Weaver, Erin Duque, Katherine Devanney

#include <iostream>
#include <iomanip>

using namespace std;


/*Theater Example Functions? What we might need to finish?

Theater Seating Project
1. Display Menu
a. displayMenu()
2. Display Seating chart
a. displayChart()
b. display every seat
3. Store row prices in a file
a. storeRowPrices()
4. Get seat info from user, # of seats, row? Starting seat number?
a. Main function
5. Total ticket sale in dollars
a. totalTicketSale()
6. Total num of tickets sold
a. numTicketSold()
7. Seat availability in each row
a. rowAvailability()
8. Seat availability in the auditorium
a. auditoriumAvailability()
*/


//Sets the size of the array used to print out the seating arrangements. 16x31 used to fit the full 15x30 seating arrangement, while later skipping the 0x0 rows and columns.
const int ROWS = 16;
const int COLS = 31;
float RowPrices[ROWS]; //global array to hold prices

void ShowGreeting() {
	cout << "Good evening, Welcome to the Movies!"; //we should make this a better greeting, and add option for user to enter their own prices.
}
void StoreRowPrices() {
	cout << " Our ticket prices are listed below: " << endl; //need to add option for user to input their own prices

	float RowPrice = 100.00; //this is the price for front-row seats.  Every subseqent row behind it will be $5 cheaper than the row in front of it.

	for (int i = 1; i < ROWS; i++) {
		RowPrices[i] = RowPrice;
		RowPrice -= 5.00;
	}
	//Display prices by row
	for (int i = 1; i < ROWS; i++) {
		//cout << "Row #" << i + 1 << ": ";
		cout << "Row #" << i << ": ";
		cout << RowPrices[i] << endl;
	}
}

//Displays both the current purchased and unpurchased seats in the theater when used.
void displaySeating(char seating[ROWS][COLS]) {
	cout << endl;
	cout << "Row|";
	for (int i = 1; i < COLS; i++) {
		cout << right << setw(3) << i;
	}
	cout << '\n';
	for (int i = 1; i < ROWS; i++) { //Loop prints out current contents of seating array.
		cout << right << setw(3) << i << "|";
		for (int j = 1; j < COLS; j++) {
			cout << right << setw(3) << seating[i][j];
		}
		cout << '\n';
	}
}
//displays the row availability
void rowAvailability(char seating[ROWS][COLS]) {//using only rows in this array function
	int row = 1;
	int NumSeatsAvailable = COLS-1;

	do
	{
		if (row > 15 || row <= 0)
			cout << "That row is invalid. ";
		cout << "Enter the Row you would like to view (1-15): \n";
		cin >> row;           //new variable for row in this function only

	} while (row > 15 || row <= 0);

	cout << "Row Availability\n\n";//shows the row the user selected
	for (int i = 1; i < COLS; i++) 
		cout << seating[row][i];       //cout array of selected row

	for (int j = 1; j < COLS; j++) {     //determines the number of seats available by counting the *
		if (seating[row][j] == '*') {
			NumSeatsAvailable -= 1;
		}
	}
	
   cout << "\nThere are " << NumSeatsAvailable << " number of seats in this row.\n";//displays the number of seats available
}

//Asks the user for a seat row and column, will 'purchase' the seat and change the character in the array to symbol for purchased seats.
void purchaseTickets(char seating[ROWS][COLS]) {
	//Will need to add a prices array, total sales, and total tickets variable to parameters possibly to track everything later if needed.
	int people;
	double ticketcost = 0.0;
	int seatrow;
	int seatcolumn;
	bool emptyseat = true; //Used in loop to check if selected seat is empty or not.

	cout << "\nHow many people will be purchasing tickets? "; //This will ask how many people will be purchasing a ticket.
	cin >> people;
	while (people < 1) {
		cout << "Cannot order for less than one person. How many people will be purchasing tickets? ";
		cin >> people;
	}
	for (int index = 1; index <= people; index++) { //Loops through for the number of people chosen to be purchasing a seat.

		do { //Do-While loop that asks the user for a seat row and column to purchase. Will check and repeat if selected seat is already occupied.
			cout << "\nEnter desired seat row for ticket #" << index << ". (Pick 1-15): ";
			cin >> seatrow;
			while (seatrow > 15 || seatrow <= 0) { //Loop checks and repeats if selected seat row is 0 or negative, and larger than 15.
				cout << "This seat row is invalid. Enter desired seat row for ticket #" << index << ". (Pick 1-15): ";
				cin >> seatrow;
			}
			cout << "Enter the desired seat in chosen row " << seatrow << " for ticket #" << index << ". (Pick 1-30): ";
			cin >> seatcolumn;
			while (seatcolumn > 30 || seatcolumn <= 0) { //Loop checks and repeats if selected seat column is 0 or negative, and larger than 30.
				cout << "This seat is invalid. Enter the desired seat in chosen row " << seatrow << " for ticket #" << index << ". (Pick 1-30): ";
				cin >> seatcolumn;
			}
			cout << endl;

			for (int i = 1; i < ROWS; i++) { //Loop that checks if selected seat is purchased already. If it is not, it will change the seat values in array to the purchased character.
				for (int j = 1; j < COLS; j++) {
					if (i == seatrow && j == seatcolumn) { //The array will iterate through until the 'i' and 'j' matches both the selected row and col values for the seat.
						if (seating[i][j] == '*') { //Here it checks current array value if it matches the '*' symbol. If it matches, the user will be prompted to enter a new seat.
							cout << "This seat has been purchased already. Please choose a different seat selection.\n";
							emptyseat = false;
						}
						else {
							seating[i][j] = 'O'; //If not purchased, the seat character changes to the 'O' symbol for current orders.
							displaySeating(seating);
							cout << "\nPrice to purchase this seat is: $" << RowPrices[i] << endl << endl;
							ticketcost += RowPrices[i];
							emptyseat = true;
						}
					}
				}
			}
		} while (emptyseat == false);

	}
	//Replaces all of the purchase 'O' with '*' in the array after order is done.
	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {
			if (seating[i][j] == 'O') {
				seating[i][j] = '*';
			}
		}
	}
	//Displays total cost of the current ticket order.
	cout << "Total ticket cost of this order is: $" << ticketcost << " for " << people << " seats purchased.\n";
}

int TotalTicketsSold(char seating[][COLS]) {
	int TicketsSold=0;

	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {
			if (seating[i][j] == '*') {
				TicketsSold += 1;
			}
		}
	}
	return TicketsSold;
}
float TotalTicketSales(char seating[][COLS]) {
	float TotalSales = 0.00;

	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {
			if (seating[i][j] == '*')
				TotalSales += RowPrices[i-1];
		}
	}

	return TotalSales;
}

//Displays a menu of multiple options to the user to select. Calls multiple other functions as needed from within.
void displayMenu(char seating[ROWS][COLS]) {
	char choice;

	displaySeating(seating);
	
	while (true) { //While loop keeps the program running until the user decides to stop.
		cout << "\nMain Menu\n";
		cout << "1. Purchase Tickets\n";
		cout << "2. Total Ticket Sales in Dollars\n";
		cout << "3. Total Num of Tickets Sold\n";
		cout << "4. Seat Availability in Each Row\n";
		cout << "5. Seat Availability in Auditorium\n";
		cout << "6. Exit Menu\n";
		cout << "Please enter your choice: ";

		cin >> choice;
		switch (choice) { //Switch cases that display the main menu options to the user.
		case '1': //Purchase Tickets
			purchaseTickets(seating); //Will select seats and purchase tickets.
			break;
		case '2': cout << "$" << TotalTicketSales(seating) << " of tickets have been sold.\n";
			break;
		case '3': cout << TotalTicketsSold(seating) << " ticket(s) have been sold.\n";
			break;
		case '4': //Seat availability in each row menu option.
			rowAvailability(seating);
			break;
		case '5': //Seat availability in the auditorium menu option.
			displaySeating(seating); //This function displays the current theater setup with each use.
			break;
		case '6': //Choosing this option ends the program.
			cout << "\nThank you for visiting the Movies today!\n\n";
			system("pause");
			exit(0);
		default:
			cout << "\nInvalid Menu option. Please try again.\n";
			continue;
		}
		
	}
}

//Main function that initializes the seating array and begins the main menu.
int main() {
	ShowGreeting();
	StoreRowPrices();
	char seating[ROWS][COLS]; //Stores seats rows and columns

	for (int i = 1; i < ROWS; i++) { //Loop that creates the seating array, and fills it with a symbol to denote unpurchased seats that will display to the user.
		for (int j = 1; j < COLS; j++) {
			seating[i][j] = '#';
		}
	}

	displayMenu(seating);

	system("pause");
	return 0;
}