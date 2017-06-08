#ifndef _MYCLASS_H
#define _MYCLASS_H

class MyClass1
{
 public:
    int value;
    MyClass1(int value_) : value(value_) {}
    int big_than_ten(void)
    {
        if (this->value > 10)
            return 1;
        return 0;
    }
};

#endif
