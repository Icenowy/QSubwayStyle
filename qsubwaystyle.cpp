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
        case CE_TabBarTabShape:{
            QPen oldPen = painter->pen();
            painter->setPen(TabBarTabBorder);
            painter->drawRect(option->rect.adjusted(0,0,-1,-1));
            painter->drawRect(option->rect.adjusted(1,1,-2,-2));
            painter->drawRect(option->rect.adjusted(2,2,-3,-3));
            painter->setPen(oldPen);
            //qDebug() << option->state << endl;
            if(option->state & State_Selected)
                painter->fillRect(option->rect.adjusted(3,3,-3,-3),TabBarTabActiveBackground);
            //else if(option->state & )
                //painter->fillRect(option->rect.adjusted(3,3,-3,-3),ButtonActiveBackground);
            else
                painter->fillRect(option->rect.adjusted(3,3,-3,-3),TabBarTabNormalBackground);
            break;
        }
        case CE_MenuBarEmptyArea:{
            break;
        }
        case CE_MenuBarItem:{
            QPalette::ColorRole textRole = (QPalette::ColorRole)(((option->state & State_Enabled)) ? QPalette::Text : QPalette::Disabled);
            if(option->state & State_HasFocus) textRole = QPalette::HighlightedText;
            uint alignment = Qt::AlignCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
            if (!styleHint(SH_UnderlineShortcut, option, widget))
                alignment |= Qt::TextHideMnemonic;
            /*if(option->state & State_HasFocus)
            {
                painter->fillRect(option->rect.adjusted(0, 3, 0, -1),MenuBarActiveBackground);
            }*/
            if(const QStyleOptionMenuItem *mbi = qstyleoption_cast<const QStyleOptionMenuItem *>(option))
            {
                proxy()->drawItemText(painter, mbi->rect.adjusted(3, 6, -4, -5), alignment, option->palette, option->state & State_Enabled, mbi->text, textRole);
            }
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
        case PE_FrameGroupBox:
            return;
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
    pal.setColor(pal.Text,TextColor);
    pal.setColor(pal.HighlightedText,HighLightTextColor);
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
                painter->drawRect(re.adjusted(0,0,-1,-1));
                painter->drawRect(re.adjusted(1,1,-2,-2));
                painter->drawRect(re.adjusted(2,2,-3,-3));
            }
            /*if (cmb->subControls & SC_ComboBoxEditField) {
                re = proxy()->subControlRect(CC_ComboBox, option, SC_ComboBoxEditField, widget);
                painter->setClipRect(re);
                painter->setPen(ComboBoxBorder);
                painter->drawRect(re.adjusted(0,0,-1,-1));
                painter->drawRect(re.adjusted(1,1,-2,-2));
                painter->drawRect(re.adjusted(2,2,-3,-3));
            }*/
            if (cmb->subControls & SC_ComboBoxArrow) {
                re = proxy()->subControlRect(CC_ComboBox, option, SC_ComboBoxArrow, widget);
                painter->setClipRect(re);
                painter->setPen(ComboBoxBorder);
                painter->drawRect(re.adjusted(0,0,-1,-1));
                painter->drawRect(re.adjusted(1,1,-2,-2));
                painter->drawRect(re.adjusted(2,2,-3,-3));
                painter->drawPixmap(re.adjusted(3,3,-4,-4),QPixmap(ComboxArrawPixmap));
            }

            painter->restore();
            break;
        }
    case CC_ScrollBar:
        painter->save();
        if (const QStyleOptionSlider *scrollBar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            bool isEnabled = scrollBar->state & State_Enabled;
            bool reverse = scrollBar->direction == Qt::RightToLeft;
            bool horizontal = scrollBar->orientation == Qt::Horizontal;
            bool sunken = scrollBar->state & State_Sunken;

            painter->fillRect(option->rect, option->palette.background());

            QRect scrollBarSubLine = proxy()->subControlRect(control, scrollBar, SC_ScrollBarSubLine, widget);
            QRect scrollBarAddLine = proxy()->subControlRect(control, scrollBar, SC_ScrollBarAddLine, widget);
            QRect scrollBarSlider = proxy()->subControlRect(control, scrollBar, SC_ScrollBarSlider, widget);
            QRect grooveRect = proxy()->subControlRect(control, scrollBar, SC_ScrollBarGroove, widget);

            // paint groove
            /*if (scrollBar->subControls & SC_ScrollBarGroove) {
                //painter->setBrush(grooveColor);
                painter->setPen(Qt::NoPen);
                if (horizontal) {
                    painter->drawRect(grooveRect);
                    painter->setPen(darkOutline);
                    painter->drawLine(grooveRect.topLeft(), grooveRect.topRight());
                    painter->drawLine(grooveRect.bottomLeft(), grooveRect.bottomRight());
                } else {
                    painter->drawRect(grooveRect);
                    painter->setPen(darkOutline);
                    painter->drawLine(grooveRect.topLeft(), grooveRect.bottomLeft());
                    painter->drawLine(grooveRect.topRight(), grooveRect.bottomRight());
                }
            }*/
            //paint slider
            if (scrollBar->subControls & SC_ScrollBarSlider) {
                QRect pixmapRect = scrollBarSlider;
                pixmapRect.adjust(2,2,-2,-2);

                if (isEnabled) {
                    if(option->state & State_MouseOver)
                        painter->fillRect(pixmapRect,ScrollBarSliderHover);
                    else if(option->state & State_Sunken)
                        painter->fillRect(pixmapRect,ScrollBarSliderActive);
                    else
                        painter->fillRect(pixmapRect,ScrollBarSliderNormal);
                } else {
                    painter->fillRect(pixmapRect,ScrollBarSliderDisable);
                }
            }

            // The SubLine (up/left) buttons
            if (scrollBar->subControls & SC_ScrollBarSubLine) {
                //int scrollBarExtent = proxy()->pixelMetric(PM_ScrollBarExtent, option, widget);
                QRect pixmapRect = scrollBarSubLine;
                if (isEnabled) {
                    if(option->state & State_MouseOver)
                        painter->fillRect(pixmapRect,ScrollBarSliderHover);
                    else if(option->state & State_Sunken)
                        painter->fillRect(pixmapRect,ScrollBarSliderActive);
                    else
                        painter->fillRect(pixmapRect,ScrollBarSliderNormal);
                } else {
                    painter->fillRect(pixmapRect,ScrollBarSliderDisable);
                }

                // Arrows
                PrimitiveElement arrow;
                if (option->state & State_Horizontal)
                    arrow = option->direction == Qt::LeftToRight ? PE_IndicatorArrowLeft: PE_IndicatorArrowRight;
                else
                    arrow = PE_IndicatorArrowUp;
                QStyleOption arrowOpt = *option;
                arrowOpt.rect = scrollBarSubLine.adjusted(3, 3, -2, -2);
                proxy()->drawPrimitive(arrow, &arrowOpt, painter, widget);


                // The AddLine (down/right) button
                if (scrollBar->subControls & SC_ScrollBarAddLine) {
                    QRect pixmapRect = scrollBarAddLine;
                    if (isEnabled) {
                        if(option->state & State_MouseOver)
                            painter->fillRect(pixmapRect,ScrollBarSliderHover);
                        else if(option->state & State_Sunken)
                            painter->fillRect(pixmapRect,ScrollBarSliderActive);
                        else
                            painter->fillRect(pixmapRect,ScrollBarSliderNormal);
                    } else {
                        painter->fillRect(pixmapRect,ScrollBarSliderDisable);
                    }

                    PrimitiveElement arrow;
                    if (option->state & State_Horizontal)
                        arrow = option->direction == Qt::LeftToRight ? PE_IndicatorArrowRight : PE_IndicatorArrowLeft;
                    else
                        arrow = PE_IndicatorArrowDown;

                    QStyleOption arrowOpt = *option;
                    arrowOpt.rect = scrollBarAddLine.adjusted(3, 3, -2, -2);
                    proxy()->drawPrimitive(arrow, &arrowOpt, painter, widget);
                }
            }
        }
        painter->restore();
        break;
    default:
            BaseStyle::drawComplexControl(control,option,painter,widget);
        }
    }
}
