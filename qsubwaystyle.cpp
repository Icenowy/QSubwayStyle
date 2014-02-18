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
    case CE_MenuItem:
   if (const QStyleOptionMenuItem *menuitem = qstyleoption_cast<const QStyleOptionMenuItem *>(option)) {
       QPainter *p = painter;
   int x, y, w, h;
   menuitem->rect.getRect(&x, &y, &w, &h);
   int tab = menuitem->tabWidth;
   bool dis = !(menuitem->state & State_Enabled);
   bool checked = menuitem->checkType != QStyleOptionMenuItem::NotCheckable
   ? menuitem->checked : false;
   bool act = menuitem->state & State_Selected;
   // windows always has a check column, regardless whether we have an icon or not
   int checkcol = qMax<int>(menuitem->maxIconWidth, QSubwayStyle::windowsCheckMarkWidth);
   QBrush fill = menuitem->palette.brush(act ? QPalette::Highlight : QPalette::Button);
   p->fillRect(menuitem->rect.adjusted(0, 0, -1, 0), fill);
   if (menuitem->menuItemType == QStyleOptionMenuItem::Separator){
   int yoff = y-1 + h / 2;
   p->setPen(menuitem->palette.dark().color());
   p->drawLine(x + 2, yoff, x + w - 4, yoff);
   p->setPen(menuitem->palette.light().color());
   p->drawLine(x + 2, yoff + 1, x + w - 4, yoff + 1);
   return;
   }
   QRect vCheckRect = visualRect(option->direction, menuitem->rect, QRect(menuitem->rect.x(), menuitem->rect.y(), checkcol, menuitem->rect.height()));
   if (!menuitem->icon.isNull() && checked) {
   if (act) {
   qDrawShadePanel(p, vCheckRect,
   menuitem->palette, true, 1,
   &menuitem->palette.brush(QPalette::Button));
   } else {
   QBrush fill(menuitem->palette.light().color(), Qt::Dense4Pattern);
   qDrawShadePanel(p, vCheckRect, menuitem->palette, true, 1, &fill);
   }
   } else if (!act) {
   p->fillRect(vCheckRect, menuitem->palette.brush(QPalette::Button));
   }
   // On Windows Style, if we have a checkable item and an icon we
   // draw the icon recessed to indicate an item is checked. If we
   // have no icon, we draw a checkmark instead.
   if (!menuitem->icon.isNull()) {
   QIcon::Mode mode = dis ? QIcon::Disabled : QIcon::Normal;
   if (act && !dis)
   mode = QIcon::Active;
   QPixmap pixmap;
   if (checked)
   pixmap = menuitem->icon.pixmap(proxy()->pixelMetric(PM_SmallIconSize, option, widget), mode, QIcon::On);
   else
   pixmap = menuitem->icon.pixmap(proxy()->pixelMetric(PM_SmallIconSize, option, widget), mode);
   int pixw = pixmap.width();
   int pixh = pixmap.height();
   if (act && !dis && !checked)
   qDrawShadePanel(p, vCheckRect, menuitem->palette, false, 1,
   &menuitem->palette.brush(QPalette::Button));
   QRect pmr(0, 0, pixw, pixh);
   pmr.moveCenter(vCheckRect.center());
   p->setPen(menuitem->palette.text().color());
   p->drawPixmap(pmr.topLeft(), pixmap);
   } else if (checked) {
   QStyleOptionMenuItem newMi = *menuitem;
   newMi.state = State_None;
   if (!dis)
   newMi.state |= State_Enabled;
   if (act)
   newMi.state |= State_On;
   newMi.rect = visualRect(option->direction, menuitem->rect, QRect(menuitem->rect.x() + QSubwayStyle::windowsItemFrame,
   menuitem->rect.y() + QSubwayStyle::windowsItemFrame,
   checkcol - 2 * QSubwayStyle::windowsItemFrame,
   menuitem->rect.height() - 2 * QSubwayStyle::windowsItemFrame));
   proxy()->drawPrimitive(PE_IndicatorMenuCheckMark, &newMi, p, widget);
   }
   p->setPen(act ? menuitem->palette.highlightedText().color() : menuitem->palette.buttonText().color());
   QColor discol;
   if (dis) {
   discol = menuitem->palette.text().color();
   p->setPen(discol);
   }
   int xm = int(QSubwayStyle::windowsItemFrame) + checkcol + int(QSubwayStyle::windowsItemHMargin);
   int xpos = menuitem->rect.x() + xm;
   QRect textRect(xpos, y + QSubwayStyle::windowsItemVMargin,
   w - xm - QSubwayStyle::windowsRightBorder - tab + 1, h - 2 * QSubwayStyle::windowsItemVMargin);
   QRect vTextRect = visualRect(option->direction, menuitem->rect, textRect);
   QString s = menuitem->text;
   if (!s.isEmpty()) { // draw text
   p->save();
   int t = s.indexOf(QLatin1Char('\t'));
   int text_flags = Qt::AlignVCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
   if (!proxy()->styleHint(SH_UnderlineShortcut, menuitem, widget))
   text_flags |= Qt::TextHideMnemonic;
   text_flags |= Qt::AlignLeft;
   if (t >= 0) {
   QRect vShortcutRect = visualRect(option->direction, menuitem->rect,
   QRect(textRect.topRight(), QPoint(menuitem->rect.right(), textRect.bottom())));
   if (dis && !act && proxy()->styleHint(SH_EtchDisabledText, option, widget)) {
   p->setPen(menuitem->palette.light().color());
   p->drawText(vShortcutRect.adjusted(1,1,1,1), text_flags, s.mid(t + 1));
   p->setPen(discol);
   }
   p->drawText(vShortcutRect, text_flags, s.mid(t + 1));
   s = s.left(t);
   }
   QFont font = menuitem->font;
   if (menuitem->menuItemType == QStyleOptionMenuItem::DefaultItem)
   font.setBold(true);
   p->setFont(font);
   if (dis && !act && proxy()->styleHint(SH_EtchDisabledText, option, widget)) {
   p->setPen(menuitem->palette.light().color());
   p->drawText(vTextRect.adjusted(1,1,1,1), text_flags, s.left(t));
   p->setPen(discol);
   }
   p->drawText(vTextRect, text_flags, s.left(t));
   p->restore();
   }
   if (menuitem->menuItemType == QStyleOptionMenuItem::SubMenu) {// draw sub menu arrow
   int dim = (h - 2 * QSubwayStyle::windowsItemFrame) / 2;
   PrimitiveElement arrow;
   arrow = (option->direction == Qt::RightToLeft) ? PE_IndicatorArrowLeft : PE_IndicatorArrowRight;
   xpos = x + w - QSubwayStyle::windowsArrowHMargin - QSubwayStyle::windowsItemFrame - dim;
   QRect vSubMenuRect = visualRect(option->direction, menuitem->rect, QRect(xpos, y + h / 2 - dim / 2, dim, dim));
   QStyleOptionMenuItem newMI = *menuitem;
   newMI.rect = vSubMenuRect;
   newMI.state = dis ? State_None : State_Enabled;
   if (act)
   newMI.palette.setColor(QPalette::ButtonText,
   newMI.palette.highlightedText().color());
   proxy()->drawPrimitive(arrow, &newMI, p, widget);
   }
   }
   break;
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

void QSubwayStyle::polish(QApplication *application)
{
    QPalette p = application->palette();
    polish(p);
    application->setPalette(p);
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
                painter->drawRect(re.adjusted(0,0,1,-1));
                painter->drawRect(re.adjusted(1,1,0,-2));
                painter->drawRect(re.adjusted(2,2,-1,-3));
                //painter->drawPixmap(re.adjusted(3,3,-4,-4),QPixmap(ComboxArrawPixmap));
                QStyleOption option2;
                option2.rect = re.adjusted(3,3,-2,-4);
                proxy()->drawPrimitive(PE_IndicatorArrowDown,&option2,painter,widget);
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
                QStyleOption arrowoption = *option;
                arrowoption.rect = scrollBarSubLine.adjusted(3, 3, -2, -2);
                proxy()->drawPrimitive(arrow, &arrowoption, painter, widget);


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

                    QStyleOption arrowoption = *option;
                    arrowoption.rect = scrollBarAddLine.adjusted(3, 3, -2, -2);
                    proxy()->drawPrimitive(arrow, &arrowoption, painter, widget);
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
