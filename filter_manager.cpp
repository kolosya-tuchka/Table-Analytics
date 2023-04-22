#include "filter_manager.h"
#include "filter_exception.h"
#include <exception>

filter_manager::filter_manager(QTableWidget* table, QWidget* parent)
{
    this->table = table;
    this->parent = parent;
}

void filter_manager::add_filter(base_filter* filter, unsigned int col)
{
    if (filter == nullptr) {
        return;
    }
    filters[col].insert(filter);
    filter_all();
}

void filter_manager::remove_filter(base_filter *filter, unsigned int col)
{

    for (auto cur_filter = filters[col].begin(); cur_filter != filters[col].end(); ++cur_filter) {
        if ((*cur_filter) == filter) {
            delete *cur_filter;
            filters[col].erase(cur_filter);
        }
    }
    filter_all();
}

void filter_manager::filter_all()
{
    if (table == nullptr) {
        throw new filter_exception("Table is null");
    }

    for (int row = 0; row < table->rowCount(); ++row) {
        bool filtered = true;

        for (const auto& filter : filters) {
            int col = filter.first;
            std::string text = table->item(row, col)->text().toStdString();
            for (const auto& cur_filter : filters[col]) {
                if (!cur_filter->enabled) {
                    continue;
                }

                if (!cur_filter->filter(text)) {
                    filtered = false;
                    break;
                }
            }
        }
        table->setRowHidden(row, !filtered);
    }
}


