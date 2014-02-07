#include "subwaystyleplugin.h"
#include "qsubwaystyle.h"


SubwayStylePlugin::SubwayStylePlugin(QObject *parent) :
    QStylePlugin(parent)
{
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(QSubwayStyle, SubwayStylePlugin)
#endif // QT_VERSION < 0x050000

QStyle* SubwayStylePlugin::create(const QString &key)
{
    return new QSubwayStyle();
}

QStringList SubwayStylePlugin::keys() const
{
    return QStringList("Subway");
}
