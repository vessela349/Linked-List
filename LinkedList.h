#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* next;
	Node(const T& data, Node<T>* next) {
		this->data = data;
		this->next = next;
	}
};

template <typename T>
class LinkedList {
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;

	void copy(const LinkedList& other) {
		Node<T>* temp = other.getFirst();
		for (size_t i = 0; i < other.getNumOfElem(); i++) {
			this->pushBack(temp->data);
			temp = temp->next;
		}
	}

	void init() {
		this->first = NULL;
		this->last = NULL;
		this->size = 0;
	}

	void destroy() {
		while (this->first != NULL) {
			this->popFront();
		}
	}

public:
	LinkedList() {
		init();
	}

	bool isEmpty() const {
		return this->size == 0;
	}

	Node<T>* getFirst() const {
		if (this->isEmpty()) {
			return NULL;
		}
		return this->first;
	}

	LinkedList(const LinkedList& other) {
		this->init();
		copy(other);
	}
	LinkedList& operator=(const LinkedList& other) {
		if (this != &other) {
			this->destroy();
			this->init();
			this->copy(other);
		}
		return *this;
	}

	~LinkedList() {
		this->destroy();
		this->init();
	}

	size_t getNumOfElem() const {
		return this->size;
	}

	void pushFront(const T& element) {
		Node<T>* temp = new Node<T>(element, this->first);
		this->first = temp;
		if (this->isEmpty()) {
			this->last = temp;
		}
		this->size++;
	}

	void pushBack(const T& element) {
		Node<T>* temp = new Node<T>(element, NULL);
		if (temp) {
			if (this->isEmpty()) {
				this->first = temp;
				this->last = temp;
			}
			else {
				this->last->next = temp;
				this->last = temp;
			}
			this->size++;
		}
	}

	void popFront() {
		if (!this->isEmpty()) {
			Node<T>* temp = this->first;
			this->first = this->first->next;
			if (this->size == 1) {
				this->last = NULL;
				this->first = NULL;
			}
			size--;
			delete temp;
		}
		else {
			cout << "Empty list, nothing to delete." << endl;
		}
	}



	void popBack() {
		if (!this->isEmpty()) {
			if (this->last) {
				this->deleteAt(this->size - 1);
			}
		}
	}
	friend ostream& operator<<(ostream& os, const LinkedList& list) {
		Node<T>* temp = list.getFirst();
		while (temp != NULL) {
			os << " " << temp->data;
			temp = temp->next;
		}
		return os;
	}
	bool insertAt(const T& value, size_t index) {
		if (index == 0) {
			pushFront(value);
			return true;
		}
		if (index == this->size - 1) {
			pushBack(value);
			return true;
		}
		Node<T>* temp = this->first;
		while (temp != NULL && index > 1) {
			temp = temp->next;
			index--;
		}
		if (temp == NULL)
		{
			return false;
		}
		temp->next = new Node<T>(value, temp->next);
		this->size++;
		return true;

	}
	void deleteAt(size_t index) {
		if (!this->isEmpty()) {
			if (index == 0) {
				this->popFront();
				return;
			}
			Node<T>* temp1 = this->first;
			Node<T>* temp2 = NULL;
			while (temp1 != NULL && index > 0) {
				if (index == 1) {
					temp2 = temp1;            
				}
				temp1 = temp1->next;
				index--;
			}
			if (temp1 == NULL) {
				return;
			}
			temp2->next = temp1->next;
			delete temp1;
			this->size--;
		}
	}

};
