#include "GlobalInfo.hpp"

std::map<Application *, GlobalInfo> GlobalInfo::globalInfo = std::map<Application *, GlobalInfo>();
Application *GlobalInfo::offset = nullptr;
