#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int buffer_size, matrix_width, matrix_height, number_of_sequences;
vector<vector<string>> matrix;
vector<vector<string>> list_sequence;
vector<int> list_reward;
vector<pair<int, int>> result_point, temp_result_point;
vector<string> result, temp_result;
int max_value;
int debug;
int len_result;

bool isSubArray(const vector<string> &arr, const vector<string> &subarr)
{
    size_t arrSize = arr.size(), subarrSize = subarr.size();
    if (arrSize < subarrSize)
        return false;

    for (size_t i = 0; i <= arrSize - subarrSize; ++i)
    {
        bool match = true;
        for (size_t j = 0; j < subarrSize; ++j)
        {
            if (arr[i + j] != subarr[j])
            {
                match = false;
                break;
            }
        }
        if (match)
            return true;
    }
    return false;
}

void solve(int x, int y, bool ver, int num)
{
    if (matrix[y][x] == "" || num > buffer_size)
    {
        return;
    }
    int value = 0;
    for (int i = 0; i < number_of_sequences; i++)
    {
        if (isSubArray(temp_result, list_sequence[i]))
        {
            value += list_reward[i];
        }
    }
    if (value > max_value || (value == max_value && len_result > temp_result.size()))
    {
        len_result = temp_result.size();
        result = temp_result;
        max_value = value;
        result_point = temp_result_point;
    }

    if (ver)
    {
        // vertical move
        string temp = matrix[y][x];
        matrix[y][x] = "";
        pair<int, int> point(y, x);
        temp_result_point.push_back(point);
        temp_result.push_back(temp);
        for (int i = 1; i < x; i++)
        {
            solve(i, y, !ver, num + 1);
        }
        for (int i = x + 1; i <= matrix_width; i++)
        {
            solve(i, y, !ver, num + 1);
        }
        matrix[y][x] = temp;
        temp_result_point.pop_back();
        temp_result.pop_back();
        // solve(x, y + 1, ver, num);
    }
    else
    {
        // horizontal_move
        string temp = matrix[y][x];
        matrix[y][x] = "";
        pair<int, int> point(y, x);
        temp_result_point.push_back(point);
        temp_result.push_back(temp);
        for (int i = 1; i < y; i++)
        {
            solve(x, i, !ver, num + 1);
        }
        for (int i = y + 1; i <= matrix_height; i++)
        {
            solve(x, i, !ver, num + 1);
        }
        matrix[y][x] = temp;
        temp_result_point.pop_back();
        temp_result.pop_back();
        // solve(x + 1, y, ver, num);
    }
}

int main()
{
    len_result = 10000000;
    max_value = 0;
    string name_file, input_choice;
    cout << "Pilih mau pakai file atau tidak (sebagai input)? y/n (case sensitive): ";
    cin >> input_choice;
    if (input_choice == "y")
    {
        cout << "input name file: ";
        cin >> name_file;
        // read from file
        ifstream file(name_file);
        if (!file.is_open())
        {
            cout << "Error opening file, check the file!!" << endl;
            return 1;
        }
        file >> buffer_size;
        file >> matrix_width >> matrix_height;
        int width = matrix_width + 2;
        vector<string> edge;
        for (int i = 0; i < width; i++)
        {
            edge.push_back("");
        }
        matrix.push_back(edge);
        for (int i = 0; i < matrix_height; i++)
        {
            vector<string> temp;
            temp.push_back("");
            for (int j = 0; j < matrix_width; j++)
            {
                string a;
                file >> a;
                temp.push_back(a);
            }
            temp.push_back("");
            matrix.push_back(temp);
        }

        matrix.push_back(edge);

        file >> number_of_sequences;

        string sequence_all;
        getline(file, sequence_all);
        for (int i = 0; i < number_of_sequences; ++i)
        {
            vector<string> sequence;
            int reward;
            getline(file, sequence_all);
            stringstream ss(sequence_all);
            string sequence_part;
            while (!ss.eof())
            {
                getline(ss, sequence_part, ' ');
                sequence.push_back(sequence_part);
            }
            file >> reward;
            list_sequence.push_back(sequence);
            list_reward.push_back(reward);
            getline(file, sequence_all);
        }
        file.close();
    }
    else
    {
        int token_unik;
        cout << "Masukkan jumlah token unik: ";
        cin >> token_unik;
        string token[token_unik];
        cout << "Masukkan token unik: ";
        for (int i = 0; i < token_unik; i++)
        {
            cin >> token[i];
        }
        cout << "Masukkan jumlah ukuran buffer: ";
        cin >> buffer_size;
        cout << "Masukkan ukuran matriks (kolom baris): (gunakan spasi)  ";
        cin >> matrix_width >> matrix_height;
        cout << "Masukkan jumlah sekuens: ";
        cin >> number_of_sequences;
        cout << "Masukkan ukuran maksimum sekuens: ";
        int maks_sequnces;
        cin >> maks_sequnces;

        // generate
        int width = matrix_width + 2;
        vector<string> edge;
        for (int i = 0; i < width; i++)
        {
            edge.push_back("");
        }
        matrix.push_back(edge);
        for (int i = 0; i < matrix_height; i++)
        {
            vector<string> temp;
            temp.push_back("");
            for (int j = 0; j < matrix_width; j++)
            {
                string a;
                a = token[(rand() % token_unik)];
                temp.push_back(a);
            }
            temp.push_back("");
            matrix.push_back(temp);
        }
        matrix.push_back(edge);

        for (int i = 0; i < number_of_sequences; i++)
        {
            int len = (rand() % maks_sequnces) + 1;
            vector<string> sequence;
            for (int j = 0; j < len; j++)
            {
                sequence.push_back(token[rand() % token_unik]);
            }
            int reward;
            list_sequence.push_back(sequence);
            // range 10 to 50
            reward = (rand() % 41) + 10;
            list_reward.push_back(reward);
        }
    }
    auto start = high_resolution_clock::now();
    for (int i = 1; i <= matrix_width; i++)
    {

        string temp = matrix[1][i];
        matrix[1][i] = "";
        pair<int, int> point(i, 1);
        temp_result_point.push_back(point);
        temp_result.push_back(temp);
        for (int j = 2; j <= matrix_height; j++)
            solve(i, j, true, 1);
        matrix[1][i] = temp;
        temp_result_point.pop_back();
        temp_result.pop_back();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;

    cout << "Result:" << endl
         << endl;
    cout << "Matrix" << endl;
    for (auto &it : matrix)
    {
        for (auto &it1 : it)
        {
            cout << it1 << " ";
        }
        cout << endl;
    }

    cout << "List sequence and reward" << endl;
    for (int i = 0; i < number_of_sequences; i++)
    {
        int len = list_sequence[i].size();
        for (int j = 0; j < len; j++)
        {
            cout << list_sequence[i][j] << " ";
        }
        cout << endl;
        cout << list_reward[i] << endl
             << endl;
    }
    cout << "Total Reward" << endl;
    cout << max_value << endl;
    for (auto &it : result)
    {
        // Print the values
        cout << it << " ";
    }
    cout << endl;
    for (auto &it : result_point)
    {
        // Print the values
        cout << it.first << ", " << it.second << endl;
    }

    string output_choice, file_name;
    cout << "Mau save? (y/n) case sensitive: ";
    cin >> output_choice;
    if (output_choice == "y")
    {
        cout << "Masukkan nama file (nama saja): ";
        cin >> file_name;
        ofstream outputFile(file_name + ".txt");

        if (outputFile.is_open())
        {
            outputFile << "List sequence and reward" << endl;
            for (int i = 0; i < number_of_sequences; i++)
            {
                int len = list_sequence[i].size();
                for (int j = 0; j < len; j++)
                {
                    outputFile << list_sequence[i][j] << " ";
                }
                outputFile << endl;
                outputFile << list_reward[i] << endl
                           << endl;
            }
            outputFile << "Total Reward" << endl;
            outputFile << max_value << endl;
            for (auto &it : result)
            {
                // Print the values
                outputFile << it << " ";
            }
            outputFile << endl;
            for (auto &it : result_point)
            {
                // Print the values
                outputFile << it.first << ", " << it.second << endl;
            }
            cout << "Data was written to " << file_name << ".txt" << endl;
        }
    }
    return 0;
}