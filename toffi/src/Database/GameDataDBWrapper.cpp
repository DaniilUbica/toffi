#include "GameDataDBWrapper.h"

#include "Engine/DataBase/DataBaseManager.h"

#include <cassert>

const std::string DB_GAME_DATA_DB_NAME       = "game_data";
const std::string DB_GAME_DATA_RELATION_NAME = "game_data";

const std::pair<std::string, std::string> DB_ATTRIBUTE_NAME_DATA = { "attribute_name", "TEXT UNIQUE" };
const std::pair<std::string, std::string> DB_ATTRIBUTE_VALUE_DATA = { "attribute_value", "" };
const std::string DB_BEST_SCORE_FIELD_NAME = "best_score";

using namespace game_engine::database;

void GameDataDBWrapper::createDataBase() {
    assert(m_dbManager->openDatabase(DB_GAME_DATA_DB_NAME));
}

void GameDataDBWrapper::createRelation() {
    DBCreateRelationData relationRequestData;
    relationRequestData.relationName = DB_GAME_DATA_RELATION_NAME;
    relationRequestData.attributes = { DB_ATTRIBUTE_NAME_DATA, DB_ATTRIBUTE_VALUE_DATA };

    assert(m_dbManager->createRelation(relationRequestData));
}

void GameDataDBWrapper::init() {
    createDataBase();
    createRelation();
}

void GameDataDBWrapper::setBestScore(int newBestScore) {
    DBRequestData::databaseName = DB_GAME_DATA_DB_NAME;
    DBRequestData::relationName = DB_GAME_DATA_RELATION_NAME;

    DBMultiInsertData insertRequestData;
    insertRequestData.attributesNames = { DB_ATTRIBUTE_NAME_DATA.first, DB_ATTRIBUTE_VALUE_DATA.first };
    insertRequestData.values = { DB_BEST_SCORE_FIELD_NAME, newBestScore };

    assert(m_dbManager->insertValues(insertRequestData));
}

std::optional<int> GameDataDBWrapper::getBestScore() const {
    DBRequestData::databaseName = DB_GAME_DATA_DB_NAME;
    DBRequestData::relationName = DB_GAME_DATA_RELATION_NAME;

    DBSingleSelectData selectRequestData;
    selectRequestData.attributeToSelect = DB_ATTRIBUTE_VALUE_DATA.first;
    selectRequestData.whereAttributeName = DB_ATTRIBUTE_NAME_DATA.first;
    selectRequestData.whereAttributeValue = DB_BEST_SCORE_FIELD_NAME;

    return m_dbManager->getValue<int>(selectRequestData);
}
