#ifndef ANIMATOR_H
#define ANIMATOR_H

namespace gameEngine {

	class Animator
	{
	public:
		Animator* getInstance();
		~Animator();
	protected:
		Animator();
	};

}

#endif