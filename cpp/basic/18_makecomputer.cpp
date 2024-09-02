#include <iostream>
using namespace std;

class CPU{
public:
    virtual void calculator() = 0;
    virtual ~CPU(){}
};

class GPU{
public:
    virtual void display() = 0;
    virtual ~GPU(){}
};

class memory{
public:
    virtual void save() = 0;
    virtual ~memory(){}
};

class computer{
public:
    computer(CPU *cpu,GPU *gpu,memory *memory)
    {
        m_cpu = cpu;
        m_gpu = gpu;
        m_memory = memory;
    }
    void computerwork()
    {
        m_cpu->calculator();
        m_gpu->display();
        m_memory->save();
    }
    ~computer()
    {
        if(m_cpu!=NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }
        if(m_cpu!=NULL)
        {
            delete m_gpu;
            m_gpu = NULL;
        }
        if(m_memory!=NULL)
        {
            delete m_memory;
            m_memory = NULL;
        }
    }
private:
    CPU *m_cpu;
    GPU *m_gpu;
    memory *m_memory;
};

class IntelCPU:public CPU
{
public:
    virtual void calculator()
    {
        cout << "Intel CPU work" << endl;
    }
};

class LenovoCPU:public CPU
{
public:
    virtual void calculator()
    {
        cout << "Lenovo CPU work" << endl;
    }
};

class IntelGPU:public GPU
{
public:
    virtual void display()
    {
        cout << "Intel GPU work" << endl;
    }
};

class LenovoGPU:public GPU
{
public:
    virtual void display()
    {
        cout << "Lenovo GPU work" << endl;
    }
};

class Intelmemory:public memory
{
public:
    virtual void save()
    {
        cout << "Intel memory work" << endl;
    }
};

class Lenovomemory:public memory
{
public:
    virtual void save()
    {
        cout << "Lenovo memory work" << endl;
    }
};

void test01()
{
    CPU *intelcpu = new IntelCPU;
    GPU *intelgpu = new IntelGPU;
    memory *intelmemory = new Intelmemory;
    computer *computer1 = new computer(intelcpu, intelgpu, intelmemory);
    computer1->computerwork();
    delete computer1;
}

int main()
{
    test01();
    return 0;
}