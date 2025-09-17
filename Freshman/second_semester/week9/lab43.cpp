#include <iostream>
using namespace std;

class Gate
{
public:
    Gate *input[2] = {nullptr, nullptr};
    virtual bool output() = 0;
    virtual void setValue(Gate *gate, int pin) { input[pin] = gate; }
    virtual void setValue(bool val, int pin);
};

class TRUE : public Gate
{
public:
    bool output() override { return true; }
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

class FALSE : public Gate
{
public:
    bool output() override { return false; }
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin)
{
    input[pin] = val ? static_cast<Gate *>(&t) : static_cast<Gate *>(&f);
}

class NOT : public Gate
{
public:
    bool output() override { return !input[0]->output(); }
    void setValue(bool val, int pin = 0) override
    {
        input[pin] = val ? static_cast<Gate *>(&t) : static_cast<Gate *>(&f);
    }
    void setValue(Gate *gate, int pin = 0) override
    {
        input[pin] = gate;
    }
};

class NAND : public Gate
{
public:
    bool output() override { return !(input[0]->output() && input[1]->output()); }
};

class NOR : public Gate
{
public:
    bool output() override { return !(input[0]->output() || input[1]->output()); }
};

class AND : public Gate
{
public:
    AND()
    {
        component[0] = new NOT;
        component[1] = new NAND;
    }
    bool output() override
    {
        component[1]->input[0] = input[0];
        component[1]->input[1] = input[1];
        component[0]->input[0] = component[1];
        return component[0]->output();
    }

private:
    Gate *component[2];
};

class OR : public Gate
{
public:
    OR()
    {
        component[0] = new NOT;
        component[1] = new NOR;
    }
    bool output() override
    {
        component[1]->input[0] = input[0];
        component[1]->input[1] = input[1];
        component[0]->input[0] = component[1];
        return component[0]->output();
    }

private:
    Gate *component[2];
};

class XOR : public Gate
{
private:
    Gate *component[5];

public:
    XOR()
    {
        component[0] = new NOT;
        component[1] = new NOT;
        component[2] = new AND;
        component[3] = new AND;
        component[4] = new OR;
    }

    bool output() override
    {
        component[0]->input[0] = input[0]; // !a
        component[1]->input[0] = input[1]; // !b
        component[2]->input[0] = input[0]; // a && !b
        component[2]->input[1] = component[1];
        component[3]->input[0] = input[1]; // !a && b
        component[3]->input[1] = component[0];
        component[4]->input[0] = component[2]; // (a && !b) || (!a && b)
        component[4]->input[1] = component[3];
        return component[4]->output();
    }
};

class Decoder
{
public:
    virtual void setValue(bool, int) = 0;
    virtual void setValue(Gate *, int) = 0;
    virtual void setEnable(bool) = 0;
    virtual void setEnable(Gate *) = 0;
    virtual int output() = 0;
    virtual Gate *operator[](int) = 0;

protected:
    Gate *enable;
};

class Decoder2_4 : public Decoder
{
private:
    Gate *component[6];
    Gate *enables[4];

    void _out()
    {
        component[2]->input[0] = component[0];
        component[2]->input[1] = component[1];
        component[3]->input[0] = component[0]->input[0];
        component[3]->input[1] = component[1];
        component[4]->input[0] = component[0];
        component[4]->input[1] = component[1]->input[0];
        component[5]->input[0] = component[0]->input[0];
        component[5]->input[1] = component[1]->input[0];

        for (int i = 0; i < 4; ++i)
        {
            enables[i]->input[0] = enable;
            enables[i]->input[1] = component[i + 2];
        }
    }

public:
    Decoder2_4(bool val = false)
    {
        enable = val ? static_cast<Gate *>(&t) : static_cast<Gate *>(&f);
        for (int i = 0; i < 2; ++i)
            component[i] = new NOT;
        for (int i = 2; i < 6; ++i)
            component[i] = new AND;
        for (int i = 0; i < 4; ++i)
            enables[i] = new AND;
    }

    void setEnable(bool val) override { enable = val ? static_cast<Gate *>(&t) : static_cast<Gate *>(&f); }

    void setEnable(Gate *gate) override { enable = gate; }

    void setValue(Gate *gate, int i) override { component[i % 2]->input[0] = gate; }

    void setValue(bool val, int i) override { component[i % 2]->input[0] = val ? static_cast<Gate *>(&t) : static_cast<Gate *>(&f); }

    Gate *operator[](int n) override
    {
        _out();
        return enables[n];
    }

    friend ostream &operator<<(ostream &out, Decoder2_4 &dec)
    {
        for (int i = 3; i >= 0; --i)
            out << dec[i]->output() << " ";

        return out;
    }

    int output() override
    {
        for (int i = 0; i < 4; ++i)
            if (enables[i]->output())
                return i;

        return -1;
    }
};

class Decoder4_16 : public Decoder
{
private:
    Decoder2_4 *dec2_4[5];

public:
    Decoder4_16(bool val = false)
    {
        for (int i = 0; i < 5; i++)
            dec2_4[i] = new Decoder2_4(val);
    }

    void setEnable(bool val) override { dec2_4[0]->setEnable(val); }

    void setEnable(Gate *gate) override { dec2_4[0]->setEnable(gate); }

    void setValue(bool val, int pin) override
    {
        if (pin < 2)
            for (int i = 1; i < 5; i++)
                dec2_4[i]->setValue(val, pin);
        else
        {
            dec2_4[0]->setValue(val, pin - 2);

            for (int i = 1; i < 5; i++)
                dec2_4[i]->setEnable((*dec2_4[0])[i - 1]);
        }
    }

    void setValue(Gate *gate, int pin) override
    {
        if (pin < 2)
            for (int i = 1; i < 5; i++)
                dec2_4[i]->setValue(gate, pin);
        else
        {
            dec2_4[0]->setValue(gate, pin - 2);

            for (int i = 1; i < 5; i++)
                dec2_4[i]->setEnable((*dec2_4[0])[i - 1]);
        }
    }

    Gate *operator[](int n) override { return (*dec2_4[(n / 4) + 1])[n % 4]; }

    friend ostream &operator<<(ostream &out, Decoder4_16 &dec)
    {
        for (int i = 15; i >= 0; --i)
            out << dec[i]->output() << " ";

        return out;
    }

    int output() override
    {
        for (int i = 0; i < 16; i++)
            if ((*this)[i]->output())
                return i;

        return -1;
    }
};