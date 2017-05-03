/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFileInfo>
#include <QDir>
#include <QSettings>

#include "recent_files_menu.h"

RecentFilesMenu::RecentFilesMenu(QWidget *parent) :
    QMenu(tr("Recent &Files"), parent)
{
}

void RecentFilesMenu::readState()
{
    QSettings settings;

    int size = settings.beginReadArray("recentFiles");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        _recent_files << settings.value("fileName").toString();
    }
    settings.endArray();

    updateMenu();
}

void RecentFilesMenu::saveState() const
{
    QSettings settings;

    settings.beginWriteArray("recentFiles");
    for (int i = 0; i < _recent_files.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("fileName", _recent_files.at(i));
    }
    settings.endArray();
}

void RecentFilesMenu::addFile(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString absoluteNativeFileName(QDir::toNativeSeparators(fileInfo.absoluteFilePath()));

    // add file to top of list
    _recent_files.removeAll(absoluteNativeFileName);
    _recent_files.prepend(absoluteNativeFileName);

    // remove last entry if list contains more than 10 entries
    if (_recent_files.size() > 10) {
        _recent_files.removeLast();
    }

    updateMenu();
}

void RecentFilesMenu::clearMenu()
{
    _recent_files.clear();
    updateMenu();
}

void RecentFilesMenu::recentFileTriggered()
{
    QAction *action = qobject_cast<QAction*>(sender());
    emit recentFileTriggered(action->data().toString());
}

void RecentFilesMenu::updateMenu()
{
    clear();

    foreach (const QString &recentFile, _recent_files) {
        QAction *action = addAction(recentFile);
        action->setData(recentFile);

        connect(action, SIGNAL(triggered()),
                this, SLOT(recentFileTriggered()));
    }

    addSeparator();
    addAction(tr("Clear Menu"), this, SLOT(clearMenu()));

    setEnabled(!_recent_files.empty());
}
