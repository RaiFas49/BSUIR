//
// Created by popovivan on 05.10.22.
//

#ifndef DIRWALK_FUN_H
#define DIRWALK_FUN_H
#include <iostream>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <algorithm>
#include <iomanip>

struct Flags
{
    bool l{}, d{}, f{}, s{};
};
Flags parse_flags(int argc, char *argv[]);
struct File
{
    enum Type{DIR, LINK, FILE, etc} type{etc};
    std::string name;
    File(int type, const std::string &name);
};
std::string get_dir_to_walk(int argc, char *argv[]);
void collect_files(std::string current_dir, std::vector<File> &files);
void show_files(std::vector<File> &files, const Flags &flags);
bool operator<(const File &first_file, const File &second_file);
bool parse_out(const File &file, const Flags &flags);
#endif //DIRWALK_FUN_H
