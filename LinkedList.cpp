#include <iostream>

using namespace std;

template <typename T>
class LinkedList {

private:
    struct Node {
        T value;
        Node *next;

        public:
            Node(const T v): value(v), next(nullptr) {

            }
    };

    Node *head = nullptr;
    Node *last = nullptr;

public:
    // Da definire, ctor, copy-ctor, copy assignment

    void push_back(const T value) {
        if (!head) {
            head = new Node(value);
            last = head;
        } else {
            last->next = new Node(value);
            last = last->next;
        }
    }

    friend ostream& operator<<(ostream& out, const LinkedList& l) {
        Node *tmp = l.head;

        while (tmp) {
            out << tmp->value << endl;
            tmp = tmp->next;
        }
        return out;
    }

    void sort() {
        Node *tmp = head, *temp, *sw;
        T min;

        while (tmp) {
            min = tmp->value;
            sw = tmp;
            for (temp = tmp; temp; temp = temp->next) {
                if (temp->value < min) {
                    min = temp->value;
                    sw = temp;
                }
            }
            sw->value = tmp->value;
            tmp->value = min;
            tmp = tmp->next;
        }
    }

    // Do not mix insert_sorted and push_back!!
    void insert_sorted(const T value) {
        Node *tmp = head;
        T temp, temp2;

        while (tmp && value > tmp->value) {
            tmp = tmp->next;
        }
        if (tmp) {
            push_back(last->value);
            temp = tmp->value;
            tmp->value = value;
            tmp = tmp->next;

            while (tmp != last) {
                temp2 = tmp->value;
                tmp->value = temp;
                tmp = tmp->next;
            }
        } else {
            push_back(value);
        }
    }

    int size() {
        int i = 0;
        Node *tmp = head;

        while (tmp) {
            i++;
            tmp = tmp->next;
        }
        return i;
    }

    ~LinkedList() {
        // Itera nodi e chiama delete su ognuno
    }

};

int main() {
    LinkedList<int> myList, sortedList;
    LinkedList<string> charList, charSortedList;

    myList.push_back(5);
    myList.push_back(2);
    myList.push_back(64);
    cout << myList;
    myList.sort()();
    cout << myList;

    sortedList.insert_sorted(10);
    sortedList.insert_sorted(5);
    sortedList.insert_sorted(1);
    cout << sortedList;

    charList.push_back("hello");
    charList.push_back("world");
    cout << charList;

    charSortedList.insert_sorted("c");
    charSortedList.insert_sorted("a");
    charSortedList.insert_sorted("b");
    cout << charSortedList;
}
