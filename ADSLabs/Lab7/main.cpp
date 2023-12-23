#include <iostream>

struct Node {
    char data;
    Node* next;
};

class ForwardList {
private:
    Node* head;
    char max = 0, min = 127;
    size_t size = 0;

public:
    ForwardList() : head(nullptr) {}

    void push_front(char value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        if(value > max) max = value;
        if(value < min) min = value;
        size++;
    }
    int find_pos(char elem){
        Node *tmp = head;
        int i = 0;
        for(; tmp->data != elem; tmp = tmp->next, i++)
        {
            if (tmp->next == nullptr ){
                i = -1;
                break;
            }
        }
        return i;

    }
    void append(const ForwardList& other) {
        if (other.head == nullptr) {
            return; // Nothing to append
        }

        if (head == nullptr) {
            head = new Node{other.head->data, nullptr};
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node{other.head->data, nullptr};
        }

        Node* current = head;
        Node* otherCurrent = other.head->next;
        while (otherCurrent != nullptr) {
            current->next = new Node{otherCurrent->data, nullptr};
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    void weirdFunction() {
        Node* current = head;
        Node* tmp = head;
        for (int i = 0; i < 2; i++) {
            current = current->next;
        }
        for (int i = 0; i < size - 2; i++) {
            tmp = tmp->next;
        }
        std::cout << "Third element: " << current->data<< std::endl;
        std::cout << "Second from end element: " << tmp->data<< std::endl;
        std::cout << std::endl;
    }
    void strangeFunction() {
        Node* current = head;
        Node* tmp = head;
        int id1 = find_pos(min) - 1;
        int id2 = find_pos(max) + 1;

        if(id1 < 0){
            std::cout << "There's no element before min." << std::endl;
        }else{
            for (int i = 0; i < id1; i++)
            {
                current = current->next;
            }
            std::cout << "Element before min: " << current->data << std::endl;
        }

        if(id2 > size){
            std::cout << "There's no element after max." << std::endl;
        }else{
            for (int i = 0; i < id2; i++)
            {
                tmp = tmp->next;
            }
            std::cout << "Element after max: " << tmp->data << std::endl;
        }
    }
    void printMax() {
        std::cout <<"Max element is: "<< max;
        std::cout << std::endl;
    }
    void printMin() {
        std::cout <<"Min element is: "<< min;
        std::cout << std::endl;
    }
    void printSize() {
        std::cout <<"Length of array is: "<< size;
        std::cout << std::endl;
    }
};

int main() {
    ForwardList list1;
    ForwardList list2;
    list2.push_front('a');

    size_t elemCount;
    std::cout << "Enter number of elements: ";
    std::cin >> elemCount;
    char elem;
    std::cout << "Enter the elements: ";
    for (size_t i = 0; i < elemCount; i++)
    {
        std::cin >> elem;
        list1.push_front(elem);

    }
    
    list1.print();
    list1.printSize();
    list1.printMax();
    list1.printMin();
    list1.weirdFunction();
    list1.strangeFunction();

    std::cout << "Enter the element to search: ";
    std::cin >> elem;
    int pos = list1.find_pos(elem);
    if(pos == -1){
        std::cout << "There's no such element as: " << elem << '\n';
    }else{
        std::cout << "Position of element is: " << pos << '\n';
    }

    return 0;
}
