#ifndef HEADERPANEL_H
#define HEADERPANEL_H

#include <QWidget>

namespace Ui {
class HeaderPanel;
}

class HeaderPanel : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderPanel(QWidget *parent = 0);
    ~HeaderPanel();
    void changeWidgets();
    void updateWidgets();

private:
    Ui::HeaderPanel *ui;
};

#endif // HEADERPANEL_H
