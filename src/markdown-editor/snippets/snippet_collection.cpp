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

#include "snippet_collection.h"
#include <QSharedPointer>


SnippetCollection::SnippetCollection(QObject *parent) :
    QObject(parent)
{
}

int SnippetCollection::count() const
{
    return _snippets.count();
}

int SnippetCollection::insert(const Snippet &snippet)
{
    QMap<QString, Snippet>::iterator it = _snippets.insert(snippet.trigger, snippet);
    emit collectionChanged(SnippetCollection::ItemAdded, snippet);
    return std::distance(_snippets.begin(), it);
}

void SnippetCollection::update(const Snippet &snippet)
{
    _snippets.insert(snippet.trigger, snippet);
    emit collectionChanged(SnippetCollection::ItemChanged, snippet);
}

void SnippetCollection::remove(const Snippet &snippet)
{
    _snippets.remove(snippet.trigger);
    emit collectionChanged(SnippetCollection::ItemDeleted, snippet);
}

const QString SnippetCollection::name() const
{
    return QStringLiteral("snippets");
}

bool SnippetCollection::contains(const QString &trigger) const
{
    return _snippets.contains(trigger);
}

const Snippet SnippetCollection::snippet(const QString &trigger) const
{
    return _snippets.value(trigger);
}

const Snippet &SnippetCollection::at(int offset) const
{
    return (_snippets.begin() + offset).value();
}

QSharedPointer<SnippetCollection> SnippetCollection::userDefinedSnippets() const
{
    QSharedPointer<SnippetCollection> userDefinedSnippets = QSharedPointer<SnippetCollection>::create();

    foreach (Snippet snippet, _snippets.values()) {
        if (!snippet.builtin) {
            userDefinedSnippets->insert(snippet);
        }
    }

    return userDefinedSnippets;
}
