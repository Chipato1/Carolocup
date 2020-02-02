FSM(MAIN_FSM)
{
    FSM_STATES
    {
        ST_INIT,
        ST_WAIT_FOR_QR_CODE_AWAY
        ST_DRIVE
    }
    
    FSM_START(ST_INIT);
    
    FSM_BGN
    {
        FSM_STATE(ST_INIT)
        {
            FSM_CALL_TASK(Initshit);
        
            FSM_TRANSITIONS
            {
                FSM_ON_EVENT("/qr_code_detected", FSM_NEXT(ST_WAIT_FOR_QR_CODE_AWAY));
            }
        }
        
        FSM_STATE(ST_WAIT_FOR_QR_CODE_AWAY)
        {
            FSM_CALL_TASK(Waitshit);
        
            FSM_TRANSITIONS
            {
                FSM_ON_EVENT("/qr_code_no_longer_detected", FSM_NEXT(ST_DRIVE));
            }
        }
        
        FSM_STATE(ST_DRIVE)
        {
            FSM_CALL_TASK(Drive);
            
            FSM_TRANSITIONS
            {
                FSM_ON_EVENT("/stop_this_shit", FSM_NEXT(ST_INIT));
            }
        }
    }
    FSM_END
}

bool preemptiveWait(double ms, decision_making::EventQueue& queue)
{
    for (int i = 0; i < 100 && !queue.isTerminated(); i++)
        boost::this_thread::sleep(boost::posix_time::milliseconds(ms / 100.0));

    return queue.isTerminated();
}

decision_making::TaskResult initTask(string task_name, const FSMCallContext& context, EventQueue& eventQueue)
{
        ROS_INFO("Initing...");

        eventQueue.riseEvent("/qr_code_detected");
        
        return decision_making::TaskResult::SUCCESS();
}

decision_making::TaskResult waitTask(string task_name, const FSMCallContext& context, EventQueue& eventQueue)
{
        ROS_INFO("Waiting...");

        while(!preemptiveWait(1000, eventQueue)){
                ROS_INFO("Wait du Bitch");
                eventQueue.riseEvent("/qr_code_no_longer_detected");

        }
        
        return decision_making::TaskResult::SUCCESS();
}

decision_making::TaskResult driveTask(string task_name, const FSMCallContext& context, EventQueue& eventQueue)
{
        ROS_INFO("Driving...");

        while(!preemptiveWait(1000, eventQueue)){
                ROS_INFO("Drive du Bitch");
                //...

        }
        
        return decision_making::TaskResult::SUCCESS();
}

int main(int argc, char **argv)
{
	EventQueue *events;

	LocalTasks::registrate("Drive", driveTask);
	LocalTasks::registrate("Waitshit", waitTask);
	LocalTasks::registrate("Initshit", initTask);
	TaskResult res = MAIN_FSM(NULL, events);
}

