#include <iostream>
using namespace std;

#define INIT 0
#define ADD 1
#define MOVE 2
#define UNDO 3
#define REDO 4
#define SHOW 5

#define MAX_SIZE 50

extern void init(char* str);
extern void add(char c);
extern void move(int pos);
extern void undo();
extern void redo();
extern char* show();
extern void print_list();

int main() {
	int n;
	cin >> n;
	int c;
	string s;
	int v;
	char value[MAX_SIZE];
	for (int i = 0;i < n;i++) {
		cin >> c;
		switch (c) {
			case INIT: {
				cin >> value;
				init(value);
				break;
			}
			case ADD: {
				cin >> value;
				for (int i = 0;value[i];i++) {
					add(value[i]);
				}
				break;
			}
			case MOVE: {
				cin >> v;
				move(v);
				break;
			}
			case UNDO: {
				undo();
				break;
			}
			case REDO: {
				redo();
				break;
			}
			print_list();
		}
	}
}