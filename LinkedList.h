#ifndef LINKEDLIST_H
#define LINKEDLIST_H



//ToDO: Andere Struktur. Statt 15 x delete, etc. zu haben w‰re es besser so etwas wie "search by value" oder "search by position" und anschlieﬂend die T‰tigkeit "delete", "swap", "replace", "edit", ...

template <typename T>
class LinkedList
{
private:
	template <typename T>
	class Node
	{
	private:
		T mValue;
		Node* mNext;
		Node* mPrev;

		// das sollten genug eintr‰ge sein

	public:
		T getValue()
		{
			return mValue;
		}
		Node* getNext()
		{
			return mNext;
		}
		Node* getPrev()
		{
			return mPrev;

		}

		void setValue(T value)
		{
			mValue = value;;
		}
		void setNext(Node* next)
		{
			mNext = next;;
		}
		void setPrev(Node* prev)
		{
			mPrev = prev;;
		}

		Node()
			: mValue(T()), mNext(nullptr), mPrev(nullptr)
		{
		}

		Node(T value, Node* next, Node* prev)
			: mValue(value), mNext(next), mPrev(prev)
		{
		}
	};

	
	Node<T>* mFirstNode = nullptr;
	Node<T>* mLastNode = nullptr;
	uint32_t mIndex = 0;

	Node<T>* getFirstNode()
	{
		return mFirstNode;
	}
	Node<T>* getLastNode()
	{
		return mLastNode;
	}
	uint32_t getIndex()
	{
		return mIndex;
	}
	void setIndex(int index)
	{
		mIndex = index;
	}
	void setFirstNode(Node<T>* firstNode)
	{
		mFirstNode = firstNode;
	}
	void setLastNode(Node<T>* lastNode)
	{
		mLastNode = lastNode;
	}


	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll)
	{
		uint32_t index = 0;
		Node<T>* ptrNode = ll.mFirstNode;
		if (ptrNode != nullptr)
		{
			while (ptrNode != nullptr)
			{
				os << "Value: " << ptrNode->getValue() << " at: " << index++ << "\n";
				ptrNode = ptrNode->getNext();
			}
		}
		else
		{
			os << "Error: No entries.\n";
		}
		return os;
	}

	Node<T>* findNodeByValue(T& value)
	{
		Node<T>* ptrNode = getFirstNode();
		while (ptrNode != nullptr)
		{
			if (ptrNode->getValue() == value)
			{
				return ptrNode;
			}
			ptrNode = ptrNode->getNext();
		}
		return nullptr;
	}

	Node<T>* findNodeByPosition(uint32_t position)
	{
		uint32_t index = getIndex();
		if (position >= 0 && position < index)
		{
			if (position > index / 2)
			{
				Node<T>* ptrNode = getLastNode();
				for (uint32_t i = index-1; i > position; i--)
				{
					ptrNode = ptrNode->getPrev();
				}
				return ptrNode;
			}
			else
			{
				Node<T>* ptrNode = getFirstNode();

				for (uint32_t i = 0; i < position; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				return ptrNode;
			}
		}
		return nullptr;
	}

	void swapNodes(Node<T>* nodeA, Node<T>* nodeB)
	{
		
		// Spezialf‰lle: 
		// Erste, Letzte Node;
		// Nebeneinander

		if (nodeA != nullptr && nodeB != nullptr)
		{
			if (nodeA->getNext() != nodeB && nodeA->getPrev() != nodeB)
			{
				Node<T>* nodeAPrev = nodeA->getPrev();
				Node<T>* nodeANext = nodeA->getNext();
				Node<T>* nodeBPrev = nodeB->getPrev();
				Node<T>* nodeBNext = nodeB->getNext();

				nodeA->setPrev(nodeBPrev);
				nodeA->setNext(nodeBNext);
				nodeB->setPrev(nodeAPrev);
				nodeB->setNext(nodeANext);

				if (nodeAPrev != nullptr)
				{
					nodeAPrev->setNext(nodeB);
				}
				else
				{
					setFirstNode(nodeB);
				}
				if (nodeANext != nullptr)
				{
					nodeANext->setPrev(nodeB);
				}
				else
				{
					setLastNode(nodeB);
				}
				if (nodeBPrev != nullptr)
				{
					nodeBPrev->setNext(nodeA);
				}
				else
				{
					setFirstNode(nodeA);
				}
				if (nodeBNext != nullptr)
				{
					nodeBNext->setPrev(nodeA);
				}
				else
				{
					setLastNode(nodeA);
				}

			}
			else if (nodeA->getNext() == nodeB)
			{
				Node<T>* nodeAPrev = nodeA->getPrev();
				Node<T>* nodeBNext = nodeB->getNext();

				nodeA->setPrev(nodeB);
				nodeB->setNext(nodeA);

				nodeA->setNext(nodeBNext);
				nodeB->setPrev(nodeAPrev);

				if (nodeAPrev != nullptr)
				{
					nodeAPrev->setNext(nodeB);
				}
				else
				{
					setFirstNode(nodeB);
				}
				if (nodeBNext != nullptr)
				{
					nodeBNext->setPrev(nodeA);
				}
				else
				{
					setLastNode(nodeA);
				}
				
			}
			else
			{
				Node<T>* nodeANext = nodeA->getNext();
				Node<T>* nodeBPrev = nodeB->getPrev();
					
				nodeA->setNext(nodeB);
				nodeB->setPrev(nodeA);

				nodeA->setPrev(nodeBPrev);
				nodeB->setNext(nodeANext);

				if (nodeANext != nullptr)
				{
					nodeANext->setPrev(nodeB);
				}
				else
				{
					setLastNode(nodeB);
				}
				if (nodeBPrev != nullptr)
				{
					nodeBPrev->setNext(nodeA);
				}
				else
				{
					setFirstNode(nodeA);
				}
			}
		}
		else
		{
			std::cerr << "Error: Node is a NULL.\n";
		}
		
		
	}

	void deleteNode(Node<T>* node)
	{
		bool isError = false;
		if (node != nullptr)
		{
			if (node->getPrev() != nullptr && node->getNext() != nullptr)
			{
				node->getPrev()->setNext(node->getNext());
				node->getNext()->setPrev(node->getPrev());
				node->setNext(nullptr);
				node->setPrev(nullptr);
			}
			else if (node->getPrev() == nullptr)
			{
				mFirstNode = node->getNext();
				node->getNext()->setPrev(nullptr);
				node->setNext(nullptr);
			}
			else if (node->getNext() == nullptr)
			{
				mLastNode = node->getPrev();
				node->getPrev()->setNext(nullptr);
				node->setPrev(nullptr);
			}
			else
			{
				std::cerr << "Error: Could not delete Node.\n";
				isError = true;
			}
			if (!isError)
			{
				mIndex--;
			}
		}
		else
		{
			std::cerr << "Error: Could not delete Node. The list seems to be empty.\n";
		}

	}


	//TODO: MergeSort
	Node<T>* MergeSort(Node<T>* firstNode)
	{
		bool print = true;

		Node<T>* firstHalf = firstNode;
		Node<T>* secondHalf = firstNode;

		while(secondHalf != nullptr && secondHalf->getNext() != nullptr)
		{
			secondHalf = secondHalf->getNext();
			if (secondHalf->getNext() != nullptr)
			{
				firstHalf = firstHalf->getNext();
				secondHalf = secondHalf->getNext();
			}
		}

		secondHalf = firstHalf->getNext();
		firstHalf = firstNode;
		secondHalf->getPrev()->setNext(nullptr);
		secondHalf->setPrev(nullptr);

		if (print)
		{
			Node<T>* ptrNode;
			std::cout << "first: ";
			ptrNode = firstHalf;
			while (ptrNode != nullptr)
			{
				std::cout << ptrNode->getValue() << " ";
				ptrNode = ptrNode->getNext();
			}
			std::cout << "\n";
			std::cout << "second: ";
			ptrNode = secondHalf;
			while (ptrNode != nullptr)
			{
				std::cout << ptrNode->getValue() << " ";
				ptrNode = ptrNode->getNext();
			}
			std::cout << "\n";
		}

		Node<T>* a = nullptr;
		Node<T>* b = nullptr;
		Node<T>* newFirstNode = nullptr;

		if (firstHalf->getNext() != nullptr)
		{
			a = MergeSort(firstHalf);
		}
		if (secondHalf->getNext() != nullptr)
		{
			b = MergeSort(secondHalf);
		}

		Node<T>* merged = new Node<T>;
		Node<T>* temp = new Node<T>;

		merged = temp;

		while (a != nullptr && b != nullptr)
		{
			if (a->getValue() <= b->getValue())
			{
				temp->getNext()->setNext(a);
				a = a->getNext();
			}
			else
			{
				temp->getNext()->setNext(b);
				b = b->getNext();
			}
			temp = temp->getNext();
			std::cout << temp->getValue();
		}

		if (print)
		{
			Node<T>* ptrNode;
			std::cout << "merged: ";
			ptrNode = temp;
			while (ptrNode != nullptr)
			{
				std::cout << ptrNode->getValue() << " ";
				ptrNode = ptrNode->getNext();
			}
			std::cout << "\n";
		}
		
		return temp;
	}


public:
	void MergeSort(LinkedList<T>& ll)
	{
		MergeSort(ll.getFirstNode());
	}

	void SwapPosition(uint32_t positionA, uint32_t positionB)
	{
		swapNodes(findNodeByPosition(positionA), findNodeByPosition(positionB));
	}
	void SwapValue(T ValueA, T ValueB)
	{
		swapNodes(findNodeByValue(ValueA), findNodeByValue(ValueB));
	}

	// Adds a node at the end of the linked list
	void Add(T value)
	{
		if (getFirstNode() == nullptr)
		{
			Node<T>* newNode = new Node<T>(value, nullptr, nullptr);
			setFirstNode(newNode);
			setLastNode(newNode);
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, nullptr, mLastNode);
			getLastNode()->setNext(newNode);
			setLastNode(newNode);
		}
		setIndex(getIndex() + 1);
	}

	// Adds a node at the given position
	void AddAt(T value, uint32_t position)
	{
		bool isError = false;
		uint32_t index = getIndex();
		Node<T>* ptrNode = nullptr;
		if (position > 0 && position < index - 1)
		{
			if (position > index / 2)
			{
				ptrNode = getLastNode();
				for (int i = index; i > position; i--)
				{
					ptrNode = ptrNode->getPrev();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode, ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->setPrev(newNode);

			}
			else
			{
				ptrNode = getFirstNode();
				for (int i = 0; i < position; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode, ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->setPrev(newNode);
			}
		}
		else if (position == 0 && index > 0)
		{
			Node<T>* newNode = new Node<T>(value, getFirstNode(), nullptr);
			getFirstNode()->setPrev(newNode);
			setFirstNode(newNode);
		}
		else if (index == 0)
		{
			Add(value);
		}
		else if (position == index)
		{
			Add(value);
		}
		else
		{
			std::cerr << "Error: Could not add. Position is out of range!\n";
			isError = true;
		}
		if (!isError)
		{
			setIndex(getIndex() + 1);
		}

	}


	// Overwrites the value of a node at the given position.
	void ReplaceAt(T value, uint32_t position)
	{
		uint32_t index = getIndex();
		Node<T>* ptrNode = nullptr;
		if (position > 0 && position > index - 1)
		{
			if (position > index / 2)
			{
				ptrNode = mLastNode;
				for (int i = index; i > position; i--)
				{
					ptrNode = ptrNode->getPrev();
				}
				ptrNode->setValue(value);
			}
			else
			{
				ptrNode = mFirstNode;
				for (int i = 0; i < position; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				ptrNode->setValue(value);
			}
		}
		else if (position == 0 && index > 0)
		{
			mFirstNode->setValue(value);
		}
		else if (index == 0)
		{
			std::cerr << "Error: Could not replace. The list seems to be empty!\n";
		}
		else if (position == index)
		{
			mLastNode->setValue(value);
		}
		else
		{
			std::cerr << "Error: Could not replace. Position is out of range!\n";
		}
	}

	// Returns the length of the linked list as an integer
	int getLength()
	{
		return getIndex();
	}

	// Deletes the node at the given position
	void deleteAt(uint32_t position)
	{
		uint32_t index = getIndex();
		Node<T>* ptrNode = nullptr;
		if (position > mIndex / 2)
		{
			ptrNode = mLastNode;
			for (uint32_t i = mIndex; i > position; i--)
			{
				ptrNode = ptrNode->getPrev();
			}
			deleteNode(ptrNode);
		}
		else
		{
			ptrNode = getFirstNode();
			for (uint32_t i = 0; i < position; i++)
			{
				ptrNode = ptrNode->getNext();
			}
			deleteNode(ptrNode);
		}

	}

	// Delete an amount of nodes
	// amount is the number of nodes to be deleted
	// fromStart deceides if it deletes the nodes from the beginning or the end of the linked list
	void deleteAmount(uint32_t amount, bool fromStart)
	{
		uint32_t index = getIndex();
		if (amount < index)
		{
			if (fromStart)
			{
				for (int i = 0; i < amount; i++)
				{
					setFirstNode(getFirstNode()->getNext());
				}
				getFirstNode()->getPrev()->setNext(nullptr);
				getFirstNode()->setPrev(nullptr);
			}
			else
			{
				for (int i = 0; i < amount; i++)
				{
					setLastNode(getLastNode()->getPrev());
				}
				getLastNode()->getNext()->setPrev(nullptr);
				getLastNode()->setNext(nullptr);
			}
			index -= amount;
		}
		else
		{
			std::cerr << "Error: Could not delete " << amount << " nodes. The length of the linked list is " << mIndex << ". \nDo you want to delete all? y/n\n";
			std::string answer = "";
			while ((answer != "y") && (answer != "n") && (answer != "Y") && (answer != "N"))
			{
				std::cin >> answer;
				if (answer == "y" || answer == "Y")
				{
					deleteAll();
				}
				else if (answer == "n" || answer == "N")
				{
					std::cerr << "Canceled function 'deleteAmount'.\n";
				}
				else
				{
					std::cerr << "Wrong input. Please input 'y' or 'n'.\n";
				}
			}

		}
		setIndex(index);
	}
	// Deletes all nodes
	void deleteAll()
	{
		mFirstNode = nullptr;
		mLastNode = nullptr;
		mIndex = 0;
	}

	// deletes all nodes with the given value.
	void deleteValue(T value)
	{
		Node<T>* ptrNode = mFirstNode;
		uint32_t found = 0;
		uint32_t index = 0;
		uint32_t length = getIndex();

		while (ptrNode != nullptr)
		{
			if (ptrNode->getValue() == value)
			{
				Node<T>* dNode = ptrNode;
				ptrNode = ptrNode->getNext();
				deleteNode(dNode);
				found++;
			}
			else
			{
				ptrNode = ptrNode->getNext();
			}
			index++;
		}
		if (found == 0)
		{
			std::cout << "No entries with the value '" << value << "' found.\n";
		}
		else
		{
			std::cout << "Deleted " << found << " entries.\n";
		}
	}

	// Returns true if the list is empty
	bool isEmpty()
	{
		if (mFirstNode == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Inverts the list.
	void invertList()
	{
		Node<T>* ptrNode = mLastNode;
		mLastNode = mFirstNode;
		mFirstNode = ptrNode;

		while (ptrNode != nullptr)
		{
			Node<T>* tempNode = ptrNode;
			ptrNode = ptrNode->getPrev();
			tempNode->setPrev(tempNode->getNext());
			tempNode->setNext(ptrNode);
		}

	}


	// Make privat when done testing 
	public:

	void Print()
	{
		if (mFirstNode == nullptr)
		{
			std::cerr << "Error: No entries!\n";
		}
		else
		{
			Node<T>* ptrNode = mFirstNode;
			while (ptrNode != nullptr)
			{
				std::cout << "[" << ptrNode->getValue() << "]";
				ptrNode = ptrNode->getNext();
			}
			std::cout << "\n";
		}
	}

	void PrintWithIndex()
	{
		uint32_t index = 0;
		if (mFirstNode == nullptr)
		{
			std::cerr << "Error: No entries!\n";
		}
		else
		{
			Node<T>* ptrNode = mFirstNode;
			while (ptrNode != nullptr)
			{
				std::cout << "[" << ptrNode->getValue() << "|(" << index++ << ")]";
				ptrNode = ptrNode->getNext();
			}
			std::cout << "\n";
		}
	}

	void PrintReverse()
	{
		if (mFirstNode == nullptr)
		{
			std::cerr << "Error: No entries!\n";
		}
		else
		{
			Node<T>* ptrNode = mLastNode;
			while (ptrNode != nullptr)
			{
				std::cout << "[" << ptrNode->getValue() << "]";
				ptrNode = ptrNode->getPrev();
			}
			std::cout << "\n";
		}
	}

	void PrintReverseWithIndex()
	{
		uint32_t index = mIndex - 1;
		if (mFirstNode == nullptr)
		{
			std::cerr << "Error: No entries!\n";
		}
		else
		{
			Node<T>* ptrNode = mLastNode;
			while (ptrNode != nullptr)
			{
				std::cout << "[" << ptrNode->getValue() << "|(" << index-- << ")]";
				ptrNode = ptrNode->getPrev();
			}
			std::cout << "\n";
		}
	}

};

#endif
