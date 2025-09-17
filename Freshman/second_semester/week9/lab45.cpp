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

// Abstract base class for multiplexers (mux).
class Mux
{
protected:
    Gate *enable; // Gate to control the enabling of the mux.

public:
    virtual void setData(bool, int) = 0;   // Virtual function to set data input based on boolean value.
    virtual void setData(Gate *, int) = 0; // Virtual function to set data input connecting another gate.

    virtual void setSelect(bool, int) = 0;   // Virtual function to set select line based on boolean value.
    virtual void setSelect(Gate *, int) = 0; // Virtual function to set select line connecting another gate.

    virtual void setEnable(bool) = 0;   // Virtual function to enable or disable the mux.
    virtual void setEnable(Gate *) = 0; // Virtual function to enable or disable the mux using a gate.

    virtual Gate *output() = 0; // Virtual function to get the output of the mux.
};

// Derived class representing a 2-to-1 multiplexer.
class Mux2_1 : public Mux
{
private:
    Gate *component[5]; // Array to hold internal components (AND, NOT, OR, AND gates).

public:
    Mux2_1() : Mux2_1(0) {} // Constructor chaining to initialize the mux with default enable state as false.

    Mux2_1(bool val)
    {
        if (val)
            this->enable = &t; // Set enable gate to TRUE if val is true.
        else
            this->enable = &f;  // Set enable gate to FALSE if val is false.
        component[0] = new AND; // First component is an AND gate.
        component[1] = new AND; // Second component is another AND gate.
        component[2] = new NOT; // Third component is a NOT gate, used to invert the select line.
        component[3] = new OR;  // Fourth component is an OR gate, used to combine the outputs of the AND gates.
        component[4] = new AND; // Fifth component is another AND gate, used to gate the output with the enable line.
    }

    void setData(bool val, int pin) override
    {
        switch (pin)
        {
        case 0:
            component[0]->setValue(val, 0);
            break; // Set data input of first AND gate.
        case 1:
            component[1]->setValue(val, 0);
            break; // Set data input of second AND gate.
        default:;
        }
    }

    void setData(Gate *gate, int pin) override
    {
        switch (pin)
        {
        case 0:
            component[0]->setValue(gate, 0);
            break; // Connect first AND gate to another gate.
        case 1:
            component[1]->setValue(gate, 0);
            break; // Connect second AND gate to another gate.
        default:;
        }
    }

    void setEnable(bool val) override
    {
        if (val)
            this->enable = &t; // Set enable gate to TRUE.
        else
            this->enable = &f; // Set enable gate to FALSE.
    }

    void setEnable(Gate *gate) override { this->enable = gate; }

    void setSelect(bool val, int pin = 0) override
    {
        component[1]->setValue(val, 1); // Set select input of second AND gate.
        component[2]->setValue(val, 0); // Set input of NOT gate.

        component[0]->input[1] = component[2]; // Connect first AND gate's second input to output of NOT gate.
    }

    void setSelect(Gate *gate, int pin = 0) override
    {
        component[1]->setValue(gate, 1); // Connect second AND gate's select input to another gate.
        component[2]->setValue(gate, 0); // Connect NOT gate to another gate.

        component[0]->input[1] = component[2]; // Connect first AND gate's second input to output of NOT gate.
    }

    Gate *output() override
    {
        component[3]->setValue(component[0], 0); // Set first input of OR gate to output of first AND gate.
        component[3]->setValue(component[1], 1); // Set second input of OR gate to output of second AND gate.
        component[4]->setValue(this->enable, 0); // Set first input of final AND gate to enable gate.
        component[4]->setValue(component[3], 1); // Set second input of final AND gate to output of OR gate.

        return component[4]; // Return output of final AND gate, which is the output of the mux.
    }
};

// Derived class representing a 4-to-1 multiplexer using three 2-to-1 multiplexers.
class Mux4_1 : public Mux
{
private:
    Mux *mux2_1[3]; // Array to hold three 2-to-1 muxes.

public:
    Mux4_1() {}

    Mux4_1(bool val)
    {
        mux2_1[0] = new Mux2_1(val); // First 2-to-1 mux.
        mux2_1[1] = new Mux2_1(val); // Second 2-to-1 mux.
        mux2_1[2] = new Mux2_1(val); // Third 2-to-1 mux, used to select between outputs of the first two muxes.
    }

    void setData(bool val, int pin) override
    {
        if (pin < 2)
            mux2_1[0]->setData(val, pin); // Set data inputs of first 2-to-1 mux.
        else
            mux2_1[1]->setData(val, pin - 2); // Set data inputs of second 2-to-1 mux.
    }

    void setData(Gate *gate, int pin) override
    {
        if (pin < 2)
            mux2_1[0]->setData(gate, pin); // Connect data inputs of first 2-to-1 mux to another gate.
        else
            mux2_1[1]->setData(gate, pin - 2); // Connect data inputs of second 2-to-1 mux to another gate.
    }

    void setEnable(bool val) override
    {
        for (int i = 0; i < 3; i++)
            mux2_1[i]->setEnable(val); // Set enable state for all three 2-to-1 muxes.
    }

    void setEnable(Gate *gate) override
    {
        for (int i = 0; i < 3; i++)
            mux2_1[i]->setEnable(gate); // Connect enable gates of all three 2-to-1 muxes to another gate.
    }

    void setSelect(bool val, int pin) override
    {
        if (pin == 0)
        {
            mux2_1[0]->setSelect(val, 0); // Set select line of first 2-to-1 mux.
            mux2_1[1]->setSelect(val, 0); // Set select line of second 2-to-1 mux.
        }
        else
            mux2_1[2]->setSelect(val, 0); // Set select line of third 2-to-1 mux.
    }

    void setSelect(Gate *gate, int pin) override
    {
        if (pin == 0)
        {
            mux2_1[0]->setSelect(gate, 0); // Connect select line of first 2-to-1 mux to another gate.
            mux2_1[1]->setSelect(gate, 0); // Connect select line of second 2-to-1 mux to another gate.
        }
        else
            mux2_1[2]->setSelect(gate, 0); // Connect select line of third 2-to-1 mux to another gate.
    }

    Gate *output() override
    {
        mux2_1[2]->setData(mux2_1[0]->output(), 0); // Set first data input of third 2-to-1 mux to output of first mux.
        mux2_1[2]->setData(mux2_1[1]->output(), 1); // Set second data input of third 2-to-1 mux to output of second mux.

        return mux2_1[2]->output(); // Return output of third 2-to-1 mux, which is the output of the 4-to-1 mux.
    }
};
