#include "stdafx.h"
#include "SelectAreaDialog.h"

// SelectAreaDialog의 기본 생성자입니다.
SelectAreaDialog::SelectAreaDialog(QPixmap *pixmap, QWidget *parent) :
	QDialog(parent)
{
	label = new QLabel(this);
	label->setPixmap(*pixmap);
	label->showFullScreen();
	showFullScreen();
}

// 캡처한 영역을 QRect형으로 반환합니다.
QRect SelectAreaDialog::getRect()
{
	return *areaRect;
}

void SelectAreaDialog::paintEvent(QPaintEvent *paintEvent)
{
	//
}

// 마우스 누름 이벤트
void SelectAreaDialog::mousePressEvent(QMouseEvent *mouseEvent)
{
	point1 = new QPoint(mouseEvent->x(), mouseEvent->y());
}

// 마우스 뗌 이벤트
void SelectAreaDialog::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	point2 = new QPoint(mouseEvent->x(), mouseEvent->y());

	int x, y, w, h;

	if (point1->x() < point2->x())
	{
		x = point1->x();
		w = point2->x() - point1->x() + 1;
	}
	else
	{
		x = point2->x();
		w = point1->x() - point2->x() + 1;
	}

	if (point1->y() < point2->y())
	{
		y = point1->y();
		h = point2->y() - point1->y() + 1;
	}
	else
	{
		y = point2->y();
		h = point1->y() - point2->y() + 1;
	}

	areaRect = new QRect(x, y, w, h);

	close();
}
