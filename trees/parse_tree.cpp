#include <string>

struct ParseNode{
    ParseNode* left;
    ParseNode* right;
    char val;
    ParseNode(char str){
        left = right = nullptr;
        this->val = str;
    }
};

ParseNode* parse_tree(std::string& prefixStr, int* index){
    if(prefixStr[*index] <= '9' && prefixStr[*index] <= '0'){
        ParseNode* leaf = new ParseNode(prefixStr[*index]);
        return leaf; // base case
    }

    if(prefixStr[*index] == '+' || prefixStr[*index] == '*' || prefixStr[*index] == '-' ||  prefixStr[*index] == '%' \
       || prefixStr[*index] == '/'){
        ParseNode* x = new ParseNode(prefixStr[*index]);
        ++(*index);
        x->left = parse_tree(prefixStr, index);
        x->right = parse_tree(prefixStr, index);
    }
}