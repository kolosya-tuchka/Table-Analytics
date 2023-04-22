#ifndef FILTERS_FACTORY_H
#define FILTERS_FACTORY_H

#include "hard_filter_creator.h"
#include "soft_filter_creator.h"
#include "regex_filter_creator.h"
#include "filter_exception.h"
#include "base_filter_view.h"
#include <QtWidgets>
#include "filter_manager.h"
#include <map>

class filters_controller
{
public:
    filters_controller(QTableWidget* table, QMenu* table_menu, QWidget* view_parent);
    void add_filter(base_filter* filter);
    void handle_filters_menu(int col);
    void reset();
private:
    void add_default_filters();
    void add_filter_view(base_filter* filter, base_filter_creator* creator, int col);

    std::map<std::string, base_filter_creator*> creators;
    filter_manager* manager;
    QTableWidget* table;
    QWidget* view_parent;
    QMenu* table_menu;
};

#endif // FILTERS_FACTORY_H
