#include "MyQueue.h"
#include <iostream>
using namespace std;



int main() {
	MyQueue<int> q;


	q.print();


	q.push(1);
	q.push(2);
	cout << q.front() << endl;
	q.print();

	q.push(3);
	q.push(4);
	q.print();
	q.push(5);
	q.print();

	q.pop();	
	q.pop();
	q.print();
	for(int i=6;i<11;i++) q.push(i);
	q.print();


	for(int i=11;i<20;i++) {
		cout << "Inserindo " << i << endl;
		q.push(i);
		q.print();
	} 
}