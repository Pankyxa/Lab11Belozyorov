#pragma once

#include <iostream>
#include <random>
#include <string>


namespace HashTable
{
	bool isCountry = false;
	bool isCapital = false;
	template<typename T, typename U>
	class Node
	{
	private:
		T Country;
		U Capital;
		Node* Next;
	public:
		Node(const T& Country, const U& Capital)
			:
			Country(Country),
			Capital(Capital),
			Next(nullptr) {}

		Node() = default;
		~Node() = default;
	public:
		template<typename T, typename U>
		friend std::istream& operator>>(std::istream& stream, Node<T, U>& user);


		void setCountry(const T& Country)
		{
			this->Country = Country;
		}
		void setCapital(const U& Capital)
		{
			this->Capital = Capital;
		}
		void setNext(Node* Next)
		{
			this->Next = Next;
		}
		T getCountry() const
		{
			return Country;
		}
		U getCapital() const
		{
			return Capital;
		}
		Node* getNext() const
		{
			return Next;
		}

	};


	template<typename T, typename U, int tableSize>
	class Hashtable
	{
	private:
		Node<T, U>** ht;
	public:
		Hashtable();
		~Hashtable();
	public:
		int Hash(const T&);
		void Put(const T&, const U&);
		Node<T, U>* Get(const T&, const U&);
	};


	template<typename T, typename U>
	std::istream& operator>>(std::istream& stream, Node<T, U>& node)
	{
		std::cout << "Country: ";
		stream >> node.Country;

		std::cout << "Capital: ";
		stream >> node.Capital;

		return stream;
	}

	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::Hashtable()
	{
		ht = new Node<T, U> * [tableSize];

		for (int i = 0; i != tableSize; ++i)
		{
			ht[i] = new Node<T, U>();
			ht[i] = nullptr;
		}
	}


	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::~Hashtable()
	{
		for (int slot = 0; slot != tableSize; ++slot)
		{
			if (ht[slot] == nullptr)
			{
				continue;
			}

			Node<T, U>* tmp = ht[slot];
			Node<T, U>* prev = nullptr;

			while (tmp != nullptr)
			{
				prev = tmp;
				tmp = prev->getNext();
				delete prev;
			}

			ht[slot] = nullptr;
		}
	}


	template<typename T, typename U, int tableSize>
	int Hashtable<T, U, tableSize>::Hash(const T& Login)
	{
		int hashVal = 0;

		const char* c_string = Login.c_str();

		for (int i = 0; i != Login.size(); ++i)
		{
			hashVal += (int)c_string[i];
		}

		return hashVal % tableSize;
	}

	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Put(const T& Country, const U& Capital)
	{
		int HashVal = Hash(Country);

		Node<T, U>* tmp = ht[HashVal];
		Node<T, U>* prev = nullptr;

		while (tmp != nullptr)
		{
			prev = tmp;
			tmp = prev->getNext();
		}

		if (prev == nullptr)
		{
			tmp = new Node<T, U>(Country, Capital);
			ht[HashVal] = tmp;
		}
		else
		{
			tmp = new Node<T, U>(Country, Capital);
			prev->setNext(tmp);
		}
	}

	template<typename T, typename U, int tableSize>
	Node<T, U>* Hashtable<T, U, tableSize>::Get(const T& Country, const U& Capital)
	{
		bool isFind = false;
		int HashVal = Hash(Country);

		Node<T, U>* tmp = ht[HashVal];

		for (; tmp != nullptr; tmp = tmp->getNext())
		{
			if (tmp->getCountry() == Country)
			{
				isCountry = true;
				isFind = true;
				return tmp;
			}
			if (tmp->getCapital() == Capital)
			{
				isCapital = true;
				isFind = true;
				return tmp;
			}
		}
	}
}
