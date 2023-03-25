#include "thread_pool.h"
#include <iostream>
#include <string>
#include <atomic>

thread_pool& thread_pool::instance(){
	static thread_pool result(10);
	return result;
}

thread_pool::thread_pool(size_t num_threads):num_threads(num_threads){
}

thread_pool::~thread_pool(){
	stop();
}

void thread_pool::start(){

	for(unsigned int count = 0; count < num_threads; count++){
		workers.emplace_back([=]{
			while(true){
				job task;
				{
					std::unique_lock<std::mutex> lock(mutex_object);
				
					condition.wait(lock,[=]{return terminate || !jobs.empty();});

					if(terminate && jobs.empty())
						break;


					task = std::move(jobs.front());
					jobs.pop();
				}
				
				task();
			}
		});
	}
}

void thread_pool::stop() noexcept{
	{
		std::unique_lock<std::mutex> lock(mutex_object);
		terminate = true;
	}

	condition.notify_all();

	for(std::thread& worker:workers){
		worker.join();
	}

	workers.clear();
}

void thread_pool::set_num_threads(std::size_t num){
	num_threads = num;
}

void thread_pool::add_job(job task){
	{
		std::unique_lock<std::mutex> lock(mutex_object);
		jobs.emplace(std::move(task));
	}

	condition.notify_one();
}
