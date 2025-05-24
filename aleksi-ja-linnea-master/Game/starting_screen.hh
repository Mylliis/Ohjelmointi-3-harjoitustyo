#ifndef STARTING_SCREEN_HH
#define STARTING_SCREEN_HH

#include <QDialog>

namespace Ui {
class Starting_screen;
}

class Starting_screen : public QDialog
{
    Q_OBJECT

public:
    explicit Starting_screen(QWidget *parent = 0);
    ~Starting_screen();

signals:
    void sendValue(QString player_1, QString player_2);
    void accepted();

public slots:
    void on_pushButton_clicked();

private slots:
    void on_help_btn_clicked();

private:
    Ui::Starting_screen *ui;
};

#endif // STARTING_SCREEN_HH
