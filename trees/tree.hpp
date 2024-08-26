// template<typename type_t>
struct Tree{
    Tree* left;
    Tree* right;
    int val;
};

inline void visit(Tree* node){
    std::cout << node->val << "\n";
}