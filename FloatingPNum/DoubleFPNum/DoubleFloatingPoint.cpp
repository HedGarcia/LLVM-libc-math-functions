#include <iostream>
#include <stdint.h>
#include <bitset>
#include <string>
using namespace std;

void printBitSet(uint64_t x) {
    bitset<64> b(x);
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

struct doublePrecision {
    private:
        uint64_t valueFP;
    public: 
        doublePrecision() {
            valueFP = 0x0000000000000000U;
        }

        doublePrecision(uint64_t valueFP) {
            this->valueFP = valueFP;
        }

        void setMantissa(uint64_t mantVal){
            valueFP |= mantVal;
        }
        uint64_t getMantissa() {
            return valueFP & 0x000FFFFFFFFFFFFFU;
        }
        // Move the exponent up to set it in the correct bit position.
        void setExponent(uint64_t expVal){
            valueFP |= (expVal << 52);
        }
        uint64_t getExponent(){
            uint64_t exponent = (valueFP >> 52) & 0x00000000000007FFU;
            return exponent;
        }
        // Will be assigned to the highest order bit.
        // Cast to 64 bit value to avoid Arithmetic Overflow.
        void setSign(bool signVal){
            uint64_t sign = (signVal) ? ((uint64_t)1 << 63) : ((uint64_t)0 << 63); 
            valueFP |= sign;
        }
        //Move to the end of the bit sequence so a single digit is returned. 
        uint64_t getSign(){
            return (valueFP >> 63) & 0x0000000000000001U;
        }

        uint64_t getValue(){
            return valueFP;
        }

};

int main()
{
    doublePrecision doubleP;
    cout << "Default value: ";
    printBitSet(doubleP.getValue());
   
    doubleP.setMantissa(0x000FFFFFFFFFFFFFU);
    cout << "After setting Mantissa: ";
    printBitSet(doubleP.getValue());

    doubleP.setExponent(0x00000000000007FFU);
    cout << "After setting Exponent: ";
    printBitSet(doubleP.getValue());

    cout << "Getting the Mantissa: ";
    printBitSet(doubleP.getMantissa());

    cout << "Getting the Exponent: ";
    printBitSet(doubleP.getExponent());

    doubleP.setSign(1);
    cout << "After setting Sign: ";
    printBitSet(doubleP.getValue());

    cout << "Getting the sign: " << doubleP.getSign() << endl;
    cout << "Sizeof(structure): " << sizeof(doubleP.getValue()) << " bytes" << endl;
    return 0;
}