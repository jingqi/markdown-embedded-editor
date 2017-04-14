
#ifndef ___HEADFILE_273EBD21_0961_4491_A969_0D3070DD5965_
#define ___HEADFILE_273EBD21_0961_4491_A969_0D3070DD5965_

#include <QString>
#include <stdexcept>

namespace mdee
{

class Theme
{
public:
    Theme(const QString &name,
          const QString &markdownHighlighting,
          const QString &codeHighlighting,
          const QString &previewStylesheet,
          bool builtIn = false);

    QString name() const { return m_name; }

    QString markdownHighlighting() const { return m_markdownHighlighting; }

    QString codeHighlighting() const { return m_codeHighlighting; }

    QString previewStylesheet() const { return m_previewStylesheet; }

    bool isBuiltIn() const { return m_builtIn; }

    bool operator<(const Theme &rhs) const
    {
        return m_name < rhs.name();
    }

    bool operator ==(const Theme &rhs) const
    {
        return m_name == rhs.name();
    }

private:
    void checkInvariants() const;

private:
    QString m_name;
    QString m_markdownHighlighting;
    QString m_codeHighlighting;
    QString m_previewStylesheet;
    bool m_builtIn;
};

}

#endif
