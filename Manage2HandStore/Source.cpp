#include "MainMenu.h"

int main() {
	ProductList l, cart;
	InvoiceList il;
	ifstream filein;
	ofstream fileout;
	MainMenu(l, cart, il, filein, fileout);
	return 0;
}

