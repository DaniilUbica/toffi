#pragma once

#include "DataBaseWrapperBase.h"

#include <optional>

class GameDataDBWrapper : public DataBaseWrapperBase {
    using DataBaseWrapperBase::DataBaseWrapperBase;
public:
    void createDataBase() override;
    void createRelation() override;

    void init();

    void setBestScore(int newBestScore);
    std::optional<int> getBestScore() const;
};
