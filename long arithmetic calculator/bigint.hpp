#include <vector>
#include <cstdint>

using std::vector;

class BigInt {
    
private:
    vector<int32_t> digits;
    int32_t MAX_DIGITS = 5;
    int32_t BASE = INT32_MAX;
public:
    BigInt(int a = 0);
    BigInt(const BigInt &x);
    
    void complement();
    BigInt add(const BigInt &x) const;
    BigInt sub(const BigInt &x) const;
    void print_result(const BigInt &x) const;

    //void neg();
    //BigInt &mul(const BigInt &x) const;
    //BigInt &div(const BigInt &x) const;
    //BigInt &mod(const BigInt &x) const;
    //BigInt &pow(const BigInt &x) const;
};