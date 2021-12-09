#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Reservation.h"
#include "exportexcelobjet.h"
#include <QFileDialog>
#include <QPrinter>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_4_clicked();

    void on_pushmod_2_clicked();

    void on_supp_clicked();

    void on_xl_clicked();

    void on_search_textEdited(const QString &arg1);

    void on_tri_clicked();

    void readfile();


    void on_tabWidget_2_currentChanged(int index);

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
    Reservation tmpres ;
};
#endif // MAINWINDOW_H
