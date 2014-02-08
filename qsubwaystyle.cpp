#include "qsubwaystyle.h"
#include <QPainter>
#include <QStyleOption>
#include <QApplication>

#include <QDebug>

#include "subwaycolor.h"

QSubwayStyle::QSubwayStyle()
{
}

void QSubwayStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch(element)
    {
        case CE_PushButtonBevel:{
            QPen oldPen = painter->pen();
            painter->setPen(ButtonBorder);
            painter->drawRect(option->rect.adjusted(0,0,-1,-1));
            painter->drawRect(option->rect.adjusted(1,1,-2,-2));
            painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            painter->setPen(oldPen);
            //qDebug() << option->state << endl;
            if(option->state & State_MouseOver)
                painter->fillRect(option->rect.adjusted(3,3,-3,-3),ButtonHoverBackground);
            //else if(option->state & )
                //painter->fillRect(option->rect.adjusted(3,3,-3,-3),ButtonActiveBackground);
            else
                painter->fillRect(option->rect.adjusted(3,3,-3,-3),ButtonNormalBackground);
            break;
        }
        default:
            BaseStyle::drawControl(element,option,painter,widget);
    }
}

void QSubwayStyle::drawPrimitive ( PrimitiveElement elem, const QStyleOption * option, QPainter * painter, const QWidget * widget) const
{
    switch(elem)
    {
        case PE_FrameLineEdit:{
            QPen oldPen = painter->pen();
            painter->setPen(LineEditBorder);
            painter->drawRect(option->rect.adjusted(0,0,-1,-1));
            painter->drawRect(option->rect.adjusted(1,1,-2,-2));
            painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            painter->setPen(oldPen);
            return;
        }
        case PE_FrameFocusRect:
            return;
        case PE_FrameTabWidget:{
            QPen oldPen = painter->pen();
            painter->setPen(TabWidgetBorder);
            painter->drawRect(option->rect.adjusted(0,0,-1,-1));
            painter->drawRect(option->rect.adjusted(1,1,-2,-2));
            painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            painter->setPen(oldPen);
            return;
        }
        default:
            BaseStyle::drawPrimitive(elem,option,painter,widget);
    }
}

QRect QSubwayStyle::subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    switch(element)
    {
        case SE_LineEditContents:
            return option->rect.adjusted(3,3,-3,-3);
        default:
            return BaseStyle::subElementRect(element,option,widget);
    }
}

void QSubwayStyle::polish(QPalette &pal)
{
    pal.setColor(pal.Window,WindowBackground);
    pal.setColor(pal.Base,BaseBackground);
}

void QSubwayStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch(control)
    {
    case CC_ComboBox:
    {
        if (const QStyleOptionComboBox *cmb = qstyleoption_cast<const QStyleOptionComboBox *>(option))
        {
            QRect re;
            int flags = option->state;
            //if (hoverWidget == widget) state |= MT_HOVER;
            /*if (!(flags & State_Enabled))
                state = MT_DISABLED;
            else if (cmb->activeSubControls == SC_ComboBoxArrow && (cmb->state & State_Sunken))
                state = MT_ACTIVE;
            else if (cmb->activeSubControls == SC_ComboBoxArrow && (cmb->state & State_MouseOver))
                state = MT_HOVER;
            else
                state = MT_NORMAL;*/
            painter->save();

            if (cmb->subControls & SC_ComboBoxFrame) {
                re = proxy()->subControlRect(CC_ComboBox, option, SC_ComboBoxFrame, widget);
                painter->setClipRect(re);
                painter->setPen(ComboBoxBorder);
                painter->drawRect(option->rect.adjusted(0,0,-1,-1));
                painter->drawRect(option->rect.adjusted(1,1,-2,-2));
                painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            }
            if (cmb->subControls & SC_ComboBoxEditField) {
                re = proxy()->subControlRect(CC_ComboBox, option, SC_ComboBoxEditField, widget);
                painter->setClipRect(re);
                painter->setPen(ComboBoxBorder);
                painter->drawRect(option->rect.adjusted(0,0,-1,-1));
                painter->drawRect(option->rect.adjusted(1,1,-2,-2));
                painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            }
            if (cmb->subControls & SC_ComboBoxArrow) {
                re = proxy()->subControlRect(CC_ComboBox, option, SC_ComboBoxArrow, widget);
                painter->setClipRect(re);
                painter->setPen(ComboBoxBorder);
                painter->drawRect(option->rect.adjusted(0,0,-1,-1));
                painter->drawRect(option->rect.adjusted(1,1,-2,-2));
                painter->drawRect(option->rect.adjusted(2,2,-3,-3));
                painter->drawPixmap(re,QPixmap(ComboxArrawPixmap));
            }

            painter->restore();
            break;
        }
    default:
            BaseStyle::drawComplexControl(control,option,painter,widget);
        }
    }
}
