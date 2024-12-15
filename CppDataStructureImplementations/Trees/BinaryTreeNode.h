#pragma once
#include "../Utils/TreePrinter.h"
#include <type_traits>
#include <string>

template <typename T>
concept ToWstringConvertible = requires(T t) {
    { std::to_wstring(t) } -> std::convertible_to<std::wstring>;
};

template <typename T>
class BinaryTreeNode : public PrintableNode 
{
private:
    static constexpr bool isOrCanBeConvertedToWstring = std::is_same_v<T, std::wstring> || std::is_convertible_v<T, std::wstring>;
    static constexpr bool isValidArgumentForToWstring = ToWstringConvertible<T>;

public:
    using KeyType = T;

    BinaryTreeNode(const T& _data) : data{ _data }, left{}, right{} {}

    PrintableNode* getLeft() const override 
    {
        return left.get();
    }

    PrintableNode* getRight() const override 
    {
        return right.get();
    }

    std::wstring getText() const override 
    {
        static_assert(isOrCanBeConvertedToWstring || isValidArgumentForToWstring, "Type for BinaryTreeNode cannot be converted to wstring!");

        if constexpr (isOrCanBeConvertedToWstring)
        {
            return data;
        }
        else if constexpr (isValidArgumentForToWstring)
        {
            return std::to_wstring(data);
        }
    }

    T data;
    int height{};
    std::unique_ptr<BinaryTreeNode> left;
    std::unique_ptr<BinaryTreeNode> right;
};