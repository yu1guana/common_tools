#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace Hoge {

//] This file describes the Parameters class.
//] This class has the below member variables and methods.
//]
//] Variables (@: private member )
//] ==============================
//]   | Type                  | Name
//] --|-----------------------|------------------------------
//]   | static constexpr int  | num_parameters
//]   | static constexpr char | comment_line_symbol
//]   | int                   | param_1
//]   | int                   | param_2
//]   | std::string           | fileName_1
//] --|-----------------------|------------------------------
//]
//] Methods (@: private member )
//] ============================
//]   | Type              | Methods name | Arguments
//] --|-------------------|--------------|-----------------------------------------------------
//]   |                   | Parameters   |
//]   |                   | Parameters   | const int param_1_arg
//]   |                   |              | const int param_2_arg
//]   |                   |              | const std::string fileName_1_arg
//]   |                   | Parameters   | const std::string fileName_parammeters
//] --|-------------------|--------------|-----------------------------------------------------
//]   | void              | ReadFile     | const std::string fileName_parammeters
//] --|-------------------|--------------|-----------------------------------------------------
//]
//]
//] The example of parameters file is as follows
//] The function 'ReadFile' ignores blank lines and lines with
//] starting from the character which is determined by the
//] variable 'comment_line_symbol'.
//]
//] parameters_tmp.txt
//] =====================
//] param_1 10
//] param_2 4
//] fileName_1 temp.txt
//] =====================

class Parameters {
  public:
    //] Variables
    static constexpr int num_parameters = 3;
    static constexpr char comment_line_symbol = '#';
    int param_1;
    int param_2;
    std::string fileName_1;

    //] Constructor
    Parameters()
      :param_1(0),
       param_2(0),
       fileName_1("")
    {}

    //] Constructor
    Parameters( const int param_1_arg,
                const int param_2_arg,
                const int num_generations_arg,
                const std::string fileName_1_arg)
      :param_1(param_1_arg),
       param_2(param_2_arg),
       fileName_1(fileName_1_arg)
    {}

    //] Constructor
    Parameters( const std::string fileName_parammeters ) {
      ReadFile( fileName_parammeters );
    }

    //] Read parameters file
    void ReadFile( const std::string fileName_parammeters ) {
      int count_parameters = 0;
      bool flag_err = 0;
      int line_number = 0;
      //] Open a file
      std::ifstream ifs_parameters( fileName_parammeters );
      if ( !ifs_parameters ) {
        std::cerr << "Error: cannot open the file '" << fileName_parammeters << "'." << std::endl;
        exit(EXIT_FAILURE);
      }
      //] Read lines
      std::string oneline;
      while ( ifs_parameters ) {
        //] Get a line number
        line_number++;
        //] Read one line
        std::getline(ifs_parameters, oneline);
        std::istringstream iss_buff(oneline);
        std::string parameter_name;
        iss_buff >> parameter_name;
        //] Read a parameter
        if ( parameter_name == "param_1" ) {
          //] Param_1
          count_parameters++;
          iss_buff >> param_1;
          if ( param_1 <= 0 ) {
            std::cerr << "Error: The " << line_number <<"-th line in '" << fileName_parammeters << "'." << std::endl;
            std::cerr << "       param_1 must be positive." << std::endl;
            std::cerr << "       param_1 = " << param_1 << "." << std::endl;
            flag_err = 1;
          }
        } else if ( parameter_name == "param_2" ) {
          //] param_2
          count_parameters++;
          iss_buff >> param_2;
          if ( param_2 < 0 ) {
            std::cerr << "Error: The " << line_number <<"-th line in '" << fileName_parammeters << "'." << std::endl;
            std::cerr << "       param_2 must not be negative." << std::endl;
            std::cerr << "       param_2 = " << param_2 << "." << std::endl;
            flag_err = 1;
          }
        } else if ( parameter_name == "fileName_1" ) {
          //] fileName_1
          count_parameters++;
          iss_buff >> fileName_1;
        } else if ( parameter_name.empty() ) {
          //] Blank line
        } else if ( parameter_name.front() == comment_line_symbol ) {
          //] Comment line
        } else {
          //] Others
          std::cerr << "Error: The " << line_number <<"-th line in '" << fileName_parammeters << "'." << std::endl;
          std::cerr << "       '" << parameter_name << "' is a wrong parameter." << std::endl;
          flag_err = 1;
        }
      }
      //] Close a file
      ifs_parameters.close();
      //] Check the number of parameters
      if ( count_parameters != num_parameters ) {
        std::cerr << "Error: In the file '" << fileName_parammeters << "'." << std::endl;
        std::cerr << "       The number of parametes is wrong." << std::endl;
        flag_err = 1;
      }
      //] Check other errors
      if ( param_1 <= param_2 ) {
        std::cerr << "Error: In the file '" << fileName_parammeters << "'." << std::endl;
        std::cerr << "       param_2 must be param_2 < param_1." << std::endl;
        std::cerr << "       param_2 = " << param_2 << "." << std::endl;
        std::cerr << "       param_1 = " << param_1 << "." << std::endl;
        flag_err = 1;
      }
      //] Error check
      if ( flag_err ) {
        exit(EXIT_FAILURE);
      }
    }

};

} //] namespace Hoge
