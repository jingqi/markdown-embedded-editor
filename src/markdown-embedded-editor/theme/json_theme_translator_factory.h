
#ifndef ___HEADFILE_20E2D580_BB48_4D85_A02A_A840DB715CD6_
#define ___HEADFILE_20E2D580_BB48_4D85_A02A_A840DB715CD6_

#include <jsontranslatorfactory.h>
#include <jsontranslator.h>

#include "theme.h"
#include "json_theme_translator.h"

template <>
class JsonTranslatorFactory<organic::Theme>
{
public:
    static JsonTranslator<organic::Theme> *create()
    {
        return new organic::JsonThemeTranslator();
    }
};

#endif
