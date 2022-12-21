#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <map>
#include <vector>
#include <memory>
#include <functional>


namespace data
{
	template<typename T>
	class Node
	{
	public:
		virtual ~Node() {};
		virtual bool is_leaf() const { return false; }
	};

	template<typename T>
	class Branch : public Node<T>
	{
		std::unique_ptr <Node<T>> _left_child;
		std::unique_ptr<Node<T>> _right_child;

	public:
		Branch(std::unique_ptr<Node<T>> left_child, std::unique_ptr<Node<T>> right_child) : _left_child(std::move(left_child)), _right_child(std::move(_right_child)) { }

		const Node<T>& get_right_child() const
		{
			return (*_right_child);
		}

		Node<T>& get_right_child()
		{
			return (*_right_child);
		}

		const Node<T>& get_left_child() const
		{
			return (*_left_child);
		}

		Node<T>& get_left_child()
		{
			return (*_left_child);
		}

		bool is_leaf() const override
		{
			return false;
		}
	};



	template<typename T>
	class Leaf : public Node<T>
	{
		T _value;

	public:
		Leaf(const T value) : _value(value) { }

		const T& get_value() const
		{
			return this->_value;
		}

		T& get_value()
		{
			return this->_value;
		}

		bool is_leaf() const override
		{
			return true;
		}
	};
}

#endif BINARY_TREE_H
