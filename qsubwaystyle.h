#ifndef QSUBWAYSTYLE_H
#define QSUBWAYSTYLE_H

#include <QWindowsStyle>
#include <QPlastiqueStyle>
#include <QCommonStyle>
#include <QCleanlooksStyle>

#define BaseStyle QCleanlooksStyle

class QSubwayStyle : public BaseStyle
{
    Q_OBJECT
public:
    QSubwayStyle();
    void drawControl ( ControlElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget = 0 ) const;
    void drawPrimitive ( PrimitiveElement elem, const QStyleOption * option, QPainter * painter, const QWidget * widget = 0 ) const;
    QRect subElementRect ( SubElement element, const QStyleOption * option, const QWidget * widget = 0 ) const;
    void polish(QPalette &pal);
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
signals:
    
public slots:
    
};

#endif // QSUBWAYSTYLE_H
