#include <cstring>
#include <string>

#define MAX_BI_LEN 256

#define DEC 10
#define HEX 16

#define MSBIT ((unsigned long)1 << 31)
#define OBITS (MSBIT - 1)

struct CBigInt
{
    unsigned int mSign;               // 符号位，0表示正数，1表示负数
    unsigned int mLength;             // 大数在0x100000000进制下的数字位数
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
    int ToInt() const
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
        return (mValue[0] & 0x00000001) == 0;
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
            r = CBigInt::Add(*this, value);
            r.mSign = mSign;
        }
        else
        {
            if (CompareNoSign(value) >= 0)
            {
                r = CBigInt::Sub(*this, value);
                if (r.IsZero())
                    r.mSign = 0;
                else
                    r.mSign = mSign;
            }
            else
            {
                r = CBigInt::Sub(value, *this);
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
            r = CBigInt::Add(*this, value);
            r.mSign = mSign;
        }
        else
        {
            if (CompareNoSign(value) >= 0)
            {
                r = CBigInt::Sub(*this, value);
                if (r.IsZero())
                    r.mSign = 0;
                else
                    r.mSign = mSign;
            }
            else
            {
                r = CBigInt::Sub(value, *this);
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
        CBigInt r = CBigInt::Mul(*this, value);
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
        CBigInt r = CBigInt::Power(*this, n);
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
        CBigInt r = CBigInt::ShiftLeft(*this, bits);
        r.mSign = mSign;

        return r;
    }
    const CBigInt &operator<<=(__int64 bits)
    {
        *this = CBigInt::ShiftLeft(*this, bits);
        return *this;
    }

    CBigInt operator>>(__int64 bits) const
    {
        CBigInt r = CBigInt::ShiftRight(*this, bits);
        r.mSign = mSign;

        return r;
    }
    const CBigInt &operator>>=(__int64 bits)
    {
        *this = CBigInt::ShiftRight(*this, bits);
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
        return (mValue[wp] & bitMask) != 0;
    }
    __int64 GetTotalBits() const
    {
        __int64 c = (mLength - 1) * 32;
        for (unsigned long mv = mValue[mLength - 1]; mv != 0; mv >>= 1)
            c++;
        return c;
    }

public: // 数据转换接口
    void GetFromString(const char *str, unsigned int system = HEX)
    {
        ZeroData();
        int i = 0;
        int len = (int)strlen(str), k;
        if ((len == 0) || ((len == 1) && (str[0] == '-')))
        {
            return;
        }
        if (str[0] == '-')
            i++;

        while (i < len)
        {
            *this = CBigInt::Mul(*this, system);
            if ((str[i] >= '0') && (str[i] <= '9'))
                k = str[i] - 48;
            else if ((str[i] >= 'A') && (str[i] <= 'F'))
                k = str[i] - 55;
            else if ((str[i] >= 'a') && (str[i] <= 'f'))
                k = str[i] - 87;
            else
                k = 0;
            *this = CBigInt::Add(*this, k);
            i++;
        }
        if (str[0] == '-')
            mSign = 1;
    }
    void PutToString(std::string &str, unsigned int system = HEX)
    {
        if ((mLength == 1) && (mValue[0] == 0))
        {
            str = "0";
            return;
        }
        str = "";
        const char *t = "0123456789ABCDEF";
        CBigInt value = *this;
        CBigInt sys = system;
        while (value.mValue[value.mLength - 1] > 0)
        {
            CBigInt a;
            CBigInt::Div(value, sys, value, a);
            str.insert(str.begin(), t[abs(a.ToInt())]);
        }
        if (mSign == 1)
        {
            str.insert(str.begin(), '-');
        }
    }
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
    int GetFromData(const char *pData, int nBytes) // 返回实际的位数
    {
        int i, j;
#if 0
/* remove leading zeros.. */
  while(*pData == 0) 
  {
    pData++; 
		nBytes--;
    if(nBytes == 0) 
    {
      return -1;
    } 
  }
#endif
        ZeroData();
        int m = sizeof(unsigned long); // 32 / 8;
        int n = nBytes / m;
        int r = nBytes % m;
        unsigned long wrd = 0;
        unsigned long cMask = 0x000000FF;
        unsigned long uTmp = 0;
        if (r != 0)
        {
            n++;
            for (j = 0; j < r; j++)
            {
                wrd <<= 8;
                uTmp = *pData++;
                uTmp &= cMask;
                wrd |= uTmp;
            }
        }
        mLength = n;
        if (n > MAX_BI_LEN)
        {
            return -1;
        }

        if (r != 0)
        {
            n--;
            mValue[n] = wrd;
        }
        for (i = n - 1; i >= 0; i--)
        {
            for (j = 0; j < m; j++)
            {
                wrd <<= 8;
                uTmp = *pData++;
                uTmp &= cMask;
                wrd |= uTmp;
            }
            mValue[i] = wrd;
        }

        /*  strip leading zeros from big number  */
        unsigned long s = mLength & MSBIT;
        int zm = (int)(mLength & OBITS);
        while (zm > 0 && mValue[zm - 1] == 0)
            zm--;
        mLength = zm;
        if (zm > 0)
            mLength |= s;

        return nBytes;
    }
    int PutToData(char *pBuffer, int nBufferBytes, bool bAdjust) // 返回数据的字节数
    {
        int i, j;
        /*  strip leading zeros from big number  */
        unsigned long s;
        int zm;
        s = mLength & MSBIT;
        zm = (int)(mLength & OBITS);
        while (zm > 0 && mValue[zm - 1] == 0)
            zm--;
        mLength = zm;
        if (zm > 0)
            mLength |= s;

        int m = sizeof(unsigned long); // 32 / 8;
        unsigned long wrd = 0;
        unsigned long cMask = 0x000000FF;
        unsigned long uTmp = 0;
        int start;

        int n = (int)(mLength & OBITS);
        n--;
        int len = n * m;
        wrd = mValue[n]; /* most significant */
        int r = 0;
        while (wrd != 0)
        {
            r++;
            wrd >>= 8;
            len++;
        }
        r %= m;

        if (len > nBufferBytes)
        {
            return 0;
        }

        if (bAdjust)
        {
            start = nBufferBytes - len;
            for (i = 0; i < start; i++)
                pBuffer[i] = 0;
        }
        else
            start = 0;

        if (r != 0)
        {
            wrd = mValue[n--];
            for (i = r - 1; i >= 0; i--)
            {
                pBuffer[start + i] = (char)(wrd & cMask);
                wrd >>= 8;
            }
        }

        for (i = r; i < len; i += m)
        {
            wrd = mValue[n--];
            for (j = m - 1; j >= 0; j--)
            {
                pBuffer[start + i + j] = (char)(wrd & cMask);
                wrd >>= 8;
            }
        }

        if (bAdjust)
            return nBufferBytes;
        else
            return len;
    }

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

    static CBigInt Add(const CBigInt &left, const CBigInt &right)
    {
        CBigInt r;
        unsigned carry = 0;
        unsigned __int64 sum;

        r.mLength = left.mLength;
        if (r.mLength < right.mLength)
            r.mLength = right.mLength;
        for (unsigned int i = 0; i < r.mLength; i++)
        {
            sum = carry;
            sum += left.mValue[i];
            sum += right.mValue[i];
            r.mValue[i] = (unsigned long)sum;
            carry = (unsigned)(sum >> 32);
        }
        r.mValue[r.mLength] = carry;
        r.mLength += carry;

        return r;
    }
    static CBigInt Sub(const CBigInt &left, const CBigInt &right)
    {
        CBigInt r;
        unsigned int borrow = 0;
        const unsigned __int64 num = 0x100000000;
        r.mLength = left.mLength;
        for (unsigned int i = 0; i < r.mLength; i++)
        {
            if ((left.mValue[i] > right.mValue[i]) || ((left.mValue[i] == right.mValue[i]) && (borrow == 0)))
            {
                r.mValue[i] = left.mValue[i] - right.mValue[i] - borrow;
                borrow = 0;
            }
            else
            {
                r.mValue[i] = (unsigned long)(num + left.mValue[i] - right.mValue[i] - borrow);
                borrow = 1;
            }
        }
        while ((r.mValue[r.mLength - 1] == 0) && (r.mLength > 1))
            r.mLength--;
        return r;
    }
    static CBigInt Mul(const CBigInt &left, const CBigInt &right)
    {
        CBigInt r;
        if (left.IsZero() || right.IsZero())
            return r;

        unsigned __int64 carry = 0;
        unsigned __int64 sum;
        unsigned __int64 mul;
        r.mLength = left.mLength + right.mLength - 1; // 初步估算结果的位数
        for (unsigned int i = 0; i < left.mLength; i++)
        {
            sum = carry;
            carry = 0;
            for (unsigned int j = 0; j < right.mLength; j++)
            {
                unsigned int k = i - j;
                if ((k >= 0) && (k < left.mLength))
                {
                    mul = left.mValue[k];
                    mul *= right.mValue[j];
                    carry += mul >> 32;
                    mul &= 0xffffffff;
                    sum += mul;
                }
            }
            carry += sum >> 32;
            r.mValue[i] = (unsigned long)sum;
        }
        if (carry != 0) // 最后仍有进位，则大数位数需要扩大
        {
            r.mValue[r.mLength] = (unsigned long)carry;
            r.mLength++;
        }

        return r;
    }
    static void Div(const CBigInt &left, const CBigInt &right, CBigInt &quotient, CBigInt &remainder)
    {
        CBigInt r = 0;
        CBigInt a = left;
        while (a.CompareNoSign(right) >= 0)
        {
            unsigned __int64 div = a.mValue[a.mLength - 1];
            unsigned __int64 num = right.mValue[right.mLength - 1];
            unsigned int len = a.mLength - right.mLength;
            if ((div == num) && (len == 0))
            {
                r = CBigInt::Add(r, CBigInt(1));
                a = CBigInt::Sub(a, right);
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

            r = CBigInt::Add(r, multi);
            CBigInt tmp = CBigInt::Mul(right, multi);
            a = CBigInt::Sub(a, tmp);
        }
        quotient = r;
        remainder = a;
    }

    static void Mod(const CBigInt &left, const CBigInt &right, CBigInt &result)
    {
        CBigInt a = left;
        while (a.CompareNoSign(right) >= 0)
        {
            unsigned __int64 div = a.mValue[a.mLength - 1];
            unsigned __int64 num = right.mValue[right.mLength - 1];
            unsigned int len = a.mLength - right.mLength;
            if ((div == num) && (len == 0))
            {
                a = CBigInt::Sub(a, right);
                break;
            }
            if ((div <= num) && (len > 0))
            {
                len--;
                div = (div << 32) + a.mValue[a.mLength - 2];
            }
            div = div / (num + 1);
            CBigInt multi = div;
            multi = CBigInt::Mul(right, multi);
            if (len > 0)
            {
                multi.mLength += len;
                unsigned int i;
                for (i = multi.mLength - 1; i >= len; i--)
                    multi.mValue[i] = multi.mValue[i - len];
                for (i = 0; i < len; i++)
                    multi.mValue[i] = 0;
            }
            a = CBigInt::Sub(a, multi);
        }
        result = a;
    }
    static CBigInt Power(const CBigInt &value, const CBigInt &n)
    {
        CBigInt r = 1;
        CBigInt t = value;

        for (__int64 i = 0; i < n.GetTotalBits(); i++)
        {
            if (n.TestBit(i))
                r = CBigInt::Mul(r, t);
            t = CBigInt::Mul(t, t);
        }
        return r;
    }

    static CBigInt ShiftLeft(const CBigInt &value, __int64 bits)
    {
        __int64 wpos = bits / 32;
        __int64 woff = bits % 32;

        CBigInt result = value;
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
                result.mValue[j + wpos] = result.mValue[j];
            for (int k = 0; k < wpos; k++)
                result.mValue[k] = 0;
            result.mLength += (unsigned int)wpos;
        }
        return result;
    }
    static CBigInt ShiftRight(const CBigInt &value, __int64 bits)
    {
        CBigInt r;
        if (bits >= value.GetTotalBits())
            return r;

        __int64 wpos = bits / 32;
        __int64 woff = bits % 32;

        r = value;
        if (woff != 0)
        {
            const unsigned long maskLeft = 0xFFFFFFFF << woff;
            const unsigned long maskRight = ~maskLeft;
            for (unsigned int i = 0; i < r.mLength; i++)
            {
                unsigned long olp = r.mValue[i] & maskLeft;
                if (i < (r.mLength - 1))
                {
                    unsigned long nrp = r.mValue[i + 1] & maskRight;
                    r.mValue[i] = (olp >> woff) | (nrp << (32 - woff));
                }
                else
                {
                    r.mValue[i] = olp >> woff;
                }
            }
            if (r.mValue[r.mLength - 1] == 0)
                r.mLength--;
        }
        if (wpos != 0)
        {
            if (r.mLength <= wpos)
            {
                r = 0;
            }
            else
            {
                r.mLength -= (unsigned int)wpos;
                for (unsigned int j = 0; j < r.mLength; j++)
                    r.mValue[j] = r.mValue[j + wpos];
            }
        }
        return r;
    }
};

int main()
{
    return 0;
}