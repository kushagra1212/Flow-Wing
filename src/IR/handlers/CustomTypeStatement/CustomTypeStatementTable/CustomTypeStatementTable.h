#ifndef FLOWWING_CUSTOM_TYPE_EXP_TABLE_H
#define FLOWWING_CUSTOM_TYPE_EXP_TABLE_H

#include "../../../../SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../../../common/Common.h"

class CustomTypeStatementTable {
private:
  std::unordered_map<std::string, BoundCustomTypeStatement *> _type_exp_map;

public:
  inline BoundCustomTypeStatement *getExp(const std::string &name) {
    if (_type_exp_map.find(name) != _type_exp_map.end()) {
      return _type_exp_map[name];
    }
    return nullptr; // Not found
  }

  inline void setExp(const std::string &name, BoundCustomTypeStatement *value) {
    _type_exp_map[name] = value;
  }
};

#endif // FLOWWING_CUSTOM_TYPE_EXP_TABLE_H