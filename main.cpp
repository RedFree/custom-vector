#include <iostream>
#include <string>
#include "vector.hpp"

void print_separator() {
    std::cout << "---------------------------\n";
}

void test_basic_operations() {
    std::cout << "测试基本操作...\n";

    Vector<int> vec;
    std::cout << "创建空 vector\n";

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    std::cout << "push_back 10, 20, 30\n";

    std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";
    std::cout << "元素: ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    std::cout << "front: " << vec.front() << ", back: " << vec.back() << "\n";

    vec.pop_back();
    std::cout << "pop_back 后 size: " << vec.size() << "\n";

    print_separator();
}

void test_constructors() {
    std::cout << "测试构造函数...\n";

    Vector<int> vec1(5, 100);  // 5个100
    std::cout << "vec1(5, 100): ";
    for (int i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << "\n";

    Vector<int> vec2 = {1, 2, 3, 4, 5};  // 初始化列表
    std::cout << "vec2 = {1, 2, 3, 4, 5}: ";
    for (int i = 0; i < vec2.size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << "\n";

    Vector<int> vec3(vec2);  // 拷贝构造
    std::cout << "vec3 = vec2 (拷贝): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    Vector<int> vec4;
    vec4 = vec1;  // 赋值
    std::cout << "vec4 = vec1 (赋值): ";
    for (int i = 0; i < vec4.size(); ++i) {
        std::cout << vec4[i] << " ";
    }
    std::cout << "\n";

    print_separator();
}

void test_iterators() {
    std::cout << "测试迭代器...\n";

    Vector<int> vec = {10, 20, 30, 40, 50};

    std::cout << "正向迭代: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "反向迭代: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "const 迭代器: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    print_separator();
}

void test_insert_erase() {
    std::cout << "测试 insert 和 erase...\n";

    Vector<int> vec = {10, 20, 40, 50};

    std::cout << "原始: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << "\n";

    auto it = vec.begin();
    ++it;  // 指向20
    vec.insert(it, 30);
    std::cout << "insert 30 到 index 1: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << "\n";

    it = vec.begin();
    ++it;  // 指向20
    ++it;  // 指向30
    vec.erase(it);
    std::cout << "erase index 2: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << "\n";

    print_separator();
}

void test_reserve_resize() {
    std::cout << "测试 reserve 和 resize...\n";

    Vector<int> vec;

    vec.reserve(100);
    std::cout << "reserve(100), size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    std::cout << "push_back 10 个元素后, size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    vec.resize(20, 999);
    std::cout << "resize(20, 999): ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.resize(5);
    std::cout << "resize(5): ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.shrink_to_fit();
    std::cout << "shrink_to_fit, capacity: " << vec.capacity() << "\n";

    print_separator();
}

void test_string_vector() {
    std::cout << "测试 string 类型的 vector...\n";

    Vector<std::string> vec;

    vec.push_back("Hello");
    vec.push_back("World");
    vec.push_back("C++");

    std::cout << "元素: ";
    for (const auto& s : vec) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    print_separator();
}

void test_out_of_range() {
    std::cout << "测试 out_of_range 异常...\n";

    Vector<int> vec = {1, 2, 3};

    try {
        std::cout << "访问 index 5: " << vec[5] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }

    try {
        vec.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }

    try {
        vec.back();
    } catch (const std::out_of_range& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }

    print_separator();
}

int main() {
    std::cout << "=== 自定义 Vector 测试 ===\n\n";

    test_basic_operations();
    test_constructors();
    test_iterators();
    test_insert_erase();
    test_reserve_resize();
    test_string_vector();
    test_out_of_range();

    std::cout << "所有测试完成!\n";

    return 0;
}
