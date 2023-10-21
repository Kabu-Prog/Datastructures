#ifndef LINKEDLIST_H
#define LINKEDLIST_H


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

		// das sollten genug einträge sein

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
			if (mPrev != nullptr)
			{
				return mPrev;
			}
			else
			{
				return nullptr;
			}
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

	void deleteNode(Node<T>* node)
	{
		bool isError = false;
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
			std::cerr << "Error: Could not delete Node.";
			isError = true;
		}
		if (!isError)
		{
			mIndex--;
		}
	}

public:
	// Adds a node at the end of the linked list
	void Add(T value)
	{
		if (mFirstNode == nullptr)
		{
			Node<T>* newNode = new Node<T>(value, nullptr, nullptr);
			mFirstNode = newNode;
			mLastNode = newNode;
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, nullptr, mLastNode);
			mLastNode->setNext(newNode);
			mLastNode = newNode;
		}
		mIndex++;
	}

	// Adds a node at the given position
	void AddAt(T value, uint32_t position)
	{
		bool isError = false;
		Node<T>* ptrNode;
		if (position > 0 && position < mIndex-1)
		{
			if (position > mIndex / 2)
			{
				ptrNode = mLastNode;
				for (int i = mIndex; i > position; i--)
				{
					ptrNode = ptrNode->getPrev();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode, ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->setPrev(newNode);

			}
			else
			{
				ptrNode = mFirstNode;
				for (int i = 0; i < position; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode, ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->setPrev(newNode);
			}
		}
		else if (position == 0 && mIndex > 0)
		{
			Node<T>* newNode = new Node<T>(value, mFirstNode, nullptr);
			mFirstNode->setPrev(newNode);
			mFirstNode = newNode;
		}
		else if (mIndex == 0)
		{
			Add(value);
		}
		else if (position == mIndex)
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
			mIndex++;
		}
		
	}

	// Overwrites the value of a node at the given position.
	void ReplaceAt(T value, uint32_t position)
	{
		Node<T>* ptrNode;
		if (position > 0 && position < mIndex - 1)
		{
			if (position > mIndex / 2)
			{
				ptrNode = mLastNode;
				for (int i = mIndex; i > position; i--)
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
		else if (position == 0 && mIndex > 0)
		{
			mFirstNode->setValue(value);
		}
		else if (mIndex == 0)
		{
			Add(value);
		}
		else if (position == mIndex)
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
		return mIndex;
	}

	// Deletes the node at the given position
	void deleteAt(int position)
	{
		Node<T>* ptrNode;
		if (position > mIndex / 2)
		{
			ptrNode = mLastNode;
			for (int i = mIndex; i > position; i--)
			{
				ptrNode = ptrNode->getPrev();
			}
			deleteNode(ptrNode);
		}
		else
		{
			ptrNode = mFirstNode;
			for (int i = 0; i < position; i++)
			{
				ptrNode = ptrNode->getNext();
			}
			deleteNode(ptrNode);
		}

	}
	// Delete an amount of nodes
	// amount is the number of nodes to be deleted
	// fromStart deceides if it deletes the nodes from the beginning or the end of the linked list
	void deleteAmount(int amount, bool fromStart)
	{
		if (amount < mIndex)
		{
			if (fromStart)
			{
				for (int i = 0; i < amount; i++)
				{
					mFirstNode = mFirstNode->getNext();
				}
				mFirstNode->getPrev()->setNext(nullptr);
				mFirstNode->setPrev(nullptr);
			}
			else
			{
				for (int i = 0; i < amount; i++)
				{
					mLastNode = mLastNode->getPrev();
				}
				mLastNode->getNext()->setPrev(nullptr);
				mLastNode->setNext(nullptr);
			}
			mIndex -= amount;
		}
		else
		{
			std::cerr << "Error: Could not delete " << amount << " nodes. The length of the linked list is " << mIndex << ". Do you want to delete all? y/n";
			std::string answer = "";
			while (answer != "y" || answer != "n" || answer != "Y" || answer != "N")
			{
				std::cin >> answer;
				if (answer == "y" || answer == "Y")
				{
					deleteAll();
				}
				else if (answer == "n" || answer == "N")
				{
					std::cerr << "Canceled function 'deleteAmount'.";
				}
				else
				{
					std::cerr << "Wrong input. Please input 'y' or 'n'.";
				}
			}
			
		}
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
		int found = 0;
		int index = 0;
		int length = mIndex;

		while(ptrNode != nullptr)
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


	// ToDo: 

	// - Zugriff auf Element nach Position
	// - Zugriff auf Element nach Inhalt
	// - Überprüfen ob Liste leer ist
	// - Umkehren der Liste
	// - Sortieren der Liste
	// - Iteration über die Liste um Operationen auf Element auszuführen
	// - Zusammenführen von Listen




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
		uint32_t index = mIndex -1;
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
