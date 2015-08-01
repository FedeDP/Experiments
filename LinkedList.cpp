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

    void free_node(Node *t) {
        if (t->next) {
            free_node(t->next);
        }
        delete t;
    }

public:
    void add_node(const T value) {
        last_elem->next = new Node(value);
        last_elem = last_elem->next;
    }

    friend ostream& operator<<(ostream& out, const LinkedList &l) {
        auto *tmp = l.head;

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

    // Do not mix insert_sorted and add_node!!
    void insert_sorted(const T value) {
        auto *tmp = head;
        T temp, temp2; // fix temp2 usage here...

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
                temp = temp2;
                tmp = tmp->next;
            }
        } else {
            add_node(value);
        }
    }

    int size() {
        auto i = 0, *tmp = head;

        while (tmp) {
            i++;
            tmp = tmp->next;
        }
        return i;
    }

    LinkedList(const T value) {
        head = new Node(value);
        last_elem = head;
    }

    LinkedList(const LinkedList<T> &l) {
        auto *tmp = l.head;

        cout << "Copy constructor." << endl;
        head = new Node(tmp->value);
        last_elem = head;
        while (tmp->next) {
            add_node(tmp->next->value);
            tmp = tmp->next;
        }
    }

    ~LinkedList() {
        cout << "freeing nodes" << endl;
        free_node(head);
    }

    void operator=(const LinkedList &l) {
        cout << "Assigning..." << endl;
        head = l.head;
        last_elem = l.last_elem;
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