
// 自定义信号槽机制 https://blog.csdn.net/langwang122/article/details/81238423

#include <vector>

class ISloter
{
public:
    virtual ~ISloter() { };
    virtual void doFun() = 0;
};

template<typename T>
class Sloter : public ISloter
{
    typedef void(T::* CallBackFun)(void);

public:
    Sloter(T* obj, CallBackFun fun)
        : d_object(obj), m_callBackFun(fun)
    {

    }

    ~Sloter()
    {

    }

private:
    T* d_object;
    CallBackFun m_callBackFun;

public:
    void doFun()
    {
        (d_object->*m_callBackFun)();
    }
};

class Signal
{
public:
    Signal()
    {

    }

    ~Signal()
    {
        if (1 == m_slots.size())
        {
            delete m_slots[0];
        }
    }

private:
    std::vector<ISloter*> m_slots;

public:

    template<typename T>
    void regest(T* obj, void(T::* fun)(void))
    {

        if (0 == m_slots.size())
        {
            m_slots.push_back(new Sloter<T>(obj, fun));
        }
    }

    void doFun()
    {
        if (1 == m_slots.size())
        {
            m_slots[0]->doFun();
        }
    }
};

// 将信号与触发函数连起来
#define CONNECT(signalObj, signal, slotObj, slot) (signalObj)->get_##signal().regest(slotObj, slot);

// 注意这个宏会改变后面的成员的public/private/protect属性，用的时候请注意
// 定义信号
#define SIGNAL(signal) \
private: \
    Signal signal_##signal; \
public: \
    Signal& get_##signal() \
    {\
        return signal_##signal;\
    }\
private:

// 触发信号
#define EMIT(signal) signal_##signal.doFun();

class A
{
public:
    A()
    {

    }

    ~A()
    {

    }

private:
    // 定义一个信号
    SIGNAL(TestSignal)

public:
    void EmitSignal()
    {
        printf("A Signal Emit!!\r\n");

        // 触发这个信号
        EMIT(TestSignal)
    }
};

class B
{
public:
    B()
    {

    }
    ~B()
    {

    }

public:
    // 测试时绑定的槽函数
    void DoSlot()
    {
        printf("B Slot Run!!\r\n");
    }

};

int main()
{
    A a;
    B b;

    // 将信号和槽绑定
    CONNECT(&a, TestSignal, &b, &B::DoSlot);

    // 触发信号
    a.EmitSignal();

    return 0;
}
