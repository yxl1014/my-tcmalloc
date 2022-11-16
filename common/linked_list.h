//
// Created by yxl on 22-11-16.
//

#ifndef MY_TCMALLOC_LINKED_LIST_H
#define MY_TCMALLOC_LINKED_LIST_H

#include <cstdlib>
#include <cstdint>

namespace MyTCMalloc {
    namespace Common {
        void *SLL_Next(void *t) {
            return *(reinterpret_cast<void **>(t));
        }

        void SLL_SetNext(void *t, void *n) {
            *(reinterpret_cast<void **>(t)) = n;
        }

        void SLL_Push(void **list, void *element) {
            SLL_SetNext(element, *list);
            *list = element;
        }

        void *SLL_Pop(void **list) {
            void *result = *list;
            void *next = SLL_Next(*list);
            *list = next;
            return result;
        }

        class linked_list {
        private:
            void *list_;       // Linked list.
            uint32_t length_;  // Current length.

        public:
            void Init() {
                list_ = nullptr;
                length_ = 0;
            }

            // Return current length of list
            size_t length() const { return length_; }

            // Is list empty?
            bool empty() const { return list_ == nullptr; }

            void Push(void *ptr) {
                SLL_Push(&list_, ptr);
                length_++;
            }

            bool TryPop(void **ret) {
                void *obj = list_;
                if (obj == nullptr) {
                    return false;
                }

                void *next = SLL_Next(obj);
                list_ = next;
                length_--;

                *ret = obj;
                return true;
            }

            // PushBatch and PopBatch do not guarantee an ordering.
            void PushBatch(int N, void **batch) {
                if (N <= 0)
                    return;
                for (int i = 0; i < N - 1; ++i) {
                    SLL_SetNext(batch[i], batch[i + 1]);
                }
                SLL_SetNext(batch[N - 1], list_);
                list_ = batch[0];
                length_ += N;
            }

            void PopBatch(int N, void **batch) {
                void *p = list_;
                for (int i = 0; i < N; ++i) {
                    batch[i] = p;
                    p = SLL_Next(p);
                }
                list_ = p;
                if (length_ < N)
                    return;
                length_ -= N;
            }
        };

        template<typename T>
        class TList {
        private:
            class Iter;

        public:
            // The intrusive element supertype.  Use the CRTP to declare your class:
            // class MyListItems : public TList<MyListItems>::Elem { ...
            class Elem {
                friend class Iter;

                friend class TList<T>;

                Elem *next_;
                Elem *prev_;

            protected:
                constexpr Elem() : next_(nullptr), prev_(nullptr) {}

                // Returns true iff the list is empty after removing this
                bool remove() {
                    // Copy out next/prev before doing stores, otherwise compiler assumes
                    // potential aliasing and does unnecessary reloads after stores.
                    Elem *next = next_;
                    Elem *prev = prev_;
                    ASSERT(prev->next_ == this);
                    prev->next_ = next;
                    ASSERT(next->prev_ == this);
                    next->prev_ = prev;
                    return next == prev;
                }

                void prepend(Elem *item) {
                    Elem *prev = prev_;
                    item->prev_ = prev;
                    item->next_ = this;
                    prev->next_ = item;
                    prev_ = item;
                }

                void append(Elem *item) {
                    Elem *next = next_;
                    item->next_ = next;
                    item->prev_ = this;
                    next->prev_ = item;
                    next_ = item;
                }
            };

            // Initialize to empty list.
            constexpr TList() { head_.next_ = head_.prev_ = &head_; }

            bool empty() const { return head_.next_ == &head_; }

            // Return the length of the linked list. O(n).
            size_t length() const {
                size_t result = 0;
                for (Elem *e = head_.next_; e != &head_; e = e->next_) {
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

            // Support for range-based iteration over a list.
            Iter begin() const { return Iter(head_.next_); }

            Iter end() const { return Iter(const_cast<Elem *>(&head_)); }

            // Iterator pointing to a given list item.
            // REQUIRES: item is a member of the list.
            Iter at(T *item) const { return Iter(item); }

        private:
            // Support for range-based iteration over a list.
            class Iter {
                friend class TList;

                Elem *elem_;

                explicit Iter(Elem *elem) : elem_(elem) {}

            public:
                Iter &operator++() {
                    elem_ = elem_->next_;
                    return *this;
                }

                Iter &operator--() {
                    elem_ = elem_->prev_;
                    return *this;
                }

                bool operator!=(Iter other) const { return elem_ != other.elem_; }

                bool operator==(Iter other) const { return elem_ == other.elem_; }

                T *operator*() const { return static_cast<T *>(elem_); }

                T *operator->() const { return static_cast<T *>(elem_); }
            };

            friend class Iter;

            Elem head_;
        };
    }
}


#endif //MY_TCMALLOC_LINKED_LIST_H
