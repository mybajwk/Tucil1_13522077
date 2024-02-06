#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
using namespace std;

int buffer_size, matrix_width, matrix_height, number_of_sequences;
vector<vector<int>> matrix;
vector<vector<int>> list_sequence;
vector<int> list_reward;
vector<pair<int, int>> result_point, temp_result_point;
vector<int> result, temp_result;
int max_value;
int debug;

bool isSubArray(vector<int> &arr, vector<int> &subarr)
{
    if (arr.size() < subarr.size())
        return false;
    for (size_t i = 0; i <= arr.size() - subarr.size(); ++i)
    {
        bool match = true;
        for (size_t j = 0; j < subarr.size(); ++j)
        {
            if (arr[i + j] != subarr[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }
    return false;
}

void solve(int x, int y, bool ver, int num)
{
    if (matrix[y][x] == -1 || num > buffer_size)
    {
        // cout << x << " " << y << "aaaaaaaa";
        return;
    }
    // do some checking
    // for (auto &it : temp_result)
    // {
    //     // Print the values
    //     cout << it << ' ';
    // }
    // for (auto &it : temp_result_point)
    // {
    //     // Print the values
    //     cout << it.first << "," << it.second << ' ';
    // }
    // cout << endl;
    int value = 0;
    for (int i = 0; i < number_of_sequences; i++)
    {
        if (isSubArray(temp_result, list_sequence[i]))
        {
            // cout << "aaa";
            value += list_reward[i];
        }
    }
    if (value > max_value)
    {
        // cout << ":coi" << endl;
        result = temp_result;
        max_value = value;
        result_point = temp_result_point;
    }

    if (ver)
    {
        // cout << "a";
        // vertical move
        int temp = matrix[y][x];
        matrix[y][x] = -1;
        pair<int, int> point(y, x);
        temp_result_point.push_back(point);
        temp_result.push_back(temp);
        solve(x + 1, y, !ver, num + 1);
        for (int i = 1; i < matrix_width; i++)
        {
            if (i != x)
                solve(i, y, !ver, num + 1);
        }
        // if (x > 2)
        //     solve(x - 2, y, !ver, num + 1);

        // cout << x << "aaa" << y << endl;
        matrix[y][x] = temp;
        temp_result_point.pop_back();
        temp_result.pop_back();
        solve(x, y + 1, ver, num);
        // solve(x, y - 1, ver, num);
    }
    else
    {
        // horizontal_move
        int temp = matrix[y][x];
        matrix[y][x] = -1;
        pair<int, int> point(y, x);
        temp_result_point.push_back(point);
        temp_result.push_back(temp);
        solve(x, y + 1, !ver, num + 1);
        // solve(x, y - 1, !ver, num + 1);
        for (int i = 1; i < matrix_height; i++)
        {
            if (i != y)
                solve(x, i, !ver, num + 1);
        }
        // solve(x - 1, y, !ver, num + 1);

        matrix[y][x] = temp;
        temp_result_point.pop_back();
        temp_result.pop_back();
        solve(x + 1, y, ver, num);
        // solve(x - 1, y, ver, num);
    }
}

int main()
{
    max_value = 0;
    // read from file
    ifstream file("input.in");
    if (!file.is_open())
    {
        cout << "Error opening file, check the file!!" << endl;
        return 1;
    }
    file >> buffer_size;
    file >> matrix_width >> matrix_height;
    int width = matrix_width + 2;
    vector<int> edge;
    for (int i = 0; i < width; i++)
    {
        edge.push_back(-1);
    }
    matrix.push_back(edge);
    for (int i = 0; i < matrix_height; i++)
    {
        vector<int> temp;
        temp.push_back(-1);
        for (int j = 0; j < matrix_width; j++)
        {
            string a;
            file >> a;
            temp.push_back(stoi(a, 0, 16));
        }
        temp.push_back(-1);
        matrix.push_back(temp);
    }

    matrix.push_back(edge);

    file >> number_of_sequences;

    string sequence_all;
    getline(file, sequence_all);
    for (int i = 0; i < number_of_sequences; ++i)
    {
        vector<int> sequence;
        int reward;
        getline(file, sequence_all);
        stringstream ss(sequence_all);
        string sequence_part;
        while (!ss.eof())
        {
            getline(ss, sequence_part, ' ');
            sequence.push_back(stoi(sequence_part, 0, 16));
        }
        file >> reward;
        list_sequence.push_back(sequence);
        list_reward.push_back(reward);
        getline(file, sequence_all);
    }

    // start
    int temp = matrix[1][1];
    matrix[1][1] = -1;
    pair<int, int> point(1, 1);
    temp_result_point.push_back(point);
    temp_result.push_back(temp);
    //
    cout << "a " << endl;
    solve(1, 2, true, 1);
    cout << "a " << endl;
    for (auto &it : result)
    {
        // Print the values
        cout << it << " ";
    }
    for (auto &it : result_point)
    {
        // Print the values
        cout << it.first << "," << it.second << " ";
    }
    cout << endl
         << max_value << endl;
    file.close();
    return 0;
}