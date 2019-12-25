#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int ac, char *av[])
{
    try
    {
        // Declare a group of options that will be allowed
        // only on the command line
        po::options_description generic("Generic options");
        generic.add_options()
            ("version,v", "print version string")
            ("help", "produce help message")
            ;

        po::options_description cmdline_options;
        cmdline_options.add(generic);

        po::positional_options_description p;
        //p.add("input-file", -1);

        po::variables_map vm;
        store(po::command_line_parser(ac, av).options(cmdline_options).positional(p).run(), vm);

        if (vm.count("help"))
        {
            std::cout << "Usage: " << av[0] << " [options] input-files\n";
            //std::cout << visible << "\n";
            return 0;
        }

        if (vm.count("version"))
        {
            std::cout << "Multiple sources example, version 1.0\n";
            return 0;
        }

    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}








