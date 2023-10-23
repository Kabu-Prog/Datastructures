#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<std::string> ll;

	ll.Add("3");
	ll.Add("A");
	ll.Add("B");
	ll.Add("4");
	ll.Add("5");
	ll.Add("6");

	ll.SwapPosition(1, 0);

	ll.Print();

	ll.invertList();

	ll.Print();

	ll.SwapValue("A", "B");

	ll.Print();

	ll.invertList();

	ll.AddAt("ABC", 5);

	ll.deleteAmount(3, false);

	ll.Print();

	std::cout << ll;


}