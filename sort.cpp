#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // для sort,find_if
#include <utility> // для pair

using namespace std;

#define  INCREASE  '<'
#define  DECREASE  '>'

bool string_have_only_number(string str)
{
    bool minus = false;
    bool dot = false; // для чисел с плавающей точкой
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '.' && dot == false)
        {//только 1 точка
            dot = true;
            continue;
        }
        if(str[i] == '-' && minus == false) 
        {// только 1 минус
            minus = true;
            continue;
        };
        if(str[i] < '0' || str[i] > '9') 
        {// только цифры
            return false;
        }
    }
    return true;
    //в строке только цифры
}

bool string_have_only_words(string str)
{
     auto digits = find_if(str.begin(),str.end(),[](char c) { return c >= '0' && c <= '9'; });
     return digits == end(str);
     // есть ли цифры?(digits == null)
}

vector<vector<string>> split_into_subvectors(vector<string> content)
{
    vector<vector<string>> separator = 
    {
        {}, // words 0
        {}, // numbers 1
        {} // mixed words and numbers 2
    };
    
    for(int i = 0; i < content.size(); i++)
    {
        if(string_have_only_words(content[i])) 
            separator[0].push_back(content[i]);
        else if(string_have_only_number(content[i])) 
            separator[1].push_back(content[i]);
        else
            separator[2].push_back(content[i]);
    }
    return separator;
}

void sort_numbers(vector<string>& character_numbers,char comparison)
{
    vector<pair<double,int>> digit_numbers; // first number second index
    //pair - структура данных которая хранит в себе
    // 2 любых типа данных в first и second
    
    for(int i = 0; i < character_numbers.size(); i++)
    {
        digit_numbers.push_back( make_pair<double,int>( stod(character_numbers[i]),int(i) ) );
        //stod(string to double) - конвертирует string в double
        //make_pair - создает pair
    }
    
    if(comparison == DECREASE)
        sort(digit_numbers.begin(),digit_numbers.end(),[](pair<double,int> f,pair<double,int> s){ return f.first > s.first; });
    else if(comparison == INCREASE)
        sort(digit_numbers.begin(),digit_numbers.end(),[](pair<double,int> f,pair<double,int> s){ return f.first < s.first; });
    //sort - использует трехкратную гибридную технику сортировки под названием Introsort . 
    //Это комбинация быстрой сортировки , сортировки кучи и сортировки вставками.
        
    vector<string> sorted;
    for(int i = 0; i < digit_numbers.size(); i++)
    {
        sorted.push_back(character_numbers[digit_numbers[i].second]);
        //добавляем в вектор sorted
        //числа из оригинального вектора
        //по отсортированным индексам
    }
    character_numbers = sorted;
    //присваиваем отсортированные числа
}

void sort_words(vector<string>& words,char comparison)
{
    if(comparison == DECREASE)
        sort(words.begin(),words.end(),[](string f,string s){ return f > s; });
    else if(comparison == INCREASE)
        sort(words.begin(),words.end(),[](string f,string s){ return f < s; });
    //обычная сортировка по алфавиту
}

vector<string> get_numbers_from_string(vector<string> content)
{
    vector<string> numbers;
    string numb;
    for(int i = 0; i < content.size(); i++)
    {
        auto begin = find_if(content[i].begin(),content[i].end(),[](char c) { return (c >= '0' && c <= '9');});
        //указатель на первую цифру в строке
        auto end = find_if(begin,content[i].end(),[](char c) { return (c < '0' || c > '9');});
        //указатель на последнюю цифру в строке
        for(;begin != end;begin++)
        {
            numb +=  *begin;
            //записует число
        }
        numbers.push_back(numb);
        numb = "";
    }
    return numbers;
}

void sort_mixed_words_and_numbers(vector<string>& content,char comparison)
{
    vector<string> numbers = get_numbers_from_string(content);
    vector<pair<double,int>> numbers_with_index; // first numb second index
    //pair - структура данных которая хранит в себе
    // 2 любых типа данных в first и second
    
    for(int i = 0; i < numbers.size(); i++)
    {
        numbers_with_index.push_back(make_pair<double,int>(stod(numbers[i]),int(i)));
        //stod(string to double) - конвертирует строку в double
        //make_pair - создает pair
    }
    
    if(comparison == DECREASE)
        sort(numbers_with_index.begin(),numbers_with_index.end(),[](pair<double,int> f,pair<double,int> s) { return f.first > s.first; });
    else if(comparison == INCREASE)
        sort(numbers_with_index.begin(),numbers_with_index.end(),[](pair<double,int> f,pair<double,int> s) { return f.first < s.first; });
    //sort - использует трехкратную гибридную технику сортировки под названием Introsort. 
    //Это комбинация быстрой сортировки , сортировки кучи и сортировки вставками.
    
    vector<string> sorted;
    for(int i = 0; i < numbers.size(); i++)
    {
        sorted.push_back(content[numbers_with_index[i].second]);
        //добавляем в вектор sorted
        //числа из оригинального вектора
        //по отсортированным индексам
    }
    content = sorted;
    //присваиваем отсортированные строки
}

vector<string> concatenation_subvectors(vector<vector<string>> word_mix_numb)
{
    vector<string> content;
    for(int i = 0; i < word_mix_numb.size(); i++)
    {
        for(int j = 0; j < word_mix_numb[i].size(); j++)
        {
            content.push_back(word_mix_numb[i][j]);
        }
    }
    return content;
}


void sort(vector<string>& content,int comparison)
{
    vector<vector<string>> separator = split_into_subvectors(content);
    vector<string> words = separator[0];
    vector<string> numbers = separator[1];
    vector<string> mix = separator[2];
    sort_numbers(numbers,comparison);
    sort_words(words,comparison);
    sort_mixed_words_and_numbers(mix,comparison);
    content = concatenation_subvectors(vector<vector<string>> { words,mix,numbers } );
}

int main()
{
    vector<string> test =
    {
        "content with file 1",
        "content with file 8",
        "content with file 11",
        "cont1ent",
        "cont150ent",
        "cont22ent",
        "cont33ent",
        "cont334ent",
        "cont203ent",
        "content with file 22",
        "content with file 33",
        "-0.333",
        "-1.23",
        "content with file 334",
        "content with file 203",
        "-0.234",
        "0.290",
        "1",
        "1150",
        "0",
        "-1.24",
        "-1.234",
        "-9000",
        "cont8ent",
        "cont11ent",
        "cont2ent",
        "cont10ent",
        "cont3ent",
        "1.234567",
        "423",
        "-4563",
        "Utopia show",
        "OOp",
        "C++",
        "-0.234567",
        "Day",
        "Day of the day",
        "Data science",
        "Doom doom",
        "5898",
        "-3",
        "Moonlight",
        "9",
        "Bad boy",
        "A",
        "c",
        "content with file 2",
        "content with file 10",
        "content with file 3",
        "content with file 150",
        "D",
        "a",
        "B",
        "2",
        "3",
        "0.1",
        "0.254789",
        "d",
        "b",
        "10",
        "123124",
        "-1",
        "-254",
        "-0.25",
        "-0.1",
        "Asc",
        "csa"
    };
    
    vector<string> copy_test = test; 
    
    sort(test,INCREASE);
    
    cout << "\n-------------------\nНа увеличение:\n-------------------\n";
    for(int i = 0; i < test.size(); i++)
    {
        cout << test[i] << endl;
    }
    
    sort(copy_test,DECREASE);
    cout << "\n-------------------\nНа уменьшение:\n-------------------\n";
    for(int i = 0; i < test.size(); i++)
    {
        cout << copy_test[i] << endl;
    }
}