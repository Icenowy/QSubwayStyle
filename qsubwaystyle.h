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
    void polish ( QApplication * application );
signals:
    
public slots:
    

public:
    enum {
   windowsItemFrame = 2, // menu item frame width
   windowsSepHeight = 9, // separator item height
   windowsItemHMargin = 3, // menu item hor text margin
   windowsItemVMargin = 2, // menu item ver text margin
   windowsArrowHMargin = 6, // arrow horizontal margin
   windowsRightBorder = 15, // right border on windows
   windowsCheckMarkWidth = 12 // checkmarks width on windows
   };
};

#endif // QSUBWAYSTYLE_H
