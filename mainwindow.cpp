#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csv_reader.h"
#include <vector>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>
#include <QTextCodec>
#include <QInputDialog>
#include <functional>
#include <set>
#include "csv_writer.h"
#include <fstream>
#include <windows.h>
#include "codec.h"
#include "Timeline/Track.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table_menu = new QMenu();

    connect(ui->loadTable, &QAction::triggered, [this](){LoadTable();});
    connect(ui->saveTable, &QAction::triggered, [this](){SaveTable();});
    ui->tableWidget->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::customContextMenuRequested, this, &MainWindow::HandleTableContextMenu);
    filters = new filters_controller(ui->tableWidget, table_menu, ui->filtersBox);

    setLocale(QLocale::Russian);
    SetConsoleCP(1251);
    std::setlocale(LC_ALL, "ru");

    scene = new QGraphicsScene();
    view = new GraphicsView(scene);
    scene->setSceneRect(360,0, 360, 180);
    view->scale(1, 1);
    timeline = new TimeLine(view);

    view->setInteractive(true);
    view->setMouseTracking(true);
    view->setFocus();

    ui->verticalLayout_4->addWidget(view);
    connect(ui->addResource, &QAction::triggered, [this]() {
        AddResource();
      }
    );

    ui->dockWidget_4->hide();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete timeline;
    delete ui;
    delete csv;
    delete table_menu;
    delete filters;
}

void MainWindow::WritePrefix(int column) {
  set<int> cols;

  const auto& ranges = ui->tableWidget->selectedRanges();
  for (const auto& col : ranges) {
      cols.insert(col.leftColumn());
  }
  QString delim = QInputDialog::getText(this, codec->toUnicode("Ввод разделителя"), codec->toUnicode("Введите разделитель для объединения"), QLineEdit::Normal, "/");
  for (auto col = cols.begin(); col != cols.end(); ++col) {
      QString curHeaderText = ui->tableWidget->horizontalHeaderItem(*col)->text();
      for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
          QTableWidgetItem* item = ui->tableWidget->item(row, *col);
          item->setText(curHeaderText + delim + item->text());
      }
  }
}

void MainWindow::Unite() {
    set<int> cols;

    const auto& ranges = ui->tableWidget->selectedRanges();
    for (const auto& col : ranges) {
        cols.insert(col.leftColumn());
    }
    QString delim = QInputDialog::getText(this, codec->toUnicode("Ввод разделителя"), codec->toUnicode("Введите разделитель для объединения"), QLineEdit::Normal, "/");
    auto col = cols.begin();
    int firstCol = *col;
    ++col;
    for (; col != cols.end(); ++col) {
        QTableWidgetItem* header = ui->tableWidget->horizontalHeaderItem(firstCol);
        QString curHeaderText = ui->tableWidget->horizontalHeaderItem(*col)->text();
        header->setText(header->text() + delim + curHeaderText);
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QString text = ui->tableWidget->item(row, *col)->text();
            QTableWidgetItem* item = ui->tableWidget->item(row, firstCol);
            item->setText(item->text() + delim + text);
        }
    }
    for (col = --cols.end(); col != cols.begin(); --col) {
        ui->tableWidget->removeColumn(*col);

      }
}

void MainWindow::AddResource()
{
    QString text = QInputDialog::getText(this, codec->toUnicode("Ввод текста"), codec->toUnicode("Введите текст ресурса"), QLineEdit::Normal, codec->toUnicode("Ресурс"));

    QString headers[3] = {"Ресурс", "x", "y"};
    for (int i = 0; i < 3; ++i) {
        if (i == ui->tableWidget->columnCount()) {
            ui->tableWidget->insertColumn(i);
            ui->tableWidget->horizontalHeaderItem(i)->setText(headers[i]);
        }
    }

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int row = ui->tableWidget->rowCount() - 1;
    for (int i = 0; i < 3; ++i) {
        ui->tableWidget->setItem(row, i, new QTableWidgetItem());
    }
    Track* track = new Track(200, QColor(Qt::cyan), scene, text);
    scene->addItem(track);
    track->setPos(QPointF(300,0));

    ui->tableWidget->item(row, 0)->setText(text);
    ui->tableWidget->item(row, 1)->setText(to_string((int)track->pos().x()).c_str());
    ui->tableWidget->item(row, 2)->setText(to_string((int)track->pos().y()).c_str());
    connect(track, &Track::sendMouseMoveEventSignal, [this, row, track]() {
        this->ui->tableWidget->item(row, 1)->setText(to_string((int)track->pos().x()).c_str());
        this->ui->tableWidget->item(row, 2)->setText(to_string((int)track->pos().y()).c_str());
    });
}

void MainWindow::HandleTableContextMenu(QPoint qpos) {
    int col = ui->tableWidget->indexAt(qpos).column();
    if (ui->tableWidget->selectedRanges().count() <= 1) {
        ui->tableWidget->selectColumn(col);
    }
    table_menu->clear();
    QAction* unite = new QAction(codec->toUnicode("Объединить"), this);
    QAction* writePrefix = new QAction(codec->toUnicode("Прописать"), this);
    table_menu->addAction(unite);
    table_menu->addAction(writePrefix);

    connect(writePrefix, &QAction::triggered, [this, col](){WritePrefix(col);});
    connect(unite, &QAction::triggered, this, &MainWindow::Unite);

    unite->setEnabled(ui->tableWidget->selectedRanges().size() > 1);
    table_menu->popup(ui->tableWidget->horizontalHeader()->viewport()->mapToGlobal(qpos));
}

void MainWindow::SetTable(std::string path, csv_config config){
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    csv = new csv_reader(codec::get_codec()->toUnicode(path.c_str()).toLocal8Bit(), config);
    csv->open();

    ifstream input;
    input.open(path);

    if (*csv) {
        vector<string> headerRow;
        *csv >> headerRow;
        ui->tableWidget->setColumnCount(headerRow.size());
        QStringList qstrList;
        for (auto str : headerRow) {
            qstrList.append(codec->toUnicode(str.c_str()));
        }
        ui->tableWidget->setHorizontalHeaderLabels(qstrList);
    }
    int row = 0;
    while (*csv) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        vector<string> temp;
        *csv >> temp;

        for (int col = 0; col < temp.size(); ++col) {
            if (col > ui->tableWidget->columnCount()) {
                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
            }

            QTableWidgetItem* item = new QTableWidgetItem();
            QString qstr = codec->toUnicode(temp[col].c_str());
            item->setText(qstr);
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
    delete csv;
}

void MainWindow::LoadTable() {
    QFileDialog fileDialog;
    fileDialog.setNameFilter("CSV (*.csv)");
    QString filename = fileDialog.getOpenFileName(this, codec->toUnicode("Выберите таблицу"), "", "CSV (*.csv)");
    if (filename == "") {
        return;
    }
    SetTable(filename.toStdString(), csv_config());
}

void MainWindow::SaveTable() {
    QFileDialog fileDialog;
    fileDialog.setNameFilter("CSV (*.csv)");
    QString filename = fileDialog.getSaveFileName(this, codec->toUnicode("Выберите таблицу"), "", "CSV (*.csv)");
    if (filename == "") {
        return;
    }

    csv_writer csv;
    csv.open(filename.toLocal8Bit());

    vector<string> curRow;
    int colCount = ui->tableWidget->columnCount();
    for (int col = 0; col < colCount; ++col) {
        curRow.push_back(ui->tableWidget->horizontalHeaderItem(col)->text().toLocal8Bit().toStdString());
    }
    string* last = &curRow[curRow.size() - 1];
    *last = last->substr(0, last->size());
    csv << curRow;
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        if (ui->tableWidget->isRowHidden(row)) {
            continue;
        }

        curRow.clear();
        for (int col = 0; col < colCount; ++col) {
            curRow.push_back(ui->tableWidget->item(row, col)->text().toLocal8Bit().toStdString());
        }
        string* last = &curRow[curRow.size() - 1];
        *last = last->substr(0, last->size() - 1);
        csv << curRow;
    }
    csv.close();
}
