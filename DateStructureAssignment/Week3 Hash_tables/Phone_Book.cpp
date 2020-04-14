#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query
{
    string type, name;
    int* number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    static vector<int> t(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;

        if (queries[i].type == "add")
        {
            cin >> t[i] >> queries[i].name;
            queries[i].number = &t[i];
        }
        else
            cin >> t[i];
        queries[i].number = &t[i];
    }
    return queries;
}

void write_responses(const vector<string>& result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
            //cpp vector resize if the num does not exist
            if(*queries[i].number >= contacts.size())
            {
                contacts.resize(*(queries[i].number) + 1);
            }
            // if we already have contact with such number,
            // we should rewrite contact's name
            contacts[*queries[i].number].number = queries[i].number;
            contacts[*queries[i].number].name = queries[i].name;
        }
        else if (queries[i].type == "del")
        {
            if(*(queries[i].number) +1 <= contacts.size())//Only dele when the query is within the range
            {
                //std::cout << "Deleting " <<*queries[i].number<< std::endl;
                if (contacts[*queries[i].number].number == nullptr){
                    //std::cout << "Nothing to delete " << std::endl;
                }
                else if(*contacts[*queries[i].number].number == *queries[i].number)//Only dele when the num does exist
                {
                    //std::cout << "Really Gonna Delete " << *queries[i].number << std::endl;
                    contacts[*queries[i].number].number = nullptr;
                    contacts[*queries[i].number].name = std::string();
                }
            }
        }
        else
        {
            // "find"
            string response = "not found";
            if(contacts.empty()){
                result.push_back(response);
            }
            else if(contacts[*queries[i].number].number == nullptr)
            {
                result.push_back(response);
            }
            else if(*contacts[*queries[i].number].number == *queries[i].number)
            {
                response = contacts[*queries[i].number].name;
                result.push_back(response);
            }
        }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}

