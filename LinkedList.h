#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template <typename T>
class LinkedList
{
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
			os << "Keine Eintraege vorhanden.\n";
		}
		return os;
	}

	uint32_t getIndex()
	{

	}


public:
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

	void AddAt(T value, uint32_t index)
	{
		Node<T>* ptrNode;
		if (index > 0 && index < mIndex)
		{
			if (index > mIndex / 2)
			{
				ptrNode = mLastNode;
				for (int i = mIndex; i > index; i--)
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
				for (int i = 0; i < index; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode, ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->setPrev(newNode);
			}
		}
		else
		{
			std::cerr << "Fehler: Außerhalb des Index!";
		}
		mIndex++;
	}

	// eigentlich würde es reichen den Wert zu überschreiben
	void ReplaceAt(T value, uint32_t index)
	{
		Node<T>* ptrNode;
		if (index > 0 && index < mIndex)
		{
			if (index > mIndex / 2)
			{
				ptrNode = mLastNode;
				for (int i = mIndex; i > index; i--)
				{
					ptrNode = ptrNode->getPrev();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode->getNext(), ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->getNext()->setPrev(newNode);

			}
			else
			{
				ptrNode = mFirstNode;
				for (int i = 0; i < index; i++)
				{
					ptrNode = ptrNode->getNext();
				}
				Node<T>* newNode = new Node<T>(value, ptrNode->getNext(), ptrNode->getPrev());
				ptrNode->getPrev()->setNext(newNode);
				ptrNode->getNext()->setPrev(newNode);
			}
			~ptrNode();
		}
		else
		{
			std::cerr << "Fehler: Außerhalb des Index!";
		}

	}

	// ToDo: 
	// - Entfernen von Elementen 
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
			std::cerr << "Keinen Inhalt gefunden";
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
			std::cerr << "Keinen Inhalt gefunden";
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
			std::cerr << "Keinen Inhalt gefunden";
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
			std::cerr << "Keinen Inhalt gefunden";
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
