#ifndef HEADERPANEL_H
#define HEADERPANEL_H

#include <QWidget>

#include "pagebrowser.h"

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

protected slots:
    bool goto_page(const char *page, bool remember = true);

signals:
    void newPage(const char * pagename, bool remember);

private:
    Ui::HeaderPanel *ui;
    page *pparent;
};

#endif // HEADERPANEL_H
