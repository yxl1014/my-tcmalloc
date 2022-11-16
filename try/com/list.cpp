#include <cstdlib>

//
// Created by yxl on 22-11-16.
//
template<typename T>
class List {

public:
    class ListNode {
        T *data;
        ListNode *next_;
        ListNode *prev_;
    public:
        constexpr ListNode() : next_(nullptr), prev_(nullptr) {}

        // Returns true iff the list is empty after removing this
        bool remove() {
            // Copy out next/prev before doing stores, otherwise compiler assumes
            // potential aliasing and does unnecessary reloads after stores.
            ListNode *next = next_;
            ListNode *prev = prev_;
            ASSERT(prev->next_ == this);
            prev->next_ = next;
            ASSERT(next->prev_ == this);
            next->prev_ = prev;
            prev_ = nullptr;
            next_ = nullptr;
            return next == prev;
        }

        //尾插
        void prepend(ListNode *item) {
            ListNode *prev = prev_;
            item->prev_ = prev;
            item->next_ = this;
            prev->next_ = item;
            prev_ = item;
        }

        //头插
        void append(ListNode *item) {
            ListNode *next = next_;
            item->next_ = next;
            item->prev_ = this;
            next->prev_ = item;
            next_ = item;
        }

    };

    // Initialize to empty list.
    constexpr List() { head_.next_ = head_.prev_ = &head_; }

    bool empty() const { return head_.next_ == &head_; }

    // Return the length of the linked list. O(n).
    size_t length() const {
        size_t result = 0;
        for (ListNode *e = head_.next_; e != &head_; e = e->next_) {
            result++;
        }
        return result;
    }

    // Returns first element in the list. The list must not be empty.
    T *first() const {
        ASSERT(!empty());
        ASSERT(head_.next_ != nullptr);
        return static_cast<T *>(head_.next_);
    }

    // Returns last element in the list. The list must not be empty.
    T *last() const {
        ASSERT(!empty());
        ASSERT(head_.prev_ != nullptr);
        return static_cast<T *>(head_.prev_);
    }

    // Add item to the front of list.
    void prepend(T *item) { head_.append(item); }

    void append(T *item) { head_.prepend(item); }

    bool remove(T *item) {
        // must be on the list; we don't check.
        return item->remove();
    }
private:
    ListNode head_;
};