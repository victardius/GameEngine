#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
	static System* getInstance();
	~System();
private:
	System();
};

#endif