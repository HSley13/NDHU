#include <iostream>  // Include the iostream library to enable input/output operations
using namespace std; // Use the standard namespace

// Define an abstract base class Gate with pure virtual functions
class Gate
{
public:
    // Two input pointers of type Gate
    Gate *input[2] = {nullptr, nullptr};
    // A pure virtual function output() which needs to be overridden by derived classes
    virtual bool output() = 0;
    // Two functions setValue() to set the input gates or boolean values
    virtual void setValue(Gate *gate, int pin);
    virtual void setValue(bool, int);
};

// Define a class TRUE which inherits from Gate and represents a logical true gate
class TRUE : public Gate
{
public:
    // The output function always returns true
    bool output() override { return true; }
    // The setValue() functions do nothing in this class
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

// Define a class FALSE which inherits from Gate and represents a logical false gate
class FALSE : public Gate
{
public:
    // The output function always returns false
    bool output() override { return false; }
    // The setValue() functions do nothing in this class
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

// Create instances of TRUE and FALSE classes
TRUE t;
FALSE f;

// Implement the setValue() function for Gate class
void Gate::setValue(bool val, int pin)
{
    if (val)
        this->input[pin] = &t; // If the value is true, set the input to the true gate
    else
        this->input[pin] = &f; // If the value is false, set the input to the false gate
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; } // Set the input to the given gate

// Define a class NOT which inherits from Gate and represents a logical not gate
class NOT : public Gate
{
public:
    // The output function returns the negation of the input
    bool output() override { return !(this->input[0]->output()); }
    // The setValue() functions set the input gate or value
    void setValue(bool val, int pin = 0) override
    {
        if (val)
            this->input[0] = &t;
        else
            this->input[0] = &f;
    }
    void setValue(Gate *gate, int pin = 0) override { this->input[0] = gate; }
};

// Define classes NAND, NOR, AND, OR which inherit from Gate and represent the corresponding logical gates
class NAND : public Gate
{
public:
    bool output() override { return !(this->input[0]->output() && this->input[1]->output()); }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override
    {
        if (val)
            this->input[pin] = &t;
        else
            this->input[pin] = &f;
    }
};

class NOR : public Gate
{
public:
    bool output() override { return !(this->input[0]->output() || this->input[1]->output()); }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override
    {
        if (val)
            this->input[pin] = &t;
        else
            this->input[pin] = &f;
    }
};

class AND : public Gate
{
public:
    AND()
    {
        // Create instances of NAND and NOT gates
        component[0] = new NAND();
        component[1] = new NOT();
    }
    bool output() override
    {
        // Set the inputs of the NAND and NOT gates and return the output of the NOT gate
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];
        component[1]->input[0] = component[0];
        return component[1]->output();
    }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override
    {
        if (val)
            this->input[pin] = &t;
        else
            this->input[pin] = &f;
    }

private:
    // An array of Gate pointers to hold the components of the AND gate
    Gate *component[2];
};

class OR : public Gate
{
public:
    OR()
    {
        // Create instances of NOR and NOT gates
        component[0] = new NOR();
        component[1] = new NOT();
    }
    bool output() override
    {
        // Set the inputs of the NOR and NOT gates and return the output of the NOT gate
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];
        component[1]->input[0] = component[0];
        return component[1]->output();
    }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override
    {
        if (val)
            this->input[pin] = &t;
        else
            this->input[pin] = &f;
    }

private:
    // An array of Gate pointers to hold the components of the OR gate
    Gate *component[2];
};

// Define an abstract base class Mux with pure virtual functions
class Mux
{
public:
    // Pure virtual functions to set data, enable, and select inputs
    virtual void setData(bool, int) = 0;
    virtual void setData(Gate *, int) = 0;
    virtual void setEnable(bool) = 0;
    virtual void setEnable(Gate *) = 0;
    virtual void setSelect(bool, int) = 0;
    virtual void setSelect(Gate *, int) = 0;
    // A pure virtual function to get the output
    virtual Gate *output() = 0;

protected:
    // A pointer to the enable input gate
    Gate *enable;
};

// Define a class Mux2_1 which inherits from Mux and represents a 2:1 multiplexer
class Mux2_1 : public Mux
{
public:
    // Default constructor and constructor with enable input value
    Mux2_1() : Mux2_1(0) {}
    Mux2_1(bool val)
    {
        if (val)
            this->enable = &t; // Set the enable input to the true gate if the value is true
        else
            this->enable = &f; // Set the enable input to the false gate if the value is false
        // Create instances of AND, AND, NOT, and OR gates
        component[0] = new AND;
        component[1] = new AND;
        component[2] = new NOT;
        component[3] = new OR;
        component[4] = new AND;
    }
    // Set the data inputs of the multiplexer
    void setData(bool val, int pin) override
    {
        switch (pin)
        {
        case 0:
            component[0]->setValue(val, 0);
            break; // Set the data input 0 to the given value
        case 1:
            component[1]->setValue(val, 0);
            break; // Set the data input 1 to the given value
        default:;
        }
    }
    void setData(Gate *gate, int pin) override
    {
        switch (pin)
        {
        case 0:
            component[0]->setValue(gate, 0);
            break; // Set the data input 0 to the given gate
        case 1:
            component[1]->setValue(gate, 0);
            break; // Set the data input 1 to the given gate
        default:;
        }
    }
    // Set the enable input of the multiplexer
    void setEnable(bool val) override
    {
        if (val)
            this->enable = &t; // Set the enable input to the true gate if the value is true
        else
            this->enable = &f; // Set the enable input to the false gate if thevalue is false
    }
    void setEnable(Gate *gate) override
    {
        this->enable = gate; // Set the enable input to the given gate
    }
    // Set the select input of the multiplexer
    void setSelect(bool val, int pin = 0) override
    {
        component[1]->setValue(val, 1);        // Set the select input of the second AND gate to the given value
        component[2]->setValue(val, 0);        // Set the select input of the NOT gate to the given value
        component[0]->input[1] = component[2]; // Connect the output of the NOT gate to the second input of the first AND gate
    }
    void setSelect(Gate *gate, int pin = 0) override
    {
        component[1]->setValue(gate, 1);       // Set the select input of the second AND gate to the given gate
        component[2]->setValue(gate, 0);       // Set the select input of the NOT gate to the given gate
        component[0]->input[1] = component[2]; // Connect the output of the NOT gate to the second input of the first AND gate
    }
    // Get the output of the multiplexer
    Gate *output() override
    {
        component[3]->setValue(component[0], 0); // Set the first input of the OR gate to the output of the first AND gate
        component[3]->setValue(component[1], 1); // Set the second input of the OR gate to the output of the second AND gate
        component[4]->setValue(this->enable, 0); // Set the input of the final AND gate to the enable input
        component[4]->setValue(component[3], 1); // Set the second input of the final AND gate to the output of the OR gate
        return component[4];                     // Return the output of the final AND gate
    }

private:
    // An array of Gate pointers to hold the components of the multiplexer
    Gate *component[5];
};

// Define a class Mux4_1 which inherits from Mux and represents a 4:1 multiplexer
class Mux4_1 : public Mux
{
public:
    // Default constructor
    Mux4_1() {}
    // Constructor with enable input value
    Mux4_1(bool val)
    {
        // Create instances of Mux2_1 multiplexers
        mux2_1[0] = new Mux2_1(val);
        mux2_1[1] = new Mux2_1(val);
        mux2_1[2] = new Mux2_1(val);
    }
    // Set the data inputs of the multiplexer
    void setData(bool val, int pin) override
    {
        if (pin < 2)
            mux2_1[0]->setData(val, pin); // Set the data inputs of the first Mux2_1 multiplexer
        else
            mux2_1[1]->setData(val, pin - 2); // Set the data inputs of the second Mux2_1 multiplexer
    }

    void setData(Gate *gate, int pin) override
    {
        if (pin < 2)
            mux2_1[0]->setData(gate, pin); // Set the data inputs of the first Mux2_1 multiplexer
        else
            mux2_1[1]->setData(gate, pin - 2); // Set the data inputs of the second Mux2_1 multiplexer
    }
    // Set the enable input of the multiplexer
    void setEnable(bool val) override
    {
        for (int i = 0; i < 3; i++)
            mux2_1[i]->setEnable(val); // Set the enable inputs of all Mux2_1 multiplexers
    }

    void setEnable(Gate *gate) override
    {
        for (int i = 0; i < 3; i++)
            mux2_1[i]->setEnable(gate); // Set the enable inputs of all Mux2_1 multiplexers
    }
    // Set the select inputs of the multiplexer
    void setSelect(bool val, int pin) override
    {
        if (pin == 0)
        {
            mux2_1[0]->setSelect(val, 0); // Set the select inputs of the first Mux2_1 multiplexer
            mux2_1[1]->setSelect(val, 0); // Set the select inputs of the second Mux2_1 multiplexer
        }
        else
        {
            mux2_1[2]->setSelect(val, 0); // Set the select inputs of the third Mux2_1 multiplexer
        }
    }

    void setSelect(Gate *gate, int pin) override
    {
        if (pin == 0)
        {
            mux2_1[0]->setSelect(gate, 0); // Set the select inputs of the first Mux2_1 multiplexer
            mux2_1[1]->setSelect(gate, 0); // Set the select inputs of the second Mux2_1 multiplexer
        }
        else
            mux2_1[2]->setSelect(gate, 0); // Set the select inputs of the third Mux2_1 multiplexer
    }
    // Get the output of the multiplexer
    Gate *output() override
    {
        mux2_1[2]->setData(mux2_1[0]->output(), 0); // Set the first input of the third Mux2_1 multiplexer to the output of the first Mux2_1 multiplexer
        mux2_1[2]->setData(mux2_1[1]->output(), 1); // Set the second input of the third Mux2_1 multiplexer to the output of the second Mux2_1 multiplexer
        return mux2_1[2]->output();                 // Return the output of the third Mux2_1 multiplexer
    }

private:
    // An array of Mux2_1 pointers to hold the components of the multiplexer
    Mux *mux2_1[3];
};

// Define a class XOR_Mux which inherits from Gate and represents an XOR gate implemented using a 4:1 multiplexer
class XOR_Mux : public Gate
{
public:
    // Default constructor
    XOR_Mux() : mux(true)
    {
        mux.setEnable(true); // Set the enable input of the multiplexer to true
    }
    // Set the select inputs of the multiplexer
    void setValue(bool val, int pin) override
    {
        mux.setSelect(val, pin); // Set the select inputs of the multiplexer
    }

    void setValue(Gate *gate, int pin) override
    {
        mux.setSelect(gate, pin); // Set the select inputs of the multiplexer
    }
    // Get the output of the XOR gate
    bool output() override
    {
        // Set the data inputs of the multiplexer to the values required to implement an XOR gate
        mux.setData(false, 0);
        mux.setData(true, 1);
        mux.setData(true, 2);
        mux.setData(false, 3);
        // Return the output of the multiplexer
        return mux.output()->output();
    }

private:
    // An instance of the Mux4_1 class to implement the XOR gate
    Mux4_1 mux;
};

int main()
{
    // Create an instance of the XOR_Mux class
    XOR_Mux xorGate;
    // Read two integer values from the user
    int a, b;
    cin >> a >> b;

    // Set the select inputs of the XOR gate to the given values
    xorGate.setValue(a, 0);
    xorGate.setValue(b, 1);

    // Print the output of the XOR gate
    cout << xorGate.output() << endl;

    return 0;
}