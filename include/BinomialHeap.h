#ifndef HEAP_INCLUDE_BINOMIALHEAP_H
#define HEAP_INCLUDE_BINOMIALHEAP_H

#include <functional>
#include <optional>
#include <stdexcept>

template <typename T, typename Comparator = std::less<T>>
class BinomialHeap {
    struct Node {
        T key;
        int degree;
        Node* parent;
        Node* child;
        Node* sibling;

        explicit Node(T k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
    };

    Node* _head = nullptr;
    Comparator _comp;

    Node* mergeTrees(Node* b1, Node* b2) const {
        if (_comp(b2->key, b1->key)) {
            std::swap(b1, b2);
        }
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    Node* unionHeaps(Node* h1, Node* h2) const {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* newHead = nullptr;
        Node** pos = &newHead;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *pos = h1;
                h1 = h1->sibling;
            }
            else {
                *pos = h2;
                h2 = h2->sibling;
            }
            pos = &((*pos)->sibling);
        }

        *pos = h1 ? h1 : h2;
        return newHead;
    }

    void adjustHeap() {
        if (!_head) return;

        Node* prev = nullptr;
        Node* curr = _head;
        Node* next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            }
            else {
                if (_comp(curr->key, next->key)) {
                    curr->sibling = next->sibling;
                    mergeTrees(curr, next);
                }
                else {
                    if (prev) {
                        prev->sibling = next;
                    }
                    else {
                        _head = next;
                    }
                    mergeTrees(next, curr);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
    }

    Node* findNode(Node* node, const T key) const {
        if (!node) return nullptr;
        if (node->key == key) return node;

        if (auto res = findNode(node->child, key); res) return res;
        if (auto res = findNode(node->sibling, key); res) return res;

        return nullptr;
    }

public:
    BinomialHeap() = default;

    explicit BinomialHeap(const std::vector<T>& data, Comparator comp = Comparator())
        : _comp(comp) {
        for (const T& value : data) {
            insert(value);
        }
    }

    ~BinomialHeap() { clear(); }

    void clear() {
        while (_head) {
            Node* minNode = extractMinTree();
            delete minNode;
        }
    }

    bool empty() const { 
        return _head == nullptr; 
    }

    void insert(const T& key) {
        Node* node = new Node(key);
        _head = unionHeaps(_head, node);
        adjustHeap();
    }

    std::optional<T> getMin() const {
        if (!_head) return std::nullopt;

        Node* minNode = _head;
        Node* next = _head->sibling;

        while (next) {
            if (_comp(next->key, minNode->key)) {
                minNode = next;
            }
            next = next->sibling;
        }

        return minNode->key;
    }

    std::optional<T> extractMin() {
        if (!_head) return std::nullopt;

        Node* minNode = extractMinTree();
        T min = minNode->key;

        if (minNode->child) {
            Node* newHead = reverseChildList(minNode->child);
            _head = unionHeaps(_head, newHead);
        }

        delete minNode;
        adjustHeap();
        return min;
    }

    void deleteKey(const T& key) {
        if (auto node = findNode(_head, key)) {
            decreaseKey(node, std::numeric_limits<T>::min());
            extractMin();
        }
    }

    void decreaseKey(Node* node, const T& newKey) {
        if (_comp(newKey, node->key)) throw std::invalid_argument("New key is greater than old key");

        node->key = newKey;
        Node* y = node;
        Node* z = y->parent;

        while (z && _comp(y->key, z->key)) {
            std::swap(y->key, z->key);
            y = z;
            z = y->parent;
        }
    }

    void merge(BinomialHeap& other) {
        _head = unionHeaps(_head, other._head);
        other._head = nullptr;
    }

private:
    Node* extractMinTree() {
        if (!_head) return nullptr;

        Node* minNode = _head;
        Node* minPrev = nullptr;
        Node* next = _head->sibling;
        Node* prev = _head;

        while (next) {
            if (_comp(next->key, minNode->key)) {
                minNode = next;
                minPrev = prev;
            }
            prev = next;
            next = next->sibling;
        }

        if (minPrev) {
            minPrev->sibling = minNode->sibling;
        }
        else {
            _head = minNode->sibling;
        }

        return minNode;
    }

    Node* reverseChildList(Node* node) {
        Node* prev = nullptr;
        Node* curr = node;
        Node* next;

        while (curr) {
            next = curr->sibling;
            curr->sibling = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};

#endif