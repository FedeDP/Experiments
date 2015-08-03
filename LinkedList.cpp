#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class LinkedList {

private:
    struct Node {
        T value;
        Node *next;

        Node(const T v): value(v), next(nullptr) {}
    };

    Node *head;

    void free_node(Node *t) {
        if (t->next) {
            free_node(t->next);
        }
        delete t;
    }

    void copy_nodes(const LinkedList &l) {
        auto tmp = l.head;

        head = new Node(tmp->value);
        while (tmp->next) {
            add_node(tmp->next->value);
            tmp = tmp->next;
        }
    }

public:
    LinkedList(const T value) {
        head = new Node(value);
    }

    LinkedList(const LinkedList<T> &l) {
        cout << "Copy constructor." << endl;
        copy_nodes(l);
    }

    ~LinkedList() {
        cout << "freeing nodes" << endl;
        free_node(head);
    }

    LinkedList& operator=(const LinkedList &l) {
        cout << "Assigning..." << endl;
        free_node(head);
        copy_nodes(l);
        return *this;
    }

    friend ostream& operator<<(ostream& out, const LinkedList &l) {
        auto tmp = l.head;

        while (tmp) {
            out << tmp->value << endl;
            tmp = tmp->next;
        }
        return out;
    }

    void add_node(const T value) {
        auto tmp = head;

        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = new Node(value);
    }

    void sort() {
        Node *first = head, *second, *sw;
        T min;

        while (first) {
            min = first->value;
            sw = first;
            for (second = first; second; second = second->next) {
                if (second->value < min) {
                    min = second->value;
                    sw = second;
                }
            }
            sw->value = first->value;
            first->value = min;
            first = first->next;
        }
    }

    // Do not mix insert_sorted and add_node!!
    void insert_sorted(const T value) {
        auto tmp = head;
        T first, second;

        while (tmp && value > tmp->value) {
            tmp = tmp->next;
        }
        if (tmp) {
            auto last = tmp;

            while (last->next) {
                last = last->next;
            }
            add_node(last->value);
            first = tmp->value;
            tmp->value = value;
            tmp = tmp->next;
            while (tmp) {
                second = tmp->value;
                tmp->value = first;
                first = second;
                tmp = tmp->next;
            }
        } else {
            add_node(value);
        }
    }

    int size() {
        auto i = 0, tmp = head;

        while (tmp) {
            i++;
            tmp = tmp->next;
        }
        return i;
    }
};

int main() {
    LinkedList<int> myList(5);

    myList.add_node(2);
    myList.add_node(64);
    myList.sort();
    cout << myList << endl;

    cout << "check copy constructor" << endl;
    LinkedList<int> copiedList(myList);
    cout << copiedList << endl;

    cout << "adding 5 to first list, and assigning first list to second one" << endl;
    myList.add_node(5);
    copiedList = myList;
    cout << copiedList << endl;

    cout << "check insert_sorted" << endl;
    LinkedList<int> sortedList(10);
    sortedList.insert_sorted(5);
    sortedList.insert_sorted(1);
    cout << sortedList << endl;

    cout << "check template" << endl;
    LinkedList<string> charList("hello");
    charList.add_node("world");
    cout << charList << endl;

    LinkedList<string> charSortedList("c");
    charSortedList.insert_sorted("a");
    charSortedList.insert_sorted("b");
    cout << charSortedList << endl;
}