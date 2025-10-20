#include "CashValueController.h"

void CashValueController::addCash(int cash) {
    m_cashValue += cash;
    fireCashValueChanged(m_cashValue);
}
