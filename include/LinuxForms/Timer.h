#ifndef TIMER_HPP
#define TIMER_HPP

#include <gtk/gtk.h>
#include "Events.h"
#include "EventHandler.h"

namespace LinuxForms
{
    class Timer
    {
    public:
        int interval;
        bool run;    
        EventHandler<TimerTickEvent> onTick;
        
        Timer(int interval = 25)
        {
            this->interval = interval;
        }
        
        void Start()
        {
            if(onTick != nullptr)
            {                
                run = true;                
                g_timeout_add(interval, Update, this);            
            }
        }
        
        void Stop()
        {
            run = false;
        }
        
    private:
        
        static gboolean Update(gpointer data)
        {
            Timer* timer = reinterpret_cast<Timer*>(data);
            
            if(timer != nullptr)
            {            
                if(timer->onTick != nullptr)
                {
                    timer->onTick();
                    return timer->run;
                }
            }
            
            return true;
        }
    };
}
#endif
