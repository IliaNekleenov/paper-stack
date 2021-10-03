#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include "papersheetform.h"
#include "paperplateform.h"
#include "paperstack.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onPositionedPaperObjectSubmitted(const std::shared_ptr<PositionedPaperObject>& object);
    void onRemoveTopItemClicked();
    void loadStackFromFile();
    void saveStackToFile();

private:
    Ui::MainWindow *ui;
    QListWidget* stackView;
    PaperSheetForm* paperSheetForm;
    PaperPlateForm* paperPlateForm;
    QLabel* statusLabel;
    QPushButton* removeTopItemButton;
    QPushButton* loadFromFileButton;
    QPushButton* saveToFileButton;

    PaperStack paperStack;

    QWidget* createHLineSeparator();
    void onStackContentsChanged();
};
#endif // MAINWINDOW_H
