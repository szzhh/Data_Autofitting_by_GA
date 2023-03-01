#include "engine.h"  
#include <QtWidgets/QApplication>
#include "ui_test.h"
#include "test.h"
#include <qpainter.h>

test::test(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::testClass)
{
    ui->setupUi(this);
	this->resize(QSize(600, 600));
}
test::~test()
{
	delete ui;
}








