#include "../include/pcclist/pcclist.h"

namespace PCCList {

    std::ostream&
    operator<<(std::ostream& os, List::ValueRef const& vr) {
        auto const& t = vr.ref.type();
        if      (t == typeid(int))         os << std::any_cast<int>(vr.ref);
        else if (t == typeid(double))      os << std::any_cast<double>(vr.ref);
        else if (t == typeid(std::string)) os << std::any_cast<std::string>(vr.ref);
        else                                os << "[unprintable: " << t.name() << "]";
        return os;
    }


    List::List() = default;
    List::~List() = default;

    void List::append(const char* s) {
        data.emplace_back(std::string(s));
    }
    void List::append(char* s) {
        data.emplace_back(std::string(s));
    }

    void List::insert(size_t idx, const char* s) {
        if (idx > data.size()) throw std::out_of_range{"insert: index out of range"};
        data.insert(data.begin() + idx, std::string(s));
    }
    void List::insert(size_t idx, char* s) {
        if (idx > data.size()) throw std::out_of_range{"insert: index out of range"};
        data.insert(data.begin() + idx, std::string(s));
    }

    void List::remove(size_t idx) {
        if (idx >= data.size()) throw std::out_of_range{"remove: index out of range"};
        data.erase(data.begin() + idx);
    }
    void List::clear() noexcept {
        data.clear();
    }
    size_t List::size() const noexcept {
        return data.size();
    }
    

    List::ValueRef List::operator[](size_t idx) {
        if (idx >= data.size()) throw std::out_of_range{"operator[]: index out of range"};
        return ValueRef{data[idx]};
    }
    List::ConstValueRef List::operator[](size_t idx) const {
        if (idx >= data.size()) throw std::out_of_range{"operator[] const: index out of range"};
        return ConstValueRef{data[idx]};
    }
    
} // namespace PCCList