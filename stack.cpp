// Stack
#include<iostream>
using namespace std;

template <class datatype>
class StackInterface{
public:
	virtual void push(datatype data) = 0;
	virtual datatype peek() = 0;
	virtual void pop() = 0;
	virtual bool isEmpty() = 0;
	virtual bool isFull(){
		return true;
	};
	virtual void display() = 0;
};

template <class datatype>
class StackAsArray:public StackInterface<datatype>{
	datatype* array;
	int top;
	int size;
public:
	StackAsArray(int size){
		top = -1;
		array = new datatype[size];
		this->size = size;
	}

	StackAsArray(){
			top = -1;
			array = new datatype[50];
			this->size = 50;
		}

	void push(datatype data){
		if(!isFull())
			array[++top] = data;
		else
			cout<<"The stack in full of contents, cannot push "<<data<<" anymore"<<endl;
	}

	void pop(){
		if(!isEmpty())
			--top;
		else
			cout<<"There are no elements in the stack to pop"<<endl;
	}

	bool isFull(){
		if(top == size - 1)
			return true;
		return false;
	}

	bool isEmpty(){
		if(top == -1)
			return true;
		return false;
	}

	datatype peek(){
		if(!isEmpty())
		return array[top];

		cout<<"There are no elements in the stack"<<endl;
		return -1;
	}

	void display(){
		if(!isEmpty()){
			for(int i=0;i<=top;++i){
				if(i!=top)
					cout<<array[i]<<" | ";
				else
					cout<<array[i]<<endl;
			}
		}
		else
			cout<<"The stack is empty..."<<endl;
	}
};

template <class datatype>
class StackAsLinkedlist:public StackInterface<datatype>{
	StackAsLinkedlist* head;
public:
	datatype data;
	StackAsLinkedlist* next;
	StackAsLinkedlist(){
		head = NULL;
	}

	void push(datatype data){
		StackAsLinkedlist<datatype>* newNode = new StackAsLinkedlist<datatype>();
		newNode->data = data;
		newNode->next = head;
		head = newNode;
	}

	void pop(){
		if(!isEmpty()){
			StackAsLinkedlist* firstNode = head;
			head = head->next;
			delete firstNode;
		}
		else
			cout<<"There are no elements in the stack to pop"<<endl;
	}

	bool isEmpty(){
		if(head == NULL)
			return true;
		return false;
	}

	datatype peek(){
		if(!isEmpty())
		return head->data;

		cout<<"There are no elements in the stack"<<endl;
		return -1;
	}

	void display(){
		if(!isEmpty()){
			StackAsLinkedlist* temp = head;
			while(temp != NULL){
				if(temp->next == NULL)
					cout<<temp->data<<endl;
				else
					cout<<temp->data<<" | ";
				temp = temp->next;
			}
		}
		else
			cout<<"The stack is empty..."<<endl;
	}
};

template <class datatype>
class StackFacade{
public:
	static StackInterface<datatype>* getInstance(string type = "linkedlist",int size = 50){
		if(type == "array")
			return new StackAsArray<datatype>(size);
		else
			return new StackAsLinkedlist<datatype>();
	}
};

int main(){
	StackInterface<int>* stack = StackFacade<int>::getInstance();
	int n,data;
	do{
		cout<<"--------- Menu ---------"<<endl;
		cout<<"1. Push"<<endl;
		cout<<"2. Pop"<<endl;
		cout<<"3. Peek"<<endl;
		cout<<"4. Display contents"<<endl;
		cout<<"5. Exit"<<endl;

		cout<<"Enter your choice(1-4)";
		cin>>n;
		switch(n){
			case 1:cout<<"Enter an value: ";
				   cin>>data;
				   stack->push(data);
				   break;
			case 2:stack->pop(); break;
			case 3:cout<<"Peek: "<<stack->peek()<<endl; break;
			case 4:cout<<"Contents: "; stack->display(); break;
		}
	}while(n != 5);

	return 0;
}