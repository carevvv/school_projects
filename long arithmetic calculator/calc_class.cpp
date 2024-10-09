#include <iostream>
#include <stack>
#include <deque>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include <vector>
using std::string;
using std::vector;

class Calc {
    public:
        Calc(){this->results = vector<int>();}
        Calc(const Calc & x){this->results = x.results;}
        int add(int a);
        int sub(int a);
        int mul(int a);
        int div(int a);
        int pow(int a);
        int mod(int a);
        void clear();
        int add(int a, int b) const;
        int sub(int a, int b) const;
        int mul(int a, int b) const;
        int div(int a, int b) const;
        int pow(int a, int b) const;
        int mod(int a, int b) const;
        int solva(const string &s) const; //const до типа - мы не можем изменять сам объект и можем передать ссылку на элемент, перед ссылкой - сама ссылка не изменяется, после всего - эта функция не буде тменять перменные класса(его состояние).
    private:
        vector<int> results;    
};


int main (void) {
    Calc calc;
    calc.add(3, 5);

    return 0;
}