//
// Created by popovivan on 05.10.22.
//

#include "fun.h"
std::string get_dir_to_walk(int argc, char *argv[])
{
    std::string dir_to_walk = (argc == 1 || argv[1][0] == '-') ? "." : argv[1];
    if(dir_to_walk.back() == '/')
        dir_to_walk.pop_back();
    return dir_to_walk;
}
Flags parse_flags(int argc, char *argv[])
{
    Flags flags;
    int flag;
    bool is_any_flags{};
    while((flag = getopt(argc, argv, "ldfs")) != -1) {
        if (flag == 'l' || flag == 'd' || flag == 'f' || flag == 's') {
            is_any_flags = true;
            //break;
        }
        switch (flag) {
            case 'l':
                flags.l = true;
                break;
            case 'd':
                flags.d = true;
                break;
            case 'f':
                flags.f = true;
                break;
            case 's':
                flags.s = true;
                break;
            default:
                throw (std::runtime_error("No such flag"));
        }
    }
    if(!is_any_flags)
        flags.l = flags.d = flags.f = true;
    return flags;
}
File::File(int type, const std::string &name)
{
    this->name = name;
    switch(type)
    {
        case DT_DIR:
        {
            this->type = File::Type::DIR;
            break;
        }
        case DT_REG:
        {
            this->type = File::Type::FILE;
            break;
        }
        case DT_LNK:
        {
            this->type = File::Type::LINK;
            break;
        }
        default:
        {
            this->type = File::Type::etc;
            break;
        }
    }
}

void collect_files(std::string current_dir, std::vector<File> &files)
{
    DIR *dir = opendir((current_dir + "/").c_str());    // открыли
    if(!dir)    // проверка
    {
        if (errno == EACCES)
        {
            std::cout << "Cant open file: access error" << std::endl;
            return;
        }
        else
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }
    auto add_file = [&current_dir, &files](const dirent *content)//закинули найденый файл в список
    {
        files.emplace_back(content->d_type, current_dir + '/' + content->d_name);
    };
    dirent *file;
    while((file = readdir(dir)))
    {
        std::string name = file->d_name;
        if((name == "." || name == ".."))
            continue;
        add_file(file);
        if(file->d_type == DT_DIR)
            collect_files(current_dir + '/' + name, files);
    }
    closedir(dir);
}

void show_files(std::vector<File> &files, const Flags &flags)
{
    if(flags.s)
        std::sort(files.begin(), files.end());
    std::cout << std::setw(30) << std::left << "File name: " << std::endl;
    for (const auto &file: files)
        if (parse_out(file, flags))
            std::cout << std::setw(30) << std::left << file.name << std::endl;
}

bool operator<(const File &first_file, const File &second_file)
{
    return std::tie(first_file.type, first_file.name) < std::tie(second_file.type, second_file.name);
}
bool parse_out(const File &file, const Flags &flags)
{
    switch (file.type) {
        case File::DIR: std::cout << "\033[1;34m";
            return flags.d;
        case File::LINK: std::cout << "\033[1;36m";
            return flags.l;
        case File::FILE: std::cout <<  "\033[0m";
            return flags.f;
        default: std::cout << "\033[1;31m";
            return false;
    }
}