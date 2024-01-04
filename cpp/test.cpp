#include <iostream>
#include <memory>
using namespace std;

class FighterMemento // 玩家主角相关的备忘录类
{
    friend class Fighter; // 友元类Fighter可以访问本类的私有成员函数

    // 玩家主角类中要保存起来的数据，就放到这里来
    int m_life;   // 生命值
    int m_magic;  // 魔法值
    int m_attack; // 攻击力

    // public:
private: // 构造函数，用private修饰以防止在外部被随意创建，error
    FighterMemento(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack) {}

    void say()
    {
        cout << "ok\n";
    }
};

class Fighter
{
    int m_life;   // 生命值
    int m_magic;  // 魔法值
    int m_attack; // 攻击力
public:
    void tt()
    {
        FighterMemento a(1, 2, 3);
        a.say();
    }
    shared_ptr<FighterMemento> createMomento() const
    {
        FighterMemento a(1, 2, 3);

        shared_ptr<FighterMemento> bb(new FighterMemento(1, 2, 3));
        return bb;
        // make_shared<FighterMemento>(m_life, m_magic, m_attack);
    }
};

int main()
{
    Fighter b;
    b.tt();
    cout << "Over!\n";
    return 0;
}