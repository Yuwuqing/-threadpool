// 线程池项目.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "threadpool.h"
using uLong = unsigned long long;

class MyTask : public Task
{
public:
    MyTask(int begin, int end)
        : begin_(begin)
        , end_(end)
    {}

    Any run()  
    {
        std::cout << "tid:" << std::this_thread::get_id()
            << "begin!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        uLong sum = 0;
        for (uLong i = begin_; i <= end_; i++)
            sum += i;
        std::cout << "tid:" << std::this_thread::get_id()
            << "end!" << std::endl;

        return sum;
    }

private:
    int begin_;
    int end_;
};

int main()
{
    {
        ThreadPool pool;
        pool.setMode(PoolMode::MODE_CACHED);
        // 开始启动线程池
        pool.start(2);

        //在vs下，条件变量析构会释放相应资源的.linux下没有
        Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        uLong sum1 = res1.get().cast_<uLong>();
        cout << sum1 << endl; 
    } 
    
    cout << "main over!" << endl;
    getchar();

}
