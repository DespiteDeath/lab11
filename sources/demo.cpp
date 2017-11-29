#include <print.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <stdlib.h>

using namespace boost::program_options;

int main(int argc, char** argv) {
    
std::string text;
    
    try {
        options_description options_desc{"General options"}; //obj of options_description class
        //flags:
        options_desc.add_options()
        ("help,h", "Show help")
        ("output,o", value<std::string>(), "Output p");
        
        variables_map console;
        store(parse_command_line(argc, argv, options_desc), console); //parsing console
        notify(console);
        
        if(!getenv("HOME")){
            std::cout << "HOME not found - error" << std::endl;
            return 0;
        }
           
        std::string home_path = getenv("HOME");
        home_path += "/.config/demo.cfg";

        variables_map file;
        
        if(boost::filesystem::exists(home_path)) {
            store(parse_config_file<char>( home_path.c_str(), options_desc), file);
        }
        
        notify(file);
    
        if(console.count("help") || file.count("help")) {
            std::cout << options_desc << std::endl;
        }
        else if(console.count("output")) {
            std::ofstream out(console["output"].as<std::string>(), std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        }
        else if (getenv("DEMO_OUTPUT")) {
            std::cout << "env" << std::endl;
            std::string _trAdd = getenv("DEMO_OUTPUT");
            std::ofstream out(_trAdd, std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        }
        else if (file.count("output")) {
            std::cout << "Output in >> " << file["output"].as<std::string>() << std::endl;
            std::ofstream out(file["output"].as<std::string>(), std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        }
        else {
            std::cout << "DEFAULT" << std::endl;
            std::ofstream out("default.log", std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        }
    }
    catch (const error & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
