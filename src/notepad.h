#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void close();
//    void print();
    void exit();
    void copy();
    void cut();
    void paste();
    void undo();
    void redo();
//    void selectFont();
    void toggleFontBold();
    void toggleFontUnderline();
    void toggleFontItalic();
//    void about();
private:
    Ui::Notepad *ui;
    QString cfile;
};
#endif // NOTEPAD_H
