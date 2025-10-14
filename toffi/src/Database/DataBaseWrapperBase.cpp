#include "DataBaseWrapperBase.h"

DataBaseWrapperBase::DataBaseWrapperBase(std::shared_ptr<game_engine::database::DataBaseManager> dbManager) : m_dbManager(dbManager) {}

DataBaseWrapperBase::~DataBaseWrapperBase() {}
