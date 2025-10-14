#pragma once

#include <memory>

namespace game_engine {
namespace database {
    class DataBaseManager;
}
}

class DataBaseWrapperBase {
public:
    DataBaseWrapperBase(std::shared_ptr<game_engine::database::DataBaseManager> dbManager);
    ~DataBaseWrapperBase();

    virtual void createDataBase() = 0;
    virtual void createRelation() = 0;

protected:
    std::shared_ptr<game_engine::database::DataBaseManager> m_dbManager;
};
