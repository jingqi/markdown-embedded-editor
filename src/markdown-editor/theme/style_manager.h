
#ifndef ___HEADFILE_D228F9CD_D466_4235_AF30_24238FAE696D_
#define ___HEADFILE_D228F9CD_D466_4235_AF30_24238FAE696D_

#include <QMap>
#include <QString>
#include "theme.h"

namespace mde
{

class StyleManager
{
public:
    void insertCustomPreviewStylesheet(const QString &styleName, const QString &stylePath);

    static QString markdownHighlightingPath(const Theme &theme);
    static QString codeHighlightingPath(const Theme &theme);
    static QString previewStylesheetPath(const Theme &theme);

private:
    static QMap<QString, QString> customPreviewStylesheets;
};

}

#endif
