#include "ev_timer.h"
#include "zlog.h"

EVTimer::EVTimer() : m_active(false), m_period(0), m_repeat(-1)
{

}

EVTimer::EVTimer(int repeat) : m_active(false), m_period(0), m_repeat(repeat)
{
    
}

EVTimer::~EVTimer()
{

}