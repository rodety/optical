#ifndef CONFIGPROGRAM_H
#define CONFIGPROGRAM_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class ConfigProgram;
}

class ConfigProgram : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigProgram(QWidget *parent = 0);
    ~ConfigProgram();

    QWidget *login;
    void setWidgetLogin(QWidget *w);
    void setHostName(QString str);
    void setDatabase(QString str);
    void setName(QString str);
    void setPass(QString str);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ConfigProgram *ui;
};

#endif // CONFIGPROGRAM_H
