#include <iostream>

using namespace std;

template <typename T>
class LinkedList {

private:
    struct Node {
        T value;
        Node *next;

        public: Node(const T v): value(v), next(nullptr) {}
    };
    Node *head = nullptr;
    Node *last_elem = nullptr;

public:
    void add_node(const T value) {
        if (!head) {
            head = new Node(value);
            last_elem = head;
        } else {
            last_elem->next = new Node(value);
            last_elem = last_elem->next;
        }
    }

    friend ostream& operator<<(ostream& out, const LinkedList myList) {
        Node *tmp = myList.head;

        while (tmp) {
            out << tmp->value << endl;
            tmp = tmp->next;
        }
        return out;
    }

    void sort_list() {
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

    // Do not mix insert_sorted and add_node!!
    void insert_sorted(const T value) {
        Node *tmp = head;
        T temp, temp2;

        while (tmp && value > tmp->value) {
            tmp = tmp->next;
        }
        if (tmp) {
            add_node(last_elem->value);
            temp = tmp->value;
            tmp->value = value;
            tmp = tmp->next;
            while (tmp != last_elem) {
                temp2 = tmp->value;
                tmp->value = temp;
                tmp = tmp->next;
            }
        } else {
            add_node(value);
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
};

int main() {
    LinkedList<int> myList, sortedList;
    LinkedList<string> charList, charSortedList;

    myList.add_node(5);
    myList.add_node(2);
    myList.add_node(64);
    cout << myList;
    myList.sort_list();
    cout << myList;

    sortedList.insert_sorted(10);
    sortedList.insert_sorted(5);
    sortedList.insert_sorted(1);
    cout << sortedList;

    charList.add_node("hello");
    charList.add_node("world");
    cout << charList;

    charSortedList.insert_sorted("c");
    charSortedList.insert_sorted("a");
    charSortedList.insert_sorted("b");
    cout << charSortedList;
}