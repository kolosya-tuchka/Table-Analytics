#include "csv_writer.h"

csv_writer::csv_writer()
{
    file_path = "test_out.csv";
    config = csv_config(';', '\n', '"');
}

csv_writer::csv_writer(string file_path, vector<string> field_names, csv_config config)
{
    this->field_names = field_names;
    this->file_path = file_path;
    this->config = config;
}

csv_writer::~csv_writer()
{
    close();
}

void csv_writer::set_file_path(const char* file_path)
{
    if (!output.is_open()) {
        this->file_path = file_path;
    }
}

string csv_writer::get_file_path()
{
    return file_path;
}

void csv_writer::open()
{
    output.open(file_path);
    if (field_names.size() > 0) {
        (*this) << field_names;
    }
}

void csv_writer::open(const char* file_path)
{
    this->file_path = file_path;
    open();
}

void csv_writer::close()
{
    output.close();
}

bool csv_writer::do_need_escape(string str) {
    for (char c : str) {
        if (c == config.delim || c == config.escape || c == config.row_delim) {
            return true;
        }
    }
    return false;
}
