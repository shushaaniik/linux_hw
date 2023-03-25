# HW 2

## Signal echo

The handler of the signal SIGUSR1 is supposed to react by printing the following information:
* The PID of the sender process,
* The UID and the user name of the sender,
* The current values of the EIP, EAX, EBX registers.

### Usage:
```
cd HW2
make
./signal-echo

**from another terminal**
ps ax
kill -SIGUSR1 [signal-echo pid]
```
