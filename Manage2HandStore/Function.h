#pragma once
#include "Product2HList.h" 

// ham chuyen string thanh chu thuong
string ToLower(string str) {
	for (auto& c : str) {
		c = tolower(c);
	}
	return str;
}

//ham thoa tim kiem tu khoa
bool MatchSearchKeyWord(NodeProduct* p, string findString) {
	findString = ToLower(findString);
	size_t result = ToLower(p->data.getId()).find(findString);
	size_t ndresult = ToLower(p->data.getName()).find(findString);
	size_t rdresult = ToLower(p->data.getBrand()).find(findString);
	if (result != string::npos || ndresult != string::npos || rdresult != string::npos) {
		return true;
	}
	else {
		return false;
	}
}

//ham thoa tim kiem theo khoang gia
bool MatchSearchPrice(NodeProduct* p, int from, int to) {
	if (p->data.getPrice() >= from && p->data.getPrice() <= to) {
		return true;
	}
	else {
		return false;
	}
}

//ham tach so luong san pham
NodeProduct* TranferQuantity(ProductList& l, NodeProduct*& from, int quantity) {
	NodeProduct* to = CreateNode(from->data); to->data.setQuantity(0);
	if (from->data.IsEnoughQuantity(quantity)) {
		to->data.setQuantity(quantity);
		from->data.setQuantity(from->data.getQuantity() - quantity);
	}
	else {
		return NULL;
	}
	if (from->data.getQuantity() <= 0) {
		DeleteById(l, from->data.getId());
	}
	return to;
}

//ham in menu tra ve lua chon
int PrintMenu(string attr[], int nAttr, int lenghtMenu, int printFrom = 0) {
	//in header
	int titleLen = (int)((lenghtMenu - attr[0].length()) / 2);
	if ((lenghtMenu - attr[0].length()) % 2 != 0) {
		lenghtMenu++;
		titleLen++;
	}
	cout << "\n\t\t";
	for (int i = 0; i < titleLen; i++) {
		if (i == 0 || i == titleLen - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << attr[0];
	for (int i = 0; i < titleLen; i++) {
		if (i == 0 || i == titleLen - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}

	// in body
	if (printFrom == 0) {
		for (int i = 1; i < nAttr; i++) {
			if (i - 1 < 10) {
				cout << "\n\t\t| " << i - 1 << ". " << left << setw(lenghtMenu - 6) << attr[i].append(".") << "|";
			}
			else {
				cout << "\n\t\t| " << i - 1 << ". " << left << setw(lenghtMenu - 7) << attr[i].append(".") << "|";
			}
			attr[i] = attr[i].substr(0, attr[i].length() - 1);
		}
	}
	else {
		for (int i = 1; i < nAttr; i++) {
			if (i < 10) {
				cout << "\n\t\t| " << i << ". " << left << setw(lenghtMenu - 6) << attr[i].append(".") << "|";
			}
			else {
				cout << "\n\t\t| " << i << ". " << left << setw(lenghtMenu - 7) << attr[i].append(".") << "|";
			}
			attr[i] = attr[i].substr(0, attr[i].length() - 1);
		}
	}

	// in footer
	cout << "\n\t\t";
	for (int i = 0; i < lenghtMenu; i++) {
		if (i == 0 || i == lenghtMenu - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	string sawn;
	cout << "\nEnter your selection: "; getline(cin, sawn);
	int awn = (printFrom == 0) ? CheckSelection(sawn, 0, nAttr - 2) : CheckSelection(sawn, 1, nAttr - 1);
	return (printFrom == 0) ? awn : (awn - 1);
}

//ham in danh sach
void OutputFormedList(ProductList l, bool allInfor = false, string title = "PRODUCT") {
	string attr[6] = { "ID", "NAME", "BRAND", "IMPORT PRICE", "REMAINING", "PRICE" };
	if (title == "CART") attr[4] = "QUANTITY";
	if (l.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t+-------------------------+" << endl;
		if (title == "CART") {
			cout << "\t\t\t|   " << title << " HAS NO PRODUCT   |" << endl;
		}
		else {
			cout << "\t\t\t|   LIST HAS NO PRODUCT   |" << endl;
		}
		cout << "\t\t\t+-------------------------+\n\n\n\n\n\n" << endl;
	}
	else if (!allInfor) {
		cout << "\n\n\t\t\t\t\t" << title << " LIST\n";
		cout << "\t+---------------------------------------------------------------------------------+" << endl;
		cout << "\t|" << left << setw(12) << attr[0]
			<< "|  " << left << setw(20) << attr[1]
			<< "|  " << left << setw(15) << attr[2]
			<< "| " << left << setw(10) << attr[4]
			<< "|  " << left << setw(13) << attr[5] << "|" << endl;
		cout << "\t+---------------------------------------------------------------------------------+" << endl;
		for (NodeProduct* p = l.head; p != NULL; p = p->next) {
			cout << p->data;
		}
		cout << "\t+---------------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "\n\n\t\t\t\t\t" << title << " LIST\n";
		cout << "\t+-----------------------------------------------------------------------------------------------+" << endl;
		cout << "\t|" << left << setw(12) << attr[0]
			<< "|  " << left << setw(20) << attr[1]
			<< "|  " << left << setw(15) << attr[2]
			<< "| " << left << setw(13) << attr[3]
			<< "| " << left << setw(10) << attr[4]
			<< "|  " << left << setw(12) << attr[5] << "|" << endl;
		cout << "\t+-----------------------------------------------------------------------------------------------+" << endl;
		for (NodeProduct* p = l.head; p != NULL; p = p->next) {
			cout << "\t|" << left << setw(12) << p->data.getId()
				<< "|  " << left << setw(20) << p->data.getName()
				<< "|  " << left << setw(15) << p->data.getBrand()
				<< "|" << right << setw(12) << p->data.getImportPrice()
				<< "  |" << right << setw(9) << p->data.getQuantity()
				<< "  |" << right << setw(12) << p->data.getPrice() << "  |" << endl;
		}
		cout << "\t+-----------------------------------------------------------------------------------------------+" << endl;
	}
}

//ham kiem tra ton tai trong list
bool ExistInList(ProductList l, string id, NodeProduct*& k) {
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->data.getId() == id) {
			k = p;
			return true;
		}
	}
	k = NULL;
	return false;
}

//ham kiem tra khach hang co muon tiep tuc hay khong
bool Continue(string log) {
	string awn;
	cout << "\n" << log << "(yes or no)? ";
	getline(cin, awn);
	if (ToLower(awn).substr(0,1) == "y" || ToLower(awn) == "yes") {
		return true;
	}
	else {
		return false;
	}
}

//ham in hang thong tin hoa don
void PrintLineInvoice(int size, string s = "", string s2 = "", string type = "left") {
	int spaceLen = (int)floor(((size - s.length())) - 4);
	if (s2 != "") {
		spaceLen = (int)floor(((size - s.length() - s2.length())) - 4);
		cout << "\t\t| ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s2;
		cout << " |\n";
		return;
	}
	if (spaceLen + s.length() + 4 != size) s.append(" ");
	if (type == "center") {
		spaceLen = (int)floor(((size - s.length()) / 2) - 1);
		if (spaceLen * 2 + s.length() + 2 != size) {
			s.append(" ");
		};
		cout << "\t\t|";
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << "|\n";
	}
	else if (type == "right") {
		cout << "\t\t| ";
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s;
		cout << " |\n";
	}
	else {
		cout << "\t\t| ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << " |\n";
	}

}

//ham in hang san pham
void PrintLineProduct(int size, NodeProduct* p, int& total) {
	PrintLineInvoice(size, p->data.getName().append("(").append(p->data.getId()).append(")"), "", "left");
	cout << "\t\t|     " << left << setw(15) << p->data.getQuantity() << right << setw(15) << p->data.getPrice() << right << setw(size- 15 - 15 - 8) << p->data.getTotal();
	cout << " |\n\t\t|";
	for (int i = 0; i < (size - 2) / 2; i++) {
		cout << "- ";
	}
	cout << "|\n";
	total += p->data.getTotal();
}

// sap xep 
// file nhung product da ban
// tinh doanh thu 


