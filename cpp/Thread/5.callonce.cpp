#include <iostream>
#include <thread>
#include <mutex>
#include <string>

class Log;

static Log *m_log = nullptr;
static std::once_flag flag;
int n;

class Log{
public:
    Log(){}
    Log(const Log &log) = delete;
    Log &operator=(const Log &log) = delete;
    static Log &GetInstance()
    {
        std::call_once(flag, init);
        return *m_log;
    }
    static void init()
    {
        if(!m_log) m_log = new Log;
    }
    void myprint(std::string m_str)
    {
        std::cout <<__TIME__<< m_str << std::endl;
    }
};

void logprint()
{
    Log::GetInstance().myprint(" error ");
}

void thread_task()
{
    std::thread t1(logprint);
    std::thread t2(logprint);
    t1.join();
    t2.join();
}

int main()
{
    thread_task();
    return 0;
}
