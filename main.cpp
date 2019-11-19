#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <boost/program_options.hpp>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void remove_file(std::string &file_name, struct stat &buff, bool &R){
    if(buff.st_mode & S_IFDIR && R){
        auto res = remove(file_name.c_str());
        if (res != 0)
            std::cout << file_name << " is not empty directory" << std::endl;
    }

    else if(buff.st_mode & S_IFREG){
        remove(file_name.c_str());
    }

    else{
        std::cerr << "Can't remove directory " << file_name << std::endl;
    }
}

bool message(std::string &file_name){
    std::string answer;
    std::cout << "Remove " << file_name << " ? Write [y/Yes], [n/No] or [c/Cancel]" << std::endl;
    std::cin >> answer;
    return boost::iequals(answer, "y") or boost::iequals(answer, "yes");
}

int process_args(int argc, char* argv[], bool &R, bool &f, std::vector<std::string> &files_lst){

    namespace po = boost::program_options;

    try {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "produce help message")
                ("F,f", "Remove without message")
                ("remove_dir,R","Remove directories")
                ("input-file", po::value<std::vector<std::string>>(), "input file");

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: myrm [-h|--help] [-f] [-R] <file1> <file2> <file3> ...\n";
            std::cout << desc;
            return 1;
        }

        if (vm.count("remove_dir")) {
            R = true;
        }

        if (vm.count("F")) {
            f = true;
        }

        if (vm.count("input-file")) {
            files_lst = vm["input-file"].as< std::vector<std::string> >();
        }
    }

    catch (std::exception &e) {
        std::cout << e.what() << "\n";
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]) {

    bool R = false;
    bool f = false;
    std::vector<std::string> files_lst;
    struct stat buff{};

    auto res_args = process_args(argc, argv, R, f, files_lst);

    if (res_args == -1)
        return -1;

    else if (res_args == 1)
        return 0;

    for (auto &file_name: files_lst){
        if( stat(file_name.c_str(), &buff) == 0){
            if (!f){
                if (message(file_name))
                    remove_file(file_name, buff, R);
            }
            else
                remove_file(file_name, buff, R);
        }
        else
            std::cout << file_name << " don't exist" << std::endl;
    }

    return 0;
}