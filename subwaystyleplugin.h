#ifndef SUBWAYSTYLEPLUGIN_H
#define SUBWAYSTYLEPLUGIN_H

#include <QStylePlugin>
#include "qsubwaystyle.h"


class SubwayStylePlugin : public QStylePlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "QSubwayStyle.json")
#endif // QT_VERSION >= 0x050000
    
public:
    SubwayStylePlugin(QObject *parent = 0);
    virtual QStyle* create(const QString &key);
    virtual QStringList keys() const;
};

#endif // SUBWAYSTYLEPLUGIN_H
