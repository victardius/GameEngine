#include "Animator.h"

namespace gameEngine {

	Animator::Animator()
	{
	}

	Animator* Animator::getInstance() {
		return new Animator();
	}

	Animator::~Animator()
	{
	}

}