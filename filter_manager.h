#ifndef FILTER_MANAGER_H
#define FILTER_MANAGER_H

#include "base_filter_creator.h"
#include "hard_filter_creator.h"
#include "soft_filter_creator.h"
#include "regex_filter_creator.h"
#include <set>
#include <map>
#include "base_filter_view.h"

class filter_manager
{
public:
    filter_manager(QTableWidget* table, QWidget* parent);
    void filter_all();
    void add_filter(base_filter* filter, unsigned int col);
    void remove_filter(base_filter* filter, unsigned int col);
private:
    std::map<int, std::set<base_filter*>> filters;

    QTableWidget* table;
    QWidget* parent;
};

#endif // FILTER_MANAGER_H
