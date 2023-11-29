#include<iostream>

class Base{
    public:
        Base(){

        }
        virtual ~Base(){

        }
        virtual void print(){
            std::cout << "I am Base\n";
        }

    private:
        int baseDate;

};

class Derived : public Base{
    public:
        Derived(char c){
            derivedData = c;
        }
        virtual ~Derived(){

        }
        virtual void print() override {
            std::cout << "I am Derived\n";
        }

    private:
        char derivedData;
};

class StandAlone{
    public:
        int random;
        char me;
        StandAlone(){
            random = 0;
        }
        void print(){
            std::cout << "I am Derived\n";
        }
    private:
        //
};

int main(){
    Base* bObj;
    Derived dObj{'d'};
    StandAlone alone{};
    bObj = &dObj;
    bObj->print();
}