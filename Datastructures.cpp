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

	std::cout << ll;

	ll.PrintWithIndex();
	ll.PrintReverseWithIndex();



}