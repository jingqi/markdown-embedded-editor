
#ifndef ___HEADFILE_4A6EA914_93C0_4495_AE67_07E99B190185_
#define ___HEADFILE_4A6EA914_93C0_4495_AE67_07E99B190185_

#include <QString>
#include <QStringList>

#include <json_collection.h>
#include "theme.h"

namespace mdee
{

class ThemeCollection : public JsonCollection<Theme>
{
public:
    bool load(const QString &fileName);

    int insert(const Theme &theme);

    int count() const;
    const Theme &at(int offset) const;
    bool contains(const QString &name) const;
    const Theme theme(const QString &name) const;
    QStringList themeNames() const;

    const QString name() const;

private:
    QStringList themesIndex;
    QList<Theme> themes;
};

}

#endif
