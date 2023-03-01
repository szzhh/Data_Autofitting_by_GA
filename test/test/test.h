#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class test; }
QT_END_NAMESPACE

class test : public QMainWindow
{
    Q_OBJECT

public:
    test(QWidget *parent = Q_NULLPTR);
	~test();

public slots:
	void Evolution();
	void Draw();
	void Display();
private:
    Ui::testClass *ui;
};
