#include "base_filter_view.h"
#include "filter_exception.h"
#include "codec.h"

base_filter_view::base_filter_view(QWidget *parent, base_filter* filter, std::string data)
{
    this->parent = parent;
    this->filter = filter;
    this->data = data;
    create_base();
    create();
}

base_filter_view::~base_filter_view()
{
    delete group_box;
    delete data_label;
    delete delete_button;
    delete enabled_check_box;
}

void base_filter_view::create_base()
{
    const auto codecs = codec::get_codec();
    group_box = new QGroupBox(parent);

    if (filter != nullptr) {
        group_box->setTitle(codecs->toUnicode(filter->get_name().c_str()));
    }

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    data_label = new QLineEdit();
    data_label->setText(codecs->toUnicode(data.c_str()));
    enabled_check_box = new QCheckBox();
    enabled_check_box->setCheckState(Qt::Checked);
    delete_button = new QPushButton();
    delete_button->setText("X");
    layout->addWidget(data_label, 4);
    data_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(enabled_check_box, 1);
    layout->addWidget(delete_button, 1);
    group_box->setLayout(layout);
}

void base_filter_view::set_data(std::string data) {
    this->data = data;
    data_label->setText(codec::get_codec()->toUnicode(this->data.c_str()));
}

void base_filter_view::set_filter(base_filter *filter)
{
    this->filter = filter;
    this->group_box->setTitle(codec::get_codec()->toUnicode(this->filter->get_name().c_str()));
}

void base_filter_view::set_title(QString title)
{
    group_box->setTitle(title);
}

QWidget *base_filter_view::get_widget()
{
    return group_box;
}

const QCheckBox *base_filter_view::get_check_box()
{
    return enabled_check_box;
}

const QPushButton *base_filter_view::get_delete_button()
{
  return delete_button;
}

const QLineEdit *base_filter_view::get_data()
{
  return data_label;
}

void base_filter_view::create(){}
