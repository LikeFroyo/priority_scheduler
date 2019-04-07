# priority_scheduler
Scheduler that uses a preemptive priority scheduling algorithm based on dynamically changing priority.Larger number for priority indicates higher priority*. When the process starts execution (i.e. CPU assigned),priority for that process changes at thera te of m=1. When the process waits for CPU in the ready queue (but not yet started execution),its priority changes at a rate n=2. All the processes are initially assigned priority value of 0 when	they enter ready queue for the first time . The time slice for each process is q = 1. When two processes want to join ready queue simultaneously, the process which has not executed recently is given priority. It caluclates avg waiting time and also can show how a process is actually executed.

Sample Data Set:

[ProcessID | Arrival Time | Service Time]:
[  1            0                 4 ],
[  2            1                 1 ]
[  3            2                 2 ],
[  4            3                 1 ],

Avg waiting time : 1 sec

NOTE: Processor ID should be UNIQUE as if in Operating SYSTEM.
