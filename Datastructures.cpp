#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> ll;

	ll.Add(0);
	ll.Add(1);
	ll.Add(2);
	ll.Add(3);
	ll.Add(4);
	ll.Add(5);
	ll.Add(6);

	ll.AddAt(7, 4);

	ll.AddAt(8, 0);

	ll.AddAt(9, ll.getLength());

	ll.ReplaceAt(200, 0);
	ll.ReplaceAt(100, ll.getLength());
	ll.ReplaceAt(300, 8);
	ll.ReplaceAt(400, 2);

	ll.Print();

	ll.deleteAt(0);
	ll.Print();

	ll.deleteAt(ll.getLength());


	ll.Print();

	ll.deleteAt(2);
	ll.deleteAt(4);

	ll.Print();

	ll.Add(3);
	ll.Add(3);
	ll.Add(3);
	ll.Add(3);
	ll.Add(3);
	ll.Print();

	ll.deleteValue(3);

	ll.Print();




}