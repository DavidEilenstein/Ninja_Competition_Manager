#ifndef NCM_MAINWINDOW_H
#define NCM_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class NCM_MainWindow; }
QT_END_NAMESPACE

class NCM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NCM_MainWindow(QWidget *parent = nullptr);
    ~NCM_MainWindow();

private:
    Ui::NCM_MainWindow *ui;
};
#endif // NCM_MAINWINDOW_H
