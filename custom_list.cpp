#include <iostream>
#include <string>

template <typename T, typename Alloc = std::allocator<T>> class MyList {

public:
  struct Node {
    T data;
    Node *next;
  };

  MyList(Alloc allocator = Alloc());
  ~MyList();

  void push_back(const T &data);

  template <typename U, typename B>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const MyList<U, B> &list);

  class Iterator {
  public:
    Iterator(MyList *list) : parent(list), ptr(list->head_) {}
    void operator++() {
      if (ptr != nullptr)
        ptr = ptr->next;
    }
    typename MyList::Node &operator*() { return *ptr; }
    typename MyList::Node *operator->() { return ptr; }
    bool IsEnd() const { return ptr == nullptr; }

  private:
    MyList *parent;
    typename MyList::Node *ptr;
  };

  friend class Iterator;

private:
  void Destroy(Node *node);

  Node *head_;
  Node *tail;

  Alloc allocData_;

  using AllocatorTraits = std::allocator_traits<Alloc>;
  using RebindAllocNode = typename AllocatorTraits::template rebind_alloc<Node>;
  RebindAllocNode allocNode_;
};

template <typename T, typename A>
MyList<T, A>::MyList(A allocator)
    : head_(nullptr), tail(nullptr), allocData_(allocator) {}

template <typename T, typename A> MyList<T, A>::~MyList() {
  auto ptr = head_;
  while (ptr != nullptr) {
    auto next = ptr->next;
    Destroy(ptr);
    ptr = next;
  }
}

template <typename T, typename A> void MyList<T, A>::Destroy(Node *node) {
  allocData_.destroy(node);
  allocNode_.deallocate(node, 1);
}

template <typename T, typename A> void MyList<T, A>::push_back(const T &data) {
  Node *node = allocNode_.allocate(1);
  allocData_.construct(node, Node{data, nullptr});
  if (tail != nullptr)
    tail->next = node;
  tail = node;
  if (head_ == nullptr)
    head_ = node;
}

template <typename T, typename A>
std::ostream &operator<<(std::ostream &stream, const MyList<T, A> &list) {
  for (typename MyList<T, A>::Node *ptr = list.head_; ptr != nullptr;
       ptr = ptr->next)
    stream << ptr->data << std::endl;

  return stream;
}