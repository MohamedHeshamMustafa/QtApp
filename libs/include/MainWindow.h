#pragma once
// QT
#include <QMainWindow>
#include <QGridLayout>
#include <QTextEdit>
#include <qsplitter.h>
#include <qtreeview.h>

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void setupLayout();
    void setupMenuBar();
    void setupFileViewer();
    void setupEditViewer();
    void setupSelectionViewer();
    void setupFindViewer();
    void setupHelpViewer();

public:
    //File Functions
    void onNewFileTriggered();
    void onOpenFileTriggered();
    void onOpenFolderTriggered();
    void OnExitTriggered();
    //Edit Functions
    void onCopyTriggered();
    void onCutTriggered();
    void onpasteTriggered();

private:
    //File
    QAction* _NewFile;
    QAction* _openFile;
    QAction* _openFolder;
    QAction* _exit;
    //Edit
    QAction* _copyText;
    QAction* _PasteText;
    QAction* _cutText;

    
    

private:
    QTextEdit* _textWidget;
    QWidget* _centralWidget;
    QGridLayout* _gridLayout;
    QSplitter* _widgetsplitter;
    QTreeView* _settingsWidget;
   




};