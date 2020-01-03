#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class Bayan
{
    std::vector<std::string> m_inputdir;
    std::vector<std::string> m_outputdir;
    int m_levelscan;
    int m_minfilesize;
    std::vector<std::string> m_maskname;
    int m_blocksize;
    enum algorithm {crc32, md5};
    algorithm m_alorithm = md5;

public:
    void enterdir(std::string _dir) {
        m_inputdir.push_back(_dir);
    }

    void outdir(std::string _dir) {
        m_outputdir.push_back(_dir);
    }

    void levelscan(int _level) {
        m_levelscan = _level;
    }

    void minfilesize(int _minsize) {
        m_minfilesize = _minsize;
    }

    void maskname(std::string _mask) {
        m_maskname.push_back(_mask);
    }

    void blocksize(int _blocksize) {
        m_blocksize = _blocksize;
    }

    void choicealgocrc32() {
        m_alorithm = crc32;
    }

    void choicealgomd5() {
        m_alorithm = md5;
    }

    void print() {
        std::cout << "INPUTDIR: \n";
        for (auto var : m_inputdir) {
            std::cout << var << std::endl;
        }
        std::cout << "OUTPUTDIR: \n";
        for (auto var : m_outputdir) {
            std::cout << var << std::endl;
        }
        std::cout << "level scan = " << m_levelscan << std::endl;
        std::cout << "minfilesize = " << m_minfilesize << std::endl;
        std::cout << "MASK: \n";
        for (auto var : m_maskname) {
            std::cout << var << std::endl;
        }
        std::cout << "block size = " << m_blocksize << std::endl;
        std::cout << "algo = " << m_alorithm << std::endl;
    }


};

int main(int ac, char *av[])
{
    try
    {
        Bayan bayans;

        po::options_description generic("Generic options");
        generic.add_options()
            ("input,i", po::value<std::vector<std::string>>()->multitoken(), "enter input dir")
            ("output,o", po::value<std::vector<std::string>>()->multitoken(), "enter output dir")
            ("levelscan,l", po::value<int>()->default_value(0), "enter level scan, default 0 (0 - this dir)")
            ("minsize,m", po::value<int>()->default_value(1), "enter minimum size of file, default 1")
            ("mask", po::value<std::vector<std::string>>()->multitoken(), "enter file name mask")
            ("block,b", po::value<int>()->default_value(1), "enter block size")
            ("crc32", "crc32 algorithm")
            ("md5", "md5 algorithm")
            ("version,v", "print version string")
            ("help,h", "produce help message")
            ;

        po::options_description cmdline_options;
        cmdline_options.add(generic);

        po::positional_options_description p;
        //p.add("input-file", -1);

        po::variables_map vm;
        store(po::command_line_parser(ac, av).options(cmdline_options).positional(p).run(), vm);

        if (vm.count("input")) {
            for (auto var : vm["input"].as<std::vector<std::string>>())
                  bayans.enterdir(var);
        }

        if (vm.count("output")) {
            for (auto var : vm["output"].as<std::vector<std::string>>())
                  bayans.outdir(var);
        }

        if (vm.count("levelscan")) {
            bayans.levelscan(vm["levelscan"].as<int>());
        }

        if (vm.count("minsize")) {
            bayans.minfilesize(vm["minsize"].as<int>());
        }

        if (vm.count("mask")) {
            for (auto var : vm["mask"].as<std::vector<std::string>>())
                  bayans.maskname(var);
        }

        if (vm.count("block")) {
            bayans.blocksize(vm["block"].as<int>());
        }

        if (vm.count("crc32")) {
            bayans.choicealgocrc32();
        }

        if (vm.count("md5")) {
            bayans.choicealgomd5();
        }

        if (vm.count("help")) {
            std::cout << generic;
            return 0;
        }

        if (vm.count("version")) {
            std::cout << "version 1.0\n";
            return 0;
        }

        bayans.print();

    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}








