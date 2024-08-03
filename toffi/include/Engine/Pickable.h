#pragma once

#include "GameObject.h"

class Pickable : public GameObject {
protected:
	bool m_picked = false;

	void commonPicked();

public:
    virtual void onPicked() = 0;

	bool getPicked();
};
