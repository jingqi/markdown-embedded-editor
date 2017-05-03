
#ifndef ___HEADFILE_20E2D580_BB48_4D85_A02A_A840DB715CD6_
#define ___HEADFILE_20E2D580_BB48_4D85_A02A_A840DB715CD6_

#include <json_translator_factory.h>
#include <json_translator.h>

#include "theme.h"
#include "json_theme_translator.h"

template <>
class JsonTranslatorFactory<mde::Theme>
{
public:
    static JsonTranslator<mde::Theme> *create()
    {
        return new mde::JsonThemeTranslator();
    }
};

#endif
