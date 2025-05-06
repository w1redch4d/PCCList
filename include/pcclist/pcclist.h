#pragma once
#include <vector>
#include <any>
#include <string>
#include <iostream>

namespace PCCList {

    class List {
    private:
        std::vector<std::any> data;
    
    public:
        List();
        ~List();
    
        // variadic ctor
        template<typename T, typename... Ts>
        List(T&& first, Ts&&... rest) {
            append(std::forward<T>(first));
            (append(std::forward<Ts>(rest)), ...);
        }
    
        // append overloads
        void append(const char* s);
        void append(char* s);
    
        template<
          typename T,
          typename = std::enable_if_t<
            !std::is_same<std::decay_t<T>, const char*>::value &&
            !std::is_same<std::decay_t<T>,       char*>::value
          >
        >
        void append(T&& v) {
            data.emplace_back(std::forward<T>(v));
        }
    
        // insert overloads
        void insert(size_t idx, const char* s);
        void insert(size_t idx, char* s);
    
        template<
          typename T,
          typename = std::enable_if_t<
            !std::is_same<std::decay_t<T>, const char*>::value &&
            !std::is_same<std::decay_t<T>,       char*>::value
          >
        >
        void insert(size_t idx, T&& v) {
            if (idx > data.size()) throw std::out_of_range{"insert: index out of range"};
            data.insert(data.begin() + idx, std::forward<T>(v));
        }
    
        // other non‐template methods
        void remove(size_t idx);
        void clear() noexcept;
        size_t size() const noexcept;

        
    
        // proxy for operator[]
        struct ValueRef {
            std::any &ref;
            // conversion
            template<typename T>
            operator T() const {
                return std::any_cast<T>(ref);
            }
            // assignment
            template<typename T>
            ValueRef& operator=(T&& v) {
                ref = std::forward<T>(v);
                return *this;
            }
            // stream‐out
            friend std::ostream& operator<<(std::ostream& os, ValueRef const& vr);
            // comparisons
            template<typename T>
            friend bool operator==(ValueRef const& vr, T const& v) {
                return std::any_cast<T>(vr.ref) == v;
            }
            template<typename T>
            friend bool operator==(T const& v, ValueRef const& vr) {
                return vr == v;
            }
            template<typename T>
            friend bool operator!=(ValueRef const& vr, T const& v) {
                return !(vr == v);
            }
            template<typename T>
            friend bool operator!=(T const& v, ValueRef const& vr) {
                return !(v == vr);
            }
        };
    
        struct ConstValueRef {
            const std::any &ref;
            template<typename T>
            operator T() const {
                return std::any_cast<T>(ref);
            }
        };
    
        ValueRef       operator[](size_t idx);
        ConstValueRef  operator[](size_t idx) const;

        // explicit getters
        template<typename T>
        T get(size_t idx) const {
            if (idx >= data.size()) throw std::out_of_range{"get: index out of range"};
            return std::any_cast<T>(data[idx]);
        }
        template<typename T>
        const T* try_get(size_t idx) const noexcept {
            if (idx >= data.size()) return nullptr;
            return std::any_cast<T>(&data[idx]);
        }
    
        // iterator support
        class iterator {
            using inner = std::vector<std::any>::iterator;
            inner it;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type        = List::ValueRef;
            using difference_type   = std::ptrdiff_t;
            using pointer           = void;
            using reference         = List::ValueRef;
        
            iterator(inner w) : it(w) {}
            iterator& operator++()    { ++it; return *this; }
            iterator  operator++(int) { auto tmp=*this; ++it; return tmp; }
            bool      operator==(iterator const& o) const { return it == o.it; }
            bool      operator!=(iterator const& o) const { return it != o.it; }
            List::ValueRef operator*() { return List::ValueRef{*it}; }
        };
        
        class const_iterator {
            using inner = std::vector<std::any>::const_iterator;
            inner it;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type        = List::ConstValueRef;
            using difference_type   = std::ptrdiff_t;
            using pointer           = void;
            using reference         = List::ConstValueRef;
        
            const_iterator(inner w) : it(w) {}
            const_iterator& operator++()    { ++it; return *this; }
            const_iterator  operator++(int) { auto tmp=*this; ++it; return tmp; }
            bool            operator==(const_iterator const& o) const { return it == o.it; }
            bool            operator!=(const_iterator const& o) const { return it != o.it; }
            List::ConstValueRef operator*() const { return List::ConstValueRef{*it}; }
        };
        
        // begin/end
        iterator       begin()       { return iterator{data.begin()}; }
        iterator       end()         { return iterator{data.end()}; }
        const_iterator begin() const { return const_iterator{data.cbegin()}; }
        const_iterator end()   const { return const_iterator{data.cend()}; }
        const_iterator cbegin()const { return const_iterator{data.cbegin()}; }
        const_iterator cend()  const { return const_iterator{data.cend()}; }
    };
        
    
} // namespace PCCList
