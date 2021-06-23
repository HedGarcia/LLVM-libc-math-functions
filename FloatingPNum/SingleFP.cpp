#include <iostream>
#include <stdint.h>
#include <bitset>
#include <string>
using namespace std;
void printBitSet(uint32_t x) {
    bitset<32> b(x);
    int jump = 1;
    for (char s : b.to_string()) {
        cout << s;
        if (jump % 4 == 0) {
            cout << " ";
        }
        jump++;
    }
    cout << endl;
}

struct singlePrecision{
private:
    uint32_t valueFP;
public:
    singlePrecision() {
        valueFP = 0x00000000U;
    }
    singlePrecision(uint32_t valueFP) {
        this->valueFP = valueFP;
    }
    void setMantissa(uint32_t mantVal) {
        valueFP |= mantVal;
    }
    uint32_t getMantissa() {
        return valueFP & 0x007FFFFFU;
    }
    // Move up so the first bit in exponent lies in the 23 bit. 
    void setExponent(uint32_t expVal) {
        valueFP |= (expVal << 23);
    }
    // Move to the end of the bit sequence.
    uint32_t getExponent() {
        uint32_t exponent = (valueFP >> 23) & 0x000000FFU;
        return exponent;
    }

    // Will be assigned to the highest order bit.
    void setSign(bool signVal) {
        uint32_t sign = (signVal) ? (1 << 31) : (0 << 31);
        valueFP |= sign;
    }
    // Move to the end of the bit sequence so a single value is returned.
    bool getSign() {
        uint32_t sign = (valueFP >> 31) & 0x00000001U;
        return sign;
    }
    
    uint32_t getValue() { return valueFP; }
};

int main() {
    singlePrecision single;
    cout << "Default value: ";
    printBitSet(single.getValue());

    single.setMantissa(0x007FFFFFU);
    cout << "After setting Mantissa: ";
    printBitSet(single.getValue());

    single.setExponent(0x000000FFU);
    cout << "After setting Exponent: ";
    printBitSet(single.getValue());

    cout << "Getting the Mantissa: ";
    printBitSet(single.getMantissa());

    cout << "Getting the Exponent: ";
    printBitSet(single.getExponent());

    single.setSign(1);
    cout << "After setting Sign: ";
    printBitSet(single.getValue());

    cout << "Getting the sign: " << single.getSign()<<endl ;
    cout << "Sizeof(structure): " << sizeof(single.getValue()) << " bytes" << endl;
    return 0;
}
