/*
On the website available at the address www.pmf.unizg.hr/math/djelatnici, there are data about employees and external associates of the Department of Mathematics, Faculty of Science. 
Save this web page as a file named djelatnici.html (or download it HERE). 
Then, using regular expressions, write a program that creates a directory of employees and external associates of the Department of Mathematics.
Specifically, the program must create a file named imenik.txt, where each line contains information about one employee 
or external associate in the following format: first their first and last name (without titles and other information), followed by a colon, and the associated email address of that employee or external associate. For example,

Sebastijan Horvat: sebastijan.horvat@math.hr
For employees or external associates whose email address is not listed on the website, do not save their information in the imenik.txt file.
You can see the expected content of the imenik.txt file HERE.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<regex>

using namespace std;

int main() {
    
    /*
        We transfer everything from the file into the string "ulaz"
        so we can apply functions from <regex>
    */
    ifstream dat("djelatnici.html");
    string ulaz, linija;
    while (getline(dat, linija))
        ulaz += linija + '\n';
    dat.close();

    /*
      - After much struggle and hardship, I noticed that the paragraphs
        containing contact information for each person are separated by "whitespace",
        in the HTML code, this is added as &nbsp;
      - This even exists for people where the contact is either missing or incomplete;
      - The EMAIL address is always between the 1st and 2nd occurrence of the '&' character, so I isolated that part
      - From the isolated part, I extracted the portion starting with ':' and ending with ", if it existed at all,
        and that was precisely the requested email address
      - When printing the address, it was also necessary to remove the first character because ':' was also read
    */
    string pattern = "\"person\">([^>]*)>([^<]*)([^&]*)&([^&]*)";
    regex regExpr(pattern);

    ofstream output("imenik.txt");

    sregex_iterator end_it;
    for(sregex_iterator it(ulaz.begin(), ulaz.end(), regExpr); it != end_it; ++it){
            
        string mail_pattern = ":([^\"]*)", s = it->str(4);
        regex regMail(mail_pattern);
        smatch result;
        if (regex_search(s, result, regMail))
            output << it->str(2) << ": " << result.str().substr(1) << endl;
    }

    output.close();

    return 0;
}
