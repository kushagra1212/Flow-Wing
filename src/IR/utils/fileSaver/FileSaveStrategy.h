#ifndef FILESAVESTRATEGY_H
#define FILESAVESTRATEGY_H

#include <string>

template <typename ContentType, typename LoggerType> class FileSaveStrategy {
public:
  LoggerType logger;
  virtual bool saveToFile(const std::string &path,
                          ContentType content) const = 0;
};

#endif // FILESAVESTRATEGY_H
