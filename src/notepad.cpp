#include "notepad.h"
#include "ui_notepad.h"
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionClose, &QAction::triggered, this, &Notepad::close);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::exit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::newDocument()
{
    cfile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::open()
{
    QString fname = QFileDialog::getOpenFileName(this, "Open a file");
    QFile file(fname);
    cfile=fname;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: "+file.errorString());
        return;
    }
    setWindowTitle(fname);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}
void Notepad::save()
{
    QString fname;
    if(cfile.isEmpty())
    {
        fname = QFileDialog::getSaveFileName(this, "Save");
        cfile=fname;
    }

    QFile file(cfile);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning","Cannot save file:"+ file.errorString());
        return;
    }
    setWindowTitle(cfile);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.close();
}
void Notepad::saveAs()
{
    QString fname;
    fname = QFileDialog::getSaveFileName(this,"Save");

    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }
    cfile=fname;
    setWindowTitle(cfile);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();
}
void Notepad::close()
{
    if(cfile.isEmpty()) return;
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this, "Close file","Do you want to close without saving?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        ui->textEdit->setText(QString());
        cfile=QString();
    }
    else{

    }
}
void Notepad::exit()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"Exit","Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);

    if(reply== QMessageBox::Yes)
    {
        QCoreApplication::quit();
    }
}
