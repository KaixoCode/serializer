#include "kaixo/serializer.hpp"
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <ranges>
#include <list>
#include <string>
#include <tuple>

using namespace kaixo;

struct MyTrivialStruct {
    int a;
    double b;
};

struct MyNonTrivialStruct {
    std::string str;
    std::vector<std::string> values;
};

class MyClass {
    std::string a;
    int b;

public:
    constexpr MyClass(std::string a, int b)
        :a(a), b(b) {}

    std::string& getA() { return a; }
    int& getB() { return b; }
};

template<> // Serialize specialization for class
struct serialize<MyClass> {
    template<class Type>
    static void write(basic_serializer<Type>& data, MyClass& value) {
        data << value.getA();
        data << value.getB();
    }

    template<class Type>
    static MyClass read(basic_serializer<Type>& data) {
        std::string mem1 = data.read<std::string>();
        int mem2 = data.read<int>();
        return MyClass(std::move(mem1), mem2);
    }
};

int main() {
    serializer data;
    
    {
        // Trivial type
        int val1 = 420;

        // Non-trivial type
        std::string val2 = "Hello World";

        // Contiguous trivial container
        std::array<int, 4> val3{ 1, 2, 3, 4 };

        // Non-trivial container
        std::vector<std::string> val4{
            "String 1", "More Strings", "Plenty of Strings" };

        // Trivial struct
        MyTrivialStruct val5{ 10, 2.0323 };

        // Non-trivial struct
        MyNonTrivialStruct val6{
            .str = "Test",
            .values = { "Woof", "Carrot", "Thing", "Aaa" } };

        // Non-default constructible class w/ serialize overloads
        MyClass val7{ "Private Member", 69 };

        // Tuple of classes
        std::tuple<MyClass, std::string, std::list<int>> val8{
            { "Big Very Long String", 9595 }, "More Strings!!",
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
        };

        // Array of non-default constructible classes
        std::array<MyClass, 2> val9{
            MyClass{ "In Array 1", 424 }, MyClass{ "In Array 2", 536 }
        };

        data << val1;
        data << val2;
        data << val3;
        data << val4;
        data << val5;
        data << val6;
        data << val7;
        data << val8;
        data << val9;
    }

    {
        auto v1 = data.read<int>();
        auto v2 = data.read<std::string>();
        auto v3 = data.read<std::array<int, 4>>();
        auto v4 = data.read<std::vector<std::string>>();
        auto v5 = data.read<MyTrivialStruct>();
        auto v6 = data.read<MyNonTrivialStruct>();
        auto v7 = data.read<MyClass>();
        auto v8 = data.read<std::tuple<MyClass, std::string, std::list<int>>>();
        auto v9 = data.read<std::array<MyClass, 2>>();
    }
}
