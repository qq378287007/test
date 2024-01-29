#pragma once

#include <string>

#define MAX_BI_LEN 256

#define DEC 10
#define HEX 16

#define MSBIT ((unsigned long)1 << 31)
#define OBITS (MSBIT - 1)

struct CBigInt
{
    unsigned int mSign;                 // 符号位，0表示正数，1表示负数
    unsigned int mLength;              // 大数在0x100000000进制下的数字位数
    unsigned long mValue[MAX_BI_LEN]; // 用数组记录大数在0x100000000进制下每一位的值

protected:
    void ZeroData()
    {
        mSign = 0;
        mLength = 1;
        for (int i = 0; i < mLength; i++)
            mValue[i] = 0;
    }
    void SetValue(const CBigInt &value)
    {
        mSign = value.mSign;
        mLength = value.mLength;
        for (int i = 0; i < mLength; i++)
            mValue[i] = value.mValue[i];
    }
    void SetValue(__int64 value)
    {
        mSign = 0;
        unsigned __int64 v = value;
        if (value < 0)
        {
            mSign = 1;
            v = -value;
        }

        mLength = 1;
        mValue[0] = (unsigned long)v;
        if (v > 0xffffffff)
        {
            mLength = 2;
            mValue[1] = (unsigned long)(v >> 32);
        }
    }
    int CompareNoSign(const CBigInt &value) const
    {
        if (mLength > value.mLength)
            return 1;

        if (mLength < value.mLength)
            return -1;

        for (int i = mLength - 1; i >= 0; i--)
        {
            if (mValue[i] > value.mValue[i])
                return 1;

            if (mValue[i] < value.mValue[i])
                return -1;
        }
        return 0;
    }

public:
    int ToInt()
    {
        int result = mValue[0];
        if (mSign == 1)
            result = -result;
        return result;
    }
    inline bool IsZero() const
    {
        return mLength == 1 && mValue[0] == 0;
    }
    inline bool IsEven() const
    {
        return (mValue[0] & 0x00000001) ? false : true;
    }
    CBigInt GetNegative() const
    {
        CBigInt r(*this);
        r.mSign = 1 - mSign;
        return r;
    }

public:
    CBigInt()
    {
        ZeroData();
    }
    CBigInt(const CBigInt &value)
    {
        SetValue(value);
    }
    CBigInt(__int64 value)
    {
        SetValue(value);
    }

public:
    const CBigInt &operator=(__int64 value)
    {
        SetValue(value);
        return *this;
    }
    const CBigInt &operator=(const CBigInt &value)
    {
        SetValue(value);
        return *this;
    }

public:
    bool operator<(const CBigInt &value) const
    {
        if (mSign == 0 && value.mSign == 1)
            return false;
        else if (mSign == 1 && value.mSign == 0)
            return true;
        else if (mSign == 0 && value.mSign == 0)
            return CompareNoSign(value) < 0;
        else
            return CompareNoSign(value) > 0;
    }
    bool operator<=(const CBigInt &value) const
    {
        if (mSign == 0 && value.mSign == 1)
            return false;
        else if (mSign == 1 && value.mSign == 0)
            return true;
        else if (mSign == 0 && value.mSign == 0)
            return CompareNoSign(value) <= 0;
        else
            return CompareNoSign(value) >= 0;
    }
    bool operator==(const CBigInt &value) const
    {
        return mSign == value.mSign && CompareNoSign(value) == 0;
    }
    bool operator!=(const CBigInt &value) const
    {
        return !(*this == value);
    }
    bool operator>(const CBigInt &value) const
    {
        if (mSign == 0 && value.mSign == 1)
            return true;
        else if (mSign == 1 && value.mSign == 0)
            return false;
        else if (mSign == 0 && value.mSign == 0)
            return CompareNoSign(value) > 0;
        else
            return CompareNoSign(value) < 0;
    }
    bool operator>=(const CBigInt &value) const
    {
        if (mSign == 0 && value.mSign == 1)
            return true;
        else if (mSign == 1 && value.mSign == 0)
            return false;
        else if (mSign == 0 && value.mSign == 0)
            return CompareNoSign(value) >= 0;
        else
            return CompareNoSign(value) <= 0;
    }

public:
    CBigInt operator+(const CBigInt &value) const
    {
        CBigInt r;

        if (mSign == value.mSign)
        {
            CBigInt::Add(*this, value, r);
            r.mSign = mSign;
        }
        else
        {
            if (CompareNoSign(value) >= 0)
            {
                CBigInt::Sub(*this, value, r);
                if (r.IsZero())
                    r.mSign = 0;
                else
                    r.mSign = mSign;
            }
            else
            {
                CBigInt::Sub(value, *this, r);
                r.mSign = value.mSign;
            }
        }

        return r;
    }
    const CBigInt &operator+=(const CBigInt &value)
    {
        *this = this->operator+(value);

        return *this;
    }

    CBigInt operator-(const CBigInt &value) const
    {
        CBigInt r;

        if (mSign != value.mSign)
        {
            CBigInt::Add(*this, value, r);
            r.mSign = mSign;
        }
        else
        {
            if (CompareNoSign(value) >= 0)
            {
                CBigInt::Sub(*this, value, r);
                if (r.IsZero())
                    r.mSign = 0;
                else
                    r.mSign = mSign;
            }
            else
            {
                CBigInt::Sub(value, *this, r);
                r.mSign = 1 - mSign; // 需要变号
            }
        }

        return r;
    }
    const CBigInt &operator-=(const CBigInt &value)
    {
        *this = this->operator-(value);
        return *this;
    }
    CBigInt operator*(const CBigInt &value) const
    {
        CBigInt r;
        CBigInt::Mul(*this, value, r);
        if (mSign != value.mSign)
            r.mSign = 1;
        else
            r.mSign = 0;
        return r;
    }

    const CBigInt &operator*=(const CBigInt &value)
    {
        *this = this->operator*(value);
        return *this;
    }
    CBigInt operator/(const CBigInt &value) const
    {
        CBigInt r, m;
        CBigInt::Div(*this, value, r, m);
        if (mSign != value.mSign)
            r.mSign = 1;
        else
            r.mSign = 0;

        return r;
    }
    const CBigInt &operator/=(const CBigInt &value)
    {
        *this = this->operator/(value);
        return *this;
    }

    CBigInt operator%(const CBigInt &value) const
    {
        CBigInt r, m;

        CBigInt::Div(*this, value, r, m);
        m.mSign = mSign;

        return m;
    }
    const CBigInt &operator%=(const CBigInt &value)
    {
        *this = this->operator%(value);
        return *this;
    }
    CBigInt operator^(const CBigInt &n) const
    {
        CBigInt r;
        CBigInt::Power(*this, n, r);
        if (n.IsEven())
            r.mSign = 0;
        else
            r.mSign = mSign;
        return r;
    }
    const CBigInt &operator^=(const CBigInt &n)
    {
        *this = this->operator^(n);
        return *this;
    }
    CBigInt operator<<(__int64 bits) const
    {
        CBigInt r;

        CBigInt::ShiftLeft(*this, bits, r);
        r.mSign = mSign;

        return r;
    }
    const CBigInt &operator<<=(__int64 bits)
    {
        CBigInt::ShiftLeft(*this, bits, *this);
        return *this;
    }

    CBigInt operator>>(__int64 bits) const
    {
        CBigInt r;

        CBigInt::ShiftRight(*this, bits, r);
        r.mSign = mSign;

        return r;
    }
    const CBigInt &operator>>=(__int64 bits)
    {
        CBigInt::ShiftRight(*this, bits, *this);
        return *this;
    }

public:
    bool TestBit(__int64 bits) const
    {
        __int64 wp = bits / 32;
        if (wp >= mLength)
            return false;

        __int64 bp = bits % 32;
        __int64 bitMask = 0x1 << bp;
        return mValue[wp] & bitMask != 0;
    }
    __int64 GetTotalBits() const
    {
        __int64 c = (mLength - 1) * 32;
        for (unsigned long mv = mValue[mLength - 1]; mv; mv >>= 1)
            c++;
        return c;
    }

public: // 数据转换接口
    void GetFromString(const char *str, unsigned int system = HEX);
    void PutToString(std::string &str, unsigned int system = HEX);
    void GetLong(unsigned long *values, unsigned int count)
    {
        ZeroData();
        mLength = count;
        for (unsigned int i = 0; i < count; i++)
            mValue[i] = values[i];
    }
    int PutLong(unsigned long *values, unsigned int bufLen)
    {
        if (mLength > bufLen)
            return 0;

        for (unsigned int i = 0; i < mLength; i++)
            values[i] = mValue[i];

        return mLength;
    }
    int GetFromData(const char *pData, int nBytes);               // 返回实际的位数
    int PutToData(char *pBuffer, int nBufferBytes, bool bAdjust); // 返回数据的字节数

public:
    static CBigInt GenRandomInteger(__int64 bits)
    {
        CBigInt r;

        r.mLength = (unsigned int)(bits / 32);
        for (unsigned int i = 0; i < r.mLength; i++)
            r.mValue[i] = rand() * 0x10000 + rand();

        __int64 woff = bits % 32;
        if (woff != 0)
        {
            r.mLength++;
            r.mValue[r.mLength - 1] = rand() * 0x10000 + rand();
            r.mValue[r.mLength - 1] = r.mValue[r.mLength - 1] & (0xFFFFFFFF >> (32 - woff));
        }

        return r;
    }

    static void Add(const CBigInt &value1, const CBigInt &value2, CBigInt &result)
    {
        CBigInt r = value1;

        unsigned carry = 0;
        // 先调整位数对齐
        if (r.mLength < value2.mLength)
            r.mLength = value2.mLength;
        for (unsigned int i = 0; i < r.mLength; i++)
        {
            unsigned __int64 sum = value2.mValue[i];
            sum += r.mValue[i] + carry;
            r.mValue[i] = (unsigned long)sum;
            carry = (unsigned)(sum >> 32);
        }
        // 处理最高位，如果当前最高位进位carry!=0，则需要增加大数的位数
        r.mValue[r.mLength] = carry;
        r.mLength += carry;

        result = r;
    }
    static void Sub(const CBigInt &value1, const CBigInt &value2, CBigInt &result)
    {
        CBigInt r = value1;

        unsigned int borrow = 0;
        for (unsigned int i = 0; i < r.mLength; i++)
        {
            if ((r.mValue[i] > value2.mValue[i]) || ((r.mValue[i] == value2.mValue[i]) && (borrow == 0)))
            {
                r.mValue[i] = r.mValue[i] - borrow - value2.mValue[i];
                borrow = 0;
            }
            else
            {
                unsigned __int64 num = 0x100000000 + r.mValue[i];
                r.mValue[i] = (unsigned long)(num - borrow - value2.mValue[i]);
                borrow = 1;
            }
        }
        while ((r.mValue[r.mLength - 1] == 0) && (r.mLength > 1))
            r.mLength--;

        result = r;
    }
    static void Mul(const CBigInt &value1, const CBigInt &value2, CBigInt &result)
    {
        if (value1.IsZero() || value2.IsZero())
        {
            result = 0;
            return;
        }
        unsigned __int64 carry = 0;
        CBigInt r;
        r.mLength = value1.mLength + value2.mLength - 1; // 初步估算结果的位数
        for (unsigned int i = 0; i < r.mLength; i++)
        {
            unsigned __int64 sum = carry;
            carry = 0;
            for (unsigned int j = 0; j < value2.mLength; j++)
            {
                if (((i - j) >= 0) && ((i - j) < value1.mLength))
                {
                    unsigned __int64 mul = value1.mValue[i - j];
                    mul *= value2.mValue[j];
                    carry += mul >> 32;
                    mul = mul & 0xffffffff;
                    sum += mul;
                }
            }
            carry += sum >> 32;
            r.mValue[i] = (unsigned long)sum;
        }
        if (carry != 0) // 最后仍有进位，则大数位数需要扩大
        {
            r.mLength++;
            r.mValue[r.mLength - 1] = (unsigned long)carry;
        }
        result = r;
    }
    static void Div(const CBigInt &value1, const CBigInt &value2, CBigInt &quotient, CBigInt &remainder)
    {
        CBigInt r = 0;
        CBigInt a = value1;
        while (a.CompareNoSign(value2) >= 0)
        {
            unsigned __int64 div = a.mValue[a.mLength - 1];
            unsigned __int64 num = value2.mValue[value2.mLength - 1];
            unsigned int len = a.mLength - value2.mLength;
            if ((div == num) && (len == 0))
            {
                CBigInt::Add(r, CBigInt(1), r);
                CBigInt::Sub(a, value2, a);
                break;
            }
            if ((div <= num) && (len > 0))
            {
                len--;
                div = (div << 32) + a.mValue[a.mLength - 2];
            }
            div = div / (num + 1);
            CBigInt multi = div; // 试商的结果
            if (len > 0)
            {
                multi.mLength += len;
                unsigned int i;
                for (i = multi.mLength - 1; i >= len; i--)
                    multi.mValue[i] = multi.mValue[i - len];
                for (i = 0; i < len; i++)
                    multi.mValue[i] = 0;
            }
            CBigInt tmp;
            CBigInt::Add(r, multi, r);
            CBigInt::Mul(value2, multi, tmp);
            CBigInt::Sub(a, tmp, a);
        }
        quotient = r;
        remainder = a;
    }

    static void Mod(const CBigInt &value1, const CBigInt &value2, CBigInt &result)
    {
        CBigInt a = value1;
        while (a.CompareNoSign(value2) >= 0)
        {
            unsigned __int64 div = a.mValue[a.mLength - 1];
            unsigned __int64 num = value2.mValue[value2.mLength - 1];
            unsigned int len = a.mLength - value2.mLength;
            if ((div == num) && (len == 0))
            {
                CBigInt::Sub(a, value2, a);
                break;
            }
            if ((div <= num) && (len > 0))
            {
                len--;
                div = (div << 32) + a.mValue[a.mLength - 2];
            }
            div = div / (num + 1);
            CBigInt multi = div;
            CBigInt::Mul(value2, multi, multi);
            if (len > 0)
            {
                multi.mLength += len;
                unsigned int i;
                for (i = multi.mLength - 1; i >= len; i--)
                    multi.mValue[i] = multi.mValue[i - len];
                for (i = 0; i < len; i++)
                    multi.mValue[i] = 0;
            }
            CBigInt::Sub(a, multi, a);
        }
        result = a;
    }
    static void Power(const CBigInt &value, const CBigInt &n, CBigInt &result)
    {
        result = 1;
        CBigInt t = value;

        for (__int64 i = 0; i < n.GetTotalBits(); i++)
        {
            if (n.TestBit(i))
                CBigInt::Mul(result, t, result);
            CBigInt::Mul(t, t, t);
        }
    }

    static void ShiftLeft(const CBigInt &value, __int64 bits, CBigInt &result)
    {
        __int64 wpos = bits / 32;
        __int64 woff = bits % 32;

        result = value;
        if (woff != 0)
        {
            unsigned long maskRight = 0xFFFFFFFF >> woff;
            unsigned long maskLeft = ~maskRight;
            result.mValue[result.mLength] = 0;
            result.mLength++;
            for (int i = result.mLength - 1; i >= 0; i--)
            {
                unsigned long orp = result.mValue[i] & maskRight;
                if (i > 0)
                {
                    unsigned long nlp = result.mValue[i - 1] & maskLeft;
                    result.mValue[i] = (orp << woff) | (nlp >> (32 - woff));
                }
                else
                {
                    result.mValue[i] = orp << woff;
                }
            }
            if (result.mValue[result.mLength - 1] == 0)
                result.mLength--;
        }
        if (wpos != 0)
        {
            for (int j = result.mLength - 1; j >= 0; j--)
            {
                result.mValue[j + wpos] = result.mValue[j];
            }
            for (int k = 0; k < wpos; k++)
            {
                result.mValue[k] = 0;
            }
            result.mLength += (unsigned int)wpos;
        }
    }
    static void ShiftRight(const CBigInt &value, __int64 bits, CBigInt &result)
    {
        if (bits >= value.GetTotalBits())
        {
            result = 0;
            return;
        }

        __int64 wpos = bits / 32;
        __int64 woff = bits % 32;

        result = value;
        if (woff != 0)
        {
            unsigned long maskLeft = 0xFFFFFFFF << woff;
            unsigned long maskRight = ~maskLeft;
            for (unsigned int i = 0; i < result.mLength; i++)
            {
                unsigned long olp = result.mValue[i] & maskLeft;
                if (i < (result.mLength - 1))
                {
                    unsigned long nrp = result.mValue[i + 1] & maskRight;
                    result.mValue[i] = (olp >> woff) | (nrp << (32 - woff));
                }
                else
                {
                    result.mValue[i] = olp >> woff;
                }
            }
            if (result.mValue[result.mLength - 1] == 0)
                result.mLength--;
        }
        if (wpos != 0)
        {
            if (result.mLength <= wpos)
            {
                result = 0;
            }
            else
            {
                unsigned int j;
                for (j = 0; j < (result.mLength - wpos); j++)
                {
                    result.mValue[j] = result.mValue[j + wpos];
                }
                while (j < result.mLength)
                {
                    result.mValue[j] = 0;
                    j++;
                }

                result.mLength -= (unsigned int)wpos;
            }
        }
    }
};