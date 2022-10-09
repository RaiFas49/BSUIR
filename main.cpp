#include "fun.h"

int main(int argc, char* argv[]) {
    //std::cout<<std::endl;
    //argv[1] = "/bin";
    //argv[2] = "-f";
    //argc = 3;
    //std::cout << *argv << std::endl;
    //std::cout << argv[1] << std::endl;
    //std::cout << argv[2] <<std::endl;
    //std::cout << argc <<std::endl;
    std::string dir = get_dir_to_walk(argc, argv);
    Flags flags = parse_flags(argc, argv);
    std::vector<File> files;
    collect_files(dir, files);
    show_files(files, flags);
    return 0;
}
