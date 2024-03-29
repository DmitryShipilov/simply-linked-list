#include "stdafx.h"
#include <conio.h>
#include <math.h>
#include <iostream>
using namespace std;

class Point1 {
public:
	Point1() {};
	Point1(double tx1) : x1(tx1) {};
	virtual double GetLength() {
		if (x1 < 0)
			return ((-1) * x1);
		else
			return x1;
	}
	virtual ~Point1() {


	}
protected:
	double x1; // координата

};


class Point2 final : public Point1 {
private:
	//double x1;
	double x2;
public:
	Point2(double tx1, double tx2)
	{
		x1 = tx1;
		x2 = tx2;
	}
	double GetLength() override {
		return sqrt(x1 * x1 + x2 * x2);
	}

	~Point2() {

	}
};

class PointList {
private:

	struct Node {
		Point1* copyVectorTemplate;
		Node* next;

		Node() {};
		Node(Point1* copyVectorTemplateInput) {
			copyVectorTemplate = copyVectorTemplateInput;
			next = nullptr;
		}
	};

	size_t cnt;
	Node* head;
	Node* tail;
public:
	PointList() : head(nullptr),/* tail(nullptr),*/ cnt(0) {};

	void Add(Point1* cv1) {
		Node* p = new (std::nothrow) Node();
		if (p != nullptr) {
			p->copyVectorTemplate = cv1;
			p->next = nullptr;

			if (head == nullptr)
				head = tail = p;
			else
				tail = tail->next = p;
			++cnt;
		}
	}


	void DeleteElement(Point1* cv1)
	{
		if (head != nullptr)
		{
			Node* headPtr = head;
			bool tailNode = false;

			while (head != nullptr)
			{
				if (tail->copyVectorTemplate != cv1)
				{
					if (head->copyVectorTemplate == cv1)
					{
						if (head != tail)
						{
							Node* nextNode = head->next;

							head->copyVectorTemplate = nextNode->copyVectorTemplate;
							head->next = nextNode->next;
							head = headPtr;
							delete nextNode;
							break;
						}
					}
				}
				else
				{
					tailNode = true;
					break;
				}
				head = head->next;
			}
			if (tailNode)
			{
				while (head->next != tail)
				{
					head = head->next;
				}
				tail = head;
				delete tail->next;
				tail->next = nullptr;
				head = headPtr;
			}
		}
	}
	~PointList() {
		while (head != nullptr) {
			Node* curPtr = head;
			head = head->next;
			cout << curPtr->copyVectorTemplate->GetLength() << " is deleted" << endl;
			delete curPtr;

		}
		//cout << "Destructor has been ended" << endl;
	}
	void PrintLengths() {
		for (const Node* p = head; p != nullptr; p = p->next)
			cout << p->copyVectorTemplate->GetLength() << endl;
	}

};

int main(void)
{
	Point1 a1(3.0);
	Point2 a2(3.0, 4.0);
	Point2 a3(-5.0, -12.0);
	Point1 a4(-15.0);
	Point2 a5(80.0, -60.0);
	Point2 a6(100, 100);

	PointList list;
	list.Add(&a1);
	list.Add(&a2);
	list.Add(&a3);
	list.Add(&a4);
	list.Add(&a5);
	list.Add(&a6);


	list.PrintLengths();
	cout << "After deleting" << endl;
	list.DeleteElement(&a4);
	list.PrintLengths();
	_getch();

	return 0;
}
