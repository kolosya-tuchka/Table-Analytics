#include "filters_controller.h"
#include "filter_exception.h"
#include <iostream>

filters_controller::filters_controller(QTableWidget* table, QMenu* table_menu, QWidget* view_parent)
{
    this->table_menu = table_menu;
    this->table = table;
    this->view_parent = view_parent;

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setDirection(QBoxLayout::RightToLeft);
    layout->addLayout(new QVBoxLayout(), 7);
    view_parent->setLayout(layout);

    manager = new filter_manager(this->table, this->view_parent);
    QWidget::connect(this->table->horizontalHeader(), &QHeaderView::customContextMenuRequested, [this](){
        if (this->table->rowCount() == 0) {
            return;
        }
        handle_filters_menu(this->table->selectedRanges()[0].leftColumn());
    });
    add_default_filters();
}

void filters_controller::handle_filters_menu(int col)
{
    for (auto& creator : creators) {
        QAction* action = creator.second->get_action();
        QWidget::connect(action, &QAction::triggered, [this, &creator, col]() {
            base_filter* filter = nullptr;
            try {
              filter = creator.second->create_filter();
            } catch(filter_exception* e) {
              QErrorMessage* err_msg = new QErrorMessage();
              err_msg->showMessage(e->what().c_str());
              err_msg->exec();
            }
            if (filter == nullptr) {
                return;
            }
            this->manager->add_filter(filter, col);
            this->add_filter_view(filter, creator.second, col);
        });
        table_menu->addAction(action);
      }
}

void filters_controller::reset()
{
  /*for (const auto& view : layout->children()) {
    view->deleteLater();
  }*/
}

void filters_controller::add_default_filters()
{
    creators["hard"] = (new hard_filter_creator(view_parent))->set_name("Жесткий фильтр")->set_short_name("=");
    creators["soft"] = (new soft_filter_creator(view_parent))->set_name("Мягкий фильтр")->set_short_name("~");
    creators["regex"] = (new regex_filter_creator(view_parent))->set_name("Регулярное выражение")->set_short_name("regex");
}

void filters_controller::add_filter_view(base_filter *filter, base_filter_creator *creator, int col)
{
    base_filter_view* view = creator->get_view();
    view->set_filter(filter);
    view->set_title(table->horizontalHeaderItem(col)->text());

    QHBoxLayout* layout = (QHBoxLayout*)view_parent->layout();
    QVBoxLayout* filter_layout = new QVBoxLayout();

    QWidget::connect(view->get_check_box(), &QCheckBox::stateChanged, [this, filter](){
        filter->enabled = !filter->enabled;
        this->manager->filter_all();
    });
    QWidget::connect(view->get_delete_button(), &QPushButton::pressed, [this, filter, col, view](){
        view->get_widget()->deleteLater();
        this->manager->remove_filter(filter, col);
    });
    QWidget::connect(view->get_data(), &QLineEdit::editingFinished, [this, view, filter, creator, col]() {
        this->manager->remove_filter(filter, col);
        base_filter *new_filter = creator->set_data(view->get_data()->text())->get_filter();
        this->manager->add_filter(new_filter, col);
        add_filter_view(new_filter, creator, col);
        view->get_widget()->deleteLater();
    });

    filter_layout->addWidget(view->get_widget());
    layout->addLayout(filter_layout, 0);
}
