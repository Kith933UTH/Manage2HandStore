#pragma once
#include "Product2H.h"

struct NodeProduct {
	Product2H data;
	NodeProduct* next;
};
NodeProduct* CreateNode(Product2H pro) {
	NodeProduct* p = new NodeProduct;
	if (!p) {
		cout << "\nNot enough memory.";
		return NULL;
	}
	p->data = pro;
	p->next = NULL;
	return p;
}

struct ProductList {
	NodeProduct* head;
	NodeProduct* tail;
};
void CreateList(ProductList& l) {
	l.head = NULL;
	l.tail = NULL;
}

bool AddHead(ProductList& l, NodeProduct* p) {
	if (l.head == NULL) {
		l.head = l.tail = p;
	}
	else {
		p->next = l.head;
		l.head = p;
	}
	return true;
}
bool AddTail(ProductList& l, NodeProduct* p) {
	if (l.head == NULL) {
		l.head = l.tail = p;
	}
	else {
		l.tail->next = p;
		l.tail = p;
	}
	return true;
}
bool AddToList(ProductList& l, NodeProduct*& k) {
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->data.getId() == k->data.getId()) {
			p->data.setQuantity(p->data.getQuantity() + k->data.getQuantity());
			delete k;
			return true;
		}
	}
	AddTail(l, k);
	return true;
}

bool DeleteHead(ProductList& l) {
	if (l.head == NULL) return false;
	NodeProduct* temp = l.head;
	l.head = temp->next;
	delete temp;
	return true;
}
bool DeleteTail(ProductList& l) {
	if (l.head == NULL) return false;
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->next == l.tail) {
			delete l.tail;
			p->next = NULL;
			l.tail = p;
			return true;
		}
	}
	return false;
}
bool DeleteById(ProductList& l, string id) {
	//xoa neu la node dau
	if (l.head->data.getId() == id) {
		if(DeleteHead(l)) return true;
		return false;
	}
	//xoa neu la node cuoi
	if (l.tail->data.getId() == id) {
		if (DeleteTail(l)) return true;
		return false;
	}
	//xoa neu la node giua
	NodeProduct* k = new NodeProduct;
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->data.getId() == id) {
			k->next = p->next;
			delete p;
			return true;
		}
		k = p;
	}
	return false;
}

void FreeData(ProductList& l) {
	NodeProduct* p = NULL;
	while (l.head != NULL) {
		p = l.head;
		l.head = l.head->next;
		delete p;
	}
}
void SwapData(NodeProduct *&p1, NodeProduct *&p2) {
	Product2H ptemp = p1->data;
	p1->data = p2->data;
	p2->data = ptemp;
}
