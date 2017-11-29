#include <print.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, const char* argv[]) {

    std::string text;
    std::string filename;  //filename including directory
    std::string configname(std::getenv("HOME"));  //config filename including directory
    configname += "/.config/demo.cfg";

    po::options_description options("Command line options");
    options.add_options()
            ("help,h", "print help message")
            ("output", po::value<std::string>(), "file to print to");

    std::ifstream config(configname);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, options), vm);
    po::store(po::parse_environment(options, "DEMO_"), vm);
    po::store(po::parse_config_file(config, options), vm);
    po::notify(vm);

    config.close();

    if (vm.count("help") != 0)
    {
        std::cout << options << std::endl;
        return 1;
    }

    std::string tmp;
    while(std::cin >> tmp)
    {
        text += tmp;
        if(!std::cin.eof())
        {
            text += " ";
        }
    }

    if(vm.count("output") != 0)
    {
        std::ofstream out(vm["output"].as<std::string>());
        print(text, out);
        out.close();
    } else {
        std::ofstream out("default.log");
        print(text, out);
        out.close();
    }

    return 0;
}
