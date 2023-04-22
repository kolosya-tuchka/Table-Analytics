#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include "csv_config.h"
#include "csv_reader.h"
#include "filters_controller.h"
#include <vector>
#include "Timeline/timeline.h"
#include "Timeline/GraphicsView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadTable();
    void SaveTable();
    void HandleTableContextMenu(QPoint qpos);
    void WritePrefix(int col);
    void Unite();
    void AddResource();
private:
    void SetTable(std::string path, csv_config config);

    Ui::MainWindow *ui;
    QMenu* table_menu;
    csv_reader *csv;
    const QTextCodec *codec = QTextCodec::codecForName("cp1251");
    filters_controller *filters;
    TimeLine* timeline;
    GraphicsView* view;
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
