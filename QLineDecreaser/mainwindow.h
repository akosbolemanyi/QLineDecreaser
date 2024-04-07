#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDialog>
#include <QGraphicsBlurEffect>
#include <QGroupBox>
#include <QDebug>
#include <QDateTime>
#include <QPixmap>
#include <QLineEdit>
#include <QDir>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void myfunction();

private slots:
    void on_actionMain_page_triggered();

    void on_actionProducts_triggered();

    void on_actionCart_triggered();

    void on_actionPay_triggered();

    void on_actionFeedback_triggered();

    void on_popcorn_clicked();

    void on_nachos_clicked();

    void on_coke_clicked();

    void on_zeroCoke_clicked();

    void on_popcornMenu_clicked();

    void on_nachosMenu_clicked();

    void on_viewCartItems_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushBackToMain_clicked();

    void on_pushBackToMain_3_clicked();

    void on_pushBackToMain_2_clicked();

    void on_pushBackToMain_4_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QDialog *dialog;
};
#endif // MAINWINDOW_H
