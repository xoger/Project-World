#ifndef MoveForward_H_INCLUDED
#define MoveForward_H_INCLUDED
#include "ObjectComponant.h"

class MoveForward : public ObjectComponant
{
public:
	int Speed;
	int Max = 0;
	
	void init() override;
	void Update(GameObject *Object) override;
private:
	static DerivedRegister<MoveForward> reg;
};
#endif
