#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>

using namespace std;

bool verification_string_is_number(const string &str, int &decimal_number, int &decimal_position)
{
    for(int i = 0; i < str.size(); i++)
    {
        if (str[i] > '9' && str[i] < '0' && str[i] != '.')
        {
            return false;
        }
        else if (str[i] == '.')
        {
            decimal_number ++;
            decimal_position = i;
        }
    }
    if (decimal_number >=2)
    {
        return false;
    }
    return true;
}

void sub_number(const string &str, const int &decimal_position, string &integer_part, string &decimal_part)
{
    if (decimal_position == 0)
    {
        integer_part = "0";
        decimal_part = str.substr(1, str.size() - 1);
        if (decimal_part.size() == 0)
        {
            decimal_part = "0";
        }
    }
    else if (decimal_position == (str.size() -1))
    {
        integer_part = str.substr(0, str.size() - 1);
        decimal_part = "0";
        if (integer_part.size() == 0)
        {
            integer_part = "0";
        }
    }
    else
    {
        integer_part = str.substr(0, decimal_position);
        decimal_part = str.substr(decimal_position + 1, str.size() - decimal_position - 1);
    }
}

bool add(char &sum, const vector<char> vec_addend)
{
    int int_sum = accumulate(vec_addend.begin(), vec_addend.end(), -('0' * vec_addend.size()));
    if (int_sum > 9)
    {
        sum = int_sum - 10 + '0';
        return true;
    }
    else
    {
        sum = int_sum + '0';
        return false;
    }
}

bool add(string & sum, const string &src, const string &dest, const bool &carry)
{
    bool bool_add = (carry? true : false);
    for (int i = src.size() - 1; i >= 0; i--)
    {
        char c_sum;
        vector<char> vec_addend;
        vec_addend.push_back(src[i]);
        vec_addend.push_back(dest[i]);
        if (bool_add)
        {
            vec_addend.push_back('1');
        }
        if (add(c_sum, vec_addend))
        {
            bool_add = true;
        }
        else
        {
            bool_add = false;
        }
        sum = c_sum + sum;
    }
    return bool_add;
}

string sum(const string &src, const string &dest)
{
    int src_decimal_number = 0, dest_decimal_number = 0;
    int src_decimal_position = -1, dest_decimal_position = -1;
    if (verification_string_is_number(src, src_decimal_number, src_decimal_position) &&
        verification_string_is_number(dest, dest_decimal_number, dest_decimal_position))
    {
        // cout << "src_decimal" << src_decimal_number << src_decimal_position << endl;
        // cout << "dest_decimal" << dest_decimal_number << dest_decimal_position << endl;
        string src_integer_part, src_decimal_part;
        string dest_integer_part, dest_decimal_part;

        if (src_decimal_number == 1)
        {
            sub_number(src, src_decimal_position, src_integer_part, src_decimal_part);
        }
        else if (src_decimal_number == 0)
        {
            if (src.size() == 0)
            {
                src_integer_part = "0";
            }
            else
            {
                src_integer_part = src;
            }
            src_decimal_part = "0";
        }
        else
        {
            return src + dest;
        }

        if (dest_decimal_number == 1)
        {
            sub_number(dest, dest_decimal_position, dest_integer_part, dest_decimal_part);
        }
        else if (dest_decimal_number == 0)
        {
            if (dest.size() == 0)
            {
                dest_integer_part = "0";
            }
            else
            {
                dest_integer_part = dest;
            }
            dest_decimal_part = "0";
        }
        else
        {
            return src + dest;
        }

        if (src_integer_part.size() > dest_integer_part.size())
        {
            string str_zero(src_integer_part.size() - dest_integer_part.size(),'0');
            dest_integer_part = str_zero + dest_integer_part;
        }
        else
        {
            string str_zero(dest_integer_part.size() - src_integer_part.size(),'0');
            src_integer_part = str_zero + src_integer_part;
        }
        if (src_decimal_part.size() > dest_decimal_part.size())
        {
            string str_zero(src_decimal_part.size() - dest_decimal_part.size(),'0');
            dest_decimal_part = str_zero + dest_decimal_part;
        }
        else
        {
            string str_zero(dest_decimal_part.size() - src_decimal_part.size(),'0');
            src_decimal_part = str_zero + src_decimal_part;
        }

        // cout << "src_integer " << src_integer_part << ", src_decimal " << src_decimal_part << endl;
        // cout << "dest_integer " << dest_integer_part << ", dest_decimal " << dest_decimal_part << endl;

        string sum;
        if (add(sum, src_decimal_part, dest_decimal_part, false))
        {
            // cout << "decimal_sum 1 " << sum << endl;
            string integer_sum;
            if (add(integer_sum, src_integer_part, dest_integer_part, true))
            {
                integer_sum = "1" + integer_sum;
            }
            // cout << "integer_sum 1 " << integer_sum << endl;
            return integer_sum + "." +sum;
        }
        else
        {
            // cout << "decimal_sum 2 " << sum << endl;
            string integer_sum;
            if (add(integer_sum, src_integer_part, dest_integer_part, false))
            {
                integer_sum = "1" + integer_sum;
            }
            // cout << "integer_sum 2 " << integer_sum << endl;
            if (sum == "0")
            {
                return integer_sum;
            }
            return integer_sum + "." +sum;
        }
    }
    else
    {
        return src + dest;
    }
}

template <typename M, typename N>
string sum(const M &src, const N &dest)
{
    string str_src, str_dest;
    stringstream stream;
    stream << src;
    str_src = stream.str();
    // cout << "str_src" << str_src << endl;
    stream.str("");
    stream.clear();
    stream << dest;
    str_dest = stream.str();
    // cout << "str_dest" << str_dest << endl;
    return sum(str_src, str_dest);
}

template <typename M, typename N>
void print_sum(const M src, const N dest)
{
    cout << src << " + " << dest << " = ";
    cout << sum(src, dest) << endl;
}

int main(int argc, char *argv[])
{
    print_sum("1", "2");
    print_sum("111", "2");
    print_sum("1", "222");
    print_sum("1.1", "2.2");
    print_sum("0", "0");
    print_sum("1", "0");
    print_sum("0", "1");
    print_sum("1.11", "2.2");
    print_sum("11.1", "2.2");
    print_sum("1.1", "22.2");
    print_sum(".1", "2");
    print_sum("1", ".2");
    print_sum("1", ".");
    print_sum(".", "2");
    print_sum("", "2");
    print_sum("1", "");
    print_sum("", "");
    print_sum(".", ".");
    print_sum(".", "..");
    print_sum("..", ".");
    print_sum("142868364868168624628628364376382682376473", "47927492742974297429472947294279749274974927294729472947298472947294729742974274297294");
    print_sum(1, 0);
    print_sum(1, 2);
    print_sum(0, 2);
    print_sum(0.0, 0.0);
    print_sum(0.1, 2);
    print_sum(1, 0.22);
    print_sum(1, "");
    print_sum("", 0);
    //print_sum(12787497927597295739957397397539753975937539, 35937593759375397593753975397593739753979729792597692769279279579275975375937927592795793579);
    return 0;
}
