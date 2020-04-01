#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using std::string;
typedef unsigned long long ull;

struct Data
{
    string pattern, text;
};

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input)
{
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    const int x = 256;
    const int p = 31;
    int h = 1;
    int pat_hval = 0;//patteren hash value
    int t_haval = 0;//input text hash value
    for(int i=0; i< s.length()-1; i++)
    {
        h = (h*x)% p;//will never be negative, thus no need to "+ p"
    }
    std::cout << "The h value is: "<< h<< "\n";
    //First Window Hash value
    for(int i = 0; i < s.length(); i++)
    {
        pat_hval = ((x*pat_hval + s[i])% p + p)%p;
        t_haval = ((x*t_haval + t[i])%p + p)%p;
    }
    std::cout << pat_hval << "\n";
    std::cout << t_haval<< "\n";
    std::cout << "There r " << t.length()-s.length()+1<<" windows"<< "\n";
    //Slide every window
    for(int i = 0; i <= t.length()-s.length(); i++)
    {
        if(pat_hval == t_haval)
        {
            std::cout <<  "Hash Value the same"<< "\n";
            //Check every char
            int j;
            for(j = 0; j <s.length(); j++)
            {
                if(t[i+j] != s[j])
                    break;
            }
            if(j == s.length())
                ans.push_back(i);//if reach to the end --- patteren = txt.substring
        }
        //Next Window, compute the hash value
        if(i < t.length()-s.length() )
        {
            std::cout << "The head char: "<< int(t[i])<< "\n";
            std::cout << "The tail char: "<< int(t[i+s.length()])<< "\n";
            t_haval = (((t_haval - t[i]*h)*x + t[i+s.length()])%p + p) % p;//Update txt hash value
            std::cout << "The new txt hash value is "<<t_haval<< "\n";
        }
    }

    return ans;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
