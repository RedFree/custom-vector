# Custom Vector

一个用 C++ 实现的自定义 vector 容器，不使用标准库的 `std::vector`，帮助深入理解底层实现原理。

## 🌟 自定义 String 实现

本项目还包含了一个**自定义的 String 类** (`CustomString`)，用于演示在没有 `std::string` 的情况下如何实现字符串管理。

### 为什么需要自定义 String？

在学习 C++ 底层实现时，理解字符串管理的复杂性非常重要：
- 动态内存分配与释放
- 深拷贝与浅拷贝问题
- C 风格字符串与 C++ 封装的差异
- 资源管理与异常安全

### CustomString 特性

- ✅ **动态内存管理**：根据内容长度自动分配合适大小的内存
- ✅ **深拷贝支持**：拷贝构造和赋值操作进行深拷贝，避免悬空指针
- ✅ **移动语义**：支持移动构造和移动赋值，提升性能
- ✅ **C 风格兼容**：提供 `c_str()` 方法返回 C 风格字符串
- ✅ **常用操作**：支持 `size()`, `empty()`, `operator+`, `operator==` 等
- ✅ **异常安全**：在内存分配失败时正确处理异常

## 功能特性

- ✅ 基本操作：`push_back`, `pop_back`, `size`, `capacity`, `empty`
- ✅ 迭代器支持：`begin`, `end`, `rbegin`, `rend`, `const_iterator`
- ✅ 拷贝语义：拷贝构造函数和赋值运算符
- ✅ 移动语义：移动构造和移动赋值运算符
- ✅ 动态扩容：使用 2 倍增长策略自动扩容
- ✅ 异常安全：`at()` 方法进行边界检查，抛出 `std::out_of_range`
- ✅ 类型支持：支持所有基本类型（int, double, float, string 等）
- ✅ 高级功能：`reserve`, `resize`, `shrink_to_fit`, `insert`, `erase`
- ✅ 初始化列表：支持 `std::initializer_list` 构造

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

### 测试自定义 String

```bash
cd build
./vector_test
# 输出中包含 "测试 string 类型的 vector..." 和 "测试移动语义..." 部分
```

## 测试

运行程序查看完整测试输出：

```bash
./vector_test
```

测试覆盖：
- 基本操作（push_back, pop_back, size, capacity）
- 构造函数（默认、初始化列表、拷贝、赋值、移动）
- 迭代器遍历（正向、反向、const）
- 插入和删除（insert, erase）
- 容量管理（reserve, resize, shrink_to_fit）
- String 类型支持
- 移动语义测试
- 异常处理

## 代码结构

```
custom-vector/
├── vector.hpp      # Vector 类实现（核心代码）
│   - 基本操作
│   - 拷贝和移动语义
│   - 迭代器（正向、反向、const）
│   - 容量管理
│   - 插入和删除
├── custom_string.hpp # 自定义 String 类实现（可选）
│   - 动态内存管理
│   - 拷贝和移动语义
│   - C 风格字符串兼容
│   - 常用字符串操作
├── main.cpp        # 完整的测试用例
├── CMakeLists.txt  # CMake 构建配置
└── README.md       # 本文件
```

## 自定义 String 实现示例

```cpp
// 使用 Vector 存储 string（已内置支持）
Vector<std::string> vec;
vec.push_back("Hello");
vec.push_back("World");

// 如果需要自定义 String 类（参考 custom_string.hpp）
// CustomString str1 = "Hello";
// CustomString str2 = "World";
// CustomString str3 = str1 + " " + str2;
```

## 设计特点

### 1. 动态扩容策略

当空间不足时，容量翻倍（2x）：
- 扩容时分配新内存
- 复制原有元素到新内存
- 释放旧内存
- 在 amortized 时间复杂度上接近 O(1)

### 2. 异常安全

`at()` 方法进行边界检查，越界时抛出 `std::out_of_range` 异常。

### 3. RAII 原则

使用拷贝构造和赋值运算符确保资源安全，遵循 RAII 原则。

### 4. 移动语义

支持移动构造和移动赋值运算符，实现资源高效转移：
- 移动构造：直接转移资源所有权
- 移动赋值：先释放原资源，再移动新资源
- 减少不必要的拷贝，提升性能

### 5. 反向迭代器

提供反向迭代器支持：
- `rbegin()` - 指向最后一个元素
- `rend()` - 指向起始位置前一个元素
- 与 std::vector 风格一致

### 6. 简洁高效

直接使用裸指针，避免额外的间接开销，易于理解和调试。

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
|------|---------------|-------------|
| 线程安全 | ❌ 不安全 | ❌ 不安全 |
| 异常安全 | ✅ at() 检查 | ✅ at() 检查 |
| 扩容策略 | 2 倍 | 通常是 1.5x - 2x |
| 移动语义 | ✅ 支持 | ✅ 支持 |
| 完整实现 | ⚠️ 基础功能 | ✅ 完整功能 |
| 类型安全 | ✅ 模板 | ✅ 模板 |
| String 支持 | ✅ std::string | ✅ std::string |

## 自定义 String 类（可选）

项目中包含一个可选的 `CustomString` 类实现，用于演示不依赖 `std::string` 的字符串管理。完整实现可参考 `custom_string.hpp` 文件。

### CustomString 核心特性

- 动态内存管理
- 深拷贝语义
- 移动语义支持
- C 风格字符串兼容 (`c_str()`)
- 常用操作符重载 (`+`, `==`, `<`, etc.)

## 许可证

MIT License

## 作者

RedFree

## 致谢

本项目用于学习和理解 C++ STL 底层实现原理。
