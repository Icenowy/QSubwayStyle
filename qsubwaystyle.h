#ifndef QSUBWAYSTYLE_H
#define QSUBWAYSTYLE_H

#include <QWindowsStyle>
#include <QPlastiqueStyle>

class QSubwayStyle : public QPlastiqueStyle
{
    Q_OBJECT
public:
    QSubwayStyle();
    void drawControl ( ControlElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget = 0 ) const;
    
signals:
    
public slots:
    
};

#endif // QSUBWAYSTYLE_H
