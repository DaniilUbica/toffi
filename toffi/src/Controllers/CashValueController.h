#pragma once

#include "cpplib/singletone.hpp"

#include <nod/nod.hpp>

class CashValueController : public game_engine::cpplib::singletone_from_this<CashValueController> {
public:
    void addCash(int cash);
    int cashValue() const { return m_cashValue; };

    nod::signal<void(int)> fireCashValueChanged;

private:
    int m_cashValue = 0;
};
