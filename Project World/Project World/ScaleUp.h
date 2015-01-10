#ifndef ScaleUp_H_INCLUDED
#define ScaleUp_H_INCLUDED
#include "ObjectComponant.h"
class ScaleUp : public ObjectComponant
{
public:
	int Speed;
	void init() override;
	void Update(GameObject *Object) override;
private:
	static DerivedRegister<ScaleUp> reg;
};
#endif
