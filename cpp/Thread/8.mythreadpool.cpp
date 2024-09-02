#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <vector>

class threadpool
{
public:
    threadpool(int num_thread):stop(false){
        for (int i = 0; i < num_thread;++i){
            threads.emplace_back([this] {
                while(true){
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock,[this]{return(stop||!tasks.empty());});
                    if(stop&&tasks.empty()){
                        return;
                    }
                    std::function<void()> task;
                    if (!tasks.empty())
                    {
                        task=std::move(tasks.front());
                        tasks.pop();
                    }
                    lock.unlock();
                    task();
                }
            });
            
        }
    }

    ~threadpool(){
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &thread : threads){
            thread.join();
        }
    }
    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args)
    {
        std::function<void()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable condition;
    bool stop;
};

int main() {
    threadpool pool(4);
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " is running in thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " is done" << std::endl;
        });
    }
    return 0;
}