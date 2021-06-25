#include <iostream>
#include <stdint.h>
#include <bitset>
#include <string>
#include "C:/Users/hedingarcia/source/repos/headerFiles/FloatProperties.h"
using namespace std;

template <typename T>
void printBitSet(T x) {
    bitset<sizeof(T)*8> b(x); //Create the bitset depending if its 32 or 64 bits.
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

template <typename T> struct FPBits {
    typedef __llvm_libc::fputil::FloatProperties<T> FloatProp;
    typedef typename FloatProp::BitsType BitsType;
private:
    BitsType valueFP;
public:
    FPBits() {
        valueFP = 0;
    }

    FPBits(BitsType valueFP) {
        this->valueFP = valueFP;
    }

    BitsType getValue() { return valueFP; }
    void setValue(BitsType valueFP) { this->valueFP = valueFP; }

    // Invert the bit mask to clear the old value first.
    void setMantissa(BitsType mantVal) {
        valueFP &= ~(FloatProp::mantissaMask);
        valueFP |= mantVal;
    }

    BitsType getMantissa() {
        return valueFP & FloatProp::mantissaMask;
    }

    // Use the number of bits of the Mantissa for the Exponent's position.
    void setExponent(BitsType expVal) {
        valueFP &= ~(FloatProp::exponentMask);
        valueFP |= (expVal << FloatProp::mantissaWidth);
    }

    // Move to the end of the bit sequence.
    BitsType getExponent() {
        return ((valueFP  & FloatProp::exponentMask) >> FloatProp::mantissaWidth);
    }

    // Will be assigned to the highest order bit.
    void setSign(bool signVal) {
        valueFP &= ~(FloatProp::signMask);
        BitsType sign = (BitsType)signVal << (sizeof(valueFP)*8-1);
        valueFP |= sign;
    }

    // Move to the end of the bit sequence so a single value is returned.
    bool getSign() {
        return ((valueFP & FloatProp::signMask) >> (sizeof(valueFP) * 8 - 1));
    }

    // Return the float point number based on the bit representation.
    T getFPNum() {
        union {
            BitsType bitRepr;
            T FPNum;
        }FPunion;
        FPunion.bitRepr = valueFP;
        return FPunion.FPNum;
    }
    // Set the bit representation of the given float point number.
    void setFPNum(T pointNum) {
        union {
            T FPNum;
            BitsType bitRepr;
        }FPunion;
        FPunion.FPNum = pointNum;
        valueFP = FPunion.bitRepr;
    }
};

void testSinglePrecision();
void testDoublePrecision();

int main() {
    cout << "Single Precision Test: " << endl; 
    testSinglePrecision();
    cout << endl;
    cout << "======================\n";
    cout << "Double Precision Test: " << endl; 
    testDoublePrecision();
    return 0;
}

void testSinglePrecision() {
    FPBits<float> single;

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

    cout << "Getting the sign: " << single.getSign() << endl;
    cout << "Sizeof(structure): " << sizeof(single.getValue()) << " bytes" << endl;

    single.setFPNum(4.5663);
    cout << "Bit representation of a float: ";
    printBitSet(single.getValue());
    cout << "Float: " << single.getFPNum();
}

void testDoublePrecision() {
    FPBits<double> doubleFP;

    cout << "Default value: ";
    printBitSet(doubleFP.getValue());

    doubleFP.setMantissa(0x000FFFFFFFFFFFFFU);
    cout << "After setting Mantissa: ";
    printBitSet(doubleFP.getValue());

    doubleFP.setExponent(0x00000000000007FFU);
    cout << "After setting Exponent: ";
    printBitSet(doubleFP.getValue());

    cout << "Getting the Mantissa: ";
    printBitSet(doubleFP.getMantissa());

    cout << "Getting the Exponent: ";
    printBitSet(doubleFP.getExponent());

    doubleFP.setSign(1);
    cout << "After setting Sign: ";
    printBitSet(doubleFP.getValue());

    cout << "Getting the sign: " << doubleFP.getSign() << endl;
    cout << "Sizeof(structure): " << sizeof(doubleFP.getValue()) << " bytes" << endl;

    doubleFP.setFPNum(7.8671);
    cout << "Bit representation of a float: ";
    printBitSet(doubleFP.getValue());
    cout << "Float: " << doubleFP.getFPNum();
}
