// Basic Single Linked list
// Changed my code style to be consistent
#include <iostream>


class LinkedList {
  
  struct ListNode {
    int value;
    ListNode* next;
  };

  // Called when there are more than 1 element
  ListNode* SearchSpecificNode(ListNode* node, ListNode* node_after) {
    if (node->next == node_after)
      return node;
    else
      return SearchSpecificNode(node->next, node_after);
  }

 public:
  LinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

  ~LinkedList() {
    ListNode* iterator = head_;

    while (iterator) {
      ListNode* current = iterator;
      iterator = iterator->next;
      delete current;
    }
    std::cout << "Cleared." << std::endl;
  }

  size_t Size() {
    return this->length_;
  }

  bool IsEmpty() {
    return this->head_ == nullptr;
  }

  ListNode* SearchNode(int value) {
    ListNode* node = this->head_;

    while (node) {
      if (node->value == value) return node;
      node = node->next;
    }
    return nullptr;
  }

  void PushBack(int value) {
    ListNode* new_node = nullptr;

    if (IsEmpty()) {
      new_node = new ListNode;
      this->head_ = new_node;
    } else {
      new_node = this->tail_;
      new_node->next = new ListNode;
      new_node = new_node->next;
    }

    new_node->value = value;
    new_node->next = nullptr;
    this->tail_ = new_node;
    ++this->length_;
  }

  void PushFront(int value) {
    ListNode* new_node = new ListNode;

    if (IsEmpty())
      this->tail_ = new_node;
    
    new_node->value = value;
    new_node->next = this->head_;
    this->head_ = new_node;
    ++this->length_;
  }

  // Inserting after given value
  void Insert(int value, int value_before) {
    ListNode* node_before = SearchNode(value_before);

    if (!node_before)
      throw std::runtime_error("\nInsert: value before not found.");

    ListNode* new_node = new ListNode;
    new_node->value = value;
    new_node->next = node_before->next;
    node_before->next = new_node;
    ++this->length_;
  }

  void CheckSize() {
    if (Size() == 1) {
      ListNode* tmp = this->head_;
      this->head_ = this->tail_ = nullptr;
    } else if (!Size()) {
      throw std::out_of_range("\nPopBack: empty list.");
    }
  }

  // Could be 0(1) but need extra space..
  void PopBack() {
    CheckSize();
    ListNode* node = this->head_;
    ListNode* tmp = this->tail_;
    node = SearchSpecificNode(node, tmp);
    
    node->next = nullptr;
    this->tail_ = node;

    delete tmp;
    --this->length_;
  }

  void PopFront() {
    CheckSize();
    ListNode* temp = this->head_;
    this->head_ = this->head_->next;

    delete temp;
    --this->length_;
  }

  void Remove(int value) {
    CheckSize();
    ListNode* node_to_delete = SearchNode(value);

    if (!node_to_delete)
      throw std::runtime_error("\nRemove: value not found.");

    if (node_to_delete == this->head_) {
      PopFront();
    } else if (node_to_delete == this->tail_) {
      PopBack();
    } else {
      ListNode* node = SearchSpecificNode(this->head_, node_to_delete);
      node->next = node_to_delete->next;
      delete node_to_delete;
      --this->length_;
    }
  }

  void PrintList() {
    ListNode* it = this->head_;
    size_t i = 1;

    while (it) {
      std::cout << "[ " << i << "th, " << it->value << " ]\n";
      it = it->next;
      ++i;
    }
  }

 private:
  size_t length_;
  ListNode* head_;
  ListNode* tail_;
};


int main() {
  LinkedList list;
  
  for (int i = 1; i <= 5; ++i)
    list.PushBack(i);

  list.PushFront(8);
  list.PopFront();
  list.PopBack();
  list.Insert(8, 3);
  list.Remove(8);
  list.Remove(1);
  list.PushFront(1);
  list.Insert(5, 4);
  list.Remove(5);
  list.PrintList();
  std::cout << "Size = " << list.Size() << std::endl;

  return 0;
}