#pragma once
#include "Product2HList.h"

struct NodeInvoice {
	string id;
	string description;
	int count;
	ProductList data;
	NodeInvoice* next;
};
NodeInvoice* CreateNodeInvoice(string id, string description, int count, ProductList l) {
	NodeInvoice* p = new NodeInvoice;
	if (!p) {
		cout << "\nNot enough memory.";
		return NULL;
	}
	p->id = id;
	p->description = description;
	p->count = count;
	CreateList(p->data);
	for (NodeProduct *k = l.head; k != NULL; k = k->next) {
		AddTail(p->data, CreateNode(k->data));
	}
	p->next = NULL;
	return p;
}

struct InvoiceList {
	NodeInvoice* head;
	NodeInvoice* tail;
};
void CreateListInvoice(InvoiceList& l) {
	l.head = NULL;
	l.tail = NULL;
}

bool AddTailInvoiceList(InvoiceList& l, NodeInvoice* p) {
	if (l.head == NULL) {
		l.head = l.tail = p;
	}
	else {
		l.tail->next = p;
		l.tail = p;
	}
	return true;
}

void FreeData(InvoiceList& l) {
	NodeInvoice* p = NULL;
	while (l.head != NULL) {
		p = l.head;
		l.head = l.head->next;
		delete p;
	}
}

