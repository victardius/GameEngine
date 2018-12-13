#include "System.h"



System::System()
{
}

System* System::getInstance() {
	return new System();
}

System::~System()
{
}
