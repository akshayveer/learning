#include <iostream>
#include <stdexcept>

using namespace std;

#define MAX_SIZE 50
char text[MAX_SIZE];

struct linkedListNode {
	char c;
	linkedListNode* next;
	linkedListNode* prev;
	linkedListNode (char cc) {
		c = cc;
	}
};

struct state
{
	int command;
	int pos;
	char val;
};


class Stack
{
	state container[MAX_SIZE];
	int length;
	int end;
public:
	Stack() {
		length = 0;
		end = -1;
	}

	void push(int command, int pos, char val) {
		end++;
		container[end].command = command;
		container[end].pos = pos;
		container[end].val = val;
		length++;
	}

	state top() {
		return container[end];
	}

	void pop() {
		end--;
		length--;
	}

	bool empty() {
		return length == 0;
	}

	void clear() {
		length = 0;
		end = -1;
	}
	
};

class LinkedList
{
	linkedListNode* head;
	linkedListNode* tail;
	int length;

private:

	linkedListNode* getNode(int pos) {
		linkedListNode* current = head;

		for (int i = 0;i < pos && current;i++) {
			current = current->next;
		}

		return current;
	}

	void insertLast(char c) {
		if (tail == NULL) {
			tail = new linkedListNode(c);
			head = tail;
		}
		else {
			tail->next = new linkedListNode(c);
			tail->next->prev = tail;
			tail = tail->next;
		}
	}

	void insertFirst(char c) {
		if (head == NULL) {
			head = new linkedListNode(c);
			tail = head;
		}
		else {
			linkedListNode* child = new linkedListNode(c);
			child->next = head;
			head->prev = child;
			head = child;
		}
	}

	void insertBefore(char c, linkedListNode* node) {
		linkedListNode* prev = node->prev;
		linkedListNode* child = new linkedListNode(c);
		child->next = node;
		node->prev = child;

		if (prev == NULL) {
			head = child;
		}
		else {
			prev->next = child;
			child->prev = prev;
		}
	}

	void remove(linkedListNode* node) {
		linkedListNode* prev = node->prev;
		linkedListNode* next = node->next;

		if (prev != NULL) {
			prev->next = next;
		}

		if (next != NULL) {
			next->prev = prev;
		}

		if (prev == NULL) {
			head = next;
		}

		if (next == NULL) {
			tail = prev;
		}
	}

public:
	LinkedList() {
		head = NULL;
		tail = NULL;
		length = 0;
	}


	void insert(char c, int pos) {
		pos = min(pos, length);
		
		linkedListNode* node = getNode(pos);
		if (node == NULL) {
			insertLast(c);
		}
		else {
			insertBefore(c, node);
		}
		length++;
		
	}


	char remove(int pos) {
		char ret = 0;
		
		if (pos < length && pos >= 0) {
			linkedListNode* node = getNode(pos);
			if (node == NULL) {
				cout << "ambious result\n";
			}
			else {
				ret = node->c;
				remove(node);
				length--;
			}
		}
		return ret;
	}

	void clear() {
		head = tail = NULL;
		length = 0;
	}

	char* show() {
		cout << "show called\n";
		int i = 0;
		linkedListNode* cur = head;
		while (i < MAX_SIZE && cur) {
			cout << cur->c << endl;
			text[i] = cur->c;
			i++;
			cur = cur->next;
		}
		text[i] = '\0';
		return text;
	}

	void print_list() {
		linkedListNode* cur = head;
		while (cur) {
			cout << cur->c;
			cur = cur->next;
		}
		cout << endl;
	}

};

class TextEditor
{
	Stack undoStack;
	Stack redoStack;

	LinkedList list;
	const static int ADD = 0;
	const static int REMOVE = 1;
	int cursor_position;

private:
	char del() {
		char c = list.remove(cursor_position - 1);
		if (c) cursor_position--;
		return c;
	}

	void ins(char c) {
		list.insert(c, cursor_position);
		cursor_position++;
	}

public:

	void clear() {
		undoStack.clear();
		redoStack.clear();
		list.clear();
		cursor_position = 0;
	}

	void init(char* str) {
		int i = 0;
		while (i < MAX_SIZE && str[i]) {
			ins(str[i]);
			i++;
		}
	}

	void insert(char c) {
		redoStack.clear();
		if (c == '\b') {
			// remove undo will be add
			char ret = del();
			undoStack.push(REMOVE, cursor_position, ret);
		}
		else {
			// we are  adding so unod will bre rmeove
			ins(c);
			undoStack.push(ADD, cursor_position, 0);

		}
	}

	void move(int pos) {
		cursor_position = pos;
	}

	void undo() {
		if (!undoStack.empty()) {
			int command = undoStack.top().command;
			cursor_position = undoStack.top().pos;
			int c = undoStack.top().val;
			undoStack.pop();

			if (command == ADD) {
				char ret = del();
				redoStack.push(REMOVE, cursor_position, ret);
			}
			else {
				ins(c);
				redoStack.push(ADD, cursor_position, 0);
			}
		}
	}

	void redo() {
		if (!redoStack.empty()) {
			int command = redoStack.top().command;
			cursor_position = redoStack.top().pos;
			char c = redoStack.top().val;

			redoStack.pop();
			if (command == ADD) {
				insert('\b');
			}
			else {
				insert(c);
			}
		}
	}

	char* show() {
		print_list();
		return text;
	}

	void print_list() {
		list.print_list();
	}
};

TextEditor editor;

void init(char* str) {
	editor.clear();
	editor.init(str);
	editor.print_list();

}

void add(char c) {
	editor.insert(c);
	editor.print_list();
}

void move(int pos) {
	editor.move(pos);
	editor.print_list();
}

void undo() {
	editor.undo();
	editor.print_list();
}

void redo() {
	editor.redo();
	editor.print_list();
}

char* show() {
	return editor.show();
}

void print_list() {
	editor.print_list();
}

