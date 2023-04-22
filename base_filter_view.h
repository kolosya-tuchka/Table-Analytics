#ifndef BASE_FILTER_VIEW_H
#define BASE_FILTER_VIEW_H

#include <QWidget>
#include <QtWidgets>
#include "base_filter.h"

class base_filter_view
{
public:
    base_filter_view(QWidget* parent, base_filter* filter, std::string data = "filter");
    ~base_filter_view();
    virtual void set_data(std::string data);
    void set_filter(base_filter* filter);
    void set_title(QString title);

    QWidget* get_widget();
    const QCheckBox* get_check_box();
    const QPushButton* get_delete_button();
    const QLineEdit* get_data();
protected:
    std::string data;
    base_filter* filter;

    QGroupBox* group_box;
    QLineEdit* data_label;
    QPushButton* delete_button;
    QCheckBox* enabled_check_box;

    QWidget* parent;

    void create_base();
    virtual void create();
};

#endif // BASE_FILTER_VIEW_H
