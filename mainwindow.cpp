#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Paper Stack");
    auto mainLayout = new QHBoxLayout(this);
    auto formsLayout = new QVBoxLayout(this);
    auto stackLayout = new QVBoxLayout(this);
    auto fileButtonsLayout = new QHBoxLayout(this);

    paperSheetForm = new PaperSheetForm("Paper Sheet", this);
    QObject::connect(paperSheetForm, &PaperSheetForm::objectSubmitted, this, &MainWindow::onPositionedPaperObjectSubmitted);
    paperPlateForm = new PaperPlateForm("Paper Plate", this);
    QObject::connect(paperPlateForm, &PaperSheetForm::objectSubmitted, this, &MainWindow::onPositionedPaperObjectSubmitted);
    statusLabel = new QLabel("Status: in balance", this);
    auto font = statusLabel->font();
    font.setPointSize(FONT_POINT_SIZE);
    statusLabel->setFont(font);

    formsLayout->addWidget(paperSheetForm);
    formsLayout->addWidget(createHLineSeparator());
    formsLayout->addWidget(paperPlateForm);
    formsLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    formsLayout->addWidget(createHLineSeparator());
    formsLayout->addWidget(statusLabel);
    mainLayout->addLayout(formsLayout);

    loadFromFileButton = new QPushButton("Load from file");
    loadFromFileButton->setFont(font);
    QObject::connect(loadFromFileButton, &QPushButton::clicked, this, &MainWindow::loadStackFromFile);
    saveToFileButton = new QPushButton("Save to file");
    saveToFileButton->setFont(font);
    QObject::connect(saveToFileButton, &QPushButton::clicked, this, &MainWindow::saveStackToFile);
    fileButtonsLayout->addWidget(loadFromFileButton);
    fileButtonsLayout->addWidget(saveToFileButton);

    stackView = new QListWidget(this);
    stackView->setMinimumWidth(400);
    removeTopItemButton = new QPushButton("Remove item from top", this);
    removeTopItemButton->setFont(font);
    QObject::connect(removeTopItemButton, &QPushButton::clicked, this, &MainWindow::onRemoveTopItemClicked);

    stackLayout->addLayout(fileButtonsLayout);
    stackLayout->addWidget(stackView);
    stackLayout->addWidget(removeTopItemButton);
    mainLayout->addLayout(stackLayout, 1);
    ui->centralwidget->setLayout(mainLayout);
    onStackContentsChanged();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onPositionedPaperObjectSubmitted(const std::shared_ptr<PositionedPaperObject> &object) {
    paperStack.add(object);
    stackView->insertItem(0, object->description());
    onStackContentsChanged();
}

void MainWindow::onRemoveTopItemClicked() {
    if(paperStack.getSize() == 0) {
        QMessageBox::warning(this, "Paper stack is empty", "Add some items before deleting them");
        return;
    }
    paperStack.pop();
    delete stackView->takeItem(0);
    onStackContentsChanged();
}

void MainWindow::loadStackFromFile() {
    auto fileName = QFileDialog::getOpenFileName(this, "Choose file with stack contents");
    try {
        paperStack = PaperStack::readFromFile(fileName);
    } catch (...) {
        QMessageBox::critical(this, "Error", "Could not load stack from file " + fileName);
        return;
    }
    stackView->clear();
    auto iterator = paperStack.iterator();
    while(iterator != nullptr) {
        stackView->addItem(iterator->getValue()->description());
        iterator = iterator->lowerElement();
    }
    onStackContentsChanged();
}

void MainWindow::saveStackToFile() {
    auto fileName = QFileDialog::getSaveFileName(this, "Choose destination to save stack contents");
    try {
        paperStack.writeToFile(fileName);
    } catch (...) {
        QMessageBox::critical(this, "Error", "Could not save stack to file " + fileName);
        return;
    }
}

void MainWindow::onStackContentsChanged() {
    if(paperStack.isInBalance()) {
        statusLabel->setText("Status: in balance");
        statusLabel->setStyleSheet("color: green;");
    } else {
        statusLabel->setText("Status: falls :(");
        statusLabel->setStyleSheet("color: red;");
    }
}

QWidget *MainWindow::createHLineSeparator() {
    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

