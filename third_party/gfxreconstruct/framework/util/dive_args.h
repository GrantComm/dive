#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>      // Requires C++17 or later
#include <utility>      // For std::pair, std::move
#include <stdexcept>    // For std::out_of_range

// Forward declarations
class dive_args;
class dive_args_array;

// Represents a value within dive_args. It can be a string,
// a nested dive_args object, or an array of dive_args_values.
using dive_args_value = std::variant<
    std::string,
    dive_args,
    dive_args_array
>;

// Represents an array of dive_args_values
class dive_args_array {
public:
    std::vector<dive_args_value> elements;

    dive_args_array() = default;
    dive_args_array(std::initializer_list<dive_args_value> list) : elements(list) {}

    dive_args_value& operator[](size_t index) {
        if (index >= elements.size()) {
            elements.resize(index + 1);
        }
        return elements[index];
    }

    const dive_args_value& operator[](size_t index) const {
        return elements.at(index);
    }

    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }
    auto cbegin() const { return elements.cbegin(); }
    auto cend() const { return elements.cend(); }

    size_t size() const { return elements.size(); }
    bool empty() const { return elements.empty(); }
};

// Custom structure: dive_args (now can contain nested structures)
class dive_args {
private:
    std::vector<std::string> keys_order;
    std::unordered_map<std::string, dive_args_value> data;

public:
    dive_args() = default;
    dive_args(std::initializer_list<std::pair<const std::string, dive_args_value>> list) {
        for (const auto& p : list) {
            (*this)[p.first] = p.second;
        }
    }

    // Accessor that returns a reference to a dive_args_value.
    // This allows setting strings, nested dive_args, or dive_args_arrays.
    dive_args_value& operator[](const std::string& key) {
        if (data.find(key) == data.end()) {
            keys_order.push_back(key);
        }
        return data[key];
    }

    const dive_args_value& operator[](const std::string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw std::out_of_range("Key not found in dive_args: " + key);
        }
        return it->second;
    }

    size_t size() const { return keys_order.size(); }
    bool empty() const { return keys_order.empty(); }
    bool contains(const std::string& key) const { return data.count(key) > 0; }

    // --- Iterator Support ---
    // (Similar to the previous implementation, but now iterates over
    // std::pair<const std::string, dive_args_value>)
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const std::string, dive_args_value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;

        class Proxy {
        public:
            const std::string& first;
            dive_args_value& second;

            Proxy(const std::string& k, dive_args_value& v) : first(k), second(v) {}
            Proxy* operator->() { return this; }
        };
        using reference = Proxy;

    private:
        std::vector<std::string>::iterator key_it;
        dive_args* parent_args;

    public:
        Iterator(std::vector<std::string>::iterator it, dive_args* args)
            : key_it(it), parent_args(args) {}

        Iterator& operator++() { ++key_it; return *this; }
        Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }
        reference operator*() const {
            const std::string& current_key = *key_it;
            return Proxy(current_key, parent_args->data.at(current_key));
        }
        bool operator==(const Iterator& other) const { return key_it == other.key_it; }
        bool operator!=(const Iterator& other) const { return key_it != other.key_it; }
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const std::string, const dive_args_value>;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;

        class ConstProxy {
        public:
            const std::string& first;
            const dive_args_value& second;

            ConstProxy(const std::string& k, const dive_args_value& v) : first(k), second(v) {}
            ConstProxy* operator->() { return this; }
        };
        using reference = ConstProxy;

    private:
        std::vector<std::string>::const_iterator key_it;
        const dive_args* parent_args;

    public:
        ConstIterator(std::vector<std::string>::const_iterator it, const dive_args* args)
            : key_it(it), parent_args(args) {}

        ConstIterator& operator++() { ++key_it; return *this; }
        ConstIterator operator++(int) { ConstIterator temp = *this; ++(*this); return temp; }
        reference operator*() const {
            const std::string& current_key = *key_it;
            return ConstProxy(current_key, parent_args->data.at(current_key));
        }
        bool operator==(const ConstIterator& other) const { return key_it == other.key_it; }
        bool operator!=(const ConstIterator& other) const { return key_it != other.key_it; }
    };

    Iterator begin() { return Iterator(keys_order.begin(), this); }
    Iterator end() { return Iterator(keys_order.end(), this); }
    ConstIterator begin() const { return ConstIterator(keys_order.begin(), this); }
    ConstIterator end() const { return ConstIterator(keys_order.end(), this); }
    ConstIterator cbegin() const { return ConstIterator(keys_order.cbegin(), this); }
    ConstIterator cend() const { return ConstIterator(keys_order.cend(), this); }

    // Method to get a string representation for display
    std::string display() const;
};