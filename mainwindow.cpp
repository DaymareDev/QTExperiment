#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QJsonDocument>
#include <QTCore/QJsonObject>
#include <QTcore/QJsonArray>
#include <QTcore/QJsonValue>
#include <QTCore/QJsonValueRef>
#include <QTextEdit>
#include <QStandardItem>
#include <QAbstractTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDescriptors("Descriptors.json");
    populateDescriptorsTable();
}

void MainWindow::loadDescriptors(const QString &filePath)
{
    QFile descriptorsFile(filePath);
    if(!descriptorsFile.open(QFileDevice::ReadWrite))
    {
        return;
    }
    QByteArray fileData = descriptorsFile.readAll();
    descriptorsDocument = new QJsonDocument(QJsonDocument::fromJson(fileData));
    descriptorsFile.close();
}

void MainWindow::populateDescriptorsTable()
{

}

MainWindow::~MainWindow()
{
    delete ui;
    delete descriptorsDocument;
}


void MainWindow::on_ButtonDocumentCreate_clicked()
{
    QFile toCreate("Test.json");
    if(!toCreate.open(QFileDevice::Truncate | QFileDevice::WriteOnly))
    { 
        return;
    }

    QJsonObject obj;

    const QJsonValue value(12);

    obj.insert("DerpTest", value);
    QJsonDocument doc(obj);
    QByteArray binary = doc.toJson();
    toCreate.write(binary);

    toCreate.close();





}

void MainWindow::on_actionFilters_triggered()
{

}

void MainWindow::on_NodeEditorTabs_state_row_add_clicked()
{
    QTextEdit* valueField = this->findChild<QTextEdit*>("textEditStateValueMap");
    QTextEdit* nameOfValue = this->findChild<QTextEdit*>("textEditStateName");
    addRowToTableView(QString(valueField->toPlainText()), QString(nameOfValue->toPlainText()));
}

void MainWindow::addRowToTableView(const QString& value, const QString& name)
{
    QTableWidget* table = this->findChild<QTableWidget*>("tableWidget");

    QAbstractTableModel* model = dynamic_cast<QAbstractTableModel*>(table->model());
    model->insertRow(model->rowCount());
    int rowIndex = model->rowCount()-1;
    QModelIndex index;
    index = model->index(rowIndex,0);
    model->setData(index, QVariant::fromValue(value));
    index = model->index(rowIndex,1);
    model->setData(index,QVariant::fromValue(name));

}



void MainWindow::on_saveDescriptorButton_clicked()
{
    QTableWidget* table = this->findChild<QTableWidget*>("tableWidget");
    QAbstractTableModel* model = dynamic_cast<QAbstractTableModel*>(table->model());

}
