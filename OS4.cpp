#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//求平均寻道长度
double average(const vector<int>& length) {
    double sum = 0;
    for (int x : length) {
        sum += x;
    }
    return sum / length.size();
}

//求移动总道数
int sum(const vector<int>& length) {
    int sum = 0;
    for (int x : length) {
        sum += x;
    }
    return sum;
}

//先来先服务算法
void FCFS(const vector<int>& request, int start) {
    vector<int> next; //定义一个整数向量，用来存放访问序列
    vector<int> length; //定义一个整数向量，用来存放每次访问所移动的磁道数
    int now = start; //定义一个整数变量，用来记录当前磁头位置，初始值为start
    for (int x : request) 
    { //遍历请求向量中的每个元素
        next.push_back(x); //将当前元素加入访问序列
        length.push_back(abs(x - now)); //计算当前元素与当前磁头位置的差的绝对值，加入移动长度向量
        now = x; //更新当前磁头位置为当前元素
    }
    cout << "\nFCFS调度结果:\n"; //输出一行提示信息
    cout << "磁道的服务顺序: "; //输出一行提示信息
    for (int x : next) 
    { //遍历访问序列中的每个元素
        cout << x << " ";
    }
    cout << "\n移动的总道数: " << sum(length) << "\n"; //输出一行提示信息和移动长度向量的和
    cout << "平均寻道长度: " << average(length) << "\n"; //输出一行提示信息和移动长度向量的平均值
}

void SSTF(const vector<int>& request, int start) { //定义一个函数，参数是一个整数向量（表示请求的磁道号）和一个整数（表示初始磁头位置）
    vector<int> next; //定义一个整数向量，用来存放访问序列
    vector<int> length; //定义一个整数向量，用来存放每次访问所移动的磁道数
    vector<bool> visited(request.size(), false); //定义一个布尔向量，用来标记某个请求是否已被访问过
    int now = start; //定义一个整数变量，用来记录当前磁头位置，初始值为start
    for (int i = 0; i < request.size(); i++) 
    { 
        //遍历请求向量中的每个元素
        int min = INT_MAX; //定义一个整数变量，用来记录最短距离，初始值为最大整数
        int flag = -1; //定义一个整数变量，用来记录最短距离对应的下标，初始值为-1
        for (int j = 0; j < request.size(); j++) //遍历请求向量中的每个元素
        {
            if (!visited[j] && abs(request[j] - now) < min) { //如果当前元素没有被访问过，并且与当前磁头位置的差的绝对值小于最短距离
            min = abs(request[j] - now); //更新最短距离为当前差的绝对值
            flag = j; //更新最短距离对应的下标为当前下标
            }
        }
        next.push_back(request[flag]); //将最短距离对应的元素加入访问序列
        length.push_back(min); //将最短距离加入移动长度向量
        visited[flag] = true; //将最短距离对应的元素标记为已访问
        now = request[flag]; //更新当前磁头位置为最短距离对应的元素
    }
    cout << "\nSSTF调度结果:\n"; 
    cout << "磁道的服务顺序: "; 
    for (int x : next) 
    { //遍历访问序列中的每个元素
        cout << x << " "; 
    }
    cout << "\n移动的总道数: " << sum(length) << "\n"; //输出移动的总道数的标题和值，后面换行
    cout << "平均寻道长度: " << average(length) << "\n"; //输出平均寻道长度的标题和值，后面换行
}

//电梯算法
//先对请求进行排序，然后确定当前磁头在已排序序列中的位置。然后，它按照排序后的顺序服务磁道
void SCAN(const vector<int>& request, int start) { //定义一个函数，参数是一个整数向量（表示请求的磁道号）和一个整数（表示初始磁头位置）
    vector<int> next; //定义一个整数向量，用来存放访问序列
    vector<int> length; //定义一个整数向量，用来存放每次访问所移动的磁道数
    vector<int> sorted(request); //定义一个整数向量，用来存放排序后的请求
    sort(sorted.begin(), sorted.end()); //对请求向量进行升序排序
    int now = start; //定义一个整数变量，用来记录当前磁头位置，初始值为start
    int flag = 0; //定义一个整数变量，用来记录当前磁头在已排序序列中的位置，初始值为0
    while (sorted[flag] < now) 
    { //当当前位置小于当前磁头位置时
        flag++; //将当前位置加1
    }
    //先沿一个方向移动
    for (int i = flag; i < sorted.size(); i++) { //从当前位置开始，遍历排序后的请求向量中的每个元素
        next.push_back(sorted[i]); //将当前元素加入访问序列
        length.push_back(abs(sorted[i] - now)); //计算当前元素与当前磁头位置的差的绝对值，加入移动长度向量
        now = sorted[i]; //更新当前磁头位置为当前元素
        }
    //再沿相反方向移动
    for (int i = flag - 1; i >= 0; i--) { //从当前位置减1开始，倒序遍历排序后的请求向量中的每个元素
        next.push_back(sorted[i]); //将当前元素加入访问序列
        length.push_back(abs(sorted[i] - now)); //计算当前元素与当前磁头位置的差的绝对值，加入移动长度向量
        now = sorted[i]; //更新当前磁头位置为当前元素
    }
    cout << "\nSCAN调度结果:\n"; 
    cout << "磁道的服务顺序: "; 
    for (int x : next) 
    { //遍历访问序列中的每个元素
        cout << x << " ";
    }
    cout << "\n移动的总道数: " << sum(length) << "\n"; //输出移动的总道数的标题和值，后面换行
    cout << "平均寻道长度: " << average(length) << "\n"; //输出平均寻道长度的标题和值，后面换行
}

vector<int> readRequestFromFile(const string& filename) {
    vector<int> request;
    ifstream fin(filename);
    if (fin) {
        int x;
        while (fin >> x) {
            request.push_back(x);
        }
        fin.close();
    }
    else {
        cout << "无法打开文件: " << filename << "\n";
    }
    return request;
}

void performDiskScheduling(const vector<int>& request, int start) {
    cout << "----------------------------------------" << endl;
    cout << "磁盘调度算法" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    cout << "先来先服务算法 (FCFS):" << endl;
    FCFS(request, start); //先来先服务算法
    cout << endl;

    cout << "最短寻道时间优先算法 (SSTF):" << endl;
    SSTF(request, start); //最短寻道时间优先算法
    cout << endl;

    cout << "电梯算法 (SCAN):" << endl;
    SCAN(request, start); //电梯算法
    cout << endl;

    cout << "----------------------------------------" << endl;
}

int main() {
    string filename;
    cout << "请输入磁道服务顺序文件名: ";
    cin >> filename;
    string validFilename = filename + ".txt";

    vector<int> request = readRequestFromFile(validFilename); //读取磁道服务顺序

    if (!request.empty()) 
    {
        int start; //开始磁道号
        cout << "请输入开始磁道号: ";
        cin >> start;
        cout << endl;

        performDiskScheduling(request, start);
    }
    return 0;
}