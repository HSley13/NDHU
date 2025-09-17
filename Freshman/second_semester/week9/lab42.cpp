#include <iostream>

class Gate
{
public:
    Gate *input[2];
    virtual bool output() = 0;
    void setValue(bool, int);
    void setValue(Gate *, int);
};

class TRUE : public Gate
{
public:
    virtual bool output() { return 1; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
};

class FALSE : public Gate
{
public:
    virtual bool output() { return 0; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin)
{
    if (val)
        this->input[pin] = &t;
    else
        this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate
{
public:
    virtual bool output() { return !(this->input[0]->output()); }
    void setValue(bool val, int pin = 0);
    void setValue(Gate *gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate
{
public:
    virtual bool output() { return !(this->input[0]->output()) || !(this->input[1]->output()); }
};

class NOR : public Gate
{
public:
    virtual bool output() { return !(this->input[0]->output()) && !(this->input[1]->output()); }
};

class AND : public Gate
{
private:
    Gate *component[2];

public:
    AND();
    virtual bool output();
};

AND::AND() : Gate()
{
    component[0] = new NAND;
    component[1] = new NOT;
}

bool AND::output()
{
    component[0]->input[0] = this->input[0];
    component[0]->input[1] = this->input[1];
    component[1]->input[0] = component[0];

    return component[1]->output();
}

class OR : public Gate
{
private:
    Gate *component[2];

public:
    OR();
    virtual bool output();
};

OR::OR() : Gate()
{
    component[0] = new NOT;
    component[1] = new NOR;
}

bool OR::output()
{
    component[1]->input[0] = this->input[0];
    component[1]->input[1] = this->input[1];
    component[0]->input[0] = component[1];

    return component[0]->output();
}

class XOR : public Gate
{
private:
    Gate *component[5];

public:
    XOR() : Gate() {}
    virtual bool output() { return ((this->input[0]->output() && !this->input[1]->output()) || (!this->input[0]->output() && this->input[1]->output())); }
};

class Adder
{
public:
    virtual void setValue(bool, int) = 0;
    virtual void setValue(Gate *, int) = 0;
    virtual Gate *sum() = 0;
    virtual Gate *carryOut() = 0;
};

class OneBitHalfAdder : public Adder
{
private:
    Gate *component[2];

public:
    OneBitHalfAdder();

    virtual void setValue(bool val, int pin);

    virtual void setValue(Gate *gate, int pin);

    virtual Gate *sum() { return component[0]; }

    virtual Gate *carryOut() { return component[1]; }
};

OneBitHalfAdder::OneBitHalfAdder()
{
    component[0] = new XOR;
    component[1] = new AND;
}

void OneBitHalfAdder::setValue(bool val, int pin)
{
    if (val)
    {
        component[0]->setValue(&t, pin);
        component[1]->setValue(&t, pin);
    }
    else
    {
        component[0]->setValue(&f, pin);
        component[1]->setValue(&f, pin);
    }
}

void OneBitHalfAdder::setValue(Gate *gate, int pin)
{
    component[0]->input[pin] = gate;
    component[1]->input[pin] = gate;
}

class OneBitFullAdder : public Adder
{
private:
    Adder *a[2];
    Gate *carry;

public:
    OneBitFullAdder();

    virtual void setValue(bool val, int pin);

    virtual void setValue(Gate *gate, int pin);

    virtual Gate *sum() { return a[1]->sum(); }

    virtual Gate *carryOut() { return carry; }
};

OneBitFullAdder::OneBitFullAdder()
{
    a[0] = new OneBitHalfAdder;
    a[1] = new OneBitHalfAdder;
    carry = new OR;
}

void OneBitFullAdder::setValue(bool val, int pin)
{
    if (pin < 2)
        a[0]->setValue(val, pin);
    else
        a[1]->setValue(val, 1);

    a[1]->setValue(a[0]->sum(), 0);

    carry->setValue(a[0]->carryOut(), 0);
    carry->setValue(a[1]->carryOut(), 1);
}

void OneBitFullAdder::setValue(Gate *gate, int pin)
{
    if (pin < 2)
        a[0]->setValue(gate, pin);
    else
        a[1]->setValue(gate, 1);

    a[1]->setValue(a[0]->sum(), 0);

    carry->setValue(a[0]->carryOut(), 0);
    carry->setValue(a[1]->carryOut(), 1);
}