#pragma once

// Qt �����ӿ�ũ ���
#include <QtWidgets/QDialog>

class SelectAreaDialog : public QDialog
{
	Q_OBJECT

private:
	QLabel *label;
	QRect *areaRect;
	QPoint *point1;
	QPoint *point2;

public:
	SelectAreaDialog(QPixmap *pixmap, QWidget *parent = 0);
	QRect getRect();

private:
	void paintEvent(QPaintEvent *paintEvent) override;
	void mousePressEvent(QMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
};