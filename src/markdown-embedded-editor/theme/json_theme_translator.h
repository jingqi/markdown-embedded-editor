
#ifndef ___HEADFILE_CA63EF05_CD36_4F18_A9A4_74614277AA02_
#define ___HEADFILE_CA63EF05_CD36_4F18_A9A4_74614277AA02_

#include <QJsonObject>

#include <json_translator.h>
#include "theme.h"

namespace mdee
{

class JsonThemeTranslator : public JsonTranslator<Theme>
{
private:
    Theme fromJsonObject(const QJsonObject &object);
    QJsonObject toJsonObject(const Theme &theme);
};

}

#endif
