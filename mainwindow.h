#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void on_NodeEditorTabs_state_row_add_clicked();
    void on_ButtonDocumentCreate_clicked();
    
private slots:


    void on_actionFilters_triggered();

    void on_saveDescriptorButton_clicked();

private:

    QString descriptorFilePath;

    Ui::MainWindow *ui;
    QJsonDocument* descriptorsDocument;

    void addRowToTableView(const QString& value, const QString& name);
    /**
     * @brief loadDescriptors loads descriptors into descriptorsDocument.
     * @param filePath [in] the path to the file to read from.
     *  Attempts to load the given descriptor file into a QJsonDocument.
     *  Creates an empty file and document if the given path is not valid.
     */
    void loadDescriptors(const QString& filePath);
    /**
     * @brief populateDescriptorsTable populates descriptors ui with data from descriptorsDocument.
     */
    void populateDescriptorsTable();


};

#endif // MAINWINDOW_H
