#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data_;          // 动态数组指针
    size_t size_;      // 当前元素个数
    size_t capacity_;  // 容量

public:
    // 构造函数
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    explicit Vector(size_t n, const T& value = T())
        : size_(n), capacity_(n) {
        if (n > 0) {
            data_ = new T[n];
            for (size_t i = 0; i < n; ++i) {
                data_[i] = value;
            }
        }
    }
    Vector(std::initializer_list<T> init)
        : size_(init.size()), capacity_(init.size()) {
        if (size_ > 0) {
            data_ = new T[size_];
            std::copy(init.begin(), init.end(), data_);
        }
    }
    // 拷贝构造函数
    Vector(const Vector& other)
        : size_(other.size_), capacity_(other.capacity_) {
        if (size_ > 0) {
            data_ = new T[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }
    // 赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            if (size_ > 0) {
                data_ = new T[size_];
                std::copy(other.data_, other.data_ + size_, data_);
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }
    // 析构函数
    ~Vector() {
        delete[] data_;
    }

    // 访问元素
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    T& front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }
    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }
    T& back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }
    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }
    T* data() {
        return data_;
    }
    const T* data() const {
        return data_;
    }

    // 迭代器
    class iterator {
    private:
        T* ptr_;
    public:
        iterator(T* ptr) : ptr_(ptr) {}
        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }
        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }
        T& operator*() {
            return *ptr_;
        }
        T* operator->() {
            return ptr_;
        }
    };

    class const_iterator {
    private:
        const T* ptr_;
    public:
        const_iterator(const T* ptr) : ptr_(ptr) {}
        const_iterator& operator++() {
            ++ptr_;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr_;
            return temp;
        }
        bool operator==(const const_iterator& other) const {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const const_iterator& other) const {
            return ptr_ != other.ptr_;
        }
        const T& operator*() const {
            return *ptr_;
        }
    };

    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + size_); }
    const_iterator cbegin() const { return const_iterator(data_); }
    const_iterator cend() const { return const_iterator(data_ + size_); }

    // 容量相关
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity];
            if (size_ > 0) {
                std::copy(data_, data_ + size_, new_data);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    void shrink_to_fit() {
        if (size_ < capacity_) {
            reserve(size_);
        }
    }

    // 元素操作
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }
        data_[size_++] = value;
    }
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }
        data_[size_++] = std::move(value);
    }
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        --size_;
    }
    void clear() {
        size_ = 0;
        // 不释放内存，只重置 size
    }

    // 修改器
    void assign(size_t count, const T& value) {
        if (count > capacity_) {
            reserve(count);
        }
        for (size_t i = 0; i < count; ++i) {
            data_[i] = value;
        }
        size_ = count;
    }
    void assign(std::initializer_list<T> init) {
        if (init.size() > capacity_) {
            reserve(init.size());
        }
        std::copy(init.begin(), init.end(), data_);
        size_ = init.size();
    }

    // 插入和删除
    iterator insert(iterator pos, const T& value) {
        size_t index = pos - begin();
        if (size_ >= capacity_) {
            reserve(size_ + 1);
        }
        for (size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++size_;
        return iterator(data_ + index);
    }
    iterator erase(iterator pos) {
        if (pos == end()) {
            return pos;
        }
        for (auto i = pos; i != end() - 1; ++i) {
            *i = *(i + 1);
        }
        --size_;
        return pos;
    }
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = value;
            }
        }
        size_ = new_size;
    }
};

#endif // VECTOR_HPP
