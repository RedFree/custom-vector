# Custom Vector

一个用 C++ 实现的自定义 vector 容器，不使用标准库的 `std::vector`，帮助深入理解底层实现原理。

## 功能特性

- ✅ **基本操作**：`push_back`, `pop_back`, `size`, `capacity`, `empty`
- ✅ **迭代器支持**：`begin`, `end`, `rbegin`, `rend`, `const_iterator`
- ✅ **拷贝语义**：拷贝构造函数和赋值运算符
- ✅ **动态扩容**：使用 2 倍增长策略自动扩容
- ✅ **异常安全**：`at()` 方法进行边界检查，抛出 `std::out_of_range`
- ✅ **类型支持**：支持所有基本类型（int, double, float, string 等）
- ✅ **高级功能**：`reserve`, `resize`, `shrink_to_fit`, `insert`, `erase`
- ✅ **初始化列表**：支持 `std::initializer_list` 构造

## 编译

### 使用 CMake（推荐）

```bash
mkdir build && cd build
cmake ..
make
./vector_test
```

### 直接使用 g++

```bash
g++ -std=c++11 main.cpp -o vector_test
./vector_test
```

### 使用 Clang

```bash
clang++ -std=c++11 main.cpp -o vector_test
./vector_test
```

## 测试

运行程序查看完整测试输出：

```bash
./vector_test
```

测试覆盖：
- 基本操作（push_back, pop_back, size, capacity）
- 构造函数（默认、初始化列表、拷贝、赋值）
- 迭代器遍历（正向、反向、const）
- 插入和删除（insert, erase）
- 容量管理（reserve, resize, shrink_to_fit）
- String 类型支持
- 异常处理

## 代码结构

```
custom-vector/
├── vector.hpp      # Vector 类实现（核心代码）
├── main.cpp        # 完整的测试用例
├── CMakeLists.txt  # CMake 构建配置
└── README.md       # 本文件
```

### vector.hpp 关键实现

```cpp
template <typename T>
class Vector {
private:
    T* data_;          // 动态数组指针
    size_t size_;      // 当前元素个数
    size_t capacity_;  // 容量

public:
    // 构造函数
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    explicit Vector(size_t n, const T& value = T());
    Vector(std::initializer_list<T> init);

    // 拷贝语义
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    // 基本操作
    void push_back(const T& value);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    // 访问元素
    T& operator[](size_t index);
    T& at(size_t index);  // 异常安全版本
    T& front();
    T& back();

    // 迭代器
    class iterator;
    iterator begin();
    iterator end();

    // 高级功能
    void reserve(size_t new_capacity);
    void resize(size_t new_size, const T& value = T());
    void shrink_to_fit();
    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);
};
```

## 设计特点

### 1. 动态扩容策略

当空间不足时，容量翻倍（2x）：
```cpp
if (size_ >= capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
}
```

这种策略在 amortized 时间复杂度上接近 O(1)，平衡了性能和内存使用。

### 2. 异常安全

`at()` 方法进行边界检查：
```cpp
T& at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Vector index out of range");
    }
    return data_[index];
}
```

### 3. RAII 原则

使用拷贝构造和赋值运算符确保资源安全：
```cpp
Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[size_];
    std::copy(other.data_, other.data_ + size_, data_);
}
```

### 4. 简洁高效

直接使用裸指针，避免额外的间接开销：
- 无虚函数
- 无模板元编程
- 无复杂的内存池
- 易于理解和调试

## 示例用法

### 基本用法

```cpp
Vector<int> vec;

vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

std::cout << vec.size() << "\n";      // 3
std::cout << vec.front() << "\n";     // 1
std::cout << vec.back() << "\n";      // 3

vec.pop_back();
std::cout << vec.size() << "\n";      // 2
```

### 迭代器

```cpp
Vector<int> vec = {1, 2, 3, 4, 5};

// 正向遍历
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// 反向遍历
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";
}
```

### 初始化列表

```cpp
Vector<int> vec1 = {1, 2, 3, 4, 5};
Vector<std::string> vec2 = {"Hello", "World", "C++"};
```

## 性能分析

### 时间复杂度

| 操作 | 时间复杂度 |
|------|-----------|
| `push_back` | 平均 O(1)，扩容时 O(n) |
| `pop_back` | O(1) |
| `at()` / `operator[]` | O(1) |
| `insert` | O(n)（需要移动元素） |
| `erase` | O(n)（需要移动元素） |
| `size` / `capacity` | O(1) |
| `reserve` | O(n)（只执行一次） |
| `resize` | O(n)（取决于新大小） |
| `shrink_to_fit` | O(n) |

### 空间复杂度

- O(n) 存储元素
- 额外 O(1) 空间用于 size 和 capacity

## 与 std::vector 的对比

| 特性 | Custom Vector | std::vector |
|------|--------------|-------------|
| 线程安全 | ❌ 不安全 | ❌ 不安全 |
| 异常安全 | ✅ at() 检查 | ✅ at() 检查 |
| 扩容策略 | 2 倍 | 通常是 1.5x - 2x |
| 移动语义 | ❌ 不支持 | ✅ 支持 |
| 完整实现 | ⚠️ 基础功能 | ✅ 完整功能 |
| 类型安全 | ✅ 模板 | ✅ 模板 |

## 许可证

MIT License

## 作者

OpenClaw Assistant

## 致谢

本项目用于学习和理解 C++ STL 底层实现原理。
