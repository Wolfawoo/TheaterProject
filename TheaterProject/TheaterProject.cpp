// CSC114-4C2
// Group Project
// Justin Weaver, Erin Duque, Katherine Devanney

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//Sets the size of the array used to print out the seating arrangements. 16x31 used to fit the full 15x30 seating arrangement, while later skipping the 0x0 rows and columns.
const int ROWS = 16;
const int COLS = 31;
char seating[ROWS][COLS]; //Stores seats rows and columns
float RowPrices[ROWS]; //global array to hold prices

//Prototypes
void ShowGreeting();
void displayMenu(char[][COLS]);
void displaySeating(char[][COLS]);
void StoreRowPrices();
void rowAvailability(char[][COLS]);
void auditoriumAvailability(char[][COLS]);
void purchaseTickets(char[][COLS]);
int TotalTicketsSold(char[][COLS]);
void displayPrices(float[]);




//Main function that initializes the seating array and begins the main menu.
int main() {

	for (int i = 1; i < ROWS; i++) { //Loop that creates the seating array, and fills it with a symbol to denote unpurchased seats that will display to the user.
		for (int j = 1; j < COLS; j++) {
			seating[i][j] = '#';
		}
	}
	ShowGreeting();
	StoreRowPrices();
	displayMenu(seating);

	system("pause");
	return 0;
}

void ShowGreeting() {
	cout << "Good evening, Welcome to the Movies!\n";
	cout << "This program allows you to select your seat, purchase tickets, view theater availability, and more!\n";
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
	int NumSeatsAvailable = COLS - 1;

	do
	{
		if (row > 15 || row <= 0)
			cout << "That row is invalid. ";
		cout << "\nEnter the Row you would like to view (1-15): ";
		cin >> row;           //new variable for row in this function only

	} while (row > 15 || row <= 0);

	cout << "\nRow Availability for Row " << row << ":\n";//shows the auditorium availability
	cout << "'#' = Available Seat for Purchase;\t'*' = Unavailable Seat for Purchase;\n\n";
	for (int i = 1; i < COLS; i++) {
		cout << left << setw(3) << i;
	}
	cout << "\n";
	for (int i = 1; i < COLS; i++)
		cout << left << setw(3) << seating[row][i];      //cout array of selected row

	for (int j = 1; j < COLS; j++) {     //determines the number of seats available by counting the *
		if (seating[row][j] == '*') {
			NumSeatsAvailable -= 1;
		}
	}

	cout << "\n\nThere are " << NumSeatsAvailable << " seats available in this row.\n";//displays the number of seats available
}

//displays auditorium availability
void auditoriumAvailability(char seating[ROWS][COLS]) //includes array of all rows, columns
{
	int RowSeatsAvailable = ROWS - 1;
	int ColSeatsAvailable = COLS - 1;
	int row = 1;

	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {     //determines the number of seats available by counting the *
			if (seating[row][j] == '*') {
				RowSeatsAvailable -= 1;
				ColSeatsAvailable -= 1;
			}
		}
	}
	cout << "\nAuditorium Availability:\n";//shows the auditorium availability
	cout << "'#' = Available Seat for Purchase;\t'*' = Unavailable Seat for Purchase;\n";
	displaySeating(seating); //This function displays the current theater setup with each use.

	cout << "\nThere are " << RowSeatsAvailable * ColSeatsAvailable - TotalTicketsSold(seating) << " seats available in the auditorium.\n";//displays total availablility
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
							cout << "'O' = Seat Purchased for this Order;\t'#' = Available Seat for Purchase;\t'*' = Unavailable Seat for Purchase;\n";
							displaySeating(seating);
							cout << "\nPrice to purchase this seat is: $" << RowPrices[i] << endl << endl;
							ticketcost += RowPrices[i];
							emptyseat = true;
						}
					}
				}
			}
		} while (emptyseat == false);
		system("pause");

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
	cout << "\nTotal ticket cost of this order is: $" << ticketcost << " for " << people << " seats purchased.\n";
}

int TotalTicketsSold(char seating[ROWS][COLS]) {
	int TicketsSold = 0;

	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {
			if (seating[i][j] == '*') {
				TicketsSold += 1;
			}
		}
	}
	return TicketsSold;
}
float TotalTicketSales(char seating[ROWS][COLS]) {
	float TotalSales = 0.00;

	for (int i = 1; i < ROWS; i++) {
		for (int j = 1; j < COLS; j++) {
			if (seating[i][j] == '*')
				TotalSales += RowPrices[i - 1];
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
		cout << "6. Display Ticket Prices\n";
		cout << "7. Exit Menu\n";
		cout << "Please enter your choice: ";

		cin >> choice;
		switch (choice) { //Switch cases that display the main menu options to the user.
		case '1': //Purchase Tickets
			purchaseTickets(seating); //Will select seats and purchase tickets.
			system("pause");
			break;
		case '2': cout << "\n$" << TotalTicketSales(seating) << " of tickets have been sold.\n";
			system("pause");
			break;
		case '3': cout << endl << TotalTicketsSold(seating) << " ticket(s) have been sold.\n";
			system("pause");
			break;
		case '4': //Seat availability in each row menu option.
			rowAvailability(seating);
			system("pause");
			break;
		case '5': //Seat availability in the auditorium menu option.
			auditoriumAvailability(seating);
			system("pause");
			break;
		case '6': //Display ticket prices at user
			displayPrices(RowPrices);
			break;
		case '7': //Choosing this option ends the program.
			cout << "\nThank you for visiting the Movies today!\n\n";
			system("pause");
			exit(0);
		default:
			cout << "\nInvalid Menu option. Please try again.\n";
			continue;
		}

	}
}

void StoreRowPrices() {
	int choice = 1; //initialize choice to use default prices
	float input; //holds user input for each row
	float price; //holds prices read from file until they are read to array
	ifstream inputfile;
	cout << "The current theater prices are listed below: " << endl; //need to add option for user to input their own prices

	float RowPrice = 100.00; //this is the price for front-row seats.  Every subseqent row behind it will be $5 cheaper than the row in front of it.

	for (int i = 1; i < ROWS; i++) {
		RowPrices[i] = RowPrice;
		RowPrice -= 5.00;
	}
	displayPrices(RowPrices);

	cout << "\nWould you like to use these prices, read prices in from a file, or enter your own?\n";
	do {
		if (choice != 1 && choice != 2 && choice != 3)
			cout << "\nInvalid choice.\n";
		cout << "Press '1' to use default prices.\nPress '2' to read prices in from a file.\nPress '3' to enter your own prices.\nPlease enter choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3);

	switch (choice) {
	case 1: cout << "You have chosen to use default ticket prices.  Here is the menu of other options: \n";
		break;
	case 2:
		inputfile.open("TicketPrices.txt");
		cout << "\nTicket Prices from File:\n";
		/*while (inputfile >> price)
			for (int i = 1; i < ROWS; i++)
				RowPrices[i] = price;*/
		for (int i = 1; i < ROWS; i++) {
			inputfile >> RowPrices[i];
		}
		inputfile.close();
		displayPrices(RowPrices);
		break;
	case 3:
		for (int i = 1; i < ROWS; i++) {
			cout << "Enter the price for row #" << i << ": $";
			cin >> input;
			RowPrices[i] = input;
		}
		cout << "You have entered prices for all rows." << endl << endl;
		system("pause");
		break;
	}
}
void displayPrices(float prices[]) { //Display prices by row
	cout << setprecision(2) << fixed << endl;
	cout << "Current Ticket Prices for each Row:\n";
	for (int i = 1; i < ROWS; i++) {
		cout << "Row #" << i << ": $";
		cout << prices[i] << endl;
	}
	system("pause");
}