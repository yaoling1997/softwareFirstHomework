#include "sudokuGUI.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <qstring.h>
#include <solver.h>
const int width = 50, height = 50;

void Solver::update() {
	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++)
			if (empty[i][j]) {
				bool ok = false;
				int x = lineEdit[i][j].displayText().toInt(&ok, 10);
				if (ok)
					matrix[i][j] = x;
				else
					matrix[i][j] = -1;
			}
	if (checkMatrix())
		label->setText("right!");
	else
		label->setText("wrong!");
}


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMainWindow w;
	Solver solver;
	solver.buildMatrix();
	w.setWindowTitle("sudoku");
	w.setFixedSize(width*matrixLen + 10, height*matrixLen + 10 + height);
	QLabel label[matrixLen][matrixLen];
	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++)
			if (solver.matrix[i][j] == 0) {
				solver.lineEdit[i][j].setParent(&w);
				solver.lineEdit[i][j].setAlignment(Qt::AlignCenter);
				solver.lineEdit[i][j].setGeometry(5 + j*width, 5 + i*height, width, height);
				solver.lineEdit[i][j].show();
			}
			else {
				label[i][j].setParent(&w);
				label[i][j].setText(QString::number(solver.matrix[i][j], 10));
				label[i][j].setAlignment(Qt::AlignCenter);
				label[i][j].setGeometry(5 + j*width, 5 + i*height, width, height);
				label[i][j].setStyleSheet("border:2px solid gray;");
				label[i][j].show();
			}
	}
	QLabel result("result", &w);
	result.setGeometry(5 + 2 * width, 5 + matrixLen*height, width, height / 2);
	result.show();
	QPushButton btn("submit", &w);
	btn.setGeometry(5 + 4 * width, 5 + matrixLen*height, width, height / 2);
	btn.show();
	solver.label = &result;
	QObject::connect(&btn, SIGNAL(clicked()), &solver, SLOT(update()));
	//QObject::connect(&btn, SIGNAL(clicked()), &app, SLOT(quit()));
	w.show();
	return app.exec();
}
