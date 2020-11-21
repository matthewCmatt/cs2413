//Author: Matthew Carroll
//Date: 11/22/2020
//Description:
// - A program to create a Direct Address Table (DAT)
// - A hash table based on mod hash function with dynamic modulus
// - Collision avoidance: separate chaining and open addressing with quadratic probing.

#include <iostream>
#include <vector>
#include <queue>

	//Take keys (ending with -1)
	//Take data (ending with *)
	//Take index of table type:
	//	0	Direct Address Table
	//	1	Hash table with separate chaining
	//	2	Hash table with open addressing + quadratic probing
	//Take modulus of hash function (integer)
	//Take sequence of search keys (ending with -1)


class Key_Value //Object holding the key/value pairs
{
public:
	int key;
	char data;
	Key_Value* next;

	Key_Value() {
		this->key = -1;
		this->data = '*';
		next = nullptr;
	}

	Key_Value(int key) {
		this->key = key;
		this->data = '&';
		next = nullptr;
	}

	Key_Value(int key, char data) {
		this->key = key;
		this->data = data;
		next = nullptr;
	}
};


int hash(int modulus, int key) {
	return key % modulus;
}

int main() {
	std::vector<Key_Value> inputs;
	int table_type;
	int modulus;					//Synonymous with hash table size.
	std::queue<int> search_keys;
	std::vector<Key_Value> hash_table;

	//[captures](params) -> ret { body }

	//INPUT KEYS
	{
		int input_key;

		std::cin >> input_key;				//Take input of keys
		while (input_key != -1) {
			Key_Value obj(input_key);		//Then, create a Key_Value with that key
			inputs.push_back(obj);	//And add it to the vector storing inputs
			std::cin >> input_key;
		}
	}

	//INPUT DATA
	{
		char input_data;

		std::cin >> input_data;				//Take input of data
		for (Key_Value &obj : inputs) {
			obj.data = input_data;			//And add it to the Key_Value in order
			std::cin >> input_data;
		}
		std::cin; //Get rid of vestigial '*' character (it isn't used to check for end of data stream).
	}

	//INPUT TABLE TYPE & MODULUS
	std::cin >> table_type;
	std::cin >> modulus;

	//INPUT SEARCH KEYS
	{
		int input_key;

		std::cin >> input_key;
		while (input_key != -1) {
			search_keys.push(input_key);
			std::cin >> input_key;
		}
	}


	switch (table_type) {
		case 0 :	//Direct address table

		//Make table
		{
			for (Key_Value obj : inputs) {
				hash_table.resize(obj.key + 1);	//Grow table size if the key is too big.
				hash_table.at(obj.key) = obj;
			}
		}

		//Search for keys and output
		{
			while (!search_keys.empty()) {
				std::cout << hash_table.at(search_keys.front()).data << ' ';
				search_keys.pop();
			}
		}

		break;

		case 1 :	//Hash table with separate chaining
			
		//Make table
		{
			int hash_value;
			hash_table.assign(modulus, Key_Value());
			Key_Value* pointer;
			for (Key_Value &obj : inputs) {
				hash_value = hash(modulus, obj.key);
				if (hash_table.at(hash_value).key == -1) {
					hash_table.at(hash_value) = obj;
				}
				else {
					pointer = &hash_table.at(hash_value);
					while (pointer->next != nullptr) {
						pointer = pointer->next;
					}
					pointer->next = &obj;
				}
			}
		}

		//Search for keys and output
		{
			int hash_value;
			int search_key;
			Key_Value* pointer;
			while (!search_keys.empty()) {
				search_key = search_keys.front();
				hash_value = hash(modulus, search_key);

				pointer = &hash_table.at(hash_value);									//Iterate through pointers unless the last in the chain or key is found.
				while ((pointer->next != nullptr) && (pointer->key != search_key)) {
					pointer = pointer->next;
				}

				if (pointer->key == search_key) {										//Print data of pointer element. It will either be '*' (if value wasn't found) or the actual data value for a given key.
					std::cout << pointer->data << ' ';
				}
				else {
					std::cout << "* ";
				}

				search_keys.pop();														//Iterate through all the search keys, doing this.
			}
		}

		break;

		case 2 :	//Hash table with open addressing + quadratic probing
			
		//Make table
		{
			int hash_value;
			int i;

			rehash:

			hash_table.assign(modulus, Key_Value());

			for (Key_Value& obj : inputs) {
				i = 0;
				do {
					hash_value = (int)(hash(modulus, obj.key) + std::pow(i, 2)) % hash_table.size();
					i++;

					if (i > hash_table.size()) {	//If we loop too many times, the hash_table is probably too small
						modulus *= 2;				//so double the modulus/table size
						std::cout << "Rehashed!";
						goto rehash;				//and redo it.
					}

				} while ((hash_table.at(hash_value).key != -1));
				
				hash_table.at(hash_value) = obj;

			}
			
			std::cout << "Done!";
		}

		//Search for keys and output
		{

		}

		break;

		default :
			std::cout << "Invalid table type.";
	}
}