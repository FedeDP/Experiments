#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class LinkedList {

private:
    struct Node {
        T value;
        unique_ptr<Node> next;

        Node(const T v): value(v) {}
    };

    unique_ptr<Node> head;
    size_t length;

    void copy_nodes(const LinkedList &l) {
        auto tmp = l.head.get();

        length = 1;
        head = unique_ptr<Node>(new Node(tmp->value));
        while (tmp->next) {
            add_node(tmp->next->value);
            tmp = tmp->next.get();
        }
    }

public:
    LinkedList(const T value) {
        head = unique_ptr<Node>{new Node(value)};
        length = 1;
    }

    LinkedList(const LinkedList<T> &l) {
        copy_nodes(l);
    }

    LinkedList& operator=(const LinkedList &l) {
        copy_nodes(l);
        return *this;
    }

    friend ostream& operator<<(ostream& out, const LinkedList &l) {
        auto tmp = l.head.get();

        while (tmp) {
            out << tmp->value << endl;
            tmp = tmp->next.get();
        }
        return out;
    }

    void add_node(const T value) {
        auto tmp = head.get();

        while (tmp->next) {
            tmp = tmp->next.get();
        }
        tmp->next = unique_ptr<Node>{new Node(value)};
        length++;
    }

    T get(size_t index) const {
        auto tmp = head.get();

        if ((index < 1) || (index > length)) {
            throw out_of_range("Index out of range");
        }
        do {
            index--;
            tmp = tmp->next.get();
        } while (index != 1);
        return tmp->value;
    }

    void set(size_t index, T value) {
        auto tmp = head.get();

        if ((index < 1) || (index > length)) {
            throw out_of_range("Index out of range");
        }
        do {
            index--;
            tmp = tmp->next.get();
        } while (index != 1);
        tmp->value = value;
    }

    void sort() const {
        Node *first = head.get();
        Node *second, *sw;
        T min;

        while (first) {
            min = first->value;
            sw = first;
            for (second = first; second; second = second->next.get()) {
                if (second->value < min) {
                    min = second->value;
                    sw = second;
                }
            }
            sw->value = first->value;
            first->value = min;
            first = first->next.get();
        }
    }

    // Do not mix insert_sorted and add_node!!
    void insert_sorted(const T value) {
        auto tmp = head.get();
        T first, second;

        while (tmp && value > tmp->value) {
            tmp = tmp->next.get();
        }
        if (tmp) {
            auto last = tmp;

            while (last->next) {
                last = last->next.get();
            }
            add_node(last->value);
            first = tmp->value;
            tmp->value = value;
            tmp = tmp->next.get();
            while (tmp) {
                second = tmp->value;
                tmp->value = first;
                first = second;
                tmp = tmp->next.get();
            }
        } else {
            add_node(value);
        }
    }

    size_t size() const {
        return length;
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

    cout << "checking getter" << endl;
    try {
        auto x = charSortedList.get(4);
        cout << x << endl;
    } catch (const out_of_range& oor) {
        cerr << "Out of Range error: " << oor.what() << endl;
    }

    cout << "checking setter" << endl;
    try {
        charSortedList.set(2, "L");
        auto x = charSortedList.get(2);
        cout << x << endl;
    } catch (const out_of_range& oor) {
        cerr << "Out of Range error: " << oor.what() << endl;
    }

    cout << "checking size operator" << endl;
    auto x = charSortedList.size();
    cout << x << endl;
}