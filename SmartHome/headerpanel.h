#ifndef HEADERPANEL_H
#define HEADERPANEL_H

#include <QWidget>

#include "pagebrowser.h"
#include "automation.h"

namespace Ui {
class HeaderPanel;
}

class HeaderPanel : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderPanel(QWidget *parent = 0);
    ~HeaderPanel();
    void changeWidgets(const char *trend = NULL, const char *icon = NULL, const char *back = NULL, const char *title = NULL);
    void updateWidgets(const QString datetime = (const char *)NULL);

protected slots:
    bool goto_page(const char *page, bool remember = true);

private slots:
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_trend_clicked() { goto_trend_page(trend.toLatin1().data()); }

signals:
    void newPage(const char * pagename, bool remember);

private:
    Ui::HeaderPanel *ui;
    page *pparent;
    QString trend;
};

#endif // HEADERPANEL_H
