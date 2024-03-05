#pragma once
#include "Observer.h"
#include "WishList.h"
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpainter.h>

class ReadOnly:public Observer,public QWidget
{
private:
	WishList& wl;
	void paintEvent(QPaintEvent* ev) override
	{
		QPainter p{ this };
		int x = 0,y = 0;
		for (auto a : wl.getAllWishList())
		{
			//p.drawRect(x, y, 10, a.getPret() * 10);
			x = rand() % 200 + 1;
			y = rand() % 200 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 120, 90);
			QRectF source(0, 0, 780, 720);
			QImage image("999.png");
			p.drawImage(target, image, source);
			x += 40;
		}
	}

	void update() override
	{
		repaint();
	}

	~ReadOnly()
	{
		wl.removeObserver(this);
	}

public:
	ReadOnly(WishList& wl) :wl{ wl } {
		wl.addObserver(this);
	}
};