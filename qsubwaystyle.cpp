#include "qsubwaystyle.h"
#include <QPainter>
#include <QStyleOption>
#include <QApplication>

QSubwayStyle::QSubwayStyle()
{
}

void QSubwayStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch(element)
    {
        case CE_PushButtonBevel:
            painter->drawRect(option->rect.adjusted(0,0,-1,-1));
            painter->drawRect(option->rect.adjusted(1,1,-2,-2));
            painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            if(option->state & State_MouseOver)
                painter->fillRect(option->rect.adjusted(3,3,-3,-3),Qt::gray);
            break;
        default:
            QPlastiqueStyle::drawControl(element,option,painter,widget);
    }
}
