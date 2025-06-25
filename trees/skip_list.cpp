#include <iostream>
#include <random>

template <typename T>
struct Node{
		explicit Node(int levels) : level{levels}{
			next = new struct Node*[levels];
			for(int i = 0; i < levels; ++i){
				next[i] = nullptr;
			}
		}

		explicit Node(int levels, T d) : Node(levels), data{d}{
		}

		virtual ~Node(){
			delete [] next;
		}

	private:
		int level;
		struct Node* next;
		T data;
};

template <typename T>
class SkipList{
	Node<T> header;
	int listLevel; // current level of this list
	
	public:
		explicit SkipList(int maxL) : maxLevel{maxL}, header{maxLevel}, listLevel{0}{
		}

		Node<T>* getHeader() const{
			return &header;
		}
		const int maxLevel;		
		
		Node<T>* insert(T data){
			std::minstd_rand rgen;
		}

		Node<T>* find(T tdata) const{
			Node<T>* itr = &this->header;
			for(int i = listLevel; i >= 0; --i){
				while(itr->next[i] != nullptr && temp->next[i]->data < tdata)
					temp = temp->next[i];
			}
			temp = temp->next[0];
			
			if(temp != nullptr && temp->data == data) return temp;
			return nullptr;
		}
};
