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
    ui(new Ui::MainWindow), descriptorFilePath("Descriptors.json")
{
    ui->setupUi(this);
    loadDescriptors(descriptorFilePath);
    populateDescriptorsTable();
}

void MainWindow::loadDescriptors(const QString &filePath)
{
    QFile descriptorsFile(filePath);
    if(!descriptorsFile.open(QFileDevice::ReadWrite) || descriptorsFile.size() < 1)
    {
        descriptorsDocument = new QJsonDocument(QJsonArray());
        return;
    }
    QByteArray fileData = descriptorsFile.readAll();

    descriptorsDocument = new QJsonDocument(QJsonDocument::fromJson(fileData));
    descriptorsFile.close();
}

void MainWindow::populateDescriptorsTable()
{
    if(descriptorsDocument == 0 || descriptorsDocument->isEmpty())
        return;

    QJsonArray jsonData = descriptorsDocument->array();

    for(int i = 0; i < jsonData.size(); i++)
    {
        QJsonObject jsonObj = jsonData[i].toObject();
        addRowToTableView(jsonObj.value("name").toString(), "deerp");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete descriptorsDocument;
}


void MainWindow::on_ButtonDocumentCreate_clicked()
{


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
    QJsonObject descriptorObject;
    descriptorObject.insert("Descriptor Name", (findChild<QTextEdit*>("textEditDescriptorName"))->toPlainText());

    QJsonArray valueNameSpecs;

    QTableWidget* table = this->findChild<QTableWidget*>("tableWidget");
    QAbstractTableModel* model = dynamic_cast<QAbstractTableModel*>(table->model());
    QModelIndex indexer;
    for(int i = 0; i < model->rowCount(); i++)
    {
        float value = model->data(model->index(i,0)).toFloat();
        QString name = model->data(model->index(i,1)).toString();
        QJsonObject valueNameObject;
        valueNameObject.insert("name", name);
        valueNameObject.insert("value", QJsonValue(value));
        valueNameSpecs.append(valueNameObject);
    }
    descriptorObject.insert("ValueNameSpecs", valueNameSpecs);
    QJsonArray descriptor = descriptorsDocument->array();
    descriptor.append(descriptorObject);
    descriptorsDocument->setArray(descriptor);

    QFile descriptorFile(descriptorFilePath);
    if(!descriptorFile.open(QFileDevice::Truncate | QFileDevice::WriteOnly))
    {
        return;
    }
    QByteArray toWrite = descriptorsDocument->toJson();
    QString debugSize;
    debugSize.setNum(toWrite.size());
    descriptorFile.write(toWrite, toWrite.size());
    descriptorFile.close();



}
